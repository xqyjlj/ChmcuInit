#ifndef MASTER_H
#define MASTER_H

#include <QMainWindow>
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

private slots:
    void on_start_project_pressed();

private:
    Ui::master* ui;

    void init_mcu(void);
};

#endif // MASTER_H
