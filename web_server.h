#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <QObject>

class WebServer : public QObject
{
    Q_OBJECT
public:
    explicit WebServer(const char *document_root, const char *port, QObject *parent = 0);

    bool is_running();

    void start();
    void stop();

signals:

public slots:

};

#endif // WEB_SERVER_H
