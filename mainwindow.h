#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QDialog>
#include <QLabel>
#include <QPixmap>

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

private slots:
    void on_ConnectButtonon_released();
    void processDistance();

    void on_spinBox_valueChanged(int arg1);

    void on_max_spinBox_valueChanged(int arg1);

    void on_min_spinBox_valueChanged(int arg1);

    void on_hyst_spinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;

    QSettings *settings;

    SessionManager *session_mgr;

    pictureWindow *imageWindow;
    QLabel *imageLabel;

    float distance;
    float distance_prev;
    float distance_percent;

    float hyst_center;
    float hyst_value;

    int dist_min;
    int dist_max;

    int city;

    /**
     * \brief handle arrival of new data
     */
    void handleDataReceived(const QByteArray &data);
    int cityPics(void);
    QString cityFilename(void);

};

#endif // MAINWINDOW_H
