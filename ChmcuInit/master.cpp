#include "master.h"
#include "ui_master.h"
#include "QGraphicsProxyWidget"
master::master(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::master)
{
    ui->setupUi(this);

    fun_mcu->set_mcu_treeWidget_Resize(ui->mcu_info);
    fun_mcu->set_mcu_treeWidget_Resize(ui->mcu_choose);

    mcu_scene* fun_mcu_scene = new mcu_scene();
    ui->mcu_view->setScene(fun_mcu_scene);
    mcu_tssop24* fun_mcu_tssop24 = new mcu_tssop24();
    fun_mcu_tssop24->resize(400, 400);
    QGraphicsProxyWidget* pWidget = fun_mcu_scene->addWidget(fun_mcu_tssop24); //在场景中添加自定义的ActorWidget，返回一个QGraphicsProxyWidget指针

    pWidget->setPos((ui->mcu_view->width() - fun_mcu_tssop24->width()) / 2, (ui->mcu_view->height() - fun_mcu_tssop24->height()) / 2); //通过QGraphicsProxyWidget指针设置其位置，居中显示
    pWidget->setFlags(QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable); //通过QGraphicsProxyWidget指针设置其可选、可移动、可聚焦

}

master::~master()
{
    delete ui;
}
