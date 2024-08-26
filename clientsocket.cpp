#include "clientsocket.h"
#include<QHostAddress>
clientSocket::clientSocket(QObject *parent) : QObject(parent)
{
    m_socket=new QTcpSocket(this);
    connect(m_socket,&QTcpSocket::connected,[this]()
    {
       //发射信号
       emit connectSucessed();
    });
    connect(m_socket,&QTcpSocket::readyRead,this,&clientSocket::handleReadSlot);
}
//处理读数据
void clientSocket::handleReadSlot()
{
    m_buffer.append( m_socket->readAll());
    while(static_cast<unsigned long long>(m_buffer.size())>=sizeof(size_t))
    {
        size_t size;
        memcpy(&size,m_buffer.data(),sizeof(size_t));
        if(static_cast<unsigned long long>(m_buffer.size()) < size + sizeof(size_t))
        {
            break;
        }
        emit dataRecevied(m_buffer.mid(sizeof(size_t),size));
        m_buffer.remove(0,size + sizeof(size_t));
    }
}
//连接服务器
void clientSocket::connectToServer(const QString &ip,quint16 port)
{
    m_ip=ip;
    m_port=port;

    m_socket->connectToHost(QHostAddress(ip),port);

}
int clientSocket::writeData(const QByteArray & data)
{
    size_t len=data.size();
    //  先发送数据包大小
    m_socket->write((const char*)&len,sizeof(len));
    //在发送数据包内容
    m_socket->write(data);
    return len;
}
//析构函数
clientSocket::~clientSocket()
{

}
