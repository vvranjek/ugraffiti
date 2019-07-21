/**
 * \file
 * <!--
 * Copyright 2015 Develer S.r.l. (http://www.develer.com/)
 * -->
 *
 * \brief SessionManager class header
 *
 * \author Aurelien Rainone <aurelien@develer.com>
 */

#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

//#include "connectdialog.h"
//#include "filetransfer.h"
#include <QHash>

#include <QObject>
#include <QSerialPort>

class FileTransfer;

/**
 * \brief manage serial port session
 */
class SessionManager : public QObject
{
    Q_OBJECT

public:

    /**
     * \brief file transfer protocols and variants
     */
    enum Protocol
    {
        XMODEM = 1,
        YMODEM = 10,
        ZMODEM = 100
    };

private:

    /// serial port instance
    QSerialPort            *serial;

    /// current session configuration
    QHash<QString, QString> curr_cfg;

    /// indicate that a connection has been initiated or is in progress
    bool        in_progress;

    /// file transfer implementation
    FileTransfer *file_transfer;

public:

    explicit SessionManager(QObject *parent = 0);
    ~SessionManager();

    /**
     * \brief open a serial port session
     * \param port_cfg    serial port settings
     */
	void openSession(QString profile);

    /**
     * \brief close current serial port session
     */
    void closeSession();

    /**
     * \brief return true if the session is active
     */
    bool isSessionOpen() const;

    /**
     * \brief send data to serial port
     * \param data    byte array data
     */
    void sendToSerial(const QByteArray &data);

    /**
     * \brief init a file transfer thread
     * \param filename  file to transfer
     * \param type      protocol to use
     */
    void transferFile(const QString &filename, Protocol type);

    /**
     * \brief handle file transfer cancelation signal
     */
    void handleTransferCancelledByUser();

private:

    /**
     * \brief read data from serial port
     */
    void readData();

    /**
     * \brief save given data to configured dump file
     */
    void saveToFile(const QByteArray &data);

    /**
     * \brief handle serial port error
     */
    void handleError(QSerialPort::SerialPortError serialPortError);

signals:

    /**
     * \brief signal emitted when a new session is opened
     */
    void sessionOpened();

    /**
     * \brief signal emitted when current has been closed
     */
    void sessionClosed();

    /**
     * \brief signal emitted when new data has been received from the serial port
     * \param data    byte array data
     */
    void dataReceived(const QByteArray &data);

    /**
     * \brief signal emitted each time the file transfer progresses
     * (minimum amount to emit is 1% progress)
     * \percent percentage of file transfered
     */
    void fileTransferProgressed(int percent);
};

#endif // SESSIONMANAGER_H
