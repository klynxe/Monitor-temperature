#ifndef PACKAGEGET_H
#define PACKAGEGET_H

#include <QObject>

class PackageGet : public QObject
{
    Q_OBJECT
public:
    PackageGet();
    void read(QByteArray bytes);
    PackageGet(const PackageGet &obj);
    PackageGet& operator=(const PackageGet&);
    bool getOkCRC();
private:
    void checkCRC();
public:
    quint8 P1v7;
    quint8 P3v0;
    quint8 P3v8;
    quint8 U1v7;
    quint8 U1v0;
    quint8 U1v8;
    quint8 tt;
    quint8 CRC;
private:
    QByteArray bytes;
    bool okCRC;
};

#endif // PACKAGEGET_H
