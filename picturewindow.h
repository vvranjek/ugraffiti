#ifndef PICTUREWINDOW_H
#define PICTUREWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

namespace Ui {
class pictureWindow;
}

class pictureWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit pictureWindow(QWidget *parent = nullptr);
    ~pictureWindow();

    void setPicture(QString value);

private slots:
    void on_fullscreenButton_released();

private:
    Ui::pictureWindow *ui;

    QPixmap pixmap;

protected:
    void keyPressEvent(QKeyEvent* event);
};

#endif // PICTUREWINDOW_H
