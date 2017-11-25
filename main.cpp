#include "gui.h"
#include <QApplication>

//Starting point, which boots up the application and shows a window with all of the GUI work on it.
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
