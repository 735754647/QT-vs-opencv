#include "CTcpClient.h"

CTcpClient::CTcpClient(QObject *parent)
    : AbsConnection(parent)
{
//    emit sigProtocolChanged(EnmProtocolType::ENM_TCP_CLIENT);

    //    m_pHostAddress = new QHostAddress();
    m_pTcpClient = new QTcpSocket(this);
    connect(m_pTcpClient, &QTcpSocket::connected,[=]{
        QString strIp = m_pTcpClient->peerAddress().toString();
        quint16 nPort = m_pTcpClient->peerPort();
        emit sigConnectChanged(strIp,nPort,true);
        //        emit sigStateChanged(EnmState::ENM_CONNECTED);
    });
    connect(m_pTcpClient, &QTcpSocket::disconnected,[=]{
        QString strIp = m_pTcpClient->peerAddress().toString();
        quint16 nPort = m_pTcpClient->peerPort();
        emit sigConnectChanged(strIp,nPort,false);
        //        emit sigStateChanged(EnmState::ENM_NOT_READY);
    });
    connect(m_pTcpClient, &QTcpSocket::stateChanged,[=](QAbstractSocket::SocketState enmState){
        switch (enmState) {
        case QAbstractSocket::HostLookupState:
            emit sigStateChanged(EnmState::ENM_READYED);break;
        case QAbstractSocket::ConnectingState:
            emit sigStateChanged(EnmState::ENM_READYED);break;
        case QAbstractSocket::ConnectedState:
            emit sigStateChanged(EnmState::ENM_CONNECTED);break;
        case QAbstractSocket::ClosingState:
            emit sigStateChanged(EnmState::ENM_NOT_READY);break;
        default:
            break;
        }
    });
    connect(m_pTcpClient, &QTcpSocket::readyRead,[=]{ //收数据
        emit sigReadyRead(m_pTcpClient);

        QByteArray byteArr = m_pTcpClient->readAll();
        emit sigDataArrive(m_pTcpClient->peerAddress().toString(),m_pTcpClient->peerPort(),byteArr);
    });
}

CTcpClient::~CTcpClient()
{

}

bool CTcpClient::startConnection(void *pInfo)
{
    StSocketInfo *pSocketInfo = static_cast<StSocketInfo*>(pInfo);
    m_pTcpClient->abort();
    //    m_pHostAddress->setAddress(pSocketInfo->strIp);
    QHostAddress hostAddress(pSocketInfo->strIp);
    m_pTcpClient->connectToHost(hostAddress,pSocketInfo->nPort); //@MAJR 使用waitForConnect(1000);

    return true; //@Note 默认客户端准备成功
}

void CTcpClient::stopConnection()
{
    emit sigStateChanged(EnmState::ENM_NOT_READY);
    //    m_pTcpClient->disconnectFromHost(); //@BUG 崩溃

    m_pTcpClient->close(); //会先调用disconnectFromHost
}

int CTcpClient::sendAll(QByteArray byteArr)
{
    emit sigSend(byteArr);
    return m_pTcpClient->write(byteArr);
}

int CTcpClient::send(QString strIp, quint16 nPort, QByteArray byteArr)
{
    Q_UNUSED(strIp)
    Q_UNUSED(nPort)

    emit sigSend(byteArr);
    return m_pTcpClient->write(byteArr);
}

QString CTcpClient::errorString()
{
    QString strError;
    switch (m_pTcpClient->error()) {
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
