#include "devicevalue.h"

#include <QRgb>

QImage DeviceValue::colorImg = QImage(":/img/color.png");

DeviceValue::DeviceValue(int row, int column, bool topRow, bool firstColumn, QObject *parent) : QObject(parent)
{
    this->row = row;
    this->column = column;
    this->name = QString('a'+row)+QString::number(column+1);

    groupCell = new QGroupBox;
    //groupCell->setTitle(QString('a'+j-1)+QString::number(i+1));
    groupCell->setTitle("");

    layoutCell = new QVBoxLayout;
    layoutCell->setSpacing(0);
    layoutCell->setContentsMargins(1,1,1,1);

    if(topRow)
    {
        rowLable = new QHBoxLayout;
        rowLable->setSpacing(0);
        rowLable->setContentsMargins(0,0,0,0);
    }

    rowU = new QHBoxLayout;
    rowU->setSpacing(0);
    rowU->setContentsMargins(0,0,0,0);
    rowP = new QHBoxLayout;
    rowP->setSpacing(0);
    rowP->setContentsMargins(0,0,0,0);
    rowT = new QHBoxLayout;
    rowT->setSpacing(0);
    rowT->setContentsMargins(0,0,0,0);

    if(topRow) {
        if(firstColumn){
            lable_empty = new QLabel;
            lable_empty->setText("");
            lable_empty->setMinimumWidth(25);
            lable_empty->setMinimumHeight(15);
            lable_empty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            lable_empty->setAlignment(Qt::AlignCenter);
        }
        lable_1_7 = new QLabel;
        lable_1_7->setText("1.7");
        lable_1_7->setMinimumWidth(25);
        lable_1_7->setMinimumHeight(15);
        lable_1_7->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        lable_1_7->setAlignment(Qt::AlignCenter);
        lable_3_0 = new QLabel;
        lable_3_0->setText("3.8");
        lable_3_0->setMinimumWidth(25);
        lable_3_0->setMinimumHeight(15);
        lable_3_0->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        lable_3_0->setAlignment(Qt::AlignCenter);
        lable_3_8 = new QLabel;
        lable_3_8->setText("3.8");
        lable_3_8->setMinimumWidth(25);
        lable_3_8->setMinimumHeight(15);
        lable_3_8->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        lable_3_8->setAlignment(Qt::AlignCenter);
    }

    if(firstColumn){
        lableU = new QLabel;
        lableU->setText("U,В");
        lableU->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        lableU->setMinimumWidth(25);
        lableU->setMinimumHeight(15);
    }
    editU_1_7 = new QLineEdit;
    editU_1_7->setText("0");
    editU_1_7->setMinimumWidth(25);
    editU_1_7->setMinimumHeight(15);
    editU_1_7->setReadOnly(true);
    editU_1_7->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    editU_3_0 = new QLineEdit;
    editU_3_0->setText("0");
    editU_3_0->setMinimumWidth(25);
    editU_3_0->setMinimumHeight(15);
    editU_3_0->setReadOnly(true);
    editU_3_0->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    editU_3_8 = new QLineEdit;
    editU_3_8->setText("0");
    editU_3_8->setMinimumWidth(25);
    editU_3_8->setMinimumHeight(15);
    editU_3_8->setReadOnly(true);
    editU_3_8->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    if(firstColumn){
        lableP = new QLabel;
        lableP->setText("P,Вт");
        lableP->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        lableP->setMinimumWidth(25);
        lableP->setMinimumHeight(15);
    }
    editP_1_7 = new QLineEdit;
    editP_1_7->setText("0");
    editP_1_7->setMinimumWidth(25);
    editP_1_7->setMinimumHeight(15);
    editP_1_7->setReadOnly(true);
    editP_1_7->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    editP_3_0 = new QLineEdit;
    editP_3_0->setText("0");
    editP_3_0->setMinimumWidth(25);
    editP_3_0->setMinimumHeight(15);
    editP_3_0->setReadOnly(true);
    editP_3_0->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    editP_3_8 = new QLineEdit;
    editP_3_8->setText("0");
    editP_3_8->setMinimumWidth(25);
    editP_3_8->setMinimumHeight(15);
    editP_3_8->setReadOnly(true);
    editP_3_8->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    if(firstColumn){
        lableT = new QLabel;
        lableT->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        lableT->setText("T,°C");
        lableT->setMinimumWidth(25);
        lableT->setMinimumHeight(15);
    }
    wT_color = new QWidget;
    wT_color->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    QRgb rgbColor;
    rgbColor = colorImg.pixel(0,colorImg.height()-1);
    wT_color->setStyleSheet("background-color:rgb(" + QString::number(qRed(rgbColor))+ ", " +
                            QString::number(qGreen(rgbColor))+ ", " +
                            QString::number(qBlue(rgbColor))+ ");");
    wT_color->setMinimumWidth(25);
    wT_color->setMinimumHeight(15);
    editT_count = new QLineEdit;
    editT_count->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    editT_count->setText("0");
    editT_count->setMinimumWidth(25);
    editT_count->setMinimumHeight(15);
    editT_count->setReadOnly(true);
    lableName = new QLabel;
    lableName->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    lableName->setMinimumWidth(25);
    lableName->setMinimumHeight(15);
    lableName->setText(name);
    lableName->setAlignment(Qt::AlignCenter);
    lableName->setStyleSheet("font-weight: bold;");

    if(topRow)
    {
        if(firstColumn){
            rowLable->addWidget(lable_empty);
        }
        rowLable->addWidget(lable_1_7);
        rowLable->addWidget(lable_3_0);
        rowLable->addWidget(lable_3_8);
    }

    if(firstColumn){
        rowU->addWidget(lableU);
    }
    rowU->addWidget(editU_1_7);
    rowU->addWidget(editU_3_0);
    rowU->addWidget(editU_3_8);

    if(firstColumn){
        rowP->addWidget(lableP);
    }
    rowP->addWidget(editP_1_7);
    rowP->addWidget(editP_3_0);
    rowP->addWidget(editP_3_8);

    if(firstColumn){
        rowT->addWidget(lableT);
    }
    rowT->addWidget(wT_color);
    rowT->addWidget(editT_count);
    rowT->addWidget(lableName);
    rowT->setStretchFactor(lableT, 0);
    rowT->setStretchFactor(wT_color, 1);
    rowT->setStretchFactor(editT_count, 1);
    rowT->setStretchFactor(lableName, 1);

    if(topRow)
        layoutCell->addLayout(rowLable);
    layoutCell->addLayout(rowU);
    layoutCell->addLayout(rowP);
    layoutCell->addLayout(rowT);

    groupCell->setLayout(layoutCell);
}

void DeviceValue::setValue(int U_1_7, int U_3_0, int U_3_8, int P_1_7, int P_3_0, int P_3_8, int T)
{
    dvd.U_1_7 = U_1_7;
    dvd.U_3_0 = U_3_0;
    dvd.U_3_8 = U_3_8;
    dvd.P_1_7 = P_1_7;
    dvd.P_3_0 = P_3_0;
    dvd.P_3_8 = P_3_8;
    dvd.T = T;

    editU_1_7->setText(QString::number(U_1_7));
    editU_3_0->setText(QString::number(U_3_0));
    editU_3_8->setText(QString::number(U_3_8));

    editP_1_7->setText(QString::number(P_1_7));
    editP_3_0->setText(QString::number(P_3_0));
    editP_3_8->setText(QString::number(P_3_8));

    editT_count->setText(QString::number(T));
    QRgb rgbColor;
    if(T >= 0 && T <= 100)
    {
        int row = (colorImg.height()-1)/100*T;
        rgbColor = colorImg.pixel(0,colorImg.height()-1-row);
    }
    else
    {
        rgbColor = colorImg.pixel(0,0);
    }

    wT_color->setStyleSheet("background-color:rgb(" + QString::number(qRed(rgbColor))+ ", " +
                            QString::number(qGreen(rgbColor))+ ", " +
                            QString::number(qBlue(rgbColor))+ ");");
}

QGroupBox *DeviceValue::getGroupCell() const
{
    return groupCell;
}

QString DeviceValue::getName() const
{
    return name;
}

DeviceValueData DeviceValue::getDvd() const
{
    return dvd;
}

DeviceValueData::DeviceValueData()
{
    this->U_1_7 = 0;
    this->U_3_0 = 0;
    this->U_3_8 = 0;
    this->P_1_7 = 0;
    this->P_3_0 = 0;
    this->P_3_8 = 0;
    this->T = 0;
}

DeviceValueData::DeviceValueData(int U_1_7, int U_3_0, int U_3_8, int P_1_7, int P_3_0, int P_3_8, int T)
{
    this->U_1_7 = U_1_7;
    this->U_3_0 = U_3_0;
    this->U_3_8 = U_3_8;
    this->P_1_7 = P_1_7;
    this->P_3_0 = P_3_0;
    this->P_3_8 = P_3_8;
    this->T = T;
}

bool DeviceValueData::checkValue()
{
    return true;
}
