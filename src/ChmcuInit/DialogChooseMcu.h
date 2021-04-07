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
#ifndef DIALOGCHOOSEMCU_H
#define DIALOGCHOOSEMCU_H

#include <QDialog>
#include "XmlRead.h"
#include <QAbstractButton>
namespace Ui
{
class DialogChooseMcu;
}

/**
 * @brief The DialogChooseMcu class
 *
 * 选择芯片项目对话框
 */
class DialogChooseMcu : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChooseMcu(QWidget* parent = nullptr);
    ~DialogChooseMcu();

private:

    /**
     * @brief   读取芯片家族模型
     *
     * @param   null
     *
     * @return  null
    */
    void readFamiliesModel(void);

    /**
     * @brief   查找芯片内核
     *
     * @param   null
     *
     * @return  null
    */
    void findCore(void);

    /**
     * @brief   添加公司到QTreewidget的公司节点
     *
     * @param   null
     *
     * @return  null
    */
    void addCompany(void);

    /**
     * @brief   添加内核到QTreewidget的内核节点
     *
     * @param   null
     *
     * @return  null
    */
    void addCore(void);

    /**
     * @brief   添加主科到QTreewidget的主科节点
     *
     * @param   null
     *
     * @return  null
    */
    void addFamily(void);

    /**
     * @brief   添加亚科到QTreewidget的亚科节点
     *
     * @param   null
     *
     * @return  null
    */
    void addSubfamily(void);

    /**
     * @brief   查找芯片封装
     *
     * @param   null
     *
     * @return  null
    */
    void findPackage(void);

    /**
     * @brief   添加封装到QTreewidget的封装节点
     *
     * @param   null
     *
     * @return  null
    */
    void addPackage(void);

    /**
     * @brief   添加MCU信息到QTableWidget中
     *
     * @param   null
     *
     * @return  null
    */
    void addTableWidget(void);
private slots:

    /**
     * @brief   QButtonBox点击槽函数
     *
     * @param   null
     *
     * @return  null
    */
    void buttonBoxClick(QAbstractButton* button);

    /**
     * @brief   QTableWidget Item被选中槽函数
     *
     * @param   null
     *
     * @return  null
    */
    void tableWidgetItemSelectionChanged();

signals:
    /**
     * @brief   创建MCU工程信号
     *
     * @param   null
     *
     * @return  null
    */
    void createMcuProject(QString name);

private:
    Ui::DialogChooseMcu* ui;                            //ui文件

    QStringList mcompanys;                              //公司列表
    QStringList mfamilys;                               //主科列表
    QStringList msubfamilys;                            //亚科列表
    QList<Model::XmlFamilyChipModel> mmcus;             //MCU模型列表
    QStringList mcores;                                 //内核列表
    QStringList mpackages;                              //封装列表
    QStringList mmcuPacks;                              //Mcu包列表
};

#endif // DIALOGCHOOSEMCU_H
