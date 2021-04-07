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
 ** 2021-04-03     xqyjlj       the first version        xqyjlj@126.com
 **/
#ifndef TREEWIDGETCHOOSEFUNCTION_H
#define TREEWIDGETCHOOSEFUNCTION_H

#include <QTreeWidget>
#include "Model.h"
#include "FormPinAttribute.h"
#include <QVector>
#include <QComboBox>

/**
 * @brief The TreeWidgetChooseFunction class
 *
 * 树形功能选择界面
 */
class TreeWidgetChooseFunction : public QTreeWidget
{
    Q_OBJECT
public:
    explicit TreeWidgetChooseFunction(QWidget* parent = nullptr);

    /**
     * @brief   设置引脚模型
     *
     * @param   model: 引脚模型
     *
     * @return  null
    */
    void setPinModel(QList<Model::XmlPinModel> list);
signals:

    /**
     * @brief   pin子节点被点击信号
     *
     * @param   bools: 装有所有引脚被选中的bool状态
     *
     * @return  null
    */
    void pinClicked(QVector<bool> bools);

    /**
     * @brief   设置引脚属性配置界面信号
     *
     * @param   widget: FormPinAttribute对象
     *
     * @return  null
    */
    void pinAttributeOpened(FormPinAttribute* widget);
public slots:

    /**
     * @brief   选择引脚
     *
     * @param   bools: 装有所有引脚被选中的bool状态
     *
     * @return  null
    */
    void selectPin(QVector<bool> bools);
private slots:

    /**
     * @brief   TreeWidgetChooseFunction(自己)的Item选中状态被改变而触发的槽函数
     *
     * @param   null
     *
     * @return  null
    */
    void TreeWidgetChooseFunctionItemSelectionChanged(void);

    /**
     * @brief   comboBox的项被改变时触发的槽函数
     *
     * @param   str: 触发之后文本
     *
     * @return  null
    */
    void comboBoxCurrentTextChanged(QString str);
private:
    QList<QTreeWidgetItem*> selectItems;                //被选中的QTreeWidgetItem集合
    QList<QTreeWidgetItem*> mpinItems;                  //引脚列表
    QList<QComboBox*> mpinComboBox;                     //引脚对应的复选框
    QVector<FormPinAttribute*> mformPinAttributes;      //引脚对应的界面
};

#endif // TREEWIDGETCHOOSEFUNCTION_H
