#ifndef _MV_SDK_EXPORT_H__
#define _MV_SDK_EXPORT_H__

#include "MvErrorDefine.h"
#include "CameraParams.h"

#ifndef MVSDKEXPORT_API

    #ifdef _WIN32
        #if defined(MVSDKEXPORT_EXPORTS)
            #define MVSDKEXPORT_API __declspec(dllexport)
        #else
            #define MVSDKEXPORT_API __declspec(dllimport)
        #endif
    #else
        #ifndef __stdcall
            #define __stdcall
        #endif

        #ifndef MVSDKEXPORT_API
            #define  MVSDKEXPORT_API
        #endif
    #endif

#endif

#ifndef IN
    #define IN
#endif

#ifndef OUT
    #define OUT
#endif

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************/
/* 相机的基本指令和操作                                         */
/************************************************************************/
MVSDKEXPORT_API unsigned int __stdcall MV_CC_GetSDKVersion();
MVSDKEXPORT_API int __stdcall MV_CC_EnumerateTls();
MVSDKEXPORT_API int __stdcall MV_CC_EnumDevices(IN unsigned int nTLayerType, IN OUT MV_CC_DEVICE_INFO_LIST* pstDevList);
MVSDKEXPORT_API int __stdcall MV_CC_EnumDevicesEx(IN unsigned int nTLayerType, IN OUT MV_CC_DEVICE_INFO_LIST* pstDevList, IN const char* pManufacturerName);
MVSDKEXPORT_API bool __stdcall MV_CC_IsDeviceAccessible(IN MV_CC_DEVICE_INFO* pstDevInfo, IN unsigned int nAccessMode);
MVSDKEXPORT_API int __stdcall MV_CC_SetSDKLogPath(IN const char * pSDKLogPath);
MVSDKEXPORT_API int __stdcall MV_CC_CreateHandle(OUT void ** handle, IN const MV_CC_DEVICE_INFO* pstDevInfo);
MVSDKEXPORT_API int __stdcall MV_CC_CreateHandleWithoutLog(OUT void ** handle, IN const MV_CC_DEVICE_INFO* pstDevInfo);
MVSDKEXPORT_API int __stdcall MV_CC_DestroyHandle(IN void * handle);
MVSDKEXPORT_API int __stdcall MV_CC_OpenDevice(IN void* handle,IN unsigned int nAccessMode, IN unsigned short nSwitchoverKey);
MVSDKEXPORT_API int __stdcall MV_CC_CloseDevice(IN void* handle);
MVSDKEXPORT_API int __stdcall MV_CC_RegisterImageCallBackEx(void* handle, void(__stdcall* cbOutput)(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser),void* pUser);
MVSDKEXPORT_API int __stdcall MV_CC_RegisterImageCallBackForRGB(void* handle, void(__stdcall* cbOutput)(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser),void* pUser);
MVSDKEXPORT_API int __stdcall MV_CC_RegisterImageCallBackForBGR(void* handle, void(__stdcall* cbOutput)(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser), void* pUser);
MVSDKEXPORT_API int __stdcall MV_CC_StartGrabbing(IN void* handle);
MVSDKEXPORT_API int __stdcall MV_CC_StopGrabbing(IN void* handle);
MVSDKEXPORT_API int __stdcall MV_CC_GetImageForRGB(IN void* handle, IN OUT unsigned char * pData , IN unsigned int nDataSize, IN OUT MV_FRAME_OUT_INFO_EX* pFrameInfo, int nMsec);
MVSDKEXPORT_API int __stdcall MV_CC_GetImageForBGR(IN void* handle, IN OUT unsigned char * pData , IN unsigned int nDataSize, IN OUT MV_FRAME_OUT_INFO_EX* pFrameInfo, int nMsec);
MVSDKEXPORT_API int __stdcall MV_CC_GetImageBuffer(IN void* handle, OUT MV_FRAME_OUT* pFrame, int nMsec);
MVSDKEXPORT_API int __stdcall MV_CC_FreeImageBuffer(IN void* handle, IN MV_FRAME_OUT* pFrame);
MVSDKEXPORT_API int __stdcall MV_CC_GetOneFrameTimeout(IN void* handle, IN OUT unsigned char * pData , IN unsigned int nDataSize, IN OUT MV_FRAME_OUT_INFO_EX* pFrameInfo, unsigned int nMsec);
MVSDKEXPORT_API int __stdcall MV_CC_Display(IN void* handle, void* hWnd);
MVSDKEXPORT_API int __stdcall MV_CC_DisplayOneFrame(IN void* handle, IN MV_DISPLAY_FRAME_INFO* pDisplayInfo);
MVSDKEXPORT_API int __stdcall MV_CC_SetImageNodeNum(IN void* handle, unsigned int nNum);
MVSDKEXPORT_API int __stdcall MV_CC_GetImageInfo(IN void* handle, IN OUT MV_IMAGE_BASIC_INFO* pstInfo);
MVSDKEXPORT_API int __stdcall MV_CC_GetDeviceInfo(IN void * handle, IN OUT MV_CC_DEVICE_INFO* pstDevInfo);
MVSDKEXPORT_API int __stdcall MV_CC_GetAllMatchInfo(IN void* handle, IN OUT MV_ALL_MATCH_INFO* pstInfo);

/************************************************************************/
/* 设置和获取相机参数的万能接口                                 */
/************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetIntValue(IN void* handle,IN const char* strValue,OUT MVCC_INTVALUE *pIntValue);
MVSDKEXPORT_API int __stdcall MV_CC_GetIntValueEx(IN void* handle,IN const char* strValue,OUT MVCC_INTVALUE_EX *pIntValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetIntValue(IN void* handle,IN const char* strValue,IN unsigned int nValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetIntValueEx(IN void* handle,IN const char* strValue,IN int64_t nValue);

MVSDKEXPORT_API int __stdcall MV_CC_GetEnumValue(IN void* handle,IN const char* strValue,OUT MVCC_ENUMVALUE *pEnumValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetEnumValue(IN void* handle,IN const char* strValue,IN unsigned int nValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetEnumValueByString(IN void* handle,IN const char* strValue,IN const char* sValue);

MVSDKEXPORT_API int __stdcall MV_CC_GetFloatValue(IN void* handle,IN const char* strValue,OUT MVCC_FLOATVALUE *pFloatValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetFloatValue(IN void* handle,IN const char* strValue,IN float fValue);

MVSDKEXPORT_API int __stdcall MV_CC_GetBoolValue(IN void* handle,IN const char* strValue,OUT bool *pBoolValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetBoolValue(IN void* handle,IN const char* strValue,IN bool bValue);

MVSDKEXPORT_API int __stdcall MV_CC_GetStringValue(IN void* handle,IN const char* strKey,OUT MVCC_STRINGVALUE *pStringValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetStringValue(IN void* handle,IN const char* strKey,IN const char * sValue);

MVSDKEXPORT_API int __stdcall MV_CC_SetCommandValue(IN void* handle,IN const char* strValue);

MVSDKEXPORT_API int __stdcall MV_CC_InvalidateNodes(IN void* handle);

/************************************************************************/
/* 相机参数获取和设置，此模块的所有接口，将逐步废弃，建议用上面的万能接口代替   */
/************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetWidth(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetWidth(IN void* handle, IN const unsigned int nValue);

// 获取和设置图像高度
MVSDKEXPORT_API int __stdcall MV_CC_GetHeight(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetHeight(IN void* handle, IN const unsigned int nValue);

// 获取和设置AOI的偏移
MVSDKEXPORT_API int __stdcall MV_CC_GetAOIoffsetX(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetAOIoffsetX(IN void* handle, IN const unsigned int nValue);

// 获取和设置AOI的偏移
MVSDKEXPORT_API int __stdcall MV_CC_GetAOIoffsetY(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetAOIoffsetY(IN void* handle, IN const unsigned int nValue);

// 调整自动曝光值下限
MVSDKEXPORT_API int __stdcall MV_CC_GetAutoExposureTimeLower(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetAutoExposureTimeLower(IN void* handle, IN const unsigned int nValue);

//调整自动曝光值上限
MVSDKEXPORT_API int __stdcall MV_CC_GetAutoExposureTimeUpper(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetAutoExposureTimeUpper(IN void* handle, IN const unsigned int nValue);

// 明亮度调整
MVSDKEXPORT_API int __stdcall MV_CC_GetBrightness(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetBrightness(IN void* handle, IN const unsigned int nValue);

//获取和设置帧率
MVSDKEXPORT_API int __stdcall MV_CC_GetFrameRate(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetFrameRate(IN void* handle, IN const float fValue);

// 调整增益值
MVSDKEXPORT_API int __stdcall MV_CC_GetGain(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetGain(IN void* handle, IN const float fValue);

// 调整当前曝光值
MVSDKEXPORT_API int __stdcall MV_CC_GetExposureTime(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetExposureTime(IN void* handle, IN const float fValue);

//获取和设置像素格式
MVSDKEXPORT_API int __stdcall MV_CC_GetPixelFormat(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetPixelFormat(IN void* handle, IN const unsigned int nValue);

// 采集模式，参考 CameraParam.h 中的 MV_CAM_ACQUISITION_MODE 定义
MVSDKEXPORT_API int __stdcall MV_CC_GetAcquisitionMode(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetAcquisitionMode(IN void* handle, IN const unsigned int nValue);

// 增益模式，参考 CameraParam.h 中的 MV_CAM_GAIN_MODE 定义
MVSDKEXPORT_API int __stdcall MV_CC_GetGainMode(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetGainMode(IN void* handle, IN const unsigned int nValue);

// 自动曝光模式，参考 CameraParam.h 中的 MV_CAM_EXPOSURE_AUTO_MODE 定义
MVSDKEXPORT_API int __stdcall MV_CC_GetExposureAutoMode(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetExposureAutoMode(IN void* handle, IN const unsigned int nValue);

// 触发模式，参考 CameraParam.h 中的 MV_CAM_TRIGGER_MODE 定义
MVSDKEXPORT_API int __stdcall MV_CC_GetTriggerMode(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetTriggerMode(IN void* handle, IN const unsigned int nValue);

// 触发延时
MVSDKEXPORT_API int __stdcall MV_CC_GetTriggerDelay(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetTriggerDelay(IN void* handle, IN const float fValue);

// 触发源，参考 CameraParam.h 中的 MV_CAM_TRIGGER_SOURCE 定义
MVSDKEXPORT_API int __stdcall MV_CC_GetTriggerSource(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetTriggerSource(IN void* handle, IN const unsigned int nValue);

// 软触发一次（接口仅在已选择的触发源为软件触发时有效）
MVSDKEXPORT_API int __stdcall MV_CC_TriggerSoftwareExecute(IN void* handle);

// Gamma 类型，参考 CameraParam.h 中的 MV_CAM_GAMMA_SELECTOR 定义
MVSDKEXPORT_API int __stdcall MV_CC_GetGammaSelector(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetGammaSelector(IN void* handle, IN const unsigned int nValue);

// Gamma值
MVSDKEXPORT_API int __stdcall MV_CC_GetGamma(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetGamma(IN void* handle, IN const float fValue);

// 锐度
MVSDKEXPORT_API int __stdcall MV_CC_GetSharpness(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetSharpness(IN void* handle, IN const unsigned int nValue);

// 灰度
MVSDKEXPORT_API int __stdcall MV_CC_GetHue(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetHue(IN void* handle, IN const unsigned int nValue);

// 饱和度
MVSDKEXPORT_API int __stdcall MV_CC_GetSaturation(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetSaturation(IN void* handle, IN const unsigned int nValue);

// 自动白平衡，参考 CameraParam.h 中的 MV_CAM_BALANCEWHITE_AUTO 定义
MVSDKEXPORT_API int __stdcall MV_CC_GetBalanceWhiteAuto(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetBalanceWhiteAuto(IN void* handle, IN const unsigned int nValue);

// 白平衡 红
MVSDKEXPORT_API int __stdcall MV_CC_GetBalanceRatioRed(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetBalanceRatioRed(IN void* handle, IN const unsigned int nValue);

// 白平衡 绿
MVSDKEXPORT_API int __stdcall MV_CC_GetBalanceRatioGreen(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetBalanceRatioGreen(IN void* handle, IN const unsigned int nValue);

// 白平衡 蓝
MVSDKEXPORT_API int __stdcall MV_CC_GetBalanceRatioBlue(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetBalanceRatioBlue(IN void* handle, IN const unsigned int nValue);

// 获取水印信息内包含的信息类型
MVSDKEXPORT_API int __stdcall MV_CC_GetFrameSpecInfoAbility(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetFrameSpecInfoAbility(IN void* handle, IN const unsigned int nValue);

MVSDKEXPORT_API int __stdcall MV_CC_GetDeviceUserID(IN void* handle, IN OUT MVCC_STRINGVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetDeviceUserID(IN void* handle, IN const char* chValue);

// 获取和设置相机一次触发的帧数
MVSDKEXPORT_API int __stdcall MV_CC_GetBurstFrameCount(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetBurstFrameCount(IN void* handle, IN const unsigned int nValue);

// 获取和设置行频
MVSDKEXPORT_API int __stdcall MV_CC_GetAcquisitionLineRate(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetAcquisitionLineRate(IN void* handle, IN const unsigned int nValue);

// 获取设备心跳信息
MVSDKEXPORT_API int __stdcall MV_CC_GetHeartBeatTimeout(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetHeartBeatTimeout(IN void* handle, IN const unsigned int nValue);

/************************************************************************/
/* 设备升级 和 寄存器读写 和异常、事件回调                            */
/************************************************************************/
// 设备本地升级
MVSDKEXPORT_API int __stdcall MV_CC_LocalUpgrade(IN void* handle, const void *pFilePathName);
// 获取当前升级进度
MVSDKEXPORT_API int __stdcall MV_CC_GetUpgradeProcess(IN void* handle, unsigned int* pnProcess);
// 获取最佳的packet size，对应GigEVision设备是 SCPS，对应U3V设备是每次从驱动读取的包大小
MVSDKEXPORT_API int __stdcall MV_CC_GetOptimalPacketSize(IN void* handle);

MVSDKEXPORT_API int __stdcall MV_CC_ReadMemory(IN void* handle , void *pBuffer, int64_t nAddress, int64_t nLength);
MVSDKEXPORT_API int __stdcall MV_CC_WriteMemory(IN void* handle , const void *pBuffer, int64_t nAddress, int64_t nLength);

// 注册异常消息回调，在打开设备之后调用
MVSDKEXPORT_API int __stdcall MV_CC_RegisterExceptionCallBack(IN void* handle, void(__stdcall* cbException)(unsigned int nMsgType, void* pUser),void* pUser);

//注册Event回调
MVSDKEXPORT_API int __stdcall MV_CC_RegisterEventCallBackEx(void* handle, const char* pEventName,void(__stdcall* cbEvent)(MV_EVENT_OUT_INFO * pEventInfo, void* pUser),void* pUser);
MVSDKEXPORT_API int __stdcall MV_CC_RegisterAllEventCallBack(void* handle,void(__stdcall* cbEvent)(MV_EVENT_OUT_INFO * pEventInfo, void* pUser),void* pUser);

/************************************************************************/
/* GigEVision 设备独有的接口                                            */
/************************************************************************/
// 强制IP
MVSDKEXPORT_API int __stdcall MV_GIGE_ForceIpEx(IN void* handle, unsigned int nIP, unsigned int nSubNetMask, unsigned int nDefaultGateWay);

// 配置IP方式，type：MV_IP_CFG_x
MVSDKEXPORT_API int __stdcall MV_GIGE_SetIpConfig(IN void* handle, unsigned int nType);

// 设置仅使用某种模式,type: MV_NET_TRANS_x，不设置时，默认优先使用driver
MVSDKEXPORT_API int __stdcall MV_GIGE_SetNetTransMode(IN void* handle, unsigned int nType);

//获取网络传输信息
MVSDKEXPORT_API int __stdcall MV_GIGE_GetNetTransInfo(IN void* handle, MV_NETTRANS_INFO* pstInfo);

//设置gvcp超时时间
MVSDKEXPORT_API int __stdcall MV_GIGE_SetGvcpTimeout(void* handle, unsigned int nMillisec);

//设置是否打开重发包支持，及重发包设置
MVSDKEXPORT_API int __stdcall MV_GIGE_SetResend(void* handle, unsigned int bEnable, unsigned int nMaxResendPercent, unsigned int nResendTimeout);

// 配置网络包大小
MVSDKEXPORT_API int __stdcall MV_GIGE_GetGevSCPSPacketSize(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_GIGE_SetGevSCPSPacketSize(IN void* handle, IN const unsigned int nValue);

// 配置网络包发送间隔
MVSDKEXPORT_API int __stdcall MV_GIGE_GetGevSCPD(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_GIGE_SetGevSCPD(IN void* handle, IN const unsigned int nValue);

// 配置接收端IP地址，0xa9fe0102 表示 169.254.1.2
MVSDKEXPORT_API int __stdcall MV_GIGE_GetGevSCDA(IN void* handle, unsigned int* pnIP);
MVSDKEXPORT_API int __stdcall MV_GIGE_SetGevSCDA(IN void* handle, unsigned int nIP);

// 配置发送端的端口号
MVSDKEXPORT_API int __stdcall MV_GIGE_GetGevSCSP(IN void* handle, unsigned int* pnPort);
MVSDKEXPORT_API int __stdcall MV_GIGE_SetGevSCSP(IN void* handle, unsigned int nPort);

MVSDKEXPORT_API int __stdcall MV_GIGE_SetTransmissionType(void* handle, MV_TRANSMISSION_TYPE * pstTransmissionType);

/************************************************************************/
/* XML解析树的生成                                                         */
/************************************************************************/

MVSDKEXPORT_API int __stdcall MV_XML_GetGenICamXML(IN void* handle, IN OUT unsigned char* pData, IN unsigned int nDataSize, OUT unsigned int* pnDataLen);

// 获取根节点
MVSDKEXPORT_API int __stdcall MV_XML_GetRootNode(IN void* handle, IN OUT MV_XML_NODE_FEATURE* pstNode);

// 从xml中获取指定节点的所有子节点，根节点为Root
MVSDKEXPORT_API int __stdcall MV_XML_GetChildren(IN void* handle, IN MV_XML_NODE_FEATURE* pstNode, IN OUT MV_XML_NODES_LIST* pstNodesList);

//获得当前节点的属性
MVSDKEXPORT_API int __stdcall MV_XML_GetNodeFeature(IN void* handle, IN MV_XML_NODE_FEATURE* pstNode, IN OUT void* pstFeature);

// pstFeature 具体结构体内容参考 MV_XML_FEATURE_x
MVSDKEXPORT_API int __stdcall MV_XML_UpdateNodeFeature(IN void* handle, IN MV_XML_InterfaceType enType, IN void* pstFeature);

// 有节点需要更新时的回调函数
// 当调用MV_XML_UpdateNodeFeature接口更新节点属性时，注册的回调函数cbUpdate会在pstNodesList中返回与之相关联的节点
MVSDKEXPORT_API int __stdcall MV_XML_RegisterUpdateCallBack(IN void* handle, 
                                                            IN void(__stdcall* cbUpdate)(MV_XML_InterfaceType enType, void* pstFeature, MV_XML_NODES_LIST* pstNodesList, void* pUser),
                                                            IN void* pUser);

/************************************************************************/
/* 附加接口                                   */
/************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SaveImageEx2(IN void* handle, IN OUT MV_SAVE_IMAGE_PARAM_EX* pSaveParam);
MVSDKEXPORT_API int __stdcall MV_CC_ConvertPixelType(IN void* handle, IN OUT MV_CC_PIXEL_CONVERT_PARAM* pstCvtParam);
MVSDKEXPORT_API int __stdcall MV_CC_SetBayerCvtQuality(IN void* handle, IN unsigned int BayerCvtQuality);
MVSDKEXPORT_API int __stdcall MV_CC_FeatureSave(IN void* handle, IN const char* pFileName);
MVSDKEXPORT_API int __stdcall MV_CC_FeatureLoad(IN void* handle, IN const char* pFileName);
MVSDKEXPORT_API int __stdcall MV_CC_FileAccessRead(IN void* handle, IN MV_CC_FILE_ACCESS * pstFileAccess);
MVSDKEXPORT_API int __stdcall MV_CC_FileAccessWrite(IN void* handle, IN MV_CC_FILE_ACCESS * pstFileAccess);
MVSDKEXPORT_API int __stdcall MV_CC_GetFileAccessProgress(IN void* handle, OUT MV_CC_FILE_ACCESS_PROGRESS * pstFileAccessProgress);

/************************************************************************/
/* 弃用的接口                                 */
/************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetOneFrame(IN void* handle, IN OUT unsigned char * pData , IN unsigned int nDataSize, IN OUT MV_FRAME_OUT_INFO* pFrameInfo);
MVSDKEXPORT_API int __stdcall MV_CC_RegisterImageCallBack(void* handle, void(__stdcall* cbOutput)(unsigned char * pData, MV_FRAME_OUT_INFO* pFrameInfo, void* pUser),void* pUser);
MVSDKEXPORT_API int __stdcall MV_CC_SaveImage(IN OUT MV_SAVE_IMAGE_PARAM* pSaveParam);
MVSDKEXPORT_API int __stdcall MV_CC_SaveImageEx(IN OUT MV_SAVE_IMAGE_PARAM_EX* pSaveParam);
MVSDKEXPORT_API int __stdcall MV_GIGE_ForceIp(IN void* handle, unsigned int nIP);
MVSDKEXPORT_API int __stdcall MV_CC_RegisterEventCallBack(void* handle, void(__stdcall* cbEvent)(unsigned int nExternalEventId, void* pUser),void* pUser);

#ifdef __cplusplus
}
#endif 

#endif
