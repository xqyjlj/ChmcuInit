#ifndef MCU_XML_H
#define MCU_XML_H

#include <QObject>
#include <QXmlStreamReader>
class mcu_xml : public QObject
{
    Q_OBJECT
public:
    explicit mcu_xml(QObject* parent = nullptr);
public:
    QStringList read_pin(QString path, QStringList list, int indel);
signals:

public slots:
};

#endif // MCU_XML_H
