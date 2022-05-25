#include "CUdp.h"

CUdp::CUdp(QObject *parent)
    : AbsConnection(parent)
{
//    emit sigProtocolChanged(EnmProtocolType::ENM_UDP);

    m_pUdp = new QUdpSocket(this);
    connect(m_pUdp,&QUdpSocket::readyRead,[=]{
        emit sigStateChanged(EnmState::ENM_CONNECTED);
        emit sigReadyRead(m_pUdp);

        QHostAddress hostAddress;
        quint16 nPort;
        QByteArray byteArr;
        byteArr.resize(m_pUdp->pendingDatagramSize());

        m_pUdp->readDatagram(byteArr.data(),byteArr.size(),&hostAddress,&nPort);

        emit sigDataArrive(hostAddress.toString(),nPort,byteArr);
        emit sigConnectChanged(hostAddress.toString(),nPort,true); //在Udp中  收到数据即认为连接过 没有断开的概念
    });
}

CUdp::~CUdp()
{
    stopConnection();
}

bool CUdp::startConnection(void *pInfo)
{
    StSocketInfo *pSocketInfo = static_cast<StSocketInfo *>(pInfo);

    m_pUdp->abort();
    if (false == m_pUdp->bind(QHostAddress(pSocketInfo->strIp),pSocketInfo->nPort)) {
        return false;
    }


    if(m_pUdp->open(QIODevice::ReadWrite)){
        emit sigStateChanged(EnmState::ENM_READYED);
        return true;
    }else{
        qWarning()<<"Udp打开失败";
        return false;
    }
}

void CUdp::stopConnection()
{
    m_pUdp->close();
    emit sigStateChanged(EnmState::ENM_NOT_READY);
}

int CUdp::sendAll(QByteArray byteArr)
{
    emit sigSend(byteArr);
    return m_pUdp->write(byteArr); //@TODO 发给谁  是否应该发给以发送过的所有连接
}

int CUdp::send(QString strIp, quint16 nPort, QByteArray byteArr)
{
    emit sigSend(byteArr);
    return m_pUdp->writeDatagram(byteArr,QHostAddress(strIp),nPort);
}

QString CUdp::errorString()
{
    QString strError;
    switch (m_pUdp->error()) {
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
