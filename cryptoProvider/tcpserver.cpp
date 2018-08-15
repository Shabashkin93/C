#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);
    connect(server, &QTcpServer::newConnection, this, &TcpServer::onNewConnection);
}

void TcpServer::onNewConnection(){
    socket = server->nextPendingConnection();
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    socket->write("Hello client");
    socket->flush();
    socket->disconnectFromHost();
}

void TcpServer::setHostAdress(QString host){
    this->_adress = host;
}

void TcpServer::setHostPort(quint16 port){
    this->_port = port;
}

void TcpServer::startServer(){
    if(!server->listen(QHostAddress(_adress), _port)){
        qDebug()<< server->errorString();
    }
    else
    {
        qDebug()<<"Server started on ip" << _adress << "and port"<< _port;
    }
}

void TcpServer::stopServer(){
    server->close();
    qDebug() <<"Server on ip" << _adress << "and port"<< _port << "is stopped";
}

void TcpServer::sendMsg(const QByteArray &data){
    if(server->isListening()){
        socket->write(data);
        socket->flush();
    }
    else{
        qDebug()<<"error send";
    }
}

void TcpServer::onsocketkReady(){
    data = socket->readAll();
    qDebug()<<"Data" << data;
}
