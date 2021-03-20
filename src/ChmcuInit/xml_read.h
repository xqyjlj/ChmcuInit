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
 ** 2021-03-19     xqyjlj       the first version        xqyjlj@126.com
 **/
#ifndef XML_READ_H
#define XML_READ_H

#include <QObject>
#include <QStringList>
#include <QXmlStreamReader>
namespace NXml
{
class CXml_read : public QObject
{
    Q_OBJECT
public:
    explicit CXml_read(QObject *parent = nullptr);

    /**
     * @brief   get all company name in xml file
     *
     * @param   null
     *
     * @return  QStringList with company name
    */
    QStringList get_all_company_name();

    /**
     * @brief   get all company`s family name in the XML file
     *
     * @param   company: the name of the company we want to read
     *
     * @return  QStringList with family name
    */
    QStringList get_all_family_name(QString company);

    /**
     * @brief   get all family`s subfamily name in the XML file
     *
     * @param   family: the name of the family we want to read
     *
     * @return  QStringList with subfamily name
    */
    QStringList get_all_subfamily_name(QString family);
signals:

private:

    /**
     * @brief   read family name in xml file
     *
     * @param   *reader: QXmlStreamReader handle
     *
     * @return  QStringList with family name
    */
    QStringList read_family_name(QXmlStreamReader *reader);

    /**
     * @brief   read subfamily name in xml file
     *
     * @param   *reader: QXmlStreamReader handle
     *
     * @return  QStringList with subfamily name
    */
    QStringList read_subfamily_name(QXmlStreamReader *reader);
};

}

#endif // XML_READ_H
