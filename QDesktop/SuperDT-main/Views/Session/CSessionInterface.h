#ifndef CSESSIONINTERFACE_H
#define CSESSIONINTERFACE_H

#include "AbsConnection.h"

class CSessionInterface
{
public:
    CSessionInterface(AbsConnection *pConnection);

private slots:
    virtual void connectStateChanged(QString strIp,quint16 nPort,bool bState) = 0;
    virtual void dataArrive(QString strIp,quint16 nPort,QByteArray byteArr) = 0;
private:
    AbsConnection *m_pConnection;
};

#endif // CSESSIONINTERFACE_H
