#include "CByte2Text.h"
#include "CSettings.h"

CByte2Text::CByte2Text(QByteArray byteArray, bool bHex, QObject *parent)
    : QObject{parent}
{
    m_bHex = bHex;
    slotTextCodeChanged(CSettings::getInstance()->textCode(),m_bHex);
    connect(CSettings::getInstance(),&CSettings::sigTextCodeChanged,this,[=](QString strTextCode){
        slotTextCodeChanged(strTextCode,m_bHex);
    });
    slotByteArrChanged(byteArray); //按编码初始化 m_strText
}

void CByte2Text::byteArr2Hex(const QByteArray &byteArray, QString &strSource)
{
    strSource = byteArray.toHex(' ');
}

void CByte2Text::byteArr2Utf8(const QByteArray &byteArray, QString &strSource)
{
    strSource = QString::fromUtf8(byteArray);
}

void CByte2Text::byteArr2Gbk(const QByteArray &byteArray, QString &strSource)
{
    strSource = QString::fromLocal8Bit(byteArray);
}

void CByte2Text::slotTextCodeChanged(QString strTextCode,bool bHex)
{
    if(bHex)
    {
        byteArr2Text = byteArr2Hex;
    }
    else
    {
        if("UTF-8" == strTextCode){
            byteArr2Text = byteArr2Utf8;
        }else if("GBK" == strTextCode){
            byteArr2Text = byteArr2Gbk;
        }else{
            byteArr2Text = byteArr2Utf8;
        }
    }
}

void CByte2Text::slotByteArrChanged(QByteArray &byteArray)
{
    byteArr2Text(byteArray,m_strText);
}

void CByte2Text::slotHexChanged(bool bHex)
{
    m_bHex = bHex;
    slotTextCodeChanged(CSettings::getInstance()->textCode(),m_bHex);
}
