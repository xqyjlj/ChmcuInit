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
 ** 2021-04-22     xqyjlj       the first version        xqyjlj@126.com
 **/

#include "TreeWidgetMcuChooseFunction.h"
#include <QHeaderView>

TreeWidgetMcuChooseFunction::TreeWidgetMcuChooseFunction(QWidget *parent) : QTreeWidget(parent)
{
    setMouseTracking(true);

    m_itemPin = createMasterItem(u8"引脚");

    header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    connect(this, &QTreeWidget::currentItemChanged, this, &TreeWidgetMcuChooseFunction::slotCurrentItemChanged,
            Qt::UniqueConnection);
}

void TreeWidgetMcuChooseFunction::setBaseObject(BaseObject *baseObject)
{
    m_baseObject = baseObject;
    ASSERT_X(m_baseObject, u8"TreeWidgetMcuChooseFunction", u8"空指针-> m_baseObject");

    connect(m_baseObject, &BaseObject::signalConfigProject, this, &TreeWidgetMcuChooseFunction::slotConfigProject,
            Qt::UniqueConnection);

    createPinItems();
}

QTreeWidgetItem *TreeWidgetMcuChooseFunction::createMasterItem(const QString &name)
{
    auto *item = new QTreeWidgetItem(this);
    item->setText(0, name);
    item->setExpanded(true);
    return item;
}

QTreeWidgetItem *TreeWidgetMcuChooseFunction::createPinItem(XmlPinModel::PinModel_T &pinModel)
{
    ASSERT_X(m_itemPin, u8"TreeWidgetMcuChooseFunction", u8"空指针-> m_item_pin");
    auto *item = new QTreeWidgetItem(m_itemPin);
    item->setText(0, pinModel.name);
    item->setWhatsThis(0, pinModel.position);
    item->setToolTip(0, QString(pinModel.position) + u8": " + pinModel.name);
    item->setStatusTip(0, QString(pinModel.position) + u8": " + pinModel.name);

    m_itemPins << item;

    QComboBox *comboBox = createPinComboBox(pinModel.signal);

    setItemWidget(item, 1, comboBox);

    createFormMcuPinAttribute(pinModel);
    return item;
}

void TreeWidgetMcuChooseFunction::createPinItems()
{
    m_pinModels = m_baseObject->getPinModels();
            foreach(XmlPinModel::PinModel_T pinModel, m_pinModels)
        {
            createPinItem(pinModel);
        }
}

QComboBox *TreeWidgetMcuChooseFunction::createPinComboBox(QList<XmlPinModel::SignalModel_T> &signalModels)
{
    auto *pinComboBox = new QComboBox(this);
    pinComboBox->addItem(u8"NULL");

            foreach(XmlPinModel::SignalModel_T signalModel, signalModels)
        {
            if (signalModel.ioModes.isEmpty())
            {
                pinComboBox->addItem(signalModel.name);
            } else
            {
                QStringList list = signalModel.ioModes.split(u8",");
                        foreach(QString str, list)
                    {
                        pinComboBox->addItem(str);
                        m_mapSignals.insert(str, signalModel.name);
                    }
            }
        }

    connect(pinComboBox, &QComboBox::currentTextChanged, this,
            &TreeWidgetMcuChooseFunction::slotPinComboBoxCurrentTextChanged, Qt::UniqueConnection);

    m_pinComboBoxes << pinComboBox;

    return pinComboBox;
}

void TreeWidgetMcuChooseFunction::slotPinComboBoxCurrentTextChanged(const QString &text)
{
    m_formMcuPinAttributes.at(m_currentIndex)->setTag(text);
}

void TreeWidgetMcuChooseFunction::slotCurrentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    if (current->parent() == m_itemPin)
    {
        m_currentIndex = current->whatsThis(0).toInt() - 1;
        if (previous != current)
        {
            emit signalShowFormMcuAttribute(m_formMcuPinAttributes.at(m_currentIndex));
        }
    }
}

FormMcuPinAttribute *TreeWidgetMcuChooseFunction::createFormMcuPinAttribute(XmlPinModel::PinModel_T &pinModel)
{
    auto *formMcuPinAttribute = new FormMcuPinAttribute();

    formMcuPinAttribute->setBaseObject(m_baseObject);
    formMcuPinAttribute->setMapSignals(m_mapSignals);
    formMcuPinAttribute->setPinName(pinModel.name);
    formMcuPinAttribute->setType(pinModel.type);
    formMcuPinAttribute->setTitle(pinModel.name + u8"-> " + pinModel.type);
    formMcuPinAttribute->setTag(u8"NULL");

    m_formMcuPinAttributes << formMcuPinAttribute;

    return formMcuPinAttribute;
}

void TreeWidgetMcuChooseFunction::slotConfigProject()
{
    int length = static_cast<int>(m_pinComboBoxes.length());
    for (int i = 0; i < length; i++)
    {
        QComboBox *comboBox = m_pinComboBoxes.at(i);
        if (comboBox->currentIndex() != 0)
        {
            m_formMcuPinAttributes.at(i)->slotConfigProject();
        }
    }
}
