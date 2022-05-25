#ifndef CCONFIG_H
#define CCONFIG_H

#include <QObject>
#include <QTranslator>

class CConfig : public QObject
{
    Q_OBJECT
public:
    explicit CConfig(QObject *parent = nullptr);

    enum EnmLanguage{
       ENM_LANGUAGE_ZN,
       ENM_LANGUAGE_ENGLISH,
    };
    static CConfig *getInstance();
    void init();
    void resetLanguage(EnmLanguage enmLag);
//    QString textCode();
private:
    QTranslator *m_pTranslator = nullptr;
};

#endif // CCONFIG_H
