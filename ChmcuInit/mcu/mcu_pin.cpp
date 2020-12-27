/*
 * Copyright (c) 2020-2020,  by xqyjlj
 *
 * SPDX-License-Identifier: LGPL
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-12-27     xqyjlj       the first version
 */
#include "mcu_pin.h"
#include <QAction>
#include <QDebug>
mcu_pin::mcu_pin(QWidget* parent): QPushButton(parent)
{
    QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    this->setSizePolicy(sizePolicy);

}

void mcu_pin::set_connect()
{
    QList<QAction*> actionlist = this->actions();
    for (int i = 0; i < actionlist.length(); i++)
    {
        QObject::connect(actionlist.at(i), &QAction::toggled, [ = ](bool checked)
        {
            if(checked)
            {
                static QAction* static_action = nullptr;
                if(static_action != nullptr)
                {
                    static_action->setChecked(false);
                }
                QList< QAction* > actionlist = this->actions();
                for (int i = 0; i < actionlist.length(); i++)
                {
                    if(actionlist.at(i)->isChecked())
                    {
                        static_action = actionlist.at(i);
                        this->setText(this->whatsThis() + QString(" : ") + static_action->text());
                        qDebug() << static_action->text();
                    }
                }
            }
            else
            {
                this->setText(this->whatsThis());
            }
        });
    }
}

