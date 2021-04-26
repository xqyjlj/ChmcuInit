/**
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
 ** 2021-04-24     xqyjlj       the first version        xqyjlj@126.com
 **/

// You may need to build the project (run Qt uic code generator) to get "ui_DialogSaveFile.h" resolved

#include "DialogSaveFile.h"
#include "ui_DialogSaveFile.h"
#include <QPushButton>


DialogSaveFile::DialogSaveFile(QWidget *parent) :
        QDialog(parent), ui(new Ui::DialogSaveFile)
{
    ui->setupUi(this);

    ui->ubuttonBox->button(QDialogButtonBox::Ok)->setText(u8"保存");
    ui->ubuttonBox->button(QDialogButtonBox::Ok)->setObjectName(u8"buttonBoxSave");
    ui->ubuttonBox->button(QDialogButtonBox::Cancel)->setText(u8"取消");
    ui->ubuttonBox->button(QDialogButtonBox::Cancel)->setObjectName(u8"buttonBoxCancel");

    connect(ui->ubuttonBox, &QDialogButtonBox::clicked, this, &DialogSaveFile::slotButtonBoxClick,
            Qt::UniqueConnection);
    connect(ui->ubuttonBox, &QDialogButtonBox::accepted, this, &DialogSaveFile::accept, Qt::UniqueConnection);
    connect(ui->ubuttonBox, &QDialogButtonBox::rejected, this, &DialogSaveFile::reject, Qt::UniqueConnection);
}

DialogSaveFile::~DialogSaveFile()
{
    delete ui;
}

void DialogSaveFile::slotAddProjectContent(const QString &content)
{
    ui->utextBrowser->append(content);
}

void DialogSaveFile::setBaseObject(BaseObject *baseObject)
{
    m_baseObject = baseObject;
    ASSERT_X(m_baseObject, u8"DialogSaveFile", u8"空指针-> m_baseObject");
    connect(m_baseObject->getFileProject(), &FileProject::signalAddProjectContent, this,
            &DialogSaveFile::slotAddProjectContent, Qt::UniqueConnection);
}

void DialogSaveFile::slotButtonBoxClick(QAbstractButton *button)
{
    ASSERT_X(button, u8"DialogSaveFile", u8"空指针-> button");
    if (button->objectName() == u8"buttonBoxSave")
    {
        m_baseObject->saveProject();
    }
}

