#ifndef VSESSIONINTERFACE_H
#define VSESSIONINTERFACE_H

#include "AbsConnection.h"
#include <QFrame>
#include "CConnectManager.h"

class VSessionInterface /*: public QFrame*/
{
//    Q_OBJECT
public:
//    VSessionInterface(QWidget *parent = nullptr);


    void setSessionProxy(CConnectManager *pConnectManager);
protected:
    virtual void protocolChanged(AbsConnection::EnmProtocolType enmType){Q_UNUSED(enmType)}
    virtual void stateChanged(AbsConnection::EnmState enmState) = 0;
    virtual void connectStateChanged(QString strIp,quint16 nPort,bool bState) = 0;
    virtual void dataArrive(QString strIp,quint16 nPort,QByteArray byteArr) = 0;
public:
    CConnectManager *m_pConnectManager = nullptr;
};

#endif // VSESSIONINTERFACE_H
