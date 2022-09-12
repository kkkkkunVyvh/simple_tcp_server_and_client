#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QDebug>

class myThread :  public QThread
{
    Q_OBJECT
public:
    explicit myThread(QTcpSocket *s);
    void run();

signals:
    void sendToWidget(QTcpSocket *s);

public slots:
    void clientInfoSlots();

private:
    QTcpSocket *socket;

};

#endif // MYTHREAD_H
