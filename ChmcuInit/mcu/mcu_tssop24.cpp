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
        pin_list.at(i - 1)->setText(list.at(0));
        pin_list.at(i - 1)->setWhatsThis(list.at(0));
        set_pin_menu(pin_list.at(i - 1), list);
    }
}
void mcu_tssop24::set_pin_menu(mcu_pin* pin, QStringList list)
{
    pin->setContextMenuPolicy(Qt::ActionsContextMenu);
    for (int i = 1; i < list.length(); i++)
    {
        QAction* action = new QAction(list.at(i), pin);
        action->setCheckable(true);
        pin->addAction(action);
    }
    pin->set_connect();
}
