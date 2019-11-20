#ifndef DEVICESETTING_H
#define DEVICESETTING_H

#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QSpinBox>
#include <QVBoxLayout>

class DeviceSettingData
{
public:
    DeviceSettingData();
    DeviceSettingData(int P_1_7, int P_3_0, int P_3_8);

    bool checkValue();

    int currentP_1_7 = 0;
    int currentP_3_0 = 0;
    int currentP_3_8 = 0;
};

class DeviceSetting : public QObject
{
    Q_OBJECT
public:
    explicit DeviceSetting(int row, int column, bool topRow, bool firstColumn, QObject *parent = 0);

    void setValue(int P_1_7, int P_3_0, int P_3_8);

    void setEditable(bool editable);

    bool checkValueOnEdit();

    bool setValueFromEdit();

    void returnValue();

    QGroupBox *getGroupCell() const;

    QString getName() const;

    static bool indexByName(QString name, int& row, int& column);

    DeviceSettingData getDsd() const;

    int getCountTryRequest() const;
    void setCountTryRequest(int value);

private:
    int row;
    int column;
    int number;
    QString name;

    DeviceSettingData dsd;

    QGroupBox * groupCell;

    QVBoxLayout * layoutCell;

    QHBoxLayout * rowLable;
    QHBoxLayout * rowP;

    QLabel * lable_empty;
    QLabel * lable_empty_name;
    QLabel * lable_1_7;
    QLabel * lable_3_0;
    QLabel * lable_3_8;

    QLabel * lableP;
    QLabel * lableName;
    QSpinBox * spinP_1_7;
    QSpinBox * spinP_3_0;
    QSpinBox * spinP_3_8;

    int countTryRequest;

signals:

public slots:
};

#endif // DEVICESETTING_H
