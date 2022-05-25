#include "CHelper.h"

#include <QHostAddress>
#include <QHostInfo>
QStringList CHelper::localIPv4List()
{
    QHostInfo hostInfo = QHostInfo::fromName(QHostInfo::localHostName());

    QList<QHostAddress> listAddr = hostInfo.addresses();
    QStringList listIPv4;
    foreach (QHostAddress addr,listAddr) {
        if (QAbstractSocket::IPv4Protocol == addr.protocol()) {
            listIPv4.append(addr.toString());
        }
    }
    //列表不带回环地址
    if(!listIPv4.contains("127.0.0.1"))
        listIPv4 << "127.0.0.1";

    return listIPv4;
}

#include <QSerialPort>
#include <QSerialPortInfo>
QStringList CHelper::serialportList()
{
    QStringList CommPortList;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if (serial.open(QIODevice::ReadWrite))
        {
            CommPortList.append(serial.portName());
            serial.close();
        }
    }

    return CommPortList;
}

void CHelper::recursiveInstallEventFilter(QObject *pObject)
{
    if(pObject->children().count() > 0) {
        foreach (QObject *objChild, pObject->children()) {
            objChild->installEventFilter(pObject);
            recursiveInstallEventFilter(objChild);
        }
    }
}
#include <QPushButton>
#include <QLabel>
#include <QObject>

void CHelper::recursiveResetUIText(QObject *pObject)
{
    if(pObject->children().count() > 0) {
        foreach (QObject *objChild, pObject->children()) {
            //重新显示文本
//            qDebug()<<"transplate ui:"<<objChild;
            if(QPushButton *pBtn = qobject_cast<QPushButton *>(objChild)){
                qDebug()<<"$$$:"<<objChild<<pBtn->text();
                pBtn->setText(QPushButton::tr(pBtn->text().toUtf8().data()));
            }/*else if(QLabel *pForm = qobject_cast<QLabel *>(objChild)){
                pForm->setText(QObject::tr(pForm->text().toStdString().c_str()));
            }*/
            recursiveResetUIText(objChild);
        }
    }
}
