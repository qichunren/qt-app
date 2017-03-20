/*
# Copyright (c) 2016 Shanghai Novotech. All rights reserved.
*/

#include "nt_local_server.h"

#include <QLocalServer>
#include <QLocalSocket>
#include <QProcess>
#include <QDateTime>

#define FEED_DOG_INTERVAL 5000

NtLocalSocket::NtLocalSocket(QLocalSocket *socket, QObject *parent) :
    QObject(parent),
    _socket_(socket),
    timer(new QTimer(this))
{
    start_at =  QDateTime::currentDateTime().toTime_t();
    timer->setInterval(FEED_DOG_INTERVAL);
    connect(timer, SIGNAL(timeout()), this, SLOT(feed_watch_dog()));
}

QLocalSocket * NtLocalSocket::socket() const
{
    return _socket_;
}

void NtLocalSocket::start_feed_watch_dog()
{
    QTimer::singleShot(0, this, SLOT(feed_watch_dog()));
    timer->start();
}

void NtLocalSocket::feed_watch_dog()
{
    if (_socket_ != NULL)
    {
        if (_socket_->state() == QLocalSocket::ConnectedState)
        {
            QString response = QString("NtBone %1\n").arg(1);
            _socket_->write(response.toUtf8());
            _socket_->flush();
        }
    }
}

quint32 NtLocalSocket::uptime() const
{
    return QDateTime::currentDateTime().toTime_t() - start_at;
}

QString NtLocalSocket::uptime_str() const
{
    quint32 duration = uptime();
    if (duration < 60)
    {
        return QString("%1 seconds").arg(duration);
    }
    else if (duration < 3600)
    {
        quint16 minutes = duration / 60;
        quint16 seconds = duration % 60;
        return QString("%1 min, %2 sec").arg(minutes).arg(seconds);
    }
    else
    {
        quint16 hours = duration / 3600;
        quint16 left_seconds = duration % 3600;
        quint16 minutes = left_seconds / 60;
        quint16 seconds = left_seconds % 60;
        return QString("%1 hours, %2 min, %3 sec").arg(hours).arg(minutes).arg(seconds);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NtLocalServer::NtLocalServer(QObject *parent) :
    QObject(parent),
    _localServer_(new QLocalServer(this))
{
    connect(_localServer_, SIGNAL(newConnection()), this, SLOT(serve_new_connection_handler()));
}

NtLocalServer::~NtLocalServer() {
    if (_localServer_)
        _localServer_->close();
}

void NtLocalServer::serve_new_connection_handler() {
    puts("New local socket connection comming.\n");
    QLocalSocket* socket = _localServer_->nextPendingConnection();
    if (socket != NULL)
    {
        NtLocalSocket * local_socket = new NtLocalSocket(socket);
        _connections_.insert(socket, local_socket);
        connect(socket, SIGNAL(readyRead()), this, SLOT(socket_ready_read_handler()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(socket_close_handler()));
    }
}

void NtLocalServer::socket_ready_read_handler() {
    QLocalSocket* socket = static_cast<QLocalSocket*>(sender());
    if (socket) {
        NtLocalSocket * local_socket = _connections_.value(socket);
        QString response;
        QTextStream stream(socket);
        QString receivedContent = stream.readAll();
        qDebug() << "********************* Local socket:" << receivedContent;
        if (receivedContent.startsWith("LASER_MODE:"))
        {            

        }       
        else if (receivedContent == "RESET" )
        {

        }
        else if (receivedContent == "PAIGO_WATCH_DOG")
        {
            local_socket->start_feed_watch_dog();
        }
    }
}

void NtLocalServer::socket_close_handler()
{
    QLocalSocket * socket = qobject_cast<QLocalSocket *>(sender());
    NtLocalSocket * local_socket = _connections_.value(socket);
    _connections_.remove(socket);
    local_socket->deleteLater();
}

void NtLocalServer::start()
{
    if (!_localServer_)
        return;
    QLocalServer::removeServer(NtLocalServer_socket);
    bool ok = _localServer_->listen(NtLocalServer_socket);
    if (!ok) {
        puts("Unable to start local server\n");
        exit(1);
    }
    puts("Local server listened.\n");
}
