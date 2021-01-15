/*
 * Copyright (c) 2020-2020,  by xqyjlj
 *
 * SPDX-License-Identifier: LGPL
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-15     xqyjlj       the first version
 */
#ifndef WINDOW_PIN_H
#define WINDOW_PIN_H

#include <QTreeWidget>
#include <QString>
#include "mcu_xml.h"
class window_pin : public QTreeWidget
{
    Q_OBJECT
public:
    explicit window_pin(QWidget* parent = nullptr, QString path = QString(""));

    void set_xml_file_path(QString path);
private:
    QString xml_file_path;
    mcu_xml* fun_mcu_xml;
signals:
    void item_doubled_clicked_info(int pin, int fun, bool ischange);
public slots:
    void change_item_color(int pin, int index);
private slots:
    void item_double_clicked(QTreeWidgetItem* item, int column);
};

#endif // WINDOW_PIN_H
