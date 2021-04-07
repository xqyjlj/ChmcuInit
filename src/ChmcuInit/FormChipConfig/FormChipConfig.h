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
 ** 2021-03-29     xqyjlj       the first version        xqyjlj@126.com
 **/
#ifndef FORMCHIPCONFIG_H
#define FORMCHIPCONFIG_H

#include <QWidget>
#include "XmlRead.h"
#include "FormSTM32PeripheralsModeConfig.h"
#include "WidgetLQFP48.h"
#include "FormPinAttribute.h"
#include <QGraphicsScene>

namespace Ui
{
class FormChipConfig;
}
/**
 * @brief The FormChipConfig class
 *
 * 提供芯片配置界面
 */
class FormChipConfig : public QWidget
{
    Q_OBJECT

public:
    explicit FormChipConfig(QWidget* parent = nullptr);
    ~FormChipConfig();

    /**
     * @brief   设置Mcu
     *
     * @param   mcuName: mcu名
     *
     * @return  null
    */
    void setMcu(QString mcuName);

private:

    /**
     * @brief   设置Mcu引脚模型
     *
     * @param   mcuName: mcu名
     *
     * @return  null
    */
    void setPinModel(QString mcuPath, QString mcuName);

    /**
     * @brief   设置IP引脚模型
     *
     * @param   mcuName: mcu名
     *
     * @return  null
    */
    void setIpModel(QString mcuPath);

    /**
     * @brief   设置外设属性配置界面槽函数
     *
     * @param   ip: ip名
     *          locate: ip包位置
     *
     * @return  null
    */
    void setFormSTM32PeripheralsModeConfigWidget(QString ip, QString locate);

public slots:

    /**
     * @brief   设置引脚属性配置界面槽函数
     *
     * @param   widget: FormPinAttribute对象
     *
     * @return  null
    */
    void setFormPinAttributeWidget(FormPinAttribute* widget);

    /**
     * @brief   设置外设属性配置界面槽函数
     *
     * @param   ip: ip名
     *          locate: ip包位置
     *
     * @return  null
    */
    void setFormPeripheralsModeConfigWidget(QString ip, QString locate);
private:
    Ui::FormChipConfig* ui;                                                     //ui文件
    QList<FormSTM32PeripheralsModeConfig*> mformSTM32PeripheralsModeConfigs;    //外设模型控制列表
    QStringList mmodeConfigNames;                                               //IP模式名
    QString mmcuName;                                                           //MCU名
    QString mmcuPath;                                                           //MCU路径
    QList<Model::XmlPinModel> mpinModels;                                       //MCU引脚信息列表
    QString mcorePath;                                                          //程序现在目前路径

    QGraphicsScene* mgraphicsScene = nullptr;                                   //QgraphicsView管理器
    QWidget* mpackWidget = nullptr;                                             //封装
    QList<Model::XmlIpModel> mipModels;                                         //IP模型名
};

#endif // FORMCHIPCONFIG_H
