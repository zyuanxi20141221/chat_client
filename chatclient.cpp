#include "chatclient.h"
#include <QHostAddress>

ChatClient::ChatClient(QObject *parent)
   :QTcpSocket(parent)
{
    printf("ChatClient");
    connect(this, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(this, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

ChatClient::~ChatClient()
{
    printf("~ChatClient");
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
    qint64 ret = writeData(data,len);
    if(ret <= 0)
    {
        return false;
    }
    waitForBytesWritten(-1);
    printf("send data %s \n", data);
    waitForReadyRead(-1);
    return true;
}

void ChatClient::parseData(const char* data, quint64 len)
{
    printf("receive data %s\n", data);
}

void ChatClient::onConnected()
{
    printf("connected %d \n", socketDescriptor());
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
