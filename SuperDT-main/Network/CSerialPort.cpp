#include "CSerialPort.h"
#include <QTimer>
#include <QTime>

CSerialPort::CSerialPort(QObject *parent)
    : AbsConnection(parent)
{
    //解决断包思路 波特率1200时 一个字节需6.6ms 数据发送过慢  计算机收到一个字节即会发出readyRead信号
    //因此将两个字节的接收时间设为超时时间  超时未收到才发出readyRead 间隔之内收到直接合并为一个信号
    m_pTimer = new QTimer(this);
    connect(m_pTimer,&QTimer::timeout,[=]{
        emit sigDataArrive("",0,m_byteArrRecv);//已超时 将合并到的包发送出去
        m_byteArrRecv.clear();
        m_pTimer->stop();
//        qDebug()<<"超时已发出"<<QTime::currentTime();
    });

    m_pSerialPort = new QSerialPort(this);
    connect(m_pSerialPort,&QSerialPort::readyRead,[=]{
        if(m_bAutoSubpackage){
            m_byteArrRecv.append(m_pSerialPort->readAll()); //未超时 合并包
            m_pTimer->start();
//            qDebug()<<"合并"<<QTime::currentTime();
        }else{
            emit sigDataArrive(m_pSerialPort->portName(),0,m_pSerialPort->readAll());
        }

        emit sigReadyRead(m_pSerialPort);
    });
}

CSerialPort::~CSerialPort()
{
    stopConnection();
}

bool CSerialPort::startConnection(void *pInfo)
{
    StSerialInfo *pStSerialInfo = static_cast<StSerialInfo *>(pInfo);
    m_pSerialPort->setPortName(pStSerialInfo->strPortName);
    m_pSerialPort->setBaudRate(pStSerialInfo->enmBaudRate);
    m_pSerialPort->setDataBits(pStSerialInfo->enmDataBits);
    m_pSerialPort->setParity(pStSerialInfo->enmParity);
    m_pSerialPort->setStopBits(pStSerialInfo->enmStopBits);
    m_pSerialPort->setFlowControl(pStSerialInfo->enmFlowControl);
    m_bAutoSubpackage = pStSerialInfo->bAutoSubpackage;
    //计算每字节数据所需的时间 ms
    double dTimeByte = 1000.0 * 8/(double)pStSerialInfo->enmBaudRate;

//    qDebug()<<"每字节需时间："<<dTimeByte<<" ms";
    dTimeByte += dTimeByte; //
    m_pTimer->setInterval((int)(dTimeByte > 3 ? dTimeByte : 3)); //最大精度1ms  误差经常3~5ms  超时时间过长会导致粘包
//    qDebug()<<"设定超时时间："<<m_pTimer->interval()<<" ms";

    if(m_pSerialPort->open(QIODevice::ReadWrite)){
        emit sigStateChanged(EnmState::ENM_READYED); //默认连接
        emit sigStateChanged(EnmState::ENM_CONNECTED);
        return true;
    }else{
        qWarning()<<"串口打开失败！";
        return false;
    }
}

void CSerialPort::stopConnection()
{
    m_pSerialPort->close();
    emit sigStateChanged(EnmState::ENM_NOT_READY);
}

int CSerialPort::sendAll(QByteArray byteArr)
{

    emit sigSend(byteArr);

    return m_pSerialPort->write(byteArr);
}

int CSerialPort::send(QString strIp, quint16 nPort, QByteArray byteArr)
{
    Q_UNUSED(strIp)
    Q_UNUSED(nPort)

    emit sigSend(byteArr);

    return m_pSerialPort->write(byteArr);
}

QString CSerialPort::errorString()
{
    QString strError;
    switch (m_pSerialPort->error()) {
    case QSerialPort::NoError:
        strError = tr("正常");
        break;
    case QSerialPort::OpenError:
        strError = tr("设备已被打开");
        break;
    case QSerialPort::NotOpenError:
        strError = tr("设备未打开");
        break;
    case QSerialPort::TimeoutError:
        strError = tr("操作超时");
        break;
    case QSerialPort::ReadError:
        strError = tr("读取设备错误");
        break;
    case QSerialPort::WriteError:
        strError = tr("写入设备错误");
        break;
    case QSerialPort::ResourceError:
        strError = tr("设备从系统中消失");
        break;
    default:
        strError = tr("打开失败");
        break;
    }
    return strError;
}
