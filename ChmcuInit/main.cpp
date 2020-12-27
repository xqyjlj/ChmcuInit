#include "master.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    master w;
    w.showMaximized();
    w.show();

    return a.exec();
}
