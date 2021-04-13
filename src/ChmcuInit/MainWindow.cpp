﻿/**
 ** This file is part of the ChmcuInit project.
 ** Copyright 2021 xqyjlj <xqyjlj@126.com>.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **
 **
 ** 该文件是ChmcuInit项目的一部分。
 ** 版权所有2021 xqyjlj
 **
 ** 本程序是免费软件:您可以重新发布和/或修改它
 ** 根据GNU通用公共许可证的条款，由自由软件基金会，或第三版许可证，或(随您选择)任何更新版本。
 **
 ** 分发此程序是希望它会有用，但没有任何保证：甚至没有默示的保证特定目的的适销性或适用性。有关更多详细信息，请参见GNU通用公共许可证。
 **
 ** 您应该已经与这个程序一起收到GNU通用公共许可证的副本。如果不是，请参见<http://www.gnu.org/licenses/>。
 **
 ** Change Logs:
 ** Date           Author       Notes                    Email
 ** 2021-03-20     xqyjlj       the first version        xqyjlj@126.com
 **/
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Debug.h"
#include "Model.h"
#include "XmlRead.h"
#include "FormHome.h"

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mbaseObject = new BaseObject(this);

    ASSERT_X(mbaseObject, "MainWindow", "空指针");

    ui->formHome->setBaseObject(mbaseObject);

    ui->MainWindowStackedWidget->setCurrentIndex(0);
    connect(ui->formHome, &FormHome::createMcuProject, this, [ = ](QString name)
    {
        Q_UNUSED(name);
        this->setWindowState(Qt::WindowMaximized);
        ui->formChipConfig->setBaseObject(mbaseObject);
        ui->MainWindowStackedWidget->setCurrentIndex(1);
    });

#ifdef QT_NO_DEBUG
    ui->MainWindowStackedWidget->setCurrentIndex(0);
#else
//    this->setWindowState(Qt::WindowMaximized);
//    ui->formChipConfig->setMcu("STM32F103C8T6");
//    ui->MainWindowStackedWidget->setCurrentIndex(1);
#endif
}


MainWindow::~MainWindow()
{
    delete ui;
}

