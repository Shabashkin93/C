#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr);


signals:

public slots:
    void onNewConnection();
    void setHostAdress(QString host);
    void setHostPort(quint16 port);
    void startServer();
    void stopServer();
    void sendMsg(const QByteArray &data);
    void onsocketkReady();
private:
    QTcpServer *server;
    QTcpSocket *socket;
    QString _adress = "127.0.0.1";
    quint16 _port = 1234;
    QByteArray data;
};

#endif // TCPSERVER_H
