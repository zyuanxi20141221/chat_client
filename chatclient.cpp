#include "chatclient.h"
#include <QHostAddress>
#include "writethread.h"

ChatClient::ChatClient(QTcpSocket *parent)
   :QTcpSocket(parent)
{
    printf("ChatClient::ChatClient\n");
    connect(this, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(this, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

ChatClient::~ChatClient()
{
    printf("ChatClient::~ChatClient\n");
}

void ChatClient::connectToServer(const char* ip, quint16 port)
{
    QString strIp(ip);
    QHostAddress address;
    address.setAddress(strIp);
    connectToHost(address,port);
}

void ChatClient::closeClient()
{
    disconnectFromHost();
    close();
}

bool ChatClient::writeDataToServer(const char* data, quint64 len)
{
    if(data == NULL || len <=0)
    {
        return false;
    }
    qint64 ret = write(data,len);
    if(ret <= 0)
    {
        return false;
    }
    waitForBytesWritten(-1);
    printf("send data: %s \n", data);
    return true;
}

bool ChatClient::writeDataToServer(const QByteArray &data)
{
    if(data == NULL)
    {
        return false;
    }
    qint64 ret = write(data);
    if(ret <= 0)
    {
        return false;
    }
    waitForBytesWritten(-1);
    printf("send data %s \n", data);
    return true;
}

void ChatClient::parseData(const char* data, quint64 len)
{
    printf("receive data: %s\n", data);
}

void ChatClient::onConnected()
{
    printf("connected %d \n", socketDescriptor());
    WriteThread *writeThread = new WriteThread(NULL, this);
    writeThread->start();
}

void ChatClient::onReadyRead()
{
    printf("ready read!\n");
    char data[BUFFERSIZE_MAX] = {0};
    qint64 len = read(data, BUFFERSIZE_MAX);
    if(len <=0) {
        return;
    } else {
        parseData(data, len);
    }
}

void ChatClient::onSendData(const char* data)
{
    printf("ChatClient::onSendData %s\n", data);
    writeDataToServer(data, strlen(data));
}
