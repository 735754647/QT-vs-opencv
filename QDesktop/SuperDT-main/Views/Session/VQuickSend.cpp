#include "VQuickSend.h"
#include "ui_VQuickSend.h"
#include "CHelper.h"
#include <QDebug>
#include "CSettings.h"

VQuickSend::VQuickSend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VQuickSend)
{
    ui->setupUi(this);

    CHelper::recursiveInstallEventFilter(this);


    //发送键长按支持 @MAJR 触发时间随设置动态调整
    int nSpan = CSettings::getInstance()->settings()->value("Setting/Span").toInt();
    ui->pushButton->setAutoRepeat(true);
    ui->pushButton->setAutoRepeatInterval(nSpan);
    ui->pushButton->setAutoRepeatDelay(200);
}

VQuickSend::~VQuickSend()
{
    delete ui;
}

void VQuickSend::setChecked(bool bIsChecked)
{
    ui->radioButton->setChecked(bIsChecked);
}

StQuickSend VQuickSend::info()
{
    StQuickSend stData(ui->textEdit->toPlainText(),
                       ui->checkBox->isChecked(),
                       ui->spinBox->value());

    return stData;
}

bool VQuickSend::eventFilter(QObject *watched, QEvent *event)
{
    switch (event->type()) {
    case QEvent::MouseButtonPress:
    {
        emit sigSelected(this);
        //防止 radiubutton会取消选中
        if(qobject_cast<QRadioButton *>(watched)){
            event->accept();
            return true;
        }
    }break;
    case QEvent::FocusIn:
    {
        emit sigSelected(this);
    }break;
    default:
        break;
    }

    return QWidget::eventFilter(watched,event);
}

void VQuickSend::on_pushButton_clicked()
{
    emit sigSendClicked(info());
}
