#include "workport.h"

WorkPort::WorkPort(QObject *parent) : QObject(parent)
{
    connect(&serial, SIGNAL(readyRead()), this, SLOT(on_readyRead()));
    connect(&serial,SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(on_error(QSerialPort::SerialPortError)));
}

void WorkPort::on_portOpen(QString portName)
{
    this->portName = portName;
    if(serial.isOpen())
    {
        serial.close();
        statusPort = 0;
    }
    serial.setPortName(portName);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setParity(QSerialPort::NoParity);
    serial.setDataBits(QSerialPort::Data8);
    serial.setFlowControl(QSerialPort::NoFlowControl);
    serial.setBaudRate(QSerialPort::Baud19200);
    if (!serial.open(QIODevice::ReadWrite)) {
        statusPort = 2;
    }
    else
    {
        statusPort = 1;
    }
    emit s_portOpen(statusPort);
}

void WorkPort::on_portClose()
{
    if(serial.isOpen())
    {
        serial.close();
    }
    statusPort = 0;
    emit s_portClose(statusPort);
}

void WorkPort::on_data(QByteArray bytes)
{
    if(!serial.isOpen())
        return;
    serial.write(bytes.data(), bytes.length());
}

void WorkPort::on_readyRead()
{
    //Sleeper::msleep();
    QByteArray data;
    //char buff[64];
    //int n = serial.read(buff, 64);
    data.append(serial.readAll());
    //if(serial.re)
    emit s_data(data);
}

void WorkPort::on_error(QSerialPort::SerialPortError error)
{
    if(error == QSerialPort::NoError)
        return;
    emit s_error("Ошибка работы с COM " + serial.errorString());
}
