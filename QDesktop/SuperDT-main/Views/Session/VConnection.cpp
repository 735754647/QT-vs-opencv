#include "VConnection.h"
#include "ui_VConnection.h"
#include "CHelper.h"
#include "CSettings.h"
#include "CUIHelper.h"
#include "CMainWindow.h"
#include "VToast.h"

VConnection::VConnection(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::VConnection)
{
    ui->setupUi(this);

    init();

    //绑定参数修改消息  实时设置连接参数
    connect(ui->comboBox_ip_or_serialname, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,&VConnection::slotArgReset);
    connect(ui->comboBox_port_or_baudrate, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,&VConnection::slotArgReset);
    connect(ui->comboBox_data_bit, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,&VConnection::slotArgReset);
    connect(ui->comboBox_parity, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,&VConnection::slotArgReset);
    connect(ui->comboBox_flowctrl, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,&VConnection::slotArgReset);
    connect(ui->comboBox_stop_bit, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,&VConnection::slotArgReset);

    connect(ui->comboBox_ip_or_serialname,&QComboBox::currentTextChanged,this,&VConnection::slotArgReset);
    connect(ui->comboBox_port_or_baudrate,&QComboBox::currentTextChanged,this,&VConnection::slotArgReset);
}

VConnection::~VConnection()
{
    delete ui;
}

void VConnection::protocolChanged(AbsConnection::EnmProtocolType enmType)
{
    m_strListBtnText.clear();

    switch (enmType) {
    case CConnectManager::ENM_TCP_CLIENT:
    {
        ui->widget_serial_settings->hide(); //隐藏串口设置
        ui->comboBox_ip_or_serialname->setToolTip(tr("服务器Ip"));
        ui->comboBox_port_or_baudrate->setToolTip(tr("服务器Port"));
        m_strListBtnText<<tr("连接")<<tr("连接中")<<tr("断开");
    }break;
    case CConnectManager::ENM_TCP_SERVER:
    {
        ui->widget_serial_settings->hide(); //隐藏串口设置
        ui->comboBox_ip_or_serialname->setToolTip(tr("绑定本地Ip"));
        ui->comboBox_port_or_baudrate->setToolTip(tr("绑定本地Port"));
        m_strListBtnText<<tr("监听")<<tr("监听中")<<tr("关闭");
    }break;
    case CConnectManager::ENM_UDP:
    {
        ui->widget_serial_settings->hide(); //隐藏串口设置

        ui->comboBox_ip_or_serialname->setToolTip(tr("绑定本地Ip"));
        ui->comboBox_port_or_baudrate->setToolTip(tr("绑定本地Port"));
        m_strListBtnText<<tr("监听")<<tr("监听中")<<tr("关闭");
    }break;
    case CConnectManager::ENM_SERIAL:
    {
        ui->widget_serial_settings->show();//显示串口设置
        ui->comboBox_ip_or_serialname->setToolTip(tr("串口名称"));
        ui->comboBox_port_or_baudrate->setToolTip(tr("波特率"));
        m_strListBtnText<<tr("打开")<<tr("打开中")<<tr("关闭");
    }break;
    default:
        qWarning()<<"不支持的协议:"<<enmType;
        break;
    }

    if(!m_strListBtnText.isEmpty())
        ui->pushButton_connect->setText(m_strListBtnText.first());

    refreshAvailableDev(); //刷新可用串口或IP地址
}

void VConnection::stateChanged(AbsConnection::EnmState enmState)
{
    static QStringList strListColor = {"#ff4d4d","#ffaa00","#47d147"}; //红、黄、绿
//    static QStringList strListState = {"noready","readyed","connected"};
    int nIndex = (int)enmState;
    if(strListColor.size() > nIndex && m_strListBtnText.size() > nIndex) {
        ui->label_state->setStyleSheet(QString("border-radius:5px;background:%1;").arg(strListColor[nIndex]));//状态点状态变化
        ui->pushButton_connect->setText(m_strListBtnText[nIndex]); //按钮文本变化
//        ui->pushButton_connect->setProperty("state",strListState[nIndex]);

        //断开连接时
        if(AbsConnection::ENM_NOT_READY == enmState){
            ui->pushButton_connect->setChecked(false); //连接按钮置回未连接状态
        }
    }
}

void VConnection::init()
{
    ui->widget_serial_settings->hide();


    refreshAvailableDev();
}
void VConnection::refreshAvailableDev()
{
    //刷新可用参数 Ip 或 串口名称
    static QStringList strListBaudRate = {"1200","2400","4800","9600","19200","38400","57600","115200"};

    ui->comboBox_ip_or_serialname->clear();
    ui->comboBox_port_or_baudrate->clear();

    AbsConnection::EnmProtocolType enmType = (AbsConnection::EnmProtocolType)ui->comboBox_protocal->currentIndex();


    if(m_pPortOrSerialNameModel == nullptr){
        m_pPortOrSerialNameModel = new QStandardItemModel();
    }
    //串口
    if (CConnectManager::ENM_SERIAL == enmType)
    {
        QList<QSerialPortInfo> listInfo = QSerialPortInfo::availablePorts();

        //串口信息
        foreach (QSerialPortInfo info, listInfo) {
            QStandardItem *pItem = new QStandardItem(info.portName());
            pItem->setToolTip(info.description());
            m_pPortOrSerialNameModel->appendRow(pItem);
//           qDebug()<<info.portName()<<info.description()<<info.serialNumber()<<info.systemLocation()<<info.manufacturer();
        }
//        ui->comboBox_ip_or_serialname->addItems(CHelper::serialportList()); //串口名称列表
        ui->comboBox_port_or_baudrate->addItems(strListBaudRate); //波特率列表
        ui->comboBox_port_or_baudrate->setCurrentIndex(3);        //默认9600 @MAJR 记忆上次设置的波特率 读出填上
        ui->comboBox_ip_or_serialname->setModel(m_pPortOrSerialNameModel);
    }
    //网络
    else
    {
        ui->comboBox_ip_or_serialname->addItems(CHelper::localIPv4List()); //IPV4 列表
        QString strDefaultPort = CSettings::getInstance()->settings()->value("Setting/DefaultPort").toString();
        ui->comboBox_port_or_baudrate->setCurrentText(strDefaultPort);
    }

    //串口名称和Ip 占宽度不同 所以自动调节一下 以下代码没啥卵用  @TODO仍需解决
//    qDebug()<<"重新调整大小";
//    ui->comboBox_ip_or_serialname->updateGeometry();
}

void VConnection::setConnectionProxy(CConnectManager *pConnectManager)
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
void VConnection::on_comboBox_protocal_currentIndexChanged(int index)
{
    m_pConnectManager->resetConnect((AbsConnection::EnmProtocolType)index);
}

void VConnection::on_pushButton_connect_clicked(bool checked)
{
    if (false == checked) {
       m_pConnectManager->stopConnection();
       return ;
    }


    QString strArg1 = ui->comboBox_ip_or_serialname->currentText();
    QString strArg2 = ui->comboBox_port_or_baudrate->currentText();

    if (AbsConnection::ENM_SERIAL == ui->comboBox_protocal->currentIndex()) {
        StSerialInfo stData;
        stData.strPortName = strArg1;
        stData.enmBaudRate = (QSerialPort::BaudRate)strArg2.toInt();
        stData.enmDataBits = (QSerialPort::DataBits)ui->comboBox_data_bit->currentText().toInt();
        stData.enmFlowControl = (QSerialPort::FlowControl)ui->comboBox_flowctrl->currentText().toInt();
        int nArr[5] = {QSerialPort::NoParity,QSerialPort::EvenParity,
                       QSerialPort::OddParity,QSerialPort::SpaceParity,QSerialPort::MarkParity};
        stData.enmParity = (QSerialPort::Parity)nArr[ui->comboBox_parity->currentIndex()];
        int nStopArr[] = {QSerialPort::OneStop,QSerialPort::OneAndHalfStop,QSerialPort::TwoStop};
        stData.enmStopBits = (QSerialPort::StopBits)nStopArr[ui->comboBox_stop_bit->currentIndex()];
        stData.bAutoSubpackage = true; //默认开启自动分包
        if(!m_pConnectManager->startConnection((void *)&stData)){
            //错误判断
            VToast::getInstance()->show(m_pConnectManager->errorString());
            ui->pushButton_connect->setChecked(false); //连接按钮置回未连接状态
        }
    } else {
        StSocketInfo stData(strArg1,strArg2.toInt());
        if(!m_pConnectManager->startConnection((void *)&stData)){
            //错误判断
            VToast::getInstance()->show(m_pConnectManager->errorString());
            ui->pushButton_connect->setChecked(false); //连接按钮置回未连接状态
        }
    }
}

void VConnection::slotArgReset()
{
    //已打开连接时 修改连接参数
    if(ui->pushButton_connect->isChecked())
    {
        ui->pushButton_connect->click(); //停止
        ui->pushButton_connect->click(); //开始
    }
}
