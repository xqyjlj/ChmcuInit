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
 ** 2021-04-29     xqyjlj       the first version        xqyjlj@126.com
 **/

#include "XmlFileProjectModel.h"
#include <QFile>
#include "Debug.h"

XmlFileProjectModel::XmlFileProjectModel(QObject *parent) : QObject(parent)
{

}

void XmlFileProjectModel::setConfigurationModel(const ConfigurationModel_T &configurationModel, const QString &path)
{
    QFile file(path);
    if (file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate))
    {
        QXmlStreamWriter writer(&file);

        writer.setAutoFormatting(true);
        writer.writeStartDocument("1.0", true);

        writer.writeComment(u8"此文件为ChmcuInit软件配置文件，软件地址：https://github.com/xqyjlj/ChmcuInit");

        writer.writeStartElement(u8"Configuration");
        writer.writeAttribute(u8"Name", configurationModel.name);

        setMcuModel(&writer, configurationModel.mcu);

        writer.writeEndElement();

        writer.writeEndDocument();
    }
    else
    {
        ASSERT_X(false, u8"XmlFileProjectModel", QString(u8"Cannot write file %1").arg(path));
        return;
    }

    file.close();
}

void XmlFileProjectModel::setMcuModel(QXmlStreamWriter *writer, const McuModel_T &mcuModel)
{
    writer->writeStartElement(u8"Mcu");
    writer->writeAttribute(u8"Name", mcuModel.name);
    writer->writeAttribute(u8"Family", mcuModel.family);

    setGpioModel(writer, mcuModel.gpios);

    writer->writeEndElement();
}

void XmlFileProjectModel::setGpioModel(QXmlStreamWriter *writer, const QList<GpioModel_T> &gpioModels)
{
    if (!gpioModels.isEmpty())
    {
        writer->writeStartElement(u8"IP");

        writer->writeAttribute(u8"Name", u8"GPIO");

        for (const GpioModel_T &gpioModel: gpioModels)
        {
            writer->writeStartElement(u8"GPIO");

            writer->writeAttribute(u8"Name", gpioModel.name);
            writer->writeAttribute(u8"Level", gpioModel.level);
            writer->writeAttribute(u8"Speed", gpioModel.speed);
            writer->writeAttribute(u8"Pull", gpioModel.pull);
            writer->writeAttribute(u8"Pin", gpioModel.pin);
            writer->writeAttribute(u8"Mode", gpioModel.mode);
            writer->writeAttribute(u8"Label", gpioModel.label);
            writer->writeAttribute(u8"Port", gpioModel.port);

            writer->writeEndElement();
        }

        writer->writeEndElement();
    }
}

XmlFileProjectModel::ConfigurationModel_T XmlFileProjectModel::getConfigurationModel(const QString &path)
{
    ConfigurationModel_T configurationModel;
    QFile file(path);
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QXmlStreamReader reader;
        reader.setDevice(&file);
        while (!reader.atEnd())
        {
            if (reader.isStartElement() && reader.name() == QString(u8"Configuration"))
            {
                configurationModel.name = reader.attributes().value(u8"Name").toString();
                configurationModel.mcu = getMcuModel(&reader);
            }
            reader.readNext();
        }
    }
    else
    {
        ASSERT_X(false, u8"XmlFileProjectModel", QString(u8"Cannot read file %1").arg(path));
    }

    return configurationModel;
}

XmlFileProjectModel::McuModel_T XmlFileProjectModel::getMcuModel(QXmlStreamReader *reader)
{
    McuModel_T mcuModel;
    while (!reader->atEnd())
    {
        if (reader->isStartElement() && reader->name() == QString(u8"Mcu"))
        {
            mcuModel.name = reader->attributes().value(u8"Name").toString();
            mcuModel.family = reader->attributes().value(u8"Family").toString();
        }
        else if (reader->isStartElement() && reader->name() == QString(u8"IP"))
        {
            if (reader->attributes().value(u8"Name").toString() == u8"GPIO")
            {
                mcuModel.gpios = getGpioModels(reader);
            }
        }
        else if (reader->isEndElement() && reader->name() == QString(u8"Mcu"))
        {
            break;
        }
        reader->readNext();
    }
    return mcuModel;
}

QList<XmlFileProjectModel::GpioModel_T> XmlFileProjectModel::getGpioModels(QXmlStreamReader *reader)
{
    QList<XmlFileProjectModel::GpioModel_T> gpioModels;

    while (!reader->atEnd())
    {
        if (reader->isStartElement() && reader->name() == QString(u8"GPIO"))
        {
            XmlFileProjectModel::GpioModel_T gpioModel;
            gpioModel.name = reader->attributes().value(u8"Name").toString();
            gpioModel.port = reader->attributes().value(u8"Port").toString();
            gpioModel.label = reader->attributes().value(u8"Label").toString();
            gpioModel.pin = reader->attributes().value(u8"Pin").toString();
            gpioModel.mode = reader->attributes().value(u8"Mode").toString();
            gpioModel.speed = reader->attributes().value(u8"Speed").toString();
            gpioModel.pull = reader->attributes().value(u8"Pull").toString();
            gpioModel.level = reader->attributes().value(u8"Level").toString();
            gpioModels << gpioModel;
        }
        else if (reader->isEndElement() && reader->name() == QString(u8"IP"))
        {
            break;
        }
        reader->readNext();
    }

    return gpioModels;
}


