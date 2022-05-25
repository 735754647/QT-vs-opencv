#ifndef CICONFONT_H
#define CICONFONT_H

#include <QObject>
#include <QIcon>

class CIconFont : public QObject
{
    Q_OBJECT
public:
    explicit CIconFont(QObject *parent = nullptr);

    static CIconFont *getInstance();

    void init(QString strFile);
    QFont font();

    QPixmap pixmap(QChar ch,QSize size,QString strColor = "black");

    QString m_strFontName;
};

#endif // CICONFONT_H
