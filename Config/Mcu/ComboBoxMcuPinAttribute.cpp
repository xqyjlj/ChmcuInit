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
 ** 2021-04-23     xqyjlj       the first version        xqyjlj@126.com
 **/

#include "ComboBoxMcuPinAttribute.h"

ComboBoxMcuPinAttribute::ComboBoxMcuPinAttribute(QWidget *parent) : QComboBox(parent)
{

}

void ComboBoxMcuPinAttribute::setBaseObject(BaseObject *baseObject)
{
    m_baseObject = baseObject;
    ASSERT_X(m_baseObject, u8"ComboBoxMcuPinAttribute", u8"空指针-> m_baseObject");
    setMapIoTables();
}

void ComboBoxMcuPinAttribute::setMapIoTables()
{
    m_mapIoTables = m_baseObject->getMapIoTables();
}

void ComboBoxMcuPinAttribute::setTag(const QString &tag)
{
    m_tag = tag;
    setItemStatus();
}

void ComboBoxMcuPinAttribute::setItemStatus()
{
    int length = static_cast<int>(m_keys.length());

    bool disabled = true;

    setDisabled(disabled);

    for (int i = length - 1; i >= 0; i--)
    {
        setItemData(i, QVariant(1 | 32), Qt::UserRole - 1);
        if (!m_mapIoTables.values(m_keys.at(i)).at(0).contains(m_tag))
        {
            setItemData(i, QVariant(0), Qt::UserRole - 1);
        } else
        {
            disabled = false;
            setCurrentIndex(i);
        }
    }
    setDisabled(disabled);
}

void ComboBoxMcuPinAttribute::addKey(const QString &key)
{
    m_keys << key;
    addItem(key);
    setItemData(count() - 1, QVariant(0), Qt::UserRole - 1);
}

QString ComboBoxMcuPinAttribute::getCurrentValue()
{
    if(isEnabled())
    {
        return m_mapIoTables.values(currentText()).at(1);
    }
    else
    {
        return QString();
    }
}