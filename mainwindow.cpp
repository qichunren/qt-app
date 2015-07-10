#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "web_server.h"
#include "database.h"
#include <QWebView>
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


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    web_server->start();
    view->load(QUrl("http://localhost:8080"));
}



void MainWindow::on_pushButton_2_clicked()
{
    web_server->stop();
}
