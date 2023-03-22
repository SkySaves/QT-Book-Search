#ifndef DBMANAGER_H
#define DBMANAGER_H



#include <QtSql/QtSql>

class DBmanager
{
public:
    DBmanager(const QString& path);

private:
    QSqlDatabase m_db;

};

#endif // DBMANAGER_H
