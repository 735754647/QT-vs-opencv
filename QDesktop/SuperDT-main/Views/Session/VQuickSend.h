#ifndef VQUICKSEND_H
#define VQUICKSEND_H

#include <QWidget>
#include "IConnectInterface.h"
#include <QEvent>

struct StQuickSend
{
    StQuickSend(QString text,bool hex,int span)
    {
        strText = text;
        bHex = hex;
        nSpan = span;
    }
    QString strText;
    bool bHex;
    int nSpan;
};
namespace Ui {
class VQuickSend;
}

class VQuickSend : public QWidget/*,public IConnectInterface*/
{
    Q_OBJECT

public:
    explicit VQuickSend(QWidget *parent = nullptr);
    ~VQuickSend();

    void setChecked(bool bIsChecked);
    StQuickSend info();
signals:
    void sigSelected(VQuickSend *p);
    void sigSendClicked(StQuickSend stData);
private:
    virtual bool eventFilter(QObject *watched, QEvent *event);
private slots:
    void on_pushButton_clicked();

public:
    Ui::VQuickSend *ui;
};

#endif // VQUICKSEND_H
