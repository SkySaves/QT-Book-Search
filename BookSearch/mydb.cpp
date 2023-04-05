#include "mydb.h"

MyDB* MyDB::instance = nullptr;


MyDB::MyDB()
{
    init();
}
void MyDB::init()
{
    db = QSqlDatabase::addDatabase("QSQLITE", "Data");
    db.setDatabaseName("bookstore.db");

    if(QFile::exists("bookstore.db"))
            qDebug() << "DB file exist";
        else
           qDebug() << "DB file doesn't exists";

        if (!db.open())
            qDebug() << db.lastError().text();
        else
            qDebug() << "Database loaded successful!";

}

MyDB *MyDB::getInstance()
{
    qDebug() << "in MyDB::getInstance()";

    if(instance == nullptr)
        instance = new MyDB();

    return instance;

}

QSqlDatabase MyDB::getDBInstance()
{
    return db;
}

void MyDB::ResetInstance()
   {
      delete instance;
      instance = nullptr;
   }

MyDB::~MyDB()
{
   db.close();
}
