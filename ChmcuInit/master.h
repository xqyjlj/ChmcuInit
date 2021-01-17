/*
 * Copyright (c) 2020-2020,  by xqyjlj
 *
 * SPDX-License-Identifier: LGPL
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-15     xqyjlj       the first version
 */
#ifndef MASTER_H
#define MASTER_H

#include <QMainWindow>
#include "mcu_tssop24.h"
#include "mcu_scene.h"
#include "code_use.h"
namespace Ui
{
    class master;
}

class master : public QMainWindow
{
    Q_OBJECT

public:
    explicit master(QWidget *parent = nullptr);
    ~master();

private slots:
    void on_start_project_pressed();

    void on_action_generate_code_triggered();

private:
    Ui::master *ui;
    mcu_scene *fun_mcu_scene;
    mcu_tssop24 *fun_mcu_tssop24;
    code_use *fun_code_use = new code_use();

    void init_mcu(void);
    void init_connect(void);
};

#endif // MASTER_H
