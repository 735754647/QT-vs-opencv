#ifndef VCONNECT_H
#define VCONNECT_H

#include <QFrame>
#include "VSessionInterface.h"
#include "IConnectInterface.h"

namespace Ui {
class VConnect;
}

class VConnect : public QFrame/*,public IConnectInterface*/
{
    Q_OBJECT

public:
    explicit VConnect(QWidget *parent = nullptr);
    ~VConnect();

protected:
    virtual void protocolChanged(AbsConnection::EnmProtocolType enmType);
    virtual void stateChanged(AbsConnection::EnmState enmState);
    virtual void connectStateChanged(QString strIp,quint16 nPort,bool bState);
    virtual void dataArrive(QString strIp,quint16 nPort,QByteArray byteArr);
private slots:
    void on_comboBox_protocal_currentIndexChanged(int index);

private:
    void init();
    void refreshAvailableDev(); //刷新可用的Ip 或 可用的串口
private:
    Ui::VConnect *ui;
    QStringList m_strListBtnText;
};

#endif // VCONNECT_H
