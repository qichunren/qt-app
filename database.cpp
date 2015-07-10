#include "database.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

Database::Database(QObject *parent) :
    QObject(parent)
{
}


bool Database::connect(const QString &host, const QString &uname, const QString &pwd, const QString &name)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(host);
    db.setDatabaseName(name);
    db.setUserName(uname);
    db.setPassword(pwd);

    qDebug() << "Available db drivers: "<< QSqlDatabase::drivers();

    if (db.open())
    {
            qDebug() << "Connect mysql db success!";
            return true;
    }
    else
    {
        qDebug() << "Failed to connect mysql db." << db.lastError().text();
        return false;
    }
}


QList<QString> Database::get_all()
{
    QList<QString> recordList;
    QSqlQuery query;
    query.exec("SELECT id, name, longitude, latitude FROM stations order by id"); //
    while (query.next()) {

        recordList.append(query.value(1).toString());
    }
    return recordList;
}
