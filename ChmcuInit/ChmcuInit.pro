#-------------------------------------------------
# Copyright (c) 2020-2020,  by xqyjlj
#
#  SPDX-License-Identifier: LGPL
#
#  Change Logs:
#  Date           Author       Notes
#  2021-01-15     xqyjlj       the first version
#-------------------------------------------------

QT      += core gui
QT      += xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChmcuInit
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        Code/CodeAnnotationt.cpp \
        Code/CodeCreateDriver.cpp \
        Code/CodeDriver.cpp \
        Code/CodeFunction.cpp \
        Keil/KeilXml.cpp \
        Mcu/McuChip.cpp \
        Mcu/McuPin.cpp \
        Mcu/McuScene.cpp \
        Mcu/McuTssop24.cpp \
        Mcu/McuXml.cpp \
        Window/WindowPin.cpp \
        main.cpp \
        master.cpp

HEADERS += \
        Code/CodeAnnotationt.h \
        Code/CodeCreateDriver.h \
        Code/CodeDriver.h \
        Code/CodeFunction.h \
        Keil/KeilXml.h \
        Mcu/McuChip.h \
        Mcu/McuPin.h \
        Mcu/McuScene.h \
        Mcu/McuTssop24.h \
        Mcu/McuXml.h \
        Window/WindowPin.h \
        master.h

FORMS += \
        master.ui

INCLUDEPATH += \
        Keil\
        Mcu\
        Window\
        Code
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/quazip/lib/ -lquazip
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/quazip/lib/ -lquazipd
else:unix: LIBS += -L$$PWD/lib/quazip/lib/ -lquazip

INCLUDEPATH += $$PWD/lib/quazip/include
DEPENDPATH += $$PWD/lib/quazip/include
