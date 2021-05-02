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

#include "FormGpio.h"
#include "ui_FormGpio.h"


FormGpio::FormGpio(QWidget *parent) :
        QWidget(parent), ui(new Ui::FormGpio)
{
    ui->setupUi(this);

    connect(ui->u_tableWidgetGpio, &TableWidgetGpio::signalShowGpioAttributeWidget, this,
            &FormGpio::slotShowGpioAttributeWidget,
            Qt::UniqueConnection);
}

FormGpio::~FormGpio()
{
    delete ui;
}

void FormGpio::setBaseObject(BaseObject *baseObject)
{
    m_baseObject = baseObject;
    ASSERT_X(m_baseObject, u8"FormGpio", u8"空指针-> m_baseObject");

    ui->u_tableWidgetGpio->setBaseObject(m_baseObject);
}

void FormGpio::slotPinSignalClicked(const QString &name, const QString &tag, bool isCanceled)
{
    if (isCanceled)
    {
        ui->u_tableWidgetGpio->addGpioModel(name, tag);
    }
    else
    {
        ui->u_tableWidgetGpio->removeGpioModel(name);
    }
}

void FormGpio::slotShowGpioAttributeWidget(FormGpioAttribute *widget)
{
    static FormGpioAttribute *previousWidget = nullptr;

    if (!widget)
    {
        ui->u_gridLayoutPinAttribute->removeWidget(previousWidget);
    }
    else if (previousWidget && previousWidget != widget && widget)
    {
        widget->setParent(ui->u_widgetPinAttribute);
        ui->u_gridLayoutPinAttribute->replaceWidget(previousWidget, widget);
        widget->show();
        previousWidget->hide();
    }
    else
    {
        ui->u_gridLayoutPinAttribute->addWidget(widget);
    }

    previousWidget = widget;
}

