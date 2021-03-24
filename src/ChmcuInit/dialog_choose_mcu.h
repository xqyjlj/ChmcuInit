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
#ifndef DIALOG_CHOOSE_MCU_H
#define DIALOG_CHOOSE_MCU_H

#include <QDialog>
#include "xml_read.h"
#include <QAbstractButton>
namespace Ui
{
class CDialog_choose_mcu;
}

class CDialog_choose_mcu : public QDialog
{
    Q_OBJECT

public:
    explicit CDialog_choose_mcu(QWidget *parent = nullptr);
    ~CDialog_choose_mcu();

private:

    /**
     * @brief   read families xml
     *
     * @param   null
     *
     * @return  null
    */
    void read_families_xml(void);

    /**
     * @brief   find all core in xml
     *
     * @param   null
     *
     * @return  null
    */
    void find_core(void);

    /**
     * @brief   add company name to treewidget`s company node
     *
     * @param   null
     *
     * @return  null
    */
    void add_company(void);

    /**
     * @brief   add core name to treewidget`s core node
     *
     * @param   null
     *
     * @return  null
    */
    void add_core(void);

    /**
     * @brief   add family name to treewidget`s family node
     *
     * @param   null
     *
     * @return  null
    */
    void add_family(void);

    /**
     * @brief   add subfamily name to treewidget`s subfamily node
     *
     * @param   null
     *
     * @return  null
    */
    void add_subfamily(void);

    /**
     * @brief   find all package in xml
     *
     * @param   null
     *
     * @return  null
    */
    void find_package(void);

    /**
     * @brief   add package name to treewidget`s package node
     *
     * @param   null
     *
     * @return  null
    */
    void add_package(void);

    /**
     * @brief   add mcu info to QTableWidget
     *
     * @param   null
     *
     * @return  null
    */
    void add_tableWidget(void);
private:
    Ui::CDialog_choose_mcu *ui;

    QStringList qsl_company_g;
    QStringList qsl_family_g;
    QStringList qsl_subfamily_g;
    QList<NModel::CMcu_model> ql_mcu_g;
    QStringList qs_core_g;
    QStringList qs_package_g;

private slots:
    /**
     * @brief   SLOT of buttonBox click
     *
     * @param   null
     *
     * @return  null
    */
    void buttonBox_click(QAbstractButton *button);

    void on_tableWidget_itemSelectionChanged();

signals:
    /**
     * @brief   SIGAL of Create mcu project
     *
     * @param   null
     *
     * @return  null
    */
    void create_mcu_project(QString name);
};

#endif // DIALOG_CHOOSE_MCU_H
