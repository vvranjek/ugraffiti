#include "picturewindow.h"
#include "ui_picturewindow.h"

pictureWindow::pictureWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::pictureWindow)
{
    ui->setupUi(this);

    setContentsMargins(0,0,0,0);


    ui->imageLabel->setText("TESTING");
    //ui->HLayout->setContentsMargins(0,0,0,0);
    //ui->HLayout->setSpacing(0);

    pixmap.load("/home/vid/src/ugraffiti/pics/1.jpg");
    //QPixmap scaled=pixmap.scaled ( 800, 480, Qt::IgnoreAspectRatio, Qt::FastTransformation );

    ui->imageLabel->setPixmap(pixmap);
    ui->imageLabel->setScaledContents( true );
    ui->imageLabel->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    //this->setWindowState(this->windowState() | Qt::WindowFullScreen);

    //this->setModal(true);
}

pictureWindow::~pictureWindow()
{
    delete ui;
}

void pictureWindow::on_fullscreenButton_released()
{
    showFullScreen();
}
