#include <QApplication>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.setWindowTitle("Vodonos 1.0.0");
  w.show();
  return a.exec();
}
