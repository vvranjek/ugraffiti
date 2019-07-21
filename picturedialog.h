#ifndef PICTUREDIALOG_H
#define PICTUREDIALOG_H

#include <QDialog>
#include <QPixmap>

namespace Ui {
class pictureDialog;
}

class pictureDialog : public QDialog
{
    Q_OBJECT

public:
    explicit pictureDialog(QWidget *parent = nullptr);
    ~pictureDialog();

private slots:
    void on_pushButton_released();

private:
    Ui::pictureDialog *ui;

    QPixmap pixmap;

};

#endif // PICTUREDIALOG_H
