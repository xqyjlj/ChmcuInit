/*
 * Copyright (c) 2020-2020,  by xqyjlj
 *
 * SPDX-License-Identifier: LGPL
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-15     xqyjlj       the first version
 */
#include "WindowPin.h"
#include "QDebug"
#include <QTreeWidgetItem>
WindowPin::WindowPin(QWidget* parent, QString path) : QTreeWidget(parent)
{
    xml_file_path = path;
    fun_mcu_xml = new McuXml(this);

    for (int i = 1; i <= 24; i++)
    {
        QStringList list;
        list = fun_mcu_xml->read_pin(":/mcu/hc32/res/db/mcu/HDSC/HC32/HC32F002/HC32F002D4P8.xml", list, i);
        QTreeWidgetItem* item = new QTreeWidgetItem(QStringList() << QString::number(i) + QString(" : ") + list.at(0));
        item->setWhatsThis(0, QString::number(i));
        for (int i = 0; i < list.length() - 1; i++)
        {
            QTreeWidgetItem* it_item = new QTreeWidgetItem(QStringList() << list.at(i + 1));
            it_item->setWhatsThis(0, QString::number(i + 1));
            item->addChild(it_item);
        }
        this->addTopLevelItem(item);
    }
    connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(item_double_clicked(QTreeWidgetItem*, int)), Qt::UniqueConnection);
}

void WindowPin::item_double_clicked(QTreeWidgetItem* item, int column)
{
    if(item->parent())
    {
        bool ischange = (item->backgroundColor(0) == Qt::green);
        if(ischange)
        {
            item->setBackgroundColor(0, Qt::white);
        }
        else
        {
            for (int i = 0; i < item->parent()->childCount() ; i++ )
            {
                item->parent()->child(i)->setBackgroundColor(0, Qt::white);
            }
            item->setBackgroundColor(0, Qt::green);
        }
        emit item_doubled_clicked_info(item->parent()->whatsThis(column).toInt(), item->whatsThis(column).toInt(), ischange);
    }
}

void WindowPin::change_item_color(int pin, int index)
{
    QTreeWidgetItem* item = this->topLevelItem(pin - 1);
    if(item)
    {
        item->setExpanded(true);
        for (int i = 0; i < item->childCount() ; i++ )
        {
            item->child(i)->setBackgroundColor(0, Qt::white);
        }
        QTreeWidgetItem* it_item = item->child(index - 1);
        if(it_item)
        {
            it_item->setBackgroundColor(0, Qt::green);
            return;
        }
        item->setExpanded(false);
    }
}

void WindowPin::set_xml_file_path(QString path)
{
    xml_file_path = path;
}
