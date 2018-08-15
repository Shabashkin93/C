#include "tcpclient.h"

TcpClient::TcpClient(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
}


void TcpClient::startClient()
{
    socket->connectToHost(_adress,_port);
    connect(socket, &QTcpSocket::readyRead, this, &TcpClient::socketReady);
    connect(socket, &QTcpSocket::disconnected, this, &TcpClient::stopClient);
}

void TcpClient::stopClient()
{
    socket->deleteLater();
}

void TcpClient::socketReady()
{
    if (socket->waitForConnected(500))
    {
            socket->waitForReadyRead(500);
            qDebug()<<"socket connect to adress" << _adress << "and port" << _port;
            Data = socket->readAll();
            qDebug()<<Data;
    }
}

void TcpClient::setHostAdress(const QString &host){
    this->_adress = host;
}

void TcpClient::setHostPort(quint16 port){
    this->_port = port;
}

void TcpClient::sendMsg(const QByteArray &data){
    if(socket->state() == QAbstractSocket::ConnectedState)
        {
            socket->write(data); //write the data itself
            qDebug()<< "msg are send";
        }
    else{
        qDebug()<< "Msg are not send((";
    }
}
