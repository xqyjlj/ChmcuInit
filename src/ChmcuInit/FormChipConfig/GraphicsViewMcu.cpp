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
#include "GraphicsViewMcu.h"

#define VIEW_CENTER viewport()->rect().center()
#define VIEW_WIDTH  viewport()->rect().width()
#define VIEW_HEIGHT viewport()->rect().height()


GraphicsViewMcu::GraphicsViewMcu(QWidget* parent)
    : QGraphicsView(parent),
      mtranslateButton(Qt::LeftButton),
      mtranslateSpeed(1.0),
      mzoomDelta(0.1),
      mmouseTranslate(false),
      mscale(1.0)
{
    // 去掉滚动条
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHint(QPainter::Antialiasing);

    setSceneRect(INT_MIN / 2, INT_MIN / 2, INT_MAX, INT_MAX);
    centerOn(0, 0);
    setDragMode(QGraphicsView::NoDrag);
}

/**
 * @brief   设置平移速度
 *
 * @param   speed: 平移速度
 *
 * @return  null
*/
void GraphicsViewMcu::setTranslateSpeed(qreal speed)
{
    // 建议速度范围
    Q_ASSERT_X(speed >= 0.0 && speed <= 2.0,
               "GraphicsViewMcu::setTranslateSpeed", "Speed should be in range [0.0, 2.0].");
    mtranslateSpeed = speed;
}

/**
 * @brief   获得平移速度
 *
 * @param   null
 *
 * @return  平移速度
*/
qreal GraphicsViewMcu::getTranslateSpeed() const
{
    return mtranslateSpeed;
}

/**
 * @brief   设置缩放的增量
 *
 * @param   delta: 缩放的增量
 *
 * @return  null
*/
void GraphicsViewMcu::setZoomDelta(qreal delta)
{
    // 建议增量范围
    Q_ASSERT_X(delta >= 0.0 && delta <= 1.0,
               "GraphicsViewMcu::setZoomDelta", "Delta should be in range [0.0, 1.0].");
    mzoomDelta = delta;
}

/**
 * @brief   获得缩放的增量
 *
 * @param   null
 *
 * @return  缩放的增量
*/
qreal GraphicsViewMcu::getZoomDelta() const
{
    return mzoomDelta;
}

/**
 * @brief   按键事件
 *
 * @param   event: 按键事件
 *
 * @return  null
*/
void GraphicsViewMcu::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
    case Qt::Key_Up:
        translate(QPointF(0, -2));  // 上移
        break;
    case Qt::Key_Down:
        translate(QPointF(0, 2));  // 下移
        break;
    case Qt::Key_Left:
        translate(QPointF(-2, 0));  // 左移
        break;
    case Qt::Key_Right:
        translate(QPointF(2, 0));  // 右移
        break;
    case Qt::Key_Plus:  // 放大
        zoomIn();
        break;
    case Qt::Key_Minus:  // 缩小
        zoomOut();
        break;
    case Qt::Key_Space:  // 逆时针旋转
        rotate(-90);
        break;
    case Qt::Key_Enter:  // 顺时针旋转
    case Qt::Key_Return:
        rotate(5);
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

/**
 * @brief   鼠标移动事件
 *
 * @param   event: 鼠标事件
 *
 * @return  null
*/
void GraphicsViewMcu::mouseMoveEvent(QMouseEvent* event)
{
    if (mmouseTranslate)
    {
        QPointF mouseDelta = mapToScene(event->pos()) - mapToScene(mlastMousePos);
        translate(mouseDelta);
    }

    mlastMousePos = event->pos();

    QGraphicsView::mouseMoveEvent(event);
}

/**
 * @brief   鼠标按下事件
 *
 * @param   event: 鼠标事件
 *
 * @return  null
*/
void GraphicsViewMcu::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == mtranslateButton)
    {
        // 当光标底下没有 item 时才能移动

        mmouseTranslate = true;
        mlastMousePos = event->pos();
    }
    QGraphicsView::mousePressEvent(event);
}

/**
 * @brief   鼠标松开事件
 *
 * @param   event: 鼠标事件
 *
 * @return  null
*/
void GraphicsViewMcu::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == mtranslateButton)
        mmouseTranslate = false;

    QGraphicsView::mouseReleaseEvent(event);
}

/**
 * @brief   滚轮事件
 *
 * @param   event: 滚轮事件
 *
 * @return  null
*/
void GraphicsViewMcu::wheelEvent(QWheelEvent* event)
{
    // 滚轮的滚动量
    QPoint scrollAmount = event->angleDelta();
    // 正值表示滚轮远离使用者放大负值表示朝向使用者缩小
    scrollAmount.y() > 0 ? zoomIn() : zoomOut();
}

/**
 * @brief   放大
 *
 * @param   null
 *
 * @return  null
*/
void GraphicsViewMcu::zoomIn()
{
    zoom(1 + mzoomDelta);
}

/**
 * @brief   缩小
 *
 * @param   null
 *
 * @return  null
*/
void GraphicsViewMcu::zoomOut()
{
    zoom(1 - mzoomDelta);
}

/**
 * @brief   按比例缩小
 *
 * @param   scaleFactor: 缩放的比例因子
 *
 * @return  null
*/
void GraphicsViewMcu::zoom(float scaleFactor)
{
    // 防止过小或过大
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
    mscale *= scaleFactor;
}

/**
 * @brief   平移
 *
 * @param   scaleFactor: 坐标
 *
 * @return  null
*/
void GraphicsViewMcu::translate(QPointF delta)
{
    // 根据当前 zoom 缩放平移数
    delta *= mscale;
    delta *= mtranslateSpeed;

    // view 根据鼠标下的点作为锚点来定位 scene
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    QPoint newCenter(VIEW_WIDTH / 2 - delta.x(),  VIEW_HEIGHT / 2 - delta.y());
    centerOn(mapToScene(newCenter));

    // scene 在 view 的中心点作为锚点
    setTransformationAnchor(QGraphicsView::AnchorViewCenter);
}
