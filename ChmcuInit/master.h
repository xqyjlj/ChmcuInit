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
#include "McuTssop24.h"
#include "McuScene.h"
#include "CodeDriver.h"
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

    void on_action_generate_code_triggered();

private:
    Ui::master* ui;
    McuScene* fun_mcu_scene;
    McuTssop24* fun_mcu_tssop24;
    CodeDriver* fun_code_driver = new CodeDriver(this);

    void init_mcu(void);
    void init_connect(void);
};

#endif // MASTER_H
