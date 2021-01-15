/*
 * Copyright (c) 2020-2020,  by xqyjlj
 *
 * SPDX-License-Identifier: LGPL
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-12-27     xqyjlj       the first version
 */
#include "mcu_pin.h"
#include <QDebug>
#include <QEvent>
mcu_pin::mcu_pin(QWidget* parent): QComboBox(parent)
{
    QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    this->setSizePolicy(sizePolicy);
}
void mcu_pin::showPopup()
{
    emit sigPopup();
    QComboBox::showPopup();
    QWidget* popup = this->findChild<QFrame*>();
    popup->move(popup->x(), popup->y() + 4);
}

void mcu_pin::textchanged(int index)
{
    if(this->itemText(index).contains(QString(":")))
    {
        this->setStyleSheet("QComboBox { "
                            "background-color: rgb(0, 255, 0);"
                            "border: 0px solid gray;"
                            "}");
        emit index_changed(this->itemText(0), index, true);
    }
    else
    {
        this->setStyleSheet("");
        emit index_changed(this->itemText(0), index, false);
    }
}

void mcu_pin::setconnect()
{
    connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(textchanged(int)));
}
