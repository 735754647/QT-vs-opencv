#include "mythread.h"
#include "QDebug"
MyThread::MyThread()
{

}

MyThread::~MyThread()
{
    if(cameraPtr==NULL)
    {
        delete cameraPtr;
    }
//    if(imagePtr==NULL)
//    {
//        delete imagePtr;
//    }
}
void MyThread::getCameraPtr(CameraInterface *camera)
{
    cameraPtr=camera;
}

//void MyThread::getImagePtr(cv::Mat *image)
//{
//    imagePtr=image;
//}

void MyThread::run()
{
    if(cameraPtr==NULL)
    {
        return;
    }

//    if(imagePtr==NULL)
//    {
//        return;
//    }

    while(!isInterruptionRequested())
    {
       if(Status)  //ÅÐ¶ÏÊÇ·ñÍ£Ö¹µÄ×´Ì¬
        {

           std::cout<<"Thread_Trigger:"<<cameraPtr->softTrigger()<<std::endl;
         //  std::cout<<"Thread_Readbuffer:"<<cameraPtr->ReadBuffer(*imagePtr)<<std::endl;
           emit mess();
           msleep(100);
        }
    }
}

void MyThread::ChangeCloseStatus()
{
    Status=false;
    qDebug()<<"Status:="<<Status;
}

void MyThread::ChangeOpenStatus()
{
    Status=true;
    qDebug()<<"Status:="<<Status;
}



