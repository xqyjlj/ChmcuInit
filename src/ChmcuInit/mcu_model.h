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
 ** 2021-03-20     xqyjlj       the first version        xqyjlj@126.com
 **/


#ifndef MCU_MODEL_H
#define MCU_MODEL_H

#include <QStringList>

namespace NModel
{

class CMcu_voltage_model
{
public:
    QString min;
    QString max;
};

class CMcu_temperature_model
{
public:
    QString min;
    QString max;
};

class CMcu_current_model
{
public:
    QString lowest;
    QString Run;
};

class CMcu_peripheral_model
{
public:
    QString Type;
};

class CMcu_model
{
public:
    QString Core;
    QString Frequency;
    QString Ram;
    QString IO;
    QString Flash;
    CMcu_voltage_model voltage;
    CMcu_temperature_model temperature;
    CMcu_current_model current;
    QList<CMcu_peripheral_model> peripheral;
};

}


#endif // MCU_MODEL_H
