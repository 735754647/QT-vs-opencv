#include "CConfig.h"
#include "CTableConfig.h"

#include <QApplication>
#include <QDebug>
#include "CHelper.h"
#include <QFile>
#include "CUIHelper.h"
#include <QStandardPaths>

CConfig::CConfig(QObject *parent) : QObject(parent)
{

}

CConfig *CConfig::getInstance()
{
    static CConfig *pInstance = nullptr;
    if(nullptr == pInstance) {
        pInstance = new CConfig();
    }
    return pInstance;
}

void CConfig::init()
{
    QString strLanguage = CTableConfig::instance()->queryValue(CTableConfig::Language);
    if("简体中文" == strLanguage) {
        resetLanguage(ENM_LANGUAGE_ZN);
    } else if("English" == strLanguage) {
        resetLanguage(ENM_LANGUAGE_ENGLISH);
    }
    //检查初始皮肤
       QString strSkinFile = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) + CTableConfig::instance()->queryValue(CTableConfig::Skin);
       QFile file(strSkinFile);
       if(file.exists()){
           CUIHelper::installQss(strSkinFile);
       }else {
           //设置默认皮肤
           CUIHelper::installQss(":/Resource/Skin/defaultStyle.qss");
       }
       //设置字体
       QStringList strListFont = CTableConfig::instance()->queryValue(CTableConfig::Font).split(',');
       if(!strListFont.isEmpty()){
           //多个字体 首先会在第一个字体中寻找 依次往后
           QFont font = QApplication::font();
           font.setFamily(QString("%1,%2").arg(strListFont.first())
                          .arg(strListFont.last()));
           font.setPixelSize(CTableConfig::instance()->queryValue(CTableConfig::FontSize).toInt());
           QApplication::setFont(font,"QObject");
           qInfo()<<"初始化应用字体:"<<font.family()<<font.pixelSize();
       }
   }



void CConfig::resetLanguage(CConfig::EnmLanguage enmLag)
{
    //弹窗提示
    QString strTsFile;
    switch (enmLag) {
    case CConfig::ENM_LANGUAGE_ZN:
        strTsFile = "";   //中文
        break;
    case CConfig::ENM_LANGUAGE_ENGLISH:
        strTsFile = ":/Trans/english.qm";
        break;
    default:
        break;
    }
    if(nullptr != m_pTranslator) {
        qApp->removeTranslator(m_pTranslator);
        delete m_pTranslator;
        m_pTranslator = nullptr;
    }
    m_pTranslator = new QTranslator(this);
    m_pTranslator->load(strTsFile);
    qApp->installTranslator(m_pTranslator);
}
//QString CConfig::textCode()
//{
//    return m_pSettings->value("Setting/TextCode","UTF-8").toString();
//}
