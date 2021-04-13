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
 **
 ** 该文件是ChmcuInit项目的一部分。
 ** 版权所有2021 xqyjlj
 **
 ** 本程序是免费软件:您可以重新发布和/或修改它
 ** 根据GNU通用公共许可证的条款，由自由软件基金会，或第三版许可证，或(随您选择)任何更新版本。
 **
 ** 分发此程序是希望它会有用，但没有任何保证：甚至没有默示的保证特定目的的适销性或适用性。有关更多详细信息，请参见GNU通用公共许可证。
 **
 ** 您应该已经与这个程序一起收到GNU通用公共许可证的副本。如果不是，请参见<http://www.gnu.org/licenses/>。
 **
 ** Change Logs:
 ** Date           Author       Notes                    Email
 ** 2021-03-20     xqyjlj       the first version        xqyjlj@126.com
 **/
#include "FormHome.h"
#include "ui_FormHome.h"
#include "DialogChooseMcu.h"
#include "DialogChooseBoard.h"
#include <QStyle>

#include "Debug.h"
#include "FileManage.h"
#include <QMessageBox>
FormHome::FormHome(QWidget* parent) : QWidget(parent), ui(new Ui::FormHome)
{
    ui->setupUi(this);
    ui->buttonCreateBoardProject->setIcon(QApplication::style()->standardIcon(QStyle::SP_DirOpenIcon));
    ui->buttonCreateChipProject->setIcon(QApplication::style()->standardIcon(QStyle::SP_DirOpenIcon));
    connect(ui->buttonCreateBoardProject, SIGNAL(pressed()), this, SLOT(buttonCreateBoardProjectPressed()), Qt::UniqueConnection);
    connect(ui->buttonCreateChipProject, SIGNAL(pressed()), this, SLOT(buttonCreateChipProjectPressed()), Qt::UniqueConnection);
}

FormHome::~FormHome()
{
    delete ui;
}

/**
 * @brief   设置基础对象
 *
 * @param   baseObject: 基础对象
 *
 * @return  null
*/
void FormHome::setBaseObject(BaseObject* baseObject)
{
    mbaseObject = baseObject;
}
/**
 * @brief   创建板工程按钮按下槽函数
 *
 * @param   null
 *
 * @return  null
*/
void FormHome::buttonCreateBoardProjectPressed()
{
    ASSERT_X(mbaseObject, "FormHome", "空指针");
    DialogChooseBoard dialog(this);
    dialog.setWindowTitle(tr("新建开发板项目"));
    dialog.setBaseObject(mbaseObject);
    dialog.exec();

}

/**
 * @brief   创建芯片工程按钮按下槽函数
 *
 * @param   null
 *
 * @return  null
*/
void FormHome::buttonCreateChipProjectPressed()
{
    ASSERT_X(mbaseObject, "FormHome", "空指针");
    DialogChooseMcu dialog(this);
    dialog.setWindowTitle(tr("新建芯片项目"));
    dialog.setBaseObject(mbaseObject);
    connect(&dialog, &DialogChooseMcu::createMcuProject, this, [ = ](QString name)
    {
        if (FileManage().getMcuPackList().contains(name))
        {
            emit createMcuProject(name);
        }
        else
        {
            QMessageBox::critical(nullptr, tr("Error"), tr("目前还未准备这个包"));
        }
    });
    dialog.exec();
}
