#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QObject>
#include<QString>
#include<QTcpSocket>
#include<QByteArray>
class clientSocket : public QObject
{
    Q_OBJECT
public:
    explicit clientSocket(QObject *parent = nullptr);
    //析构函数
    ~clientSocket();
    //连接服务器
    void connectToServer(const QString &ip,quint16 port);
    int writeData(const QByteArray & data);

signals:
    void connectSucessed();
    void dataRecevied(const QByteArray &data);
public slots:
    void handleReadSlot();
private:
    QTcpSocket * m_socket;
    QString m_ip;
    quint16 m_port;
    //数据缓冲区
    QByteArray m_buffer;
};

#endif // CLIENTSOCKET_H
