#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "game.h"

#include <QMainWindow>
#include <QTcpSocket>
#include <QDataStream>
#include <QProcess>
#include <QTimer>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

 public:
    MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:

  void sendToServer();

  void on_createQuery_clicked(); // замена статуса запроса на активный

  void slotSendRSP(RSP action);

  void ShowTimer();

  void showGame();

private:

  int second;
  QTimer *timer;
  Ui::MainWindow *ui;
  QTcpSocket *socket;
  QByteArray block; // delete (username)
  Game windGame;

  void newConnection();

 public slots:
  void getMessage();
};
#endif  // MAINWINDOW_H
