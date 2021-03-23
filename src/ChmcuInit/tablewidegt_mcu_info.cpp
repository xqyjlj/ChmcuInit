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

#include "tablewidegt_mcu_info.h"

CTablewidegt_mcu_info::CTablewidegt_mcu_info(QWidget *parent) : QTableWidget(parent)
{

}


/**
 * @brief   add mcu model to QTableWidget
 *
 * @param   null
 *
 * @return  null
*/
void CTablewidegt_mcu_info::add_mcu_model(NModel::CMcu_model model)
{
    int count = this->rowCount();
    this->insertRow(count);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setItem(count, 0, new QTableWidgetItem(model.name));
    this->setItem(count, 3, new QTableWidgetItem(model.packagename));
    this->setItem(count, 4, new QTableWidgetItem(model.flash));
    this->setItem(count, 5, new QTableWidgetItem(model.ram));
    this->setItem(count, 6, new QTableWidgetItem(model.io));
    this->setItem(count, 7, new QTableWidgetItem(model.frequency));
    this->setItem(count, 8, new QTableWidgetItem(model.company));
    this->setItem(count, 9, new QTableWidgetItem(model.core));
    this->setItem(count, 10, new QTableWidgetItem(model.family));
    this->setItem(count, 11, new QTableWidgetItem(model.subfamily));
}
