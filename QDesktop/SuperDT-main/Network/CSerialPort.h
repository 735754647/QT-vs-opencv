#ifndef CSERIALPORT_H
#define CSERIALPORT_H

#include "AbsConnection.h"
#include <QSerialPort>
#include <QTimer>

class CSerialPort : public AbsConnection
{
    Q_OBJECT
public:
    explicit CSerialPort(QObject *parent = 0);
    ~CSerialPort();

    virtual bool startConnection(void *pInfo); //@TODO 应有返回值
    virtual void stopConnection(); //断开连接 或 停止监听
    virtual int sendAll(QByteArray byteArr);
    virtual int send(QString strIp,quint16 nPort,QByteArray byteArr);
    virtual QString errorString();
private:
    QSerialPort *m_pSerialPort = nullptr;

    QByteArray m_byteArrRecv;

    bool m_bAutoSubpackage = true; //是否开启自动分包
    QTimer *m_pTimer = nullptr;
};

#endif // CSERIALPORT_H
