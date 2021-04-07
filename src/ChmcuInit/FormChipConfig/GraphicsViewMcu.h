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
 ** 2021-03-31     xqyjlj       the first version        xqyjlj@126.com
 **/
#ifndef GRAPHICSVIEWMCUH
#define GRAPHICSVIEWMCUH

#include <QObject>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>

/**
 * @brief The GraphicsViewMcu class
 *
 * 可移动放大缩小移动界面
 */
class GraphicsViewMcu : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicsViewMcu(QWidget* parent = nullptr);

    /**
     * @brief   设置平移速度
     *
     * @param   speed: 平移速度
     *
     * @return  null
    */
    void setTranslateSpeed(qreal speed);

    /**
     * @brief   获得平移速度
     *
     * @param   null
     *
     * @return  平移速度
    */
    qreal getTranslateSpeed() const;

    /**
     * @brief   设置缩放的增量
     *
     * @param   delta: 缩放的增量
     *
     * @return  null
    */
    void setZoomDelta(qreal delta);

    /**
     * @brief   获得缩放的增量
     *
     * @param   null
     *
     * @return  缩放的增量
    */
    qreal getZoomDelta() const;

public slots:

    /**
     * @brief   放大
     *
     * @param   null
     *
     * @return  null
    */
    void zoomIn();

    /**
     * @brief   缩小
     *
     * @param   null
     *
     * @return  null
    */
    void zoomOut();

    /**
     * @brief   按比例缩小
     *
     * @param   scaleFactor: 缩放的比例因子
     *
     * @return  null
    */
    void zoom(float scaleFactor);

    /**
     * @brief   平移
     *
     * @param   scaleFactor: 坐标
     *
     * @return  null
    */
    void translate(QPointF delta);

signals:

private:
    Qt::MouseButton mtranslateButton;       // 平移按钮
    qreal mtranslateSpeed;                  // 平移速度
    qreal mzoomDelta;                       // 缩放的增量
    bool mmouseTranslate;                   // 平移标识
    QPoint mlastMousePos;                   // 鼠标最后按下的位置
    qreal mscale;                           // 缩放值

protected:

    /**
     * @brief   按键事件
     *
     * @param   event: 按键事件
     *
     * @return  null
    */
    virtual void keyPressEvent(QKeyEvent* event) override;

    /**
     * @brief   鼠标移动事件
     *
     * @param   event: 鼠标事件
     *
     * @return  null
    */
    virtual void mouseMoveEvent(QMouseEvent* event) override;

    /**
     * @brief   鼠标按下事件
     *
     * @param   event: 鼠标事件
     *
     * @return  null
    */
    virtual void mousePressEvent(QMouseEvent* event) override;

    /**
     * @brief   鼠标松开事件
     *
     * @param   event: 鼠标事件
     *
     * @return  null
    */
    virtual void mouseReleaseEvent(QMouseEvent* event) override;

    /**
     * @brief   滚轮事件
     *
     * @param   event: 滚轮事件
     *
     * @return  null
    */
    virtual void wheelEvent(QWheelEvent* event) override;
};

#endif // GRAPHICSVIEWH
