#ifndef NTDECK_H
#define NTDECK_H

#include <QObject>
#include "mainwindow.h"

class Ntdeck : public QObject
{
    Q_OBJECT
public:
    explicit Ntdeck(MainWindow * mainWindow, QObject *parent = 0);
    Q_INVOKABLE void hello();

signals:

public slots:

private:
    MainWindow * window;

};

#endif // NTDECK_H
