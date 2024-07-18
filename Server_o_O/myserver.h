#ifndef MYSERVER_H
#define MYSERVER_H

#include "database.h"
#include "game.h"

#include <QDebug>
#include <QDir>
#include <QObject>
#include <QProcess>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>

class MyServer : public QObject
{
  Q_OBJECT
 public:
  explicit MyServer(QObject *parent = 0);

 public slots:

  void newConnection();
  void getMessage();

private:

  Game game;
  Database data;
  QTcpServer *server;
  QVector <std::pair <QTcpSocket*,QString>> socket_vector;

  int count = 0; // счётчик отправки всех активных пользователей временная замена пока не вставлю атймер с автоматической отправкой

  bool continu_e = true; // чтобы лишний раз не отравлять хз как по другому реализовать :/

  void userAdd(QString userName);
  void sendStartGame();
  bool checkUsername(QTcpSocket *socket, QString username);

};
#endif  // MYSERVER_H

