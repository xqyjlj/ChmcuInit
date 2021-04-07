include(../../ChmcuInit.pri)

QT       += core gui xml widgets webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Debug.cpp \
    DialogChooseBoard.cpp \
    DialogChooseMcu.cpp \
    FileManage.cpp \
    FormChipConfig/FormChipConfig.cpp \
    FormChipConfig/GraphicsViewMcu.cpp \
    FormChipConfig/Parameter/STM32/FormPinAttribute.cpp \
    FormChipConfig/Parameter/STM32/FormSTM32PeripheralsModeConfig.cpp \
    FormChipConfig/Parameter/STM32/STM32XmlRead.cpp \
    FormChipConfig/ChipView/LabelPin.cpp \
    FormChipConfig/ChipView/WidgetLQFP48.cpp \
    FormChipConfig/TreeWidgetChooseFunction.cpp \
    FormHome.cpp \
    TableWidegtMcuInfo.cpp \
    FormChipConfig/TreeWidgetChooseIp.cpp \
    TreeWidgetChooseMcuBoard.cpp \
    XmlRead.cpp \
    XmlWrite.cpp \
    demo/demo_chip.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    Debug.h \
    DialogChooseBoard.h \
    DialogChooseMcu.h \
    FileManage.h \
    FormChipConfig/FormChipConfig.h \
    FormChipConfig/GraphicsViewMcu.h \
    FormChipConfig/Parameter/STM32/FormPinAttribute.h \
    FormChipConfig/Parameter/STM32/FormSTM32PeripheralsModeConfig.h \
    FormChipConfig/Parameter/STM32/STM32Model.h \
    FormChipConfig/Parameter/STM32/STM32XmlRead.h \
    FormChipConfig/TreeWidgetChooseFunction.h \
    FormHome.h \
    MainWindow.h \
    FormChipConfig/ChipView/LabelPin.h \
    FormChipConfig/ChipView/WidgetLQFP48.h \
    Model.h \
    TableWidegtMcuInfo.h \
    FormChipConfig/TreeWidgetChooseIp.h \
    TreeWidgetChooseMcuBoard.h \
    XmlRead.h \
    XmlWrite.h \
    demo/demo_chip.h

FORMS += \
    DialogChooseBoard.ui \
    DialogChooseMcu.ui \
    FormChipConfig/FormChipConfig.ui \
    FormChipConfig/Parameter/STM32/FormPinAttribute.ui \
    FormChipConfig/Parameter/STM32/FormSTM32PeripheralsModeConfig.ui \
    FormHome.ui \
    MainWindow.ui \
    FormChipConfig/ChipView/WidgetLQFP48.ui

INCLUDEPATH += \
    FormChipConfig/ChipView \
    FormChipConfig/Parameter/STM32 \
    FormChipConfig/

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qrc.qrc

DISTFILES +=
