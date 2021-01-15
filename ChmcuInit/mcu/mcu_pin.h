/*
 * Copyright (c) 2020-2020,  by xqyjlj
 *
 * SPDX-License-Identifier: LGPL
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-15     xqyjlj       the first version
 */
#ifndef MCU_PIN_H
#define MCU_PIN_H

#include <QComboBox>

class mcu_pin: public QComboBox
{
    Q_OBJECT
public:
    explicit mcu_pin(QWidget* parent = nullptr);
    void setconnect(void);
Q_SIGNALS:
    void sigPopup();
protected:
    void showPopup();
private slots:
    void textchanged(int index);
private:

signals:
    void index_changed(QString pin, int fun);
};

#endif // MCU_PIN_H
