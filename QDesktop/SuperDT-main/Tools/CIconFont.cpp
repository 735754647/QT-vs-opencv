#include "CIconFont.h"
#include <QFontDatabase>

CIconFont::CIconFont(QObject *parent) : QObject(parent)
{

}

CIconFont *CIconFont::getInstance()
{
    static CIconFont *pInstance = nullptr;
    if(nullptr == pInstance) {
        pInstance = new CIconFont();
    }
    return pInstance;
}

void CIconFont::init(QString strFile)
{
    int fontId = QFontDatabase::addApplicationFont(strFile);
    m_strFontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
}

QFont CIconFont::font()
{
    return QFont(m_strFontName);
}
#include <QLabel>
#include <QSize>
QPixmap CIconFont::pixmap(QChar ch, QSize size, QString strColor)
{
    QLabel *pLabel = new QLabel();
    pLabel->setText(ch);
    pLabel->setStyleSheet(QString("font:%1px iconfont;color:%2;background:transparent;")
                          .arg(qMin(size.width(),size.height()))
                          .arg(strColor));
    pLabel->resize(size);

    QPixmap pixmap(pLabel->size());
    pixmap.fill(Qt::transparent);
    pLabel->render(&pixmap);
    pLabel->deleteLater();

    return pixmap;
}
