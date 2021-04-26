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

#include <QCoreApplication>
#include "BaseObject.h"

BaseObject::BaseObject(QObject *parent) : QObject(parent)
{
    setObjectName(u8"BaseObject");

    m_corePath = QCoreApplication::applicationDirPath();

    m_xmlFamilyModel = new XmlFamilyModel(this);
    m_xmlPinModel = new XmlPinModel(this);
    m_xmlIpModel = new XmlIpModel(this);
    m_xmlIoModel = new XmlIoModel(this);

    m_fileProject = new FileProject(this);

    m_mcuModels = m_xmlFamilyModel->getMcuModels();
}

QString BaseObject::getMcuReadMePath(const QString &fileName) const
{
    return m_corePath + u8"/origin/families/chip/" + fileName + u8"/readme.html";
}

const QString &BaseObject::getCorePath() const
{
    return m_corePath;
}

void BaseObject::setCorePath(const QString &corePath)
{
    m_corePath = corePath;
}

QString BaseObject::getMcuPackPath(const QString &fileName) const
{
    return m_corePath + u8"/origin/families/chip/" + fileName;
}

const XmlFamilyModel::McuModel_T &BaseObject::getMcuModel() const
{
    return m_mcuModel;
}

void BaseObject::setMcuModel(const XmlFamilyModel::McuModel_T &mcuModel)
{
    m_mcuModel = mcuModel;
    setPinModels();
    setIpModels();
    m_fileProject->setMcuModel(m_mcuModel);
}

const QList<XmlPinModel::PinModel_T> &BaseObject::getPinModels() const
{
    return m_pinModels;
}

void BaseObject::setPinModels(const QList<XmlPinModel::PinModel_T> &pinModels)
{
    m_pinModels = pinModels;
}

void BaseObject::configProject()
{
    emit signalConfigProject();
}

QString BaseObject::getMcuPackPath() const
{
    return m_corePath + u8"/origin/families/chip/" + m_mcuModel.name;
}

void BaseObject::setMcuModels(const QList<XmlFamilyModel::McuModel_T> &mcuModels)
{
    m_mcuModels = mcuModels;
}

const QList<XmlFamilyModel::McuModel_T> &BaseObject::getMcuModels() const
{
    return m_mcuModels;
}

void BaseObject::setMcuModel(const QString &mcuName)
{
    m_mcuModel = m_xmlFamilyModel->getMcuModel(mcuName);
    setPinModels();
    setIpModels();
    m_fileProject->setMcuModel(m_mcuModel);
}

void BaseObject::setPinModels()
{
    m_pinModels = m_xmlPinModel->getPinModels(getMcuPath(m_mcuModel.name), m_mcuModel.name);
}

QString BaseObject::getMcuPath(const QString &file) const
{
    return m_corePath + u8"/origin/families/chip/" + file + u8"/" + file + u8".xml";
}

void BaseObject::setIpModels()
{
    m_ipModels =m_xmlIpModel->getIpModels(getMcuPath(m_mcuModel.name));
    foreach (XmlIpModel::IpModel_T ipModel, m_ipModels)
    {
        if (!m_ipNames.contains(ipModel.name))
        {
            m_ipNames << ipModel.name;
            QString path = m_corePath + ipModel.packPath + ipModel.packName + ".xml";
            if (ipModel.name == "IO")
            {
                setIoModel(path);
            }
        }
    }
}

const XmlIoModel::IoModel_T &BaseObject::getIoModel() const
{
    return m_ioModel;
}

const QMultiMap<QString, QString> & BaseObject::getMapIoTables() const
{
    return m_mapIoTables;
}

void BaseObject::setMapIoTables()
{
    foreach(XmlIoModel::ParameterModel_T parameterModel, m_ioModel.parameters)
    {
        foreach (XmlIoModel::TableModel_T tableModel, parameterModel.tables)
        {
            m_mapIoTables.insert(tableModel.key, tableModel.value);
            m_mapIoTables.insert(tableModel.key, tableModel.tag);
        }
    }
}

void BaseObject::setIoModel(QString &path)
{
    m_ioModel = m_xmlIoModel->getIoModel(path, m_mcuModel.subfamily, m_mcuModel.name);
    setMapIoTables();
}

FileProject *BaseObject::getFileProject() const
{
    return m_fileProject;
}

void BaseObject::saveProject()
{
    m_fileProject->saveFile();
}

