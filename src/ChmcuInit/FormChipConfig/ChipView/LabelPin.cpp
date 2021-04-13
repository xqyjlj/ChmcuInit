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
#include "LabelPin.h"
#include "Debug.h"


LabelPin::LabelPin(QWidget* parent) : QLabel(parent)
{

}
/**
 * @brief   设置文字方向
 *
 * @param   dir: 文字方向
 *
 * @return  null
*/
void LabelPin::setDirection(enum Direction dir)
{
    mdirection = dir;
    this->update();
}
/**
 * @brief   重绘事件
 *
 * @param   e: 绘画事件
 *
 * @return  null
*/
void LabelPin::paintEvent(QPaintEvent* e)
{
    Q_UNUSED(e);

    QFont font("JetBrains Mono", 15);
    QFontMetrics fm(font);
    QString text = fm.elidedText(this->text(), Qt::ElideRight, 70);
    QPainter painter(this);

    if (mpinModel.type == "IO")
    {
        if (mselected)
        {
            painter.setBrush(SelectedColor);
        }
        else
        {
            painter.setBrush(DefaultColor);
        }
    }
    else if (mpinModel.type == "Power")
    {
        painter.setBrush(PowerColor);
    }
    else
    {
        painter.setBrush(OtherColor);
    }


    painter.drawRect(0, 0, 80, 80);
    painter.setFont(font);
    switch (mdirection)
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

/**
 * @brief   设置引脚模型
 *
 * @param   model: 引脚模型
 *
 * @return  null
*/
void LabelPin::setPinModel(Model::XmlPinModel model)
{
    mpinModel = model;
    parseSignals(mpinModel.signal);
}
/**
 * @brief   获得引脚模型
 *
 * @param   null
 *
 * @return  Model::XmlPinModel: 引脚模型
*/
Model::XmlPinModel LabelPin::getPinModel() const
{
    return mpinModel;
}
/**
 * @brief   获得引脚信号
 *
 * @param   null
 *
 * @return  QStringList: 引脚模型
*/
QStringList LabelPin::getSignals(void) const
{
    return msignals;
}
/**
 * @brief   解析引脚信号
 *
 * @param   signalModel 引脚信号
 *
 * @return  null
*/
bool LabelPin::parseSignals(QList<Model::XmlPinModel::SignalModel> signalModels)
{
    if (!signalModels.isEmpty())
    {
        foreach (Model::XmlPinModel::SignalModel signal, signalModels)
        {
            if (!signal.ioModes.isEmpty())
            {
                msignals << signal.ioModes.split(",");
            }
            if (!signal.name.isEmpty())
            {
                if (signal.name != "GPIO")
                {
                    msignals << signal.name;
                }
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}
/**
 * @brief   设置选中信号
 *
 * @param   _bool: 是否选中
 *
 * @return  null
*/
void LabelPin::setSelect(bool _bool)
{
    mselected = _bool;
    update();
}
/**
 * @brief   获得选中信号
 *
 * @param   null
 *
 * @return  bool: 是否选中
*/
bool LabelPin::getSelect(void) const
{
    return mselected;
}
