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
        code/code_use.cpp \
        keil/keil_xml.cpp \
        main.cpp \
        master.cpp \
        mcu/mcu_chip.cpp \
        mcu/mcu_pin.cpp \
        mcu/mcu_scene.cpp \
        mcu/mcu_tssop24.cpp \
        mcu/mcu_xml.cpp \
        window/window_pin.cpp

HEADERS += \
        code/code_use.h \
        keil/keil_xml.h \
        master.h \
        mcu/mcu_chip.h \
        mcu/mcu_pin.h \
        mcu/mcu_scene.h \
        mcu/mcu_tssop24.h \
        mcu/mcu_xml.h \
        window/window_pin.h

FORMS += \
        master.ui

INCLUDEPATH += \
        keil\
        mcu\
        window
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
