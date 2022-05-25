#include "CConnectManager.h"
#include "CTcpClient.h"
#include "CTcpServer.h"
#include "CUdp.h"
#include "CSerialPort.h"

CConnectManager::CConnectManager(QObject *parent)
    : AbsConnection(parent)
{

}

CConnectManager::~CConnectManager()
{

}

void CConnectManager::resetConnect(AbsConnection::EnmProtocolType enmType)
{
    if(nullptr != m_pConnect){
        m_pConnect->stopConnection();
        delete m_pConnect;
        m_pConnect = nullptr;
    }

    switch (enmType) {
    case AbsConnection::ENM_TCP_CLIENT:
        m_pConnect = new CTcpClient(this);
        break;
    case AbsConnection::ENM_TCP_SERVER:
        m_pConnect = new CTcpServer(this);
        break;
    case AbsConnection::ENM_UDP:
        m_pConnect = new CUdp(this);
        break;
    case AbsConnection::ENM_SERIAL:
        m_pConnect = new CSerialPort(this);
        break;
    default:
        break;
    }

    connect(m_pConnect,&AbsConnection::sigStateChanged,this,&CConnectManager::sigStateChanged);
    connect(m_pConnect,&AbsConnection::sigConnectChanged,this,&CConnectManager::sigConnectChanged);
    connect(m_pConnect,&AbsConnection::sigReadyRead,this,&CConnectManager::sigReadyRead);
    connect(m_pConnect,&AbsConnection::sigDataArrive,this,&CConnectManager::sigDataArrive);
    connect(m_pConnect,&AbsConnection::sigSend,this,&CConnectManager::sigSend);
    connect(m_pConnect,&AbsConnection::sigDataArrive,this,[=](QString strIp,quint16 nPort,QByteArray byteArr){
        Q_UNUSED(strIp)
        Q_UNUSED(nPort)

        m_nRecvBytes += byteArr.size();
        emit sigRecvBytes(m_nRecvBytes);
    });

    emit sigProtocolChanged(enmType);
}

bool CConnectManager::startConnection(void *pInfo)
{
    return m_pConnect->startConnection(pInfo);
}

void CConnectManager::stopConnection()
{
    m_pConnect->stopConnection();
}

int CConnectManager::sendAll(QByteArray byteArr)
{
    int nSize = m_pConnect->sendAll(byteArr);

    //发送计数
    if(-1 != nSize){
        m_nSendBytes += nSize;
        emit sigSendBytes(m_nSendBytes);
    }

    return nSize;
}

int CConnectManager::send(QString strIp, quint16 nPort, QByteArray byteArr)
{
    int nSize = m_pConnect->send(strIp,nPort,byteArr);

    //发送计数
    if(-1 != nSize){
        m_nSendBytes += nSize;
        emit sigSendBytes(m_nSendBytes);
    }

    return nSize;
}

QString CConnectManager::errorString()
{
    return m_pConnect->errorString();
}

void CConnectManager::slotRecount()
{
    m_nSendBytes = 0;
    m_nRecvBytes = 0;
    emit sigSendBytes(m_nSendBytes);
    emit sigRecvBytes(m_nRecvBytes);
}
