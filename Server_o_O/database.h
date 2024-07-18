#ifndef DATABASE_H
#define DATABASE_H

#endif // DATABASE_H

#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QFileInfo>

class Database : public QObject
{
 public:
  explicit Database();

  QSqlDatabase db;

  void queryAdd(QString str); // добавление пользователя в db
  void open(); // открытие db
  int getPriority(QString str); // получение приоритета
};
