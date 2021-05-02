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

#include "FormMcuConfig.h"
#include "ui_FormMcuConfig.h"
#include "WidgetLQFP48.h"

FormMcuConfig::FormMcuConfig(QWidget *parent) :
        QWidget(parent), ui(new Ui::FormMcuConfig)
{
    ui->setupUi(this);
    connect(ui->u_treeWidgetChooseIp, &TreeWidgetChooseIp::signalShowWidget, this, &FormMcuConfig::slotShowIpWidget,
            Qt::UniqueConnection);
}

FormMcuConfig::~FormMcuConfig()
{
    delete ui;
}

void FormMcuConfig::setBaseObject(BaseObject *baseObject)
{
    m_baseObject = baseObject;
    ASSERT_X(m_baseObject, u8"FormMcuConfig", u8"空指针-> m_baseObject");
    ui->u_treeWidgetChooseIp->setBaseObject(m_baseObject);

    auto *graphicsScene = new QGraphicsScene(ui->u_graphicsView);
    auto *widgetLqfp48 = new WidgetLQFP48();
    widgetLqfp48->setBaseObject(m_baseObject);

    connect(widgetLqfp48, SIGNAL(signalPinSignalClicked(QString, QString, bool)), ui->u_treeWidgetChooseIp,
            SLOT(slotPinSignalClicked(QString, QString, bool)), Qt::UniqueConnection);

    graphicsScene->addWidget(widgetLqfp48);
    ui->u_graphicsView->setScene(graphicsScene);
}

void FormMcuConfig::slotShowIpWidget(QWidget *widget, const QString &widgetName)
{
    static QWidget *previousWidget = nullptr;
    ASSERT_X(widget, "FormChipConfig", "空指针" + widgetName);

    if (previousWidget && previousWidget != widget)
    {
        widget->setParent(ui->u_widgetIp);
        ui->u_gridLayoutIp->replaceWidget(previousWidget, widget);
        widget->show();
        previousWidget->hide();
    }
    else
    {
        ui->u_gridLayoutIp->addWidget(widget);
    }
    previousWidget = widget;
}

//void FormMcuConfig::slotShowFormMcuAttribute(FormMcuPinAttribute *widget)
//{
//    //static FormMcuPinAttribute *s_lastWidget = nullptr;
//    //ASSERT_X(widget, "FormChipConfig", "空指针 ->widget");
//    //if (s_lastWidget)
//    //{
//    //    widget->setParent(ui->uformMcuAttribute);
//    //    ui->ulayoutFormMcuAttribute->replaceWidget(s_lastWidget, widget);
//    //    widget->show();
//    //    s_lastWidget->hide();
//    //} else
//    //{
//    //    ui->ulayoutFormMcuAttribute->addWidget(widget);
//    //}
//    //s_lastWidget = widget;
//}

