/*
 * Copyright (c) 2020-2020,  by xqyjlj
 *
 * SPDX-License-Identifier: LGPL
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-15     xqyjlj       the first version
 */
#ifndef MCUXML_H
#define MCUXML_H

#include <QObject>
#include <QXmlStreamReader>
class McuXml : public QObject
{
    Q_OBJECT
public:
    explicit McuXml(QObject* parent = nullptr);
public:
    QStringList read_pin(QString path, QStringList list, int indel);
signals:

public slots:
};

#endif // MCUXML_H
