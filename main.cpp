#include <QApplication>
#include <QPushButton>
#include <QStyleFactory>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFont font;
    font.setFamily(u8"YaHei Consolas Hybrid");
    font.setPointSize(12);
    QApplication::setFont(font);

    auto *baseObject = new BaseObject(&a);
    ASSERT_X(baseObject, u8"main", u8"空指针-> baseObject");

    MainWindow w;
    w.setBaseObject(baseObject);
    w.show();

    return QApplication::exec();
}
