/*
 * Copyright (c) 2020-2020,  by xqyjlj
 *
 * SPDX-License-Identifier: LGPL
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-12-24     xqyjlj       the first version
 */
#include "mcu.h"
#include <QHeaderView>
mcu::mcu(QObject* parent) : QObject(parent)
{

}

void mcu::set_mcu_treeWidget_Resize(QTreeWidget* obj)
{
    QHeaderView* head = obj->header();
    head->setSectionResizeMode(QHeaderView::ResizeToContents);
}
