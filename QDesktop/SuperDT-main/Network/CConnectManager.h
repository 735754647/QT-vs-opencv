#ifndef CCONNECTMANAGER_H
#define CCONNECTMANAGER_H

#include <QObject>
#include "AbsConnection.h"

class CConnectManager : public AbsConnection
{
    Q_OBJECT
public:
    explicit CConnectManager(QObject *parent = 0);
    ~CConnectManager();

    void resetConnect(AbsConnection::EnmProtocolType enmType);
    virtual bool startConnection(void *pInfo);
    virtual void stopConnection();
    virtual int sendAll(QByteArray byteArr);
    virtual int send(QString strIp,quint16 nPort,QByteArray byteArr);
    virtual QString errorString();

    int sendBytes(){return m_nSendBytes;}
    int recvBytes(){return m_nRecvBytes;}
signals:
    void sigProtocolChanged(AbsConnection::EnmProtocolType enmType);

    //发送接收计数
    void sigRecvBytes(int nBytes);
    void sigSendBytes(int nBytes);
public slots:
    void slotRecount(); //重新计数
private:
    AbsConnection *m_pConnect = nullptr;

    int m_nSendBytes = 0; //发送总字节数
    int m_nRecvBytes = 0; //接收总字节数
};


#endif // CCONNECTMANAGER_H
