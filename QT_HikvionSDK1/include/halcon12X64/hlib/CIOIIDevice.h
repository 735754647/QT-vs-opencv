/*****************************************************************************
 * CIOIIDevice.h
 *****************************************************************************
 *
 * Project:     HALCON/libhalcon
 * Description: Integration interface for IO Devices
 *
 * (c) 2013-2014 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 *****************************************************************************
 *
 *
 *****************************************************************************
 */

#ifndef CIOIIDEVICE_H
#define CIOIIDEVICE_H

#ifndef HC_NO_FRAMEGRABBER

#define HIOII_VERSION       1

#define HIOGET_IOII_VERSION(IOI_VERSION)   ((IOI_VERSION)>>16)
#define HIOGET_IOI_REVISION(IOI_VERSION)   (((IOI_VERSION)>>8)&0xFF)
#define HIOGET_IOI_BUILD(IOI_VERSION)      ((IOI_VERSION)&0xFF)
#define HIOI_VERSION(IOI_REVISION,IOI_BUILD)  \
  (((HIOII_VERSION)<<16)|((IOI_REVISION)<<8)|(IOI_BUILD))

#if !defined HIOI_PREFIX
# if defined H_PARALLEL
#  define HIOI_PREFIX "hio"
# else
#   define HIOI_PREFIX "seqhio"
# endif
#endif

#if !defined HIOI_SUFFIX
# if defined HC_LARGE_IMAGES
#  define HIOI_SUFFIX "xl"
# else
#  define HIOI_SUFFIX ""
# endif
#endif

/*
 * The PRINT_ERROR macro is used to print an error message. Please note that
 * if more than one argument is used, the first argument *must* be a string
 * literal.
 * Variadic macros are a feature of C99; however most C++ compilers should
 * support them (Microsoft's cl does since Visual Studio 2005, i.e. cl8).
 * Unfortunately, there is no standard way to determine the number of 
 * arguments, so we must resort to some preprocessor magic.
 *
 * Note that cl's preprocessor is broken (different versions of cl are broken
 * in different ways) and requires various workarounds
 * to get this to work, which make the already complex macro much more
 * difficult to understand.
 */
#if !defined(_MSC_VER)
#  define XCONCAT(A,B) A##B
#  define CONCAT(A,B)  XCONCAT(A,B)
#  define VA_ARGS_CNT(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,N,...) N
#  define VA_ARGS_CEIL2(...) VA_ARGS_CNT(__VA_ARGS__,2,2,2,2,2,2,2,2,2,1)
#  define PRINT_ERROR(...)                                              \
  CONCAT(PRINT_ERROR,VA_ARGS_CEIL2(__VA_ARGS__))(__VA_ARGS__)
#else
#  define COMBINE(A,B) A B
#  define CONCAT__(A,B) A##B
#  define CONCAT_(A,B) CONCAT__(A,B)
#  define CONCAT(A,B)  CONCAT_(A,B)
#  define VA_ARGS_CEIL2(...) VA_ARGS_CNT_((__VA_ARGS__,2,2,2,2,2,2,2,2,2,1))
#  define VA_ARGS_CNT_(foo) VA_ARGS_CNT foo
#  define VA_ARGS_CNT(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,N,...) N
#  define PRINT_ERROR(...)                                              \
  COMBINE(CONCAT(PRINT_ERROR,VA_ARGS_CEIL2(__VA_ARGS__)),(__VA_ARGS__))
#endif
#define PRINT_ERROR1(MSG)                                               \
  do {                                                                  \
    if (HDoLowError)                                                    \
    {                                                                   \
      char msg[MAX_STRING];                                             \
      snprintf(msg,sizeof(msg),"%s\n(%s:%d)",MSG,__func__,__LINE__);    \
      IOPrintErrorMessage(msg);                                         \
    }                                                                   \
  } while (0)                                                           
#define PRINT_ERROR2(FMT,...)                                           \
  do {                                                                  \
    if (HDoLowError)                                                    \
    {                                                                   \
      char msg[MAX_STRING];                                             \
      snprintf(msg,sizeof(msg),FMT"\n(%s:%d)",__VA_ARGS__,__func__,__LINE__);\
      IOPrintErrorMessage(msg);                                         \
    }                                                                   \
  } while (0)                                                           

#if defined(__cplusplus)
extern "C" {
#endif

#ifndef HC_NO_STRUCT_MEMBER_ALIGNMENT 
/* sets the struct member alignment to avoid problems if 
 * the settings of the user differ to those of the HALCON
 * version. (8 is the default alignment, generally) */
# pragma pack(push,8) 
#endif

/* HIOInstance holds the general data of a (virtual) device instance */
typedef struct _HIOInstance {
  struct _HIOClass *ioclass;     /* backward reference to the interface 
                                  * class handle */
  char *H_RESTRICT  name;        /* name of opened device */
  void *H_RESTRICT  iochnl_list; /* list of opened device channels */
  void *H_RESTRICT  usrinst;     /* holds the device specific data, set by 
                                  * the device interface. */
} HIOInstance;

/* HIOChannel holds the general data of a (virtual) channel */
typedef struct _HIOChannel {
  char *H_RESTRICT      name;      /* name of opened channels */
  struct _HIOInstance * ioinst;    /* backward reference to the interface 
                                    * device instance */
  void     *H_RESTRICT  usrchnl;   /* holds the channel specific data, set by
                                    * the device interface. */
} HIOChannel;

/* HIOClass holds the class information of a io device interface */
typedef struct _HIOClass {
  /* -------------------------- internal --------------------------------- */
  char  *lib_name;               /* name of io class library               */
  void  *lib_handle;             /* handle of interface library            */
  INT4  interface_version;       /* current HALCON io device interface 
                                  * version                                */
  INT4  flags;                   /* interface flags                        */
  void  *ioinst_list;            /* list of instantiated device interfaces */
  void  *hioclass;               /* back reference to the actual HALCON 
                                  * handle */
  HBOOL  keep_open;              /* If true, do not close the interface if
                                  * no instances are open.                 */
  /* ----------------- interface-specific functions ---------------------- */
  Herror (*Cleanup)          (Hproc_handle ph, struct _HIOClass *ioclass);
  Herror (*QueryInterface)   (Hproc_handle ph);
  Herror (*OpenDevice)       (Hproc_handle ph,HIOInstance *const* ioinst,
                              INT4_8 *inst_num);
  Herror (*CloseDevice)      (Hproc_handle ph,HIOInstance *const* ioinst,
                              INT4_8 inst_num);
  Herror (*SetDeviceParam)   (Hproc_handle ph,HIOInstance *H_RESTRICT ioinst);
  Herror (*GetDeviceParam)   (Hproc_handle ph,HIOInstance const* ioinst);
  Herror (*QueryDevice)      (Hproc_handle ph,HIOInstance const* ioinst);
  Herror (*OpenChannel)      (Hproc_handle ph,HIOInstance const* ioinst,
                              HIOChannel *const* iochnls, INT4_8 *chnlnum);
  Herror (*CloseChannel)     (Hproc_handle ph,
                              HIOChannel *const* iochnls, INT4_8 chnlnum);
  Herror (*SetChannelParam)  (Hproc_handle ph,
                              HIOChannel *const* iochnls, INT4_8 chnlnum);
  Herror (*GetChannelParam)  (Hproc_handle ph,
                              HIOChannel const*const* iochnls, INT4_8 chnlnum);
  Herror (*ReadChannel)      (Hproc_handle ph,
                              HIOChannel const*const* iochnls, INT4_8 chnlnum);
  Herror (*WriteChannel)     (Hproc_handle ph,
                              HIOChannel *const* iochnls, INT4_8 chnlnum);

  /* These are optional */
  Herror (*ControlInterface) (Hproc_handle ph);
  Herror (*ControlDevice)    (Hproc_handle ph,HIOInstance const* ioinst);
  Herror (*ControlChannel)   (Hproc_handle ph,HIOChannel *const* iochnls,
                              INT4_8 chnlnum);
} HIOClass;


typedef Herror (*HIOI_INIT_FUNC) (Hproc_handle ,HIOClass *);
#define HIOI_INIT_NAME   "HIOIInit"
#define HIOI_FLAGS_NAME  "HIOIFlags"

/*
 * Special IO interface flags. Tp set the flags, the interface should export
 * the symbol HIOI_FLAGS_NAME, which must be an INT4.
 *
 * The following flags are defined:
 *
 * HIO_FLAG_THREAD_INIT: if set, the interface cleanup function is called
 * from the same thread as the init function.
 */
#define HIO_FLAG_THREAD_INIT          (1<<0)  

#ifndef HC_NO_STRUCT_MEMBER_ALIGNMENT 
#pragma pack(pop)
#endif

extern HLibExport  Herror IOPrintErrorMessage(char *err);

extern Herror HStartupCIOIIDevice( void);
extern Herror HShutdownCIOIIDevice( void);


#if defined(__cplusplus)
}
#endif


#endif /* ifndef HC_NO_IODEVICE */
#endif /* ifndef CIODEVICE_H */
