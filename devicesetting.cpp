#include "devicesetting.h"

#include <QException>
#include <QIntValidator>

DeviceSetting::DeviceSetting(int row, int column, bool topRow, bool firstColumn, QObject *parent) : QObject(parent)
{
    this->row = row;
    this->column = column;
    this->name = QString('a'+row)+QString::number(column+1);

    groupCell = new QGroupBox;
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

    rowP = new QHBoxLayout;
    rowP->setSpacing(0);
    rowP->setContentsMargins(0,0,0,0);

    if(topRow) {
        if(firstColumn){
            lable_empty = new QLabel;
            lable_empty->setText("");
            lable_empty->setMinimumWidth(25);
            lable_empty->setMinimumHeight(15);
            lable_empty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            lable_empty->setAlignment(Qt::AlignCenter);
        }
        lable_empty_name = new QLabel;
        lable_empty_name->setText("");
        lable_empty_name->setMinimumWidth(25);
        lable_empty_name->setMinimumHeight(15);
        lable_empty_name->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        lable_empty_name->setAlignment(Qt::AlignCenter);
        lable_1_7 = new QLabel;
        lable_1_7->setText("1.7");
        lable_1_7->setMinimumWidth(50);
        lable_1_7->setMinimumHeight(15);
        lable_1_7->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        lable_1_7->setAlignment(Qt::AlignCenter);
        lable_3_0 = new QLabel;
        lable_3_0->setText("3.8");
        lable_3_0->setMinimumWidth(50);
        lable_3_0->setMinimumHeight(15);
        lable_3_0->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        lable_3_0->setAlignment(Qt::AlignCenter);
        lable_3_8 = new QLabel;
        lable_3_8->setText("3.8");
        lable_3_8->setMinimumWidth(50);
        lable_3_8->setMinimumHeight(15);
        lable_3_8->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        lable_3_8->setAlignment(Qt::AlignCenter);
    }

    if(firstColumn){
        lableP = new QLabel;
        lableP->setText("P,%");
        lableP->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        lableP->setMinimumWidth(25);
        lableP->setMinimumHeight(15);
    }
    lableName = new QLabel;
    lableName->setText(name);
    lableName->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    lableName->setMinimumWidth(25);
    lableName->setMinimumHeight(15);
    lableName->setAlignment(Qt::AlignCenter);
    lableName->setStyleSheet("font-weight: bold;");
    /*editP_1_7 = new QLineEdit;
    editP_1_7->setText("0");
    editP_1_7->setMinimumWidth(25);
    editP_1_7->setMinimumHeight(15);
    editP_1_7->setReadOnly(true);
    editP_1_7->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    editP_1_7->setValidator( new QIntValidator(0, 120, this) );*/
    spinP_1_7 = new QSpinBox;
    spinP_1_7->setValue(0);
    spinP_1_7->setMinimumWidth(50);
    spinP_1_7->setMinimumHeight(15);
    spinP_1_7->setReadOnly(true);
    spinP_1_7->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    spinP_1_7->setRange(0,120);
    spinP_1_7->findChild <QLineEdit * >( )->setReadOnly(true);
    spinP_3_0 = new QSpinBox;
    spinP_3_0->setValue(0);
    spinP_3_0->setMinimumWidth(50);
    spinP_3_0->setMinimumHeight(15);
    spinP_3_0->setReadOnly(true);
    spinP_3_0->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    spinP_3_0->setRange(0,120);
    spinP_3_0->findChild <QLineEdit * >( )->setReadOnly(true);
    spinP_3_8 = new QSpinBox;
    spinP_3_8->setValue(0);
    spinP_3_8->setMinimumWidth(50);
    spinP_3_8->setMinimumHeight(15);
    spinP_3_8->setReadOnly(true);
    spinP_3_8->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    spinP_3_8->setRange(0,100);
    spinP_3_8->setSingleStep(100);
    spinP_3_8->findChild <QLineEdit * >( )->setReadOnly(true);
    if(topRow)
    {
        if(firstColumn){
            rowLable->addWidget(lable_empty);
        }
        rowLable->addWidget(lable_empty_name);
        rowLable->addWidget(lable_1_7);
        rowLable->addWidget(lable_3_0);
        rowLable->addWidget(lable_3_8);
    }

    if(firstColumn){
        rowP->addWidget(lableP);
    }
    rowP->addWidget(lableName);
    rowP->addWidget(spinP_1_7);
    rowP->addWidget(spinP_3_0);
    rowP->addWidget(spinP_3_8);

    if(topRow)
        layoutCell->addLayout(rowLable);
    layoutCell->addLayout(rowP);

    groupCell->setLayout(layoutCell);
}

void DeviceSetting::setValue(int P_1_7, int P_3_0, int P_3_8)
{
    this->dsd.currentP_1_7 = P_1_7;
    this->dsd.currentP_3_0 = P_3_0;
    this->dsd.currentP_3_8 = P_3_8;

    spinP_1_7->setValue(P_1_7);
    spinP_3_0->setValue(P_3_0);
    spinP_3_8->setValue(P_3_8);
}

void DeviceSetting::setEditable(bool editable)
{
    spinP_1_7->setReadOnly(!editable);
    spinP_3_0->setReadOnly(!editable);
    spinP_3_8->setReadOnly(!editable);

    spinP_1_7->findChild <QLineEdit * >( )->setReadOnly(true);
    spinP_3_0->findChild <QLineEdit * >( )->setReadOnly(true);
    spinP_3_8->findChild <QLineEdit * >( )->setReadOnly(true);
}

bool DeviceSetting::checkValueOnEdit()
{
    return true;
}

bool DeviceSetting::setValueFromEdit()
{
    int P_1_7 = spinP_1_7->value();
    int P_3_0 = spinP_3_0->value();
    int P_3_8 = spinP_3_8->value();

    dsd.currentP_1_7 = P_1_7;
    dsd.currentP_3_0 = P_3_0;
    dsd.currentP_3_8 = P_3_8;

    return true;
}

void DeviceSetting::returnValue()
{
    spinP_1_7->setValue(dsd.currentP_1_7);
    spinP_3_0->setValue(dsd.currentP_3_0);
    spinP_3_8->setValue(dsd.currentP_3_8);
}

QGroupBox *DeviceSetting::getGroupCell() const
{
    return groupCell;
}

QString DeviceSetting::getName() const
{
    return name;
}

bool DeviceSetting::indexByName(QString name, int &row, int &column)
{
    try {
    if(name.size() < 2)
        return false;
    row = 'a'-name.at(0).toLower().toLatin1();
    column = name.at(1).toLower().toLatin1()-1;
    return true;
    }
    catch (QException e){
         return false;
    }
}

DeviceSettingData DeviceSetting::getDsd() const
{
    return dsd;
}

DeviceSettingData::DeviceSettingData()
{
    this->currentP_1_7 = 0;
    this->currentP_3_0 = 0;
    this->currentP_3_8 = 0;
}

DeviceSettingData::DeviceSettingData(int P_1_7, int P_3_0, int P_3_8)
{
    this->currentP_1_7 = P_1_7;
    this->currentP_3_0 = P_3_0;
    this->currentP_3_8 = P_3_8;
}
bool DeviceSettingData::checkValue()
{
    if(currentP_1_7 < 0 || currentP_1_7 > 120)
        return false;
    if(currentP_3_0 < 0 || currentP_3_0 > 120)
        return false;
    if(currentP_3_8 != 0 && currentP_3_8 != 100)
        return false;
    return true;
}
