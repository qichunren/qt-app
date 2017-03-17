#include "mainwindow.h"
#include "nt_header.h"
#include <QApplication>

#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    bool is_daemon = false;
    bool is_dev_mode = false;
    bool is_fullscreen = false;
    for(u_int8_t i=0;i<argc;i++) {
        if(strcmp (argv[i], "-d") == 0 || strcmp (argv[i], "--daemon") == 0) {
            is_daemon = true;
        }
        if(strcmp (argv[i], "--dev") == 0) {
            is_dev_mode = true;
        }
        if(strcmp (argv[i], "--fullscreen") == 0) {
            is_fullscreen = true;
        }
        if(strcmp (argv[i], "-v") == 0 || strcmp (argv[i], "--version") == 0) {
            puts(APP_NAME " " APP_VERSION " build at " BUILD_DATE);
            exit(1);
        }
        if(strcmp (argv[i], "-h") == 0 || strcmp (argv[i], "--help") == 0) {
            puts(APP_NAME " " APP_VERSION " build at " BUILD_DATE);
            puts("Arguments:");
            puts("  -d, --daemon  : Run as a deamon.");
            puts("  --dev         : Run in dev mode.");
            puts("  --fullscreen  : Display fullscreen.");
            puts("  -v, --version : Display version.");
            exit(1);
        }
    }

    if(is_daemon)
    {
        printf("%s run as a daemon.\n", USER_AGENT);
        daemon(0, 0);
    }

    QApplication a(argc, argv);
    MainWindow w;
    if(is_fullscreen)
        w.showFullScreen();
    else
        w.showMaximized();

    return a.exec();
}
