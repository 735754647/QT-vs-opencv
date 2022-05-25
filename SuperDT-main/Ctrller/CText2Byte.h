#ifndef CTEXT2BYTE_H
#define CTEXT2BYTE_H

#include <QObject>

class CText2Byte : public QObject
{
    Q_OBJECT
public:
    explicit CText2Byte(QString strText,bool bHex,QObject *parent = nullptr);

    QByteArray &data(){return m_byteArr;}   
public slots:
    void slotTextCodeChanged(QString strTextCode, bool bHex);
    void slotTextChanged(QString &strText);
    void slotHexChanged(bool bHex);
private:
    static void text2Hex(const QString &strSource,QByteArray &byteArray);
    static void text2Utf8(const QString &strSource,QByteArray &byteArray);
    static void text2Gbk(const QString &strSource,QByteArray &byteArray);
private:
    bool m_bHex;
    QByteArray m_byteArr;
    void (*text2ByteArr)(const QString &,QByteArray &) = nullptr; 
};

#endif // CTEXT2BYTE_H
