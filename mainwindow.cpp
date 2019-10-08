#include "devicesetting.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QFileDialog>
#include <QException>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    WorkPort * workPort = new WorkPort;

    dialogSelectPort = new DialogSelectPort(workPort);
    dialogSelectPort->setModal(true);



    connect(dialogSelectPort, SIGNAL(s_portOpen(QString)), workPort, SLOT(on_portOpen(QString)));
    connect(dialogSelectPort, SIGNAL(s_portClose()), workPort, SLOT(on_portClose()));
    connect(workPort, SIGNAL(s_portOpen(result)), dialogSelectPort, SLOT(on_portOpen(result)));
    connect(workPort, SIGNAL(s_portClose(result)), dialogSelectPort, SLOT(on_portClose(result)));

    workPort->moveToThread(&threadPort);
    threadPort.start();



    //Create cell for current value
    {
        QWidget * widgetForScroll = new QWidget;
        QHBoxLayout * layoutWithAllCell = new QHBoxLayout;
        layoutWithAllCell->setSpacing(0);
        layoutWithAllCell->setContentsMargins(1,1,1,1);

        for(int i = 0; i < rowSize.size(); i++)
        {
            QVBoxLayout * layoutWithRowCell = new QVBoxLayout;
            layoutWithRowCell->setContentsMargins(5,i*20,5,i*20);
            layoutWithRowCell->setSpacing(0);

            for(int j = rowSize[i]; j > 0; j--)
            {
                DeviceValue * dv = new DeviceValue(j-1, i, j-1 == rowSize[i]-1, i == 0);
                deviceValues.insert(dv->getName(), dv);
                layoutWithRowCell->addWidget(dv->getGroupCell());
            }
            layoutWithAllCell->addLayout(layoutWithRowCell);
        }
        //layoutWithAllCell->setSizeConstraint(layoutWithAllCell->SetMinimumSize);
        layoutWithAllCell->setSizeConstraint(layoutWithAllCell->SetMinimumSize);

        //ui->layout->setLayout(layoutWithAllCell);
        widgetForScroll->setLayout(layoutWithAllCell);
        ui->rootCellLayoutCurrentValue->setWidget(widgetForScroll);
    }

    //Create cell for set value
    {
        QWidget * widgetForScroll = new QWidget;
        QHBoxLayout * layoutWithAllCell = new QHBoxLayout;
        layoutWithAllCell->setSpacing(0);
        layoutWithAllCell->setContentsMargins(1,1,1,1);

        for(int i = 0; i < rowSize.size(); i++)
        {
            QVBoxLayout * layoutWithRowCell = new QVBoxLayout;
            layoutWithRowCell->setContentsMargins(5,i*20,5,i*20);
            layoutWithRowCell->setSpacing(0);
            for(int j = rowSize[i]; j > 0; j--)
            {
                DeviceSetting * ds = new DeviceSetting(j-1, i, j-1 == rowSize[i]-1, i == 0);
                deviceSettings.insert(ds->getName(), ds);
                layoutWithRowCell->addWidget(ds->getGroupCell());
            }
            layoutWithAllCell->addLayout(layoutWithRowCell);
        }
        //layoutWithAllCell->setSizeConstraint(layoutWithAllCell->SetMinimumSize);
        layoutWithAllCell->setSizeConstraint(layoutWithAllCell->SetMinimumSize);

        //ui->layout->setLayout(layoutWithAllCell);
        widgetForScroll->setLayout(layoutWithAllCell);
        ui->rootCellLayoutSetValue->setWidget(widgetForScroll);
    }

    ui->deviceSettingSave->setVisible(false);
    ui->deviceSettingCancel->setVisible(false);
}

MainWindow::~MainWindow()
{
    threadPort.quit();
    threadPort.wait();
    delete ui;
}

void MainWindow::on_resultOpen(int result)
{

}

void MainWindow::on_deviceSettingEdit_clicked()
{
    ui->deviceSettingSave->setVisible(true);
    ui->deviceSettingCancel->setVisible(true);

    ui->deviceSettingEdit->setVisible(false);
    ui->deviceSettingSaveToFile->setVisible(false);
    ui->deviceSettingLoadFromFile->setVisible(false);

    for(DeviceSetting* ds : deviceSettings){
        ds->setEditable(true);
    }
}

void MainWindow::on_deviceSettingCancel_clicked()
{
    for(DeviceSetting* ds : deviceSettings){
        ds->returnValue();
        ds->setEditable(false);
    }

    ui->deviceSettingSave->setVisible(false);
    ui->deviceSettingCancel->setVisible(false);

    ui->deviceSettingEdit->setVisible(true);
    ui->deviceSettingSaveToFile->setVisible(true);
    ui->deviceSettingLoadFromFile->setVisible(true);

}

void MainWindow::on_deviceSettingSave_clicked()
{
    for(DeviceSetting* ds : deviceSettings){
        if(!ds->checkValueOnEdit())
        {
            QMessageBox msgBox;
            msgBox.setText("Введены некорректные данные " + ds->getName()+". \nДопустимо: P 1.7 (1-120) \nP 3.0 (1-120) \nP 3.8 (1 или 100)");
            msgBox.exec();
            return;
        }
    }

    for(DeviceSetting* ds : deviceSettings){
        ds->setValueFromEdit();
        ds->setEditable(false);
    }

    ui->deviceSettingSave->setVisible(false);
    ui->deviceSettingCancel->setVisible(false);

    ui->deviceSettingEdit->setVisible(true);
    ui->deviceSettingSaveToFile->setVisible(true);
    ui->deviceSettingLoadFromFile->setVisible(true);

    QMessageBox msgBox;
    msgBox.setText("Сохранено");
    msgBox.exec();
    return;
}

void MainWindow::on_deviceSettingSaveToFile_clicked()
{
    QString path = QFileDialog::getSaveFileName(this, QObject::tr("Укажите файл для сохранения"),
        QCoreApplication::applicationDirPath (),
        QObject::tr("Файл настроек (*.rocl)"),0,QFileDialog::DontUseNativeDialog).trimmed();
    if(path.isEmpty())
    {
        return;
    }

    QString fileData = "";
    for(DeviceSetting* ds : deviceSettings){
        if(!fileData.isEmpty())
            fileData+="\n";
        fileData+=ds->getName()+"-"+QString::number(ds->getDsd().currentP_1_7)+";"+
                QString::number(ds->getDsd().currentP_3_0)+";"+
                QString::number(ds->getDsd().currentP_3_8);
    }

    QFile file(path);
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox msgBox;
        msgBox.setText("Ошибка открытия файла для записи");
        msgBox.exec();
        file.close();
        return;
    }

    int n = file.write(fileData.toUtf8());
    file.close();
    if(n != fileData.count())
    {
        QMessageBox msgBox;
        msgBox.setText("Ошибка записи файла");
        msgBox.exec();
        file.close();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Файл успешно сохранен");
        msgBox.exec();
        file.close();
    }

}

void MainWindow::on_deviceSettingLoadFromFile_clicked()
{
    QString path =  QFileDialog::getOpenFileName(this, QObject::tr("Выберите файл"),
        QCoreApplication::applicationDirPath (),
        QObject::tr("Проект (*.rocl)"),0,QFileDialog::DontUseNativeDialog);
    QFile file(path);
    if (!file.exists())
    {
        return;
    }

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox msgBox;
        msgBox.setText("Не удалось открыть файл");
        msgBox.exec();
        return;
    }

    QMap<QString, DeviceSettingData> filesData;

    try {
        if(file.size() == 0)
        {
            QMessageBox msgBox;
            msgBox.setText("Файл пуст");
            msgBox.exec();
            return;
        }
        while(true)
        {
            QByteArray lineData = file.readLine();
            if(lineData.size() < 1)
                break;
            QString line = QString::fromUtf8(lineData);
            QStringList listline = line.split("-",line.SkipEmptyParts);
            if(listline.size() != 2)
            {
                QMessageBox msgBox;
                msgBox.setText("Файл не корректный");
                msgBox.exec();
                return;
            }
            QString partName = listline.at(0);
            QString partData = listline.at(1);

            QStringList listData = partData.split(";",line.SkipEmptyParts);
            if(listData.size() != 3)
            {
                QMessageBox msgBox;
                msgBox.setText("Файл не корректный");
                msgBox.exec();
                return;
            }

            bool okP_1_7, okP_3_0, okP_3_8;
            int P_1_7, P_3_0, P_3_8;
            P_1_7 = listData.at(0).toInt(&okP_1_7);
            P_3_0 = listData.at(1).toInt(&okP_3_0);
            P_3_8 = listData.at(2).toInt(&okP_3_8);

            int row, column;
            if(!DeviceSetting::indexByName(partName, row, column))
            {
                QMessageBox msgBox;
                msgBox.setText("Файл не корректный");
                msgBox.exec();
                return;
            }

            if(!okP_1_7 || !okP_3_0 || !okP_3_8)
            {
                QMessageBox msgBox;
                msgBox.setText("Файл не корректный");
                msgBox.exec();
                return;
            }

            DeviceSettingData dsd = DeviceSettingData(P_1_7, P_3_0, P_3_8);
            if(!dsd.checkValue())
            {
                QMessageBox msgBox;
                msgBox.setText("Файл не корректный");
                msgBox.exec();
                return;
            }
            filesData.insert(partName, dsd);
        }



        for(QString key:filesData.keys()){
            DeviceSettingData dsd = filesData.value(key);
            deviceSettings.value(key)->setValue(dsd.currentP_1_7, dsd.currentP_3_0, dsd.currentP_3_8);
        }
    }
    catch(QException e) {
        QMessageBox msgBox;
        msgBox.setText("Ошибка загрузки файла");
        msgBox.exec();
        return;
    }

    QMessageBox msgBox;
    msgBox.setText("Успешно загружено");
    msgBox.exec();
    return;

}

void MainWindow::on_deviceValueSaveToFile_clicked()
{
    QString path = QFileDialog::getSaveFileName(this, QObject::tr("Укажите файл для сохранения"),
        QCoreApplication::applicationDirPath (),
        QObject::tr("Файл настроек (*.rocx)"),0,QFileDialog::DontUseNativeDialog).trimmed();
    if(path.isEmpty())
    {
        return;
    }

    QString fileData = "";
    for(DeviceValue* dv : deviceValues){
        if(!fileData.isEmpty())
            fileData+="\n";
        fileData+=dv->getName()+"-"+QString::number(dv->getDvd().U_1_7)+";"+QString::number(dv->getDvd().U_3_0)+";"+QString::number(dv->getDvd().U_3_8) +";" +
                QString::number(dv->getDvd().P_1_7)+";"+QString::number(dv->getDvd().P_3_0)+";"+QString::number(dv->getDvd().P_3_8) +";" +
                QString::number(dv->getDvd().T);
    }

    QFile file(path);
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox msgBox;
        msgBox.setText("Ошибка открытия файла для записи");
        msgBox.exec();
        file.close();
        return;
    }

    int n = file.write(fileData.toUtf8());
    file.close();
    if(n != fileData.count())
    {
        QMessageBox msgBox;
        msgBox.setText("Ошибка записи файла");
        msgBox.exec();
        file.close();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Файл успешно сохранен");
        msgBox.exec();
        file.close();
    }
}

void MainWindow::on_deviceValueLoadFromFile_clicked()
{
    QString path =  QFileDialog::getOpenFileName(this, QObject::tr("Выберите файл"),
        QCoreApplication::applicationDirPath (),
        QObject::tr("Данные (*.rocx)"),0,QFileDialog::DontUseNativeDialog);
    QFile file(path);
    if (!file.exists())
    {
        return;
    }

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox msgBox;
        msgBox.setText("Не удалось открыть файл");
        msgBox.exec();
        return;
    }

    QMap<QString, DeviceValueData> filesData;

    try {
        if(file.size() == 0)
        {
            QMessageBox msgBox;
            msgBox.setText("Файл пуст");
            msgBox.exec();
            return;
        }
        while(true)
        {
            QByteArray lineData = file.readLine();
            if(lineData.size() < 1)
                break;
            QString line = QString::fromUtf8(lineData);
            QStringList listline = line.split("-",line.SkipEmptyParts);
            if(listline.size() != 2)
            {
                QMessageBox msgBox;
                msgBox.setText("Файл не корректный");
                msgBox.exec();
                return;
            }
            QString partName = listline.at(0);
            QString partData = listline.at(1);

            QStringList listData = partData.split(";",line.SkipEmptyParts);
            if(listData.size() != 7)
            {
                QMessageBox msgBox;
                msgBox.setText("Файл не корректный");
                msgBox.exec();
                return;
            }

            bool okU_1_7, okU_3_0, okU_3_8,okP_1_7, okP_3_0, okP_3_8, okT;
            int U_1_7, U_3_0, U_3_8, P_1_7, P_3_0, P_3_8, Temp;
            U_1_7 = listData.at(0).toInt(&okU_1_7);
            U_3_0 = listData.at(1).toInt(&okU_3_0);
            U_3_8 = listData.at(2).toInt(&okU_3_8);
            P_1_7 = listData.at(3).toInt(&okP_1_7);
            P_3_0 = listData.at(4).toInt(&okP_3_0);
            P_3_8 = listData.at(5).toInt(&okP_3_8);
            Temp = listData.at(6).toInt(&okT);

            int row, column;
            if(!DeviceSetting::indexByName(partName, row, column))
            {
                QMessageBox msgBox;
                msgBox.setText("Файл не корректный");
                msgBox.exec();
                return;
            }

            if(!okU_1_7 || !okU_3_0 || !okU_3_8 || !okP_1_7 || !okP_3_0 || !okP_3_8 || !okT)
            {
                QMessageBox msgBox;
                msgBox.setText("Файл не корректный");
                msgBox.exec();
                return;
            }

            DeviceValueData dvd = DeviceValueData(U_1_7, U_3_0, U_3_8, P_1_7, P_3_0, P_3_8, Temp);
            if(!dvd.checkValue())
            {
                QMessageBox msgBox;
                msgBox.setText("Файл не корректный");
                msgBox.exec();
                return;
            }
            filesData.insert(partName, dvd);
        }

        for(QString key:filesData.keys()){
            DeviceValueData dvd = filesData.value(key);
            deviceValues.value(key)->setValue(dvd.U_1_7, dvd.U_3_0, dvd.U_3_8, dvd.P_1_7, dvd.P_3_0, dvd.P_3_8, dvd.T);
        }
    }
    catch(QException e) {
        QMessageBox msgBox;
        msgBox.setText("Ошибка загрузки файла");
        msgBox.exec();
        return;
    }

    QMessageBox msgBox;
    msgBox.setText("Успешно загружено");
    msgBox.exec();
    return;
}

void MainWindow::on_selectPort_triggered()
{
    dialogSelectPort->loadPorts();
    dialogSelectPort->show();
}
