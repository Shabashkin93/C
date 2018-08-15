#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QObject>
class TcpClient: public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent =nullptr);
//    ~myclient();
public slots:
    void setHostAdress(const QString &host);
    void setHostPort(quint16 port);
    void startClient();
    void stopClient();
    void socketReady();
    void sendMsg(const QByteArray &data);
private:
    QTcpSocket* socket;
    QByteArray Data;
    QString _adress = "127.0.0.1";
    quint16 _port = 1234;
};
#endif // TCPCLIENT_H
