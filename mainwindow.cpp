#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <art_defines.h>
#include <QDir>
#include <QTimer>
#include <QSettings>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    distance(200.0),
    city(1),
    hyst_value(10.0)
{
    ui->setupUi(this);

    settings = new QSettings("MySoft", "Star Runner");

    session_mgr = new SessionManager(this);
    imageWindow = new pictureWindow(this);
    imageWindow->resize(200,200);
    imageWindow->show();



    //imageWindow->setWindowFlags(Qt::FramelessWindowHint);
    //imageWindow->setWindowState( imageWindow->windowState() | Qt::WindowFullScreen);
    //imageWindow->showFullScreen();

    // handle reception of new data from serial port
    connect(session_mgr, &SessionManager::dataReceived, this, &MainWindow::handleDataReceived);
    connect(this, &MainWindow::openSerial, session_mgr, &SessionManager::openSerial);
    //connect(this, &MainWindow::distanceReceived, this, &MainWindow::processDistance);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(processDistance()));
    timer->start(30);

    /* Load settings */
    ui->max_spinBox->setValue(settings->value("dist_max").toInt());
    ui->min_spinBox->setValue(settings->value("dist_min").toInt());
    ui->hyst_spinBox->setValue(settings->value("hyst").toInt());


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleDataReceived(const QByteArray &data)
{

    //qDebug() << "data: " << data;
    const QString dist_str = "dist=";


    int index = data.lastIndexOf(dist_str);

    if (index == 0) {
        //int distance = QString::number(data.mid(data.lastIndexOf(dist_str), data.size()-data.lastIndexOf(dist_str)));
        QString distance_str = data.mid(index+dist_str.size(), data.size()-dist_str.size());
        //qDebug() << "distance: " << distance_str;


        int distance_int = distance_str.toInt();

        //qDebug() << "distance: " << distance_int;

        ui->debugEdit->append(QString::number(distance_int));

        distance = distance_int;

        ui->dist_lcdNumber->display(distance);

        emit distanceReceived(distance_int);
    }


}

void MainWindow::on_ConnectButtonon_released()
{
    emit openSerial();
}

void MainWindow::processDistance()
{
    //qDebug() << "Distanc is: " << distance;



    float dist_filtered;
    float dist_hyst;
    float dist_final;

    if (distance < dist_min - hyst_value) distance = dist_min - hyst_value;
    if (distance > dist_max + hyst_value) distance = dist_max + hyst_value;

    //distance = 0.98(distance_prev - distance) + 0.2*distance;

    /* Smooth filter */
    dist_filtered = (float)distance_prev + (float)((float)distance - distance_prev)*0.3;
    distance_prev = dist_filtered;
    ui->dist_filter_lcdNumber->display(dist_filtered);

    /* Hysteresis filter */

    if (dist_filtered > hyst_center + hyst_value) {
        hyst_center = dist_filtered - hyst_value;
    }

    if (dist_filtered < hyst_center - hyst_value) {
        hyst_center = dist_filtered + hyst_value;
    }

    //qDebug() << "Filtered is: " << dist_filtered;

    dist_final = hyst_center;
    distance_percent =  ((dist_final-dist_min)/(float)(dist_max-dist_min));
    qDebug() << "Percent is: " << distance_percent;




    /* Update picture */
    int pic_num;

    int city = 1;
    // TODO: get city

    pic_num = MainWindow::cityPics() * (1.0-distance_percent);

    //qDebug() << cityPics() << " * " << distance_percent << " = " << pic_num;

    QString filename = cityFilename() + QString::number(pic_num) + ".jpg";

    qDebug() << "Filename: " << filename;

    imageWindow->setPicture(filename);


}

int MainWindow::cityPics(void)
{
    switch (city) {
    case Maribor :
        return MARIBOR_MAX;
    case Milano :
        return MILANO_MAX;
    case Praga :
        return PRAGA_MAX;
    case Zurich :
        return ZURICH_MAX;
    case Lyon :
        return LYON_MAX;
    default :
        return 1;
    }
}

QString MainWindow::cityFilename(void)
{

    QString default_location = QDir::currentPath() + "/../art";

    switch (city) {
    case Maribor :
        return default_location + "/maribor/";;
    case Milano :
        return default_location + "/milano/";
    case Praga :
        return default_location + "/praga/";
    case Zurich :
        return default_location + "/zurich/";
    case Lyon :
        return default_location + "/lyon/";
    default :
        return default_location + "/maribor/";
    }
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{

}

void MainWindow::on_max_spinBox_valueChanged(int arg1)
{
    dist_max = arg1;
    settings->setValue("dist_max", arg1);
}

void MainWindow::on_min_spinBox_valueChanged(int arg1)
{
    dist_min = arg1;
    settings->setValue("dist_min", arg1);
}

void MainWindow::on_hyst_spinBox_valueChanged(int arg1)
{
    hyst_value = arg1;
    settings->setValue("hyst", arg1);
}
