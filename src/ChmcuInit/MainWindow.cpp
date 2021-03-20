/**
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
 ** Change Logs:
 ** Date           Author       Notes                    Email
 ** 2021-03-19     xqyjlj       the first version        xqyjlj@126.com
 **/
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "debug.h"
#include "xml_read.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList list = NXml::CXml_read().get_all_company_name();
    foreach (QString str, list)
    {
        LOG_D << str;
        QStringList list = NXml::CXml_read().get_all_family_name(str);
        foreach (QString str, list)
        {
            LOG_D << "   " + str;
            QStringList list = NXml::CXml_read().get_all_subfamily_name(str);
            foreach (QString str, list)
            {
                LOG_D << "      " + str;
                QStringList list = NXml::CXml_read().get_all_mcu_name(str);
                foreach (QString str, list)
                {
                    LOG_D << "          " + str;
                    NModel::CMcu_model model = NXml::CXml_read().get_all_mcu_info(str);
                    LOG_D << "              " + model.name << model.packagename
                          << model.core << model.current.lowest;
                }
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

