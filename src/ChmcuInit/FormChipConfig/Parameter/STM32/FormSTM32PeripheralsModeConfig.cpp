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
#include "FormSTM32PeripheralsModeConfig.h"
#include "ui_FormSTM32PeripheralsModeConfig.h"
#include <QFile>
#include <QXmlStreamReader>
#include <QMessageBox>

#include "Debug.h"
#include <QCheckBox>
FormSTM32PeripheralsModeConfig::FormSTM32PeripheralsModeConfig(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::FormSTM32PeripheralsModeConfig)
{
    ui->setupUi(this);
}

FormSTM32PeripheralsModeConfig::~FormSTM32PeripheralsModeConfig()
{
    delete ui;
}

/**
 * @brief   设置IP核
 *
 * @param   mcu: mcu名
 *          ipLocate: IP核的地址
 *
 * @return  null
*/
void FormSTM32PeripheralsModeConfig::setIp(QString mcu, QString ipLocate)
{
//    mcu_name_g = mcu;
//    ip_locate_g = QCoreApplication::applicationDirPath() + ip_locate;
//    read_ip();
//    add_mode_widegt();
}

//void FormSTM32PeripheralsModeConfig::readIp(void)
//{
////    QFile file(ip_locate_g);
////    if (file.open(QFile::ReadOnly | QFile::Text))
////    {
////        QXmlStreamReader reader;
////        reader.setDevice(&file);
////        while (!reader.atEnd())
////        {
////            if (reader.isStartElement() &&
////                    reader.name() == QString("RefParameter") &&
////                    reader.attributes().value("Label").toString() == "Mode" &&
////                    reader.attributes().value("MCU").toString().contains(mcu_name_g))
////            {
////                while (!reader.atEnd())
////                {
////                    if (reader.isStartElement() && reader.name() == QString("PossibleValue"))
////                    {
////                        value_list_g << reader.attributes().value("Value").toString();
////                    }
////                    reader.readNext();
////                }
////                break;
////            }
////            reader.readNext();
////        }
////    }
////    else
////    {
////        QMessageBox::critical(nullptr, tr("Error"), tr("Cannot read file %1").arg(ip_locate_g));
////    }
////    file.close();
//}

//void FormSTM32PeripheralsModeConfig::addModeWidegt(void)
//{
////    foreach (QString str, value_list_g)
////    {
////        QCheckBox *checkBox = new QCheckBox(this);
////        checkBox->setObjectName("checkBox_" + str);
////        checkBox->setText(str);
////        ui->verticalLayout->addWidget(checkBox);
////    }
//}
