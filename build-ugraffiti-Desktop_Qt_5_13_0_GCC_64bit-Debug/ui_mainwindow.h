/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QComboBox *deviceComboBox;
    QSpinBox *min_spinBox;
    QLabel *label_2;
    QSpinBox *max_spinBox;
    QLabel *label_3;
    QPushButton *pushButton;
    QLCDNumber *dist_filter_lcdNumber;
    QLabel *label_4;
    QLCDNumber *dist_lcdNumber;
    QLabel *label_5;
    QPushButton *pushButton_2;
    QLabel *label_6;
    QPushButton *ConnectButtonon;
    QLabel *label;
    QSpinBox *nextCitySpinBox;
    QLabel *label_7;
    QSpinBox *hyst_spinBox;
    QDoubleSpinBox *smooth_SpinBox;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(384, 336);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 10, 341, 210));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        deviceComboBox = new QComboBox(layoutWidget);
        deviceComboBox->setObjectName(QString::fromUtf8("deviceComboBox"));

        gridLayout->addWidget(deviceComboBox, 0, 1, 1, 3);

        min_spinBox = new QSpinBox(layoutWidget);
        min_spinBox->setObjectName(QString::fromUtf8("min_spinBox"));
        min_spinBox->setMaximum(20000);

        gridLayout->addWidget(min_spinBox, 2, 1, 1, 2);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        max_spinBox = new QSpinBox(layoutWidget);
        max_spinBox->setObjectName(QString::fromUtf8("max_spinBox"));
        max_spinBox->setMaximum(20000);

        gridLayout->addWidget(max_spinBox, 3, 1, 1, 2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 4, 0, 1, 1);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 0, 4, 1, 2);

        dist_filter_lcdNumber = new QLCDNumber(layoutWidget);
        dist_filter_lcdNumber->setObjectName(QString::fromUtf8("dist_filter_lcdNumber"));
        dist_filter_lcdNumber->setFrameShadow(QFrame::Plain);
        dist_filter_lcdNumber->setSegmentStyle(QLCDNumber::Flat);

        gridLayout->addWidget(dist_filter_lcdNumber, 3, 5, 1, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        dist_lcdNumber = new QLCDNumber(layoutWidget);
        dist_lcdNumber->setObjectName(QString::fromUtf8("dist_lcdNumber"));
        dist_lcdNumber->setFrameShape(QFrame::Box);
        dist_lcdNumber->setFrameShadow(QFrame::Plain);
        dist_lcdNumber->setLineWidth(1);
        dist_lcdNumber->setSmallDecimalPoint(false);
        dist_lcdNumber->setSegmentStyle(QLCDNumber::Flat);

        gridLayout->addWidget(dist_lcdNumber, 2, 5, 1, 1);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_5, 2, 3, 1, 2);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 1, 4, 1, 2);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_6, 3, 3, 1, 2);

        ConnectButtonon = new QPushButton(layoutWidget);
        ConnectButtonon->setObjectName(QString::fromUtf8("ConnectButtonon"));

        gridLayout->addWidget(ConnectButtonon, 0, 0, 1, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setLayoutDirection(Qt::LeftToRight);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 2, 0, 1, 1);

        nextCitySpinBox = new QSpinBox(layoutWidget);
        nextCitySpinBox->setObjectName(QString::fromUtf8("nextCitySpinBox"));
        nextCitySpinBox->setMaximum(99999);

        gridLayout->addWidget(nextCitySpinBox, 1, 1, 1, 3);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_7, 5, 0, 1, 1);

        hyst_spinBox = new QSpinBox(layoutWidget);
        hyst_spinBox->setObjectName(QString::fromUtf8("hyst_spinBox"));
        hyst_spinBox->setMaximum(20000);

        gridLayout->addWidget(hyst_spinBox, 4, 1, 1, 2);

        smooth_SpinBox = new QDoubleSpinBox(layoutWidget);
        smooth_SpinBox->setObjectName(QString::fromUtf8("smooth_SpinBox"));
        smooth_SpinBox->setDecimals(3);
        smooth_SpinBox->setMinimum(0.000000000000000);
        smooth_SpinBox->setMaximum(1.000000000000000);
        smooth_SpinBox->setSingleStep(0.001000000000000);
        smooth_SpinBox->setValue(0.300000000000000);

        gridLayout->addWidget(smooth_SpinBox, 5, 1, 1, 2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 384, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Max", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Hyst", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Refresh", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Next city time", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Distance", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Next City", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Filtered", nullptr));
        ConnectButtonon->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Min", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Smooth", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
