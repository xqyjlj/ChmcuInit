/*
 * Copyright (c) 2020-2020,  by xqyjlj
 *
 * SPDX-License-Identifier: LGPL
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-15     xqyjlj       the first version
 */
#include "master.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    master w;
    w.showMaximized();
    w.show();

    return a.exec();
}
