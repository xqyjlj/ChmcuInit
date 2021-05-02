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
 ** 2021-04-29     xqyjlj       the first version        xqyjlj@126.com
 **/

#include <Debug.h>
#include "CoderHalIo.h"
#include <QFile>
#include <QDir>

CoderHalIo::CoderHalIo(QObject *parent) : QObject(parent)
{

}

void CoderHalIo::setGpioModels(const QList<XmlFileProjectModel::GpioModel_T> &gpioModels, const QString &path)
{
    QString filePath = path + u8"/src/gpio.c";
    QString srcDir = path + u8"/src";
    QDir dir(srcDir);
    if (!dir.exists(srcDir))
    {
        dir.mkdir(srcDir);
    }

    QFile file(filePath);
    if (file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate))
    {
        CoderStreamWriter writer(this, &file);

        createHeader(&writer);

        writer.writeTag(u8"User include");
        writer.writeEndTag();

        writer.writeTag(u8"User code");
        writer.writeEndTag();

        createFunction(gpioModels, &writer);
    }
    else
    {
        ASSERT_X(false, u8"CoderHalIo", QString(u8"Cannot write file %1").arg(filePath));
        return;
    }

    file.close();
}

void CoderHalIo::createHeader(CoderStreamWriter *writer)
{
    writer->writeFileHeaderComment(u8"gpio.c",
                                   u8"This file provides code for the configuration of all used GPIO pins");
    writer->writeHeader(u8"gpio.h");
}

void CoderHalIo::createFunction(const QList<XmlFileProjectModel::GpioModel_T> &gpioModels, CoderStreamWriter *writer)
{
    CoderStreamWriter::Function_T function;
    QStringList ports;

    function.name = u8"CmiIoInit";
    function.briefComment = u8"Configure pins";

    writer->writeFunction(function);
    writer->writeStartFunction();

    writer->writeElement(u8"GPIO_InitTypeDef", u8"GPIO_InitStruct", u8"{0}");

    for (const XmlFileProjectModel::GpioModel_T &gpioModel :gpioModels)
    {
        QString port = gpioModel.port;
        if (!ports.contains(port))
        {
            ports << port;
            writer->writeCommand(QString(u8"__HAL_RCC_%1_CLK_ENABLE").arg(port));
        }
        createPin(gpioModel, writer);
    }

    writer->writeEndFunction();
}

void CoderHalIo::createPin(const XmlFileProjectModel::GpioModel_T &gpioModel, CoderStreamWriter *writer)
{
    writer->writeLine();
    if (!gpioModel.level.isEmpty())
    {
        QStringList parameters;
        parameters << gpioModel.port << gpioModel.pin << gpioModel.level;
        writer->writeCommand(u8"HAL_GPIO_WritePin", parameters);
    }
    if (!gpioModel.pin.isEmpty() && !gpioModel.pull.isEmpty() && !gpioModel.mode.isEmpty())
    {
        QString str = u8"GPIO_InitStruct";
        writer->writeAttribute(str + ".Pin", gpioModel.pin);
        writer->writeAttribute(str + ".Pull", gpioModel.pull);
        writer->writeAttribute(str + ".Mode", gpioModel.mode);
        if (!gpioModel.speed.isEmpty())
        {
            writer->writeAttribute(str + ".Speed", gpioModel.speed);
        }
        QStringList parameters;
        parameters << gpioModel.port << u8"&GPIO_InitStruct";
        writer->writeCommand(u8"HAL_GPIO_Init", parameters);
    }
    writer->writeLine();
}
