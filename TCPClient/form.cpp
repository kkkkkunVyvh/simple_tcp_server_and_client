#include "form.h"
#include "ui_form.h"

Form::Form(QTcpSocket *s,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    socket = s;
}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_2_clicked()
{
    ui->lineEdit->clear();
}

//发送数据给服务器
void Form::on_pushButton_clicked()
{
    QString s = ui->lineEdit->text();
    QByteArray ba;
    ba.append(s);
    socket->write(ba);
}
