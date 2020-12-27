#ifndef KEIL_XML_H
#define KEIL_XML_H

#include <QObject>
#include <QString>
class keil_xml : public QObject
{
    Q_OBJECT
public:
    QString project_name;


public:
    explicit keil_xml(QObject* parent = nullptr);

    bool creat_keil_project(void);
signals:

public slots:
};

#endif // KEIL_XML_H
