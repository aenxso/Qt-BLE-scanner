#include "BT_Widget.h"

#include <QApplication>
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    BT_Widget w;
    QCoreApplication::setApplicationName("battery-test");
    QCoreApplication::setApplicationVersion("1.0");
    new Controller();

//    w.show();

    return a.exec();
}
