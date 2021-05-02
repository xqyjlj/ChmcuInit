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
 ** 2021-04-21     xqyjlj       the first version        xqyjlj@126.com
 **/

#include "XmlPinModel.h"
#include "Debug.h"
#include <QFile>

XmlPinModel::XmlPinModel(QObject *parent) : QObject(parent)
{}

QList<XmlPinModel::PinModel_T> XmlPinModel::getPinModels(const QString &mcuPath, const QString &mcuName)
{
    QList<PinModel_T> list;
    int pins;
    QFile file(mcuPath);
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QXmlStreamReader reader;
        reader.setDevice(&file);
        while (!reader.atEnd())
        {
            if (reader.isStartElement() && reader.name() == QString("Mcu") &&
                reader.attributes().value("Name").toString() == mcuName)
            {
                pins = reader.attributes().value("PinNum").toInt();
                list = readPinModels(&reader);
                if (pins != list.length())
                {
                    list.clear();
                }
                break;
            }
            reader.readNext();
        }
    } else
    {
        ASSERT_X(false, "XmlPinModel", QString("Cannot read file %1").arg(mcuPath));
    }
    file.close();
    return list;
}

QList<XmlPinModel::PinModel_T> XmlPinModel::readPinModels(QXmlStreamReader *reader)
{
    QList<PinModel_T> list;
    while (!reader->atEnd())
    {
        reader->readNext();
        if (reader->isStartElement() && reader->name() == QString("Pin"))
        {
            PinModel_T pinModel;
            pinModel.name = reader->attributes().value("Name").toString();
            pinModel.position = reader->attributes().value("Position").toString();
            pinModel.type = reader->attributes().value("Type").toString();

            while (!reader->atEnd())
            {
                if (reader->isEndElement() && reader->name() == QString("Pin"))
                {
                    break;
                } else if (reader->isStartElement() && reader->name() == QString("Signal"))
                {
                    SignalModel_T pinSignalModel;
                    pinSignalModel.name = reader->attributes().value("Name").toString();
                    QString ioModes = reader->attributes().value("IOModes").toString();
                    if (!ioModes.isEmpty())
                    {
                        pinSignalModel.ioModes = ioModes.split(u8",");
                    }
                    pinModel.signal << pinSignalModel;
                }
                reader->readNext();
            }
            list << pinModel;
        }
    }
    return list;
}
