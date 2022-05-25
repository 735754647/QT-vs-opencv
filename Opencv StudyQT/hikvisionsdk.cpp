#include "hikvisionsdk.h"

MV_CC_DEVICE_INFO_LIST m_stDevList;         // ch:设备信息列表结构体变量，用来存储设备列表
MV_CC_DEVICE_INFO* m_Device=NULL;                 //设备对象


HikvisionSDK::HikvisionSDK()
{
    m_hDevHandle    = NULL;
}

HikvisionSDK::~HikvisionSDK()
{
    if (m_hDevHandle)
    {
        MV_CC_DestroyHandle(m_hDevHandle);
        m_hDevHandle    = NULL;
    }
}


//连接相机
int  HikvisionSDK::connectCamera(std::string id)
{
    //查询设备列表
    int tempValue=MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &m_stDevList);
    if(tempValue!=0)
        //设备更新成功接收命令的返回值为0，返回值不为0则为异常
        return -1;
    if(m_stDevList.nDeviceNum==0)
        //未找到任何相机
        return 2;
    for (unsigned int i = 0; i < m_stDevList.nDeviceNum; i++)
    {
        MV_CC_DEVICE_INFO* pDeviceInfo = m_stDevList.pDeviceInfo[i];

        if (NULL == pDeviceInfo)
        {
            continue;
        }
        if(pDeviceInfo->nTLayerType==MV_USB_DEVICE)
        {
            if(id== (char*)pDeviceInfo->SpecialInfo.stUsb3VInfo.chSerialNumber||id== (char*)pDeviceInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName||id== (char*)pDeviceInfo->SpecialInfo.stUsb3VInfo.chSerialNumber||id=="PECVD")
            {
                m_Device= m_stDevList.pDeviceInfo[i];
                break;
            }
        }

        if(pDeviceInfo->nTLayerType==MV_GIGE_DEVICE)
        {
            if(id== (char*)pDeviceInfo->SpecialInfo.stUsb3VInfo.chSerialNumber||id== (char*)pDeviceInfo->SpecialInfo.stGigEInfo.chUserDefinedName||id== (char*)pDeviceInfo->SpecialInfo.stGigEInfo.chSerialNumber||id=="PECVD")
            {
                m_Device= m_stDevList.pDeviceInfo[i];
                break;
            }
        }
        continue;
    }
    if(m_Device==NULL)
    {
        //未找到指定名称的相机
        return 3;
    }

    tempValue  = MV_CC_CreateHandle(&m_hDevHandle, m_Device);
    if(tempValue!=0)
        return -1;

    tempValue = MV_CC_OpenDevice(m_hDevHandle);
    if (tempValue!=0)
    {
        MV_CC_DestroyHandle(m_hDevHandle);
        m_hDevHandle = NULL;
        return -1;
    }else
    {
        setTriggerMode(1);
        return 0;
    }
    if (m_Device->nTLayerType == MV_GIGE_DEVICE)
    {
    }
    if(m_Device->nTLayerType == MV_USB_DEVICE)
    {
        MV_CC_SetImageNodeNum(&m_hDevHandle,2);
    }
}

//启动相机采集
int HikvisionSDK::startCamera()
{
    int tempValue=MV_CC_StartGrabbing(m_hDevHandle);
    if(tempValue!=0)
    {
        return -1;
    }else
    {
        return 0;
    }
}

//停止相机采集
int HikvisionSDK::stopCamera()
{
    int tempValue=MV_CC_StopGrabbing(m_hDevHandle);
    if(tempValue!=0)
    {
        return -1;
    }else
    {
        return 0;
    }
}

//关闭相机
int HikvisionSDK::closeCamera()
{
    if (NULL == m_hDevHandle)
    {
        return -1;
    }
    MV_CC_CloseDevice(m_hDevHandle);
    int tempValue = MV_CC_DestroyHandle(m_hDevHandle);
    m_hDevHandle = NULL;
    if(tempValue!=0)
    {
        return -1;
    }else
    {
        return 0;
    }
}

//发送软触发
int HikvisionSDK::softTrigger()
{
    int tempValue= MV_CC_SetCommandValue(m_hDevHandle, "TriggerSoftware");
    if(tempValue!=0)
    {
        return -1;
    }else
    {
        return 0;
    }
}

//读取相机中的图像
int HikvisionSDK::ReadBuffer(Mat &image)
{
    Mat* getImage=new Mat();
    unsigned int nRecvBufSize = 0;
    MVCC_INTVALUE stParam;
    memset(&stParam, 0, sizeof(MVCC_INTVALUE));
    int tempValue = MV_CC_GetIntValue(m_hDevHandle, "PayloadSize", &stParam);
    if (tempValue != 0)
    {
        return -1;
    }
    nRecvBufSize = stParam.nCurValue;
    unsigned char* pDate;
    pDate=(unsigned char *)malloc(nRecvBufSize);

    MV_FRAME_OUT_INFO_EX stImageInfo = {0};
    tempValue= MV_CC_GetOneFrameTimeout(m_hDevHandle, pDate, nRecvBufSize, &stImageInfo, 700);
    if(tempValue!=0)
    {
        return -1;
    }
    m_nBufSizeForSaveImage = stImageInfo.nWidth * stImageInfo.nHeight * 3 + 2048;
    unsigned char* m_pBufForSaveImage;
    m_pBufForSaveImage = (unsigned char*)malloc(m_nBufSizeForSaveImage);


    bool isMono;
    switch (stImageInfo.enPixelType)
    {
    case PixelType_Gvsp_Mono8:
    case PixelType_Gvsp_Mono10:
    case PixelType_Gvsp_Mono10_Packed:
    case PixelType_Gvsp_Mono12:
    case PixelType_Gvsp_Mono12_Packed:
        isMono=true;
        break;
    default:
        isMono=false;
        break;
    }
    if(isMono)
    {
        *getImage=Mat(stImageInfo.nHeight,stImageInfo.nWidth,CV_8UC1,pDate);
        //imwrite("d:\\测试opencv_Mono.tif", image);
    }
    else
    {
        //转换图像格式为BGR8
        MV_CC_PIXEL_CONVERT_PARAM stConvertParam = {0};
        memset(&stConvertParam, 0, sizeof(MV_CC_PIXEL_CONVERT_PARAM));
        stConvertParam.nWidth = stImageInfo.nWidth;                 //ch:图像宽 | en:image width
        stConvertParam.nHeight = stImageInfo.nHeight;               //ch:图像高 | en:image height
        //stConvertParam.pSrcData = m_pBufForDriver;                  //ch:输入数据缓存 | en:input data buffer
        stConvertParam.pSrcData = pDate;                  //ch:输入数据缓存 | en:input data buffer
        stConvertParam.nSrcDataLen = stImageInfo.nFrameLen;         //ch:输入数据大小 | en:input data size
        stConvertParam.enSrcPixelType = stImageInfo.enPixelType;    //ch:输入像素格式 | en:input pixel format
        stConvertParam.enDstPixelType = PixelType_Gvsp_BGR8_Packed; //ch:输出像素格式 | en:output pixel format  适用于OPENCV的图像格式
        //stConvertParam.enDstPixelType = PixelType_Gvsp_RGB8_Packed; //ch:输出像素格式 | en:output pixel format
        stConvertParam.pDstBuffer = m_pBufForSaveImage;                    //ch:输出数据缓存 | en:output data buffer
        stConvertParam.nDstBufferSize = m_nBufSizeForSaveImage;            //ch:输出缓存大小 | en:output buffer size
        MV_CC_ConvertPixelType(m_hDevHandle, &stConvertParam);

        *getImage=Mat(stImageInfo.nHeight,stImageInfo.nWidth,CV_8UC3,m_pBufForSaveImage);
        //imwrite("d:\\测试opencv_Color.tif", image);
    }
    (*getImage).copyTo(image);
    (*getImage).release();
    free(pDate);
    free(m_pBufForSaveImage);
    return 0;
}

//获取图像高度值
int HikvisionSDK::getHeight()
{
    MVCC_INTVALUE stParam;
    memset(&stParam, 0, sizeof(MVCC_INTVALUE));
    int tempValue=MV_CC_GetIntValue(m_hDevHandle, "Height", &stParam);
    int value= stParam.nCurValue;
    if(tempValue!=0)
    {
        return -1;
    }else
    {
        return value;
    }
}

//获取图像宽度值
int HikvisionSDK::getWidth()
{
    MVCC_INTVALUE stParam;
    memset(&stParam, 0, sizeof(MVCC_INTVALUE));
    int tempValue=MV_CC_GetIntValue(m_hDevHandle, "Width", &stParam);
    int value= stParam.nCurValue;
    if(tempValue!=0)
    {
        return -1;
    }else
    {
        return value;
    }
}

//获取相机曝光时间
float HikvisionSDK::getExposureTime()
{
    MVCC_FLOATVALUE stParam;
    memset(&stParam, 0, sizeof(MVCC_INTVALUE));
    int tempValue=MV_CC_GetFloatValue(m_hDevHandle, "ExposureTime", &stParam);
    float value= stParam.fCurValue;
    if(tempValue!=0)
    {
        return -1;
    }else
    {
        return value;
    }
}

//设置图像ROI高度
int HikvisionSDK::setHeight(unsigned int height)
{
    int tempValue=MV_CC_SetIntValue(m_hDevHandle, "Height", height);
    if(tempValue!=0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

//设置图像ROI宽度
int HikvisionSDK::setWidth(unsigned int width)
{
    int tempValue=MV_CC_SetIntValue(m_hDevHandle, "Width", width);
    if(tempValue!=0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

//设置图像水平偏移OffsetX
int HikvisionSDK::setOffsetX(unsigned int offsetX)
{
    int tempValue=MV_CC_SetIntValue(m_hDevHandle, "OffsetX", offsetX);
    if(tempValue!=0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

//设置图像竖直偏移OffsetY
int HikvisionSDK::setOffsetY(unsigned int offsetY)
{
    int tempValue=MV_CC_SetIntValue(m_hDevHandle, "OffsetY", offsetY);
    if(tempValue!=0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

//设置是否为触发模式
int HikvisionSDK::setTriggerMode(unsigned int TriggerModeNum)
{
     //0：Off  1：On
     int tempValue= MV_CC_SetEnumValue(m_hDevHandle,"TriggerMode", TriggerModeNum);
     if(tempValue!=0)
     {
         return -1;
     }else
     {
         return 0;
     }
}

//设置触发源
int HikvisionSDK::setTriggerSource(unsigned int TriggerSourceNum)
{
    //0：Line0  1：Line1  7：Software
    int tempValue= MV_CC_SetEnumValue(m_hDevHandle,"TriggerSource", TriggerSourceNum);
    if(tempValue!=0)
    {
        return -1;
    }else
    {
        return 0;
    }
}

//设置帧率控制使能
int HikvisionSDK::setFrameRateEnable(bool comm)
{
    int tempValue =MV_CC_SetBoolValue(m_hDevHandle, "AcquisitionFrameRateEnable", comm);
    if (tempValue != 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

//设置心跳时间
int HikvisionSDK::setHeartBeatTime(unsigned int time)
{
    //心跳时间最小为500ms
    if(time<500)
        time=500;
    int tempValue=MV_CC_SetIntValue(m_hDevHandle, "GevHeartbeatTimeout", time);
    if(tempValue!=0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

//设置曝光时间
int HikvisionSDK::setExposureTime(float ExposureTimeNum)
{
    int tempValue= MV_CC_SetFloatValue(m_hDevHandle, "ExposureTime",ExposureTimeNum );
    if(tempValue!=0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}
//关闭自动曝光
int HikvisionSDK::setExposureAuto(bool exposureAutoFlag)
{
    int tempValue= MV_CC_SetEnumValue(m_hDevHandle,"ExposureAuto", exposureAutoFlag);
    if (tempValue != 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

//关闭自动增益
int HikvisionSDK::setGainAuto(bool gainAutoFlag)
{
    int tempValue= MV_CC_SetEnumValue(m_hDevHandle,"GainAuto", gainAutoFlag);
    if (tempValue != 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

//清理相机缓存
void HikvisionSDK::clearBuffer()
{
    //stopCamera();
    //startCamera();
}
