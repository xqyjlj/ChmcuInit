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
 ** 2021-04-24     xqyjlj       the first version        xqyjlj@126.com
 **/

#include "FileProject.h"
#include "Debug.h"
#include "CoderHalIo.h"

FileProject::FileProject(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<XmlFileProjectModel::GpioModel_T>("XmlFileProjectModel::GpioModel_T");
}

void FileProject::slotAddGpioModel(const XmlFileProjectModel::GpioModel_T &gpioModel)
{

    if (!m_parameterNames.contains(gpioModel.name))
    {
        m_parameterNames << gpioModel.name;
        m_configurationModel.mcu.gpios << gpioModel;
    }

    emit signalAddProjectContent(u8"Pin: " + gpioModel.name);
}

void FileProject::setMcuModel(const XmlFamilyModel::McuModel_T &mcuModel)
{
    m_mcuModel = mcuModel;

    m_configurationModel.mcu.name = m_mcuModel.name;
    m_configurationModel.mcu.family = m_mcuModel.family;
}

void FileProject::saveProject(const QString &projectName, const QString &projectPath)
{
    m_configurationModel.name = projectName;
    XmlFileProjectModel::setConfigurationModel(m_configurationModel, projectPath);
}