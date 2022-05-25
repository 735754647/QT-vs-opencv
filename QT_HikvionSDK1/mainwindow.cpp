#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
#include<QString>
#include<QDebug>
HTuple WindowHandle;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //线程对象实例化
    myThread = new MyThread();
    IsRun = false;
    //将线程中的信号与槽进行连接
     InitCam();
     connect(myThread,SIGNAL(mess()),this,SLOT(display()));//信号槽函数   。必须display  是slot

     // 操作创建窗的窗口口  打开部分
     Hlong windID = (Hlong)this->ui->gvMain->winId();//**将控件和halcon窗体绑定起来，设定父窗体
     OpenWindow(0, 0, ui->gvMain->width(), ui->gvMain->height(), windID, "visible", "", &WindowHandle);//创建一个窗体WindowHandle.
     SetPart(WindowHandle, 0, 0, 1024,1280); // 1944 2592
     GunLunFlag = true;

}


MainWindow::~MainWindow()
{
    delete ui;

    if(camera!=NULL)
    {
        delete camera;
    }
}


void MainWindow::on_btn_Connect_clicked()
{

    if(camera==NULL)
    {
        InitCam();
        ui->btn_Close->setEnabled(false);
    }

}


void MainWindow::InitCam()
{
    camera=new HikvisionSDK();
    //连接相机
    std::cout<<"Connect:  "<<camera->connectCamera(0)<<std::endl;
    //设置为触发模式
    std::cout<<"TriggerMode:  "<<camera->setTriggerMode(1)<<std::endl;
    //设置触发源为软触发
    std::cout<<"TriggerSource:  "<<camera->setTriggerSource(7)<<std::endl;
    //设置曝光时间
    std::cout<<"SetExposureTime:  "<<camera->setExposureTime(40000)<<std::endl;
    //开启相机采集
    std::cout<<"StartCamera:  "<<camera->startCamera()<<std::endl;
    myThread->getCameraPtr(camera);
    //myThread->getImagePtr(myImage);
}

//触发采集
void MainWindow::on_btn_Trigger_clicked()
{
        HObject* image=new HObject();
        IsRun =true;
        //发送软触发
        std::cout<<"SoftTrigger:  "<<camera->softTrigger()<<std::endl;
        //读取Mat格式的图像
        camera->ReadBuffer(*image);
        CopyImage(*image, &halconImage);
        display(image);
        //释放指针
        delete image;
}


//线程调用连续采集
void MainWindow::display()
{
    HObject* image=new HObject();
    //读取Mat格式的图像
    camera->ReadBuffer(*image);
    display(image);
    //释放指针
    delete image;
}


//图片采集函数
void MainWindow::display(const HObject* imagePtr)
{
    std::cout<<"so"<<std::endl;
    //判断是黑白、彩色图像
    DispObj((*imagePtr), WindowHandle);
    QString path="./picture/halcon"+QString::number(ui->sB_Num->value())+".png";
    //WriteImage((*imagePtr), "png", 0, HTuple(path.toLatin1().data()));
    //int num=ui->sB_Num->value();
    //ui->sB_Num->setValue(num+1);
}



void MainWindow::on_pushButton_clicked()
{
    if(!IsRun)
    {
        myThread->start();
        IsRun = true;
    }
    else
    {
        myThread->start();
        IsRun = true;
    }

}



void MainWindow::on_StopAcquisition_clicked()
{
    myThread->ChangeCloseStatus();
    if(IsRun)
    {
        myThread->requestInterruption();
        myThread->wait();

        IsRun =false;
       // camera->stopCamera();
       // camera->closeCamera();
    }
}
void MainWindow::on_btn_Close_clicked()
{
    if(camera!=NULL)
    {
        myThread->requestInterruption();
         camera->closeCamera();
    }
    //ui->Image_Label->clear();
    ui->btn_Connect->setEnabled(true);
}
void MainWindow::on_pushButton_2_clicked()
{

}
void MainWindow::on_pB_exposTime_clicked()
{
    int exposTime=ui->sB_exposure->value();
    int ret=camera->setExposureTime(exposTime);
    qDebug()<<"ret:="<<ret;
}
void MainWindow::on_pB_setGain_clicked()
{
    int Gain =ui->sB_Gain->value();
    int ret=camera->setGain(Gain);
    qDebug()<<"ret:="<<ret;
}
//滚轮事件
void MainWindow::wheelEvent(QWheelEvent *event)
{
    if(ui->gvMain->geometry().contains(this->mapFromGlobal(QCursor::pos())))
    {
        //resizeImage();
        SetWindowExtents(WindowHandle, 0, 0,  ui->gvMain->width(), ui->gvMain->height());
        try
        {
            if (GunLunFlag == true)
        {
            QPoint pos = event->pos();
            HTuple Row0_1, Col0_1, Row1_1, Col1_1;
            HTuple ImagePtX, ImagePtY;
            QRect WndRect;
            double Scale = 0.1;
            HTuple Width, Height;
            GetImageSize(halconImage, &Width, &Height);
            WndRect = QRect(QPoint(0, 0), QPoint(ui->gvMain->width(), ui->gvMain->height()));

            if (WndRect.contains(event->pos()))
            {
                if (event->delta() > 0)
                {
                    ImagePtX = wcCol0 + (pos.x() - WndRect.left()) / (WndRect.width() - 1.0) * (wcCol1 - wcCol0);
                    ImagePtY = wcRow0 + (pos.y() - WndRect.top()) / (WndRect.height() - 1.0) * (wcRow1 - wcRow0);
                    Row0_1 = ImagePtY - 1 / (1 - Scale) * (ImagePtY - wcRow0);
                    Row1_1 = ImagePtY - 1 / (1 - Scale) * (ImagePtY - wcRow1);
                    Col0_1 = ImagePtX - 1 / (1 - Scale) * (ImagePtX - wcCol0);
                    Col1_1 = ImagePtX - 1 / (1 - Scale) * (ImagePtX - wcCol1);
                    wcRow0 = Row0_1;
                    wcCol0 = Col0_1;
                    wcRow1 = Row1_1;
                    wcCol1 = Col1_1;
                    if (wcRow0 < 0 || wcCol0 < 0)
                    {
                        wcRow0 = 0;
                        wcCol0 = 0;
                        wcRow1 = Height;
                        wcCol1 = Width;
                    }
                    ClearWindow(WindowHandle);
                    SetPart(WindowHandle, wcRow0, wcCol0, wcRow1, wcCol1);
                    DispObj(halconImage, WindowHandle);
                }
                else
                {
                    ImagePtX = wcCol0 + (pos.x() - WndRect.left()) / (WndRect.width() - 1.0) * (wcCol1 - wcCol0);
                    ImagePtY = wcRow0 + (pos.y() - WndRect.top()) / (WndRect.height() - 1.0) * (wcRow1 - wcRow0);
                    Row0_1 = ImagePtY - 1 / (1 + Scale) * (ImagePtY - wcRow0);
                    Row1_1 = ImagePtY - 1 / (1 + Scale) * (ImagePtY - wcRow1);
                    Col0_1 = ImagePtX - 1 / (1 + Scale) * (ImagePtX - wcCol0);
                    Col1_1 = ImagePtX - 1 / (1 + Scale) * (ImagePtX - wcCol1);
                    wcRow0 = Row0_1;
                    wcCol0 = Col0_1;
                    wcRow1 = Row1_1;
                    wcCol1 = Col1_1;
                }
                ClearWindow(WindowHandle);
                SetPart(WindowHandle, wcRow0, wcCol0, wcRow1, wcCol1);
                DispObj(halconImage, WindowHandle);
            }
        }
        }
        catch(...)
        {
           ui->lEStatus->setText("Picture is error!.");
           ui->lEStatus->setStyleSheet("background-color: red");
           return;
        }
    }
}
void MainWindow::on_lxcj_clicked()
{

    myThread->ChangeOpenStatus();
    if(!IsRun)
    {
        myThread->start();
        IsRun = true;
    }
    else
    {
        myThread->start();
        IsRun = true;
    }
}

