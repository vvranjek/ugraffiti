#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <art_defines.h>
#include <QDir>
#include <QTimer>
#include <QSettings>
#include <QSerialPortInfo>
#include <QFileDialog>
#include <QFile>
#include <QDateTime>


#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    distance(200.0),
    city(1),
    hyst_value(10.0),
    initComplete(false)
{
    ui->setupUi(this);


    /* THREAD */

    mythingy = new QObject(this);
    //QThread* thisthread = this->thread();
    //QThread* mainthread = QCoreApplication::instance()->thread();
    //breakpoint here to check thisthread and mainthread
    Worker *worker = new Worker(mythingy, this);
    //worker->doWork("");
    connect(worker, SIGNAL(deleteObject(QObject*)), this, SLOT(deleteObject(QObject*)));
    connect(this, SIGNAL(pictureReady(QString)), worker, SLOT(setPicture(QString)));



    settings = new QSettings("MySoft", "Star Runner");

    session_mgr = new SessionManager(this);


    timerNext = new QTimer(this);


    //imageWindow->setWindowFlags(Qt::FramelessWindowHint);
    //imageWindow->setWindowState( imageWindow->windowState() | Qt::WindowFullScreen);
    //imageWindow->showFullScreen();

    // handle reception of new data from serial port
    connect(timerNext, SIGNAL(timeout()), this, SLOT(nextCityTimeout()));
    connect(session_mgr, &SessionManager::dataReceived, this, &MainWindow::handleDataReceived);
    connect(this, &MainWindow::openSerial, session_mgr, &SessionManager::openSerial);
    connect(this, &MainWindow::closeSerial, session_mgr, &SessionManager::closeSession);
    //connect(this, &MainWindow::distanceReceived, this, &MainWindow::processDistance);

    QTimer *timer_laser_request = new QTimer(this);
    connect(timer_laser_request, SIGNAL(timeout()), this, SLOT(requestDistance()));
    timer_laser_request->start(350);

    QTimer *reset_timer = new QTimer(this);
    connect(timer_laser_request, SIGNAL(timeout()), this, SLOT(requestDistance()));
    timer_laser_request->start(350);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(processDistance()));
    timer->start(30);

    refreshPorts();


    cities_list.append("");
    cities_list.append("Maribor");
    cities_list.append("Milano");
    cities_list.append("Praga");
    cities_list.append("Zurich");
    cities_list.append("Lyon");
    cities_list.append("");
    cities_list.append("");

    for (int i = 0; i < cities_list.size(); i++) {
        cities.insert(cities_list.at(i), i);
        if (QString(cities_list.at(i)).size() > 2 ) {
            ui->citiesCombo->addItem(cities_list.at(i));
        }

    }

    citiesPicsMax.insert("Maribor", 413);
    citiesPicsMax.insert("Milano", 425);
    citiesPicsMax.insert("Praga", 492);
    citiesPicsMax.insert("Zurich", 418);
    citiesPicsMax.insert("Lyon", 449);
    citiesPicsMax.insert("places_max", 6);



    /* Load settings */
    ui->max_spinBox->setValue(settings->value("dist_max").toInt());
    ui->min_spinBox->setValue(settings->value("dist_min").toInt());
    ui->hyst_spinBox->setValue(settings->value("hyst").toInt());
    ui->deviceComboBox->setCurrentText(settings->value("port").toString());
    ui->nextCitySpinBox->setValue(settings->value("next").toInt());
    ui->smooth_SpinBox->setValue(settings->value("smooth").toDouble());
    ui->artPath->setText(settings->value("artPath").toString());


    timerNext->start(ui->nextCitySpinBox->value()*1000);

    initComplete = true;

    //on_ConnectButtonon_released();

    ui->ConnectButtonon->toggle();
    //on_ConnectButtonon_toggled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
    //worker->deleteLater();
}

void MainWindow::handleDataReceived(const QByteArray &data)
{
    //qDebug() << "data: " << data;


    bool laser_meter = true;

    if (laser_meter) {
        int index_start = data.indexOf(":");
        int index_end = data.indexOf("m,");
        if (index_end > 0 && index_start >= 0) {
            qDebug() << "data: " << data;
            QString distance_str = data.mid(index_start+1, index_end-1);
            int distance_int = int(distance_str.toDouble()*100.0);
            qDebug() << "distance_str: " << distance_str;
            qDebug() << "distance_int: " << distance_int;
            distance = distance_int;
            ui->dist_lcdNumber->display(distance);
            processDistance();
        }

    }

    else {
        const QString dist_str = "dist=";


        int index = data.lastIndexOf(dist_str);

        if (index == 0) {
            //int distance = QString::number(data.mid(data.lastIndexOf(dist_str), data.size()-data.lastIndexOf(dist_str)));
            QString distance_str = data.mid(index+dist_str.size(), data.size()-dist_str.size());
            //qDebug() << "distance: " << distance_str;


            int distance_int = distance_str.toInt();

            //qDebug() << "distance: " << distance_int;

            distance = distance_int;

            ui->dist_lcdNumber->display(distance);

           // emit distanceReceived(distance_int);

            //processDistance();
        }
    }
}

void MainWindow::on_ConnectButtonon_released()
{
    //ui->ConnectButtonon->toggle();

//    qDebug() << "Connect presse";

//    if (ui->ConnectButtonon->isChecked()) {
//        qDebug() << "Conect open serial!";
//        emit openSerial();
//        ui->ConnectButtonon->setText("Disconnect");
//        ui->ConnectButtonon->setChecked(true);
//    }
//    else {
//        qDebug() << "Conect close serial!";
//        emit closeSerial();
//        ui->ConnectButtonon->setText("Connect");
//        ui->ConnectButtonon->setChecked(false);
//    }
}


void MainWindow::on_ConnectButtonon_toggled(bool checked)
{
        if (ui->ConnectButtonon->isChecked()) {
            emit openSerial();
            ui->ConnectButtonon->setText("Disconnect");
        }
        else {
            emit closeSerial();
            ui->ConnectButtonon->setText("Connect");
        }
}

//void void MainWindow::reset_distance() {
    //pic_num = cityPics();
//}


void MainWindow::processDistance()
{
    //qDebug() << "Distanc is: " << distance;



    float dist_filtered;
    float dist_hyst;
    float dist_final;

    qDebug() << "Distance: " << distance;
    if (distance < dist_min - hyst_value) distance_limited = dist_min - hyst_value;
    if (distance > dist_max + hyst_value) {
        // Draghi Ahim, tukaj spremeni stevilo za cas
        qDebug() << "Max reached: " << QDateTime::currentSecsSinceEpoch() << "/" << ts + 3;
        if (QDateTime::currentSecsSinceEpoch() > ts + 3) {
            qDebug() << "RESET reached: ";
            distance_limited = dist_max-1;
        }
        else {
            distance_limited = distance_prev;

        }
    }
    else {
        distance_limited = distance;
        qDebug() << "TIMER SET: ";
        ts = QDateTime::currentSecsSinceEpoch();
    }
    //if (distance > dist_max + hyst_value) distance = dist_max + hyst_value;

    //distance = 0.98(distance_prev - distance) + 0.2*distance;

    /* Smooth filter */
    dist_filtered = (float)distance_prev + (float)((float)distance_limited - distance_prev)*ui->smooth_SpinBox->value();
    distance_prev = dist_filtered;
    ui->dist_filter_lcdNumber->display(dist_filtered);

    //dist_filtered = distance;

    /* Hysteresis filter */
    if (dist_filtered > hyst_center + hyst_value) {
        hyst_center = dist_filtered - hyst_value;
    }

    if (dist_filtered < hyst_center - hyst_value) {
        hyst_center = dist_filtered + hyst_value;
    }

    dist_final = hyst_center;
    distance_percent =  ((dist_final-dist_min)/(float)(dist_max-dist_min));
    //qDebug() << "Percent is: " << distance_percent;


    /* Update picture */
    int pic_num;
    pic_num = (int)(/* citiesPicsMax.value(currentCity)*/  MainWindow::cityPics() * (1.0f-distance_percent));

    if (pic_num < 1) pic_num = 1;

    //qDebug() << "pic_num is: " << pic_num << "/" << MainWindow::cityPics();

    //QString filename = cityFilename() + QString::number(pic_num) + ".jpg";
    //imageWindow->setPicture(filename);

    if (pic_num != pic_prev) {
        QString filename = cityFilename() + QString::number(pic_num) + ".jpg";
        //qDebug() << "Filename: " << filename;
        pic_prev = pic_num;


        //imageWindow->setPicture(filename);

        emit pictureReady(filename);
    }
}

void MainWindow::requestDistance()
{
    session_mgr->sendToSerial("F\n\r");
}

int MainWindow::cityPics(void)
{
    //qDebug() << "max pics: " << citiesPicsMax[cities_list[city]];
    //qDebug() << "Current city: " << cities_list[city];
    return citiesPicsMax[cities_list[city]];

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

    case Amsterdam :
        return LYON_MAX;
    case Eindhoven :
        return EINDHOVEN_MAX;
    case London :
        return LONDON_MAX;
    case Berlin :
        return BERLIN_MAX;
    case Dunaj :
        return DUNAJ_MAX;





    default :
        return 1;
    }
}

QString MainWindow::cityFilename(void)
{

    QString default_location = ui->artPath->text();

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

    case Amsterdam :
        return default_location + "/lyon/";
    case Eindhoven :
        return default_location + "/eindhoven/";
    case London :
        return default_location + "/london/";
    case Berlin :
        return default_location + "/berlin/";
    case Dunaj :
        return default_location + "/dunaj/";
    default :
        return default_location + "/maribor/";
    }
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

void MainWindow::refreshPorts()
{
    QList<QSerialPortInfo> ports(QSerialPortInfo::availablePorts());
    for (int idx = 0; idx < ports.length(); ++idx)
    {
        const QSerialPortInfo& port_info = ports.at(idx);
        ui->deviceComboBox->addItem(port_info.systemLocation());

        // construct description tooltip
        QString tooltip;

        // add description if not empty
        if (!port_info.description().isEmpty())
            tooltip.append(port_info.description());
        if (!port_info.manufacturer().isEmpty())
        {
            // add ' / manufacturer' if not empty
            if (!tooltip.isEmpty())
                tooltip.push_back(QStringLiteral(" / "));
            tooltip.append(port_info.manufacturer());
        }
        // assign portName
        if (tooltip.isEmpty())
            tooltip = port_info.portName();

        ui->deviceComboBox->setItemData(idx, tooltip, Qt::ToolTipRole);
    }

}

void MainWindow::on_deviceComboBox_currentIndexChanged(const QString &arg1)
{
    settings->setValue("port", arg1);
}

void MainWindow::nextCity()
{
    city++;
    if (city > places_max -1) {
        city = 1;
    }

    ui->citiesCombo->setCurrentText(cities_list[city]);

    qDebug() << "City: " << city;
}

void MainWindow::nextCityTimeout()
{
    if (ui->timeoutCheckbox->isChecked()) {
        nextCity();
    }
}

void MainWindow::on_nextCitySpinBox_valueChanged(int arg1)
{
    if (arg1 != 0) {
        timerNext->start(arg1*1000);
        settings->setValue("next", arg1);
    }
}

void MainWindow::on_smooth_SpinBox_valueChanged(double arg1)
{
    settings->setValue("smooth", arg1);
}


Worker::Worker(QObject* thingy, QObject* parent)
    : QObject(parent),
      running(false),
      picReady(false)
{
    mythingy = thingy;
    QThread* thread = new QThread(this);
    this->moveToThread(thread);

    //use a timer to allow the constructor to exit
    QTimer* timer = new QTimer(this);
    //timer->setSingleShot(true);
    //timer->start(50);
    //connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    //QThread* thisthread = this->thread();
    //QThread* mainthread = QCoreApplication::instance()->thread();
    //breakpoint here to check thisthread and mainthread
    thread->start();

    doWork("");
}

void Worker::doWork(QString pic)
{
    qDebug() << "Thread";
    QThread* thisthread = this->thread();
    QThread* mainthread = QCoreApplication::instance()->thread();


        imageWindow = new pictureWindow();
        imageWindow->resize(640,480);
        imageWindow->move(300, 300);
        imageWindow->show();




    //breakpoint here to check thisthread and mainthread
    //deleteObject(mythingy);
}

void Worker::update()
{
    running = true;

    QFile file(picture);

    if (picture != pic_prev && file.exists()) {
        pic_prev = picture;
        imageWindow->setPicture(picture);
        qDebug() << "Filename: " << picture;

    }


    running = false;
}

void Worker::setPicture(QString pic)
{
    picture = pic;
    if (!running) update();
}


void MainWindow::deleteObject(QObject* thingy)
{
    QThread* thisthread = this->thread();
    QThread* mainthread = QCoreApplication::instance()->thread();
    //breakpoint here to check thisthread and mainthread
    delete thingy;
}


void MainWindow::on_citiesCombo_currentTextChanged(const QString &arg1)
{
    if (initComplete) {
        city = cities.value(ui->citiesCombo->currentText());
    }
}

void MainWindow::on_artPathButton_released()
{
    artPath = QFileDialog::getExistingDirectory(this, "Choose path to art folder");
    ui->artPath->setText(artPath);
    settings->setValue("artPath", artPath);
}

void MainWindow::on_nextCityButton_released()
{
    nextCity();
}
