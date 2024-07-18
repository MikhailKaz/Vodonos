#include "database.h"

Database::Database() { open(); }

void Database::open()
{
  db = QSqlDatabase::addDatabase("QSQLITE");

  db.setDatabaseName("./Users.db");
  QFileInfo checkFile("./Users.db"); // ???

  if (!db.open()) {
    qDebug() << "No connetion to data base";
  }  // функция открытия и проверка
  else{
      QSqlQuery qry;
      // not exits проверка на наличие таблица

      if(!qry.exec("CREATE TABLE IF NOT EXIST Users(Username TEXT, Priority INT)")){ // если таблицы не существует
          qry.exec("CREATE TABLE Users(Username TEXT, Priority INT)"); // то создаём её
      }
  }
}

void Database::queryAdd(QString str)
{
  QSqlQuery qry;
  QString query; // текст запроса

  //первый select - добавление, второй - проверка
  query = "INSERT INTO Users (Username, Priority) SELECT '" + str + "', 1 WHERE NOT EXISTS (SELECT 1 FROM Users WHERE Username = '" + str + "')";

  qry.exec(query);

}

int Database::getPriority(QString str){
    QSqlQuery qry;
    QString query; // текст запроса

    query = "SELECT Priority FROM Users WHERE Username = '" + str + "'";
    qry.exec(query);
    qry.next();
    return qry.value(0).toInt();
}

