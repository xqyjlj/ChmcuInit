#ifndef MASTER_H
#define MASTER_H

#include <QMainWindow>
#include "mcu.h"
#include "mcu_tssop24.h"
#include "mcu_scene.h"
namespace Ui
{
    class master;
}

class master : public QMainWindow
{
    Q_OBJECT

public:
    explicit master(QWidget* parent = nullptr);
    ~master();

private:
    Ui::master* ui;
    mcu* fun_mcu = new mcu(this);
};

#endif // MASTER_H
