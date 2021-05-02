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

#include "TreeWidgetChooseIp.h"

TreeWidgetChooseIp::TreeWidgetChooseIp(QWidget *parent) : QTreeWidget(parent)
{
    connect(this, &QTreeWidget::currentItemChanged, this, &TreeWidgetChooseIp::slotCurrentItemChanged,
            Qt::UniqueConnection);
}

void TreeWidgetChooseIp::setBaseObject(BaseObject *baseObject)
{
    m_baseObject = baseObject;
    ASSERT_X(m_baseObject, u8"TreeWidgetChooseIp", u8"空指针-> m_baseObject");
    createMasterItems();
}

void TreeWidgetChooseIp::createMasterItems()
{
    m_ipTagModels = m_baseObject->getIpTagModels();
    m_ipModels = m_baseObject->getIpModels();

    for (const XmlIpModel::IpTagModel_T &ipTagModel: m_ipTagModels)
    {
        createMasterItem(ipTagModel);
    }
}

void TreeWidgetChooseIp::createMasterItem(const XmlIpModel::IpTagModel_T &ipTagModel)
{
    auto *item = new QTreeWidgetItem(this);
    item->setText(0, ipTagModel.chineseName);
    item->setExpanded(true);
    createIpItems(item, ipTagModel.ips);
}

void TreeWidgetChooseIp::createIpItem(QTreeWidgetItem *master, const QString &name)
{
    auto *item = new QTreeWidgetItem(master);
    item->setText(0, name);
    item->setWhatsThis(0, u8"IP:" + name);
    if (name == u8"GPIO")
    {
        auto *formGpio = new FormGpio();
        formGpio->setBaseObject(m_baseObject);
        m_mapItemWidget.insert(item->text(0), formGpio);
    }
}

void TreeWidgetChooseIp::createIpItems(QTreeWidgetItem *master, const QList<XmlIpModel::IpModel_T> &ipModels)
{
    for (const XmlIpModel::IpModel_T &ipModel: ipModels)
    {
        createIpItem(master, ipModel.instanceName);
    }
}

void TreeWidgetChooseIp::slotCurrentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    if (current->whatsThis(0).contains(u8"IP"))
    {
        if (previous != current)
        {
            if (current->text(0) == u8"GPIO")
            {
                emit signalShowWidget(m_mapItemWidget.value(current->text(0)), u8"FormGpio");
            }
        }
    }
}

[[maybe_unused]] void TreeWidgetChooseIp::slotPinSignalClicked(const QString &name, const QString &tag, bool isCanceled)
{
    if (m_mapItemWidget.contains(u8"GPIO"))
    {
        dynamic_cast<FormGpio *>(m_mapItemWidget.value(u8"GPIO"))->slotPinSignalClicked(name, tag, isCanceled);
    }
}
