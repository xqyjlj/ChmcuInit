/*
 * Copyright (c) 2020-2020,  by xqyjlj
 *
 * SPDX-License-Identifier: LGPL
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-15     xqyjlj       the first version
 */
#ifndef MCU_XML_H
#define MCU_XML_H

#include <QObject>
#include <QXmlStreamReader>
class mcu_xml : public QObject
{
    Q_OBJECT
public:
    explicit mcu_xml(QObject* parent = nullptr);
public:
    QStringList read_pin(QString path, QStringList list, int indel);
signals:

public slots:
};

#endif // MCU_XML_H
