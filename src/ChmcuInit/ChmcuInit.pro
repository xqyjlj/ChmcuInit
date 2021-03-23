include(../../ChmcuInit.pri)

QT       += core gui xml widgets webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    debug.cpp \
    dialog_choose_board.cpp \
    dialog_choose_mcu.cpp \
    form_home_widget.cpp \
    main.cpp \
    MainWindow.cpp \
    tablewidegt_mcu_info.cpp \
    textbrowser_mcu_board_info.cpp \
    treewidget_choose_mcu_board.cpp \
    xml_read.cpp \
    xml_write.cpp

HEADERS += \
    MainWindow.h \
    debug.h \
    dialog_choose_board.h \
    dialog_choose_mcu.h \
    form_home_widget.h \
    mcu_model.h \
    tablewidegt_mcu_info.h \
    textbrowser_mcu_board_info.h \
    treewidget_choose_mcu_board.h \
    xml_read.h \
    xml_write.h

FORMS += \
    MainWindow.ui \
    dialog_choose_board.ui \
    dialog_choose_mcu.ui \
    form_home_widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qrc.qrc
