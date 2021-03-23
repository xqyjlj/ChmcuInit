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
#ifndef CTABLEWIDEGT_MCU_INFO_H
#define CTABLEWIDEGT_MCU_INFO_H

#include <QObject>
#include <QTableWidget>
#include "mcu_model.h"


namespace Ui
{
class CTablewidegt_mcu_info;
}

class CTablewidegt_mcu_info : public QTableWidget
{
    Q_OBJECT
public:
    explicit CTablewidegt_mcu_info(QWidget *parent = nullptr);

    /**
     * @brief   add mcu model to QTableWidget
     *
     * @param   null
     *
     * @return  null
    */
    void add_mcu_model(NModel::CMcu_model model);

signals:

};

#endif // CTABLEWIDEGT_MCU_INFO_H
