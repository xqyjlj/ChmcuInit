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
 ** 2021-04-20     xqyjlj       the first version        xqyjlj@126.com
 **/

#ifndef CHMCUINIT_XMLFAMILYMODEL_H
#define CHMCUINIT_XMLFAMILYMODEL_H

#include <QObject>
#include <QXmlStreamReader>

class XmlFamilyModel : public QObject
{
Q_OBJECT
public:
    class VoltageModel_T
    {
    public:
        QString min;
        QString max;
    };

    class TemperatureModel_T
    {
    public:
        QString min;
        QString max;
    };

    class CurrentModel_T
    {
    public:
        QString lowest;
        QString run;
    };

    class PeripheralModel_T
    {
    public:
        QString type;
    };

    class McuModel_T
    {
    public:
        QString company;
        QString family;
        QString subfamily;
        QString name;
        QString package;
        QString core;
        QString frequency;
        QString ram;
        QString io;
        QString flash;
        VoltageModel_T voltage;
        TemperatureModel_T temperature;
        CurrentModel_T current;
        QList<PeripheralModel_T> peripheral;
    };

signals:

public:
    explicit XmlFamilyModel(QObject *parent = nullptr);

private:
    static McuModel_T readMcuModel(QXmlStreamReader *reader);

public:

    [[nodiscard]] static QList<McuModel_T> getMcuModels();

    [[nodiscard]] static McuModel_T getMcuModel(const QString &mcuName);

    [[nodiscard]] static QString getMcuPackPath(const QString &mcuName);
};


#endif //CHMCUINIT_XMLFAMILYMODEL_H
