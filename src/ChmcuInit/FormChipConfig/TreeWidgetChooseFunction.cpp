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
    STM32Model::XmlIpF1IoModel model =
        STM32Xml::STM32XmlRead().getIpF1IoModel(
            "C:/Users/xqyjlj/Desktop/build-ChmcuInit-Desktop_Qt_5_15_2_MSVC2019_64bit-Debug/src/ChmcuInit/debug/origin/families/ip/stm32/stm32_io_F1_Cube_0_0.xml",
            "STM32F103",
            "STM32F103C8T6");
}

/**
 * @brief   设置引脚模型
 *
 * @param   model: 引脚模型
 *
 * @return  null
*/
void TreeWidgetChooseFunction::setPinModel(QList<Model::XmlPinModel> list)
{
    QList<QTreeWidgetItem*> _items = this->findItems(tr("Pin"), Qt::MatchExactly);
    if (_items.length() && !list.isEmpty())
    {
        QTreeWidgetItem* _parent = _items.at(0);
        _parent->setExpanded(true);
        mformPinAttributes = QVector<FormPinAttribute*>(list.length(), nullptr);
        foreach (Model::XmlPinModel _model, list)
        {
            QTreeWidgetItem* _item = new QTreeWidgetItem(_parent);
            _item->setText(0, _model.position + ": " + _model.name);

            QComboBox* _comboBox = new QComboBox(this);
            _comboBox->addItem("无");
            foreach (Model::XmlPinModel::SignalModel _signalModel, _model.signal)
            {
                _comboBox->addItem(_signalModel.name);
            }
            this->setItemWidget(_item, 1, _comboBox);
            mpinComboBox << _comboBox;
            _comboBox->setWhatsThis(_model.position);
            connect(_comboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(comboBoxCurrentTextChanged(QString)), Qt::UniqueConnection);
            _item->setWhatsThis(0, _model.position);
            mpinItems << _item;
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
    LOG_D << selectItems;
    QVector<bool> bools(mpinItems.length(), false);
    foreach (QTreeWidgetItem* item, selectItems)
    {
        int index = item->whatsThis(0).toInt() - 1;
        if (index > mpinItems.length() - 1 || index < 0)
            return;
        bools[index] = true;

        if (mformPinAttributes.at(index) == nullptr)
        {
            mformPinAttributes[index] = new FormPinAttribute();
        }
        emit pinAttributeOpened(mformPinAttributes.at(index));
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
void TreeWidgetChooseFunction::comboBoxCurrentTextChanged(QString str)
{
    LOG_D << str;
}
