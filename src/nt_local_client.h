/*
# Copyright (c) 2016 Shanghai Novotech. All rights reserved.
*/

#ifndef NT_LOCAL_CLIENT_H
#define NT_LOCAL_CLIENT_H

#include <QObject>
#include <QLocalSocket>

class NtLocalClient : public QObject
{
    Q_OBJECT

public:
    explicit NtLocalClient(QObject *parent = 0);
    void connect_server();
    void send_msg(const char * message);

signals:

public slots:
    void socket_error(QLocalSocket::LocalSocketError error);
    void when_connected();
    void readyRead();

private:
    QLocalSocket * _client_;
};

#endif // NT_LOCAL_CLIENT_H
