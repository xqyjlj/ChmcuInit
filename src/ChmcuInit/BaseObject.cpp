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
 ** 2021-04-08     xqyjlj       the first version        xqyjlj@126.com
 **/
#include "BaseObject.h"
#include <QCoreApplication>
#include "XmlRead.h"
#include "Debug.h"

BaseObject::BaseObject(QObject* parent) : QObject(parent)
{
    mcorePath = QCoreApplication::applicationDirPath();
}

/**
 * @brief   设置Mcu名
 *
 * @param   mcuName: mcu名
 *
 * @return  null
*/
void BaseObject::setMcuName(const QString mcuName)
{
    mmcuName = mcuName;
    setMcuPath(mcorePath + "/origin/families/chip/" + mmcuName + "/" + mmcuName + ".xml");
    setIpModels();
    setPinModels();
}

/**
 * @brief   获取Mcu名
 *
 * @param   null
 *
 * @return  Mcu名
*/
QString BaseObject::getMcuName(void) const
{
    return mmcuName;
}

/**
 * @brief   设置公司名
 *
 * @param   companyName: 公司名
 *
 * @return  null
*/
void BaseObject::setCompanyName(const QString companyName)
{
    mcompanyName = companyName;
}

/**
 * @brief   获取公司名
 *
 * @param   null
 *
 * @return  公司名
*/
QString BaseObject::getCompanyName(void) const
{
    return mcompanyName;
}

/**
 * @brief   设置主科名
 *
 * @param   familyName: 主科名
 *
 * @return  null
*/
void BaseObject::setFamilyName(const QString familyName)
{
    mfamilyName = familyName;
}

/**
 * @brief   获取主科名
 *
 * @param   null
 *
 * @return  主科名
*/
QString BaseObject::getFamilyName(void) const
{
    return mfamilyName;
}

/**
 * @brief   设置亚科名
 *
 * @param   subfamilyName: 亚科名
 *
 * @return  null
*/
void BaseObject::setSubfamilyName(const QString subfamilyName)
{
    msubfamilyName = subfamilyName;
}

/**
 * @brief   获取亚科名
 *
 * @param   null
 *
 * @return  亚科名
*/
QString BaseObject::getSubfamilyName(void) const
{
    return msubfamilyName;
}

/**
 * @brief   设置封装名
 *
 * @param   packageName: 封装名
 *
 * @return  null
*/
void BaseObject::setPackageName(const QString packageName)
{
    mpackageName = packageName;
}

/**
 * @brief   获取封装名
 *
 * @param   null
 *
 * @return  封装名
*/
QString BaseObject::getPackageName(void) const
{
    return mpackageName;
}

/**
 * @brief   获取芯片Readme文档路径
 *
 * @param   file: 文件名
 *
 * @return  芯片Readme文档路径
*/
QString BaseObject::getMcuReadMePath(QString file) const
{
    return mcorePath + "/origin/families/chip/" + file + "/readme.html";;
}

/**
 * @brief   设置芯片路径
 *
 * @param   mcuPath: 芯片路径
 *
 * @return  null
*/
void BaseObject::setMcuPath(const QString mcuPath)
{
    mmcuPath = mcuPath;
}

/**
 * @brief   获取芯片路径
 *
 * @param   null
 *
 * @return  芯片路径
*/
QString BaseObject::getMcuPath() const
{
    return mmcuPath;
}

/**
 * @brief   设置IP模型列表
 *
 * @param   ipModels: IP模型列表
 *
 * @return  null
*/
void BaseObject::setIpModels(const QList<Model::XmlIpModel> ipModels)
{
    mipModels = ipModels;
    setIpName();
}

/**
 * @brief   设置IP模型列表
 *
 * @param   null
 *
 * @return  null
*/
void BaseObject::setIpModels(void)
{
    mipModels = Xml::XmlRead().getIpModels(mmcuPath);
    setIpName();
}

/**
 * @brief   获取IP模型列表
 *
 * @param   null
 *
 * @return  IP模型列表
*/
QList<Model::XmlIpModel>* BaseObject::getIpModels() const
{
    return const_cast<QList<Model::XmlIpModel>*>(&mipModels);
}

/**
 * @brief   设置Pin模型列表
 *
 * @param   pinModels: Pin模型
 *
 * @return  null
*/
void BaseObject::setPinModels(const QList<Model::XmlPinModel> pinModels)
{
    mpinModels = pinModels;
}

/**
 * @brief   设置Pin模型列表
 *
 * @param   null
 *
 * @return  null
*/
void BaseObject::setPinModels(void)
{
    mpinModels = Xml::XmlRead().getPinModels(mmcuPath, mmcuName);
}

/**
 * @brief   获取Pin模型列表
 *
 * @param   null
 *
 * @return  Pin模型列表
*/
QList<Model::XmlPinModel>* BaseObject::getPinModels() const
{
    return const_cast<QList<Model::XmlPinModel>*>(&mpinModels);
}

/**
 * @brief   设置IP名列表
 *
 * @param   null
 *
 * @return  null
*/
void BaseObject::setIpName(void)
{
    int length = mipModels.length();

    for (int i = 0; i < length; i++)
    {
        Model::XmlIpModel* model = const_cast<Model::XmlIpModel* >(&mipModels.at(i));
        if ((!model->name.isEmpty()) && (!mipNames.contains(model->name)))
        {
            mipNames << model->name;
        }
    }
}

/**
 * @brief   获取IP名列表
 *
 * @param   null
 *
 * @return  IP名列表
*/
QStringList* BaseObject::getIpNames() const
{
    return const_cast<QStringList*>(&mipNames);
}

/**
 * @brief   获取IP包地址
 *
 * @param   ipName: IP名
 *
 * @return  IP包地址
*/
QString BaseObject::getIpPackPath(QString ipName)
{
    int length = mipModels.length();

    for (int i = 0; i < length; i++)
    {
        Model::XmlIpModel* model = const_cast<Model::XmlIpModel* >(&mipModels.at(i));

        if (model->name == ipName)
        {
            return mcorePath + model->packLocate + model->packName + ".xml";
        }
    }
    return "";
}
