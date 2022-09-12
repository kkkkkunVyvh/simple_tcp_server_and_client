#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("服务器");

    server = new QTcpServer;

    server->listen(QHostAddress::AnyIPv4,8000);

    //客户端发起连接，server发出信号
    connect(server,&QTcpServer::newConnection,this,&Widget::newClientHandler);
}

void Widget::newClientHandler()
{
    QTcpSocket *socket = server->nextPendingConnection();

    QString IP = socket->peerAddress().toString(); //获取ip地址
    QString port = QString::number(socket->peerPort()); //获取端口号（客户端的）

    ui->ipLineEdit->setText(IP);
    ui->portLineEdit->setText(port);

    //启动线程
    myThread *t = new myThread(socket);
    t->start();

    //接收从thread发过来的socket
    connect(t,&myThread::sendToWidget,this,&Widget::threadSlots);
}

void Widget::threadSlots(QTcpSocket *s)
{
    QString IP = s->peerAddress().toString(); //获取ip地址
    QString port = QString::number(s->peerPort()); //获取端口号（客户端的）
    QString str = (QString)s->readAll();

    ui->ipLineEdit->setText(IP);
    ui->portLineEdit->setText(port);
    ui->lineEdit->setText(str);
}

Widget::~Widget()
{
    delete ui;
}

