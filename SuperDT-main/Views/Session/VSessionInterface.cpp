#include "VSessionInterface.h"


//VSessionInterface::VSessionInterface(QWidget *parent)
//    :QFrame(parent)
//{

//}

void VSessionInterface::setSessionProxy(CConnectManager *pConnectManager)
{
    m_pConnectManager = pConnectManager;

//    QObject::connect(m_pConnection,&AbsConnection::sigStateChanged,this,&VSessionInterface::slotStateChanged);
//    QObject::connect(m_pConnection,&AbsConnection::sigConnectChanged,this,&VSessionInterface::slotConnectStateChanged);
//    QObject::connect(m_pConnection,&AbsConnection::sigDataArrive,this,&VSessionInterface::slotDataArrive);

//    connect(m_pConnect,&AbsConnection::sigStateChanged,[=](AbsConnection::EnmState enmState){});
//    connect(m_pConnect,&AbsConnection::sigConnectChanged,[=](QString strIp,quint16 nPort,bool bState){});
//    connect(m_pConnect,&AbsConnection::sigReadyRead,[=](QIODevice *pIODevice){});
//    connect(m_pConnect,&AbsConnection::sigDataArrive,[=](QString strIp,quint16 nPort,QByteArray byteArr){});
}
