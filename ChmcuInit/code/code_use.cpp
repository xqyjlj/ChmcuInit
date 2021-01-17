/*
 * Copyright (c) 2020-2020,  by xqyjlj
 *
 * SPDX-License-Identifier: LGPL
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-16     xqyjlj       the first version
 */
#include "code_use.h"
#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>
code_use::code_use(QObject *parent) : QObject(parent)
{

}

QString get_label_data(QString label)
{
    QString label_data;
    QFile *File = new QFile(":/code/res/db/sys/code.xml");
    if(File->open(QFile::ReadOnly | QFile::Text))
    {
        QXmlStreamReader *reader = new QXmlStreamReader(File);
        while(!reader->atEnd())
        {
            QXmlStreamReader::TokenType type = reader->readNext();
            if(type == QXmlStreamReader::StartElement && reader->name().toString() == label)
            {
                label_data = reader->readElementText();
                break;
            }
        }
        File->close();
    }
    return label_data;
}
