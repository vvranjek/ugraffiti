#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // handle reception of new data from serial port
    //connect(session_mgr, &SessionManager::dataReceived, this, &MainWindow::handleDataReceived);

}

MainWindow::~MainWindow()
{
    delete ui;
}
