/*
 * Copyright (c) 2020-2020,  by xqyjlj
 *
 * SPDX-License-Identifier: LGPL
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-15     xqyjlj       the first version
 */
#include "master.h"
#include "ui_master.h"
#include "QGraphicsProxyWidget"
#include <QSplitter>
#include <QDebug>
#include <QMessageBox>
master::master(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::master)
{
    ui->setupUi(this);
    init_mcu();
    ui->pin_tree->set_xml_file_path(":/mcu/hc32/res/db/mcu/HDSC/HC32/HC32F002/HC32F002D4P8.xml");
    init_connect();
}

master::~master()
{
    delete ui;
}

void master::init_mcu(void)
{
    QHeaderView* head = ui->mcu_info->header();
    head->setSectionResizeMode(QHeaderView::ResizeToContents);

    head = ui->mcu_choose->header();
    head->setSectionResizeMode(QHeaderView::ResizeToContents);

    fun_mcu_scene = new McuScene();
    ui->mcu_view->setScene(fun_mcu_scene);
    fun_mcu_tssop24 = new McuTssop24();
    fun_mcu_tssop24->resize(400, 400);
    fun_mcu_scene->addWidget(fun_mcu_tssop24);

    QSplitter* splitter1 = new QSplitter(Qt::Vertical);
    splitter1->setStretchFactor(0, 2);
    splitter1->setStretchFactor(1, 1);
    splitter1->setChildrenCollapsible(false);

    splitter1->addWidget(ui->mcu_view);
    splitter1->addWidget(ui->pin_table);

    QSplitter* splitter2 = new QSplitter(Qt::Horizontal);
    splitter2->setStretchFactor(0, 1);
    splitter2->setStretchFactor(1, 3);
    splitter2->setStretchFactor(2, 1);
    splitter2->setChildrenCollapsible(false);

    splitter2->addWidget(ui->tabWidget);
    splitter2->addWidget(splitter1);
    splitter2->addWidget(ui->tabWidget_2);

    ui->stackedWidget->layout()->replaceWidget(ui->stackedWidget->widget(1), splitter2);
    ui->stackedWidget->widget(1)->hide();
}

void master::init_connect(void)
{
    connect(fun_mcu_tssop24, SIGNAL(item_click(int, int)), ui->pin_tree, SLOT(change_item_color(int, int)));
    connect(ui->pin_tree, SIGNAL(item_doubled_clicked_info(int, int, bool)), fun_mcu_tssop24, SLOT(change_pin_color(int, int, bool)));
}

void master::on_start_project_pressed()
{
    if(ui->mcu_info->currentItem())
    {
        ui->stackedWidget->setCurrentIndex(1);
    }
    else
    {
        QMessageBox::critical(this, "错误", "请选择正确的芯片型号", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
}

void master::on_action_generate_code_triggered()
{

}
