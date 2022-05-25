#ifndef VCONNECTION_H
#define VCONNECTION_H

#include <QFrame>
#include "IConnectInterface.h"
#include "CConnectManager.h"
#include <QStandardItemModel>
#include <QSerialPortInfo>

namespace Ui {
class VConnection;
}

class VConnection : public QFrame,public IConnectInterface
{
    Q_OBJECT

public:
    explicit VConnection(QWidget *parent = 0);
    ~VConnection();

    void refreshAvailableDev(); //刷新可用IP、端口 或 串口号、波特率
public:
    virtual void setConnectionProxy(CConnectManager *pConnectManager);
    virtual void protocolChanged(AbsConnection::EnmProtocolType enmType);
    virtual void stateChanged(AbsConnection::EnmState enmState);
private:
    void init();
private slots:
    void on_comboBox_protocal_currentIndexChanged(int index);

    void on_pushButton_connect_clicked(bool checked);
    void slotArgReset();
private:
    Ui::VConnection *ui;
    QStringList m_strListBtnText;

    QStandardItemModel *m_pPortOrSerialNameModel = nullptr;
};

#endif // VCONNECTION_H
