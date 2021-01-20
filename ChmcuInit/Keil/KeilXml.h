/*
 * Copyright (c) 2020-2020,  by xqyjlj
 *
 * SPDX-License-Identifier: LGPL
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-15     xqyjlj       the first version
 */
#ifndef KEILXML_H
#define KEILXML_H

#include <QObject>
#include <QString>
class KeilXml : public QObject
{
    Q_OBJECT
public:
    QString project_name;


public:
    explicit KeilXml(QObject* parent = nullptr);

    bool creat_keil_project(void);
signals:

public slots:
};

#endif // KEILXML_H
