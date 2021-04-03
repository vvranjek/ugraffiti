/**
 * \file
 * <!--
 * Copyright 2015 Develer S.r.l. (http://www.develer.com/)
 * -->
 *
 * \brief SessionManager class implementation
 *
 * \author Aurelien Rainone <aurelien@develer.com>
 */

#include "sessionmanager.h"
#include "outputmanager.h"

#include <QCoreApplication>
#include <QSerialPortInfo>
#include <QProgressDialog>
#include <QMessageBox>
#include <QFile>
#include <QDebug>
#include "settings.h"



SessionManager::SessionManager(QObject *parent) :
    QObject(parent)
{
    serial = new QSerialPort();
    in_progress = false;
    file_transfer = 0;

    connect(serial, &QSerialPort::readyRead, this, &SessionManager::readData);
    connect(serial, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>
                (&QSerialPort::error), this, &SessionManager::handleError);
}

SessionManager::~SessionManager()
{
    if (serial)
    {
        // closes connection if needed
        if (serial->isOpen())
            serial->close();
        delete serial;
    }
}

void SessionManager::handleError(QSerialPort::SerialPortError serialPortError)
{
    switch (serialPortError)
    {
        // no error
        case QSerialPort::NoError:
            break;

        // recoverable errors : inform user and clear error
        case QSerialPort::OpenError:

            QMessageBox::warning(NULL, tr("Error"), serial->errorString());
            // reset error
            serial->clearError();
            break;

        // unrecoverable errors : inform user and close the port/connection
        default:
            if (in_progress)
            {
                //QMessageBox::critical(NULL, tr("Error"), serial->errorString());

                // on some error (ex: hot unplugging) the 'QSerialPort::error' property successively
                // takes multiple values.
                // to prevent from displaying successive error messages, the in_progress flag is
                // set to indicate that we are not interested by next messages, until the user tries to open
                // again the serial port
                in_progress = false;
                if (serial->isOpen())
                {
                    serial->clearError();

                    closeSession();
                }
            }
            break;
    }
}

void SessionManager::openSession(const QString profile)
{
    bool cfg_ok = true, ok;

	QHash<QString, QString> port_cfg = settings::loadSettings(profile);

    // try converting port config from the hash
    QSerialPort::BaudRate baud_rate = static_cast<QSerialPort::BaudRate>
            (port_cfg["baud_rate"].toInt(&ok));
    cfg_ok &= ok;

    QSerialPort::DataBits data_bits = static_cast<QSerialPort::DataBits>
            (port_cfg["data_bits"].toInt(&ok));
    cfg_ok &= ok;

    QSerialPort::Parity parity = static_cast<QSerialPort::Parity>
            (port_cfg["parity"].toInt(&ok));
    cfg_ok &= ok;

    QSerialPort::StopBits stop_bits = static_cast<QSerialPort::StopBits>
            (port_cfg["stop_bits"].toInt(&ok));
    cfg_ok &= ok;

    QSerialPort::FlowControl flow_control = static_cast<QSerialPort::FlowControl>
            (port_cfg["flow_control"].toInt(&ok));
    cfg_ok &= ok;

    // a conversion didn't make it
    Q_ASSERT_X(cfg_ok, "SessionManager::openSession", "a conversion didn't make it");

    // configure port
#if (QT_VERSION < QT_VERSION_CHECK(5, 5, 0)) && defined(Q_OS_MAC)
    // 'device not found' error on MacOsX when we try to open port
    // after calling setPortName with a full device name (eg: /dev/ttyUSB01)

    // issues:
    // - https://github.com/develersrl/serial-ninja/issues/7
    // - https://github.com/develersrl/serial-ninja/issues/17
    // this is a QSerialPort bug, corrected for Qt > 5.5:
    // - https://codereview.qt-project.org/#/c/108571/
    if (port_cfg[QStringLiteral("device")].contains('/'))
        serial->setPortName(port_cfg[QStringLiteral("device")]);
    else
        serial->setPort(QSerialPortInfo(port_cfg[QStringLiteral("device")]));
#else
    // tested on linux and windows
    // and this is necessary to make QSerialPort work with pseudo
    // terminal created with socat for example
    serial->setPortName(port_cfg[QStringLiteral("device")]);
#endif
    serial->setBaudRate(baud_rate);
    serial->setDataBits(data_bits);
    serial->setParity(parity);
    serial->setStopBits(stop_bits);
    serial->setFlowControl(flow_control);

    // flag indicating that a connection is in progress (eventually successful or not)
    in_progress = true;

    // open serial port
    if (serial->open(QIODevice::ReadWrite))
    {
        curr_cfg = port_cfg;
        emit sessionOpened();
    }
    else
    {
        // here, stopped means 'no connection is in progress'
        emit sessionOpened();
        //emit sessionClosed();
    }
}

/* The same as openSession, but without profile */
void SessionManager::openSerial()
{
    // try converting port config from the hash
    QSerialPort::BaudRate baud_rate = QSerialPort::Baud19200;
    QSerialPort::DataBits data_bits = QSerialPort::Data8;
    QSerialPort::Parity parity = QSerialPort::NoParity;
    QSerialPort::StopBits stop_bits = QSerialPort::OneStop;
    QSerialPort::FlowControl flow_control = QSerialPort::NoFlowControl;

    // configure port
#if (QT_VERSION < QT_VERSION_CHECK(5, 5, 0)) && defined(Q_OS_MAC)
    // 'device not found' error on MacOsX when we try to open port
    // after calling setPortName with a full device name (eg: /dev/ttyUSB01)

    // issues:
    // - https://github.com/develersrl/serial-ninja/issues/7
    // - https://github.com/develersrl/serial-ninja/issues/17
    // this is a QSerialPort bug, corrected for Qt > 5.5:
    // - https://codereview.qt-project.org/#/c/108571/
    if (port_cfg[QStringLiteral("device")].contains('/'))
        serial->setPortName(port_cfg[QStringLiteral("device")]);
    else
        serial->setPort(QSerialPortInfo(port_cfg[QStringLiteral("device")]));
#else
    // tested on linux and windows
    // and this is necessary to make QSerialPort work with pseudo
    // terminal created with socat for example
    serial->setPortName("/dev/ttyUSB0");
#endif
    serial->setBaudRate(baud_rate);
    serial->setDataBits(data_bits);
    serial->setParity(parity);
    serial->setStopBits(stop_bits);
    serial->setFlowControl(flow_control);

    // flag indicating that a connection is in progress (eventually successful or not)
    in_progress = true;

    // open serial port
    if (serial->open(QIODevice::ReadWrite))
    {
        emit sessionOpened();
    }
    else
    {
        // here, stopped means 'no connection is in progress'
        emit sessionOpened();
        //emit sessionClosed();
    }
}


void SessionManager::closeSession()
{
    if (serial->isOpen())
    {
        serial->close();
        emit sessionClosed();
    }
}

bool SessionManager::isSessionOpen() const
{
    return serial->isOpen();
}

void SessionManager::readData()
{
    QByteArray data(serial->readLine());
    emit dataReceived(data);
}

void SessionManager::sendToSerial(const QByteArray &data)
{
    serial->write(data);
}

