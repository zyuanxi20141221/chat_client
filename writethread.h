#ifndef WRITETHREAD_H
#define WRITETHREAD_H

#include <QThread>
#include <chatclient.h>

class WriteThread : public QThread
{
    Q_OBJECT

signals:
    void sendData(const char* data);

public:
    WriteThread(QObject *parent = NULL, ChatClient *client = NULL);
    ~WriteThread();
    void run();

private:
    ChatClient *client;
};

#endif // WRITETHREAD_H
