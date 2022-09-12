#include "mythread.h"

myThread::myThread(QTcpSocket *s)
{
    socket = s;
}

void myThread::run()
{
    //服务器收到客户端发送的消息，会发出readyRead的信号
    connect(socket,&QTcpSocket::readyRead,this,&myThread::clientInfoSlots);

}

void myThread::clientInfoSlots()
{
    //发送信号
    emit sendToWidget(socket);
}
