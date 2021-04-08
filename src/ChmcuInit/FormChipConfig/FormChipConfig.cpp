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
#include "FormChipConfig.h"
#include "ui_FormChipConfig.h"
#include "Debug.h"
#include <QCoreApplication>

FormChipConfig::FormChipConfig(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::FormChipConfig)
{
    ui->setupUi(this);

    mgraphicsScene = new QGraphicsScene(ui->graphicsViewMcu);
    connect(ui->treeWidgetChooseFunction, SIGNAL(pinAttributeOpened(FormPinAttribute*)), this, SLOT(setFormPinAttributeWidget(FormPinAttribute*)), Qt::UniqueConnection);
    connect(ui->treeWidgetChooseIp, SIGNAL(ipChosen(QString, QString)), this, SLOT(setFormPeripheralsModeConfigWidget(QString, QString)), Qt::UniqueConnection);
}

FormChipConfig::~FormChipConfig()
{
    delete ui;
}

/**
 * @brief   设置Mcu
 *
 * @param   mcuName: mcu名
 *
 * @return  null
*/
void FormChipConfig::setMcu(QString mcuName)
{
    mcorePath = QCoreApplication::applicationDirPath();
    mmcuPath = mcorePath + "/origin/families/chip/" + mcuName + "/" + mcuName + ".xml";
    mmcuName = mcuName;
    setPinModel(mmcuPath, mmcuName);
    setIpModel(mmcuPath);
}

/**
 * @brief   设置Mcu引脚模型
 *
 * @param   mcuName: mcu名
 *
 * @return  null
*/
void FormChipConfig::setPinModel(QString mcuPath, QString mcuName)
{
    mpinModels = Xml::XmlRead().getPinInfo(mcuPath, mcuName);
    Model::XmlFamilyChipModel family = Xml::XmlRead().getMcuInfo(mcuName);
    if (family.packagename == "LQFP48")
    {
        if (!mpackWidget)
        {
            mpackWidget = new WidgetLQFP48();
            connect(ui->treeWidgetChooseFunction, SIGNAL(pinClicked(QVector<bool>)), mpackWidget, SLOT(selectPin(QVector<bool>)), Qt::UniqueConnection);
            connect(mpackWidget, SIGNAL(pinClicked(QVector<bool>)), ui->treeWidgetChooseFunction, SLOT(selectPin(QVector<bool>)), Qt::UniqueConnection);
        }
        ASSERT_X(mpackWidget, "FormChipConfig", "空指针");
        reinterpret_cast<WidgetLQFP48*>(mpackWidget)->setPinModel(mpinModels);
    }
    else
    {
        return;
    }
    ASSERT_X(mpackWidget, "FormChipConfig", "空指针");
    ASSERT_X(mgraphicsScene, "FormChipConfig", "空指针");
    mgraphicsScene->addWidget(mpackWidget);
    ui->graphicsViewMcu->setScene(mgraphicsScene);
    ui->treeWidgetChooseFunction->setPinModel(mpinModels);
}

/**
 * @brief   设置引脚属性配置界面槽函数
 *
 * @param   widget: FormPinAttribute对象
 *
 * @return  null
*/
void FormChipConfig::setFormPinAttributeWidget(FormPinAttribute* widget)
{
    LOG_D << widget;
    static FormPinAttribute* last_widget = nullptr;
    ASSERT_X(widget, "FormChipConfig", "空指针");
    if (last_widget)
    {
        widget->setParent(ui->PInAttributeWidget);
        ui->PinAttributeLayout->replaceWidget(last_widget, widget);
        widget->show();
        last_widget->hide();
    }
    else
    {
        ui->PinAttributeLayout->addWidget(widget);
    }
    last_widget = widget;
}

/**
 * @brief   设置IP引脚模型
 *
 * @param   mcuName: mcu名
 *
 * @return  null
*/
void FormChipConfig::setIpModel(QString mcuPath)
{
    mipModels = Xml::XmlRead().getIpInfo(mcuPath);
    ui->treeWidgetChooseIp->setIpModel(mipModels);
}

/**
 * @brief   设置外设属性配置界面槽函数
 *
 * @param   ip: ip名
 *          locate: ip包位置
 *
 * @return  null
*/
void FormChipConfig::setFormPeripheralsModeConfigWidget(QString ip, QString locate)
{
    if (locate.contains("stm32"))
    {
        setFormSTM32PeripheralsModeConfigWidget(ip, mcorePath + locate);
    }
}

/**
 * @brief   设置外设属性配置界面槽函数
 *
 * @param   ip: ip名
 *          locate: ip包位置
 *
 * @return  null
*/
void FormChipConfig::setFormSTM32PeripheralsModeConfigWidget(QString ip, QString locate)
{
    if (!mmodeConfigNames.contains(ip))
    {
        mmodeConfigNames << ip;
        FormSTM32PeripheralsModeConfig* mode_config = new FormSTM32PeripheralsModeConfig(this);
        mode_config->setWhatsThis(ip);
        mode_config->setIp(mmcuName, locate);
        mformSTM32PeripheralsModeConfigs << mode_config;
    }

    static int last_node = -1;
    int node = -1, len = mformSTM32PeripheralsModeConfigs.length();
    for (int i = 0; i < len; i++)
    {
        if (mformSTM32PeripheralsModeConfigs.at(i)->whatsThis() == ip)
        {
            node = i;
            break;
        }
    }
    if (node > -1)
    {
        if (last_node > -1)
        {
            ui->gridLayout_3->replaceWidget(mformSTM32PeripheralsModeConfigs.at(last_node), mformSTM32PeripheralsModeConfigs.at(node));
            mformSTM32PeripheralsModeConfigs.at(node)->show();
            mformSTM32PeripheralsModeConfigs.at(last_node)->hide();
        }
        else
        {
            ui->gridLayout_3->addWidget(mformSTM32PeripheralsModeConfigs.at(node));
        }
        last_node = node;
    }
}
