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

#include "FormMcuPinAttribute.h"
#include <utility>
#include "ui_FormMcuPinAttribute.h"


FormMcuPinAttribute::FormMcuPinAttribute(QWidget *parent) :
        QWidget(parent), ui(new Ui::FormMcuPinAttribute)
{
    ui->setupUi(this);

    ui->utreeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->utreeWidget->setMouseTracking(true);

    m_itemPin = createMasterItem(u8"引脚");
}

FormMcuPinAttribute::~FormMcuPinAttribute()
{
    delete ui;
}

void FormMcuPinAttribute::setBaseObject(BaseObject *baseObject)
{
    m_baseObject = baseObject;
    ASSERT_X(m_baseObject, u8"FormMcuPinAttribute", u8"空指针-> m_baseObject");
    createPinItems();
}

void FormMcuPinAttribute::setPinName(const QString &pinName)
{
    m_pinName = pinName;
}

void FormMcuPinAttribute::setType(const QString &type)
{
    m_type = type;
}

void FormMcuPinAttribute::setTitle(const QString &title)
{
    m_title = title;
    ui->ulabelTitle->setText(m_title);
}

void FormMcuPinAttribute::createPinItems()
{
    m_ioModel = m_baseObject->getIoModel();

    foreach(XmlIoModel::ParameterModel_T parameterModel, m_ioModel.parameters)
    {
        if(parameterModel.widget == u8"QComboBox")
        {
            createPinItem(parameterModel);
        }
    }
}

QTreeWidgetItem *FormMcuPinAttribute::createPinItem(XmlIoModel::ParameterModel_T &parameterModel)
{
    ASSERT_X(m_itemPin, u8"FormMcuPinAttribute", u8"空指针-> m_item_pin");

    auto *item = new QTreeWidgetItem(m_itemPin);
    item->setText(0, parameterModel.chineseName);
    item->setStatusTip(0, u8"引脚属性: " + parameterModel.chineseName);
    item->setToolTip(0, u8"引脚属性: " + parameterModel.chineseName);
    item->setWhatsThis(0, parameterModel.name);
    m_itemPinAttributes << item;

    auto *comboBox = createMcuPinAttributeComboBox(parameterModel.tables, parameterModel.name);

    ui->utreeWidget->setItemWidget(item, 1, comboBox);

    return item;
}

QTreeWidgetItem *FormMcuPinAttribute::createMasterItem(const QString &name)
{
    auto *item = new QTreeWidgetItem(ui->utreeWidget);
    item->setText(0, name);
    item->setExpanded(true);
    return item;
}

ComboBoxMcuPinAttribute *
FormMcuPinAttribute::createMcuPinAttributeComboBox(QList<XmlIoModel::TableModel_T> &tableModels,
                                                   const QString &whatsThis)
{
    auto *comboBoxMcuPinAttribute = new ComboBoxMcuPinAttribute(this);

    comboBoxMcuPinAttribute->setBaseObject(m_baseObject);
    m_mcuPinComboBoxAttributes << comboBoxMcuPinAttribute;
    comboBoxMcuPinAttribute->setWhatsThis(whatsThis);

    foreach (XmlIoModel::TableModel_T tableModel, tableModels)
    {
        comboBoxMcuPinAttribute->addKey(tableModel.key);
    }

    comboBoxMcuPinAttribute->setDisabled(true);

    return comboBoxMcuPinAttribute;
}

void FormMcuPinAttribute::setTag(const QString &tag)
{
    m_tag = tag;

    ui->ulabelTitle->setText(m_title + ": " + m_tag);

    if (m_mapSignals[m_tag] == u8"GPIO")
    {
        if(m_tag.contains(u8"EXTI"))
        {
            m_tag = u8"EXTI";
        }
        setPinTreeWidgetStatus();
    }
}

void FormMcuPinAttribute::setPinTreeWidgetStatus()
{
    foreach(ComboBoxMcuPinAttribute *comboBoxMcuPinAttribute, m_mcuPinComboBoxAttributes)
    {
        comboBoxMcuPinAttribute->setTag(m_tag);
    }
}

void FormMcuPinAttribute::setMapSignals(const QMap<QString, QString> &mapSignals)
{
    m_mapSignals = mapSignals;
}


