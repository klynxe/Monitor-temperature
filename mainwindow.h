#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QTimer>

#include "devicesetting.h"
#include "devicevalue.h"
#include "dialogselectport.h"
#include "threadobject.h"
#include "workport.h"

#define TIMER_PERIOD 200

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

    void s_data(QByteArray);

public slots:
    void on_resultOpen(int result);

    void on_data(QByteArray bytes);

    void on_timer();
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
    QString numberToName(int number);

private:
    Ui::MainWindow *ui;

    DialogSelectPort * dialogSelectPort;

    WorkPort * workPort;
    ThreadObject threadPort;

    QMap<QString, DeviceValue*> deviceValues;
    QMap<QString, DeviceSetting*> deviceSettings;

    int currentRequestDevice = 0;
    int currentTime = 0;

    QTimer timer;

    QByteArray buffFull;

};

#endif // MAINWINDOW_H
