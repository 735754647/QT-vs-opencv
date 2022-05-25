#ifndef HIKVISIONSDK_H
#define HIKVISIONSDK_H
#include"camerainterface.h"
#include"MvCameraControl.h"
#include "HalconCpp.h"
#include "HDevThread.h"
using namespace HalconCpp;
class HikvisionSDK:public CameraInterface
{
public:
    HikvisionSDK();
    ~HikvisionSDK();

    // ch:连接设备
    //int connectCamera(std::string id);
    int connectCamera(int id);


    //设置是否为触发模式
    int setTriggerMode(unsigned int TriggerModeNum);

    //开启相机采集
    int startCamera();

    //关闭相机采集
    int stopCamera();

    //关闭相机
    int closeCamera();

    //软触发
    int softTrigger();

    //读取buffer
    int ReadBuffer(HObject &image);


    //设置图像高度
    int setHeight(unsigned int height);

    //设置图像ROI宽度
    int setWidth(unsigned int width);

    //获取图像高度值
    int getHeight();

    //获取图像宽度值
    int getWidth();

    //获取相机曝光时间
    float getExposureTime();

    //设置图像水平偏移OffsetX
    int setOffsetX(unsigned int offsetX);

    //设置图像竖直偏移OffsetY
    int setOffsetY(unsigned int offsetY);

    //设置触发源
    int setTriggerSource(unsigned int TriggerSourceNum);

    //设置帧率控制使能
    int setFrameRateEnable(bool comm);

    //设置心跳时间
    int setHeartBeatTime(unsigned int time);

    //设置曝光时间
    int setExposureTime(float ExposureTimeNum);

    //设置增益
    int  setGain(float Gain);
    //关闭自动曝光
    int setExposureAuto(bool exposureAutoFlag);

    //关闭自动增益
    int setGainAuto(bool gainAutoFlag);

    //清理相机缓存
    void clearBuffer();

private:
    void*         m_hDevHandle;
public:
    // 用于保存图像的缓存
    unsigned int    m_nBufSizeForSaveImage;
    // 用于从驱动获取图像的缓存
    unsigned int    m_nBufSizeForDriver;
};

#endif // HIKVISIONSDK_H
