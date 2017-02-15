#include "nt_logger.h"
#include "paigo_header.h"
#include <QFile>
#include <sys/stat.h>
#include <QDateTime>
#include <QDebug>

#define DATA_LOG_FILE "/var/log/paigo/data-%1.log"
#define DATA_LOG_SPLIT_TIME 3600

NtLogger& NtLogger::instance() {
    static NtLogger _instance;
    return _instance;
}

NtLogger::NtLogger(QObject *parent) :
    QObject(parent)
{
}

void NtLogger::check_large()
{
    struct stat st;
    stat(INFO_FILE, &st);
    quint64 file_size = st.st_size;
    if (file_size > 30 * 1024 * 1024) // 30 Mb
    {
        clear_info_logs();
    }
}

void NtLogger::log_info(const QString &message) {    
    QFile file(INFO_FILE);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        puts("Unable to write info log to file.");
        return;
    }

    QByteArray message_array;
    QString datetime(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss # "));
    message_array.append(datetime);
    message_array.append(message);
    file.write(message_array);
    qDebug() << message_array;
    file.write("\n");
    file.close();
}

void NtLogger::log_error(const QString &message) {
    QFile file(ERROR_FILE);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        puts("Unable to write error log to file.");
        return;
    }

    QByteArray message_array;
    QString datetime(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss # "));
    message_array.append(datetime);
    message_array.append(message);
    file.write(message_array);
    qDebug() << "ERROR:" << message_array;
    file.write("\n");
    file.close();
}

void NtLogger::log_data(const QString &message) {
    QString data_log_file_name;
    if (last_log_data_time.isNull())
    {
        last_log_data_time = QTime::currentTime();
        data_log_file_name = QString(DATA_LOG_FILE).arg(last_log_data_time.toString("hh-mm"));
    }
    else
    {
        QTime time = QTime::currentTime();
        int duration = last_log_data_time.secsTo(time);
        if (duration > DATA_LOG_SPLIT_TIME)
        {
            last_log_data_time = QTime::currentTime();
        }
        data_log_file_name = QString(DATA_LOG_FILE).arg(last_log_data_time.toString("hh-mm"));
    }
    QFile file(data_log_file_name);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        puts("Unable to write data log to file.");
        return;
    }

    QByteArray message_array;
    QString datetime(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss # "));
    message_array.append(datetime);
    message_array.append(message);
    file.write(message_array);
    file.write("\n");
    file.close();
}


void NtLogger::clear_info_logs() {
    QFile file(INFO_FILE);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        puts("Unable to write info log to file.");
        return;
    }

    QByteArray message_array;
    message_array.append("");
    file.write(message_array);
    file.close();
}

void NtLogger::clear_error_logs() {
    QFile file(ERROR_FILE);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        puts("Unable to write error log to file.");
        return;
    }

    QByteArray message_array;
    message_array.append("");
    file.write(message_array);
    file.close();
}
