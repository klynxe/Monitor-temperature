#ifndef PACKAGESEND_H
#define PACKAGESEND_H

#include <QObject>

#define SEND_HEADER 0xAA

class PackageSend : public QObject
{
    Q_OBJECT
public:
    PackageSend();
    void set(quint8 Adr_dev,
    quint8 P1v7,
    quint8 P3v0,
    quint8 P3v8);
    PackageSend(const PackageSend &obj);
    PackageSend& operator=(const PackageSend&);
    QByteArray getBytes() const;

private:
    quint8 header;
    quint8 Adr_dev;
    quint8 P1v7;
    quint8 P3v0;
    quint8 P3v8;
    quint8 CRC;

    QByteArray bytes;
};

#endif // PACKAGESEND_H
