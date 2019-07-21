#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    session_mgr = new SessionManager(this);

    // handle reception of new data from serial port
    connect(session_mgr, &SessionManager::dataReceived, this, &MainWindow::handleDataReceived);
    connect(this, &MainWindow::openSerial, session_mgr, &SessionManager::openSerial);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleDataReceived(const QByteArray &data)
{
    qDebug() << "Data" << data;

    ui->debugEdit->append(data);
}

void MainWindow::on_ConnectButtonon_released()
{
    emit openSerial();
}
