#include "picturedialog.h"
#include "ui_picturedialog.h"
#include <QApplication>
#include <QDesktopWidget>

pictureDialog::pictureDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pictureDialog)
{
    ui->setupUi(this);


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

pictureDialog::~pictureDialog()
{
    delete ui;
}

void pictureDialog::on_pushButton_released()
{
    this->setWindowState(Qt::WindowFullScreen);
    //this->setWindowState(this->windowState() | Qt::WindowFullScreen);

    // Make our window without panels
    //this->setWindowFlags( Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint );
    // Resize refer to desktop
   // this->resize(QApplication::desktop()->size());
  //this->resize(QApplication::desktop()



//    this->setWindowFlag(Qt::Window, true);
    //setWindowFlags(Qt::FramelessWindowHint);
    //setWindowState( windowState() | Qt::WindowFullScreen);

    //setModal(false);

    //setFixedSize(qApp->desktop()->size());
    //move(0, 0);
//    setWindowFlags(Qt::FramelessWindowHint);
   // setWindowState( d->windowState() | Qt::WindowFullScreen);
    //ui->show();
    //ui->activateWindow();










    setFixedSize(qApp->desktop()->size());
    setWindowFlags(/*Qt::FramelessWindowHint*/ Qt::Window  /* | Qt::Popup*/);
    setWindowState( windowState() | Qt::WindowFullScreen);
    //show();
    //activateWindow();









//    QRect rec = QApplication::desktop()->size();
//     height = rec.height();
//     width = rec.width();


}
