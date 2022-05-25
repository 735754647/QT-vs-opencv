#include "mythread.h"

MyThread::MyThread()
{

}

MyThread::~MyThread()
{
    if(cameraPtr==NULL)
    {
        delete cameraPtr;
    }
    if(imagePtr==NULL)
    {
        delete imagePtr;
    }
}
void MyThread::getCameraPtr(CameraInterface *camera)
{
    cameraPtr=camera;
}

void MyThread::getImagePtr(cv::Mat *image)
{
    imagePtr=image;
}

void MyThread::run()
{
    if(cameraPtr==NULL)
    {
        return;
    }

    if(imagePtr==NULL)
    {
        return;
    }

    while(!isInterruptionRequested())
    {
        std::cout<<"Thread_Trigger:"<<cameraPtr->softTrigger()<<std::endl;
        std::cout<<"Thread_Readbuffer:"<<cameraPtr->ReadBuffer(*imagePtr)<<std::endl;
        emit mess();
        msleep(50);
    }
}
