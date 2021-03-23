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
#include "xml_read.h"
#include <QFile>
#include <QMessageBox>
#include <QTranslator>
#include <QXmlStreamReader>
#include "debug.h"
#include <QCoreApplication>
namespace NXml
{

CXml_read::CXml_read(QObject *parent) : QObject(parent)
{

}

/**
 * @brief   get all company name in xml file
 *
 * @param   null
 *
 * @return  QStringList with company name
*/
QStringList CXml_read::get_all_company_name()
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
 * @brief   get all company`s family name in the XML file
 *
 * @param   company: the name of the company we want to read
 *
 * @return  QStringList with family name
*/
QStringList CXml_read::get_all_family_name(QString company)
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
                list = read_family_name(&reader);
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
 * @brief   read family name in xml file
 *
 * @param   *reader: QXmlStreamReader handle
 *
 * @return  QStringList with family name
*/
QStringList CXml_read::read_family_name(QXmlStreamReader *reader)
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
 * @brief   get all family`s subfamily name in the XML file
 *
 * @param   family: the name of the family we want to read
 *
 * @return  QStringList with subfamily name
*/
QStringList CXml_read::get_all_subfamily_name(QString family)
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
                list = read_subfamily_name(&reader);
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
 * @brief   read subfamily name in xml file
 *
 * @param   *reader: QXmlStreamReader handle
 *
 * @return  QStringList with subfamily name
*/
QStringList CXml_read::read_subfamily_name(QXmlStreamReader *reader)
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
 * @brief   get all subfamily`s mcu name in the XML file
 *
 * @param   subfamily: the name of the subfamily we want to read
 *
 * @return  QStringList with mcu name
*/
QStringList CXml_read::get_all_mcu_name(QString subfamily)
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
                list = read_mcu_name(&reader);
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
 * @brief   read mcu name in xml file
 *
 * @param   *reader: QXmlStreamReader handle
 *
 * @return  QStringList with mcu name
*/
QStringList CXml_read::read_mcu_name(QXmlStreamReader *reader)
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
 * @brief   get all mcu`s info in the XML file
 *
 * @param   mcu: the name of the mcu we want to read
 *
 * @return  CMcu_model class with mcu info
*/
NModel::CMcu_model CXml_read::get_all_mcu_info(QString mcu)
{

    NModel::CMcu_model model;
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
                model = read_mcu_info(&reader);
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
 * @brief   read mcu name in xml file
 *
 * @param   *reader: QXmlStreamReader handle
 *
 * @return  CMcu_model class with mcu info
*/
NModel::CMcu_model CXml_read::read_mcu_info(QXmlStreamReader *reader)
{
    NModel::CMcu_model model;
    while (!reader->atEnd())
    {
        if (reader->isStartElement() && reader->name() == QString("Mcu"))
        {
            model.name = reader->attributes().value("Name").toString();
            model.packagename = reader->attributes().value("PackageName").toString();
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
            NModel::CMcu_peripheral_model peripheral_model;
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
}

