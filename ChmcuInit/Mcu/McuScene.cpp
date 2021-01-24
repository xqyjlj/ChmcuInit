/*
 * Copyright (c) 2020-2020,  by xqyjlj
 *
 * SPDX-License-Identifier: LGPL
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-12-264     xqyjlj       the first version
 */
#include "McuScene.h"
#include <QDebug>
#include <QGraphicsProxyWidget>
#include <QPointF>
McuScene::McuScene(QObject* parent): QGraphicsScene(parent)
{

}

void McuScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mousePressEvent(event);

    if(event->button() == Qt::LeftButton)
    {
        m_pItemSelected = nullptr;
        foreach(QGraphicsItem* item, items(event->scenePos()))//循环查找当前鼠标位置点下所有的Item
        {
            if(item->type() == QGraphicsProxyWidget::Type)//判断此Item是否为添加的ActorWidget创建的QGraphicsProxyWidget
            {
                m_Left_Pressed = true;
                m_Pressed = event->scenePos(); //记录此时鼠标在场景中位置点
                m_pItemSelected = item; //选中的Item

                m_pProxyWidget = qgraphicsitem_cast<QGraphicsProxyWidget*>(item);
                m_ItemPos = m_pProxyWidget->scenePos(); //QGraphicsProxyWidget的位置点

                break;
            }
        }
    }
    else if (event->button() == Qt::MidButton)
    {
        m_pItemSelected = nullptr;
        foreach(QGraphicsItem* item, items(event->scenePos()))//循环查找当前鼠标位置点下所有的Item
        {
            if(item->type() == QGraphicsProxyWidget::Type)//判断此Item是否为添加的ActorWidget创建的QGraphicsProxyWidget
            {
                m_Mid_Pressed = true;
                m_pItemSelected = item; //选中的Item
                m_pProxyWidget = qgraphicsitem_cast<QGraphicsProxyWidget*>(item);
                break;
            }
        }
    }
}

void McuScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mouseMoveEvent(event);

    if(m_pItemSelected != nullptr)
    {
        if(m_Left_Pressed)
        {
            m_Offset = event->scenePos() - m_Pressed; //鼠标移动的偏移量
            m_pItemSelected->setPos(m_ItemPos + m_Offset); //结合鼠标按下时Item的位置点，重新设置Item的位置点
        }
        if(m_Mid_Pressed == true && m_Right_Release == true)
        {
            if(m_pProxyWidget != nullptr)
            {
                m_ItemPos = m_pProxyWidget->scenePos(); //QGraphicsProxyWidget的位置点
                if(event->lastScenePos().y() > event->scenePos().y())
                {
                    QWidget* widget = m_pProxyWidget->widget();
                    widget->resize(widget->width() + 8, widget->height() + 8);
                    m_pItemSelected->setPos(m_ItemPos.x() - 4, m_ItemPos.y() - 4);
                }
                else
                {
                    QWidget* widget = m_pProxyWidget->widget();
                    widget->resize(widget->width() - 8, widget->height() - 8);
                    m_pItemSelected->setPos(m_ItemPos.x() + 4, m_ItemPos.y() + 4);
                }
            }

        }
    }
}

void McuScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mouseReleaseEvent(event);

    if(event->button() == Qt::LeftButton)
    {
        m_Left_Pressed = false;
        if(m_pItemSelected != nullptr)
        {
            m_pItemSelected = nullptr; //鼠标释放时将选中的Item设为空
        }
    }
    else if (event->button() == Qt::MidButton)
    {
        m_Mid_Pressed = false;
        m_Right_Release = false;
        if(m_pItemSelected != nullptr)
        {
            m_pItemSelected = nullptr; //鼠标释放时将选中的Item设为空
        }
        if(m_pProxyWidget != nullptr)
        {
            m_pProxyWidget = nullptr; //鼠标释放时将选中的Widget设为空
        }
    }
    else if(event->button() == Qt::RightButton)
    {
        if(m_Mid_Pressed)
        {
            m_Right_Release = true;
        }
    }
}
