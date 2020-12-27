#ifndef MCU_SCENE_H
#define MCU_SCENE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class mcu_scene: public QGraphicsScene
{
public:
    explicit mcu_scene(QObject* parent = nullptr);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
private:
    QGraphicsItem* m_pItemSelected; //鼠标选中的QGraphicsItem
    QPointF m_Offset; //鼠标移动的偏移量
    QPointF m_Pressed; //鼠标按下的位置点
    QPointF m_ItemPos; //鼠标选中的QGraphicsItem在场景中的位置
    bool m_Left_Pressed; //鼠标左键是否按下
    bool m_Mid_Pressed; //鼠标中键是否按下
    bool m_Right_Release;//鼠标右键是否松开
    QGraphicsProxyWidget* m_pProxyWidget;
};

#endif // MCU_SCENE_H
