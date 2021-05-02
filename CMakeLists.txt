cmake_minimum_required(VERSION 3.5)

project(ChmcuInit)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(QRC_FILE Assets/Assets.qrc)
qt6_add_resources(QRC ${QRC_FILE})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}
        Model
        Choose
        Config
        Config/Mcu
        Config/View
        Project
        Coder
        Coder/Hal
        Config/Mcu/GPIO)

add_executable(${PROJECT_NAME}
        WIN32
        main.cpp
        MainWindow.cpp MainWindow.h MainWindow.ui
        Model/XmlFamilyModel.cpp Model/XmlFamilyModel.h
        Debug.cpp Debug.h
        Model/XmlIpModel.cpp Model/XmlIpModel.h
        BaseObject.cpp BaseObject.h
        Model/XmlPinModel.cpp Model/XmlPinModel.h
        FormHome.cpp FormHome.h FormHome.ui
        Choose/DialogChooseMcu.cpp Choose/DialogChooseMcu.h Choose/DialogChooseMcu.ui
        Choose/TableWidgetMcu.cpp Choose/TableWidgetMcu.h
        Choose/TextBrowserReadMe.cpp Choose/TextBrowserReadMe.h
        ${QRC}
        Choose/TreeWidgetChooseMcu.cpp Choose/TreeWidgetChooseMcu.h
        Config/Mcu/FormMcuConfig.cpp Config/Mcu/FormMcuConfig.h Config/Mcu/FormMcuConfig.ui
        Model/XmlIoModel.cpp Model/XmlIoModel.h
        Config/GraphicsView.cpp Config/GraphicsView.h
        Project/FileProject.cpp Project/FileProject.h
        Project/DialogSaveFile.cpp Project/DialogSaveFile.h Project/DialogSaveFile.ui
        Coder/CoderStreamWriter.cpp Coder/CoderStreamWriter.h
        Coder/Hal/CoderHalIo.cpp Coder/Hal/CoderHalIo.h
        Model/XmlFileProjectModel.cpp Model/XmlFileProjectModel.h
        Config/View/LabelPin.cpp Config/View/LabelPin.h
        Config/View/WidgetLQFP48.cpp Config/View/WidgetLQFP48.h Config/View/WidgetLQFP48.ui
        Config/View/LabelComment.cpp Config/View/LabelComment.h
        Config/Mcu/TreeWidgetChooseIp.cpp Config/Mcu/TreeWidgetChooseIp.h
        Config/Mcu/GPIO/FormGpio.cpp Config/Mcu/GPIO/FormGpio.h Config/Mcu/GPIO/FormGpio.ui
        Config/Mcu/GPIO/TableWidgetGpio.cpp Config/Mcu/GPIO/TableWidgetGpio.h
        Config/Mcu/GPIO/FormGpioAttribute.cpp Config/Mcu/GPIO/FormGpioAttribute.h Config/Mcu/GPIO/FormGpioAttribute.ui
        Config/Mcu/GPIO/ComboBoxGpioAttribute.cpp Config/Mcu/GPIO/ComboBoxGpioAttribute.h)

target_link_libraries(ChmcuInit PRIVATE Qt${QT_VERSION_MAJOR}::Widgets )



