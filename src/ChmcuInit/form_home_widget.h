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
#ifndef FORM_HOME_WIDGET_H
#define FORM_HOME_WIDGET_H

#include <QWidget>

namespace Ui
{
class CForm_home_widget;
}

class CForm_home_widget : public QWidget
{
    Q_OBJECT

public:
    explicit CForm_home_widget(QWidget *parent = nullptr);
    ~CForm_home_widget();

private slots:
    void on_new_BoardButton_pressed();

    void on_new_ChipButton_pressed();

private:
    Ui::CForm_home_widget *ui;
};

#endif // FORM_HOME_WIDGET_H
