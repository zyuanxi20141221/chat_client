#ifndef CHATCLIENT_H
#define CHATCLIENT_H
#include <QTcpSocket>

class ChatClient : public QTcpSocket
{
    Q_OBJECT

public:
    ChatClient(QTcpSocket *parent = NULL);
    ~ChatClient();

    void connectToServer(const char* ip, quint16 port); //连接到服务端
    void closeClient();  //关闭客户端
    bool writeDataToServer(const char* data, quint64 len); //写数据
    bool writeDataToServer(const QByteArray &data);

protected:
    void parseData(const char* data, quint64 len); //数据处理

private slots:
    void onConnected();
    void onReadyRead();
    void onSendData(const char* data);

private:
    enum {BUFFERSIZE_MAX = 1024};
};

#endif // CHATCLIENT_H
