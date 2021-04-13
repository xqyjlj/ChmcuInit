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
 ** 分发此程序是希望它会有用，但没有任何保证: 甚至没有默示的保证特定目的的适销性或适用性。有关更多详细信息，请参见GNU通用公共许可证。
 **
 ** 您应该已经与这个程序一起收到GNU通用公共许可证的副本。如果不是，请参见<http://www.gnu.org/licenses/>。
 **
 ** Change Logs:
 ** Date           Author       Notes                    Email
 ** 2021-03-20     xqyjlj       the first version        xqyjlj@126.com
 **/
#ifndef XMLREAD_H
#define XMLREAD_H

#include <QObject>
#include <QStringList>
#include <QXmlStreamReader>
#include "Model.h"

namespace Xml
{

/**
 * @brief The TreeWidgetChooseIp class
 *
 * 提供xml读接口
 */
class XmlRead : public QObject
{
    Q_OBJECT
public:
    explicit XmlRead(QObject* parent = nullptr);

    /**
     * @brief   获得公司名
     *
     * @param   null
     *
     * @return  公司名
    */
    QStringList getCompanyName() const;

    /**
     * @brief   获得主科名
     *
     * @param   公司名
     *
     * @return  主科名
    */
    QStringList getFamilyName(QString company) const;

    /**
     * @brief   获得亚科名
     *
     * @param   主科名
     *
     * @return  亚科名
    */
    QStringList getSubfamilyName(QString family) const;

    /**
     * @brief   获得MCU名
     *
     * @param   亚科名
     *
     * @return  MCU名
    */
    QStringList getMcuName(QString subfamily) const;

    /**
     * @brief   获得MCU信息
     *
     * @param   MCU名
     *
     * @return  MCU信息
    */
    Model::XmlFamilyChipModel getMcuInfo(QString mcu) const;

    /**
     * @brief   获得Pin模型列表
     *
     * @param   mcuPath: MCU路径
     *          mcuName: MCU名
     *
     * @return  Pin模型列表
    */
    QList<Model::XmlPinModel> getPinModels(QString mcuPath, QString mcuName) const;

    /**
     * @brief   获得IP信息列表
     *
     * @param   mcu_path: MCU路径
     *
     * @return  IP信息列表
    */
    QList<Model::XmlIpModel> getIpModels(QString mcuPath) const;
signals:

private:

    /**
     * @brief   读主科名
     *
     * @param   reader: 读XML工具
     *
     * @return  主科名
    */
    QStringList readFamilyName(QXmlStreamReader* reader) const;

    /**
     * @brief   读亚科名
     *
     * @param   reader: 读XML工具
     *
     * @return  亚科名
    */
    QStringList readSubfamilyName(QXmlStreamReader* reader) const;

    /**
     * @brief   读MCU名
     *
     * @param   reader: 读XML工具
     *
     * @return  MCU名
    */
    QStringList readMcuName(QXmlStreamReader* reader) const;

    /**
     * @brief   读MCU信息
     *
     * @param   reader: 读XML工具
     *
     * @return  MCU信息
    */
    Model::XmlFamilyChipModel readMcuInfo(QXmlStreamReader* reader) const;

    /**
     * @brief   读引脚信息
     *
     * @param   reader: 读XML工具
     *
     * @return  引脚信息
    */
    QList<Model::XmlPinModel> readPinInfo(QXmlStreamReader* reader) const;
};

}

#endif // XMLREAD_H
