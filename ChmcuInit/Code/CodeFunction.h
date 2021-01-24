#ifndef CODEFUNCTION_H
#define CODEFUNCTION_H

#include <QObject>
#include <QStringList>
class CodeFunction : public QStringList
{
public:
    enum types
    {
        t_void,
        t_uint8,
        t_uint16,
        t_uint32,
    };
public:
    explicit CodeFunction();
    void set_function_info(QString name, QStringList parameter, enum types type, bool isstatic);
    void set_annotation(QString msg);
    void set_details(QString msg);
    void set_details(QString variable, QString value);
    void set_end(void);
signals:

};

#endif // CODEFUNCTION_H
