#ifndef ABSCONNECTION_H
#define ABSCONNECTION_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QSerialPort>
#include <QDebug>

/*@MAJR
 * connectToHost();可能传入HostAddress时用new的方式不容易导致崩溃 目前有时崩溃 仍需测试
*/
struct StSocketInfo{
    StSocketInfo(QString _strIp,quint16 _nPort):strIp(_strIp),nPort(_nPort){}
    QString strIp;
//    QHostAddress hostAddress;
    quint16 nPort;
};

struct StSerialInfo{
    QString strPortName;
    QSerialPort::BaudRate enmBaudRate;
    QSerialPort::DataBits enmDataBits;
    QSerialPort::Parity enmParity;
    QSerialPort::StopBits enmStopBits;
    QSerialPort::FlowControl enmFlowControl;
    bool bAutoSubpackage; //自动分包开关
};



class AbsConnection:public QObject
{
    Q_OBJECT
public:
    explicit AbsConnection(QObject *parent);

    virtual bool startConnection(void *pInfo) = 0; //连接 参数是Ip  或者串口的参数
    virtual void stopConnection() = 0; //断开连接 或 停止监听
    virtual int sendAll(QByteArray byteArr) = 0;
    virtual int send(QString strIp,quint16 nPort,QByteArray byteArr) = 0;
    virtual QString errorString() = 0;

    enum EnmState{
        ENM_NOT_READY = 0,
        ENM_READYED,
        ENM_CONNECTED,
    };

    enum EnmProtocolType{
        ENM_TCP_CLIENT,
        ENM_TCP_SERVER,
        ENM_UDP,
        ENM_SERIAL,
    };


signals:
    void sigStateChanged(EnmState enmState); //未连接
    void sigConnectChanged(QString strIp,quint16 nPort,bool bState);
    void sigReadyRead(QIODevice *pIODevice); //外部进行类型转换 串口和Tcp Udp有不同的数据读法
    void sigDataArrive(QString strIp,quint16 nPort,QByteArray byteArr);
    void sigSend(QByteArray &byteArr);
};

#endif // ABSCONNECTION_H
