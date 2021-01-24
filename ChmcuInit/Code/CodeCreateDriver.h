#ifndef CODECREATEDRIVER_H
#define CODECREATEDRIVER_H

#include <QObject>
#include <QString>
class CodeCreateDriver : public QObject
{
    Q_OBJECT
public:
    explicit CodeCreateDriver(QObject* parent = nullptr);
    void copy(QString srczip, QString srcfile, QString aimpath);
};

#endif // CODECREATEDRIVER_H
