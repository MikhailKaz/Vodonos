#include "myserver.h"
#include <QObject>

MyServer::MyServer(QObject *parent) : QObject(parent)
{
  server = new QTcpServer(this);
  connect(server, SIGNAL(newConnection()), this, SLOT(newConnection())); // при новом подключении переходим к созданию нового подключения(сокета)

  if (!server->listen(QHostAddress::Any, 2424)) {
    qDebug() << "Server not started";
  } else {
    qDebug() << "Start server...";
  }
}

// disconnected (удаление пользователя из баы данных иначе при новом подключении сокетпоменяется а пользователь не добавится)

// Отправка с сервера
void MyServer::newConnection()
{
    QTcpSocket *client = server->nextPendingConnection(); // создаём новый сокет
    connect(client, &QTcpSocket::readyRead, this, &MyServer::getMessage); // добавляем нового пользователя в db
    //qDebug() << "vector size socket :" << socket_vector.size();
}

bool MyServer::checkUsername(QTcpSocket *socket, QString username){
    for (int i = 0; i < socket_vector.size(); i++){
        if(socket_vector[i].second == username){ // если пользователь есть в db
            socket_vector[i].first = socket; // обновляем сокет пользователя
            return false;
        }
    }
    return true; // если пользователя нету
}

void MyServer::userAdd(QString userName){  // добавление пользователя в db

    qDebug() << "add user :" << userName;
    data.queryAdd(userName);

    //qDebug() << "number priority :" << data.getPriority(userName);
}

void MyServer::sendStartGame(){ // отправка сообщения о старте игры
    if(continu_e){
        for(int i = 0; i < socket_vector.size(); i++){
            socket_vector[i].first->write("0");
        }
        qDebug() << "SIZE SOCKET :" <<socket_vector.size();
        continu_e = false;
    }
}

void MyServer::getMessage(){ // получение пакета от пользователя (первое число сообщение номер события)

    QTcpSocket *socket = static_cast<QTcpSocket *>(sender()); // static_cast - преобразование типов, sender - указатель на объект
    QString str = socket->readAll(), input = str.right(str.size()-2); // обрезаем саму команду

    qDebug() << "message :" << str; //  QTcpSocket (номер сокета), номер дейтвия имя пользователя (0 student)

    switch (str.split(" ")[0].toInt()){ // обарботчик всех событий (берём 1 элемент str он является событием)
    case 0:
        if(checkUsername(socket, input)){ // если пользователя нету в bd обновляем ему socket
            socket_vector.push_back(std::make_pair(socket,input)); // сохранияем сокет и username
            userAdd(input);
        }
        break;
    case 1 :{
        sendStartGame();
        break;
    }
    case 2:{
        game.getValGame(input.toInt(), socket); // добавляем сокет пользователя и то что он выбрал (к,н,б)
        count++;
        if (count == socket_vector.size()){ // если пришла отправка от всех пользователей (по сути новый раунд)
            count = 0;
            continu_e = true;
            int ivent = game.calcul();
            if(ivent == 1){ // если есть "победитель"
                QByteArray block;
                for(int i = 0; i < socket_vector.size(); i++){ // нужно плучить имя пользователя сравниваем сокет проигравшего с vector_socket
                    if(socket_vector[i].first == game.socket){
                        block.append(socket_vector[i].second);
                    }
                }
                game.socket->write("1"); // отправка послания проигравшему
                for(int i = 0; i < socket_vector.size(); i++){
                    if(game.socket != socket_vector[i].first){
                        socket_vector[i].first->write("2 " + block); // 2 сценарий отпрака что они выбили
                    }
                }
            }
            else if (ivent != 0){ // если любое условие сработало и не было возврата 0
                qDebug() << "Out :" << game.userOut.size() << "Stay :" << game.userStay.size();

                for(int i = 0; i < game.userOut.size(); i++){ // выбывшие
                    game.userOut[i]->write("3");
                }
                for(int i = 0; i < game.userStay.size(); i++){ // продолжающие играть
                    game.userStay[i]->write("4");
                }
                for(int i = socket_vector.size() - 1; i >= 0; i--){ // удаляем выбывших из socket_vector
                    for(int j = 0; j < game.userOut.size(); j++){
                        if(socket_vector[i].first == game.userOut[j]){
                            socket_vector.erase(socket_vector.begin()+i);
                        }
                    }
                }
                game.clear(); // запускаем деструктор для нового раунда
            }
            else{
                //qDebug() << "IVENT RETURN 0";
                for(int i = 0; i < socket_vector.size(); i++){ // ничья
                    socket_vector[i].first->write("5");
                }
                game.clear();
            }
        }
        break;
    }
    }
}
