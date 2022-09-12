#include "widget.h"
#include "ui_widget.h"

#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("客户端");

    //初始化
    socket= new QTcpSocket;
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_cancelButton_clicked()
{
    this->close();
}

void Widget::on_connectButton_clicked()
{
    //获取ip与端口
    QString IP = ui->ipLineEdit->text();
    QString port = ui->portLineEdit->text();

    //连接服务器
    socket->connectToHost(QHostAddress(IP),port.toShort());

    //连接服务器成功，socket会发出信号
    connect(socket,&QTcpSocket::connected,[this]()
    {
        QMessageBox::information(this,"连接提示","连接服务器成功");
        this->hide();
        Form *f = new Form(socket);
        f->show();
    });

    //连接断开，socket也会发出信号
    connect(socket,&QTcpSocket::disconnected,[this]()
    {
        QMessageBox::warning(this,"连接提示","服务器断开连接");
    });
}
