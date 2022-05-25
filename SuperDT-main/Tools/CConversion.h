#ifndef CCONVERSION_H
#define CCONVERSION_H

#include <QObject>

static uint16_t crc_tab16[256];
static bool crc_tab16_init = false;

static uint16_t crc_tab32[256];
static bool crc_tab32_init = false;

static uint16_t crc_tabdnp[256];
static bool crc_tabdnp_init = false;

class CConversion
{
public:
    static QByteArray hexStr2ByteArray(QString str,bool *bIsOk = nullptr);
    static QString byteArray2HexStr(QByteArray byteArr);

    //根据编码格式转换
    static void byte2String(const QByteArray &byteArr,bool bHex,QString strText);
    static void string2Byte(const QString &strText,bool bHex,QByteArray &byteArr);
    //CRC8
    static uint8_t crc8(const unsigned char *input_str, size_t num_bytes);
    //CRC16
    static void initTable16();
    static uint16_t crc16(const unsigned char *input_str, size_t num_bytes);
    //CRC16MODBUS
    static uint16_t crc16MODBUS(const unsigned char *input_str, size_t num_bytes);
    //CRC16DNP
    static void initTable16DNP();
    static uint16_t crc16DNP(const unsigned char *input_str, size_t num_bytes);
    //CRC32
    static void initTable32();
    static uint16_t crc32(const unsigned char *input_str, size_t num_bytes);
};

#endif // CCONVERSION_H
