#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
#include<QString>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //线程对象实例化
    myThread=new MyThread();
    //将线程中的信号与槽进行连接
    connect(myThread,SIGNAL(mess()),this,SLOT(display()));
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
        camera=new HikvisionSDK();
        //连接相机
        std::cout<<"Connect:  "<<camera->connectCamera("00F04893106")<<std::endl;
        //设置为触发模式
        std::cout<<"TriggerMode:  "<<camera->setTriggerMode(1)<<std::endl;
        //设置触发源为软触发
        std::cout<<"TriggerSource:  "<<camera->setTriggerSource(7)<<std::endl;
        //设置曝光时间
        std::cout<<"SetExposureTime:  "<<camera->setExposureTime(40000)<<std::endl;
        //开启相机采集
        std::cout<<"StartCamera:  "<<camera->startCamera()<<std::endl;

        myThread->getCameraPtr(camera);
        myThread->getImagePtr(myImage);
    }

}

void MainWindow::on_btn_Trigger_clicked()
{
        Mat* image=new Mat();
        //发送软触发
        std::cout<<"SoftTrigger:  "<<camera->softTrigger()<<std::endl;
        //读取Mat格式的图像
        camera->ReadBuffer(*image);
        display(image);
        //释放指针
        delete image;
}

void MainWindow::display(const Mat* imagePtr)
{
    std::cout<<"so"<<std::endl;
    //判断是黑白、彩色图像
    QImage* QmyImage=new QImage();
    if(imagePtr->channels()>1)
    {
        *QmyImage=QImage((const unsigned char*)(imagePtr->data),imagePtr->cols, imagePtr->rows, QImage::Format_RGB888);
    }
    else
    {
        *QmyImage=QImage((const unsigned char*)(imagePtr->data),imagePtr->cols, imagePtr->rows, QImage::Format_Indexed8);
    }

    *QmyImage = (*QmyImage).scaled(ui->Image_Label->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    //显示图像
    ui->Image_Label->setPixmap(QPixmap::fromImage(*QmyImage));
    delete QmyImage;
}

void MainWindow::display()
{
    //判断是黑白、彩色图像
    QImage* QmyImage=new QImage();
    if(myImage->channels()>1)
    {
        *QmyImage=QImage((const unsigned char*)(myImage->data),myImage->cols, myImage->rows, QImage::Format_RGB888);
    }
    else
    {
        *QmyImage=QImage((const unsigned char*)(myImage->data),myImage->cols, myImage->rows, QImage::Format_Indexed8);
    }

    *QmyImage = (*QmyImage).scaled(ui->Image_Label->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    //显示图像
    ui->Image_Label->setPixmap(QPixmap::fromImage(*QmyImage));
    delete QmyImage;
}

void MainWindow::on_pushButton_clicked()
{
    if(!myThread->isRunning())
    {
        myThread->start();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if(myThread->isRunning())
    {
        myThread->requestInterruption();
        myThread->wait();
       // camera->stopCamera();
       // camera->closeCamera();
    }
}
