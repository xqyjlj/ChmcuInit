/*
 * Copyright (c) 2020-2020,  by xqyjlj
 *
 * SPDX-License-Identifier: LGPL
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-15     xqyjlj       the first version
 */
#ifndef MCUPIN_H
#define MCUPIN_H

#include <QComboBox>

class McuPin: public QComboBox
{
    Q_OBJECT
public:
    explicit McuPin(QWidget* parent = nullptr);
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

#endif // MCUPIN_H
