#ifndef DEVICEVALUE_H
#define DEVICEVALUE_H


#include <QObject>
#include <QVector>
#include <QMap>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QHBoxLayout>

const int COUNT_DEVICE = 62;
const QVector<int> rowSize = QVector<int>{11, 11, 9, 10, 8, 7, 6};

class DeviceValueData
{
public:
    DeviceValueData();
    DeviceValueData(int U_1_7, int U_3_0, int U_3_8,
                    int P_1_7, int P_3_0, int P_3_8,
                    int T);

    bool checkValue();
    int U_1_7;
    int U_3_0;
    int U_3_8;
    int P_1_7;
    int P_3_0;
    int P_3_8;
    int T;
};

class DeviceValue : public QObject
{
    Q_OBJECT
public:
    explicit DeviceValue(int row, int column, bool topRow, bool firstColumn, QObject *parent = 0);

    void setValue(int U_1_7, int U_3_0, int U_3_8,
                  int P_1_7, int P_3_0, int P_3_8,
                  int T);

    QGroupBox *getGroupCell() const;

    QString getName() const;

    DeviceValueData getDvd() const;

private:

    static QImage colorImg;

    int row;
    int column;
    QString name;

    DeviceValueData dvd;

    QGroupBox * groupCell;

    QVBoxLayout * layoutCell;

    QHBoxLayout * rowLable;
    QHBoxLayout * rowU;
    QHBoxLayout * rowP;
    QHBoxLayout * rowT;

    QLabel * lable_empty;
    QLabel * lable_1_7;
    QLabel * lable_3_0;
    QLabel * lable_3_8;

    QLabel * lableU;
    QLineEdit * editU_1_7;
    QLineEdit * editU_3_0;
    QLineEdit * editU_3_8;

    QLabel * lableP;
    QLineEdit * editP_1_7;
    QLineEdit * editP_3_0;
    QLineEdit * editP_3_8;

    QLabel * lableT;
    QWidget * wT_color;
    QLineEdit * editT_count;
    QLabel * lableName;
signals:

public slots:
};

#endif // DEVICEVALUE_H
