#ifndef CTCPCLIENT_H
#define CTCPCLIENT_H

#include "AbsConnection.h"

class CTcpClient : public AbsConnection
{
    Q_OBJECT
public:
    explicit CTcpClient(QObject *parent = 0);
    ~CTcpClient();

    virtual bool startConnection(void *pInfo);
    virtual void stopConnection(); //断开连接 或 停止监听
    virtual int sendAll(QByteArray byteArr);
    virtual int send(QString strIp,quint16 nPort,QByteArray byteArr);
    virtual QString errorString();
private:
    QTcpSocket *m_pTcpClient = nullptr;
    QHostAddress *m_pHostAddress = nullptr;
};

#endif // CTCPCLIENT_H
