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

#include "TableWidgetGpio.h"
#include <QHeaderView>

TableWidgetGpio::TableWidgetGpio(QWidget *parent) : QTableWidget(parent)
{
    horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    connect(this, &QTableWidget::itemSelectionChanged, this, &TableWidgetGpio::slotItemSelectionChanged,
            Qt::UniqueConnection);
}

void TableWidgetGpio::addGpioModel(const QString &name, const QString &tag)
{
    if (m_mapGpioItem.contains(name))
    {
        m_mapGpioItem.value(name).signal->setText(tag);
        m_mapGpioItem.value(name).mode->setText(tag);

        m_mapGpioAttribute.value(name)->setTag(tag);
    }
    else
    {
        GpioItem_T gpioItem{};
        gpioItem.pinName = new QTableWidgetItem(name);
        gpioItem.signal = new QTableWidgetItem(tag);
        gpioItem.level = new QTableWidgetItem(u8"N/A");
        gpioItem.mode = new QTableWidgetItem(tag);
        gpioItem.pull = new QTableWidgetItem(u8"不上拉不下拉");
        gpioItem.speed = new QTableWidgetItem(u8"低速");
        gpioItem.label = new QTableWidgetItem(u8"N/A");

        auto *formGpioAttribute = new FormGpioAttribute();
        formGpioAttribute->setBaseObject(m_baseObject);
        formGpioAttribute->setPinName(name);
        formGpioAttribute->setTag(tag);

        m_mapGpioAttribute.insert(name, formGpioAttribute);
        m_mapGpioItem.insert(name, gpioItem);

        int count = rowCount();
        insertRow(count);
        setEditTriggers(QAbstractItemView::NoEditTriggers);

        setItem(count, 0, gpioItem.pinName);
        setItem(count, 1, gpioItem.signal);
        setItem(count, 2, gpioItem.level);
        setItem(count, 3, gpioItem.mode);
        setItem(count, 4, gpioItem.pull);
        setItem(count, 5, gpioItem.speed);
        setItem(count, 6, gpioItem.label);
    }
}

void TableWidgetGpio::removeGpioModel(const QString &name)
{
    emit signalShowGpioAttributeWidget(nullptr);

    m_mapGpioItem.remove(name);

    QList<QTableWidgetItem *> items = findItems(name, Qt::MatchRegularExpression);
    for (QTableWidgetItem *item: items)
    {
        removeRow(row(item));
    }

    delete m_mapGpioAttribute.value(name);
    m_mapGpioAttribute.remove(name);
}

void TableWidgetGpio::setBaseObject(BaseObject *baseObject)
{
    m_baseObject = baseObject;
    ASSERT_X(m_baseObject, u8"TableWidgetGpio", u8"空指针-> m_baseObject");
}

void TableWidgetGpio::slotItemSelectionChanged()
{
    QList<QTableWidgetItem *> items = selectedItems();
    if (!items.isEmpty())
    {
        emit signalShowGpioAttributeWidget(m_mapGpioAttribute.value(items.at(0)->text()));
    }
}