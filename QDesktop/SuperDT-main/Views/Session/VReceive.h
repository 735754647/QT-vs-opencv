#ifndef VRECEIVE_H
#define VRECEIVE_H

#include <QWidget>
#include "IConnectInterface.h"
#include <QMenu>
#include <QBuffer>

namespace Ui {
class VReceive;
}

class VReceive : public QWidget,public IConnectInterface
{
    Q_OBJECT

public:
    explicit VReceive(QWidget *parent = nullptr);
    ~VReceive();

    virtual void setConnectionProxy(CConnectManager *pConnectManager);


protected:
    virtual void dataArrive(QString strIp, quint16 nPort, QByteArray byteArr);
    virtual void send(QByteArray byteArr);
private slots:
    void on_pushButton_clear_clicked();

private:
    QString timestamp(); //时间戳
private:
    Ui::VReceive *ui;
};

#endif // VRECEIVE_H
