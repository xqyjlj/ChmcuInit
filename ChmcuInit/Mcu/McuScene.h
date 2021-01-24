/*
 * Copyright (c) 2020-2020,  by xqyjlj
 *
 * SPDX-License-Identifier: LGPL
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-15     xqyjlj       the first version
 */
#ifndef MCUSCENE_H
#define MCUSCENE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class McuScene: public QGraphicsScene
{
public:
    explicit McuScene(QObject* parent = nullptr);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
private:
    QGraphicsItem* m_pItemSelected = nullptr; //鼠标选中的QGraphicsItem
    QPointF m_Offset; //鼠标移动的偏移量
    QPointF m_Pressed; //鼠标按下的位置点
    QPointF m_ItemPos; //鼠标选中的QGraphicsItem在场景中的位置
    bool m_Left_Pressed = false; //鼠标左键是否按下
    bool m_Mid_Pressed = false; //鼠标中键是否按下
    bool m_Right_Release = false;//鼠标右键是否松开
    QGraphicsProxyWidget* m_pProxyWidget = nullptr;
};

#endif // MCUSCENE_H
