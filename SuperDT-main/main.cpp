#include <QApplication>
#include "CMainWindow.h"
#include "CSettings.h"
#include <QFont>
#include "CConversion.h"
#include <QDebug>
#include "CUIHelper.h"
#include "CIconFont.h"

int main(int argc, char *argv[])
{

#if(QT_VERSION >= QT_VERSION_CHECK(5,6,0))
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication a(argc, argv);
    //debug输出格式
    qSetMessagePattern("%{if-debug}[DBUG%{endif}"
                       "%{if-info}\033[32m[INFO%{endif}"
                       "%{if-warning}\033[33m[WARN%{endif}"
                       "%{if-critical}\033[31m[ERRO%{endif}"
                       "%{if-fatal}\033[35m[FATL%{endif}] "
                       "%{time yyyyMMdd h:mm:ss.zzz} "
                       "%{function}:%{line} - %{message}\033[0m");
    a.setApplicationVersion("1.3.3");
    a.setProperty("UpdateDateTime","2022/05/08");

//    QFont font;
//    font.setFamily("等线,Arial");
//    a.setFont(font);

    CSettings::getInstance()->init();
    CIconFont::getInstance()->init(":/Font/iconfont.ttf");
//    CUIHelper::installQss(QString(PRO_DIR) + "/style.qss");

    CMainWindow::getInstance()->resize(800,800);
    CMainWindow::getInstance()->show();


    return a.exec();
}
