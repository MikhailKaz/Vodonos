#include "game.h"
#include "ui_game.h"

#include <QThread>

Game::Game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::game)
{
    ui->setupUi(this);
}

Game::~Game()
{
    delete ui;
}

void Game::on_pbRock_clicked()
{
    emit selected(Rock); // посылаем сигнал int 0(emit как пометка)
    ui->pbPaper->setEnabled(false);
    ui->pbRock->setEnabled(false);
    ui->pbScissors->setEnabled(false);
}

void Game::on_pbScissors_clicked()
{
    emit selected(Scissors); // посылаем сигнал int 1(emit как пометка)
    ui->pbPaper->setEnabled(false);
    ui->pbRock->setEnabled(false);
    ui->pbScissors->setEnabled(false);
}

void Game::on_pbPaper_clicked()
{
    emit selected(Paper); // посылаем сигнал int 2(emit как пометка)
    ui->pbPaper->setEnabled(false);
    ui->pbRock->setEnabled(false);
    ui->pbScissors->setEnabled(false);
}

void Game::randSelect(){
    //qsrand(QTime::currentTime().msec());
    qsrand(QDateTime::currentDateTime().toMSecsSinceEpoch());
    QThread *currentThread = QThread::currentThread();
    emit selected(RSP((qint64)currentThread->currentThreadId() / remain % 3));
}

void Game::ShowTimer(){
    count--;
    if(count >= 0){
        ui->plainTextEdit->setPlainText("              "
        +QString::number(count));
    }
    else{
        randSelect();
        timer->stop();
    }
}

void Game::startGame(){

    ui->pbPaper->setEnabled(true);
    ui->pbRock->setEnabled(true);
    ui->pbScissors->setEnabled(true);
    remain *= 10;
    if(remain > 100000000000000){
        remain = 1;
    }
    timer = new QTimer;
    count = 5;
    connect(timer, &QTimer::timeout,this, &Game::ShowTimer);
    timer->start(1000);
}
