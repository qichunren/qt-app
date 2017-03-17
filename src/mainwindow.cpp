#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "web_server.h"
#include "database.h"
#include <QWebView>
#include <QWebFrame>
#include "ntdeck.h"
#include "configuration_dialog.h"
WebServer * web_server;

static QWebView * view;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    web_server = new WebServer("/home/qichunren/code/luna-server/public", "8080");
    Database::connect(QString("localhost"), QString("root"), QString("root"), QString("ntdeck2_development_nanjing"));

    view = new QWebView(this);
    ui->page1Layout->addWidget(view);

    connect(ui->actionSetting, SIGNAL(triggered()), this, SLOT(show_configuration_dialog()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::show_configuration_dialog()
{
    ConfigurationDialog config_dialog(this);
    int c = config_dialog.exec();
}

void MainWindow::on_pushButton_clicked()
{
    web_server->start();
    view->load(QUrl("file:///home/qichunren/code/qt-web-app/static/index.html"));
    QWebFrame * frame = view->page()->mainFrame();
    frame->addToJavaScriptWindowObject("Ntdeck", new Ntdeck(this));
}

void MainWindow::on_pushButton_2_clicked()
{
    web_server->stop();
}

void MainWindow::switchPage2() {
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
