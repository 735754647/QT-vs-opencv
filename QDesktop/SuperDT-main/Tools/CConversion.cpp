#include "CConversion.h"
#include <QDebug>
#include <stdbool.h>
#include <stdlib.h>

QByteArray CConversion::hexStr2ByteArray(QString str, bool *bIsOk)
{
    qDebug()<<"str hex:"<<str;
    QByteArray byteArr;
    str = str.replace(" ",""); //去空格
//    if (0 != (str.size() % 2)) {
//        str.insert(str.size() - 1,'0'); //不是2的倍数 给最后一个补0 例如: a0 8 ,凑成 a0 08
//    }

//    for (int nIndex = 0; nIndex < str.size(); nIndex += 2) {
//        char ch = QString(str[nIndex]).toInt(bIsOk,16) * 16 + QString(str[nIndex + 1]).toInt(bIsOk,16);
//        byteArr.append(ch);
//    }

    qDebug()<<"str hex:"<<str<<str.toUtf8();
    *bIsOk = true;
    byteArr = QByteArray::fromHex(str.toUtf8());
    qDebug()<<"byte hex:"<<byteArr;
    return byteArr;
}

QString CConversion::byteArray2HexStr(QByteArray byteArr)
{
    QString str = byteArr.toHex().toUpper();

    for (int nIndex = 3; nIndex < str.size();nIndex += 3) {
        str = str.insert(nIndex-1," ");
    }

    return str;
}

void CConversion::byte2String(const QByteArray &byteArr, bool bHex, QString strText)
{

}

void CConversion::string2Byte(const QString &strText, bool bHex, QByteArray &byteArr)
{

}

uint8_t CConversion::crc8(const unsigned char *input_str, size_t num_bytes)
{
    uint8_t crc = 0x00;
    uint8_t poly = 0x07;
    int bit;

    while (num_bytes--){
        crc ^= *input_str++;
        for (bit = 0; bit < 8; bit++) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ poly;
            }else{
                crc <<= 1;
            }
        }
    }

    return crc;
}

void CConversion::initTable16()
{
    if(!crc_tab16_init){
        uint16_t i,j,crc,c;

        for (i=0; i<256; i++) {
            crc = 0;
            c   = i;
            for (j=0; j<8; j++) {
                if ( (crc ^ c) & 0x0001 ) crc = ( crc >> 1 ) ^ 0xA001;
                else                      crc =   crc >> 1;
                c = c >> 1;
            }
            crc_tab16[i] = crc;
        }

        crc_tab16_init = true;
    }
}

uint16_t CConversion::crc16(const unsigned char *input_str, size_t num_bytes)
{
    uint16_t crc;
    const unsigned char *ptr;
    size_t a;

    if ( ! crc_tab16_init ) initTable16();

    crc = 0x0000;
    ptr = input_str;

    if ( ptr != NULL ) for (a=0; a<num_bytes; a++) {

        crc = (crc >> 8) ^ crc_tab16[ (crc ^ (uint16_t) *ptr++) & 0x00FF ];
    }
    return crc;
}

uint16_t CConversion::crc16MODBUS(const unsigned char *input_str, size_t num_bytes)
{
    uint16_t crc;
    const unsigned char *ptr;
    size_t a;

    if ( ! crc_tab16_init ) initTable16();
    crc = 0xFFFF;
    ptr = input_str;
    if ( ptr != NULL ) for (a=0; a<num_bytes; a++) {

        crc = (crc >> 8) ^ crc_tab16[ (crc ^ (uint16_t) *ptr++) & 0x00FF ];
    }
    return crc;
}

void CConversion::initTable16DNP()
{
    int i,j;
    uint16_t crc,c;

    for (i=0; i<256; i++) {
        crc = 0;
        c   = (uint16_t) i;
        for (j=0; j<8; j++) {
            if ((crc ^ c) & 0x0001 ) crc = ( crc >> 1 ) ^ 0xA6BC;
            else crc = crc >> 1;
            c = c >> 1;
        }

        crc_tabdnp[i] = crc;
    }

    crc_tabdnp_init = true;
}

uint16_t CConversion::crc16DNP(const unsigned char *input_str, size_t num_bytes)
{
    if (!crc_tabdnp_init ) initTable16DNP();

    unsigned short crc = 0x0000;
    while(num_bytes--){
        crc = (crc >> 8) ^ crc_tabdnp[(crc ^ *input_str++) & 0xff];
    }

    return (crc^0xffff);
}

void CConversion::initTable32()
{
    uint32_t i,j,crc;

    for (i=0; i<256; i++) {
        crc = i;
        for (j=0; j<8; j++) {
            if ( crc & 0x00000001L ) crc = ( crc >> 1 ) ^ 0xEDB88320ul;
            else                     crc =   crc >> 1;
        }

        crc_tab32[i] = crc;
    }
    crc_tab32_init = true;
}

uint16_t CConversion::crc32(const unsigned char *input_str, size_t num_bytes)
{
    uint32_t crc;
    const unsigned char *ptr;
    size_t a;

    if(!crc_tab32_init) initTable32();

    crc = 0xFFFFFFFFul;
    ptr = input_str;

    if ( ptr != NULL ) for (a=0; a<num_bytes; a++) {
        crc = (crc >> 8) ^ crc_tab32[ (crc ^ (uint32_t) *ptr++) & 0x000000FFul ];
    }

    return (crc ^ 0xFFFFFFFFul);
}

