#include "packageget.h"

#include <QDataStream>

PackageGet::PackageGet() : QObject(nullptr), okCRC(false)
{

}

void PackageGet::read(QByteArray bytes)
{
    this->bytes = bytes;
    QDataStream in(&this->bytes, QIODevice::ReadOnly);
    in >> this->P1v7
        >> this->P3v0
        >> this->P3v8
        >> this->U1v7
        >> this->U1v0
        >> this->U1v8
        >> this->tt
        >> this->CRC;
    checkCRC();
}

PackageGet::PackageGet(const PackageGet &obj)
{
    *this =  obj;
}

PackageGet&  PackageGet::operator=(PackageGet const& obj) {
    P1v7 = obj.P1v7;
    P3v0 = obj.P3v0;
    P3v8 = obj.P3v8;
    U1v7 = obj.U1v7;
    U1v0 = obj.U1v0;
    U1v8 = obj.U1v8;
    tt = obj.tt;
    CRC = obj.CRC;
    bytes = obj.bytes;
    return *this;
}

bool PackageGet::getOkCRC()
{
    return okCRC;
}

void PackageGet::checkCRC()
{
    if((quint8)(P1v7+P3v0+P3v8+U1v7+U1v0+U1v8+tt+CRC) == 0)
        okCRC = true;
    else
        okCRC = false;
}
