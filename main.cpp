#include <QCoreApplication>
#include <chatclient.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ChatClient client;

    client.connectToServer("127.0.0.1", 33333);
    client.waitForConnected(-1);

    char msg[1024] = {0};
    printf("please input message(exit with 'exit'): \n");
    while(1)
    {
        gets(msg);
        if(0 == strcmp(msg,"exit"))
        {
            break;
        }
        if(strlen(msg) > 0) {
            if(!client.writeDataToServer(msg,strlen(msg) + 1))
            {
                printf("write data failed!\n");
                break;
            }
        }
    }
    client.closeClient();
    return a.exec();
}
