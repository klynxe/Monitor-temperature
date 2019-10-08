#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>

#include "devicesetting.h"
#include "devicevalue.h"
#include "dialogselectport.h"
#include "threadobject.h"
#include "workport.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void s_open(QString name);

public slots:
    void on_resultOpen(int result);
private slots:
    void on_deviceSettingEdit_clicked();

    void on_deviceSettingCancel_clicked();

    void on_deviceSettingSave_clicked();

    void on_deviceSettingSaveToFile_clicked();

    void on_deviceSettingLoadFromFile_clicked();

    void on_deviceValueSaveToFile_clicked();

    void on_deviceValueLoadFromFile_clicked();

    void on_selectPort_triggered();

private:
    Ui::MainWindow *ui;

    DialogSelectPort * dialogSelectPort;

    WorkPort * workPort;
    ThreadObject threadPort;

    QMap<QString, DeviceValue*> deviceValues;
    QMap<QString, DeviceSetting*> deviceSettings;

};

#endif // MAINWINDOW_H
