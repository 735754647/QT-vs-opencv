#include "CSettings.h"

#include <QApplication>
#include <QDebug>
#include "CHelper.h"
#include <QFile>
#include "CUIHelper.h"
#include <QTextCodec>

CSettings::CSettings(QObject *parent) : QObject(parent)
{
}

CSettings *CSettings::getInstance()
{
    static CSettings *pInstance = nullptr;
    if(nullptr == pInstance) {
        pInstance = new CSettings();
    }
    return pInstance;
}

QByteArray CSettings::str2ByteArray(QString &strText)
{
    if("UTF-8" == m_pSettings->value("Setting/TextCode")) {
        return strText.toUtf8();
    }else if("GBK" == m_pSettings->value("Setting/TextCode")) {
        return strText.toLocal8Bit();
    }

    return strText.toLocal8Bit();
}

QString CSettings::byteArray2Str(QByteArray &byteArr)
{
    if("UTF-8" == m_pSettings->value("Setting/TextCode")) {
        return QString::fromUtf8(byteArr);
    }else if("GBK" == m_pSettings->value("Setting/TextCode")) {
        return QString::fromLocal8Bit(byteArr);
    }

    return QString();
}

void CSettings::init()
{
    m_pSettings = new QSettings("./Preference.ini",QSettings::IniFormat);
    m_pSettings->setIniCodec(QTextCodec::codecForName("UTF-8"));
    //文件不存在 就创建默认的ini
    if(!m_pSettings->contains("Setting/DefaultPort")) {
        m_pSettings->setValue("Setting/DefaultPort",9009);
        m_pSettings->setValue("Setting/TextCode","UTF-8");
        m_pSettings->setValue("Setting/MaxLine",10000);
        m_pSettings->setValue("Setting/LongPress",true);
        m_pSettings->setValue("Setting/Span",100);
        m_pSettings->setValue("Setting/Language","简体中文");
        m_pSettings->setValue("Setting/Skin","/Skin/userStyle.qss");
        m_pSettings->setValue("Setting/CurrSkin",0);
        m_pSettings->setValue("Setting/Font","Courier New,等线");
        m_pSettings->setValue("Setting/FontSize",12);
    }

    QString strLanguage = m_pSettings->value("Setting/Language").toString();

    if("简体中文" == strLanguage) {
        resetLanguage(ENM_LANGUAGE_ZN);
    } else if("English" == strLanguage) {
        resetLanguage(ENM_LANGUAGE_ENGLISH);
    }

    //检查初始皮肤
    QString strSkinFile = QApplication::applicationDirPath() + m_pSettings->value("Setting/Skin").toString();
    QFile file(strSkinFile);
    if(file.exists()){
        CUIHelper::installQss(strSkinFile);
    }else {
        //设置默认皮肤
        CUIHelper::installQss(":/Resource/Skin/defaultStyle.qss");
    }

    //初始化字体
    QFont font(m_pSettings->value("Setting/Font").toString());
    font.setPixelSize(m_pSettings->value("Setting/FontSize").toInt());
    qApp->setFont(font);
}

void CSettings::resetLanguage(CSettings::EnmLanguage enmLag)
{
    //弹窗提示
    QString strTsFile;
    switch (enmLag) {
    case CSettings::ENM_LANGUAGE_ZN:
        strTsFile = "";   //中文
        break;
    case CSettings::ENM_LANGUAGE_ENGLISH:
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

QString CSettings::textCode()
{
    return m_pSettings->value("Setting/TextCode","UTF-8").toString();
}

void CSettings::setTextCode(QString textCode)
{
    m_pSettings->setValue("Setting/TextCode",textCode);
    emit sigTextCodeChanged(textCode);
}
