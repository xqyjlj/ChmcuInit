/*
 * Copyright (c) 2020-2020,  by xqyjlj
 *
 * SPDX-License-Identifier: LGPL
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-16     xqyjlj       the first version
 */
#ifndef CODE_USE_H
#define CODE_USE_H

#include <QObject>
#include <QString>
class code_use : public QObject
{
    Q_OBJECT
public:
    explicit code_use(QObject* parent = nullptr);

signals:


private:

};

#endif // CODE_USE_H
