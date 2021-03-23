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
#ifndef CTREEWIDGET_CHOOSE_MCU_H
#define CTREEWIDGET_CHOOSE_MCU_H

#include <QObject>
#include <QTreeWidget>

namespace Ui
{
class CTreewidget_choose_mcu_board;
}

class CTreewidget_choose_mcu_board : public QTreeWidget
{
    Q_OBJECT
public:
    explicit CTreewidget_choose_mcu_board(QWidget *parent = nullptr);

signals:

};

#endif // CTREEWIDGET_CHOOSE_MCU_H
