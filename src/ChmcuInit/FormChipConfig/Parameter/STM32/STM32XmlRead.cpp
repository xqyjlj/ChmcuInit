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
#include "STM32XmlRead.h"
#include <QXmlStreamReader>
#include <QFile>
#include <QMessageBox>
#include "Debug.h"

#include <QCoreApplication>

namespace STM32Xml
{
STM32XmlRead::STM32XmlRead(QObject* parent) : QObject(parent)
{

}

/**
 * @brief   获得STM32的IP内容中F1的IO模型
 *
 * @param   local: 库位置
 *          QString：亚科名
 *          McuName：mcu名
 *
 * @return  STM32的IP内容中F1的IO库模型
*/
STM32Model::XmlIpF1IoModel STM32XmlRead::getIpF1IoModel(QString local, QString subfamily, QString mcuName) const
{
    STM32Model::XmlIpF1IoModel _model;
    _model.mcuName = mcuName;
    _model.subFamilyName = subfamily;
    QFile file(local);
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QXmlStreamReader reader;
        reader.setDevice(&file);
        while (!reader.atEnd())
        {
            if (reader.isStartElement() && reader.name() == QString("SubFamily") &&
                    reader.attributes().value("Name").toString() == subfamily)
            {
                while (!reader.atEnd())
                {
                    if (reader.isStartElement() && reader.name() == QString("Configuration") &&
                            reader.attributes().value("McuName").toString().contains(mcuName))
                    {
                        _model.mode = readIpF1IoModeModel(&reader);
                        return _model;
                    }
                    reader.readNext();
                }
            }
            reader.readNext();
        }
    }
    else
    {
        QMessageBox::critical(nullptr, tr("Error"), tr("Cannot read file %1").arg(local));
    }
    file.close();
    return _model;
}

/**
 * @brief   获得STM32的IP内容中F1的IO模型中的模式库
 *
 * @param   reader: 读XML工具
 *
 * @return  STM32的IP内容中F1的IO库模型中的模式库
*/
QList<STM32Model::XmlIpF1IoModel::ModeModel> STM32XmlRead::readIpF1IoModeModel(QXmlStreamReader* reader) const
{
    QList<STM32Model::XmlIpF1IoModel::ModeModel> _modeModels;
    while (!reader->atEnd())
    {
        if (reader->isStartElement() && reader->name() == QString("Mode"))
        {
            STM32Model::XmlIpF1IoModel::ModeModel _modeModel;
            _modeModel.name = reader->attributes().value("Name").toString();
            _modeModel.widgets = reader->attributes().value("Widgets").toString();
            _modeModel.tables  = readIpF1IoTableModel(reader);
            _modeModels << _modeModel;
        }
        else if (reader->isEndElement() && reader->name() == QString("Configuration"))
        {
            break;
        }
        reader->readNext();
    }
    return _modeModels;
}

/**
 * @brief   获得STM32的IP内容中F1的IO模型中的表库
 *
 * @param   reader: 读XML工具
 *
 * @return  STM32的IP内容中F1的IO库模型中的表库
*/
QList<STM32Model::XmlIpF1IoModel::TableModel> STM32XmlRead::readIpF1IoTableModel(QXmlStreamReader* reader) const
{
    QList<STM32Model::XmlIpF1IoModel::TableModel> _tableModels;

    while (!reader->atEnd())
    {
        if (reader->isStartElement() && reader->name() == QString("Table"))
        {
            STM32Model::XmlIpF1IoModel::TableModel _tableModel;
            _tableModel.key = reader->attributes().value("Key").toString();
            _tableModel.value = reader->attributes().value("Value").toString();
            _tableModels << _tableModel;
        }
        else if (reader->isEndElement() && reader->name() == QString("Mode"))
        {
            break;
        }
        reader->readNext();
    }
    return _tableModels;
}

/**
 * @brief   获得STM32的IP包的位置
 *
 * @param   local: 库位置
 *          QString：亚科名
 *          McuName：mcu名
 *
 * @return  STM32的IP内容中F1的IO库模型
*/
QString STM32XmlRead::getMcuIpPath(QString local, QString ip) const
{
    QString str;
    QFile file(local);
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QXmlStreamReader reader;
        reader.setDevice(&file);
        while (!reader.atEnd())
        {
            if (reader.isStartElement() && reader.name() == QString("IP") && reader.attributes().value("Name").toString() == ip)
            {
                QString packName = reader.attributes().value("PackName").toString();
                QString packLocate = reader.attributes().value("PackLocate").toString();
                str = QCoreApplication::applicationDirPath() + packLocate + packName + ".xml";
                break;
            }
        }
    }
    else
    {
        QMessageBox::critical(nullptr, tr("Error"), tr("Cannot read file %1").arg(local));
    }
    file.close();
    return str;
}

}
