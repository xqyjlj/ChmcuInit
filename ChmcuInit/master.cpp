#include "master.h"
#include "ui_master.h"
#include "QGraphicsProxyWidget"
#include <QSplitter>
master::master(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::master)
{
    ui->setupUi(this);
    fun_mcu = new mcu(this);

    fun_mcu->set_mcu_treeWidget_Resize(ui->mcu_info);
    fun_mcu->set_mcu_treeWidget_Resize(ui->mcu_choose);

    mcu_scene* fun_mcu_scene = new mcu_scene();
    ui->mcu_view->setScene(fun_mcu_scene);
    mcu_tssop24* fun_mcu_tssop24 = new mcu_tssop24();
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

    ui->stackedWidget->layout()->replaceWidget(ui->page_2, splitter2);
    ui->page_2->hide();
}

master::~master()
{
    delete ui;
}
