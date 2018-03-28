#include "writethread.h"

WriteThread::WriteThread(QObject *parent, ChatClient *client) : QThread(parent)
{
    this->client = client;
    connect(this, SIGNAL(sendData(const char*)), client, SLOT(onSendData(const char*)));
}

WriteThread::~WriteThread()
{
    printf("WriteThread::~WriteThread \n");
}

void WriteThread::run()
{
    while(1)
    {
        msleep(1000);
        char *s = "data from qt";
        printf("WriteThread::run %s\n", s);
        emit sendData(s);
    }
}

