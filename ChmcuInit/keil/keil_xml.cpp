/*
 * Copyright (c) 2020-2020,  by xqyjlj
 *
 * SPDX-License-Identifier: LGPL
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-12-24     xqyjlj       the first version
 */

#include "keil_xml.h"
#include <QtXml>

keil_xml::keil_xml(QObject* parent) : QObject(parent)
{

}

bool keil_xml::creat_keil_project(void)
{
    QFile file("test.xml");
    if(!file.open(QFile::ReadOnly))
    {
        return false;
    }

    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        file.close();
        return false;
    }
    file.close();

    QDomElement root = doc.documentElement();
    QDomNodeList list = root.elementsByTagName("book");
    QDomNode node = list.at(list.size() - 1).firstChild();
    QDomNode oldnode = node.firstChild();
    node.firstChild().setNodeValue("Emma");
    QDomNode newnode = node.firstChild();
    node.replaceChild(newnode, oldnode);

    if(!file.open(QFile::WriteOnly | QFile::Truncate))
    {
        return false;
    }

    QTextStream out_stream(&file);
    doc.save(out_stream, 4);
    file.close();

    return true;
}
