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
 ** 2021-03-19     xqyjlj       the first version        xqyjlj@126.com
 **/
#include "XmlRead.h"
#include <QFile>
#include <QMessageBox>
#include <QTranslator>
#include <QXmlStreamReader>
#include "Debug.h"
#include <QCoreApplication>
namespace Xml
{

XmlRead::XmlRead(QObject* parent) : QObject(parent)
{

}

/**
 * @brief   获得公司名
 *
 * @param   null
 *
 * @return  公司名
*/
QStringList XmlRead::getCompanyName() const
{
    QStringList list;
    QString str_families_xml = QCoreApplication::applicationDirPath() + "/origin/families/chip/families.xml";
    QFile file(str_families_xml);
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QXmlStreamReader reader;
        reader.setDevice(&file);
        while (!reader.atEnd())
        {
            if (reader.isStartElement())
            {
                if (reader.name() == tr("Company"))
                {
                    list << reader.attributes().value("Name").toString();
                }
            }
            reader.readNext();
        }
    }
    else
    {
        QMessageBox::critical(nullptr, tr("Error"), tr("Cannot read file %1").arg(str_families_xml));
    }
    file.close();
    return list;
}

/**
 * @brief   获得主科名
 *
 * @param   公司名
 *
 * @return  主科名
*/
QStringList XmlRead::getFamilyName(QString company) const
{
    QStringList list;
    QString str_families_xml = QCoreApplication::applicationDirPath() + "/origin/families/chip/families.xml";
    QFile file(str_families_xml);
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QXmlStreamReader reader;
        reader.setDevice(&file);
        while (!reader.atEnd())
        {
            if (reader.isStartElement() && reader.name() == QString("Company") && reader.attributes().value("Name").toString() == company)
            {
                list = readFamilyName(&reader);
                break;
            }
            reader.readNext();
        }
    }
    else
    {
        QMessageBox::critical(nullptr, tr("Error"), tr("Cannot read file %1").arg(str_families_xml));
    }
    file.close();
    return list;
}

/**
 * @brief   读主科名
 *
 * @param   reader: 读XML工具
 *
 * @return  主科名
*/
QStringList XmlRead::readFamilyName(QXmlStreamReader* reader) const
{
    QStringList list;
    while (!reader->atEnd())
    {
        reader->readNext();
        if (reader->isStartElement() && reader->name() == QString("Family"))
        {
            list << reader->attributes().value("Name").toString();
        }
        else if (reader->isEndElement() && reader->name() == QString("Family"))
        {
            break;
        }
    }
    return list;
}

/**
 * @brief   获得亚科名
 *
 * @param   主科名
 *
 * @return  亚科名
*/
QStringList XmlRead::getSubfamilyName(QString family) const
{
    QStringList list;
    QString str_families_xml = QCoreApplication::applicationDirPath() + "/origin/families/chip/families.xml";
    QFile file(str_families_xml);
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QXmlStreamReader reader;
        reader.setDevice(&file);
        while (!reader.atEnd())
        {
            if (reader.isStartElement() && reader.name() == QString("Family") && reader.attributes().value("Name").toString() == family)
            {
                list = readSubfamilyName(&reader);
                break;
            }
            reader.readNext();
        }
    }
    else
    {
        QMessageBox::critical(nullptr, tr("Error"), tr("Cannot read file %1").arg(str_families_xml));
    }
    file.close();
    return list;
}

/**
 * @brief   读亚科名
 *
 * @param   reader: 读XML工具
 *
 * @return  亚科名
*/
QStringList XmlRead::readSubfamilyName(QXmlStreamReader* reader) const
{
    QStringList list;
    while (!reader->atEnd())
    {
        reader->readNext();
        if (reader->isStartElement() && reader->name() == QString("SubFamily"))
        {
            list << reader->attributes().value("Name").toString();
        }
        else if (reader->isEndElement() && reader->name() == QString("SubFamily"))
        {
            break;
        }
    }
    return list;
}

/**
 * @brief   获得MCU名
 *
 * @param   亚科名
 *
 * @return  MCU名
*/
QStringList XmlRead::getMcuName(QString subfamily) const
{
    QStringList list;
    QString str_families_xml = QCoreApplication::applicationDirPath() + "/origin/families/chip/families.xml";
    QFile file(str_families_xml);
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QXmlStreamReader reader;
        reader.setDevice(&file);
        while (!reader.atEnd())
        {
            if (reader.isStartElement() && reader.name() == QString("SubFamily") && reader.attributes().value("Name").toString() == subfamily)
            {
                list = readMcuName(&reader);
                break;
            }
            reader.readNext();
        }
    }
    else
    {
        QMessageBox::critical(nullptr, tr("Error"), tr("Cannot read file %1").arg(str_families_xml));
    }
    file.close();
    return list;
}

/**
 * @brief   读MCU名
 *
 * @param   reader: 读XML工具
 *
 * @return  MCU名
*/
QStringList XmlRead::readMcuName(QXmlStreamReader* reader) const
{
    QStringList list;
    while (!reader->atEnd())
    {
        reader->readNext();
        if (reader->isStartElement() && reader->name() == QString("Mcu"))
        {
            list << reader->attributes().value("Name").toString();
        }
        else if (reader->isEndElement() && reader->name() == QString("SubFamily"))
        {
            break;
        }
    }
    return list;
}

/**
 * @brief   获得MCU信息
 *
 * @param   MCU名
 *
 * @return  MCU信息
*/
Model::XmlFamilyChipModel XmlRead::getMcuInfo(QString mcu) const
{
    Model::XmlFamilyChipModel model;
    QString str_families_xml = QCoreApplication::applicationDirPath() + "/origin/families/chip/families.xml";
    QFile file(str_families_xml);
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QXmlStreamReader reader;
        reader.setDevice(&file);
        while (!reader.atEnd())
        {
            if (reader.isStartElement() && reader.name() == QString("Mcu") && reader.attributes().value("Name").toString() == mcu)
            {
                model = readMcuInfo(&reader);
                break;
            }
            reader.readNext();
        }
    }
    else
    {
        QMessageBox::critical(nullptr, tr("Error"), tr("Cannot read file %1").arg(str_families_xml));
    }
    file.close();
    return model;
}

/**
 * @brief   读MCU信息
 *
 * @param   reader: 读XML工具
 *
 * @return  MCU信息
*/
Model::XmlFamilyChipModel XmlRead::readMcuInfo(QXmlStreamReader* reader) const
{
    Model::XmlFamilyChipModel model;
    while (!reader->atEnd())
    {
        if (reader->isStartElement() && reader->name() == QString("Mcu"))
        {
            model.name = reader->attributes().value("Name").toString();
            model.package = reader->attributes().value("PackageName").toString();
            model.company = reader->attributes().value("CompanyName").toString();
            model.family = reader->attributes().value("FamilyName").toString();
            model.subfamily = reader->attributes().value("SubFamilyName").toString();
        }
        else if (reader->isStartElement() && reader->name() == QString("Core"))
        {
            model.core = reader->readElementText();
        }
        else if (reader->isStartElement() && reader->name() == QString("Frequency"))
        {
            model.frequency = reader->readElementText();
        }
        else if (reader->isStartElement() && reader->name() == QString("Ram"))
        {
            model.ram = reader->readElementText();
        }
        else if (reader->isStartElement() && reader->name() == QString("IO"))
        {
            model.io = reader->readElementText();
        }
        else if (reader->isStartElement() && reader->name() == QString("Flash"))
        {
            model.flash = reader->readElementText();
        }
        else if (reader->isStartElement() && reader->name() == QString("Voltage"))
        {
            model.voltage.min = reader->attributes().value("Min").toString();
            model.voltage.max = reader->attributes().value("Max").toString();
        }
        else if (reader->isStartElement() && reader->name() == QString("Current"))
        {
            model.current.lowest = reader->attributes().value("Lowest").toString();
            model.current.run = reader->attributes().value("Run").toString();
        }
        else if (reader->isStartElement() && reader->name() == QString("Temperature"))
        {
            model.temperature.min = reader->attributes().value("Min").toString();
            model.temperature.max = reader->attributes().value("Max").toString();
        }
        else if (reader->isStartElement() && reader->name() == QString("Peripheral"))
        {
            Model::XmlFamilyChipModel::XmlPeripheralModel peripheral_model;
            peripheral_model.type = reader->attributes().value("Type").toString();
            model.peripheral << peripheral_model;
        }
        else if (reader->isEndElement() && reader->name() == QString("Mcu"))
        {
            break;
        }
        reader->readNext();
    }
    return model;
}

/**
 * @brief   获得Pin模型列表
 *
 * @param   mcuPath: MCU路径
 *          mcuName: MCU名
 *
 * @return  Pin模型列表
*/
QList<Model::XmlPinModel> XmlRead::getPinModels(QString mcuPath, QString mcuName) const
{
    QList<Model::XmlPinModel> list;
    int pins = 0;
    QFile file(mcuPath);
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QXmlStreamReader reader;
        reader.setDevice(&file);
        while (!reader.atEnd())
        {
            if (reader.isStartElement() && reader.name() == QString("Mcu") && reader.attributes().value("Name").toString() == mcuName)
            {
                pins = reader.attributes().value("PinNum").toInt();
                list = readPinInfo(&reader);
                if (list.length() != pins)
                {
                    list.clear();
                }
                break;
            }
            reader.readNext();
        }
    }
    else
    {
        QMessageBox::critical(nullptr, tr("Error"), tr("Cannot read file %1").arg(mcuPath));
    }
    file.close();
    return list;
}

/**
 * @brief   读引脚信息
 *
 * @param   reader: 读XML工具
 *
 * @return  引脚信息
*/
QList<Model::XmlPinModel> XmlRead::readPinInfo(QXmlStreamReader* reader) const
{
    QList<Model::XmlPinModel> list;
    while (!reader->atEnd())
    {
        reader->readNext();
        if (reader->isStartElement() && reader->name() == QString("Pin"))
        {
            Model::XmlPinModel pin_model;
            pin_model.name = reader->attributes().value("Name").toString();
            pin_model.position = reader->attributes().value("Position").toString();
            pin_model.type = reader->attributes().value("Type").toString();

            while (!reader->atEnd())
            {
                if (reader->isEndElement() && reader->name() == QString("Pin"))
                {
                    break;
                }
                else if (reader->isStartElement() && reader->name() == QString("Signal"))
                {
                    Model::XmlPinModel::SignalModel pin_signal_model;
                    pin_signal_model.name = reader->attributes().value("Name").toString();
                    pin_signal_model.ioModes = reader->attributes().value("IOModes").toString();
                    pin_model.signal << pin_signal_model;
                }
                reader->readNext();
            }
            list << pin_model;
        }
    }
    return list;
}

/**
 * @brief   获得IP信息列表
 *
 * @param   mcu_path: MCU路径
 *
 * @return  IP信息列表
*/
QList<Model::XmlIpModel> XmlRead::getIpModels(QString mcuPath) const
{
    QList<Model::XmlIpModel> list;
    QFile file(mcuPath);
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QXmlStreamReader reader;
        reader.setDevice(&file);
        while (!reader.atEnd())
        {
            if (reader.isStartElement() && reader.name() == QString("IP"))
            {
                Model::XmlIpModel ip_model;
                ip_model.instanceName = reader.attributes().value("InstanceName").toString();
                ip_model.name = reader.attributes().value("Name").toString();
                ip_model.packName = reader.attributes().value("PackName").toString();
                ip_model.version = reader.attributes().value("Version").toString();
                ip_model.packLocate = reader.attributes().value("PackLocate").toString();
                list << ip_model;
            }
            reader.readNext();
        }
    }
    else
    {
        QMessageBox::critical(nullptr, tr("Error"), tr("Cannot read file %1").arg(mcuPath));
    }
    file.close();
    return list;
}

}

