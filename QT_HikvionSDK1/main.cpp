#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(QString::fromLocal8Bit(""));//���ô��ڵ�����
    w.setWindowIcon(QIcon("./images/saveImage.png"));
    w.show();

    return a.exec();
}
