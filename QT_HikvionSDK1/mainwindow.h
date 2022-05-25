#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "Windows.h"
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
    void wheelEvent(QWheelEvent *event);

    bool GunLunFlag = false;
    HObject halconImage;
    HTuple Row0l, Col0l, Row1l, Col1l;
    HTuple wcRow0, wcRow1, wcCol0, wcCol1,m_objImage;

private slots:

    void on_btn_Connect_clicked();
    void on_btn_Trigger_clicked();
    //显示连续图像
    void display(); //信号槽函数
    void InitCam();
    void on_pushButton_clicked();
    void on_StopAcquisition_clicked();
    void on_btn_Close_clicked();
    void on_pushButton_2_clicked();
    void on_pB_exposTime_clicked();
    void on_pB_setGain_clicked();
    void on_lxcj_clicked();

private:
    Ui::MainWindow *ui;
    bool IsRun;
    //用于显示单张图像
    void display(const HObject* image); //私有函数  不可以当槽函数使用
    //相机指针
    CameraInterface* camera=NULL;
    //线程对象
    MyThread* myThread=NULL;
    //用于保存图像的图像指针对象
    HObject* myImage=new HObject();
};

#endif // MAINWINDOW_H
