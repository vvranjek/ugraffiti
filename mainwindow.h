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

private:
    Ui::MainWindow *ui;

    SessionManager *session_mgr;

    pictureWindow *imageWindow;
    QLabel *imageLabel;

    int distance;

    /**
     * \brief handle arrival of new data
     */
    void handleDataReceived(const QByteArray &data);

};

#endif // MAINWINDOW_H
