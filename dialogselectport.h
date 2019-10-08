#ifndef DIALOGSELECTPORT_H
#define DIALOGSELECTPORT_H

#include "workport.h"

#include <QDialog>
#include <QSerialPort>
#include <QSerialPortInfo>

namespace Ui {
class DialogSelectPort;
}

class DialogSelectPort : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSelectPort(WorkPort * workPort, QWidget *parent = 0);
    ~DialogSelectPort();

    void loadPorts();
signals:
    void s_portOpen(QString name);
    void s_portClose();
public slots:
    void on_portOpen(int result);
    void on_portClose(int result);
private slots:
    void on_cancel_clicked();

    void on_open_clicked();

private:
    Ui::DialogSelectPort *ui;

    WorkPort * workPort;

    QList<QSerialPortInfo> infos;

    //0-close
    //1-open
    //2-error open
    quint16 statusPort;
};

#endif // DIALOGSELECTPORT_H
