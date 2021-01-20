/*
 * Copyright (c) 2020-2020,  by xqyjlj
 *
 * SPDX-License-Identifier: LGPL
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-15     xqyjlj       the first version
 */
#ifndef WINDOWPIN_H
#define WINDOWPIN_H

#include <QTreeWidget>
#include <QString>
#include "McuXml.h"
class WindowPin : public QTreeWidget
{
    Q_OBJECT
public:
    explicit WindowPin(QWidget* parent = nullptr, QString path = QString(""));

    void set_xml_file_path(QString path);
private:
    QString xml_file_path;
    McuXml* fun_mcu_xml;
signals:
    void item_doubled_clicked_info(int pin, int index, bool ischange);
public slots:
    void change_item_color(int pin, int index);
private slots:
    void item_double_clicked(QTreeWidgetItem* item, int column);
};

#endif // WINDOWPIN_H
