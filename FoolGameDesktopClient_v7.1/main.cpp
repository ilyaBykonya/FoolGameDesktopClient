#include <QApplication>
#include "ApplicationGUIPart/MainApplicationWindow/ApplicationWindow.h"
#include <QFile>
int main(int argc, char *argv[])
{
    srand(time(0));
    QApplication app(argc, argv);
//    QString hostAddress;
//    quint16 portNumber;

//    QFile readConnectToHostInfoFile;
//    readConnectToHostInfoFile.setFileName("../ApplicationData/ConnectToServerInfo/host_address.txt");
//    if(!readConnectToHostInfoFile.exists())
//    {
//        QMessageBox::critical(nullptr, "Error", "Файл host_address.txt не найден.");
//        return -1;
//    }
//    if(!readConnectToHostInfoFile.open(QFile::OpenModeFlag::ReadOnly))
//    {
//        QMessageBox::critical(nullptr, "Error", "Файл host_address.txt не может быть открыт.");
//        return -1;
//    }
//    QTextStream readConnectToHostInfoStream(&readConnectToHostInfoFile);
//    readConnectToHostInfoStream >> hostAddress;

//    readConnectToHostInfoFile.setFileName("../ApplicationData/ConnectToServerInfo/port_number.txt");
//    if(!readConnectToHostInfoFile.exists())
//    {
//        QMessageBox::critical(nullptr, "Error", "Файл port_number.txt не найден.");
//        return -1;
//    }
//    if(!readConnectToHostInfoFile.open(QFile::OpenModeFlag::ReadOnly))
//    {
//        QMessageBox::critical(nullptr, "Error", "Файл port_number.txt не может быть открыт.");
//        return -1;
//    }
//    readConnectToHostInfoStream >> portNumber;






    ApplicationWindow mainWindow("127.0.0.1", 2323);
    QObject::connect(&mainWindow, &ApplicationWindow::signalExitButtonWasClicked, qApp, &QApplication::quit);
    mainWindow.show();
    return app.exec();
}
