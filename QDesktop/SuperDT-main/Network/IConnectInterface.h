#ifndef ICONNECTINTERFACE_H
#define ICONNECTINTERFACE_H

#include "AbsConnection.h"
#include "CConnectManager.h"



class IConnectInterface
{
public:
    virtual void setConnectionProxy(CConnectManager *pConnectManager) = 0;

    virtual void protocolChanged(AbsConnection::EnmProtocolType enmType){
        Q_UNUSED(enmType)
    }
    virtual void stateChanged(AbsConnection::EnmState enmState){
        Q_UNUSED(enmState)
    }
    virtual void connectStateChanged(QString strIp,quint16 nPort,bool bState){
        Q_UNUSED(strIp)
        Q_UNUSED(nPort)
        Q_UNUSED(bState)
    }
    virtual void dataArrive(QString strIp,quint16 nPort,QByteArray byteArr){
        Q_UNUSED(strIp)
        Q_UNUSED(nPort)
        Q_UNUSED(byteArr)
    }
    virtual void send(QByteArray byteArr){
        Q_UNUSED(byteArr)
    }
protected:
    CConnectManager *m_pConnectManager = nullptr;
};


#endif // ICONNECTINTERFACE_H
