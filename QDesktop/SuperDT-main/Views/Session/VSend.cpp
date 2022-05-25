#include "VSend.h"
#include "ui_VSend.h"
#include "CHelper.h"
#include "CConversion.h"
#include "CUIHelper.h"
#include "CMainWindow.h"
#include "CSettings.h"
#include "ui_VQuickSend.h"
#include "ui_VReceiveTrig.h"
#include "CIconFont.h"
#include "VToast.h"

VSend::VSend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VSend)
{
    ui->setupUi(this);

    ui->pushButton_hex->setProperty("iconText",true);
    ui->pushButton_hex->setText(QChar(0xe604));

    ui->pushButton_clear->setProperty("iconText",true);
    ui->pushButton_clear->setText(QChar(0xe7d4));

    this->setStyleSheet("");//@NOTE 解决按钮图标不显示问题

    //隐藏IP port输入
    ui->widget_address->hide();

    //发送键长按支持 @MAJR 触发时间随设置动态调整
    int nSpan = CSettings::getInstance()->settings()->value("Setting/Span").toInt();
    ui->pushButton_send->setAutoRepeat(true);
    ui->pushButton_send->setAutoRepeatInterval(nSpan);
    ui->pushButton_send->setAutoRepeatDelay(200);

    //初始化自动发送
    ui->spinBox_auto_span->hide();
    m_pTimerAutoSend = new QTimer(this);
    connect(m_pTimerAutoSend,&QTimer::timeout,[=]{
        on_pushButton_send_clicked();
    });

    //初始化快捷发送和 触发器
    for(int i = 0; i < 3; i++) {
        on_pushButton_quick_add_clicked();
        on_pushButton_trig_add_clicked();
    }

    connect(ui->comboBox_connections, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
        [=](int nIndex){
        EnmType enmItemData = (EnmType)ui->comboBox_connections->itemData(nIndex).toInt();

        switch(enmItemData){
        case EnmType::ENM_ALL_CONNECT:
            ui->widget_address->hide();
            break;
        case EnmType::ENM_CUSTOM_CONNECT:
            ui->widget_address->show();
            break;
        case EnmType::ENM_IP_PORT:
            ui->widget_address->hide();
            break;
        default:
            break;
        }
    });
}

VSend::~VSend()
{
    delete ui;
}

void VSend::setConnectionProxy(CConnectManager *pConnectManager)
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
    });
    connect(m_pConnectManager,&CConnectManager::sigProtocolChanged,[=](AbsConnection::EnmProtocolType enmType){
        this->protocolChanged(enmType);
    });
}

void VSend::protocolChanged(AbsConnection::EnmProtocolType enmType)
{
    //清除之前的连接 更改了协议已经失效
    ui->comboBox_connections->clear();

    switch(enmType){
    case AbsConnection::ENM_TCP_CLIENT:
    case AbsConnection::ENM_SERIAL:
    {
        ui->comboBox_connections->hide();
        ui->widget_address->hide();
    }break;
    case AbsConnection::ENM_TCP_SERVER:
    {
        ui->comboBox_connections->show();
        ui->widget_address->hide();

        ui->comboBox_connections->addItem(tr("所有连接"),EnmType::ENM_ALL_CONNECT);
    }break;
    case AbsConnection::ENM_UDP:
    {
        ui->comboBox_connections->show();
        ui->widget_address->show();

        ui->comboBox_connections->addItem(tr("手动设置"),EnmType::ENM_CUSTOM_CONNECT);
        ui->comboBox_ip->clear();
        ui->comboBox_ip->addItems(CHelper::localIPv4List());
    }break;
    default:
        break;
    }
}

void VSend::connectStateChanged(QString strIp, quint16 nPort, bool bState)
{
    QString strKey = strIp + ":" +QString::number(nPort);

    int nIndex = ui->comboBox_connections->findText(strKey);
    if(bState) {
        if(-1 == nIndex) //连接成功 不存在就加上
            ui->comboBox_connections->addItem(strKey,EnmType::ENM_IP_PORT);
    } else {
        if(-1 != nIndex) //断开连接 存在就删掉
            ui->comboBox_connections->removeItem(nIndex);
    }
}

void VSend::dataArrive(QString strIp, quint16 nPort, QByteArray byteArr)
{
    foreach(VReceiveTrig *pReceiveTrig,m_vecReceiveTrig) {
        pReceiveTrig->slotDataArrive(strIp,nPort,byteArr);
    }
}

void VSend::processSendText(QString &strText, bool &bHex)
{
    //字符串转二进制
    QByteArray byteArr;
    if(bHex){
        bool bIsOk;
        byteArr = CConversion::hexStr2ByteArray(strText,&bIsOk);
        if (false == bIsOk) {
            VToast::getInstance()->show(tr("十六进制字符有误"));
            CUIHelper::widgetShake(ui->textEdit_send,5); //抖动提示
            qWarning()<<"十六进制文本输入格式有误:"<<strText;
        }
    }else{
        byteArr = CSettings::getInstance()->str2ByteArray(strText);  //根据设置的字符编码 进行String转换byteArr
    }

    //确定发送对象 并发送
    int nIndex = ui->comboBox_connections->currentIndex(); //获取当前索引

    EnmType enmItemData = (EnmType)ui->comboBox_connections->itemData(nIndex).toInt();

    switch(enmItemData){
    case EnmType::ENM_ALL_CONNECT:
    {
        m_pConnectManager->sendAll(byteArr);
    }
        break;
    case EnmType::ENM_CUSTOM_CONNECT:
    {
        QString strIp = ui->comboBox_ip->currentText();
        int nPort = ui->lineEdit_port->text().toInt();
        m_pConnectManager->send(strIp,nPort,byteArr);
    }
        break;
        //如 127.0.0.1:8009
    case EnmType::ENM_IP_PORT:
    {
        QString strKey = ui->comboBox_connections->currentText();
        QStringList strListTemp = strKey.split(":");
        if(2 == strListTemp.size()){
            m_pConnectManager->send(strListTemp.first(),strListTemp.last().toInt(),byteArr);
        }
    }
        break;
    default:
        qWarning()<<"类型错误!!!";
        break;
    }
}

void VSend::on_pushButton_send_clicked()
{
    QString strText = ui->textEdit_send->toPlainText();

    bool bIsHex = ui->pushButton_hex->isChecked();
    this->processSendText(strText,bIsHex);
}

void VSend::on_checkBox_auto_send_clicked(bool checked)
{
    ui->pushButton_send->setEnabled(!checked);
    if(checked){
        ui->spinBox_auto_span->show();
        m_pTimerAutoSend->start(ui->spinBox_auto_span->value());
    }else{
        ui->spinBox_auto_span->hide();
        m_pTimerAutoSend->stop();
    }
}

void VSend::on_spinBox_auto_span_valueChanged(int arg1)
{
    if(ui->checkBox_auto_send->isChecked()) {
        m_pTimerAutoSend->start(arg1);
    }
}

void VSend::on_tabWidget_send_currentChanged(int index)
{
    if(index < ui->stackedWidget->count()){
        ui->stackedWidget->setCurrentIndex(index);
    }
}

void VSend::selectQuickSend(VQuickSend *pQuickSend)
{
   //设置选中的快捷信息
    pQuickSend->setChecked(true);
    if(nullptr != m_pSelectedQuickSend && (m_pSelectedQuickSend != pQuickSend)) {
        m_pSelectedQuickSend->setChecked(false);
    }

    m_pSelectedQuickSend = pQuickSend;
}

void VSend::selectReceiveTrig(VReceiveTrig *pReceiveTrig)
{
    pReceiveTrig->setChecked(true);
    if(nullptr != m_pSelectedReceiveTrig && (m_pSelectedReceiveTrig != pReceiveTrig)) {
        m_pSelectedReceiveTrig->setChecked(false);
    }

    m_pSelectedReceiveTrig = pReceiveTrig;
}

void VSend::on_pushButton_quick_add_clicked()
{
    //添加一个快捷发送
    VQuickSend *pQuickSend = new VQuickSend(this);

    //选中时
    connect(pQuickSend,&VQuickSend::sigSelected,[=](VQuickSend *p){ //@TODO 可删掉此参数
        selectQuickSend(p);
    });
    //点击发送按钮
    connect(pQuickSend,&VQuickSend::sigSendClicked,[=](StQuickSend stData){
        processSendText(stData.strText,stData.bHex);
    });

    m_vecQuickSend.append(pQuickSend);
    QVBoxLayout *pLayout = qobject_cast<QVBoxLayout *>(ui->scrollAreaWidgetContents->layout());
    if(nullptr != pLayout) {
        pLayout->insertWidget(pLayout->count()-1,pQuickSend);
    }

}

void VSend::on_pushButton_quick_del_clicked()
{
    //删除一个快捷发送
    if(nullptr != m_pSelectedQuickSend){
        int nRemoveIndex = m_vecQuickSend.indexOf(m_pSelectedQuickSend);
        m_vecQuickSend.removeAt(nRemoveIndex);
        m_pSelectedQuickSend->deleteLater();
        m_pSelectedQuickSend = nullptr;

        //删除选中的  再默认选中一个
        if(!m_vecQuickSend.isEmpty()){
            if(nRemoveIndex < m_vecQuickSend.count()){
                selectQuickSend(m_vecQuickSend[nRemoveIndex]);
            }else{
                selectQuickSend(m_vecQuickSend.first());
            }
        }
    }
}

void VSend::on_checkBox_quick_hex_clicked(bool checked)
{
    foreach (VQuickSend *pQuickSend,m_vecQuickSend) {
        pQuickSend->ui->checkBox->setChecked(checked); //需包含 ui_xxx头文件才可用
    }
}

void VSend::on_spinBox_quick_span_valueChanged(int arg1)
{
    foreach (VQuickSend *pQuickSend,m_vecQuickSend) {
        pQuickSend->ui->spinBox->setValue(arg1);
    }
}

void VSend::on_pushButton_loop_start_clicked(bool checked)
{

    //@BUG !!!未连接点击开始循环会崩溃
    //循环快捷发送

    //判空
    if(m_vecQuickSend.isEmpty()){
        VToast::getInstance()->show(tr("没有数据可循环发送!"));
        return ;
    }

    //修改循环按钮文本
    ui->pushButton_loop_start->setText(checked ? "停止循环" : "开始循环");

    //定时器 懒创建
    if(nullptr == m_pTimerLoopQuickSend) {
        m_pTimerLoopQuickSend = new QTimer(this);
        connect(m_pTimerLoopQuickSend,&QTimer::timeout,[=]{

            //发送选中的信息
            StQuickSend stInfo = m_vecQuickSend[m_nCurrentSendIndex]->info();
            processSendText(stInfo.strText,stInfo.bHex);

            //调整时间间隔
            if(m_pTimerLoopQuickSend->interval() != stInfo.nSpan) {
                m_pTimerLoopQuickSend->start(stInfo.nSpan);
            }

            //定位到下个非空快捷发送 @BUG info() 返回空
            do{
                ++m_nCurrentSendIndex;
                m_nCurrentSendIndex = m_nCurrentSendIndex % m_vecQuickSend.count();
            }while(m_vecQuickSend[m_nCurrentSendIndex]->info().strText.isEmpty());


            //调整选中状态
            selectQuickSend(m_vecQuickSend[m_nCurrentSendIndex]);
        });
    }

    //启动或关闭定时器
    if (checked) {
        // !!! 防止删除信息 导致索引越界
        if(m_nCurrentSendIndex < 0 || (m_nCurrentSendIndex >= m_vecQuickSend.count())){
            m_nCurrentSendIndex = 0;
        }

        int nSpan = m_vecQuickSend[m_nCurrentSendIndex]->info().nSpan;
        m_pTimerLoopQuickSend->start(nSpan);
    } else {
        m_pTimerLoopQuickSend->stop();
    }

    //禁用或启用  添加、删除
    ui->pushButton_quick_add->setEnabled(!checked);
    ui->pushButton_quick_del->setEnabled(!checked);
}

/*****************************触发器部分************************************/

void VSend::on_pushButton_trig_add_clicked()
{
    VReceiveTrig *pReceiveTrig = new VReceiveTrig(this);

    //选中时
    connect(pReceiveTrig,&VReceiveTrig::sigSelected,[=]{
        selectReceiveTrig(pReceiveTrig);
    });
    //触发时
    connect(pReceiveTrig,&VReceiveTrig::sigReceiveTrig,[=](StReceiveTrig stData){
        qDebug()<<"VSend::on_pushButton_trig_add_clicked()"<<"触发";
        if(ui->pushButton_trig_start->isChecked()) { //触发器启用时
            qDebug()<<"VSend::on_pushButton_trig_add_clicked()"<<"触发"<<stData.strSText<<stData.bHex;
            processSendText(stData.strSText,stData.bHex); //发送出去
        }
    });
    //绑定消息接收
//    connect(m_pConnectManager,&CConnectManager::sigDataArrive,pReceiveTrig,&VReceiveTrig::slotDataArrive);

    QVBoxLayout *pLayout = qobject_cast<QVBoxLayout *>(ui->scrollAreaWidgetContents_trig->layout());
    if(nullptr != pLayout) {
        pLayout->insertWidget(pLayout->count()-1,pReceiveTrig);
    }

    m_vecReceiveTrig.append(pReceiveTrig);
}

void VSend::on_pushButton_trig_del_clicked()
{
    if(nullptr != m_pSelectedReceiveTrig){
        int nRemoveIndex = m_vecReceiveTrig.indexOf(m_pSelectedReceiveTrig);
        m_vecReceiveTrig.removeAt(nRemoveIndex);
        m_pSelectedReceiveTrig->deleteLater();
        m_pSelectedReceiveTrig = nullptr;
        //删除选中的  再默认选中一个
        if(!m_vecReceiveTrig.isEmpty()){
            if(nRemoveIndex < m_vecReceiveTrig.count()){
                selectReceiveTrig(m_vecReceiveTrig[nRemoveIndex]);
            }else{
                selectReceiveTrig(m_vecReceiveTrig.first());
            }
        }
    }
}

void VSend::on_checkBox_trig_hex_clicked(bool checked)
{
    foreach(VReceiveTrig *pReceiveTrig,m_vecReceiveTrig) {
        pReceiveTrig->ui->checkBox->setChecked(checked); //需包含 ui_xxx头文件才可用
    }
}

void VSend::on_pushButton_trig_start_clicked(bool checked)
{
    //修改循环按钮文本
    ui->pushButton_trig_start->setText(checked ? tr("禁用触发器") : tr("启用触发器"));
}

void VSend::on_pushButton_clear_clicked()
{
    ui->textEdit_send->clear();
}
