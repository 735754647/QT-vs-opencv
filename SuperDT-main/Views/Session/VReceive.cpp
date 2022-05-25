#include "VReceive.h"
#include "ui_VReceive.h"
#include "CSettings.h"
#include "CConversion.h"
#include <QTextCharFormat>
#include "qcustomplot.h"
#include "VDialogProtocal.h"
#include <QTime>
#include "CIconFont.h"

VReceive::VReceive(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VReceive)
{
    ui->setupUi(this);
    ui->pushButton_hex->setProperty("iconText",true);
    ui->pushButton_hex->setText(QChar(0xe604));

    ui->pushButton_timestamp->setProperty("iconText",true);
    ui->pushButton_timestamp->setText(QChar(0xe6b5));

    ui->pushButton_display_send->setProperty("iconText",true);
    ui->pushButton_display_send->setText(QChar(0xe6a8));

    ui->pushButton_stop->setProperty("iconText",true);
    ui->pushButton_stop->setText(QChar(0xe6a6));

    ui->pushButton_clear->setProperty("iconText",true);
    ui->pushButton_clear->setText(QChar(0xe7d4));

    this->setStyleSheet(""); //@NOTE 可以解决初始化按钮不显示图标的问题
}

VReceive::~VReceive()
{
    delete ui;
}

void VReceive::setConnectionProxy(CConnectManager *pConnectManager)
{
    m_pConnectManager = pConnectManager;
    connect(m_pConnectManager,&AbsConnection::sigStateChanged,[=](AbsConnection::EnmState enmState){
        this->stateChanged(enmState);
    });
    connect(m_pConnectManager,&AbsConnection::sigConnectChanged,[=](QString strIp,quint16 nPort,bool bState){
        this->connectStateChanged(strIp,nPort,bState);
    });
    connect(m_pConnectManager,&AbsConnection::sigDataArrive,[=](QString strIp,quint16 nPort,QByteArray byteArr){
        this->dataArrive(strIp,nPort,byteArr);
        if(ui->chart->isEnabled())
            ui->chart->dataArrive(strIp,nPort,byteArr); // 绘图
    });
    connect(m_pConnectManager,&CConnectManager::sigProtocolChanged,[=](AbsConnection::EnmProtocolType enmType){
        this->protocolChanged(enmType);
    });
    connect(m_pConnectManager,&CConnectManager::sigSend,[=](QByteArray byteArr){
        this->send(byteArr);
    });
}

void VReceive::dataArrive(QString strIp, quint16 nPort, QByteArray byteArr)
{
    Q_UNUSED(strIp)
    Q_UNUSED(nPort)

    if(ui->pushButton_stop->isChecked()) //停止显示
        return ;

    //转换文本
    QString strText;
    if(ui->pushButton_hex->isChecked()){
        strText = CConversion::byteArray2HexStr(byteArr); //@TODO 进制非法应有提示 比如包含:R
    }else{
        strText = CSettings::getInstance()->byteArray2Str(byteArr);
    }
    //时间戳
    if(ui->pushButton_timestamp->isChecked())
        strText = timestamp() + strText;

    //设置文本样式 追加 显示
    QTextCharFormat textFmt;
    textFmt.setFontItalic(false);
    textFmt.setForeground(QColor("black"));

    ui->textEdit_receive->mergeCurrentCharFormat(textFmt);
    ui->textEdit_receive->append(strText);
    ui->textEdit_receive->setAlignment(Qt::AlignLeft);
    ui->textEdit_receive->moveCursor(QTextCursor::End);
}

void VReceive::send(QByteArray byteArr)
{
    if(false == ui->pushButton_display_send->isChecked())
        return ;

    //转换文本
    QString strText;
    if(ui->pushButton_hex->isChecked()){
        strText = CConversion::byteArray2HexStr(byteArr); //@TODO 进制非法应有提示 比如包含字母:R
    }else{
        strText = CSettings::getInstance()->byteArray2Str(byteArr);
    }

    //时间戳
    if(ui->pushButton_timestamp->isChecked())
        strText = timestamp() + strText;

    //设置文本样式  绿色 显示
    QTextCharFormat textFmt;
    textFmt.setFontItalic(true);
    textFmt.setForeground(QColor("#47d147"));
    ui->textEdit_receive->mergeCurrentCharFormat(textFmt);
    ui->textEdit_receive->append(strText);
    ui->textEdit_receive->setAlignment(Qt::AlignRight);

    ui->textEdit_receive->moveCursor(QTextCursor::End);
}

QString VReceive::timestamp()
{
   return "[" + QTime::currentTime().toString() + "]  ";
}

void VReceive::on_pushButton_clear_clicked()
{
    ui->textEdit_receive->clear();
}
