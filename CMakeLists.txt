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
        Project)

add_executable(${PROJECT_NAME} main.cpp
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
        Config/Mcu/TreeWidgetMcuChooseFunction.cpp Config/Mcu/TreeWidgetMcuChooseFunction.h
        Config/Mcu/FormMcuPinAttribute.cpp Config/Mcu/FormMcuPinAttribute.h Config/Mcu/FormMcuPinAttribute.ui
        Model/XmlIoModel.cpp Model/XmlIoModel.h
        Config/Mcu/ComboBoxMcuPinAttribute.cpp Config/Mcu/ComboBoxMcuPinAttribute.h
        Config/GraphicsView.cpp Config/GraphicsView.h
        Project/FileProject.cpp Project/FileProject.h
        Project/DialogSaveFile.cpp Project/DialogSaveFile.h Project/DialogSaveFile.ui)

target_link_libraries(ChmcuInit PRIVATE Qt${QT_VERSION_MAJOR}::Widgets )



