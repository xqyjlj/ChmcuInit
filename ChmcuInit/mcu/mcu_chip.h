/*
 * Copyright (c) 2020-2020,  by xqyjlj
 *
 * SPDX-License-Identifier: LGPL
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-15     xqyjlj       the first version
 */
#ifndef MCU_CHIP_H
#define MCU_CHIP_H
#include <QLabel>

class mcu_chip: public QLabel
{
public:
    explicit mcu_chip(QWidget* parent = nullptr);
};

#endif // MCU_CHIP_H
