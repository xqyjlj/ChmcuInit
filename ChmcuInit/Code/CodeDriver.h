#ifndef CODEDRIVER_H
#define CODEDRIVER_H

#include <QObject>
#include "CodeAnnotationt.h"
#include "CodeCreateDriver.h"
class CodeDriver : public QObject
{
    Q_OBJECT
public:
    explicit CodeDriver(QObject* parent = nullptr);

private:
    CodeAnnotationt* fun_code_annotation;
    CodeCreateDriver* fun_code_create_driver;
signals:

};

#endif // CODEDRIVER_H
