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

#include "LabelPin.h"
#include <utility>

LabelPin::LabelPin(QWidget *parent) : QLabel(parent)
{
    connect(m_menu, &QMenu::triggered, this, &LabelPin::slotMenuTriggered, Qt::UniqueConnection);
}

void LabelPin::setDirection(enum Direction direction)
{
    m_direction = direction;
    update();
}

void LabelPin::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    QFont font("JetBrains Mono", 15);
    QFontMetrics fm(font);
    QString text = fm.elidedText(this->text(), Qt::ElideRight, 70);
    QPainter painter(this);

    if (m_pinModel.type == "IO")
    {
        if (m_selected)
        {
            painter.setBrush(SelectedColor);
        }
        else
        {
            painter.setBrush(DefaultColor);
        }
    }
    else if (m_pinModel.type == "Power")
    {
        painter.setBrush(PowerColor);
    }
    else
    {
        painter.setBrush(OtherColor);
    }

    painter.drawRect(0, 0, 80, 80);
    painter.setFont(font);
    switch (m_direction)
    {
        case DirectionLeft:
            painter.translate(10, 30);
            painter.drawText(0, 0, text);
            break;
        case DirectionBottom:
            painter.translate(30, 70);
            painter.rotate(-90);
            painter.drawText(0, 0, text);
            break;
        case DirectionRight:
            painter.translate(10, 30);
            painter.drawText(0, 0, text);
            break;
        case DirectionTop:
            painter.translate(30, 70);
            painter.rotate(-90);
            painter.drawText(0, 0, text);
            break;
        default:
            break;
    }
    painter.resetTransform();
}

void LabelPin::setPinModel(XmlPinModel::PinModel_T pinModel)
{
    m_pinModel = std::move(pinModel);
    createActions();
}

void LabelPin::createActions()
{
    if (!m_pinModel.signal.isEmpty())
    {
        for (const XmlPinModel::SignalModel_T &signalModel:  m_pinModel.signal)
        {
            if (!signalModel.ioModes.isEmpty())
            {
                m_menu->addSeparator();

                for (const QString &ioModes: signalModel.ioModes)
                {
                    createAction(ioModes);
                }
            }
            else if (!signalModel.name.isEmpty())
            {
                if (signalModel.name != "GPIO")
                {
                    m_menu->addSeparator();

                    createAction(signalModel.name);
                }
            }
        }
    }
}

void LabelPin::setSelected(bool isSelected)
{
    m_selected = isSelected;
    update();
}

void LabelPin::contextMenuEvent(QContextMenuEvent *ev)
{
    if (m_currentAction)
    {
        m_currentAction->setChecked(true);
    }
    m_menu->exec(ev->globalPos());
}

void LabelPin::createAction(const QString &text)
{
    auto *action = new QAction(m_menu);
    action->setText(text);
    action->setCheckable(true);
    m_menu->addAction(action);
}

void LabelPin::slotMenuTriggered(QAction *action)
{
    static QAction *previousAction = nullptr;
    if (previousAction && previousAction != action)
    {
        previousAction->setChecked(false);
    }
    previousAction = action;

    setSelected(action->isChecked());
    if (action->isChecked())
    {
        emit signalPinSignalClicked(whatsThis().toInt(), action->text());
        m_currentAction = action;
    }
    else
    {
        emit signalPinSignalClicked(whatsThis().toInt(), QString());
        m_currentAction = nullptr;
    }
}

void LabelPin::setBaseObject(BaseObject *baseObject)
{
    m_baseObject = baseObject;
}

[[maybe_unused]] bool LabelPin::isSelected() const
{
    return m_selected;
}

