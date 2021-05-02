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
 ** 2021-04-22     xqyjlj       the first version        xqyjlj@126.com
 **/

#include "XmlIoModel.h"
#include "Debug.h"
#include <QFile>

XmlIoModel::XmlIoModel(QObject *parent) : QObject(parent)
{

}

XmlIoModel::IoModel_T XmlIoModel::getIoModel(const QString &path, const QString &subfamily, const QString &mcuName)
{
    XmlIoModel::IoModel_T model;
    model.mcuName = mcuName;
    model.subfamilyName = subfamily;
    QFile file(path);
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
                        model.parameters = readModeModels(&reader);
                        return model;
                    }
                    reader.readNext();
                }
            }
            reader.readNext();
        }
    }
    else
    {
        ASSERT_X(false, "XmlIoModel", QString("Cannot read file %1").arg(path));
    }
    file.close();
    return model;
}

QList<XmlIoModel::ParameterModel_T> XmlIoModel::readModeModels(QXmlStreamReader *reader)
{
    QList<XmlIoModel::ParameterModel_T> modeModels;
    while (!reader->atEnd())
    {
        if (reader->isStartElement() && reader->name() == QString("Parameter"))
        {
            XmlIoModel::ParameterModel_T mode_model;
            mode_model.name = reader->attributes().value("Name").toString();
            mode_model.chineseName = reader->attributes().value("ChineseName").toString();
            mode_model.widget = reader->attributes().value("Widget").toString();
            mode_model.tables = readTableModels(reader);
            modeModels << mode_model;
        }
        else if (reader->isEndElement() && reader->name() == QString("Configuration"))
        {
            break;
        }
        reader->readNext();
    }
    return modeModels;
}

QList<XmlIoModel::TableModel_T> XmlIoModel::readTableModels(QXmlStreamReader *reader)
{
    QList<XmlIoModel::TableModel_T> tableModels;

    while (!reader->atEnd())
    {
        if (reader->isStartElement() && reader->name() == QString("Table"))
        {
            XmlIoModel::TableModel_T table_model;
            table_model.key = reader->attributes().value("Key").toString();
            table_model.value = reader->attributes().value("Value").toString();
            table_model.tag = reader->attributes().value("Tag").toString();
            tableModels << table_model;
        }
        else if (reader->isEndElement() && reader->name() == QString("Parameter"))
        {
            break;
        }
        reader->readNext();
    }
    return tableModels;
}

QMap<QString, XmlIoModel::TableModel_T> XmlIoModel::getTableModelMap(const QList<ParameterModel_T> &parameterModels)
{
    QMap<QString, TableModel_T> tableModelMap;
    for (const XmlIoModel::ParameterModel_T &parameterModel: parameterModels)
    {
        for (const XmlIoModel::TableModel_T &tableModel: parameterModel.tables)
        {
            tableModelMap.insert(tableModel.key, tableModel);
        }
    }
    return tableModelMap;
}
