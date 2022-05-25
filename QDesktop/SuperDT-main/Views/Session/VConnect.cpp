#include "VConnect.h"
#include "ui_VConnect.h"
#include "CHelper.h"

VConnect::VConnect(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::VConnect)
{
    ui->setupUi(this);

    init();
}

VConnect::~VConnect()
{
    delete ui;
}

void VConnect::protocolChanged(AbsConnection::EnmProtocolType enmType)
{
    m_strListBtnText.clear();

    switch (enmType) {
    case CConnectManager::ENM_TCP_CLIENT:
    {
        ui->widget_serial_settings->hide(); //隐藏串口设置
        ui->comboBox_ip_or_baudrate->setToolTip("服务器Ip");
        ui->comboBox_port_or_serialname->setToolTip("服务器Port");
        m_strListBtnText<<"连接"<<"连接中"<<"断开";
    }break;
    case CConnectManager::ENM_TCP_SERVER:
    {
        ui->widget_serial_settings->hide(); //隐藏串口设置
        ui->comboBox_ip_or_baudrate->setToolTip("绑定本地Ip");
        ui->comboBox_port_or_serialname->setToolTip("绑定本地Port");
        m_strListBtnText<<"监听"<<"监听中"<<"关闭";
    }break;
    case CConnectManager::ENM_UDP:
    {
        ui->widget_serial_settings->hide(); //隐藏串口设置
        ui->comboBox_ip_or_baudrate->setToolTip("绑定本地Ip");
        ui->comboBox_port_or_serialname->setToolTip("绑定本地Port");
        m_strListBtnText<<"监听"<<"监听中"<<"关闭";
    }break;
    case CConnectManager::ENM_SERIAL:
    {
        ui->widget_serial_settings->show();//显示串口设置
        ui->comboBox_ip_or_baudrate->setToolTip("串口名称");
        ui->comboBox_port_or_serialname->setToolTip("波特率");
        m_strListBtnText<<"打开"<<"打开中"<<"关闭";
    }break;
    default:
        qWarning()<<"不支持的协议:"<<enmType;
        break;
    }

    if(!m_strListBtnText.isEmpty())
        ui->pushButton_connect->setText(m_strListBtnText.first());

    refreshAvailableDev(); //刷新可用串口或IP地址
}

void VConnect::stateChanged(AbsConnection::EnmState enmState)
{
    static QStringList strListColor = {"ff4d4d","ffaa00","47d147"}; //红、黄、绿

    int nIndex = (int)enmState;

    if(strListColor.size() > nIndex && m_strListBtnText.size() > nIndex) {
        ui->label_state->setStyleSheet(QString("border-radius:5px;background:%1;").arg(strListColor[nIndex]));//状态点状态变化
        ui->pushButton_connect->setText(m_strListBtnText[nIndex]); //按钮文本变化
    }
}

void VConnect::connectStateChanged(QString strIp, quint16 nPort, bool bState)
{
    Q_UNUSED(strIp)
    Q_UNUSED(nPort)
    Q_UNUSED(bState)
}

void VConnect::dataArrive(QString strIp, quint16 nPort, QByteArray byteArr)
{
    Q_UNUSED(strIp)
    Q_UNUSED(nPort)
    Q_UNUSED(byteArr)
}

void VConnect::init()
{
    ui->widget_serial_settings->hide(); //默认隐藏串口
}

void VConnect::refreshAvailableDev()
{
    static QStringList strListBaudRate = {"1200","2400","4800","9600","19200","38400","57600","115200"};

    ui->comboBox_ip_or_baudrate->clear();
    ui->comboBox_port_or_serialname->clear();

    AbsConnection::EnmProtocolType enmType = (AbsConnection::EnmProtocolType)ui->comboBox_protocal->currentIndex();
    if (CConnectManager::ENM_SERIAL == enmType) {
        ui->comboBox_ip_or_baudrate->addItems(CHelper::serialportList()); //串口名称列表
        ui->comboBox_port_or_serialname->addItems(strListBaudRate); //波特率列表
    } else {
        ui->comboBox_ip_or_baudrate->addItems(CHelper::localIPv4List()); //IPV4 列表
        ui->comboBox_port_or_serialname->addItem("9009"); //@TODO 获取默认的端口

    }
}


void VConnect::on_comboBox_protocal_currentIndexChanged(int index)
{
//    m_pConnectManager->resetConnect((AbsConnection::EnmProtocolType)index);
}
