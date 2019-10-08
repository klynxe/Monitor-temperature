#include "workport.h"

WorkPort::WorkPort(QObject *parent) : QObject(parent)
{

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
    if (!serial.open(QIODevice::ReadWrite)) {
        statusPort = 2;
    }
    else
        statusPort = 1;
    emit s_portOpen(statusPort);
}

void WorkPort::on_portClose()
{
    if(serial.isOpen())
    {
        serial.close();
    }
    statusPort = 0;
}
