#include "CodeFunction.h"

CodeFunction::CodeFunction() : QStringList()
{
}

void CodeFunction::set_function_info(QString name, QStringList parameter, enum types type, bool isstatic)
{
    QString msg;
    if(isstatic)
    {
        msg.append("static ");
    }
    switch (type)
    {
        case t_void:
            msg.append("void ");
            break;
        case t_uint8:
            msg.append("uint8_t ");
            break;
        case t_uint16:
            msg.append("uint16_t ");
            break;
        case t_uint32:
            msg.append("uint32_t ");
            break;
        default:
            break;
    }
    msg.append(name + QString("("));
    int length = parameter.length();
    for(int i = 0; i < length; i++)
    {
        if(i <= length - 2)
        {
            msg.append(parameter.at(i) + QString(","));
        }
        else
        {
            msg.append(parameter.at(i) + QString(")"));
        }
    }
    msg.append(QString("{"));
    this->append(msg);
}

void CodeFunction::set_annotation(QString msg)
{
    if(msg.contains("\n"))
    {
        msg.replace("\n", "\n*");
        this->append(QString("/**\n*") + msg + QString("\n*/"));
    }
    else
    {
        this->append(msg);
    }
}

void CodeFunction::set_details(QString msg)
{
    this->append(msg);
}

void CodeFunction::set_details(QString variable, QString value)
{
    this->append(variable + QString("=") + value);
}

void CodeFunction::set_end(void)
{
    this->append(QString("}\n"));
}
