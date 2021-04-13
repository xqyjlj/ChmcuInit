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
 ** 2021-04-04     xqyjlj       the first version        xqyjlj@126.com
 **/
#ifndef STM32XMLREAD_H
#define STM32XMLREAD_H

#include <QObject>
#include <QXmlStreamReader>
#include "STM32Model.h"

namespace STM32Xml
{
/**
 * @brief The STM32XmlRead class
 *
 * 提供STM32XML文件读函数
 */
class STM32XmlRead : public QObject
{
    Q_OBJECT
public:
    explicit STM32XmlRead(QObject* parent = nullptr);

    /**
     * @brief   获得STM32的IP内容中F1的IO模型
     *
     * @param   local: 库位置
     *          QString：亚科名
     *          McuName：mcu名
     *
     * @return  STM32的IP内容中F1的IO库模型
    */
    STM32Model::XmlIpF1IoModel getIpF1IoModel(QString local, QString subfamily, QString mcuName) const;

    /**
     * @brief   获得STM32的IP包的位置
     *
     * @param   local: 库位置
     *          ip: IP名
     *
     * @return  IP包的位置
    */
    QString getMcuIpPath(QString local, QString ip) const;
signals:

private:

    /**
     * @brief   获得STM32的IP内容中F1的IO模型中的模式库
     *
     * @param   reader: 读XML工具
     *
     * @return  STM32的IP内容中F1的IO库模型中的模式库
    */
    QList<STM32Model::XmlIpF1IoModel::ModeModel> readIpF1IoModeModel(QXmlStreamReader* reader) const;

    /**
     * @brief   获得STM32的IP内容中F1的IO模型中的表库
     *
     * @param   reader: 读XML工具
     *
     * @return  STM32的IP内容中F1的IO库模型中的表库
    */
    QList<STM32Model::XmlIpF1IoModel::TableModel> readIpF1IoTableModel(QXmlStreamReader* reader) const;
};
}


#endif // STM32XMLREAD_H
