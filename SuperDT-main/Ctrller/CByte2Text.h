#ifndef CBYTE2TEXT_H
#define CBYTE2TEXT_H

#include <QObject>

class CByte2Text : public QObject
{
    Q_OBJECT
public:
    explicit CByte2Text(QByteArray byteArray,bool bHex,QObject *parent = nullptr);

    QString &text(){return m_strText;}
signals:

public slots:
    void slotTextCodeChanged(QString strTextCode, bool bHex);
    void slotByteArrChanged(QByteArray &byteArray);
    void slotHexChanged(bool bHex);
private:
    static void byteArr2Hex(const QByteArray &byteArray, QString &strSource);
    static void byteArr2Utf8(const QByteArray &byteArray, QString &strSource);
    static void byteArr2Gbk(const QByteArray &byteArray, QString &strSource);
private:
    bool m_bHex;
    QString m_strText;
    void (*byteArr2Text)(const QByteArray &,QString &) = nullptr;
};

#endif // CBYTE2TEXT_H
