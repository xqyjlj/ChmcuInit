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
 ** 2021-04-01     xqyjlj       the first version        xqyjlj@126.com
 **/
#include "TreeWidgetChooseIp.h"
#include "Debug.h"

TreeWidgetChooseIp::TreeWidgetChooseIp(QWidget* parent) : QTreeWidget(parent)
{
    connect(this, &QTreeWidget::itemSelectionChanged, this, &TreeWidgetChooseIp::treeWidgetChooseIpItemSelectionChanged, Qt::UniqueConnection);
}

/**
 * @brief   设置基础对象
 *
 * @param   baseObject: 基础对象
 *
 * @return  null
*/
void TreeWidgetChooseIp::setBaseObject(BaseObject* baseObject)
{
    mbaseObject = baseObject;
    ASSERT_X(mbaseObject, "TreeWidgetChooseIp", "空指针-> mbaseObject");
    mipModels = mbaseObject->getIpModels();
    mipNames = mbaseObject->getIpNames();
    load();
}

/**
 * @brief   加载
 *
 * @param   null
 *
 * @return  null
*/
void TreeWidgetChooseIp::load()
{
    ASSERT_X(mipNames, "TreeWidgetChooseIp", "空指针-> mipNames");
    ASSERT_X(mipModels, "TreeWidgetChooseIp", "空指针-> mipModels");

    int length = mipNames->length();
    for (int i = 0; i < length; i++)
    {
        QString str = mipNames->at(i);

        QTreeWidgetItem* item = new QTreeWidgetItem(this);
        item->setText(0, str);

        int length = mipModels->length();

        for (int i = 0; i < length; i++)
        {
            Model::XmlIpModel* model = const_cast<Model::XmlIpModel* >(&mipModels->at(i));
            if (model->name == str)
            {
                QTreeWidgetItem* _item = new QTreeWidgetItem(item);
                _item->setText(0, model->instanceName);
            }
        }
    }
}

void TreeWidgetChooseIp::treeWidgetChooseIpItemSelectionChanged()
{
//    if (selectedItems().length() > 0)
//    {
//        QString str = selectedItems().at(0)->text(0);
//        foreach (Model::XmlIpModel model, ipModels)
//        {
//            if (model.instanceName == str)
//            {
//                emit ipChosen(model.instanceName, model.packLocate + "/" + model.packName + "_" + model.version + ".xml");
//            }
//        }
//    }
}
