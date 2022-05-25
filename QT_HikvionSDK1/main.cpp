#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(QString::fromLocal8Bit(""));//设置窗口的名称
    w.setWindowIcon(QIcon("./images/saveImage.png"));
    w.show();

    return a.exec();
}
