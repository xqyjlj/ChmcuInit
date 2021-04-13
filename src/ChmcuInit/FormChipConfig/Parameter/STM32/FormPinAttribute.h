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
#ifndef FORMPINATTRIBUTE_H
#define FORMPINATTRIBUTE_H

#include <QWidget>
#include "STM32Model.h"
#include "BaseObject.h"
#include <QComboBox>
#include <QTreeWidgetItem>

namespace Ui
{
class FormPinAttribute;
}
/**
 * @brief The FormPinAttribute class
 *
 * 继承自QWidget，用于配置芯片的引脚属性
 */
class FormPinAttribute : public QWidget
{
    Q_OBJECT
public:
    explicit FormPinAttribute(QWidget* parent = nullptr);
    ~FormPinAttribute();

    /**
     * @brief   设置基础对象
     *
     * @param   baseObject: 基础对象
     *
     * @return  null
    */
    void setBaseObject(const BaseObject* baseObject);

    /**
     * @brief   加载本模块
     *
     * @param   null
     *
     * @return  null
    */
    void load(void);

    /**
     * @brief   设置标题
     *
     * @param   title: 标题
     *          attribute: 属性
     *
     * @return  null
    */
    void setTitle(const QString title, const QString attribute);

    /**
     * @brief   设置种类
     *
     * @param   type: 种类
     *
     * @return  null
    */
    void setType(const QString type);


private slots:

    /**
     * @brief   comboBox的项被改变时触发的槽函数
     *
     * @param   str: 触发之后文本
     *
     * @return  null
    */
    void attributeComboBoxCurrentTextChanged(QString str);
private:

    /**
     * @brief   添加Item
     *
     * @param   null
     *
     * @return  null
    */
    void addItem(void);
private:
    Ui::FormPinAttribute* ui;                   //ui文件
    QString mtitle;                             //标题
    QStringList mattributes;                    //属性

    QStringList mkeys;                          //键
    QStringList mvalues;                        //值

    QString mtype;                              //类型

    STM32Model::XmlIpF1IoModel mipF1IoModel;    //IO模型

    QList<QTreeWidgetItem*> mtreeWidgetItems;   //属性下拉窗口

    QList<QComboBox*> mattributeComboBoxs;      //属性下拉窗口

    BaseObject* mbaseObject = nullptr;          //基础对象
};

#endif // FORMPINATTRIBUTE_H
