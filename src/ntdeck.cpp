#include "ntdeck.h"
#include <QDebug>

Ntdeck::Ntdeck(MainWindow *mainWindow, QObject *parent) :
    window(mainWindow),
    QObject(parent)
{

}

void Ntdeck::hello() {
    qDebug() << "Hello from qt";
    window->switchPage2();
}
