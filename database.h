#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = 0);
    static bool connect(const QString &host, const QString &uname, const QString &pwd, const QString &name);
    static QList<QString> get_all();

signals:

public slots:

};

#endif // DATABASE_H
