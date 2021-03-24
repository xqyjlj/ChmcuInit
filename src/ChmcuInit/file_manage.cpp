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
#include "file_manage.h"
#include <QCoreApplication>
#include "debug.h"
#include <QDir>
namespace NFile
{
CFile_manage::CFile_manage(QObject *parent) : QObject(parent)
{

}

/**
 * @brief   get mcu pack list
 *
 * @param   null
 *
 * @return  QStringList of mcu pack
*/
QStringList CFile_manage::get_mcu_pack_list(void)
{
    QStringList list;
    QDir dir(QCoreApplication::applicationDirPath() + "/origin/families/chip");
    dir.setFilter(QDir::Dirs);
    foreach (QFileInfo fullDir, dir.entryInfoList())
    {
        if (fullDir.fileName() == "." || fullDir.fileName() == "..")
            continue;
        list << fullDir.fileName();
    }
    return list;
}
}
