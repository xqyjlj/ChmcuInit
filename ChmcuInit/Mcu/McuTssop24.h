/*
 * Copyright (c) 2020-2020,  by xqyjlj
 *
 * SPDX-License-Identifier: LGPL
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-15     xqyjlj       the first version
 */
#ifndef MCUTSSOP24_H
#define MCUTSSOP24_H

#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include "McuXml.h"

#include "McuPin.h"
#include <QList>
#include "McuChip.h"

class McuTssop24: public QGroupBox
{
    Q_OBJECT
public:
    explicit McuTssop24(QWidget* parent = nullptr);
    void set_pin();
private:
    void set_pin_menu(McuPin* pin, QStringList list);
signals:
    void item_click(int _pin, int index);
public slots:
    void change_pin_color(int pin, int index, bool ischange);
    void send_index_changed_signals(QString pin, int index);
private:
    QGridLayout* gridLayout;
    McuChip* chip;

    McuPin* pin1;
    McuPin* pin2;
    McuPin* pin3;
    McuPin* pin4;
    McuPin* pin5;
    McuPin* pin6;
    McuPin* pin7;
    McuPin* pin8;
    McuPin* pin9;
    McuPin* pin10;
    McuPin* pin11;
    McuPin* pin12;
    McuPin* pin13;
    McuPin* pin14;
    McuPin* pin15;
    McuPin* pin16;
    McuPin* pin17;
    McuPin* pin18;
    McuPin* pin19;
    McuPin* pin20;
    McuPin* pin21;
    McuPin* pin22;
    McuPin* pin23;
    McuPin* pin24;

    McuXml* fun_mcu_xml;

    QList<McuPin*> pin_list;
};

#endif // MCUTSSOP24_H
