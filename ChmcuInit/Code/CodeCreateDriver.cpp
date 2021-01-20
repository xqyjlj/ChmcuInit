#include "CodeCreateDriver.h"
#include "quazip.h"
#include "quazipfile.h"
#include <QDebug>
#include <QIODevice>

#include "quazipdir.h"
#include <QDir>
#include <QFile>
#include "CodeFunction.h"
CodeCreateDriver::CodeCreateDriver(QObject* parent) : QObject(parent)
{
    copy(":/driver/res/driver/hc32/hc32f002_driver.zip", "src/gpio.c",  "./untitle/driver/src/gpio.c");
    copy(":/driver/res/driver/hc32/hc32f002_driver.zip", "inc/gpio.h",  "./untitle/driver/inc/gpio.h");
    CodeFunction code;
    QStringList list;
    list << QString("void");
    code.set_function_info(QString("led_init"), list, CodeFunction::t_void, true);
    code.set_annotation(QString("PA8->LED0\nPA9->LED1"));
    code.set_details(QString("LED0"), QString("1"));
    code.set_end();
    qDebug().noquote() << code;
}

void CodeCreateDriver::copy(QString srczip, QString srcfile, QString aimpath)
{
    QuaZip zip(srczip);
    zip.open(QuaZip::mdUnzip);
    zip.setCurrentFile(srcfile);
    QuaZipFile  zipfile(&zip);
    zipfile.open(QIODevice::ReadOnly);

    aimpath.replace("\\", "/");

    if(aimpath.contains("/"))
    {
        QString path = aimpath.mid(0, aimpath.lastIndexOf("/"));
        QDir dir;
        if(!dir.exists(path))
        {
            dir.mkpath(path);
        }
    }
    QFile file(aimpath);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(zipfile.readAll());

    zipfile.close();
    zip.close();
}
