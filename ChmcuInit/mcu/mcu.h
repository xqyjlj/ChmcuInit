#ifndef MCU_H
#define MCU_H

#include <QObject>
#include <QTreeWidget>
class mcu : public QObject
{
    Q_OBJECT
public:
    explicit mcu(QObject* parent = nullptr);

    void set_mcu_treeWidget_Resize(QTreeWidget* obj);

signals:

public slots:
};

#endif // MCU_H
