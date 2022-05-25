#include "VToast.h"
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>

VToast::VToast(QWidget *parent) : QDialog(parent)
{
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_ShowWithoutActivating,true);
    setAttribute(Qt::WA_TranslucentBackground, true);

    m_pHintLabel = new QLabel(this);
    m_pHintLabel->setStyleSheet(QString("QLabel{background:white;color:black;font-family:'等线';"
                                        "font-size:%1px;border-radius:%2px;padding:%3px;margin:%4px;}")
                                .arg((16)).arg((5)).arg((10)).arg((10)));
    m_pHintLabel->setAlignment(Qt::AlignCenter);
    m_pHintLabel->adjustSize();

    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0,0);
    shadow_effect->setColor(QColor("#10000000"));
    shadow_effect->setBlurRadius((15));
    m_pHintLabel->setGraphicsEffect(shadow_effect);

    auto layout = new QHBoxLayout(this);//水平布局
    layout->addWidget(m_pHintLabel);
}

VToast *VToast::getInstance()
{
    static VToast* pInstance = nullptr;
    if(pInstance == nullptr){
        pInstance = new VToast();
    }
    return pInstance;
}

void VToast::show(QString strText)
{
    m_pHintLabel->setText(strText);
    QDialog::show();

    QPropertyAnimation *pAnimation = new QPropertyAnimation(this,"windowOpacity");
    pAnimation->setDuration(2000);
    pAnimation->setEasingCurve(QEasingCurve::InQuint); //InQuad  OutCubic InCirc
    pAnimation->setStartValue(1.0f);
    pAnimation->setEndValue(0.0f);
    pAnimation->start();
    QObject::connect(pAnimation,&QPropertyAnimation::finished,[=]{
        this->hide();
        delete pAnimation;
    });
}
