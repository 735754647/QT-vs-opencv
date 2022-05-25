#ifndef VRECEIVETRIG_H
#define VRECEIVETRIG_H

#include <QWidget>
#include <QEvent>

struct StReceiveTrig{
    StReceiveTrig(QString rtext,QString stext,bool hex)
    {
        strRText = rtext;
        strSText = stext;
        bHex = hex;
    }
    QString strRText; //条件文本
    QString strSText; //发送文本
    bool bHex;
};
namespace Ui {
class VReceiveTrig;
}

class VReceiveTrig : public QWidget
{
    Q_OBJECT

public:
    explicit VReceiveTrig(QWidget *parent = nullptr);
    ~VReceiveTrig();

    StReceiveTrig info();
    void setChecked(bool bIsChecked);
public slots:
    void slotDataArrive(QString strIp, quint16 nPort, QByteArray byteArr);
signals:
    void sigSelected();
    void sigReceiveTrig(StReceiveTrig stData); //达到触发条件
private:
    virtual bool eventFilter(QObject *watched, QEvent *event);
public:
    Ui::VReceiveTrig *ui;
};

#endif // VRECEIVETRIG_H
