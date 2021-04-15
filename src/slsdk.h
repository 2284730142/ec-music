/** \file slsdk.h
 * \brief Sunlogin SDK api define
 * \author Oray
 */

#ifndef __ORAY_SLSDK_H__
#define __ORAY_SLSDK_H__


/** \brief SLAPI */
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#define SLAPI __stdcall
#include <windows.h>
#else
#define SLAPI
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief SLAPI�汾��
 */
#define SLAPI_VERSION 1

#ifdef _WIN64
typedef unsigned long long SLPOINTER;
#else
typedef unsigned long SLPOINTER;
#endif

/**
 * \brief �����ƶ˻���
 */
typedef SLPOINTER SLCLIENT;

/**
 * \brief ���ƶ˻���
 */
typedef SLPOINTER SLREMOTE;

/**
 * \brief �Ự
 */
typedef unsigned int SLSESSION;

/**
 * \brief ���
 */
typedef SLPOINTER SLPLUGIN;

/**
 * \brief �����Ķ���ӿ�
 */
typedef SLPOINTER SLOBJINTERFACE;

/** \brief 64 and 32 integer size type definde
 *
 */
#ifndef _WIN32
typedef unsigned long long SLUINT64;
typedef long long SLINT64;
#else
typedef unsigned __int64 SLUINT64;
typedef __int64 SLINT64;
#endif
typedef unsigned int SLUINT32;
typedef int SLINT32;


/**
 * \brief ��Ч�����ƶ˻���
 */
#define SLCLIENT_INVAILD 0

/**
 * \brief ��Ч���ƶ˻���
 */
#define SLREMOTE_INVAILD 0

/**
 * \brief ��Ч�Ự
 */
#define SLSESSION_INVAILD (-1)

/**
 * \brief ��Ч���
 */
#define SLPLUGIN_INVAILD 0

/**
 * \brief ��Ч��ʵ������
 */
#define SLOBJINTERFACE_INVAILD 0

/** \brief Error code
 *
 */
enum SLERRCODE {
  //�ɹ�
  SLERRCODE_SUCCESSED = 0, 

  //�ڲ�����
  SLERRCODE_INNER = 1, 

  //δ��ʼ��
  SLERRCODE_UNINITIALIZED = 2, 

  //��������
  SLERRCODE_ARGS = 3,

  //��֧��
  SLERRCODE_NOTSUPPORT = 4,

  //��������ʧ��
  SLERRCODE_CONNECT_FAILED = 5, 

  //�������ӳ�ʱ
  SLERRCODE_CONNECT_TIMEOUT = 6,

  //�Ự������
  SLERRCODE_SESSION_NOTEXIST = 7,

  //�Ự���
  SLERRCODE_SESSION_OVERFLOW = 8,

  //�Ự���ʹ���
  SLERRCODE_SESSION_WRONGTYPE = 9,

  //OPENID����
  SLERRCODE_EXPIRED = 10,

  //����Ƶ��
  SLERRCODE_REQUEST_FREQUENT = 11,
};

/** \brief Session's option
 *
 */
enum ESLSessionOpt {
  eSLSessionOpt_window = 1,					/*!< Window container */
  eSLSessionOpt_callback = 2,				/*!< Callback */
  eSLSessionOpt_deviceSource = 3,			/*!< Device's source */
  eSLSessionOpt_connected = 4,				/*!< Connect status */
  eSLSessionOpt_desktopctrl_listener = 5,	/*!< Desktop control listener */
  eSLSessionOpt_ipport = 6,					/*!< Port forward ip and port */
  eSLSessionOpt_savepath = 7,				/*!< File transfer save path */
  eSLSessionOpt_desktoptype = 8,			/*!< normal or microlive*/
  eSLSessionOpt_config = 9,					/*!< session config */
};

/** \brief Session's event
 *
 */
enum ESLSessionEvent {
  eSLSessionEvent_OnConnected = 1, 		  /*!< Session connected event */
  eSLSessionEvent_OnDisconnected = 2, 	/*!< Session disconnected event */
  eSLSessionEvent_OnDisplayChanged = 3,	/*!< Display resolution is changed */
  eSLSessionEvent_OnNewFiletrans = 4,   /*!< Recv a new file transfer item */
  eSLSessionEvent_OnGetRemoteSysinfo = 5, /*!< Recv remote sys info */
  eSLSessionEvent_OnRunNewInstance = 6, /*Start new Instance for Server*/
  eSLSessionEvent_OnScreenshotData = 7, /*Recv Screenshot Data*/
};

/** \video defintion
*
*/
enum ESLVideoDefinition {
	eSLVideoDefinition_SD = 1, 		/*!< Standard Definition ����*/
	eSLVideoDefinition_HD = 2, 		/*!< High Definition ����*/
	eSLVideoDefinition_UHD = 3,		/*!< Ultra High-Definition ����*/
};

/** \brief Session callback
 *
 * \param session - Id of the session
 * \param evt - Type of event
 * \param sdata - String format data
 * \param custom - User data bind to the callback
 */
typedef void ( SLAPI *SLSESSION_CALLBACK )( SLSESSION session, ESLSessionEvent evt, const char* sdata, unsigned long size, SLPOINTER custom );
/**
 * \brief �Ự�ص�����
 */
typedef struct tagSLSESSION_CALLBACK_PROP {
	SLSESSION_CALLBACK pfnCallback;	//!< �ص�����
	SLPOINTER nCustom;			//!< �Զ�������
} SLSESSION_CALLBACK_PROP;

/** \brief �Ự����
 *
 */
enum ESLSessionType {
	eSLSessionType_Desktop,		/*!< Remote Desktop session */
	eSLSessionType_File,		/*!< Remote File session */
	eSLSessionType_Cmd,			/*!< Remote CMD session */
	eSLSessionType_Sound,		/*!< Remote sound session */
	eSLSessionType_DataTrans,	/*!< Data transfer session */
	eSLSessionType_DesktopView,	/*!< Remote desktop view mode session */
	eSLSessionType_Port,		/*!< Port forward session */
	eSLSessionType_FileTrans,	/*!< File transfer session */
	eSLSessionType_Camera,		/*!< Remote Camera session */
	eSLSessionType_Sysinfo,		/*!< Remote Sysinfo session */
	eSLSessionType_Screenshots,	/*!< Remote Screenshots session */
	eSLSessionType_Permon,		/*!< Remote Permon session */
	eSLSessionType_Ssh,			/*!< Remote SSH session */
	eSLSessionType_Sound2,		/*!< Remote sound session(webrtc) */
};

enum SLProxyType
{
	SLProxy_None,
	SLProxy_HTTP,
	SLProxy_Socks5,
	SLProxy_Socks4,
	SLProxy_IE,
};

//��ö����������Զ�����湤�����еĶ�Ӧģ��
enum SLDesktopControlType
{
	eSLDesktopControl_ALL,						//����������
	eSLDesktopControl_SWITCH_SCREEN,			//�л���Ļ
	eSLDesktopControl_CHAT,						//����
	eSLDesktopControl_CAMERA,					//����ͷ����
	eSLDesktopControl_FILE,						//�ļ���������
	eSLDesktopControl_RECORD,					//¼��
	eSLDesktopControl_SCREENSHOT,				//����
	eSLDesktopControl_WHITE_BORAD,				//�װ�
	eSLDesktopControl_MORE,						//����
	eSLDesktopControl_FULL_SCREEN,				//ȫ��
	eSLDesktopControl_SCREEN_ORIGINAL_SIZE,		//��Ļԭʼ�ߴ�
	eSLDesktopControl_DESKTOP_MODEL,			//����ģʽ
	eSLDesktopControl_RESOLUTION,				//�ֱ���
	eSLDesktopControl_SWITCH_SESSION,			//�л��Ự
	eSLDesktopControl_SHORTCUT_KEY,				//��ݼ�
	eSLDesktopControl_BLACKSCREEN_MODE,			//����ģʽ
	eSLDesktopControl_FORBID_MOUSE_KEY,			//��ֹ�Է�����
	eSLDesktopControl_SOUND,					//����
	eSLDesktopControl_SHORTCUT_CTRL,			//��ݼ�Ctrl+Alt+Delete
	eSLDesktopControl_SHORTCUT_LOCK,			//��ݼ�����
	eSLDesktopControl_SHORTCUT_LOGOUT,			//��ݼ�ע��
	eSLDesktopControl_SHORTCUT_RESTART,			//��ݼ�����
	eSLDesktopControl_SHORTCUT_SHUTDOWN,		//��ݼ��ػ�
	eSLDesktopControl_SHORTCUT_EXPLORER,		//��ݼ���Դ������
	eSLDesktopControl_SHORTCUT_TASKMGR,			//��ݼ����������
	eSLDesktopControl_SHORTCUT_CONSOLE,			//��ݼ�����̨
};

//��ö�����ڻ�ȡ��Ļ�ͻỰ�ĸ����Լ��л�����
enum SLDesktopDevType
{
	eSLDesktopDev_SCREEN,					//��Ļ
	eSLDesktopDev_SESSION,					//�Ự
	eSLDesktopDev_RESOLUTION,				//�ֱ���
};

//��ö�����ڻ�ȡĳ��ģ�鵱ǰ״̬������
enum SLDesktopStateType
{
	eSLDesktopState_SCREEN_ORIGINAL_SIZE,	//ԭʼ��Ļ����
	eSLDesktopState_FULL_SCREEN,			//ȫ��
	eSLDesktopState_SOUND,					//����
	eSLDesktopState_FORBID_MOUSE_KEY,		//��ֹ�Է�����
	eSLDesktopState_WHITE_BORAD,			//�װ�
	eSLDesktopState_RESOLUTION,				//�ֱ���
	eSLDesktopState_BLACKSCREEN_MODE,		//����ģʽ
	eSLDesktopState_LOCAL_INPUT,			//��������
};

//��ö����������Զ�����湦ģ��Ŀ����͹ر�
enum SLDesktopCommandType
{
	eSLDesktopCommand_CTRL,					//��ݼ�Ctrl+Alt+Delete
	eSLDesktopCommand_LOCK,					//��ݼ�����
	eSLDesktopCommand_LOGOUT,				//��ݼ�ע��
	eSLDesktopCommand_RESTART,				//��ݼ�����
	eSLDesktopCommand_SHUTDOWN,				//��ݼ��ػ�
	eSLDesktopCommand_EXPLORER,				//��ݼ���Դ������
	eSLDesktopCommand_TASKMGR,				//��ݼ����������
	eSLDesktopCommand_CONSOLE,				//��ݼ�����̨

	eSLDesktopCommand_WORK_MODEL,			//����ģʽ
	eSLDesktopCommand_ENTERTAINMENT_MODEL,	//����ģʽ
	eSLDesktopCommand_CHAT,					//��������

	eSLDesktopCommand_SCREEN_ORIGINAL_SIZE,	//ԭʼ��Ļ����
	eSLDesktopCommand_FULL_SCREEN,			//������˳�ȫ��
	eSLDesktopCommand_SOUND,				//������ر�����
	eSLDesktopCommand_FORBID_MOUSE_KEY,		//��ֹ������Է�����
	eSLDesktopCommand_WHITE_BORAD,			//������رհװ�
	eSLDesktopCommand_BLACKSCREEN_MODE,		//������رպ���ģʽ
	eSLDesktopCommand_LOCAL_INPUT,			//������رձ������뷨����

	eSLDesktopCommand_SWITCH_SCREEN,		//�л���Ļ
	eSLDesktopCommand_SWITCH_SESSION,		//�л��Ự
	eSLDesktopCommand_RESOLUTION,			//�л��ֱ���

	//only for android
	eSLDesktopCommand_PULL_DOWN_MENU,		//�����˵�
	eSLDesktopCommand_VOLUME_INCREASE,		//����+
	eSLDesktopCommand_VOLUME_DECREASE,		//����-
	eSLDesktopCommand_HOME_KEY,				//home��
	eSLDesktopCommand_BACK_KEY,				//���ؼ�
	eSLDesktopCommand_MENU_KEY,				//�˵���
	eSLDesktopCommand_LOCK_SCREEN,			//����
	eSLDesktopCommand_SCROLL_UP,			//���Ϲ���
	eSLDesktopCommand_SCROLL_DOWM,			//���¹���
};

//��ö�����ڴ���ʵ������
enum SLObjInterfaceType
{
	eSLObjInterface_AVIConverter,
	eSLObjInterface_CloudMonitor,
	eSLObjInterface_WakeupClient,
};

//��ö�����ڴ���ʵ������
enum SLPlatformType
{
	eSLPlatformType_Windows,
	eSLPlatformType_Linux,
	eSLPlatformType_Mac,
	eSLPlatformType_Android,
	eSLPlatformType_Ios,
	eSLPlatformType_Kvm,
	eSLPlatformType_Kvm_A2,
};

//��ö�����������Ự����
enum SLSoundSourceType
{
	eSLSoundSourceType_Speaker,
	eSLSoundSourceType_Microphone,
	eSLSoundSourceType_TwoWayAudio,
};

enum SLLanguageType
{
	eSLLanguageType_zh_CN,
	eSLLanguageType_English,
};

/**
* ��������
*/
struct SLPROXY_INFO
{
	char ip[20];
	char port[10];
	char user[20];
	char pwd[20];
	char domain[200];
	SLProxyType type;	//ProxyType		
};


typedef enum __slmode {
  UI = 0,
  SERVICE = 1,
} SLMODE;

//����ͷ��Ϣ�ṹ
struct CAMERA_INFO
{
	unsigned int  uDeviceID;			//Ψһ��ʶ
	char  szName[256];					//����ͷ����
};

//������Ϣ�ṹ
struct SLBASE_INFO
{
	unsigned int  uIndex;				//Ψһ��ʶ����
	char  szName[256];					//������Ϣ
};

//����ʵ���ṹ
struct SLINSTANCE_INFO
{
	char  szMod[64];					//ģ������
	char  szName[64];					//������Ϣ
	unsigned int  uID;					//ID��Ϣ
	unsigned int  uPort;				//ת���˿�
};

//Զ�̿ؿؽṹ����
struct SLKVM_INFO
{
	char  szSN[32];						//�ؿ�sn��
	char  szPassword[32];				//�ؿ�����
	char  szIotServerAddr[64];			//�ؿ����ӵ�iot��������ַ
	unsigned int nIotPort;				//�ؿ����ӵ�iot�������˿�
	unsigned int nLoginType;			//�ؿص�¼p2p�������ķ�ʽ��0-������ID��¼ 1-������������¼
	char  szLoginAddr[128];				//������ID���߶�����������¼��ַ
	char  szLoginKey[128];				//������Key���߶�����������¼Session
	unsigned int nTimeout;				//�ؿش����ĻỰʧЧʱ�䣬��Ҫ����Чʱ�������ӿؿ�
};

/** \brief Initialize SLSDK's enviroment
 *
 * \return �Ƿ��ʼ���ɹ�
 */
bool SLAPI SLInitialize();

/*
 * \brief �˳�SLAPI����
 * \desc ���������������˳�ǰ���ã����ͷ�SLAPI������ʹ�õ���Դ
 * \return �Ƿ��˳��ɹ�
 */
bool SLAPI SLUninitialize();

/*
 * \brief ��ȡ���Ĵ�����
 * \return ����SLERRCODE������
 */
SLERRCODE SLAPI SLGetLastError();

/*
 * \brief �������Ĵ�����
 * \param errCode ������
 * \return �Ƿ����óɹ�
 */
bool SLAPI SLSetLastError(SLERRCODE errCode);

/*
 * \brief ��ȡ��������ϸ˵��
 * \return ��ϸ��Ϣ����������벻�����򷵻ء�δ֪����
 */
const char* SLAPI SLGetErrorDesc(SLERRCODE errCode);

/*
 * \brief ����ȫ�ֵ�������Ϣ<��API�����ڲ�ʹ��>
 * \param pstrConfig Json��ʽ��������Ϣ����ϸ����ĵ�
 * \param nLen ������Ϣ�ĳ���
 * \return �Ƿ����óɹ�
 */
bool SLAPI SLSetGlobalConfig(const char* pstrConfig, unsigned int nLen);

/*
 * \brief ����ȫ�ֵ����Ի���
 * \param eType ��������
 */
void SLAPI SLSetLanguage(SLLanguageType eType);


/** \brief �����ƶ��¼�
 *
 */
enum SLCLIENT_EVENT
{
	SLCLIENT_EVENT_ONCONNECT = 0,	//!< ���ӳɹ�
	SLCLIENT_EVENT_ONDISCONNECT,	//!< �Ͽ�����
	SLCLIENT_EVENT_ONLOGIN,			//!< ��¼�ɹ�
	SLCLIENT_EVENT_ONLOGINFAIL,		//!< ��¼ʧ��
	SLCLIENT_EVENT_ONCHANNELSFULL,	//!< ͨ��������
	SLCLIENT_EVENT_ONCHECKCFAIL,	//!< ���ͨ����ʧ��
};

/** \brief ���ض˰󶨿����豸�¼�
*
*/
enum SLCLIENT_WOI_EVENT
{
	SLCLIENT_WOI_EVENT_ONDISCOVER = 0,	//���ֿ����豸
	SLCLIENT_WOI_EVENT_ONBIND,			//�󶨿����豸
	SLCLIENT_WOI_EVENT_ONUNBIND,		//��󿪻��豸
};

/** \brief ���ض�UU�¼�
*
*/
enum SLCLIENT_UU_EVENT
{
	SLCLIENT_UU_EVENT_ONUPGRADESTEP = 0,	//UU��������
	SLCLIENT_UU_EVENT_ONSENDMOUSE,			//UU���������Ϣ
	SLCLIENT_UU_EVENT_ONSENDKEYBOARD,		//UU���ͼ�����Ϣ
};

/** \brief Create a new client with ui mode
 *
 * \return if success return a new instance, else SLCLIENT_INVAILD
 */
SLCLIENT SLAPI SLCreateClient(void);

/** \brief Create a new client with service mode or ui mode
 *
 * \param mode - Client's mode {@see SLMODE}
 * \return if success return a new instance, else SLCLIENT_INVAILD
 */
SLCLIENT SLAPI SLCreateClientEx( SLMODE mode );


/*
 * \brief ����һ�������ƶ˻���
 * \param client Ҫ���ٵı����ƶ˻���
 */
bool SLAPI SLDestroyClient( SLCLIENT client );

/*
 * \brief �����ƶ˻ص��¼�
 * \param client �����ƶ˻���
 * \param event �¼�
 * \param custom �û��Զ������
 */
typedef void (SLAPI *SLCLIENT_CALLBACK)(SLCLIENT client, SLCLIENT_EVENT event, SLPOINTER custom);

/*
 * \brief ���ñ����ƶ��¼��ص�����
 * \param client �����ƶ˻���
 * \param pfnCallback �ص�������ַ
 * \param custom �û��Զ���������ص�ʱ�ڲ�����Ὣ�˲���һ���ص�
 * \return �Ƿ����óɹ�
 */
bool SLAPI SLSetClientCallback(SLCLIENT client, SLCLIENT_CALLBACK pfnCallback, SLPOINTER custom);

/*
 * \brief �����ƶ˵�¼������
 * \param client �����ƶ˻���
 * \param pstrOpenID �����ߵ�ID��
 * \param pstrOpenKey ������ID��Ӧ����֤��
 * \return �Ƿ��¼�ɹ�
 */
bool SLAPI SLClientLoginWithOpenID(SLCLIENT client, const char* pstrOpenID, const char* pstrOpenKey, const char* pstrDomain = "", bool bUseSSL = false);
  
/** \brief Short name for SLClientLoginWithOpenID
 *
 */
bool SLAPI SLLoginWithOpenID(SLCLIENT client, const char* pstrOpenID, const char* pstrOpenKey, const char* pstrDomain = "", bool bUseSSL = false);

  
/*
 * \brief �����ƶ˵�¼������
 * \param client �����ƶ˻���
 * \param szAddr ��������ַ
 * \param szLic lincense
 * \return �Ƿ��¼�ɹ�
 */
bool SLAPI SLClientLoginWithLicense(SLCLIENT client, const char* szAddr, const char* szLic);

/*
 * \brief �����ƶ�ע����¼������
 * \param client �����ƶ˻���
 * \return �Ƿ�ע����¼�ɹ�
 */
bool SLAPI SLClientLogout(SLCLIENT client);

/*
 * \brief �����ƶ��Ƿ��¼��
 * \param client �����ƶ˻���
 */
bool SLAPI SLClientIsOnLoginned(SLCLIENT client);

/*
 * \brief �ڱ����ƶ˻����д���һ���Ự
 * \param client �����ƶ˻���
 * \return �Ựֵ���������ʧ�ܣ��򷵻�SLSESSION_INVAILD
 */
SLSESSION SLAPI SLCreateClientSession(SLCLIENT client, ESLSessionType eType);

/*
 * \brief ����һ���Ự
 * \param client �����ƶ˻���
 * \param session �Ự
 * \return �Ƿ����ٳɹ�
 */
bool SLAPI SLDestroyClientSession(SLCLIENT client, SLSESSION session);

/*
* \brief �򿪱��ض���־
* \param client �����ƶ˻���
* \param path ·��
* \return �Ƿ����óɹ�
*/
bool SLAPI SLOpenClientLog(SLCLIENT client, const char* path, const char* name = 0);

/*
* \brief ���ô���
* \param client �����ƶ˻���
* \param proxy ��������
* \return �Ƿ����óɹ�
*/
bool SLAPI SLSetClientProxy(SLCLIENT client, const SLPROXY_INFO& proxy);

/*
* \brief ���Դ���
* \param client �����ƶ˻���
* \param proxy ��������
* \return ���Դ����Ƿ����ӳɹ�
*/
bool SLAPI SLTestClientPorxy(SLCLIENT client, const SLPROXY_INFO& proxy);

/*
 * \brief ö�ٱ��ض˵�ǰ�ж��ٸ��Ự
 * \param client �����ƶ˻���
 * \param pSessionArray �Ự���飨���������
 * \param nArraySize ���鳤��
 * \return һ���ж��ٸ��Ự
 */
unsigned int SLAPI SLEnumClientSession(SLCLIENT client, SLSESSION* pSessionArray, unsigned int nArraySize);

/*
 * \brief ��ȡ�����ƶ����ӵ�ַ
 * \remark �����ڵ�¼�ɹ����ٻ�ȡ���ܻ�ȡ��ȷ��ֵ�������ص��¼�SLCLIENT_EVENT_ONLOGIN��������á�ͨ����ֵ�����ƶ˲���ʹ�øûỰ�ķ���
 * \return ��ַ
 */
const char* SLAPI SLGetClientAddress(SLCLIENT client);

/*
 * \brief ��ȡ�����ƶ�ĳ���Ự��ֵ
 * \remark ͨ����ֵ�����ƶ˲���ʹ�øûỰ�ķ���
 * \return �Ựֵ������Ự�������򷵻�NULL
 */
const char* SLAPI SLGetClientSessionName(SLCLIENT client, SLSESSION session);

/*
 * \brief ��ñ����ƶ˻Ự�������
 * \param client �����ƶ˻���
 * \param session �Ự
 * \return ������������ȡʧ�ܣ��򷵻�SLPLUGIN_INVAILD
 */
SLPLUGIN SLAPI SLGetClientSessionPlugin(SLCLIENT client, SLSESSION session);

/*
* \brief ��ñ����ƶ˻Ự��������Ϣ
* \param remote �����ƶ˻���
* \param session �Ự
* \param connectType ��������
* \param localType �Ƿ�����ͬһ������������IP��ͬ�� 0:����IP��һ�� 1:����IPһ��
* \return �Ƿ��óɹ�
*/
bool SLAPI SLGetClientSessionConnection(SLCLIENT client, SLSESSION session, unsigned long& connectType, unsigned long& localType);

/*
 * \brief �����ƶ�ĳ���Ự��������
 * \param client �����ƶ˻���
 * \param session �Ự
 * \param lpData ���͵�����
 * \param nLen ���͵����ݳ���
 * \return ���͵��ֽ���
 * \remark Ŀǰֻ������DataTrans���͵ĻỰ
 */
unsigned long SLAPI SLClientSessionSendData(SLCLIENT client, SLSESSION session, const char* lpData, unsigned long nLen);

/*
 * \brief �����ƶ�ĳ���Ự��������
 * \param client �����ƶ˻���
 * \param session �Ự
 * \param lpData �������ݵĻ�����
 * \param nLen ׼�����յ����ݳ���
 * \return ʵ�ʽ��յ����ֽ���
 * \remark Ŀǰֻ������DataTrans���͵ĻỰ
 */
unsigned long SLAPI SLClientSessionRecvData(SLCLIENT client, SLSESSION session, char* lpData, unsigned long nLen);

/*
 * \brief ��ȡ�����ƶ�ĳ���Ựĳ������ֵ
 * \return �Ƿ��ȡ�ɹ�
 */
bool SLAPI SLGetClientSessionOpt(SLCLIENT client, SLSESSION session, ESLSessionOpt eOpt, char* pOptVal, unsigned int nOptLen);

/*
 * \brief ���ñ����ƶ�ĳ���Ựĳ������ֵ
 * \return �Ƿ����óɹ�
 */
bool SLAPI SLSetClientSessionOpt(SLCLIENT client, SLSESSION session, ESLSessionOpt eOpt, const char* pOptVal, unsigned int nOptLen);

/*
 * \brief ����WEB����
 * \return �Ƿ�ɹ�
 */
bool SLAPI SLStartWebServer(SLCLIENT client, unsigned int nPort=0, bool bUseSSL = false, const char* pCert = "", const char* pPrivateKey = "");

/*
 * \brief �ر�WEB����
 * \return �Ƿ�ɹ�
 */
bool SLAPI SLStopWebServer(SLCLIENT client);

/*
 * \brief web������˷���������true��ʾ�Ѿ������˵�ǰ�¼����ײ㽫�����ٴ���
 * \param client �����ƶ˻���
 * \param data ָ�����ݵ�ָ��
 * \param size ���ݳ���
 */
typedef bool (SLAPI *SLWEB_FILTER)(SLCLIENT client,const void* data,unsigned int size);

/*
 * \brief ����web������˷���
 * \param client �����ƶ˻���
 * \param filter ����ָ��
 */
bool SLAPI SlSetWebServerFilter(SLCLIENT client,SLWEB_FILTER filter);

/*
 * \brief ��web�ͻ��˷�������
 * \param client �����ƶ˻���
 * \param data ָ�����ݵ�ָ��
 * \param size ���ݳ���
 */
bool SLAPI SlWebServerSend( SLCLIENT client,const void* pdata,unsigned int size );

/** \brief Send file to peer
 *
 * \param client - Client
 * \param session - Specified session
 * \param filepath - File to be sent 
 * \param resume - Resume transfer
 *
 * \return transfer id of file.
 */
SLUINT32 SLAPI SLClientSendFile( SLCLIENT client, SLSESSION session, const wchar_t* filepath, bool resume );


/** \brief Kill the file item with fid
 *
 * \param client - Client
 * \param session - Specified session
 * \param fid - Id of file item 
 *
 * \return true is ok else failed.
 */
bool SLAPI SLClientKillFile( SLCLIENT client, SLSESSION session, SLUINT32 fid );


/** \brief Get name of file item with fid
 *
 * \param client - Client
 * \param session - Specified session
 * \param fid - Id of file item 
 *
 * \return Name of file item
 */
const wchar_t* SLAPI SLClientGetFileName( SLCLIENT client, SLSESSION session, SLUINT32 fid );

/** \brief Get file size  
 *
 * \param client - Client
 * \param session - Specified session
 * \param fid - Id of file item 
 *
 * \return File item's size.
 */
SLUINT64 SLAPI SLClientGetFileSize( SLCLIENT client, SLSESSION session, SLUINT32 fid );


/** \brief Get file transfered
 *
 * \param client - Client
 * \param session - Specified session
 * \param fid - Id of file item 
 *
 * \return File item's transfered size.
 */
SLUINT64 SLAPI SLClientGetFileTransfered(  SLCLIENT client, SLSESSION session, SLUINT32 fid );


/** \brief File state is in transfering or not
 *
 * \param client - Client 
 * \param session - Specified session
 * \param fid - Id of file item 
 *
 * \return true is transfering else not.
 */
bool SLAPI SLClientFileIsTransfering( SLCLIENT client, SLSESSION session, SLUINT32 fid );


/** \brief File state is done or not
 *
 * \param client - Client
 * \param session - Specified session
 * \param fid - Id of file item 
 *
 * \return true is done else not.
 */
bool SLAPI SLClientFileIsDone( SLCLIENT client, SLSESSION session, SLUINT32 fid );

/** \brief File state is killed or not
 *
 * \param client - Client
 * \param session - Specified session
 * \param fid - Id of file item 
 *
 * \return true is killed else not.
 */
bool SLAPI SLClientFileIsKilled( SLCLIENT client, SLSESSION session, SLUINT32 fid );

bool SLAPI SLDiscoverWoiDevice(SLCLIENT client);

bool SLAPI SLBindWoiDevice(SLCLIENT client, const char* pstrSN, const char* pstrMac, const char* pstrPassword);

bool SLAPI SLUnBindWoiDevice(SLCLIENT client, const char* pstrSN, const char* pstrMac, const char* pstrPassword);

typedef void (SLAPI *SLCLIENT_WOI_CALLBACK)(SLCLIENT client, SLCLIENT_WOI_EVENT event, int code, const char* pstrResponse, SLPOINTER custom);

bool SLAPI SLSetClientWOICallback(SLCLIENT client, SLCLIENT_WOI_CALLBACK pfnCallback, SLPOINTER custom);

typedef void (SLAPI *SLCLIENT_UU_CALLBACK)(SLCLIENT client, SLCLIENT_UU_EVENT event, int err_no, int current, int total, SLPOINTER custom);

bool SLAPI SLSetClientUUCallback(SLCLIENT client, SLCLIENT_UU_CALLBACK pfnCallback, SLPOINTER custom);

int SLAPI SLFindUU(SLCLIENT client, bool isUseUU, char* pVer, unsigned int nVerLen);

bool SLAPI SLUpgradeUU(SLCLIENT client, const char* filepath, int& nCode);

/*
* \brief Զ��������������������
* \param client �����ƶ˻���
* \param session ����Ự
*/
bool SLAPI SLClientStartChat(SLCLIENT client, SLSESSION session, bool bShow = true);

/*
* \brief Զ��������������������
* \param client �����ƶ˻���
* \param session ����Ự
* \param bEnable �л�����/�ۿ�ģʽ
*/
bool SLAPI SLClientEnableControl(SLCLIENT client, SLSESSION session, bool bEnable);

/*
 * \brief ����ģʽ�е������������Ϣ<��API�����ڲ�ʹ��>
 * \param client �����ƶ˻���
 * \param session ����Ự
 * \param cmd ��Ϣ����
 * \param buf ��Ϣ����
 * \param size ��Ϣ��С
 */
bool SLAPI SLClientSendDesktopAgentMsg(SLCLIENT client, SLSESSION session, SLUINT32 cmd, const void* buf, SLUINT32 size);

/*
 * \brief ����ģʽ�������������ʵ��<��API�����ڲ�ʹ��>
 * \param client �����ƶ˻���
 * \param nPort �󶨷���˿�
 * \param nID ����ID
 */
bool SLAPI SLClientRunDesktopAgent(SLCLIENT client, int nPort, int nID);

/*
 * \brief Զ������ʱ������ҷ����<��API�����ڲ�ʹ��>
 * \param client �����ƶ˻���
 */
bool SLAPI SLClientRunDragServer(SLCLIENT client);

/*
 * \brief ����һ������ʵ��<��API�����ڲ�ʹ��>
 */
SLOBJINTERFACE SLAPI SLCreateObjInterface(SLObjInterfaceType eType);

/*
 * \brief ����һ��AVI����ת����<��API�����ڲ�ʹ��>
 * \param interface ��SLCreateInterface����������ʵ������
 */
bool SLAPI SLDestroyObjInterface(SLOBJINTERFACE inter);

/*
 * \brief ���ݲ�ѯ��Ϣ��þ����ϵͳ��Ϣ
 * \param client �����ƶ˻���
 * \param session ϵͳ�Ự
 * \param pstrQuery ��ѯ����
 * \param pstrContent ��ѯ����
 * \return �����ϵͳ��Ϣ
 */
const char* SLAPI SLGetClientSysinfo(SLCLIENT client, SLSESSION session, const char* pstrQuery, const char* pstrContent);

bool SLAPI SLAddPrintServerPort(const char* pstrServerName);
bool SLAPI SLDeletePrintServerPort(const char* pstrServerName);

/************************************************************************/
/* ���ƶ����API                                                        */
/************************************************************************/
/**
 * \brief �����ƶ��¼�
 */
enum SLREMOTE_EVENT
{
  SLREMOTE_EVENT_ONCONNECT = 0, 		//!< ���ӳɹ�
  SLREMOTE_EVENT_ONDISCONNECT, 			//!< �Ͽ�����
  SLREMOTE_EVENT_ONDISCONNECT_FOR_FULL, //!< �Ͽ�����(��Ϊ����������)  
};

/*
 * \brief ����һ�����ƶ˻���
 * \return ���ر����ƶ˻���ֵ���������ʧ���򷵻�SLREMOTE_INVAILD
 */
SLREMOTE SLAPI SLCreateRemote(void);

/*
 * \brief ����һ�����ƶ˻���
 * \param remote ���ƶ˻���
 * \return �Ƿ����ٳɹ�
 */
bool SLAPI SLDestroyRemote(SLREMOTE remote);

/*
* \brief �򿪿��ƶ���־
* \param remote ���ƶ˻���
* \param path ·��
* \return �Ƿ����óɹ�
*/
bool SLAPI SLOpenRemoteLog(SLREMOTE remote, const char* path, const char* name = 0);

/*
* \brief ���ô���
* \param client �����ƶ˻���
* \param remote ���ƶ˻���
* \return �Ƿ����óɹ�
*/
bool SLAPI SLSetRemoteProxy(SLREMOTE remote, const SLPROXY_INFO& proxy);

/*
* \brief ���Դ���
* \param Remote ���ƶ˻���
* \param proxy ��������
* \return ���Դ����Ƿ����ӳɹ�
*/
bool SLAPI SLTestRemotePorxy(SLCLIENT remote, const SLPROXY_INFO& proxy);

/*
 * \brief �����ƶ˻ص��¼�
 * \param remote �����ƶ˻���
 * \param event �¼�
 * \param custom �û��Զ������
 */
typedef void (SLAPI *SLREMOTE_CALLBACK)(SLREMOTE remote, SLSESSION session, SLREMOTE_EVENT event, SLPOINTER custom);

/*
 * \brief ���������ƶ��¼��ص�����
 * \param remote �����ƶ˻���
 * \param pfnCallback �ص�������ַ
 * \param custom �û��Զ���������ص�ʱ�ڲ�����Ὣ�˲���һ���ص�
 * \return �Ƿ����óɹ�
 */
bool SLAPI SLSetRemoteCallback(SLREMOTE remote, SLREMOTE_CALLBACK pfnCallback, SLPOINTER custom);

/*
 * \brief ���������ƶ˻Ự
 * \param remote ���ƶ˻���
 * \param eType �Ự����
 * \param pstrAddress Զ�̱����ƶ˵�ַ
 * \param pstrSession Զ������Ự��
 * \return �Ự
 */
SLSESSION SLAPI SLCreateRemoteSession(SLREMOTE remote, ESLSessionType eType, const char* pstrAddress, const char* pstrSession);

/*
 * \brief ���������ƶ˿ջỰ(������)
 * \param remote ���ƶ˻���
 * \param eType �Ự����
 * \remark ��SLCreateRemoteSession��ͬ���Ǵ���һ���ջỰ�����������ӣ����������ʹ��SLConnectRemoteSession�����ӻỰ
 * \return �Ự
 */
SLSESSION SLAPI SLCreateRemoteEmptySession(SLREMOTE remote, ESLSessionType eType);

/*
 * \brief �������ض˻Ự
 * \param remote ���ƶ˻���
 * \param session �Ự
 * \param pstrAddress Զ�̱����ƶ˵�ַ
 * \param pstrSession Զ������Ự��
 * \return �Ự
 */
bool SLAPI SLConnectRemoteSession(SLREMOTE remote, SLSESSION session, const char* pstrAddress, const char* pstrSession);

/*
 * \brief �������ض˻Ự--���ض����ǿؿ�
 * \param remote ���ƶ˻���
 * \param session �Ự
 * \param kvm_info ���ؿؿ�������Ϣ
 * \return �Ƿ����ӳɹ�
 */
bool SLAPI SLConnectKVMRemoteSession(SLREMOTE remote, SLSESSION session, const SLKVM_INFO& kvm_info);

/*
 * \brief ����һ���Ự
 * \param remote ���ƶ˻���
 * \param session �Ự
 * \return �Ƿ����ٳɹ�
 */
bool SLAPI SLDestroyRemoteSession(SLREMOTE remote, SLSESSION session);

/*
 * \brief ��������ƶ˻Ự�������
 * \param remote �����ƶ˻���
 * \param session �Ự
 * \return ������������ȡʧ�ܣ��򷵻�SLPLUGIN_INVAILD
 */
SLPLUGIN SLAPI SLGetRemoteSessionPlugin(SLREMOTE remote, SLSESSION session);

/*
 * \brief ��������ƶ˻Ự��������Ϣ
 * \param remote �����ƶ˻���
 * \param session �Ự
 * \param connectType ��������
 * \param localType �Ƿ�����ͬһ������������IP��ͬ�� 0:����IP��һ�� 1:����IPһ��
 * \return �Ƿ��óɹ�
 */
bool SLAPI SLGetRemoteSessionConnection(SLREMOTE remote, SLSESSION session, unsigned long& connectType, unsigned long& localType);

/*
 * \brief �����ƶ�ĳ���Ự��������
 * \param remote �����ƶ˻���
 * \param session �Ự
 * \param lpData ���͵�����
 * \param nLen ���͵����ݳ���
 * \return ���͵��ֽ���
 * \remark Ŀǰֻ������DataTrans���͵ĻỰ
 */
unsigned long SLAPI SLRemoteSessionSendData(SLREMOTE remote, SLSESSION session, const char* lpData, unsigned long nLen);

/*
 * \brief �����ƶ�ĳ���Ự��������
 * \param remote �����ƶ˻���
 * \param session �Ự
 * \param lpData �������ݵĻ�����
 * \param nLen �������ݻ���������
 * \return ʵ�ʽ��յ����ֽ���
 * \remark Ŀǰֻ������DataTrans���͵ĻỰ
 */
unsigned long SLAPI SLRemoteSessionRecvData(SLREMOTE remote, SLSESSION session, char* lpData, unsigned long nLen);

/*
 * \brief ��ȡ�����ƶ�ĳ���Ựĳ������ֵ
 * \return �Ƿ����óɹ�
 */
bool SLAPI SLGetRemoteSessionOpt(SLREMOTE remote, SLSESSION session, ESLSessionOpt eOpt, char* pOptVal, unsigned int nOptLen);

/*
 * \brief ���������ƶ�ĳ���Ựĳ������ֵ
 * \return �Ƿ����óɹ�
 */
bool SLAPI SLSetRemoteSessionOpt(SLREMOTE remote, SLSESSION session, ESLSessionOpt eOpt, const char* pOptVal, unsigned int nOptLen);

/*
* \brief ��ȡԶ�̻Ự��֡��
* \return ֡��
*/
unsigned long SLAPI SLGetRemoteDesktopFrameCount(SLREMOTE remote, SLSESSION session);
/*
 * \brief ����Զ�����洰�ڵĴ�С
 * \return �Ƿ����óɹ�
 */
bool SLAPI SLSetDesktopSessionPos(SLREMOTE remote, SLSESSION session, int x,int y,int width,int height);

/*
 * \brief Show desktop window
 * \return �Ƿ����óɹ�
 */
bool SLAPI SLSetDesktopSessionVisible( SLREMOTE remote, SLSESSION session );

  
/** \brief	Get original desktop size
 * \return	
 */
bool SLAPI SLGetDesktopSessionOriginSize( SLREMOTE remote, SLSESSION session, int* width, int* height );


/** \brief Start desktop record, Only one file in recording.
 * 
 * \param remote - Peer
 * \param session - Specified session
 * \param filepath - Desktop record file 
 *
 * \return true is ok else failed.
 */
bool SLAPI SLRemoteDesktopStartRecord( SLREMOTE remote, SLSESSION session, const char* filepath );


/** \brief Stop desktop record
 * 
 * \param remote - Peer
 * \param session - Specified session
 *
 */
void SLAPI SLRemoteDesktopStopRecord( SLREMOTE remote, SLSESSION session );





/** \brief Send file to peer
 *
 * \param remote - Peer
 * \param session - Specified session
 * \param filepath - File to be sent 
 * \param resume - Resume transfer
 *
 * \return transfer id of file.
 */
SLUINT32 SLAPI SLRemoteSendFile(SLREMOTE remote, SLSESSION session, const wchar_t* filepath, bool resume );


/** \brief Kill the file item with fid
 *
 * \param remote - Peer
 * \param session - Specified session
 * \param fid - Id of file item 
 *
 * \return true is ok else failed.
 */
bool SLAPI SLRemoteKillFile( SLREMOTE remote, SLSESSION session, SLUINT32 fid );

/** \brief Get name of file item with fid
 *
 * \param remote - Peer
 * \param session - Specified session
 * \param fid - Id of file item 
 *
 * \return Name of file item
 */
const wchar_t* SLAPI SLRemoteGetFileName( SLREMOTE client, SLSESSION session, SLUINT32 fid );


/** \brief Get file size  
 *
 * \param remote - Peer
 * \param session - Specified session
 * \param fid - Id of file item 
 *
 * \return File item's size.
 */
SLUINT64 SLAPI SLRemoteGetFileSize(  SLREMOTE remote, SLSESSION session, SLUINT32 fid );


/** \brief Get file transfered
 *
 * \param remote - Peer
 * \param session - Specified session
 * \param fid - Id of file item 
 *
 * \return File item's transfered size.
 */
SLUINT64 SLAPI SLRemoteGetFileTransfered(  SLREMOTE remote, SLSESSION session, SLUINT32 fid );


/** \brief File state is in transfering or not
 *
 * \param remote - Peer
 * \param session - Specified session
 * \param fid - Id of file item 
 *
 * \return true is transfering else not.
 */
bool SLAPI SLRemoteFileIsTransfering( SLREMOTE remote, SLSESSION session, SLUINT32 fid );


/** \brief File state is done or not
 *
 * \param remote - Peer
 * \param session - Specified session
 * \param fid - Id of file item 
 *
 * \return true is done else not.
 */
bool SLAPI SLRemoteFileIsDone( SLREMOTE remote, SLSESSION session, SLUINT32 fid );

/** \brief File state is killed or not
 *
 * \param remote - Peer
 * \param session - Specified session
 * \param fid - Id of file item 
 *
 * \return true is killed else not.
 */
bool SLAPI SLRemoteFileIsKilled( SLREMOTE remote, SLSESSION session, SLUINT32 fid );

/*
* \brief ����Զ��CMD���ڵĴ�С
* \return �Ƿ����óɹ�
*/
bool SLAPI SLSetCmdSessionPos(SLREMOTE remote, SLSESSION session, int x, int y, int width, int height);

/*
* \brief ����Զ������ͷ���ڵĴ�С
* \return �Ƿ����óɹ�
*/
bool SLAPI SLSetCameraSessionPos(SLREMOTE remote, SLSESSION session, int x, int y, int width, int height);

/*
* \brief ��Զ������ͷ
* \return �Ƿ�򿪳ɹ�
*/
bool SLAPI SLRemoteCameraOpen(SLREMOTE remote, SLSESSION session, unsigned long dev_id);

/*
* \brief �ر�Զ������ͷ
* \return �Ƿ�رճɹ�
*/
bool SLAPI SLRemoteCameraClose(SLREMOTE remote, SLSESSION session);

/*
* \brief ����Զ������ͷ������
* \return �Ƿ����óɹ�
*/
bool SLAPI SLRemoteCameraSetDefinition(SLREMOTE remote, SLSESSION session, ESLVideoDefinition eVD);

/*
* \brief ��ȡ����ͷ�б�
* \param infos ����ͷ�ṹ�����飬��Ϊ�գ���˺����������б��С
* \param nSize �����С
* \return �����б��С
*/
unsigned int SLAPI SLRemoteCameraGetList(SLREMOTE remote, SLSESSION session, CAMERA_INFO* infos = 0, unsigned int nSize = 0);

/*
* \brief ����Զ�̿�����������ַ����ƶ˿�
* \return �Ƿ����óɹ�
*/
bool SLSetRemoteWOIControl(SLREMOTE remote, const char* pstrAddress, unsigned int nPort);

/*
* \brief ����Զ�̿���ָ��
* \return �Ƿ��ͳɹ�
*/
bool SLAPI SLSendWakeupCommand(SLREMOTE remote, const char* pstrMac, const char* pstrPassword);

/*
* \brief Զ�̻��ѻص��¼�
* \param remote �����ƶ˻���
* \param code http��Ӧcode
* \param pstrResponse http��Ӧ��������
* \param custom �û��Զ������
*/
typedef void (SLAPI *SLREMOTE_WOI_CALLBACK)(SLREMOTE remote, int code, const char* pstrResponse, SLPOINTER custom);

/*
* \brief ���������ƶ�Զ�̻����¼��ص�����
* \param remote �����ƶ˻���
* \param pfnCallback �ص�������ַ
* \param custom �û��Զ���������ص�ʱ�ڲ�����Ὣ�˲���һ���ص�
* \return �Ƿ����óɹ�
*/
bool SLAPI SLSetRemoteWOICallback(SLREMOTE remote, SLREMOTE_WOI_CALLBACK pfnCallback, SLPOINTER custom);

/*
* \brief ���Զ�̿ͻ��˵�ϵͳ��Ϣ
* \param remote �����ƶ˻���
* \param session ��Ӧ��session
* \param pstrQuery ��ѯ����
* \param pstrContent ��ѯ����
* \return �˴β�����ID
*/
unsigned int SLAPI SLGetRemoteSysinfo(SLREMOTE remote, SLSESSION session, const char* pstrQuery, const char* pstrContent);

/*
* \brief ���Զ�̿ͻ��˵�ϵͳ��Ϣ
* \param remote �����ƶ˻���
* \param session ��Ӧ��session
* \param pstrQuery ��ѯ����
* \param pstrContent ��ѯ����
* \return �˴β�����ID
*/
unsigned int SLAPI SLGetScreenshot(SLREMOTE remote, SLSESSION session, int width, int height);

/*
* \brief ����Զ�����湤�����Ƿ�ɼ�
* \param remote �����ƶ˻���
* \param session ��Ӧ��session
* \param eType ö�����صĶ���
* \return �Ƿ����óɹ�
*/
bool SLAPI SLHideRemoteDesktopToolbarItem(SLREMOTE remote, SLSESSION session, SLDesktopControlType eType);

/*
* \brief ��ȡԶ��������Ļ,�Ự,�ֱ��ʵ��б���Ϣ
* \param remote �����ƶ˻���
* \param session ��Ӧ��session
* \param infos ������Ϣ�ṹ����Ϊ�գ���˺����������б��С
* \param nSize �����С
* \return �����б��С
*/
unsigned int SLAPI SLGetRemoteDesktopDevList(SLREMOTE remote, SLSESSION session, SLDesktopDevType eType, SLBASE_INFO* infos = 0, unsigned int nSize = 0);

/*
* \brief ����Զ�������������
* \param remote �����ƶ˻���
* \param session ��Ӧ��session
* \param eType ��Ӧ�Ĳ�������
* \param nIndex ����ֵ,ֻ������л���Ļ���л��Ự���л��ֱ��ʵ�ѡ���Ե�������Ч
* \return �Ƿ�ɹ�
*/
bool SLAPI SLSendRemoteDesktopCommand(SLREMOTE remote, SLSESSION session, SLDesktopCommandType eType, unsigned int nIndex = 0);

/*
* \brief ���Զ�����浱ǰ״̬
* \param remote �����ƶ˻���
* \param session ��Ӧ��session
* \param eType ��Ӧ�Ĳ�������
* \param nState ״ֵ̬��ǰѡ������ֵ
* \return �Ƿ�ɹ�
*/
bool SLAPI SLGetRemoteDesktopCurState(SLREMOTE remote, SLSESSION session, SLDesktopStateType eType, unsigned int& nState);

/*
* \brief ����
* \param remote �����ƶ˻���
* \param session ��Ӧ��session
* \param filepath �����ļ�ȫ·��
* \return �Ƿ�ɹ�
*/
bool SLAPI SLRemoteDesktopScreenShot(SLREMOTE remote, SLSESSION session, const char* filepath);

/*
* \brief ����
* \param remote �����ƶ˻���
* \param session ��Ӧ��session
* \param filepath ���ض˶�Ӧ�Ĳ���ƽ̨
* \return �Ƿ�ɹ�
*/
bool SLAPI SLSetRemoteDesktopPlatform(SLREMOTE remote, SLSESSION session, SLPlatformType eType);

/*
* \brief ����Զ�������������
* \param remote �����ƶ˻���
* \param session ��Ӧ��session
* \param key ��Ӧ�ļ����ַ���
* \param isDown �Ƿ��Ǽ��̰���
* \return �Ƿ�ɹ�
*/
bool SLAPI SLSendRemoteDesktopKeyUpDown(SLREMOTE remote, SLSESSION session, const char* key, bool isDown);

/*
* \brief ��Զ�������Զ�������󶨻��߽��
* \param remote �����ƶ˻���
* \param session ��Ӧ������session
* \param soundSession ��Ӧ������session
* \return �Ƿ�ɹ�
*/
bool SLAPI SLRemoteDesktopBindSound(SLREMOTE remote, SLSESSION session, SLSESSION soundSession);

/*
* \brief ����Զ��SSH���ڵĴ�С
* \return �Ƿ����óɹ�
*/
bool SLAPI SLSetSshSessionPos(SLREMOTE remote, SLSESSION session, int x, int y, int width, int height);

/*
* \brief ����Զ��Զ���ļ������ڵĴ�С
* \return �Ƿ����óɹ�
*/
bool SLAPI SLSetFileMgrSessionPos(SLREMOTE remote, SLSESSION session, int x, int y, int width, int height);

/*
* \brief ����Զ������ˮӡͼƬ
* \param remote �����ƶ˻���
* \param session ��Ӧ������session
* \param x ˮӡ����ƫ����(����0��ʾ��߾࣬С��0��ʾ�ұ߾�)
* \param y ˮӡ����ƫ����(����0��ʾ�ϱ߾࣬С��0��ʾ�±߾�)
* \param width ˮӡͼ����
* \param height ˮӡͼ��߶�
* \param alpha ͸����(0-255)
* \param buf ˮӡͼ�񻺴�(ARGB)
* \param buflen ˮӡͼ�񻺴泤��
* \return �Ƿ�ɹ�
*/
bool SLAPI SLSetRemoteDesktopWatermark(SLREMOTE remote, SLSESSION session, int x, int y, int width, int height, int alpha, const char* buf, unsigned long buflen);

/*
* \brief ��ȡԶ������ͼ��λͼ����������������С
* \param remote �����ƶ˻���
* \param session ��Ӧ������session
* \param buf ����λͼ����������Ϊ�գ��˺������ػ�������С
* \param buflen ����λͼ��������С
* \return ��������С
*/
unsigned int SLAPI SLGetRemoteDesktopBuffer(SLREMOTE remote, SLSESSION session, char* buf, unsigned int buflen);

#ifdef __cplusplus
}
#endif


#endif //__ORAY_SLSDK_H__
