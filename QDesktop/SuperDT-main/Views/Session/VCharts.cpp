#include "VCharts.h"
#include "ui_VCharts.h"
#include "VDialogProtocal.h"
#include "CUIHelper.h"

VCharts::VCharts(QWidget *parent) :
    QCustomPlot(parent),
    ui(new Ui::VCharts)
{
    ui->setupUi(this);

    ui->pushButton_start->setProperty("iconText",true);
    ui->pushButton_start->setText(QChar(0xe6a6));

    this->setStyleSheet("");

    init();
}

VCharts::~VCharts()
{
    delete ui;
}

void VCharts::init()
{
    //初始化线
    this->axisRect()->setBackground(QBrush(Qt::white));//背景色
    QColor colorLightBlue = QColor("#67c2ff");

    //网格设置
    this->xAxis->grid()->setZeroLinePen(QPen(Qt::black)); // x0线颜色
    this->xAxis->grid()->setPen(QPen(colorLightBlue, 1, Qt::PenStyle::SolidLine));
    this->yAxis->grid()->setZeroLinePen(QPen(Qt::black)); // y0线颜色
    this->yAxis->grid()->setPen(QPen(colorLightBlue, 1, Qt::PenStyle::SolidLine));

    //x轴设置
    this->xAxis->setSubTicks(false);       //关闭子刻度线显示
    this->xAxis->setTickLength(0);         //主刻度线长度为0
    this->xAxis->setBasePen(QPen(colorLightBlue));//轴颜色
    this->xAxis2->setVisible(true);        //显示x2轴
    this->xAxis2->setTickLabels(false);    //x2轴刻度不显示文本
    this->xAxis2->setSubTicks(false);
    this->xAxis2->setTicks(false);
    this->xAxis2->setBasePen(QPen(colorLightBlue));

    //y轴设置
    this->yAxis->setSubTicks(false);       //关闭子刻度线显示
    this->yAxis->setTickLength(0);         //主刻度线长度为0
    this->yAxis->setBasePen(QPen(colorLightBlue));//轴颜色
    this->yAxis2->setVisible(true);        //显示x2轴
    this->yAxis2->setTickLabels(false);    //x2轴刻度不显示文本
    this->yAxis2->setSubTicks(false);
    this->yAxis2->setTicks(false);
    this->yAxis2->setBasePen(QPen(colorLightBlue));

    connect(this->xAxis, SIGNAL(rangeChanged(QCPRange)), this->xAxis2, SLOT(setRange(QCPRange)));
    connect(this->yAxis, SIGNAL(rangeChanged(QCPRange)), this->yAxis2, SLOT(setRange(QCPRange)));
    this->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);


    //创建右键 菜单
    QAction *pActionAuto = new QAction(tr("自动缩放"));
    pActionAuto->setCheckable(true);
    pActionAuto->setChecked(m_bAutoScale);
    connect(pActionAuto,&QAction::triggered,[=](bool bChecked){
        m_bAutoScale = bChecked;
    });

    m_pActionStop = new QAction(tr("停止接收"));
    m_pActionStop->setToolTip(tr("停止接收数据"));
    m_pActionStop->setCheckable(true);
    m_pActionStop->setChecked(m_bAutoScale);
    connect(m_pActionStop,&QAction::triggered,[=](bool bChecked){
        ui->pushButton_start->setChecked(!bChecked);
    });

    QAction *pActionInfo = new QAction(tr("协议说明"));
    connect(pActionInfo,&QAction::triggered,[=]{
        VDialogProtocal dialog;
        dialog.exec();
    });

    QAction *pActionClear = new QAction(tr("清空"));
    pActionClear->setToolTip(tr("清空图表数据"));
    connect(pActionClear,&QAction::triggered,[=]{
        this->clearGraphs();
    });

    m_pMenu = new QMenu(this);
    m_pMenu->addAction(pActionAuto);
    m_pMenu->addAction(m_pActionStop);
    m_pMenu->addAction(pActionInfo);
    m_pMenu->addAction(pActionClear);
    CUIHelper::menuResetStyle(m_pMenu);
}

void VCharts::dataArrive(QString strIp, quint16 nPort, QByteArray byteTmp)
{
    Q_UNUSED(strIp)
    Q_UNUSED(nPort)

    if(m_pActionStop->isChecked())
        return ;

    //将数据添加到缓冲区
    m_bufCache.buffer().append(byteTmp);

    QByteArray byteArr;
    if(m_bufCache.open(QIODevice::ReadWrite)){
            if(m_bufCache.canReadLine()){
                byteArr = m_bufCache.readLine();
                m_bufCache.buffer().remove(0,byteArr.size());
                byteArr.remove(byteArr.size() - 1,1); //删除\n
//                qDebug()<<"读出行"<<byteArr;
            }else{
//                qDebug()<<"未读出行";
                return ;
            }
            m_bufCache.close();
    }


    //读出一行  解析画出来
    static QStringList strArrColor = {"#00dcc5","#2a8cfa","#633399","#ff3838","#e3dd35","#00dc58","#dc01c0","#00dcc5"};
    QList<QByteArray> listValue = byteArr.split(',');
    qDebug()<<listValue;
    if(this->graphCount() != listValue.count()){
        this->clearGraphs();
    }
    while(this->graphCount() != listValue.count()){
        QCPGraph *pCPGraph = this->addGraph(); //颜色随机
        pCPGraph->setPen(QPen(QColor(strArrColor[this->graphCount()%strArrColor.count()])));
        connect(this->xAxis, SIGNAL(rangeChanged(QCPRange)), this->xAxis2, SLOT(setRange(QCPRange)));
        connect(this->yAxis, SIGNAL(rangeChanged(QCPRange)), this->yAxis2, SLOT(setRange(QCPRange)));
    }
    for(int i = 0;  i < listValue.size(); i++){
        double dKey,dVal;
        dKey = this->graph(i)->dataCount() + 1;
        bool bOk;
        dVal = listValue[i].toDouble(&bOk);

        if(bOk){
            this->graph(i)->addData(dKey,dVal);
            this->graph(i)->rescaleAxes(m_bAutoScale); //是否 自动缩放纵横轴
            qDebug()<<"dkey:"<<dKey<<"dVal:"<<dVal;
            this->xAxis->setRange(dKey, 100, Qt::AlignRight);
        }
    }

    //刷新曲线
    this->replot();
}

void VCharts::contextMenuEvent(QContextMenuEvent *event)
{
     m_pMenu->exec(event->globalPos());
}

void VCharts::on_pushButton_start_toggled(bool checked)
{
    m_pActionStop->setChecked(!checked);
    if(checked){
        ui->pushButton_start->hide();
    }else{
        ui->pushButton_start->show();
    }
}
