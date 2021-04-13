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
#include "DialogChooseMcu.h"
#include "ui_DialogChooseMcu.h"
#include <QPushButton>
#include "Debug.h"
#include <QFile>

#include <QWebEngineView>
#include <QTextStream>
#include <QWebChannel>
#include "FileManage.h"
#include <QMessageBox>

DialogChooseMcu::DialogChooseMcu(QWidget* parent): QDialog(parent), ui(new Ui::DialogChooseMcu)
{
    ui->setupUi(this);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("创建"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("取消"));

    readFamiliesModel();

    addCompany();
    addCore();
    addFamily();
    addSubfamily();
    addPackage();
    addTableWidget();

    this->setWindowState(Qt::WindowMaximized);

    QFile file(":/markdown/assets/readme.html");
    file.open(QFile::ReadOnly | QFile::Text);
    ui->textBrowser->setHtml(file.readAll());
    file.close();

    connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(buttonBoxClick(QAbstractButton*)), Qt::UniqueConnection);
    connect(ui->tableWidegtMcuInfo, SIGNAL(itemSelectionChanged()), this, SLOT(tableWidgetItemSelectionChanged()), Qt::UniqueConnection);

    QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()), Qt::UniqueConnection);
    QObject::connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()), Qt::UniqueConnection);

    mmcuPacks = FileManage().getMcuPackList();
}

DialogChooseMcu::~DialogChooseMcu()
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
void DialogChooseMcu::setBaseObject(BaseObject* baseObject)
{
    mbaseObject = baseObject;
}

/**
 * @brief   读取芯片家族模型
 *
 * @param   null
 *
 * @return  null
*/
void DialogChooseMcu::readFamiliesModel(void)
{
    QStringList list = Xml::XmlRead().getCompanyName();
    mcompanys << list;
    foreach (QString str, list)
    {
        QStringList list = Xml::XmlRead().getFamilyName(str);
        mfamilys << list;
        foreach (QString str, list)
        {
            QStringList list = Xml::XmlRead().getSubfamilyName(str);
            msubfamilys << list;
            foreach (QString str, list)
            {
                QStringList list = Xml::XmlRead().getMcuName(str);
                foreach (QString str, list)
                {
                    Model::XmlFamilyChipModel model = Xml::XmlRead().getMcuInfo(str);
                    mmcus << model;
                }
            }
        }
    }
}

/**
 * @brief   添加公司到QTreewidget的公司节点
 *
 * @param   null
 *
 * @return  null
*/
void DialogChooseMcu::addCompany(void)
{
    QList<QTreeWidgetItem*> items = ui->treeWidgetChooseMcuBoard->findItems(tr("公司"), Qt::MatchExactly);
    if (items.length())
    {
        QTreeWidgetItem* parent = items.at(0);
        parent->setCheckState(0, Qt::Unchecked);

        foreach (QString str, mcompanys)
        {
            QTreeWidgetItem* item = new QTreeWidgetItem(parent);
            item->setText(0, str);
            item->setCheckState(0, Qt::Unchecked);
        }
    }
}

/**
 * @brief   寻找芯片内核
 *
 * @param   null
 *
 * @return  null
*/
void DialogChooseMcu::findCore(void)
{
    foreach (Model::XmlFamilyChipModel model, mmcus)
    {
        if ((!model.core.isEmpty()) && (!mcores.contains(model.core)))
        {
            mcores << model.core;
        }
    }
}

/**
 * @brief   添加内核到QTreewidget的内核节点
 *
 * @param   null
 *
 * @return  null
*/
void DialogChooseMcu::addCore(void)
{
    QList<QTreeWidgetItem*> items = ui->treeWidgetChooseMcuBoard->findItems(tr("内核"), Qt::MatchExactly);
    if (items.length())
    {
        QTreeWidgetItem* parent = items.at(0);
        parent->setCheckState(0, Qt::Unchecked);

        findCore();

        foreach (QString str, mcores)
        {
            QTreeWidgetItem* item = new QTreeWidgetItem(parent);
            item->setText(0, str);
            item->setCheckState(0, Qt::Unchecked);
        }
    }
}

/**
 * @brief   添加主科到QTreewidget的主科节点
 *
 * @param   null
 *
 * @return  null
*/
void DialogChooseMcu::addFamily(void)
{
    QList<QTreeWidgetItem*> items = ui->treeWidgetChooseMcuBoard->findItems(tr("主科"), Qt::MatchExactly);
    if (items.length())
    {
        QTreeWidgetItem* parent = items.at(0);
        parent->setCheckState(0, Qt::Unchecked);

        foreach (QString str, mfamilys)
        {
            QTreeWidgetItem* item = new QTreeWidgetItem(parent);
            item->setText(0, str);
            item->setCheckState(0, Qt::Unchecked);
        }
    }
}

/**
 * @brief   添加亚科到QTreewidget的亚科节点
 *
 * @param   null
 *
 * @return  null
*/
void DialogChooseMcu::addSubfamily(void)
{
    QList<QTreeWidgetItem*> items = ui->treeWidgetChooseMcuBoard->findItems(tr("亚科"), Qt::MatchExactly);
    if (items.length())
    {
        QTreeWidgetItem* parent = items.at(0);
        parent->setCheckState(0, Qt::Unchecked);

        foreach (QString str, msubfamilys)
        {
            QTreeWidgetItem* item = new QTreeWidgetItem(parent);
            item->setText(0, str);
            item->setCheckState(0, Qt::Unchecked);
        }
    }
}

/**
 * @brief   查找芯片封装
 *
 * @param   null
 *
 * @return  null
*/
void DialogChooseMcu::findPackage(void)
{
    foreach (Model::XmlFamilyChipModel model, mmcus)
    {
        if ((!model.package.isEmpty()) && (!mpackages.contains(model.package)))
        {
            mpackages << model.package;
        }
    }
}

/**
 * @brief   添加封装到QTreewidget的封装节点
 *
 * @param   null
 *
 * @return  null
*/
void DialogChooseMcu::addPackage(void)
{
    QList<QTreeWidgetItem*> items = ui->treeWidgetChooseMcuBoard->findItems(tr("封装"), Qt::MatchExactly);
    if (items.length())
    {
        QTreeWidgetItem* parent = items.at(0);
        parent->setCheckState(0, Qt::Unchecked);

        findPackage();

        foreach (QString str, mpackages)
        {
            QTreeWidgetItem* item = new QTreeWidgetItem(parent);
            item->setText(0, str);
            item->setCheckState(0, Qt::Unchecked);
        }
    }
}

/**
 * @brief   add mcu info to QTableWidget
 *
 * @param   null
 *
 * @return  null
*/
void DialogChooseMcu::addTableWidget(void)
{
    foreach (Model::XmlFamilyChipModel model, mmcus)
    {
        ui->tableWidegtMcuInfo->addMcuModel(model);
    }
}

/**
 * @brief   buttonBox点击槽函数
 *
 * @param   null
 *
 * @return  null
*/
void DialogChooseMcu::buttonBoxClick(QAbstractButton* button)
{
    if (button->text() == tr("创建"))
    {
        QList<QTableWidgetItem*> items =  ui->tableWidegtMcuInfo->selectedItems();
        if (!items.isEmpty())
        {
            ASSERT_X(mbaseObject, "DialogChooseMcu", "空指针");
            mbaseObject->setMcuName(items.at(0)->text());
            mbaseObject->setPackageName(items.at(3)->text());
            mbaseObject->setCompanyName(items.at(8)->text());
            mbaseObject->setFamilyName(items.at(10)->text());
            mbaseObject->setSubfamilyName(items.at(11)->text());

            emit createMcuProject(items.at(0)->text());
        }
        else
        {
            QMessageBox::critical(this, tr("Error"), tr("请选择包"));
        }
    }
}

/**
 * @brief   QTableWidget Item被选中槽函数
 *
 * @param   null
 *
 * @return  null
*/
void DialogChooseMcu::tableWidgetItemSelectionChanged()
{
    QList<QTableWidgetItem*> items =  ui->tableWidegtMcuInfo->selectedItems();
    if (!items.isEmpty())
    {
        ASSERT_X(mbaseObject, "DialogChooseMcu", "空指针");
        QString path = mbaseObject->getMcuReadMePath(items.at(0)->text());
        if (mmcuPacks.contains(items.at(0)->text()))
        {
            QFile file(path);
            file.open(QFile::ReadOnly | QFile::Text);
            ui->textBrowser->setHtml(file.readAll());
            file.close();
        }
        else
        {
            QFile file(":/markdown/assets/no_mcu_md.html");
            file.open(QFile::ReadOnly | QFile::Text);
            QString md = file.readAll();
            md = md.arg(path);
            ui->textBrowser->setHtml(md);
            file.close();
        }
    }
}
