#ifndef CHELPER_H
#define CHELPER_H

#include <QStringList>
#include <QObject>

class CHelper
{
public:
    static QStringList localIPv4List();
    static QStringList serialportList();
    static void recursiveInstallEventFilter(QObject *pObject); //递归安装所有子孙事件
    static void recursiveResetUIText(QObject *pObject);
};

#endif // CHELPER_H
