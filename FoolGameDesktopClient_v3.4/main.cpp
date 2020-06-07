#include "ApplicationGUIPart/MainApplicationWindow/ApplicationWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ApplicationWindow wid;
    QObject::connect(&wid, &ApplicationWindow::signalExitButtonWasClicked, qApp, &QApplication::quit);
    wid.show();
    return a.exec();
}
