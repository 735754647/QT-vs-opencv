#ifndef VSEND_H
#define VSEND_H

#include <QWidget>
#include "IConnectInterface.h"
#include <QTimer>
#include "VQuickSend.h"
#include "VReceiveTrig.h"

namespace Ui {
class VSend;
}

class VSend : public QWidget, public IConnectInterface
{
    Q_OBJECT
public:
    enum EnmType{
        ENM_ALL_CONNECT = 0,
        ENM_CUSTOM_CONNECT,
        ENM_IP_PORT,
    };

    explicit VSend(QWidget *parent = nullptr);
    ~VSend();

    virtual void setConnectionProxy(CConnectManager *pConnectManager);
private:
    void processSendText(QString &strText,bool &bHex);
    void selectQuickSend(VQuickSend *pQuickSend);
    void selectReceiveTrig(VReceiveTrig *pReceiveTrig);
protected:
    virtual void protocolChanged(AbsConnection::EnmProtocolType enmType);
    virtual void connectStateChanged(QString strIp,quint16 nPort,bool bState);
    virtual void dataArrive(QString strIp,quint16 nPort,QByteArray byteArr);
private slots:
    void on_pushButton_send_clicked();

    void on_checkBox_auto_send_clicked(bool checked);

    void on_spinBox_auto_span_valueChanged(int arg1);

    void on_tabWidget_send_currentChanged(int index);

    void on_pushButton_quick_add_clicked();

    void on_pushButton_quick_del_clicked();

    void on_checkBox_quick_hex_clicked(bool checked);

    void on_spinBox_quick_span_valueChanged(int arg1);

    void on_pushButton_loop_start_clicked(bool checked);

    void on_pushButton_trig_add_clicked();

    void on_pushButton_trig_del_clicked();

    void on_checkBox_trig_hex_clicked(bool checked);

    void on_pushButton_trig_start_clicked(bool checked);

    void on_pushButton_clear_clicked();

private:
    Ui::VSend *ui;

    QTimer *m_pTimerAutoSend = nullptr;

    //快捷发送
    VQuickSend *m_pSelectedQuickSend = nullptr;
    QVector<VQuickSend *> m_vecQuickSend;
    QTimer *m_pTimerLoopQuickSend = nullptr;
    int m_nCurrentSendIndex = 0;
    //触发器
    VReceiveTrig *m_pSelectedReceiveTrig = nullptr;
    QVector<VReceiveTrig *> m_vecReceiveTrig;
};

#endif // VSEND_H
