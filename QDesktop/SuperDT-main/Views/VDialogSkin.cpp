#include "VDialogSkin.h"
#include "ui_VDialogSkin.h"
#include <QGraphicsDropShadowEffect>
#include <QDebug>
#include <QWidget>
#include <QApplication>
#include <QDir>
#include "CSettings.h"

VDialogSkin::VDialogSkin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VDialogSkin)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);


    //设置具体阴影
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);
    shadow->setColor(QColor("#bbbbbb"));
    shadow->setBlurRadius(20);

    ui->frame->setGraphicsEffect(shadow);

    m_pFile = new QFile(":/Resource/Skin/simpleStyle.qss",this);
    if(m_pFile->open(QIODevice::ReadOnly)){
        m_strStyleSheet = QString(m_pFile->readAll());
    }
    QStringList strListColor;
    strListColor<<"#1aa3ff"<<"#70dbdb"<<"#aa80ff"<<"#ff80aa"<<"#ff944d"
                  <<"#ff9980"<<"#ffbb33"<<"#8cff66"<<"#ff4d4d"<<"#85e085";
    m_pBtnGp = new QButtonGroup(this);
    m_pBtnGp->setExclusive(true);
    connect(m_pBtnGp, QOverload<int>::of(&QButtonGroup::buttonClicked),
          [=](int id){

        if(id >= 0 && id < strListColor.count()){
             qDebug()<<id<<strListColor.at(id);

             QString strPrimaryColor = strListColor.at(id);
             QColor primaryColor(strListColor.at(id));
             int h,s,l;
             primaryColor.getHsl(&h,&s,&l);
             primaryColor.setHsl(h,s,255*0.9);
             QString strLightColor = primaryColor.name();
             primaryColor.setHsl(h,s,255*0.4);
             QString strDarkColor = primaryColor.name();

             QString strTemp = m_strStyleSheet;
             strTemp.replace("@lightPrimaryColor",strLightColor);
             strTemp.replace("@primaryColor",strPrimaryColor);
             strTemp.replace("@darkPrimaryColor",strDarkColor);
             strTemp.replace("@defaultBorderColor","#bbbbbb");
             strTemp.replace("@defaultFormBackgroundColor","#f2f2f2");
             strTemp.replace("@defaultFormPressedColor","#e6e6e6");

             qApp->setStyleSheet(strTemp);
        }
    });

    int i = 0;
    foreach(QObject *obj,ui->widget_buttons->children()){
        QPushButton *pBtn = qobject_cast<QPushButton *>(obj);
        if(pBtn){
            pBtn->setStyleSheet(QString("background:%1;").arg(strListColor.at(i)));
            m_pBtnGp->addButton(pBtn,i);
            i++;
        }
    }

    m_nCheckedId = CSettings::getInstance()->settings()->value("Setting/CurrSkin",0).toInt();
    QAbstractButton *pCheckBtn = m_pBtnGp->button(m_nCheckedId);
    if(pCheckBtn){
        pCheckBtn->setChecked(true);
    }
}

VDialogSkin::~VDialogSkin()
{
    delete ui;
}

void VDialogSkin::on_pushButton_clicked()
{
    //判断皮肤是否变化 变化才写入
    if(m_nCheckedId == m_pBtnGp->checkedId()){
        done(1);
        return ;
    }


    m_nCheckedId = m_pBtnGp->checkedId();
    CSettings::getInstance()->settings()->setValue("Setting/CurrSkin",m_nCheckedId);

    //保存样式 启动时加载
    QString strSKinPath = QApplication::applicationDirPath() + "/Skin/";
    QDir dir;
    if(!dir.exists(strSKinPath)){
        dir.mkpath(strSKinPath);
    }
    QFile file(strSKinPath + "userStyle.qss");
    if(file.open(QIODevice::ReadWrite | QIODevice::Truncate)){
        file.write(qApp->styleSheet().toUtf8());
        file.close();
    }else{
        qWarning()<<file.fileName()<<" :文件打开失败！无法保存用户设置的皮肤！";
    }

    done(1);
}
