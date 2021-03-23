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
#include "dialog_choose_board.h"
#include "ui_dialog_choose_board.h"
#include <QPushButton>

CDialog_choose_board::CDialog_choose_board(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDialog_choose_board)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("创建"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("取消"));
}

CDialog_choose_board::~CDialog_choose_board()
{
    delete ui;
}
