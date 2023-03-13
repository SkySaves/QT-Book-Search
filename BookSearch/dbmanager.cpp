#include "dbmanager.h"

DBmanager::DBmanager(const QString& path)
{

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database failed";
    }

    else
    {
        qDebug() << "DatabaseL connection ok";
    }

    m_db.close();



}
