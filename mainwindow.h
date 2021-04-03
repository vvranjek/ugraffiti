#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QDialog>
#include <QLabel>
#include <QPixmap>
#include <QThread>
#include <QMap>

#include "picturewindow.h"
#include "sessionmanager.h"


namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void openSerial();
    void distanceReceived(int value);
    void pictureReady(QString pic);

private slots:

    void deleteObject(QObject* thingy);
    void on_ConnectButtonon_released();
    void processDistance();
    void requestDistance();

    void on_max_spinBox_valueChanged(int arg1);

    void on_min_spinBox_valueChanged(int arg1);

    void on_hyst_spinBox_valueChanged(int arg1);

    void refreshPorts();

    void on_deviceComboBox_currentIndexChanged(const QString &arg1);

    void nextCity();
    void nextCityTimeout();

    void on_nextCitySpinBox_valueChanged(int arg1);

    void on_smooth_SpinBox_valueChanged(double arg1);

    void on_citiesCombo_currentTextChanged(const QString &arg1);

    void on_nextCityButton_released();

private:
    Ui::MainWindow *ui;

    QObject* mythingy;

    QSettings *settings;

    SessionManager *session_mgr;

    QLabel *imageLabel;

    QTimer *timerNext;

    //Worker* worker;

    float distance;
    float distance_prev;
    float distance_percent;

    float hyst_center;
    float hyst_value;

    int dist_min;
    int dist_max;

    int city;
    bool initComplete;

    int pic_prev;
    QStringList cities_list;
    QMap<QString, int> cities;
    QMap<QString, int> citiesPicsMax;
    QString currentCity;

    /**
     * \brief handle arrival of new data
     */
    void handleDataReceived(const QByteArray &data);
    int cityPics(void);
    QString cityFilename(void);

};


class Worker : public QObject
{
    Q_OBJECT
public:
    Worker(QObject* thingy, QObject* parent = 0);
private:
    QObject* mythingy;
    pictureWindow *imageWindow;
    QString picture;

    QString pic_prev;

signals:
    void deleteObject(QObject* thingy);
private slots:
    void doWork(QString pic);
    void update();
    void setPicture(QString pic);
};

#endif // MAINWINDOW_H
