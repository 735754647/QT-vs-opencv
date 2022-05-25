#ifndef CTCPSERVER_H
#define CTCPSERVER_H

#include "AbsConnection.h"
#include <QTcpServer>

class CTcpServer : public AbsConnection
{
    Q_OBJECT
public:
    explicit CTcpServer(QObject *parent = 0);
    ~CTcpServer();
    virtual bool startConnection(void *pInfo);
    virtual void stopConnection(); //断开连接 或 停止监听
    virtual int sendAll(QByteArray byteArr);
    virtual int send(QString strIp,quint16 nPort,QByteArray byteArr);
    virtual QString errorString();
private:
    QString toKey(QTcpSocket *pSocket);
private:
    QTcpServer *m_pTcpServer = nullptr;
    QMap<QString,QTcpSocket *> m_mapClients;
};

#endif // CTCPSERVER_H
