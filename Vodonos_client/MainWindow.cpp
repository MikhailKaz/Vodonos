#include "MainWindow.h"
#include <QThread>
#include "ui_MainWindow.h"
#include <iostream>
#include <cstdlib>

MainWindow::MainWindow(QWidget *parent)  // конструктор
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);

    block.append(QTime::currentTime().toString()); // delete (username)
    socket->connectToHost("127.0.0.1", 2424);
    qDebug() << socket->waitForConnected(10) << " - подключились к серверу";
    sendToServer();

    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::getMessage); // ожидание входящих данных
    connect(&windGame, &Game::selected, this, &MainWindow::slotSendRSP); // ожидание искусственного сигнала нажатия кнопки
}

MainWindow::~MainWindow() { delete ui; }  // деструктор

void MainWindow::sendToServer() // Отправка на сервер
{
    qDebug()<<"connect ot server...";
    //получение имени пользователя
    //char *username = std::getenv("USERNAME");

    socket->write("0 " + block); // #здесь должен быть юзернэйм
}

void MainWindow::ShowTimer(){
    second--;
    if(second >= 0){
        ui->plainTextEdit->setPlainText("                 "+
        QString::number(second));
    }
    else{
        timer->stop();
        showGame();
    }
}

void MainWindow::showGame(){
    windGame.startGame();
    windGame.setModal(true); // короче теперь windGame это всплывающее окно новое :/
    windGame.setWindowTitle("Client");
    windGame.show();
}

void MainWindow::getMessage() // получения c сервера
{
    QString str = socket->readAll(), input = str.right(str.size()-2); // обрезаем саму команду

    qDebug()<<"GET MESSAGE :" << str.split(" ")[0].toInt() << input;
    switch (str.split(" ")[0].toInt()){ // обарботчик всех событий (берём 1 элемент str он является событием)
    case 0:{ // запуск игры
        ui->plainTextEdit->setPlainText("  Reuest accepted!");
        ui->createQuery->setEnabled(false);
        timer = new QTimer(this);
        second = 5;
        QObject::connect(timer,&QTimer::timeout,this,&MainWindow::ShowTimer);
        timer->start(1000);
        break;
    }
    case 1: // нашли "победителя" (данный user)
        windGame.close();
        ui->plainTextEdit->setPlainText("Иди за водой чорт");
        break;
    case 2: // нашли "победителя" (получение username того кто идёт)
        windGame.close();
        ui->plainTextEdit->setPlainText("За водой идёт:" + input);
        break;
    case 3: // вы выбыли
        windGame.close();
        ui->plainTextEdit->setPlainText("        Вы выбыли");
        break;
    case 4: // вы продолжаете играть
        windGame.close();
        ui->plainTextEdit->setPlainText("     Вы продолжаете");
        socket->write("1"); // играем снова
        break;
    case 5: // ничья
        windGame.close();
        ui->plainTextEdit->setPlainText("        Ничья");
        socket->write("1"); // играем снова
        break;
    }
}

void MainWindow::slotSendRSP(RSP action) // 1 - символ событие для get message 2 - какая была нажата кнопка
{
    switch (action) {
    case 0:
        socket->write("2 0");
        break;
    case 1:
        socket->write("2 1");
        break;
    case 2:
        socket->write("2 2");
        break;
    }
}

void MainWindow::on_createQuery_clicked() // смена статуса запроса на активный
{
    socket->write("1");
}


