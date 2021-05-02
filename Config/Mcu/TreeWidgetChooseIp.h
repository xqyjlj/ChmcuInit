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

#ifndef CHMCUINIT_TREEWIDGETCHOOSEIP_H
#define CHMCUINIT_TREEWIDGETCHOOSEIP_H

#include <QTreeWidget>
#include "FormGpio.h"
#include "BaseObject.h"

class TreeWidgetChooseIp : public QTreeWidget
{
Q_OBJECT
public:

    explicit TreeWidgetChooseIp(QWidget *parent);

private:

    void createMasterItems();

    void createMasterItem(const XmlIpModel::IpTagModel_T &ipTagModel);

    void createIpItem(QTreeWidgetItem *master, const QString &name);

    void createIpItems(QTreeWidgetItem *master, const QList<XmlIpModel::IpModel_T> &ipModels);

signals:

    void signalShowWidget(QWidget *widget, const QString &widgetName);

public slots:

    [[maybe_unused]] void slotPinSignalClicked(const QString &name, const QString &tag, bool isCanceled);

private slots:

    void slotCurrentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

private:

    BaseObject *m_baseObject = nullptr;

    QList<XmlIpModel::IpTagModel_T> m_ipTagModels;
    QList<XmlIpModel::IpModel_T> m_ipModels;

    QMap<QString, QWidget *> m_mapItemWidget;

public:

    void setBaseObject(BaseObject *baseObject);

};


#endif //CHMCUINIT_TREEWIDGETCHOOSEIP_H
