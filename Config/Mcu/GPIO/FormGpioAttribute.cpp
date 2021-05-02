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
 ** 2021-05-02     xqyjlj       the first version        xqyjlj@126.com
 **/

#include "FormGpioAttribute.h"
#include "ui_FormGpioAttribute.h"


FormGpioAttribute::FormGpioAttribute(QWidget *parent) :
        QWidget(parent), ui(new Ui::FormGpioAttribute)
{
    ui->setupUi(this);

    ui->u_treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->u_treeWidget->setMouseTracking(true);

}

FormGpioAttribute::~FormGpioAttribute()
{
    delete ui;
}

void FormGpioAttribute::setBaseObject(BaseObject *baseObject)
{
    m_baseObject = baseObject;
    ASSERT_X(m_baseObject, u8"FormGpioAttribute", u8"空指针-> m_baseObject");

    createPinItems();

    connect(this, &FormGpioAttribute::signalAddGpioModel, m_baseObject->getFileProject(),
            &FileProject::slotAddGpioModel, Qt::UniqueConnection);

    connect(m_baseObject, &BaseObject::signalConfigProject, this, &FormGpioAttribute::slotConfigProject,
            Qt::UniqueConnection);
}

void FormGpioAttribute::setTag(const QString &tag)
{
    m_tag = tag;

    ui->u_labelTitle->setText(m_pinName + ": " + m_tag);

    if (m_tag.contains(u8"EXTI") && !m_tag.contains(u8"_"))
    {
        m_tag = u8"EXTI";
    }

    if (QString(u8"Input,Output,Analog,EVENTOUT,EXTI10").contains(m_tag))
    {
        setComboBoxGpioAttributeStatus();
    }
}

void FormGpioAttribute::setPinName(const QString &pinName)
{
    m_pinName = pinName;
}

void FormGpioAttribute::createPinItems()
{
    m_ioModel = m_baseObject->getIoModel();

    for (const XmlIoModel::ParameterModel_T &parameterModel: m_ioModel.parameters)
    {
        if (parameterModel.widget == u8"QComboBox")
        {
            createPinItemWithComboBox(parameterModel);
        }
    }
}

QTreeWidgetItem *FormGpioAttribute::createPinItemWithComboBox(const XmlIoModel::ParameterModel_T &parameterModel)
{
    auto *item = new QTreeWidgetItem(ui->u_treeWidget);
    item->setText(0, parameterModel.chineseName);
    item->setStatusTip(0, u8"引脚属性: " + parameterModel.chineseName);
    item->setToolTip(0, u8"引脚属性: " + parameterModel.chineseName);
    item->setWhatsThis(0, parameterModel.name);
    m_itemGpioAttributes << item;

    auto *comboBox = createGpioAttributeComboBox(parameterModel.tables, parameterModel.name);
    ui->u_treeWidget->setItemWidget(item, 1, comboBox);

    return item;
}

ComboBoxGpioAttribute *
FormGpioAttribute::createGpioAttributeComboBox(const QList<XmlIoModel::TableModel_T> &tableModels,
                                               const QString &whatsThis)
{
    auto *comboBoxMcuPinAttribute = new ComboBoxGpioAttribute(this);

    comboBoxMcuPinAttribute->setBaseObject(m_baseObject);
    m_mcuComboBoxGpioAttribute << comboBoxMcuPinAttribute;
    comboBoxMcuPinAttribute->setWhatsThis(whatsThis);

    for (const XmlIoModel::TableModel_T &tableModel: tableModels)
    {
        comboBoxMcuPinAttribute->addKey(tableModel.key);
    }

    comboBoxMcuPinAttribute->setDisabled(true);

    return comboBoxMcuPinAttribute;
}

void FormGpioAttribute::setComboBoxGpioAttributeStatus()
{
    for (ComboBoxGpioAttribute *comboBoxGpioAttribute: m_mcuComboBoxGpioAttribute)
    {
        comboBoxGpioAttribute->setTag(m_tag);
    }
}

void FormGpioAttribute::slotConfigProject()
{
    int length = static_cast<int>(m_itemGpioAttributes.length());
    XmlFileProjectModel::GpioModel_T gpioModel;//GPIO模型
    for (int i = 0; i < length; i++)
    {
        QTreeWidgetItem *item = m_itemGpioAttributes.at(i);
        if (!item->isDisabled())
        {
            gpioModel.name = m_pinName;
            QWidget *widget = ui->u_treeWidget->itemWidget(item, 1);
            if (widget)
            {
                QString className = QString(widget->metaObject()->className());
                if (className == u8"QComboBox")
                {
                    auto *comboBox = dynamic_cast<ComboBoxGpioAttribute *>(widget);
                    if (comboBox->whatsThis() == u8"Level")
                    {
                        gpioModel.level = comboBox->getCurrentValue();
                    }
                    else if (comboBox->whatsThis() == u8"Mode")
                    {
                        gpioModel.mode = comboBox->getCurrentValue();
                    }
                    else if (comboBox->whatsThis() == u8"Speed")
                    {
                        gpioModel.speed = comboBox->getCurrentValue();
                    }
                    else if (comboBox->whatsThis() == u8"Pull")
                    {
                        gpioModel.pull = comboBox->getCurrentValue();
                    }
                }
            }
        }
    }
    if (!gpioModel.name.isEmpty())
    {
        parseGpioModel(gpioModel);
        emit signalAddGpioModel(gpioModel);
    }
}

void FormGpioAttribute::parseGpioModel(XmlFileProjectModel::GpioModel_T &gpioModel)
{
    if (gpioModel.name.startsWith(u8"P"))
    {
        gpioModel.port = u8"GPIO" + QString(gpioModel.name.at(1));
        gpioModel.pin = u8"GPIO_PIN_" + gpioModel.name.right(gpioModel.name.length() - 2);
    }
}

