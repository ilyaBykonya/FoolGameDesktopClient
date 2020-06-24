#include <QApplication>
#include "ApplicationGUIPart/MainApplicationWindow/ApplicationWindow.h"
#include "InstanceGUIPart/GameTable/Player/ShowUserInfo/ShowUserInfoWidget.h"
int main(int argc, char *argv[])
{
    srand(time(0));
    QApplication app(argc, argv);
    ApplicationWindow mainWindow;

    mainWindow.show();
    return app.exec();
}
