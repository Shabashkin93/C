#include <QCoreApplication>
#include "tcpclient.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TcpClient Client;
    Client.startClient();
    TcpClient ClientTwo;
    ClientTwo.setHostAdress("127.0.2.1");
    ClientTwo.setHostPort(8080);
    ClientTwo.startClient();
    Client.sendMsg("messsg");
    return a.exec();
}
