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

    qDebug() << "data: " << data;
    const QString dist_str = "dist=";


    int index = data.lastIndexOf(dist_str);

    if (index == 0) {
        //int distance = QString::number(data.mid(data.lastIndexOf(dist_str), data.size()-data.lastIndexOf(dist_str)));
        QString distance_str = data.mid(index+dist_str.size(), data.size()-dist_str.size());
        //qDebug() << "distance: " << distance_str;


        int distance_int = distance_str.toInt();

        qDebug() << "distance: " << distance_int;

        ui->debugEdit->append(QString::number(distance_int));

        emit distanceReceived(distance_int);
    }


}

void MainWindow::on_ConnectButtonon_released()
{
    emit openSerial();
}
