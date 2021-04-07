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
 ** 2021-03-29     xqyjlj       the first version        xqyjlj@126.com
 **/
#ifndef LABELPIN_H
#define LABELPIN_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QPaintEvent>

#include "Model.h"
/**
 * @brief The LabelPin class
 *
 * 继承自QLabel，做芯片的引脚使用
 */
class LabelPin : public QLabel
{
    Q_OBJECT
public:
    enum Direction
    {
        DirectionTop = 0,   //上面
        DirectionBottom,    //下面
        DirectionLeft,      //左边
        DirectionRight      //右边
    };
    enum Color
    {
        ColorDefault = 0,   //默认颜色            -粉蓝色
        ColorPower,         //电源引脚颜色        -轻黄菊色1
        ColorOther,         //其他引脚颜色        -深橄榄绿色3
        ColorSelected,      //被选中引脚颜色      -钢铁蓝
    };
public:
    explicit LabelPin(QWidget* parent = nullptr);

    /**
     * @brief   设置文字方向
     *
     * @param   dir: 文字方向
     *
     * @return  null
    */
    void setDirection(enum Direction dir);

    /**
     * @brief   设置引脚模型
     *
     * @param   model: 引脚模型
     *
     * @return  null
    */
    void setPinModel(Model::XmlPinModel model);

    /**
     * @brief   获得引脚模型
     *
     * @param   null
     *
     * @return  Model::XmlPinModel: 引脚模型
    */
    Model::XmlPinModel getPinModel(void) const;

    /**
     * @brief   获得引脚信号
     *
     * @param   null
     *
     * @return  QStringList: 引脚模型
    */
    QStringList getSignals(void) const;

    /**
     * @brief   设置选中信号
     *
     * @param   _bool: 是否选中
     *
     * @return  null
    */
    void setSelect(bool _bool);

    /**
     * @brief   获得选中信号
     *
     * @param   null
     *
     * @return  bool: 是否选中
    */
    bool getSelect(void) const;
signals:

private:
    /**
     * @brief   解析引脚信号
     *
     * @param   signalModel 引脚信号
     *
     * @return  null
    */
    bool parseSignals(QList<Model::XmlPinModel::SignalModel> signalModels);
private:
    const QColor DefaultColor = QColor(176, 224, 230);      //粉蓝色
    const QColor PowerColor = QColor(255, 236, 139);        //轻黄菊色1
    const QColor OtherColor = QColor(162, 205, 90);         //深橄榄绿色3
    const QColor SelectedColor = QColor(70, 130, 180);      //钢铁蓝

    enum Direction mdirection = DirectionLeft;  //方向
    Model::XmlPinModel mpinModel;               //引脚模型
    QStringList msignals;                       //硬件信号
    bool mselected = false;                     //选中状态

protected:
    /**
     * @brief   重绘事件
     *
     * @param   e: 绘画事件
     *
     * @return  null
    */
    virtual void paintEvent(QPaintEvent* e) override;
};



#endif // LABELPIN_H
