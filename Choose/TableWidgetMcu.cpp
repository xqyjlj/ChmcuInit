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
 ** 2021-04-21     xqyjlj       the first version        xqyjlj@126.com
 **/

#include "TableWidgetMcu.h"

TableWidgetMcu::TableWidgetMcu(QWidget *parent) : QTableWidget(parent)
{
    connect(this, &QTableWidget::itemSelectionChanged, this, &TableWidgetMcu::slotItemSelectionChanged,
            Qt::UniqueConnection);
}

void TableWidgetMcu::setBaseObject(BaseObject *baseObject)
{
    m_baseObject = baseObject;
    ASSERT_X(m_baseObject, u8"TableWidgetMcu", u8"空指针-> m_baseObject");
    addAllItems();
}

void TableWidgetMcu::addRowItems(const XmlFamilyModel::McuModel_T &model)
{
    int count = rowCount();
    insertRow(count);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setItem(count, 0, new QTableWidgetItem(model.name));
    setItem(count, 1, new QTableWidgetItem());
    setItem(count, 2, new QTableWidgetItem());
    setItem(count, 3, new QTableWidgetItem(model.package));
    setItem(count, 4, new QTableWidgetItem(model.flash));
    setItem(count, 5, new QTableWidgetItem(model.ram));
    setItem(count, 6, new QTableWidgetItem(model.io));
    setItem(count, 7, new QTableWidgetItem(model.frequency));
    setItem(count, 8, new QTableWidgetItem(model.company));
    setItem(count, 9, new QTableWidgetItem(model.core));
    setItem(count, 10, new QTableWidgetItem(model.family));
    setItem(count, 11, new QTableWidgetItem(model.subfamily));
}

void TableWidgetMcu::addAllItems()
{
    m_mcuModels = m_baseObject->getMcuModels();
    for (const XmlFamilyModel::McuModel_T &mcuModel: m_mcuModels)
    {
        addRowItems(mcuModel);
    }
}

void TableWidgetMcu::slotItemSelectionChanged()
{
    QList<QTableWidgetItem *> items = selectedItems();
    if (!items.isEmpty())
    {
        m_selectionMcuName = items.at(0)->text();
        emit signalSelectionMcuNameChanged(m_selectionMcuName);
    }
}

XmlFamilyModel::McuModel_T TableWidgetMcu::getSelectionMcuModel() const
{
    XmlFamilyModel::McuModel_T model;

    for (const XmlFamilyModel::McuModel_T &mcuModel: m_mcuModels)
    {
        if (mcuModel.name == m_selectionMcuName)
        {
            model = mcuModel;
        }
    }

    return model;
}
