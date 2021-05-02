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
 ** 2021-04-21     xqyjlj       the first version        xqyjlj@126.com
 **/

#ifndef CHMCUINIT_BASEOBJECT_H
#define CHMCUINIT_BASEOBJECT_H

#include <QObject>
#include "XmlFamilyModel.h"
#include "XmlIpModel.h"
#include "XmlPinModel.h"
#include "Debug.h"
#include "XmlIoModel.h"
#include "FileProject.h"

class BaseObject : public QObject
{
Q_OBJECT
public:
    explicit BaseObject(QObject *parent);

signals:

    void signalConfigProject();

private:
    QString m_corePath;
    QString m_ProjectDir;
    QString m_ProjectName;

    FileProject *m_fileProject = nullptr;

    XmlFamilyModel::McuModel_T m_mcuModel;
    XmlIoModel::IoModel_T m_ioModel;

    QList<XmlPinModel::PinModel_T> m_pinModels;
    QList<XmlFamilyModel::McuModel_T> m_mcuModels;
    QList<XmlIpModel::IpTagModel_T> m_ipTagModels;
    QList<XmlIpModel::IpModel_T> m_ipModels;

    QStringList m_ipNames;

    QMap<QString, XmlIoModel::TableModel_T> m_mapIoTableModel;

    XmlFileProjectModel::ConfigurationModel_T m_configurationModel;

public:

    [[nodiscard]] const XmlFileProjectModel::ConfigurationModel_T &getConfigurationModel();

    [[nodiscard]] QString getProjectPath() const;

    [[nodiscard]] const QString &getProjectName() const;

    void setProjectName(const QString &projectName);

    [[nodiscard]] QString getProjectDir() const;

    void setProjectDir(const QString &projectDir);

    [[nodiscard]] const QList<XmlIpModel::IpModel_T> &getIpModels() const;

    [[nodiscard]] const QList<XmlIpModel::IpTagModel_T> &getIpTagModels() const;

    [[nodiscard]] FileProject *getFileProject() const;

    [[nodiscard]] const QMap<QString, XmlIoModel::TableModel_T> &getTableModelMap() const;

    [[nodiscard]] const XmlIoModel::IoModel_T &getIoModel() const;

    [[nodiscard]] const QList<XmlFamilyModel::McuModel_T> &getMcuModels() const;

    void setMcuModels(const QList<XmlFamilyModel::McuModel_T> &mcuModels);

    [[nodiscard]] const QList<XmlPinModel::PinModel_T> &getPinModels() const;

    void setPinModels(const QList<XmlPinModel::PinModel_T> &pinModels);

    [[nodiscard]] const XmlFamilyModel::McuModel_T &getMcuModel() const;

    void setMcuModel(const XmlFamilyModel::McuModel_T &mcuModel);

    void setMcuModel(const QString &mcuName);

    [[nodiscard]] const QString &getCorePath() const;

    void setCorePath(const QString &corePath);

    [[nodiscard]] QString getMcuReadMePath(const QString &fileName) const;

    [[nodiscard]] QString getMcuPackPath(const QString &fileName) const;

    [[nodiscard]] QString getMcuPackPath() const;

    void configProject();

    [[nodiscard]] QString getMcuPath(const QString &file) const;

    void saveProject();

    [[nodiscard]] QString getMcuName() const;

private:
    void setPinModels();

    void setIpModels();

    void setIoModel(QString &path);

    void setTableModelMap();
};


#endif //CHMCUINIT_BASEOBJECT_H
