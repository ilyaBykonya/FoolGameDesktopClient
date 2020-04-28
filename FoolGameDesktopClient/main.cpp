#include <QApplication>
#include "ConnectWithServerPart/ApplicationEthernetController.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ApplicationEthernetController appCon;
    appCon.show();
    return a.exec();
}
