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
 ** 2021-03-20     xqyjlj       the first version        xqyjlj@126.com
 **/
#include "WidgetLQFP48.h"
#include "ui_WidgetLQFP48.h"
#include <QList>
#include "Debug.h"
#include <QMenu>


WidgetLQFP48::WidgetLQFP48(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::WidgetLQFP48)
{
    ui->setupUi(this);
    mpins = this->findChildren<LabelPin*>();
    std::sort(mpins.begin(), mpins.end(), [](const LabelPin * infoA, const LabelPin * infoB)
    {
        QString infoAstr = infoA->objectName().split("_").last();
        QString infoBstr = infoB->objectName().split("_").last();
        return infoAstr.toInt() < infoBstr.toInt();
    });
    for (int i = 0; i < 12; i++)
    {
        mpins.at(i)->setDirection(LabelPin::Direction::DirectionLeft);
    }
    for (int i = 12; i < 24; i++)
    {
        mpins.at(i)->setDirection(LabelPin::Direction::DirectionBottom);
    }
    for (int i = 24; i < 36; i++)
    {
        mpins.at(i)->setDirection(LabelPin::Direction::DirectionRight);
    }
    for (int i = 36; i < 48; i++)
    {
        mpins.at(i)->setDirection(LabelPin::Direction::DirectionTop);
    }
}

WidgetLQFP48::~WidgetLQFP48()
{
    delete ui;
}

/**
 * @brief   设置基础对象
 *
 * @param   baseObject: 基础对象
 *
 * @return  null
*/
void WidgetLQFP48::setBaseObject(BaseObject* baseObject)
{
    mbaseObject = baseObject;
    ASSERT_X(mbaseObject, "WidgetLQFP48", "空指针-> mbaseObject");
    load();
}

/**
 * @brief   加载
 *
 * @param   null
 *
 * @return  null
*/
void WidgetLQFP48::load(void)
{
    QList<Model::XmlPinModel>* list = mbaseObject->getPinModels();
    if (list->length() != 48)
    {
        return;
    }
    else
    {
        for (int i = 0; i < 48; i++)
        {
            mpins.at(i)->setWhatsThis(QString::number(i + 1));
            mpins.at(i)->setText(list->at(i).name);
            mpins.at(i)->setToolTip("(" + list->at(i).position + ") " + list->at(i).name);
            mpins.at(i)->setPinModel(list->at(i));
            mpins.at(i)->installEventFilter(this);
        }
    }
}
/**
 * @brief   如果已安装此对象作为监视对象的事件过滤器，则过滤事件。
 *
 * @param   obj: QObject对象
 *          event：事件
 *
 * @return  null
*/
bool WidgetLQFP48::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);  // 事件转换
        if (mouseEvent->button() == Qt::LeftButton)
        {
            if (obj->objectName().contains("label_"))
            {
                LabelPin* pin = reinterpret_cast<LabelPin*>(obj);

                QVector<bool> bools(48, false);
                if (pin->getSelect())
                {
                    bools[pin->whatsThis().toInt() - 1] = false;
                }
                else
                {
                    bools[pin->whatsThis().toInt() - 1] = true;
                }
                emit pinClicked(bools);
                selectPin(bools);
            }
        }
    }
    return QWidget::eventFilter(obj, event);
}
/**
 * @brief   选中引脚
 *
 * @param   bools: 装有所有引脚被选中的bool状态
 *
 * @return  null
*/
void WidgetLQFP48::selectPin(QVector<bool> bools)
{
    if (bools.length() == 48)
    {
        for (int i = 0; i < 48; i++)
        {
            mpins.at(i)->setSelect(bools.at(i));
        }
    }
}
