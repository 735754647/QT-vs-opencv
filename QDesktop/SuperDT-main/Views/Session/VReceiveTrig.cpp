#include "VReceiveTrig.h"
#include "ui_VReceiveTrig.h"
#include "CConversion.h"
#include "CUIHelper.h"
#include <QDebug>
#include "CMainWindow.h"
#include "CSettings.h"
#include "CHelper.h"
#include "VToast.h"

VReceiveTrig::VReceiveTrig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VReceiveTrig)
{
    ui->setupUi(this);

    CHelper::recursiveInstallEventFilter(this);
//    qDebug()<<"VReceiveTrig children:"<<children();
}

VReceiveTrig::~VReceiveTrig()
{
    delete ui;
}

StReceiveTrig VReceiveTrig::info()
{
    StReceiveTrig stData(ui->textEdit_trig->toPlainText(),
                         ui->textEdit_send_msg->toPlainText(),
                         ui->checkBox->isChecked());
    return stData;
}

void VReceiveTrig::setChecked(bool bIsChecked)
{
    ui->radioButton->setChecked(bIsChecked);
}

bool VReceiveTrig::eventFilter(QObject *watched, QEvent *event)
{
    switch (event->type()) {
    case QEvent::MouseButtonPress:
    {
        emit sigSelected();
        //防止 radiubutton会取消选中
        if(qobject_cast<QRadioButton *>(watched)){
            event->accept();
            return true;
        }
    }break;
    case QEvent::FocusIn:
    {
        emit sigSelected();
    }break;
    default:
        break;
    }

    return QWidget::eventFilter(watched,event);
}

void VReceiveTrig::slotDataArrive(QString strIp, quint16 nPort, QByteArray byteArr)
{
    //@MAJR 只触发设置的地址  其他地址应忽略  或 任何地址发来的都可触发
    Q_UNUSED(strIp)
    Q_UNUSED(nPort)

    //检查是否触发
    QString strText = ui->textEdit_trig->toPlainText();
    QByteArray byteArrTrig;
    if(ui->checkBox->isChecked()){
        bool bIsOk;
        byteArrTrig = CConversion::hexStr2ByteArray(strText,&bIsOk);
        if (false == bIsOk) {
            VToast::getInstance()->show(tr("十六进制字符有误"));
            CUIHelper::widgetShake(ui->textEdit_trig,5); //抖动提示
            qWarning()<<"十六进制文本输入格式有误:"<<strText;
        }
    }else{
        byteArrTrig = CSettings::getInstance()->str2ByteArray(strText);
    }

    if(byteArrTrig == byteArr) {
        emit sigReceiveTrig(info());
    }
}
