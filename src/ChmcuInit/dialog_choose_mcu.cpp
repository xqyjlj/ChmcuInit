/**
 ** This file is part of the ChmcuInit project.
 ** Copyright 2021 xqyjlj <xqyjlj@126.com>.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **
 ** Change Logs:
 ** Date           Author       Notes                    Email
 ** 2021-03-22     xqyjlj       the first version        xqyjlj@126.com
 **/
#include "dialog_choose_mcu.h"
#include "ui_dialog_choose_mcu.h"
#include <QPushButton>
#include "debug.h"
#include <QFile>

#include <QCoreApplication>
#include <QWebEngineView>
#include <QTextStream>
#include <QWebChannel>
#include "file_manage.h"

CDialog_choose_mcu::CDialog_choose_mcu(QWidget *parent): QDialog(parent), ui(new Ui::CDialog_choose_mcu)
{
    ui->setupUi(this);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("创建"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("取消"));

    read_families_xml();

    add_company();
    add_core();
    add_family();
    add_subfamily();
    add_package();
    add_tableWidget();

    this->setWindowState(Qt::WindowMaximized);

    QFile file(":/markdown/assets/readme.md");
    file.open(QFile::ReadOnly | QFile::Text);
    ui->textBrowser->setMarkdown(file.readAll());
    file.close();

    connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(buttonBox_click(QAbstractButton*)));
}

CDialog_choose_mcu::~CDialog_choose_mcu()
{
    delete ui;
}

/**
 * @brief   read families xml
 *
 * @param   null
 *
 * @return  null
*/
void CDialog_choose_mcu::read_families_xml(void)
{
    QStringList list = NXml::CXml_read().get_all_company_name();
    qsl_company_g << list;
    foreach (QString str, list)
    {
        QStringList list = NXml::CXml_read().get_all_family_name(str);
        qsl_family_g << list;
        foreach (QString str, list)
        {
            QStringList list = NXml::CXml_read().get_all_subfamily_name(str);
            qsl_subfamily_g << list;
            foreach (QString str, list)
            {
                QStringList list = NXml::CXml_read().get_all_mcu_name(str);
                foreach (QString str, list)
                {
                    NModel::CMcu_model model = NXml::CXml_read().get_all_mcu_info(str);
                    ql_mcu_g << model;
                }
            }
        }
    }
}

/**
 * @brief   set company name to treewidget`s company node
 *
 * @param   null
 *
 * @return  null
*/
void CDialog_choose_mcu::add_company(void)
{
    QList<QTreeWidgetItem *> items = ui->treeWidget->findItems(tr("公司"), Qt::MatchExactly);
    if (items.length())
    {
        QTreeWidgetItem *parent = items.at(0);
        parent->setCheckState(0, Qt::Unchecked);

        foreach (QString str, qsl_company_g)
        {
            QTreeWidgetItem *item = new QTreeWidgetItem(parent);
            item->setText(0, str);
            item->setCheckState(0, Qt::Unchecked);
        }
    }
}


/**
 * @brief   find all core in xml
 *
 * @param   null
 *
 * @return  null
*/
void CDialog_choose_mcu::find_core(void)
{
    foreach (NModel::CMcu_model model, ql_mcu_g)
    {
        if ((!model.core.isEmpty()) && (!qs_core_g.contains(model.core)))
        {
            qs_core_g << model.core;
        }
    }
}


/**
 * @brief   set core name to treewidget`s core node
 *
 * @param   null
 *
 * @return  null
*/
void CDialog_choose_mcu::add_core(void)
{
    QList<QTreeWidgetItem *> items = ui->treeWidget->findItems(tr("内核"), Qt::MatchExactly);
    if (items.length())
    {
        QTreeWidgetItem *parent = items.at(0);
        parent->setCheckState(0, Qt::Unchecked);

        find_core();

        foreach (QString str, qs_core_g)
        {
            QTreeWidgetItem *item = new QTreeWidgetItem(parent);
            item->setText(0, str);
            item->setCheckState(0, Qt::Unchecked);
        }
    }
}

/**
 * @brief   set family name to treewidget`s family node
 *
 * @param   null
 *
 * @return  null
*/
void CDialog_choose_mcu::add_family(void)
{
    QList<QTreeWidgetItem *> items = ui->treeWidget->findItems(tr("系列"), Qt::MatchExactly);
    if (items.length())
    {
        QTreeWidgetItem *parent = items.at(0);
        parent->setCheckState(0, Qt::Unchecked);

        foreach (QString str, qsl_family_g)
        {
            QTreeWidgetItem *item = new QTreeWidgetItem(parent);
            item->setText(0, str);
            item->setCheckState(0, Qt::Unchecked);
        }
    }
}

/**
 * @brief   set subfamily name to treewidget`s subfamily node
 *
 * @param   null
 *
 * @return  null
*/
void CDialog_choose_mcu::add_subfamily(void)
{
    QList<QTreeWidgetItem *> items = ui->treeWidget->findItems(tr("产品"), Qt::MatchExactly);
    if (items.length())
    {
        QTreeWidgetItem *parent = items.at(0);
        parent->setCheckState(0, Qt::Unchecked);

        foreach (QString str, qsl_subfamily_g)
        {
            QTreeWidgetItem *item = new QTreeWidgetItem(parent);
            item->setText(0, str);
            item->setCheckState(0, Qt::Unchecked);
        }
    }
}

/**
 * @brief   find all package in xml
 *
 * @param   null
 *
 * @return  null
*/
void CDialog_choose_mcu::find_package(void)
{
    foreach (NModel::CMcu_model model, ql_mcu_g)
    {
        if ((!model.packagename.isEmpty()) && (!qs_package_g.contains(model.packagename)))
        {
            qs_package_g << model.packagename;
        }
    }
}

/**
 * @brief   set package name to treewidget`s package node
 *
 * @param   null
 *
 * @return  null
*/
void CDialog_choose_mcu::add_package(void)
{
    QList<QTreeWidgetItem *> items = ui->treeWidget->findItems(tr("封装"), Qt::MatchExactly);
    if (items.length())
    {
        QTreeWidgetItem *parent = items.at(0);
        parent->setCheckState(0, Qt::Unchecked);

        find_package();

        foreach (QString str, qs_package_g)
        {
            QTreeWidgetItem *item = new QTreeWidgetItem(parent);
            item->setText(0, str);
            item->setCheckState(0, Qt::Unchecked);
        }
    }
}

/**
 * @brief   add mcu info to QTableWidget
 *
 * @param   null
 *
 * @return  null
*/
void CDialog_choose_mcu::add_tableWidget(void)
{
    foreach (NModel::CMcu_model model, ql_mcu_g)
    {
        ui->tableWidget->add_mcu_model(model);
    }
}

/**
 * @brief   SLOT of buttonBox click
 *
 * @param   null
 *
 * @return  null
*/
void CDialog_choose_mcu::buttonBox_click(QAbstractButton *button)
{
    if (button->text() == tr("创建"))
    {
        QList<QTableWidgetItem *> items =  ui->tableWidget->selectedItems();
        if (!items.isEmpty())
        {
            emit create_mcu_project(items.at(0)->text());
        }

    }
}

void CDialog_choose_mcu::on_tableWidget_itemSelectionChanged()
{
    QList<QTableWidgetItem *> items =  ui->tableWidget->selectedItems();
    if (!items.isEmpty())
    {
        QString path = QCoreApplication::applicationDirPath() + "/origin/families/chip/" + items.at(0)->text() + "/readme.md";
        if (NFile::CFile_manage().get_mcu_pack_list().contains(items.at(0)->text()))
        {
            QFile file(path);
            file.open(QFile::ReadOnly | QFile::Text);
            ui->textBrowser->setMarkdown(file.readAll());
            file.close();
        }
        else
        {
            QFile file(":/markdown/assets/no_mcu_md.md");
            file.open(QFile::ReadOnly | QFile::Text);
            QString md = file.readAll();
            md = md.arg(path);
            ui->textBrowser->setMarkdown(md);
            file.close();
        }
    }
}
