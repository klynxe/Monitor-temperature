#ifndef WORKPORT_H
#define WORKPORT_H

#include <QObject>
#include <QSerialPort>

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
public slots:
    void on_portOpen(QString portName);
    void on_portClose();
    //void on_sendData();
};

#endif // WORKPORT_H
