#ifndef CAMERAINTERFACE_H
#define CAMERAINTERFACE_H
//#include"opencv2/opencv.hpp"

#include "HalconCpp.h"
#include "HDevThread.h"
using namespace HalconCpp;

#include"iostream"
class CameraInterface
{
public:
    CameraInterface();
    ~CameraInterface();

    // ch:连接设备
   // virtual int connectCamera(std::string id)=0;
     virtual int connectCamera(int id)=0;

    //设置是否为触发模式
    virtual int setTriggerMode(unsigned int TriggerModeNum)=0;

    //开启相机采集
    virtual int startCamera()=0;

    //关闭相机采集
    virtual int stopCamera()=0;

    //关闭相机
    virtual int closeCamera()=0;

    //软触发
    virtual int softTrigger()=0;

    //读取buffer
    virtual int ReadBuffer(HObject &image)=0;

    //设置图像高度
    virtual int setHeight(unsigned int height)=0;

    //设置图像ROI宽度
    virtual int setWidth(unsigned int width)=0;

    //获取图像高度值
    virtual int getHeight()=0;

    //获取图像宽度值
    virtual int getWidth()=0;

    //获取相机曝光时间
    virtual float getExposureTime()=0;

    //设置图像水平偏移OffsetX
    virtual int setOffsetX(unsigned int offsetX)=0;

    //设置图像竖直偏移OffsetY
    virtual int setOffsetY(unsigned int offsetY)=0;

    //设置触发源
    virtual int setTriggerSource(unsigned int TriggerSourceNum)=0;

    //设置帧率控制使能
    virtual int setFrameRateEnable(bool comm)=0;

    //设置心跳时间
    virtual int setHeartBeatTime(unsigned int time)=0;

    //设置曝光时间
    virtual int setExposureTime(float ExposureTimeNum)=0;

    //设置增益
    virtual int setGain(float Gain)=0;

    //关闭自动曝光
    virtual int setExposureAuto(bool exposureAutoFlag)=0;

    //关闭自动增益
    virtual int setGainAuto(bool gainAutoFlag)=0;

    //virtual int setGain(float Gain)=0;
    //清理相机缓存
    virtual void clearBuffer()=0;
};

#endif // CAMERAINTERFACE_H
