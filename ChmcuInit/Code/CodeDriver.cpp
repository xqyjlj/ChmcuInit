#include "CodeDriver.h"

CodeDriver::CodeDriver(QObject* parent) : QObject(parent)
{
    fun_code_annotation = new CodeAnnotationt(this);
    fun_code_create_driver = new CodeCreateDriver(this);
}

