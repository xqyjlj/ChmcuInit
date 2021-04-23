/**
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
 ** 2021-04-20     xqyjlj       the first version        xqyjlj@126.com
 **/

#include "XmlFamilyModel.h"
#include <QCoreApplication>
#include <QFile>
#include "Debug.h"

XmlFamilyModel::XmlFamilyModel(QObject *parent) : QObject(parent)
{
    m_corePath = QCoreApplication::applicationDirPath();
}

QList<XmlFamilyModel::McuModel_T> XmlFamilyModel::getMcuModels() const
{
    QList<XmlFamilyModel::McuModel_T> list;
    QString path = m_corePath + u8"/origin/families/chip/families.xml";
    QFile file(path);
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QXmlStreamReader reader;
        reader.setDevice(&file);
        while (!reader.atEnd())
        {
            if (reader.isStartElement() && reader.name() == QString(u8"Mcu"))
            {
                list << readMcuModel(&reader);
            }
            reader.readNext();
        }
    } else
    {
        ASSERT_X(false, u8"XmlFamilyModel", QString(u8"Cannot read file %1").arg(path));
    }
    file.close();
    return list;
}

XmlFamilyModel::McuModel_T XmlFamilyModel::readMcuModel(QXmlStreamReader *reader)
{
    XmlFamilyModel::McuModel_T model;
    while (!reader->atEnd())
    {
        if (reader->isStartElement() && reader->name() == QString(u8"Mcu"))
        {
            model.name = reader->attributes().value(u8"Name").toString();
            model.package = reader->attributes().value(u8"PackageName").toString();
            model.company = reader->attributes().value(u8"CompanyName").toString();
            model.family = reader->attributes().value(u8"FamilyName").toString();
            model.subfamily = reader->attributes().value(u8"SubFamilyName").toString();
        } else if (reader->isStartElement() && reader->name() == QString(u8"Core"))
        {
            model.core = reader->readElementText();
        } else if (reader->isStartElement() && reader->name() == QString(u8"Frequency"))
        {
            model.frequency = reader->readElementText();
        } else if (reader->isStartElement() && reader->name() == QString(u8"Ram"))
        {
            model.ram = reader->readElementText();
        } else if (reader->isStartElement() && reader->name() == QString(u8"IO"))
        {
            model.io = reader->readElementText();
        } else if (reader->isStartElement() && reader->name() == QString(u8"Flash"))
        {
            model.flash = reader->readElementText();
        } else if (reader->isStartElement() && reader->name() == QString(u8"Voltage"))
        {
            model.voltage.min = reader->attributes().value(u8"Min").toString();
            model.voltage.max = reader->attributes().value(u8"Max").toString();
        } else if (reader->isStartElement() && reader->name() == QString(u8"Current"))
        {
            model.current.lowest = reader->attributes().value(u8"Lowest").toString();
            model.current.run = reader->attributes().value(u8"Run").toString();
        } else if (reader->isStartElement() && reader->name() == QString(u8"Temperature"))
        {
            model.temperature.min = reader->attributes().value(u8"Min").toString();
            model.temperature.max = reader->attributes().value(u8"Max").toString();
        } else if (reader->isStartElement() && reader->name() == QString(u8"Peripheral"))
        {
            PeripheralModel_T peripheral_model;
            peripheral_model.type = reader->attributes().value(u8"Type").toString();
            model.peripheral << peripheral_model;
        } else if (reader->isEndElement() && reader->name() == QString(u8"Mcu"))
        {
            break;
        }
        reader->readNext();
    }
    return model;
}

XmlFamilyModel::McuModel_T XmlFamilyModel::getMcuModel(const QString &mcuName) const
{
    XmlFamilyModel::McuModel_T model;
    QString path = m_corePath + u8"/origin/families/chip/families.xml";
    QFile file(path);
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QXmlStreamReader reader;
        reader.setDevice(&file);
        while (!reader.atEnd())
        {
            if (reader.isStartElement() && reader.name() == QString(u8"Mcu") &&
                reader.attributes().value(u8"Name").toString() == mcuName)
            {
                model = readMcuModel(&reader);
                break;
            }
            reader.readNext();
        }
    } else
    {
        ASSERT_X(false, u8"XmlFamilyModel", QString(u8"Cannot read file %1").arg(path));
    }
    file.close();
    return model;
}
