#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;

    SessionManager      *session_mgr;

    /**
     * \brief handle arrival of new data
     */
    void handleDataReceived(const QByteArray &data);

};

#endif // MAINWINDOW_H
