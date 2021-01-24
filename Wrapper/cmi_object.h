#ifndef CMI_OBJECT_H
#define CMI_OBJECT_H

#include <QObject>

class Cmi_Object : public QObject
{
    Q_OBJECT
public:
    explicit Cmi_Object(QObject *parent = nullptr);

signals:

};

#endif // CMI_OBJECT_H
