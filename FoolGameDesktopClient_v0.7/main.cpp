#include <QApplication>
#include "ApplicationGUIPart/MainApplicationWindow/ApplicationWindow.h"

int main(int argc, char *argv[])
{
    srand(time(0));
    QApplication app(argc, argv);
    ApplicationWindow mainWindow;
    QObject::connect(&mainWindow, &ApplicationWindow::signalExitButtonWasClicked, qApp, &QApplication::quit);
    mainWindow.show();
    return app.exec();
}
