/*
 * Copyright (c) 2020-2020,  by xqyjlj
 *
 * SPDX-License-Identifier: LGPL
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-15     xqyjlj       the first version
 */
#ifndef MCU_TSSOP24_H
#define MCU_TSSOP24_H

#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include "mcu_xml.h"

#include "mcu_pin.h"
#include <QList>
#include "mcu_chip.h"

class mcu_tssop24: public QGroupBox
{
    Q_OBJECT
public:
    explicit mcu_tssop24(QWidget *parent = nullptr);
    void set_pin();
private:
    void set_pin_menu(mcu_pin *pin, QStringList list);
signals:
    void item_click(int _pin, int index);
public slots:
    void change_pin_color(int pin, int index, bool ischange);
    void send_index_changed_signals(QString pin, int index);
private:
    QGridLayout *gridLayout;
    mcu_chip *chip;

    mcu_pin *pin1;
    mcu_pin *pin2;
    mcu_pin *pin3;
    mcu_pin *pin4;
    mcu_pin *pin5;
    mcu_pin *pin6;
    mcu_pin *pin7;
    mcu_pin *pin8;
    mcu_pin *pin9;
    mcu_pin *pin10;
    mcu_pin *pin11;
    mcu_pin *pin12;
    mcu_pin *pin13;
    mcu_pin *pin14;
    mcu_pin *pin15;
    mcu_pin *pin16;
    mcu_pin *pin17;
    mcu_pin *pin18;
    mcu_pin *pin19;
    mcu_pin *pin20;
    mcu_pin *pin21;
    mcu_pin *pin22;
    mcu_pin *pin23;
    mcu_pin *pin24;

    mcu_xml *fun_mcu_xml;

    QList<mcu_pin *> pin_list;
};

#endif // MCU_TSSOP24_H
