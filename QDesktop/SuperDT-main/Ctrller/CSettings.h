#ifndef CSETTINGS_H
#define CSETTINGS_H

#include <QObject>
#include <QSettings>
#include <QTranslator>
class CSettings : public QObject
{
    Q_OBJECT
public:
    explicit CSettings(QObject *parent = nullptr);

    enum EnmLanguage{
       ENM_LANGUAGE_ZN,
       ENM_LANGUAGE_ENGLISH,
    };

    static CSettings *getInstance();
    QSettings *settings(){return m_pSettings;}
    QByteArray str2ByteArray(QString &strText);
    QString byteArray2Str(QByteArray &byteArr);

    void init();
    void resetLanguage(EnmLanguage enmLag);

    QString textCode();
    void setTextCode(QString textCode);
signals:
    void sigTextCodeChanged(QString strTextCode);
private:
    QSettings *m_pSettings = nullptr;

    QTranslator *m_pTranslator = nullptr;
};

#endif // CSETTINGS_H
