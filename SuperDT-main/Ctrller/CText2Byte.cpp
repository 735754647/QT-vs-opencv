#include "CText2Byte.h"
#include "CSettings.h"

CText2Byte::CText2Byte(QString strText, bool bHex, QObject *parent)
    : QObject{parent}
{
    m_bHex = bHex;
    slotTextCodeChanged(CSettings::getInstance()->textCode(),m_bHex);
    connect(CSettings::getInstance(),&CSettings::sigTextCodeChanged,this,[=](QString strTextCode){
        slotTextCodeChanged(strTextCode,m_bHex);
    });
    slotTextChanged(strText); //按编码初始化 m_byteArr
}

void CText2Byte::text2Hex(const QString &strSource, QByteArray &byteArray)
{
    byteArray = QByteArray::fromHex(strSource.toUtf8());
}

void CText2Byte::text2Utf8(const QString &strSource, QByteArray &byteArray)
{
    byteArray = strSource.toUtf8();
}

void CText2Byte::text2Gbk(const QString &strSource, QByteArray &byteArray)
{
    byteArray = strSource.toLocal8Bit();
}


void CText2Byte::slotTextCodeChanged(QString strTextCode,bool bHex)
{
    if(bHex)
    {
        text2ByteArr = text2Hex;
    }
    else
    {
        if("UTF-8" == strTextCode){
            text2ByteArr = text2Utf8;
        }else if("GBK" == strTextCode){
            text2ByteArr = text2Gbk;
        }else{
            text2ByteArr = text2Utf8; //默认使用UTF-8
        }
    }
}

void CText2Byte::slotTextChanged(QString &strText)
{
    text2ByteArr(strText,m_byteArr);
}


void CText2Byte::slotHexChanged(bool bHex)
{
    m_bHex = bHex;
    slotTextCodeChanged(CSettings::getInstance()->textCode(),m_bHex);
}
