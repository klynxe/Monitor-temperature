#include "dialogselectport.h"
#include "ui_dialogselectport.h"

#include <QtSerialPort/QSerialPortInfo>

#include <QMessageBox>

DialogSelectPort::DialogSelectPort(WorkPort * workPort, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSelectPort)
{
    ui->setupUi(this);
    statusPort = 0;
    this->workPort = workPort;
}

DialogSelectPort::~DialogSelectPort()
{
    delete ui;
}

void DialogSelectPort::loadPorts(){
    infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
        ui->availablePort->addItem(info.portName());
    if(infos.size() == 0)
    {
        ui->status->setText("Нет доступных COM портов");
    }
    else
    {
        ui->availablePort->setCurrentIndex(0);
    }

    switch(statusPort){
    case 0://close
        ui->status->setText("Порт закрыт");
        ui->open->setText("Открыть порт");
        break;
    case 2://error
        ui->status->setText("Ошибка открытия порта");
        ui->open->setText("Открыть порт");
        break;
    case 1://open
        ui->status->setText("Порт открыт");
        ui->open->setText("Закрыть порт");
        break;
    }

}

void DialogSelectPort::on_portOpen(int result)
{
    statusPort = result;
    switch(statusPort){
    case 0://close
        ui->status->setText("Порт закрыт");
        ui->open->setText("Открыть порт");
        break;
    case 2://error
        ui->status->setText("Ошибка открытия порта");
        ui->open->setText("Открыть порт");
        break;
    case 1://open
        ui->status->setText("Порт открыт");
        ui->open->setText("Закрыть порт");
        break;
    }
    ui->open->setEnabled(true);
}

void DialogSelectPort::on_portClose(int result)
{
    statusPort = result;
    switch(statusPort){
    case 0://close
        ui->status->setText("Порт закрыт");
        ui->open->setText("Открыть порт");
        break;
    case 2://error
        ui->status->setText("Ошибка открытия порта");
        ui->open->setText("Открыть порт");
        break;
    case 1://open
        ui->status->setText("Порт открыт");
        ui->open->setText("Закрыть порт");
        break;
    }
    ui->open->setEnabled(true);
}

void DialogSelectPort::on_cancel_clicked()
{
    close();
}

void DialogSelectPort::on_open_clicked()
{
    switch(statusPort){
    case 0://close
    case 2://error
        if(ui->availablePort->currentIndex() != -1)
        {
            ui->status->setText("Подключение...");
            ui->open->setEnabled(false);
            emit s_portOpen(ui->availablePort->currentText());
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("Ошибка! Не выбран порт");
            msgBox.exec();
        }
        break;
    case 1:
    {
        emit s_portClose();
        ui->status->setText("Закрытие...");
        ui->open->setEnabled(false);
    }
        break;

    }


}
