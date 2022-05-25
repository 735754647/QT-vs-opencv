#include "VSession.h"
#include "ui_VSession.h"
#include "AbsConnection.h"
#include <QSplitter>
#include "CMainWindow.h"

VSession::VSession(QWidget *parent) :
    VBaseSplitterForm(parent),
    ui(new Ui::VSession)
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor(0, 2); //设置窗口分割比例 接收占2
    ui->splitter->setStretchFactor(1, 1); //发送占1

    m_pConnectManager = new CConnectManager(this);

    ui->widget_vconnect->setConnectionProxy(m_pConnectManager);
    ui->widget_vreceive->setConnectionProxy(m_pConnectManager);
    ui->widget_vsend->setConnectionProxy(m_pConnectManager);

    m_pConnectManager->resetConnect(AbsConnection::ENM_TCP_CLIENT);

    setFormChecked(false); //默认边框

    //收发计数
    connect(m_pConnectManager,&CConnectManager::sigSendBytes,[=](int nBytes){
        if(m_bChecked)
            CMainWindow::getInstance()->slotSendBytes(nBytes);
    });
    connect(m_pConnectManager,&CConnectManager::sigRecvBytes,[=](int nBytes){
        if(m_bChecked)
            CMainWindow::getInstance()->slotRecvBytes(nBytes);
    });
    connect(CMainWindow::getInstance(),&CMainWindow::sigRecount,[=]{
        if(m_bChecked)
            m_pConnectManager->slotRecount();
    });
}

VSession::~VSession()
{
    delete ui;
}

void VSession::setFormChecked(bool bIsChecked)
{
    m_bChecked = bIsChecked;
    if(m_bChecked){
        ui->frame_session->setProperty("selected",true);
//        ui->frame_session->setStyleSheet("#frame_session{border:3px solid #1aa3ff;border-radius:5px;background:white;}");
//        ui->frame_title->setStyleSheet("#frame_title{border:2px solid #1aa3ff;border-bottom-left-radius:5px;border-bottom-right-radius:5px;border-top:none;}");

        //刷新状态栏的计数
        CMainWindow::getInstance()->slotRecvBytes(m_pConnectManager->recvBytes());
        CMainWindow::getInstance()->slotSendBytes(m_pConnectManager->sendBytes());
    } else {
        ui->frame_session->setProperty("selected",false);
//        ui->frame_session->setStyleSheet("#frame_session{border:3px solid gray;border-radius:5px;background:white;}");
//        ui->frame_title->setStyleSheet("#frame_title{border:2px solid gray;border-bottom-left-radius:5px;border-bottom-right-radius:5px;border-top:none;}");
    }

    ui->frame_session->setStyleSheet(ui->frame_session->styleSheet());
//    ui->frame_session->update(); //重设了样式表重绘界面
}
