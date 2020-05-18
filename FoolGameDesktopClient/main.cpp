#include <QApplication>
#include <QtWidgets>
#include "ConnectWithServerPart/ApplicationEthernetController.h"
#include "ApplicationGUIPart/MainApplicationWindow/ApplicationWindow.h"
#include <ctime>

int main(int argc, char *argv[])
{

    srand(time(0));
    QApplication app(argc, argv);
    ApplicationWindow wid;
    wid.setFixedSize(400, 600);
    QObject::connect(&wid, &ApplicationWindow::signalExitButtonWasClicked, qApp, &QApplication::quit);
    wid.show();
    return app.exec();
}
