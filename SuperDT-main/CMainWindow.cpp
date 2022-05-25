#include "CMainWindow.h"
#include "ui_CMainWindow.h"
#include <QDebug>
#include "VSettings.h"
#include "VAbout.h"
#include <QSizePolicy>
#include "CUIHelper.h"
#include "VDialogProtocal.h"
#include "VDialogAscii.h"
#include "CSettings.h"
#include <QToolButton>
#include <QPushButton>
#include "VWindowSplitter.h"
#include <QGraphicsDropShadowEffect>
#ifdef Q_OS_WIN
#include <windows.h>
#endif
#include "CUIHelper.h"
#include "CIconFont.h"
#include "CQssTest.h"
#include <QWidgetAction>
#include "VDialogSkin.h"

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow)
{
    ui->setupUi(this);
    this->setIconSize(QSize(32,32));

    CUIHelper::menuResetStyle(ui->menu_settings);
    CUIHelper::menuResetStyle(ui->menu_help);

    //为Action 设置图标
    ui->action_preference->setIcon(CIconFont::getInstance()->pixmap(0xe6b2,QSize(16,16)));
    ui->action_skin->setIcon(CIconFont::getInstance()->pixmap(0xe622,QSize(16,16)));
    ui->action_about->setIcon(CIconFont::getInstance()->pixmap(0xe6a9,QSize(16,16)));
    ui->action_ascii->setIcon(CIconFont::getInstance()->pixmap(0xe6bb,QSize(16,16)));
    ui->action_wave->setIcon(CIconFont::getInstance()->pixmap(0xe694,QSize(16,16)));

    connect(ui->menu_help,&QMenu::triggered,[=](QAction *pAction){
        if("action_about" == pAction->objectName()){
            VAbout vabout;
            vabout.exec();
        }else if("action_wave" == pAction->objectName()){
            VDialogProtocal dialog;
            dialog.exec();
        }else if("action_ascii" == pAction->objectName()){
            VDialogAscii dialog;
            dialog.exec();
        }else if("action_skin" == pAction->objectName()){
            CQssTest *dialog = new CQssTest;
            dialog->setAttribute(Qt::WA_DeleteOnClose);
            dialog->show();
        }
    });

    connect(ui->menu_settings,&QMenu::triggered,[=](QAction *pAction){
        if("action_preference" == pAction->objectName()){
            VSettings vsettings;
            vsettings.exec();
        }else if("action_skin" == pAction->objectName()){
            VDialogSkin vdialog;
            vdialog.exec();
//            CQssTest *qssDialog = new CQssTest();
//            qssDialog->show();
        }
    });

    //初始化工具栏
    initToolBar();

    //初始化状态栏
    initStatusBar();
}

CMainWindow::~CMainWindow()
{
    delete ui;
}

CMainWindow *CMainWindow::getInstance()
{
    static CMainWindow *pInstance = nullptr;
    if(nullptr == pInstance) {
        pInstance = new CMainWindow();
    }
    return pInstance;
}

void CMainWindow::slotSendBytes(int nBytes)
{
    m_pSendLabel->setText(tr("发送:") + QString::number(nBytes) + tr("字节"));
}

void CMainWindow::slotRecvBytes(int nBytes)
{
    m_pRecvLabel->setText(tr("接收:") + QString::number(nBytes) + tr("字节"));
}

void CMainWindow::slotTextCode(QString strTextCode)
{
    m_pTextCodeLabel->setText(strTextCode);
}

void CMainWindow::initToolBar()
{
    //垂直
    QPushButton *pBtnV = new QPushButton(QChar(0xe679),this);
    pBtnV->setProperty("iconText",true);
    connect(pBtnV,&QPushButton::clicked,[=]{
        ui->vwindowsplitter->slotVSplitScreen();
    });

    //水平
    QPushButton *pBtnH = new QPushButton(QChar(0xe67a),this);
    pBtnH->setProperty("iconText",true);
    connect(pBtnH,&QPushButton::clicked,[=]{
        ui->vwindowsplitter->slotHSplitScreen();
    });

    //关闭
    QPushButton *pBtnClose = new QPushButton(QChar(0xe68e),this);
    pBtnClose->setProperty("iconText",true);
    connect(pBtnClose,&QPushButton::clicked,[=]{
        ui->vwindowsplitter->slotMergeScreen();
    });

    //置顶
    QPushButton *pBtnTop = new QPushButton(QChar(0xe6ac),this);
    pBtnTop->setProperty("iconText",true);
    pBtnTop->setCheckable(true); //@MAJR 记忆置顶状态
    connect(pBtnTop,&QPushButton::clicked,[=](bool bChecked){
        if(bChecked){
            this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint); //置顶
        }else{
            this->setWindowFlags(this->windowFlags() & ~Qt::WindowStaysOnTopHint); //取消置顶
        }
        this->show(); //应对置顶后窗口反而消失的问题
    });

    ui->toolBar->addWidget(pBtnV);
    ui->toolBar->addWidget(pBtnH);
    ui->toolBar->addWidget(pBtnClose);
    ui->toolBar->addWidget(pBtnTop);
}

void CMainWindow::initStatusBar()
{
    QStatusBar *pBar =  this->statusBar();
    if(nullptr == pBar)
        return ;

    m_pTextCodeLabel = new QLabel();

    m_pSendLabel = new QLabel(pBar);

    m_pRecvLabel = new QLabel(pBar);

    m_pBtnRecount = new QPushButton(pBar);
    m_pBtnRecount->setText(tr("重新计数"));
    connect(m_pBtnRecount,&QPushButton::clicked,[=]{
        emit sigRecount();
    });

    pBar->addPermanentWidget(m_pTextCodeLabel);
    pBar->addPermanentWidget(m_pSendLabel);
    pBar->addPermanentWidget(m_pRecvLabel);
    pBar->addPermanentWidget(m_pBtnRecount);

    slotSendBytes(0);
    slotRecvBytes(0);
    slotTextCode(CSettings::getInstance()->textCode());
}
