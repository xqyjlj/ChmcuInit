/*
 * Copyright (c) 2020-2020,  by xqyjlj
 *
 * SPDX-License-Identifier: LGPL
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-12-26     xqyjlj       the first version
 */
#include "McuTssop24.h"
#include <QPainter>
#include <QDebug>
#include <QWheelEvent>
#include <QMenu>
#include <QAction>


McuTssop24::McuTssop24(QWidget* parent): QGroupBox(parent)
{
    gridLayout = new QGridLayout(this);
    chip = new McuChip();

    pin1 = new McuPin(this);
    pin2 = new McuPin(this);
    pin3 = new McuPin(this);
    pin4 = new McuPin(this);
    pin5 = new McuPin(this);
    pin6 = new McuPin(this);
    pin7 = new McuPin(this);
    pin8 = new McuPin(this);
    pin9 = new McuPin(this);
    pin10 = new McuPin(this);
    pin11 = new McuPin(this);
    pin12 = new McuPin(this);
    pin13 = new McuPin(this);
    pin14 = new McuPin(this);
    pin15 = new McuPin(this);
    pin16 = new McuPin(this);
    pin17 = new McuPin(this);
    pin18 = new McuPin(this);
    pin19 = new McuPin(this);
    pin20 = new McuPin(this);
    pin21 = new McuPin(this);
    pin22 = new McuPin(this);
    pin23 = new McuPin(this);
    pin24 = new McuPin(this);

    fun_mcu_xml = new McuXml(this);

    pin_list << pin1 << pin2 << pin3 << pin4 << pin5 << pin6 << pin7 << pin8 << pin9
             << pin10 << pin11 << pin12 << pin13 << pin14 << pin15 << pin16 << pin17
             << pin18 << pin19 << pin20 << pin21 << pin22 << pin23 << pin24;

    this->setTitle(QString("HC32F002"));
    gridLayout->setSpacing(6);
    gridLayout->setContentsMargins(11, 11, 11, 11);

    QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(pin1->sizePolicy().hasHeightForWidth());
    pin1->setSizePolicy(sizePolicy);

    for (int i = 0; i < 24; i++)
    {
        if(i <= 11)
        {
            gridLayout->addWidget(pin_list.at(i), i, 0, 1, 1);
        }
        else
        {
            gridLayout->addWidget(pin_list.at(i), 23 - i, 2, 1, 1);
        }
    }

    chip->setPixmap(QPixmap(QString::fromUtf8(":/mcu_img/res/mcu_img/tssop24.jpg")));
    gridLayout->addWidget(chip, 0, 1, 12, 1);

    set_pin();

}
void McuTssop24::set_pin()
{
    for (int i = 1; i <= 24; i++)
    {
        QStringList list;
        list = fun_mcu_xml->read_pin(":/mcu/hc32/res/db/mcu/HDSC/HC32/HC32F002/HC32F002D4P8.xml", list, i);
        pin_list.at(i - 1)->addItem(list.at(0));
        pin_list.at(i - 1)->setWhatsThis(list.at(0));
        set_pin_menu(pin_list.at(i - 1), list);
        pin_list.at(i - 1)->setCurrentIndex(0);
        pin_list.at(i - 1)->setconnect();
        connect(pin_list.at(i - 1), SIGNAL(index_changed(QString, int)), this, SLOT(send_index_changed_signals(QString, int)));
    }
}
void McuTssop24::set_pin_menu(McuPin* pin, QStringList list)
{
    for (int i = 1; i < list.length(); i++)
    {
        pin->addItem(list.at(0) + QString(":") + list.at(i));
    }
}
void McuTssop24::send_index_changed_signals(QString pin, int index)
{
    for (int i = 1; i <= 24; i++)
    {
        if(pin_list.at(i - 1)->itemText(0) == pin)
        {
            emit item_click(i, index);
            break;
        }
    }
}
void McuTssop24::change_pin_color(int pin, int index, bool ischange)
{
    if(ischange)
    {
        pin_list.at(pin - 1)->setCurrentIndex(0);
    }
    else
    {
        pin_list.at(pin - 1)->setCurrentIndex(index);
    }
}