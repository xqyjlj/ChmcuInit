/*
 * Copyright (c) 2020-2020,  by xqyjlj
 *
 * SPDX-License-Identifier: LGPL
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-12-26     xqyjlj       the first version
 */
#include "mcu_tssop24.h"
#include <QPainter>
#include <QDebug>
#include <QWheelEvent>
#include <QMenu>
#include <QAction>


mcu_tssop24::mcu_tssop24(QWidget* parent): QGroupBox(parent)
{
    gridLayout = new QGridLayout(this);
    chip = new mcu_chip();

    pin1 = new mcu_pin(this);
    pin2 = new mcu_pin(this);
    pin3 = new mcu_pin(this);
    pin4 = new mcu_pin(this);
    pin5 = new mcu_pin(this);
    pin6 = new mcu_pin(this);
    pin7 = new mcu_pin(this);
    pin8 = new mcu_pin(this);
    pin9 = new mcu_pin(this);
    pin10 = new mcu_pin(this);
    pin11 = new mcu_pin(this);
    pin12 = new mcu_pin(this);
    pin13 = new mcu_pin(this);
    pin14 = new mcu_pin(this);
    pin15 = new mcu_pin(this);
    pin16 = new mcu_pin(this);
    pin17 = new mcu_pin(this);
    pin18 = new mcu_pin(this);
    pin19 = new mcu_pin(this);
    pin20 = new mcu_pin(this);
    pin21 = new mcu_pin(this);
    pin22 = new mcu_pin(this);
    pin23 = new mcu_pin(this);
    pin24 = new mcu_pin(this);

    fun_mcu_xml = new mcu_xml(this);

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
void mcu_tssop24::set_pin()
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
        connect(pin_list.at(i - 1), SIGNAL(index_changed(QString, int, bool)), this, SLOT(send_index_changed_signals(QString, int, bool)));
    }
}
void mcu_tssop24::set_pin_menu(mcu_pin* pin, QStringList list)
{
    for (int i = 1; i < list.length(); i++)
    {
        pin->addItem(list.at(0) + QString(":") + list.at(i));
    }
}
void mcu_tssop24::send_index_changed_signals(QString pin, int index, bool ischange)
{
    for (int i = 1; i <= 24; i++)
    {
        if(pin_list.at(i - 1)->itemText(0) == pin)
        {
            emit item_click(i, index, ischange);
            break;
        }
    }
}
