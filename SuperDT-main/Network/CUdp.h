#ifndef CUDP_H
#define CUDP_H

#include "AbsConnection.h"
#include <QUdpSocket>

class CUdp : public AbsConnection
{
    Q_OBJECT
public:
    explicit CUdp(QObject *parent = 0);
    ~CUdp();

    virtual bool startConnection(void *pInfo);
    virtual void stopConnection(); //断开连接 或 停止监听
    virtual int sendAll(QByteArray byteArr);
    virtual int send(QString strIp,quint16 nPort,QByteArray byteArr);
    virtual QString errorString();
private:
    QUdpSocket *m_pUdp = nullptr;
};

#endif // CUDP_H
