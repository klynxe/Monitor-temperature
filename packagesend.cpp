#include "packagesend.h"

#include <QDataStream>

PackageSend::PackageSend(): QObject(nullptr)
{

}

void PackageSend::set(quint8 Adr_dev, quint8 P1v7, quint8 P3v0, quint8 P3v8)
{
    this->header = SEND_HEADER;
    this->Adr_dev = Adr_dev;
    this->P1v7 = P1v7;
    this->P3v0 = P3v0;
    this->P3v8 = P3v8;
    this->CRC = (quint8)0xFF-(header+Adr_dev+P1v7+P3v0+P3v8)+1;
    this->bytes.clear();
    QDataStream out(&this->bytes, QIODevice::WriteOnly);
    out << this->header
        << this->Adr_dev
        << this->P1v7
        << this->P3v0
        << this->P3v8
        << this->CRC;
}

PackageSend::PackageSend(const PackageSend &obj)
{
    *this =  obj;
}

PackageSend&  PackageSend::operator=(PackageSend const& obj) {
    header = obj.header;
    Adr_dev = obj.Adr_dev;
    P1v7 = obj.P1v7;
    P3v0 = obj.P3v0;
    P3v8 = obj.P3v8;
    CRC = obj.CRC;
    bytes = obj.bytes;
    return *this;
}

QByteArray PackageSend::getBytes() const
{
    return bytes;
}
