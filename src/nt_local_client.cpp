/*
# Copyright (c) 2016 Shanghai Novotech. All rights reserved.
*/

#include "nt_local_client.h"
#include <QTimer>
#include <cstdio>

NtLocalClient::NtLocalClient(QObject *parent) :
    QObject(parent),
    _client_(new QLocalSocket(this))
{    
    connect(_client_, SIGNAL(error(QLocalSocket::LocalSocketError)), this, SLOT(socket_error(QLocalSocket::LocalSocketError)));
    connect(_client_, SIGNAL(connected()), this, SLOT(when_connected()));
    connect(_client_, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void NtLocalClient::connect_server() {
    _client_->disconnectFromServer();
    _client_->connectToServer("nt_local_server.socket");
}

void NtLocalClient::send_msg(const char * message) {
    if (message == NULL)
    {
        printf("Null message send.\n");
        return;
    }

    _client_->write(message, strlen(message));
    _client_->flush();
}

// errors from emun QLocalSocket::LocalSocketError
// static const char * errors[] = {"ConnectionRefusedError", "PeerClosedError", "ServerNotFoundError", "SocketAccessError", "SocketResourceError",
//                   "SocketTimeoutError", "DatagramTooLargeError", "ConnectionError", "UnsupportedSocketOperationError",
//                   "UnknownSocketError", "OperationError"};

void NtLocalClient::socket_error(QLocalSocket::LocalSocketError error)
{
    // printf("QLocalSocket got: %s\n", errors[error]);
    if ( error == QLocalSocket::ConnectionRefusedError)
    {
        printf("Start paigo-qt application first!\n\n");
    }
    else if (error == QLocalSocket::PeerClosedError)
    {
        printf("paigo-qt closed session.\n");
    }
    exit(2);
}

void NtLocalClient::when_connected()
{

}

void NtLocalClient::readyRead()
{
    QByteArray data = _client_->readAll();
    printf("%s", data.constData());
    fflush(stdout);
}
