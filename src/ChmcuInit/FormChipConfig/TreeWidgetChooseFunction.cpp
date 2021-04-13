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
#include "TreeWidgetChooseFunction.h"
#include <QHeaderView>
#include "Debug.h"
#include "STM32XmlRead.h"


TreeWidgetChooseFunction::TreeWidgetChooseFunction(QWidget* parent) : QTreeWidget(parent)
{
    connect(this, SIGNAL(itemSelectionChanged()), this, SLOT(TreeWidgetChooseFunctionItemSelectionChanged()), Qt::UniqueConnection);
}

/**
 * @brief   设置基础对象
 *
 * @param   baseObject: 基础对象
 *
 * @return  null
*/
void TreeWidgetChooseFunction::setBaseObject(const BaseObject* baseObject)
{
    mbaseObject = const_cast<BaseObject*>(baseObject);
    ASSERT_X(mbaseObject, "TreeWidgetChooseFunction", "空指针-> mbaseObject");
    mpinModels = mbaseObject->getPinModels();
    load();
}

/**
 * @brief   加载
 *
 * @param   null
 *
 * @return  null
*/
void TreeWidgetChooseFunction::load(void)
{
    QList<QTreeWidgetItem*> _items = this->findItems(tr("Pin"), Qt::MatchExactly);
    if (_items.length())
    {
        QTreeWidgetItem* _parent = _items.at(0);
        _parent->setExpanded(true);

        int length = mpinModels->length();
        for (int i = 0; i < length ; i++)
        {
            Model::XmlPinModel* _model = const_cast<Model::XmlPinModel* >(&mpinModels->at(i));

            QTreeWidgetItem* _item = new QTreeWidgetItem(_parent);
            _item->setText(0, _model->position + ": " + _model->name);
            _item->setWhatsThis(0, _model->position);

            QComboBox* _pinComboBox = new QComboBox(this);
            _pinComboBox->addItem("无");


            int length = _model->signal.length();
            for (int i = 0; i < length; i++)
            {
                Model::XmlPinModel::SignalModel* _signalModel = const_cast<Model::XmlPinModel::SignalModel* >(&_model->signal.at(i));
                _pinComboBox->addItem(_signalModel->name);
            }

            this->setItemWidget(_item, 1, _pinComboBox);
            mpinComboBoxs << _pinComboBox;
            _pinComboBox->setWhatsThis(_model->position);

            connect(_pinComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(pinComboBoxCurrentTextChanged(QString)), Qt::UniqueConnection);

            mpinItems << _item;

            FormPinAttribute* _formPinAttributes = new FormPinAttribute();

            _formPinAttributes->setBaseObject(mbaseObject);
            _formPinAttributes->setTitle(_item->text(0), _model->type);
            _formPinAttributes->setType("无");
            mformPinAttributes << _formPinAttributes;
        }
    }
}

/**
 * @brief   TreeWidgetChooseFunction(自己)的Item选中状态被改变而触发的槽函数
 *
 * @param   null
 *
 * @return  null
*/
void TreeWidgetChooseFunction::TreeWidgetChooseFunctionItemSelectionChanged()
{
    selectItems = selectedItems();
    QVector<bool> bools(mpinItems.length(), false);
    foreach (QTreeWidgetItem* item, selectItems)
    {
        int index = item->whatsThis(0).toInt() - 1;
        if (index > mpinItems.length() - 1 || index < 0)
            return;
        bools[index] = true;
        mformPinAttribute = mformPinAttributes.at(index);
        emit pinAttributeOpened(mformPinAttribute);
    }
    emit pinClicked(bools);
}

/**
 * @brief   选择引脚
 *
 * @param   bools: 装有所有引脚被选中的bool状态
 *
 * @return  null
*/
void TreeWidgetChooseFunction::selectPin(QVector<bool> bools)
{
    int length = mpinItems.length();
    QList<QTreeWidgetItem*> _selectItems = selectedItems();
    foreach (QTreeWidgetItem* item, _selectItems)
    {
        item->setSelected(false);
    }

    if (bools.length() == length)
    {
        for (int i = 0; i < length; i++)
        {
            mpinItems.at(i)->setSelected(bools.at(i));
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
void TreeWidgetChooseFunction::pinComboBoxCurrentTextChanged(QString str)
{
    if (selectItems.length() == 1)
    {
        mformPinAttribute->setType(str);
    }
}
