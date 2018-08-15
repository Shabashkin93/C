#include <QCoreApplication>
#include "tcpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TcpServer mserver;
    mserver.startServer();
    TcpServer nserver;
    nserver.setHostAdress("127.0.2.1");
    nserver.setHostPort(8080);
    nserver.startServer();
//    mserver.sendMsg("Hi");
//    nserver.stopServer();
//    mserver.stopServer();
    return a.exec();
}
