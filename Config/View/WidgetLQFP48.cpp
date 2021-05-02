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
 ** 2021-04-30     xqyjlj       the first version        xqyjlj@126.com
 **/

#include "WidgetLQFP48.h"
#include "ui_WidgetLQFP48.h"

WidgetLQFP48::WidgetLQFP48(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::WidgetLQFP48)
{
    ui->setupUi(this);

    QPalette pale = palette();
    pale.setColor(QPalette::Window, QColor("white"));
    setPalette(pale);

    findLabel();
    setLabelComment();
}

WidgetLQFP48::~WidgetLQFP48()
{
    delete ui;
}

void WidgetLQFP48::setBaseObject(BaseObject *baseObject)
{
    m_baseObject = baseObject;
    ui->u_labelMcuBody->setText(m_baseObject->getMcuName());
    setLabelPin();
}

void WidgetLQFP48::findLabel()
{
    QList<QLabel *> labels = this->findChildren<QLabel *>();

    for (QLabel *label :labels)
    {
        if (label->objectName().contains(u8"labelPin"))
        {
            m_labelPins << dynamic_cast<LabelPin *>(label);
        }
        else if (label->objectName().contains(u8"labelComment"))
        {
            m_labelComment << dynamic_cast<LabelComment *>(label);
        }
    }

    std::sort(m_labelPins.begin(), m_labelPins.end(), [](const LabelPin *info1, const LabelPin *info2) {
        QString infoStr1 = info1->objectName().split("_").last();
        QString infoStr2 = info2->objectName().split("_").last();
        return infoStr1.toInt() < infoStr2.toInt();
    });

    std::sort(m_labelComment.begin(), m_labelComment.end(), [](const LabelComment *info1, const LabelComment *info2) {
        QString infoStr1 = info1->objectName().split("_").last();
        QString infoStr2 = info2->objectName().split("_").last();
        return infoStr1.toInt() < infoStr2.toInt();
    });
}

void WidgetLQFP48::setLabelPin()
{
    QList<XmlPinModel::PinModel_T> pinModels = m_baseObject->getPinModels();

    if (pinModels.length() != 48)
    {
        return;
    }
    for (int i = 0; i < 48; i++)
    {
        m_labelPins.at(i)->setBaseObject(m_baseObject);
        m_labelPins.at(i)->setPinModel(pinModels.at(i));
        m_labelPins.at(i)->setWhatsThis(QString::number(i + 1));
        m_labelPins.at(i)->setText(pinModels.at(i).name);
        m_labelPins.at(i)->setToolTip("(" + pinModels.at(i).position + ") " + pinModels.at(i).name);
        m_labelPins.at(i)->installEventFilter(this);

        connect(m_labelPins.at(i), &LabelPin::signalPinSignalClicked, this, &WidgetLQFP48::slotPinSignalClicked,
                Qt::UniqueConnection);

        if (i >= 0 && i <= 11)
        {
            m_labelPins.at(i)->setDirection(LabelPin::DirectionLeft);
        }
        else if (i >= 12 && i <= 23)
        {
            m_labelPins.at(i)->setDirection(LabelPin::DirectionBottom);
        }
        else if (i >= 24 && i <= 35)
        {
            m_labelPins.at(i)->setDirection(LabelPin::DirectionRight);
        }
        else if (i >= 36 && i <= 47)
        {
            m_labelPins.at(i)->setDirection(LabelPin::DirectionTop);
        }
    }
}

bool WidgetLQFP48::eventFilter(QObject *obj, QEvent *event)
{
    //if (event->type() == QEvent::MouseButtonPress)
    //{
    //    auto *mouseEvent = dynamic_cast<QMouseEvent *>(event);
    //    if (mouseEvent->button() == Qt::LeftButton)
    //    {
    //        if (obj->objectName().contains("ulabelPin"))
    //        {
    //            auto *labelPin = reinterpret_cast<LabelPin *>(obj);
    //
    //            labelPin->setSelected(!labelPin->getSelected());
    //
    //            emit pinClicked(labelPin->whatsThis().toInt() - 1, labelPin->getSelected());
    //        }
    //    }
    //}
    return QWidget::eventFilter(obj, event);
}

void WidgetLQFP48::setLabelComment()
{
    if (m_labelComment.length() != 48)
    {
        return;
    }

    for (int i = 0; i < 48; i++)
    {
        if (i >= 0 && i <= 11)
        {
            m_labelComment.at(i)->setDirection(LabelComment::DirectionLeft);
        }
        else if (i >= 12 && i <= 23)
        {
            m_labelComment.at(i)->setDirection(LabelComment::DirectionBottom);
        }
        else if (i >= 24 && i <= 35)
        {
            m_labelComment.at(i)->setDirection(LabelComment::DirectionRight);
        }
        else if (i >= 36 && i <= 47)
        {
            m_labelComment.at(i)->setDirection(LabelComment::DirectionTop);
        }
    }
}

void WidgetLQFP48::slotPinSignalClicked(int index, const QString &text)
{
    m_labelComment.at(index - 1)->setText(text);
    if (text.isEmpty())
    {
        emit signalPinSignalClicked(m_labelPins.at(index - 1)->text(), text, false);
    }
    else
    {
        emit signalPinSignalClicked(m_labelPins.at(index - 1)->text(), text, true);
    }
}

