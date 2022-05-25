#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include"hikvisionsdk.h"


#include"QMessageBox"
#include <QCloseEvent>
#include<QSettings>
#include<QDebug>
#include"mythread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btn_Connect_clicked();
    void on_btn_Trigger_clicked();


    //显示连续图像
    void display();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

    //用于显示单张图像
    void display(const Mat* image);

    //相机指针
    CameraInterface* camera=NULL;
    //线程对象
    MyThread* myThread=NULL;
    //用于保存图像的图像指针对象
    Mat* myImage=new Mat();
};

#endif // MAINWINDOW_H
