#ifndef CUIHELPER_H
#define CUIHELPER_H

#include <QWidget>
#include <QWidget>
#include <QLabel>
#include <QDesktopWidget>
#include <QPropertyAnimation>
#include <QFile>
#include <QMenu>

class CUIHelper
{
public:
    static void showUIBorder();
    static void widgetCenter(QWidget *pWidget, QWidget *parent);
    static void showHintLabel(QWidget *parent, QString strText, QString strFontSize, QString strColor, QString strBgColor, int nShowTime);
    static void showHintInfo(QString strText,QWidget *parent);
    static void installQss(QString strFile);
    static void widgetShake(QWidget *pWidget, int nRange);
    static QPixmap pixmapSvg(QString strContent, QSize size);

    static void menuResetStyle(QMenu *menu); //QMenu 重置阴影 背景透明 支持圆角
    static void recursionSubMenu(QMenu *menu, QList<QMenu *> &menus); //递归获取Menu的所有子菜单 并添加到list中
};

#endif // CUIHELPER_H
