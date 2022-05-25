#include "CUIHelper.h"
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include <QSvgRenderer>

void CUIHelper::showUIBorder()
{
    int nBoderWidth = 1;

    QString strWidgetColor = "#0dff80"; //浅绿 #0dff80
    QString strFrameColor = "#0bdedd";  //青色 #0bdedd
    QString strLabelColor = "0080f5";   //蓝色 0080f5
    //深蓝 #0B12DE
    QString strButtonColor = "#9234FA";//紫色 #9234FA

    QStringList strListStyle;
    strListStyle.append(QString("QWidget{border:%1px solid %2;}")
                        .arg(nBoderWidth).arg(strWidgetColor));
    strListStyle.append(QString("QFrame{border:%1px solid %2;}")
                        .arg(nBoderWidth).arg(strFrameColor));
    strListStyle.append(QString("QLabel{border:%1px solid %2;}")
                        .arg(nBoderWidth).arg(strLabelColor));
    strListStyle.append(QString("QPushButton{border:%1px solid %2;}")
                        .arg(nBoderWidth).arg(strButtonColor));


    qApp->setStyleSheet(strListStyle.join(""));
}

void CUIHelper::widgetCenter(QWidget *pWidget, QWidget *parent)
{
    QSize parentSize = (nullptr == parent) ? QApplication::desktop()->screenGeometry().size() : parent->size(); //双屏情况下在主屏幕上提示
    QSize subSize = parentSize - pWidget->size();

    pWidget->move(subSize.width()/2,subSize.height()/2);
}

void CUIHelper::showHintLabel(QWidget *parent, QString strText, QString strFontSize, QString strColor, QString strBgColor, int nShowTime)
{
    if(nullptr == parent){
        parent = QApplication::desktop()->screen();
    }

    QFrame *pFrmBg = new QFrame(parent); //为了兼容parent为nullptr时的圆角边框  方法是背景透明 上边叠加圆角控件

    QLabel *pHintLabel = new QLabel(pFrmBg);
    pHintLabel->setStyleSheet(QString("QLabel{background:%1;color:%2;font:%3 SimHei;border-radius:5px;}")
                              .arg(strBgColor).arg(strColor).arg(strFontSize));
    pHintLabel->setText(strText);
    pHintLabel->setAlignment(Qt::AlignCenter);
    pHintLabel->adjustSize();
    pHintLabel->resize(pHintLabel->size() + QSize(60,30));

    pFrmBg->resize(pHintLabel->size());
    pFrmBg->setWindowFlags(Qt::FramelessWindowHint);
    pFrmBg->setAttribute(Qt::WA_TranslucentBackground);
    widgetCenter(pFrmBg,parent);
    pFrmBg->show();

    QPropertyAnimation *pAnimation = new QPropertyAnimation(pFrmBg,"windowOpacity");
    pAnimation->setDuration(nShowTime);
    pAnimation->setEasingCurve(QEasingCurve::InCirc);
    pAnimation->setStartValue(1.0f);
    pAnimation->setEndValue(0.0f);
    pAnimation->start();
    QObject::connect(pAnimation,&QPropertyAnimation::finished,[=]{
        delete pAnimation;
        delete pFrmBg;
    });
}

void CUIHelper::showHintInfo(QString strText, QWidget *parent)
{
    if(nullptr == parent){
        parent = QApplication::desktop()->screen();
    }

    QFrame *pFrmBg = new QFrame(parent); //为了兼容parent为nullptr时的圆角边框  方法是背景透明 上边叠加圆角控件

    QLabel *pHintLabel = new QLabel(pFrmBg);
    pHintLabel->setStyleSheet(QString("QLabel{background:white;color:black;font-family:SimHei;border-radius:5px;border:1px solid gray;}"));
    pHintLabel->setText(strText);
    pHintLabel->setAlignment(Qt::AlignCenter);
    pHintLabel->adjustSize();
    pHintLabel->resize(pHintLabel->size() + QSize(60,30));

    pFrmBg->resize(pHintLabel->size());
    pFrmBg->setWindowFlags(Qt::FramelessWindowHint);
    pFrmBg->setAttribute(Qt::WA_TranslucentBackground);
    widgetCenter(pFrmBg,parent);
    pFrmBg->show();

    QPropertyAnimation *pAnimation = new QPropertyAnimation(pFrmBg,"windowOpacity");
    pAnimation->setDuration(1500);
    pAnimation->setEasingCurve(QEasingCurve::InCirc);
    pAnimation->setStartValue(1.0f);
    pAnimation->setEndValue(0.0f);
    pAnimation->start();
    QObject::connect(pAnimation,&QPropertyAnimation::finished,[=]{
        delete pAnimation;
        delete pFrmBg;
    });
}

void CUIHelper::installQss(QString strFile)
{
    QFile fileQss(strFile);
    if(fileQss.open(QFile::ReadOnly)){
//        QString strQss = QString::fromLatin1(fileQss.readAll());
        qApp->setStyleSheet(fileQss.readAll());
//        qDebug()<<"installQss:"<<strQss;
        fileQss.close();
    }else{
        qWarning()<<strFile<<":qss文件打开失败!";
    }
}

void CUIHelper::widgetShake(QWidget *pWidget, int nRange)
{
    int nX = pWidget->x();
    int nY = pWidget->y();

    QPropertyAnimation *pAnimation = new QPropertyAnimation(pWidget,"geometry");
    pAnimation->setEasingCurve(QEasingCurve::InOutSine);
    pAnimation->setDuration(300);
    pAnimation->setStartValue(QRect(QPoint(nX,nY),pWidget->size()));

    int nShakeCount = 20; //抖动次数
    double nStep = 1.0/nShakeCount;
    for(int i = 1; i < nShakeCount; i++){
        nRange = i&1 ? -nRange : nRange;
        pAnimation->setKeyValueAt(nStep*i,QRect(QPoint(nX + nRange,nY),pWidget->size()));
    }

    pAnimation->setEndValue(QRect(QPoint(nX,nY),pWidget->size()));
    pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}
#include <QPainter>

QPixmap CUIHelper::pixmapSvg(QString strContent,QSize size)
{
    QSvgRenderer svgRender(strContent.toUtf8());

    QPixmap pixmap =  QPixmap(size);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    svgRender.render(&painter);

    return pixmap;
}
#include <QGraphicsDropShadowEffect>
void CUIHelper::menuResetStyle(QMenu *menu)
{
    if(nullptr == menu)
        return ;

    QList<QMenu *> listMenu;
    listMenu<<menu;

    //找出所有的子孙Menu
    CUIHelper::recursionSubMenu(menu,listMenu);  //添加所有的子菜单到list中

    //为所有的Menu 取消原装直角阴影 添加Qt的阴影
    foreach (QMenu *menu, listMenu) {
        menu->setWindowFlags(menu->windowFlags()  | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
        menu->setAttribute(Qt::WA_TranslucentBackground,true);
        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(menu);
        shadow->setOffset(0,0);
        shadow->setColor(QColor("#333333"));
        shadow->setBlurRadius(10);
        menu->setGraphicsEffect(shadow);
    }
}

void CUIHelper::recursionSubMenu(QMenu *menu,QList<QMenu *> &menus)
{
    foreach (QAction *action, menu->actions()) {
        if(nullptr != action->menu()){
            menus.append(action->menu());
            recursionSubMenu(action->menu(),menus);
        }
    }
    return ;
}
