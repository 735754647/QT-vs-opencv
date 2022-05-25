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
/* ����Ļ���ָ��Ͳ���                                         */
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
/* ���úͻ�ȡ������������ܽӿ�                                 */
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
/* ���������ȡ�����ã���ģ������нӿڣ����𲽷�������������������ܽӿڴ���   */
/************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetWidth(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetWidth(IN void* handle, IN const unsigned int nValue);

// ��ȡ������ͼ��߶�
MVSDKEXPORT_API int __stdcall MV_CC_GetHeight(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetHeight(IN void* handle, IN const unsigned int nValue);

// ��ȡ������AOI��ƫ��
MVSDKEXPORT_API int __stdcall MV_CC_GetAOIoffsetX(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetAOIoffsetX(IN void* handle, IN const unsigned int nValue);

// ��ȡ������AOI��ƫ��
MVSDKEXPORT_API int __stdcall MV_CC_GetAOIoffsetY(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetAOIoffsetY(IN void* handle, IN const unsigned int nValue);

// �����Զ��ع�ֵ����
MVSDKEXPORT_API int __stdcall MV_CC_GetAutoExposureTimeLower(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetAutoExposureTimeLower(IN void* handle, IN const unsigned int nValue);

//�����Զ��ع�ֵ����
MVSDKEXPORT_API int __stdcall MV_CC_GetAutoExposureTimeUpper(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetAutoExposureTimeUpper(IN void* handle, IN const unsigned int nValue);

// �����ȵ���
MVSDKEXPORT_API int __stdcall MV_CC_GetBrightness(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetBrightness(IN void* handle, IN const unsigned int nValue);

//��ȡ������֡��
MVSDKEXPORT_API int __stdcall MV_CC_GetFrameRate(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetFrameRate(IN void* handle, IN const float fValue);

// ��������ֵ
MVSDKEXPORT_API int __stdcall MV_CC_GetGain(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetGain(IN void* handle, IN const float fValue);

// ������ǰ�ع�ֵ
MVSDKEXPORT_API int __stdcall MV_CC_GetExposureTime(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetExposureTime(IN void* handle, IN const float fValue);

//��ȡ���������ظ�ʽ
MVSDKEXPORT_API int __stdcall MV_CC_GetPixelFormat(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetPixelFormat(IN void* handle, IN const unsigned int nValue);

// �ɼ�ģʽ���ο� CameraParam.h �е� MV_CAM_ACQUISITION_MODE ����
MVSDKEXPORT_API int __stdcall MV_CC_GetAcquisitionMode(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetAcquisitionMode(IN void* handle, IN const unsigned int nValue);

// ����ģʽ���ο� CameraParam.h �е� MV_CAM_GAIN_MODE ����
MVSDKEXPORT_API int __stdcall MV_CC_GetGainMode(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetGainMode(IN void* handle, IN const unsigned int nValue);

// �Զ��ع�ģʽ���ο� CameraParam.h �е� MV_CAM_EXPOSURE_AUTO_MODE ����
MVSDKEXPORT_API int __stdcall MV_CC_GetExposureAutoMode(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetExposureAutoMode(IN void* handle, IN const unsigned int nValue);

// ����ģʽ���ο� CameraParam.h �е� MV_CAM_TRIGGER_MODE ����
MVSDKEXPORT_API int __stdcall MV_CC_GetTriggerMode(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetTriggerMode(IN void* handle, IN const unsigned int nValue);

// ������ʱ
MVSDKEXPORT_API int __stdcall MV_CC_GetTriggerDelay(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetTriggerDelay(IN void* handle, IN const float fValue);

// ����Դ���ο� CameraParam.h �е� MV_CAM_TRIGGER_SOURCE ����
MVSDKEXPORT_API int __stdcall MV_CC_GetTriggerSource(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetTriggerSource(IN void* handle, IN const unsigned int nValue);

// ����һ�Σ��ӿڽ�����ѡ��Ĵ���ԴΪ�������ʱ��Ч��
MVSDKEXPORT_API int __stdcall MV_CC_TriggerSoftwareExecute(IN void* handle);

// Gamma ���ͣ��ο� CameraParam.h �е� MV_CAM_GAMMA_SELECTOR ����
MVSDKEXPORT_API int __stdcall MV_CC_GetGammaSelector(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetGammaSelector(IN void* handle, IN const unsigned int nValue);

// Gammaֵ
MVSDKEXPORT_API int __stdcall MV_CC_GetGamma(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetGamma(IN void* handle, IN const float fValue);

// ���
MVSDKEXPORT_API int __stdcall MV_CC_GetSharpness(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetSharpness(IN void* handle, IN const unsigned int nValue);

// �Ҷ�
MVSDKEXPORT_API int __stdcall MV_CC_GetHue(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetHue(IN void* handle, IN const unsigned int nValue);

// ���Ͷ�
MVSDKEXPORT_API int __stdcall MV_CC_GetSaturation(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetSaturation(IN void* handle, IN const unsigned int nValue);

// �Զ���ƽ�⣬�ο� CameraParam.h �е� MV_CAM_BALANCEWHITE_AUTO ����
MVSDKEXPORT_API int __stdcall MV_CC_GetBalanceWhiteAuto(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetBalanceWhiteAuto(IN void* handle, IN const unsigned int nValue);

// ��ƽ�� ��
MVSDKEXPORT_API int __stdcall MV_CC_GetBalanceRatioRed(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetBalanceRatioRed(IN void* handle, IN const unsigned int nValue);

// ��ƽ�� ��
MVSDKEXPORT_API int __stdcall MV_CC_GetBalanceRatioGreen(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetBalanceRatioGreen(IN void* handle, IN const unsigned int nValue);

// ��ƽ�� ��
MVSDKEXPORT_API int __stdcall MV_CC_GetBalanceRatioBlue(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetBalanceRatioBlue(IN void* handle, IN const unsigned int nValue);

// ��ȡˮӡ��Ϣ�ڰ�������Ϣ����
MVSDKEXPORT_API int __stdcall MV_CC_GetFrameSpecInfoAbility(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetFrameSpecInfoAbility(IN void* handle, IN const unsigned int nValue);

MVSDKEXPORT_API int __stdcall MV_CC_GetDeviceUserID(IN void* handle, IN OUT MVCC_STRINGVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetDeviceUserID(IN void* handle, IN const char* chValue);

// ��ȡ���������һ�δ�����֡��
MVSDKEXPORT_API int __stdcall MV_CC_GetBurstFrameCount(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetBurstFrameCount(IN void* handle, IN const unsigned int nValue);

// ��ȡ��������Ƶ
MVSDKEXPORT_API int __stdcall MV_CC_GetAcquisitionLineRate(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetAcquisitionLineRate(IN void* handle, IN const unsigned int nValue);

// ��ȡ�豸������Ϣ
MVSDKEXPORT_API int __stdcall MV_CC_GetHeartBeatTimeout(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_CC_SetHeartBeatTimeout(IN void* handle, IN const unsigned int nValue);

/************************************************************************/
/* �豸���� �� �Ĵ�����д ���쳣���¼��ص�                            */
/************************************************************************/
// �豸��������
MVSDKEXPORT_API int __stdcall MV_CC_LocalUpgrade(IN void* handle, const void *pFilePathName);
// ��ȡ��ǰ��������
MVSDKEXPORT_API int __stdcall MV_CC_GetUpgradeProcess(IN void* handle, unsigned int* pnProcess);
// ��ȡ��ѵ�packet size����ӦGigEVision�豸�� SCPS����ӦU3V�豸��ÿ�δ�������ȡ�İ���С
MVSDKEXPORT_API int __stdcall MV_CC_GetOptimalPacketSize(IN void* handle);

MVSDKEXPORT_API int __stdcall MV_CC_ReadMemory(IN void* handle , void *pBuffer, int64_t nAddress, int64_t nLength);
MVSDKEXPORT_API int __stdcall MV_CC_WriteMemory(IN void* handle , const void *pBuffer, int64_t nAddress, int64_t nLength);

// ע���쳣��Ϣ�ص����ڴ��豸֮�����
MVSDKEXPORT_API int __stdcall MV_CC_RegisterExceptionCallBack(IN void* handle, void(__stdcall* cbException)(unsigned int nMsgType, void* pUser),void* pUser);

//ע��Event�ص�
MVSDKEXPORT_API int __stdcall MV_CC_RegisterEventCallBackEx(void* handle, const char* pEventName,void(__stdcall* cbEvent)(MV_EVENT_OUT_INFO * pEventInfo, void* pUser),void* pUser);
MVSDKEXPORT_API int __stdcall MV_CC_RegisterAllEventCallBack(void* handle,void(__stdcall* cbEvent)(MV_EVENT_OUT_INFO * pEventInfo, void* pUser),void* pUser);

/************************************************************************/
/* GigEVision �豸���еĽӿ�                                            */
/************************************************************************/
// ǿ��IP
MVSDKEXPORT_API int __stdcall MV_GIGE_ForceIpEx(IN void* handle, unsigned int nIP, unsigned int nSubNetMask, unsigned int nDefaultGateWay);

// ����IP��ʽ��type��MV_IP_CFG_x
MVSDKEXPORT_API int __stdcall MV_GIGE_SetIpConfig(IN void* handle, unsigned int nType);

// ���ý�ʹ��ĳ��ģʽ,type: MV_NET_TRANS_x��������ʱ��Ĭ������ʹ��driver
MVSDKEXPORT_API int __stdcall MV_GIGE_SetNetTransMode(IN void* handle, unsigned int nType);

//��ȡ���紫����Ϣ
MVSDKEXPORT_API int __stdcall MV_GIGE_GetNetTransInfo(IN void* handle, MV_NETTRANS_INFO* pstInfo);

//����gvcp��ʱʱ��
MVSDKEXPORT_API int __stdcall MV_GIGE_SetGvcpTimeout(void* handle, unsigned int nMillisec);

//�����Ƿ���ط���֧�֣����ط�������
MVSDKEXPORT_API int __stdcall MV_GIGE_SetResend(void* handle, unsigned int bEnable, unsigned int nMaxResendPercent, unsigned int nResendTimeout);

// �����������С
MVSDKEXPORT_API int __stdcall MV_GIGE_GetGevSCPSPacketSize(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_GIGE_SetGevSCPSPacketSize(IN void* handle, IN const unsigned int nValue);

// ������������ͼ��
MVSDKEXPORT_API int __stdcall MV_GIGE_GetGevSCPD(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
MVSDKEXPORT_API int __stdcall MV_GIGE_SetGevSCPD(IN void* handle, IN const unsigned int nValue);

// ���ý��ն�IP��ַ��0xa9fe0102 ��ʾ 169.254.1.2
MVSDKEXPORT_API int __stdcall MV_GIGE_GetGevSCDA(IN void* handle, unsigned int* pnIP);
MVSDKEXPORT_API int __stdcall MV_GIGE_SetGevSCDA(IN void* handle, unsigned int nIP);

// ���÷��Ͷ˵Ķ˿ں�
MVSDKEXPORT_API int __stdcall MV_GIGE_GetGevSCSP(IN void* handle, unsigned int* pnPort);
MVSDKEXPORT_API int __stdcall MV_GIGE_SetGevSCSP(IN void* handle, unsigned int nPort);

MVSDKEXPORT_API int __stdcall MV_GIGE_SetTransmissionType(void* handle, MV_TRANSMISSION_TYPE * pstTransmissionType);

/************************************************************************/
/* XML������������                                                         */
/************************************************************************/

MVSDKEXPORT_API int __stdcall MV_XML_GetGenICamXML(IN void* handle, IN OUT unsigned char* pData, IN unsigned int nDataSize, OUT unsigned int* pnDataLen);

// ��ȡ���ڵ�
MVSDKEXPORT_API int __stdcall MV_XML_GetRootNode(IN void* handle, IN OUT MV_XML_NODE_FEATURE* pstNode);

// ��xml�л�ȡָ���ڵ�������ӽڵ㣬���ڵ�ΪRoot
MVSDKEXPORT_API int __stdcall MV_XML_GetChildren(IN void* handle, IN MV_XML_NODE_FEATURE* pstNode, IN OUT MV_XML_NODES_LIST* pstNodesList);

//��õ�ǰ�ڵ������
MVSDKEXPORT_API int __stdcall MV_XML_GetNodeFeature(IN void* handle, IN MV_XML_NODE_FEATURE* pstNode, IN OUT void* pstFeature);

// pstFeature ����ṹ�����ݲο� MV_XML_FEATURE_x
MVSDKEXPORT_API int __stdcall MV_XML_UpdateNodeFeature(IN void* handle, IN MV_XML_InterfaceType enType, IN void* pstFeature);

// �нڵ���Ҫ����ʱ�Ļص�����
// ������MV_XML_UpdateNodeFeature�ӿڸ��½ڵ�����ʱ��ע��Ļص�����cbUpdate����pstNodesList�з�����֮������Ľڵ�
MVSDKEXPORT_API int __stdcall MV_XML_RegisterUpdateCallBack(IN void* handle, 
                                                            IN void(__stdcall* cbUpdate)(MV_XML_InterfaceType enType, void* pstFeature, MV_XML_NODES_LIST* pstNodesList, void* pUser),
                                                            IN void* pUser);

/************************************************************************/
/* ���ӽӿ�                                   */
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
/* ���õĽӿ�                                 */
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
