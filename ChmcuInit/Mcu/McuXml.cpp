/*
 * Copyright (c) 2020-2020,  by xqyjlj
 *
 * SPDX-License-Identifier: LGPL
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-12-27     xqyjlj       the first version
 */
#include "McuXml.h"
#include <QFile>
#include <QDebug>
McuXml::McuXml(QObject* parent) : QObject(parent)
{

}

QStringList McuXml::read_pin(QString path, QStringList list, int indel)
{
    QFile* File = new QFile(path);
    if(File->open(QFile::ReadOnly | QFile::Text))
    {
        QXmlStreamReader* reader = new QXmlStreamReader(File);
        while(!reader->atEnd())
        {
            QXmlStreamReader::TokenType type = reader->readNext();
            if(type == QXmlStreamReader::StartElement &&  reader->name() == "Pin" && reader->attributes().value("Position").toInt() == indel)
            {
                list << reader->attributes().value("Name").toString();
                while(!reader->atEnd())
                {
                    QXmlStreamReader::TokenType type = reader->readNext();
                    if(type == QXmlStreamReader::EndElement && reader->name() == "Pin") //如果遇到 </entry>,则表示解析完成
                    {
                        break;
                    }
                    if(type == QXmlStreamReader::StartElement)
                    {
                        if(reader->name() == "Signal")
                        {
                            list << reader->attributes().value("Name").toString();
                        }
                    }
                }
            }
        }
        File->close();
    }
    return list;
}
