#ifndef WORKPORT_H
#define WORKPORT_H

#include <QObject>
#include <QSerialPort>
#include <sleeper.h>

class WorkPort : public QObject
{
    Q_OBJECT
public:
    explicit WorkPort(QObject *parent = 0);

private:
    QSerialPort serial;

    QString portName;

    //0-close
    //1-open
    //2-error open
    quint16 statusPort;

signals:
    //void s_error();
    //void s_getData();
    void s_portOpen(int result);
    void s_portClose(int result);

    void s_data(QByteArray);
    void s_error(QString error);
public slots:
    void on_portOpen(QString portName);
    void on_portClose();

    void on_data(QByteArray bytes);
private slots:
    void on_readyRead();
    void on_error(QSerialPort::SerialPortError);

    //void on_sendData();
};

#endif // WORKPORT_H
