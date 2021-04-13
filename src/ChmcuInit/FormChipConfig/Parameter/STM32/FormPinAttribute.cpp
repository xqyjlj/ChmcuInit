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
 ** 2021-03-20     xqyjlj       the first version        xqyjlj@126.com
 **/
#include "FormPinAttribute.h"
#include "ui_FormPinAttribute.h"
#include "Debug.h"
#include "STM32XmlRead.h"


FormPinAttribute::FormPinAttribute(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::FormPinAttribute)
{
    ui->setupUi(this);
}

FormPinAttribute::~FormPinAttribute()
{
    delete ui;
}

/**
 * @brief   设置基础对象
 *
 * @param   baseObject: 基础对象
 *
 * @return  null
*/
void FormPinAttribute::setBaseObject(const BaseObject* baseObject)
{
    mbaseObject = const_cast<BaseObject*>(baseObject);
    ASSERT_X(mbaseObject, "FormPinAttribute", "空指针-> mbaseObject");
}

/**
 * @brief   加载本模块
 *
 * @param   null
 *
 * @return  null
*/
void FormPinAttribute::load(void)
{
    ASSERT_X(mbaseObject, "FormPinAttribute", "空指针-> mbaseObject");
    mipF1IoModel = STM32Xml::STM32XmlRead().getIpF1IoModel(mbaseObject->getIpPackPath("IO"), mbaseObject->getSubfamilyName(), mbaseObject->getMcuName());
}

/**
 * @brief   设置标题
 *
 * @param   title: 标题
 *          attribute: 属性
 *
 * @return  null
*/
void FormPinAttribute::setTitle(const QString title, const QString attribute)
{
    mtitle = title;
    mattributes << attribute;
    ui->labelTitle->setText(title + "->" + attribute);
    load();
    addItem();
}

/**
 * @brief   设置种类
 *
 * @param   type: 种类
 *
 * @return  null
*/
void FormPinAttribute::setType(const QString type)
{
    mtype = type;
    foreach (QTreeWidgetItem* item, mtreeWidgetItems)
    {
        LOG_D << item->text(0) << reinterpret_cast<QComboBox*>(ui->treeWidget->itemWidget(item, 1))->currentText();
    }
}

/**
 * @brief   添加Item
 *
 * @param   null
 *
 * @return  null
*/
void FormPinAttribute::addItem(void)
{
    QTreeWidgetItem* modeItem = new QTreeWidgetItem(ui->treeWidget);
    modeItem->setText(0, "IO");

    int length = mipF1IoModel.mode.length();
    for (int i = 0; i < length; i++)
    {
        STM32Model::XmlIpF1IoModel::ModeModel* modeModel = const_cast<STM32Model::XmlIpF1IoModel::ModeModel*>(&mipF1IoModel.mode.at(i));
        if (modeModel->widgets == "QComboBox")
        {
            QTreeWidgetItem* item = new QTreeWidgetItem(modeItem);
            mtreeWidgetItems << item;
            item->setText(0, modeModel->name);

            QComboBox* comboBox = new QComboBox(this);
            mattributeComboBoxs << comboBox;
            connect(comboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(attributeComboBoxCurrentTextChanged(QString)), Qt::UniqueConnection);

            int length = modeModel->tables.length();
            for (int i = 0; i < length; i++)
            {
                STM32Model::XmlIpF1IoModel::TableModel* tableModel = const_cast<STM32Model::XmlIpF1IoModel::TableModel*>(&modeModel->tables.at(i));
                mkeys << tableModel->key;
                mvalues << tableModel->value;
                comboBox->addItem(tableModel->key);
            }

            ui->treeWidget->setItemWidget(item, 1, comboBox);
        }
    }
}

/**
 * @brief   comboBox的项被改变时触发的槽函数
 *
 * @param   str: 触发之后文本
 *
 * @return  null
*/
void FormPinAttribute::attributeComboBoxCurrentTextChanged(QString str)
{
    if (!mtype.isEmpty() && mtype != "无")
    {
        LOG_D << str;
    }
}
