/*
 * Copyright (c) 2020-2020,  by xqyjlj
 *
 * SPDX-License-Identifier: LGPL
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-16     xqyjlj       the first version
 */
#ifndef CODEANNOTATIONT_H
#define CODEANNOTATIONT_H

#include <QObject>
#include <QString>
class CodeAnnotationt : public QObject
{
    Q_OBJECT
public:
    explicit CodeAnnotationt(QObject* parent = nullptr);
    QString get_label_data(QString label);
signals:


private:
    QString FileHeader;
};

#endif // CODEANNOTATIONT_H
