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
 ** 2021-03-21     xqyjlj       the first version        xqyjlj@126.com
 **/
#include "form_home_widget.h"
#include "ui_form_home_widget.h"
#include "dialog_choose_mcu.h"
#include "dialog_choose_board.h"
#include <QStyle>

CForm_home_widget::CForm_home_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CForm_home_widget)
{
    ui->setupUi(this);
    ui->new_BoardButton->setIcon(QApplication::style()->standardIcon(QStyle::SP_DirOpenIcon));
    ui->new_ChipButton->setIcon(QApplication::style()->standardIcon(QStyle::SP_DirOpenIcon));
}

CForm_home_widget::~CForm_home_widget()
{
    delete ui;
}

void CForm_home_widget::on_new_BoardButton_pressed()
{
    CDialog_choose_board dialog(this);
    dialog.setWindowTitle(tr("新建开发板项目"));
    dialog.exec();
}

void CForm_home_widget::on_new_ChipButton_pressed()
{
    CDialog_choose_mcu dialog(this);
    dialog.setWindowTitle(tr("新建芯片项目"));
    dialog.exec();
}
