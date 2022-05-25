#include "CTcpServer.h"

CTcpServer::CTcpServer(QObject *parent)
    : AbsConnection(parent)
{
//    emit sigProtocolChanged(EnmProtocolType::ENM_TCP_SERVER);

    m_pTcpServer = new QTcpServer(this);
    connect(m_pTcpServer,&QTcpServer::newConnection,[=]{
         QTcpSocket *pTcpSocket = m_pTcpServer->nextPendingConnection();
         qDebug()<<"peerName:"<<pTcpSocket->peerName();
         QString strKey = toKey(pTcpSocket);
         m_mapClients.insert(strKey,pTcpSocket);
         emit sigConnectChanged(pTcpSocket->peerAddress().toString(),pTcpSocket->peerPort(),true);
         emit sigStateChanged(EnmState::ENM_CONNECTED); //有一个连接就通知已连接
         connect(pTcpSocket,&QTcpSocket::disconnected,[=]{
             qWarning()<<"客户端断开"<<pTcpSocket->peerAddress().toString()<<pTcpSocket->peerPort();
             emit sigConnectChanged(pTcpSocket->peerAddress().toString(),pTcpSocket->peerPort(),false);
             QString strKey = toKey(pTcpSocket);
             if(m_mapClients.contains(strKey)){
                 QTcpSocket *pTmp = m_mapClients.value(strKey);
                 if(nullptr != pTmp){
                     pTmp->close();
                     pTmp->deleteLater();
                 }

                 m_mapClients.remove(strKey);

                 if(0 == m_mapClients.count()){
                     emit sigStateChanged(EnmState::ENM_READYED);
                 }
             }
         });
//         connect(pTcpSocket, &QAbstractSocket::disconnected,
//                     pTcpSocket, &QObject::deleteLater);
         connect(pTcpSocket,&QTcpSocket::readyRead,[=]{
             emit sigReadyRead(pTcpSocket);

             QByteArray byteArr = pTcpSocket->readAll();
             emit sigDataArrive(pTcpSocket->peerAddress().toString(),pTcpSocket->peerPort(),byteArr);
         });
    });

}

CTcpServer::~CTcpServer()
{
    stopConnection();
}

bool CTcpServer::startConnection(void *pInfo)
{
    StSocketInfo *pSocketInfo = static_cast<StSocketInfo *>(pInfo);
    bool bSuccess = m_pTcpServer->listen(QHostAddress(pSocketInfo->strIp),pSocketInfo->nPort);

    if (bSuccess) {
        emit sigStateChanged(EnmState::ENM_READYED); //已准备好
    }

    return bSuccess;
}

void CTcpServer::stopConnection()
{
    foreach(QTcpSocket *pSocket,m_mapClients.values()){
        if(pSocket){
            pSocket->close();
            pSocket->deleteLater();
        }
    }
    m_mapClients.clear();

    m_pTcpServer->close();
    emit sigStateChanged(EnmState::ENM_NOT_READY);
}

int CTcpServer::sendAll(QByteArray byteArr)
{
    int nSize = 0;
    QMapIterator<QString,QTcpSocket *> mapIterator(m_mapClients);
    while(mapIterator.hasNext()){
        mapIterator.next();

        QTcpSocket *pTcpSocket = mapIterator.value();
        int size = pTcpSocket->write(byteArr);
        nSize += size;
    }
    emit sigSend(byteArr);

    return nSize;
}

int CTcpServer::send(QString strIp, quint16 nPort, QByteArray byteArr)
{
    int nSize = 0;
    QString strKey = strIp + ":" + QString::number(nPort);
    if(m_mapClients.contains(strKey)){
        QTcpSocket *pTcpSocket = m_mapClients.value(strKey);
        nSize = pTcpSocket->write(byteArr);
    }
    emit sigSend(byteArr);

    return nSize;
}

QString CTcpServer::errorString()
{
    QString strError;
    switch (m_pTcpServer->serverError()) {
    case QAbstractSocket::ConnectionRefusedError:
        strError = tr("连接被拒绝或超时");
        break;
    case QAbstractSocket::RemoteHostClosedError:
        strError = tr("远程主机已关闭");
        break;
    case QAbstractSocket::HostNotFoundError:
        strError = tr("主机未找到");
        break;
    case QAbstractSocket::SocketAccessError:
        strError = tr("套接字访问");
        break;
    case QAbstractSocket::SocketResourceError:
        strError = tr("套接字资源");
        break;
    case QAbstractSocket::SocketTimeoutError:
        strError = tr("套接字超时");
        break;
    case QAbstractSocket::DatagramTooLargeError:
        strError = tr("数据报过大");
        break;
    case QAbstractSocket::NetworkError:
        strError = tr("网络错误");
        break;
    case QAbstractSocket::AddressInUseError:
        strError = tr("地址已被用");
        break;
    case QAbstractSocket::SocketAddressNotAvailableError:
        strError = tr("套接字地址不可用");
        break;
    case QAbstractSocket::UnsupportedSocketOperationError:
        strError = tr("不支持的套接字");
        break;
    case QAbstractSocket::UnfinishedSocketOperationError:
        strError = tr("套接字操作错误");
        break;
    case QAbstractSocket::ProxyAuthenticationRequiredError:
        strError = tr("代理身份验证请求错误");
        break;
    case QAbstractSocket::UnknownSocketError:
        strError = tr("未知的套接字错误");
        break;
    case QAbstractSocket::ProxyConnectionRefusedError:
        strError = tr("代理连接请求错误");
        break;
    case QAbstractSocket::ProxyConnectionClosedError:
        strError = tr("代理连接关闭错误");
        break;
    case QAbstractSocket::ProxyConnectionTimeoutError:
        strError = tr("代理连接超时");
        break;
    case QAbstractSocket::ProxyNotFoundError:
        strError = tr("代理找不到");
        break;
    case QAbstractSocket::ProxyProtocolError:
        strError = tr("代理协议错误");
        break;
    default:
        break;
    }

    return strError;
}

QString CTcpServer::toKey(QTcpSocket *pSocket)
{
    QString strKey = pSocket->peerAddress().toString() + ":" +
                     QString::number(pSocket->peerPort());

    return strKey;
}

