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

#include "TreeWidgetChooseMcu.h"

TreeWidgetChooseMcu::TreeWidgetChooseMcu(QWidget *parent) : QTreeWidget(parent)
{
    m_itemCompany = createMasterItem(u8"公司");
    m_itemCore = createMasterItem(u8"内核");
    m_itemFamily = createMasterItem(u8"主科");
    m_itemSubfamily = createMasterItem(u8"副科");
    m_itemPackage = createMasterItem(u8"封装");
}

void TreeWidgetChooseMcu::setBaseObject(BaseObject *baseObject)
{
    m_baseObject = baseObject;
    ASSERT_X(m_baseObject, u8"TreeWidgetChooseMcu", u8"空指针-> m_baseObject");

    m_mcuModels = m_baseObject->getMcuModels();

    addCompanyItems();
    addCoreItems();
    addFamilyItems();
    addSubfamilyItems();
    addPackageItems();
}

QTreeWidgetItem *TreeWidgetChooseMcu::createMasterItem(const QString& name)
{
    auto *item = new QTreeWidgetItem(this);
    item->setText(0, name);
    item->setCheckState(0, Qt::Unchecked);
    item->setExpanded(true);
    return item;
}

void TreeWidgetChooseMcu::addCompanyItems()
{
    findCompanyNames();
    foreach (QString name, m_companyNames)
    {
        addCompanyItem(name);
    }
}

void TreeWidgetChooseMcu::addCompanyItem(const QString& company)
{
    ASSERT_X(m_itemCompany, u8"TreeWidgetChooseMcu", u8"空指针-> m_itemCompany");
    auto* item = new QTreeWidgetItem(m_itemCompany);
    item->setText(0, company);
    item->setCheckState(0, Qt::Unchecked);
}

void TreeWidgetChooseMcu::findCompanyNames()
{
    foreach(XmlFamilyModel::McuModel_T model, m_mcuModels)
    {
        if (!m_companyNames.contains(model.company))
        {
            m_companyNames << model.company;
        }
    }
}

void TreeWidgetChooseMcu::findCoreNames()
{
    foreach (XmlFamilyModel::McuModel_T model, m_mcuModels)
    {
        if (!m_coreNames.contains(model.core))
        {
            m_coreNames << model.core;
        }
    }
}

void TreeWidgetChooseMcu::addCoreItems()
{
    findCoreNames();
    foreach (QString name, m_coreNames)
    {
        addCoreItem(name);
    }
}

void TreeWidgetChooseMcu::addCoreItem(const QString& core)
{
    ASSERT_X(m_itemCore, u8"TreeWidgetChooseMcu", u8"空指针-> m_itemCore");
    auto* item = new QTreeWidgetItem(m_itemCore);
    item->setText(0, core);
    item->setCheckState(0, Qt::Unchecked);
}

void TreeWidgetChooseMcu::findFamilyNames()
{
    foreach (XmlFamilyModel::McuModel_T model, m_mcuModels)
    {
        if (!m_familyNames.contains(model.family))
        {
            m_familyNames << model.family;
        }
    }
}

void TreeWidgetChooseMcu::addFamilyItems()
{
    findFamilyNames();
    foreach (QString name, m_familyNames)
    {
        addFamilyItem(name);
    }
}

void TreeWidgetChooseMcu::addFamilyItem(const QString& family)
{
    ASSERT_X(m_itemFamily, u8"TreeWidgetChooseMcu", u8"空指针-> m_itemFamily");
    auto* item = new QTreeWidgetItem(m_itemFamily);
    item->setText(0, family);
    item->setCheckState(0, Qt::Unchecked);
}

void TreeWidgetChooseMcu::findSubfamilyNames()
{
    foreach (XmlFamilyModel::McuModel_T model, m_mcuModels)
    {
        if (!m_subfamilyNames.contains(model.subfamily))
        {
            m_subfamilyNames << model.subfamily;
        }
    }
}

void TreeWidgetChooseMcu::addSubfamilyItems()
{
    findSubfamilyNames();
    foreach (QString name, m_subfamilyNames)
    {
        addSubfamilyItem(name);
    }
}

void TreeWidgetChooseMcu::addSubfamilyItem(const QString& subfamily)
{
    ASSERT_X(m_itemSubfamily, u8"TreeWidgetChooseMcu", u8"空指针-> m_itemSubfamily");
    auto* item = new QTreeWidgetItem(m_itemSubfamily);
    item->setText(0, subfamily);
    item->setCheckState(0, Qt::Unchecked);
}

void TreeWidgetChooseMcu::findPackageNames()
{
    foreach (XmlFamilyModel::McuModel_T model, m_mcuModels)
    {
        if (!m_packageNames.contains(model.package))
        {
            m_packageNames << model.package;
        }
    }
}

void TreeWidgetChooseMcu::addPackageItems()
{
    findPackageNames();
    foreach (QString name, m_packageNames)
    {
        addPackageItem(name);
    }
}

void TreeWidgetChooseMcu::addPackageItem(const QString& package)
{
    ASSERT_X(m_itemPackage, u8"TreeWidgetChooseMcu", u8"空指针-> m_itemPackage");
    auto* item = new QTreeWidgetItem(m_itemPackage);
    item->setText(0, package);
    item->setCheckState(0, Qt::Unchecked);
}

