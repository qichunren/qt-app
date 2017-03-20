/*
# Copyright (c) 2016 Shanghai Novotech. All rights reserved.
*/

#ifndef NT_LOCAL_SERVER_H
#define NT_LOCAL_SERVER_H

#include <QObject>
#include <QLocalSocket>
#include <QTimer>


#define NtLocalServer_socket "nt_local_server.socket"

class QLocalServer;

class NtLocalSocket : public QObject
{
    Q_OBJECT

public:
    explicit NtLocalSocket(QLocalSocket * socket, QObject *parent = 0);
    QLocalSocket * socket() const;
    void start_feed_watch_dog();

    quint32 uptime() const;
    QString uptime_str() const;

public slots:

    void feed_watch_dog();

private:
    QLocalSocket * _socket_;
    QTimer *timer;
    quint32 start_at;
};


class NtLocalServer : public QObject
{
    Q_OBJECT

public:
    explicit NtLocalServer(QObject *parent = 0);
    ~NtLocalServer();
    void start();

signals:

public slots:

private slots:
    void serve_new_connection_handler();
    void socket_ready_read_handler();
    void socket_close_handler();

private:
    QLocalServer * _localServer_;    
    QHash<QLocalSocket *, NtLocalSocket *> _connections_;
};

#endif // NT_LOCAL_SERVER_H
