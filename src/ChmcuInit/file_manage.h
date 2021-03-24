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
 ** 2021-03-24     xqyjlj       the first version        xqyjlj@126.com
 **/
#ifndef FILE_MANAGE_H
#define FILE_MANAGE_H

#include <QObject>
#include <QStringList>

namespace NFile
{



class CFile_manage : public QObject
{
    Q_OBJECT
public:
    explicit CFile_manage(QObject *parent = nullptr);

    /**
     * @brief   get mcu pack list
     *
     * @param   null
     *
     * @return  QStringList of mcu pack
    */
    QStringList get_mcu_pack_list(void);
signals:

};
}

#endif // FILE_MANAGE_H
