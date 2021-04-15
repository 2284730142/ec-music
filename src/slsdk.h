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
 * \brief SLAPI版本号
 */
#define SLAPI_VERSION 1

#ifdef _WIN64
typedef unsigned long long SLPOINTER;
#else
typedef unsigned long SLPOINTER;
#endif

/**
 * \brief 被控制端环境
 */
typedef SLPOINTER SLCLIENT;

/**
 * \brief 控制端环境
 */
typedef SLPOINTER SLREMOTE;

/**
 * \brief 会话
 */
typedef unsigned int SLSESSION;

/**
 * \brief 插件
 */
typedef SLPOINTER SLPLUGIN;

/**
 * \brief 公共的对象接口
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
 * \brief 无效被控制端环境
 */
#define SLCLIENT_INVAILD 0

/**
 * \brief 无效控制端环境
 */
#define SLREMOTE_INVAILD 0

/**
 * \brief 无效会话
 */
#define SLSESSION_INVAILD (-1)

/**
 * \brief 无效插件
 */
#define SLPLUGIN_INVAILD 0

/**
 * \brief 无效的实例对象
 */
#define SLOBJINTERFACE_INVAILD 0

/** \brief Error code
 *
 */
enum SLERRCODE {
  //成功
  SLERRCODE_SUCCESSED = 0, 

  //内部错误
  SLERRCODE_INNER = 1, 

  //未初始化
  SLERRCODE_UNINITIALIZED = 2, 

  //参数错误
  SLERRCODE_ARGS = 3,

  //不支持
  SLERRCODE_NOTSUPPORT = 4,

  //网络连接失败
  SLERRCODE_CONNECT_FAILED = 5, 

  //网络连接超时
  SLERRCODE_CONNECT_TIMEOUT = 6,

  //会话不存在
  SLERRCODE_SESSION_NOTEXIST = 7,

  //会话溢出
  SLERRCODE_SESSION_OVERFLOW = 8,

  //会话类型错误
  SLERRCODE_SESSION_WRONGTYPE = 9,

  //OPENID过期
  SLERRCODE_EXPIRED = 10,

  //请求频繁
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
	eSLVideoDefinition_SD = 1, 		/*!< Standard Definition 标清*/
	eSLVideoDefinition_HD = 2, 		/*!< High Definition 高清*/
	eSLVideoDefinition_UHD = 3,		/*!< Ultra High-Definition 超清*/
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
 * \brief 会话回调属性
 */
typedef struct tagSLSESSION_CALLBACK_PROP {
	SLSESSION_CALLBACK pfnCallback;	//!< 回调函数
	SLPOINTER nCustom;			//!< 自定义数据
} SLSESSION_CALLBACK_PROP;

/** \brief 会话类型
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

//此枚举用于隐藏远程桌面工具栏中的对应模块
enum SLDesktopControlType
{
	eSLDesktopControl_ALL,						//整个工具栏
	eSLDesktopControl_SWITCH_SCREEN,			//切换屏幕
	eSLDesktopControl_CHAT,						//聊天
	eSLDesktopControl_CAMERA,					//摄像头引导
	eSLDesktopControl_FILE,						//文件传输引导
	eSLDesktopControl_RECORD,					//录像
	eSLDesktopControl_SCREENSHOT,				//截屏
	eSLDesktopControl_WHITE_BORAD,				//白板
	eSLDesktopControl_MORE,						//更多
	eSLDesktopControl_FULL_SCREEN,				//全屏
	eSLDesktopControl_SCREEN_ORIGINAL_SIZE,		//屏幕原始尺寸
	eSLDesktopControl_DESKTOP_MODEL,			//桌面模式
	eSLDesktopControl_RESOLUTION,				//分辨率
	eSLDesktopControl_SWITCH_SESSION,			//切换会话
	eSLDesktopControl_SHORTCUT_KEY,				//快捷键
	eSLDesktopControl_BLACKSCREEN_MODE,			//黑屏模式
	eSLDesktopControl_FORBID_MOUSE_KEY,			//禁止对方输入
	eSLDesktopControl_SOUND,					//声音
	eSLDesktopControl_SHORTCUT_CTRL,			//快捷键Ctrl+Alt+Delete
	eSLDesktopControl_SHORTCUT_LOCK,			//快捷键锁定
	eSLDesktopControl_SHORTCUT_LOGOUT,			//快捷键注销
	eSLDesktopControl_SHORTCUT_RESTART,			//快捷键重启
	eSLDesktopControl_SHORTCUT_SHUTDOWN,		//快捷键关机
	eSLDesktopControl_SHORTCUT_EXPLORER,		//快捷键资源管理器
	eSLDesktopControl_SHORTCUT_TASKMGR,			//快捷键任务管理器
	eSLDesktopControl_SHORTCUT_CONSOLE,			//快捷键控制台
};

//此枚举用于获取屏幕和会话的个数以及切换功能
enum SLDesktopDevType
{
	eSLDesktopDev_SCREEN,					//屏幕
	eSLDesktopDev_SESSION,					//会话
	eSLDesktopDev_RESOLUTION,				//分辨率
};

//此枚举用于获取某个模块当前状态或索引
enum SLDesktopStateType
{
	eSLDesktopState_SCREEN_ORIGINAL_SIZE,	//原始屏幕比例
	eSLDesktopState_FULL_SCREEN,			//全屏
	eSLDesktopState_SOUND,					//声音
	eSLDesktopState_FORBID_MOUSE_KEY,		//禁止对方输入
	eSLDesktopState_WHITE_BORAD,			//白板
	eSLDesktopState_RESOLUTION,				//分辨率
	eSLDesktopState_BLACKSCREEN_MODE,		//黑屏模式
	eSLDesktopState_LOCAL_INPUT,			//本地输入
};

//此枚举用于设置远程桌面功模块的开启和关闭
enum SLDesktopCommandType
{
	eSLDesktopCommand_CTRL,					//快捷键Ctrl+Alt+Delete
	eSLDesktopCommand_LOCK,					//快捷键锁定
	eSLDesktopCommand_LOGOUT,				//快捷键注销
	eSLDesktopCommand_RESTART,				//快捷键重启
	eSLDesktopCommand_SHUTDOWN,				//快捷键关机
	eSLDesktopCommand_EXPLORER,				//快捷键资源管理器
	eSLDesktopCommand_TASKMGR,				//快捷键任务管理器
	eSLDesktopCommand_CONSOLE,				//快捷键控制台

	eSLDesktopCommand_WORK_MODEL,			//工作模式
	eSLDesktopCommand_ENTERTAINMENT_MODEL,	//娱乐模式
	eSLDesktopCommand_CHAT,					//发起聊天

	eSLDesktopCommand_SCREEN_ORIGINAL_SIZE,	//原始屏幕比例
	eSLDesktopCommand_FULL_SCREEN,			//进入或退出全屏
	eSLDesktopCommand_SOUND,				//开启或关闭声音
	eSLDesktopCommand_FORBID_MOUSE_KEY,		//禁止或允许对方输入
	eSLDesktopCommand_WHITE_BORAD,			//开启或关闭白板
	eSLDesktopCommand_BLACKSCREEN_MODE,		//开启或关闭黑屏模式
	eSLDesktopCommand_LOCAL_INPUT,			//开启或关闭本地输入法输入

	eSLDesktopCommand_SWITCH_SCREEN,		//切换屏幕
	eSLDesktopCommand_SWITCH_SESSION,		//切换会话
	eSLDesktopCommand_RESOLUTION,			//切换分辨率

	//only for android
	eSLDesktopCommand_PULL_DOWN_MENU,		//下拉菜单
	eSLDesktopCommand_VOLUME_INCREASE,		//音量+
	eSLDesktopCommand_VOLUME_DECREASE,		//音量-
	eSLDesktopCommand_HOME_KEY,				//home键
	eSLDesktopCommand_BACK_KEY,				//返回键
	eSLDesktopCommand_MENU_KEY,				//菜单键
	eSLDesktopCommand_LOCK_SCREEN,			//锁屏
	eSLDesktopCommand_SCROLL_UP,			//向上滚动
	eSLDesktopCommand_SCROLL_DOWM,			//向下滚动
};

//此枚举用于创建实例对象
enum SLObjInterfaceType
{
	eSLObjInterface_AVIConverter,
	eSLObjInterface_CloudMonitor,
	eSLObjInterface_WakeupClient,
};

//此枚举用于创建实例对象
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

//此枚举用于声音会话类型
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
* 代理类型
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

//摄像头信息结构
struct CAMERA_INFO
{
	unsigned int  uDeviceID;			//唯一标识
	char  szName[256];					//摄像头名称
};

//基础信息结构
struct SLBASE_INFO
{
	unsigned int  uIndex;				//唯一标识索引
	char  szName[256];					//基础信息
};

//启动实例结构
struct SLINSTANCE_INFO
{
	char  szMod[64];					//模块名称
	char  szName[64];					//名称信息
	unsigned int  uID;					//ID信息
	unsigned int  uPort;				//转发端口
};

//远程控控结构参数
struct SLKVM_INFO
{
	char  szSN[32];						//控控sn号
	char  szPassword[32];				//控控密码
	char  szIotServerAddr[64];			//控控连接的iot服务器地址
	unsigned int nIotPort;				//控控连接的iot服务器端口
	unsigned int nLoginType;			//控控登录p2p服务器的方式，0-开发者ID登录 1-独立服务器登录
	char  szLoginAddr[128];				//开发者ID或者独立服务器登录地址
	char  szLoginKey[128];				//开发者Key或者独立服务器登录Session
	unsigned int nTimeout;				//控控创建的会话失效时间，需要在有效时间内连接控控
};

/** \brief Initialize SLSDK's enviroment
 *
 * \return 是否初始化成功
 */
bool SLAPI SLInitialize();

/*
 * \brief 退出SLAPI环境
 * \desc 建议在整个进程退出前调用，以释放SLAPI环境所使用的资源
 * \return 是否退出成功
 */
bool SLAPI SLUninitialize();

/*
 * \brief 获取最后的错误码
 * \return 返回SLERRCODE错误码
 */
SLERRCODE SLAPI SLGetLastError();

/*
 * \brief 设置最后的错误码
 * \param errCode 错误码
 * \return 是否设置成功
 */
bool SLAPI SLSetLastError(SLERRCODE errCode);

/*
 * \brief 获取错误码详细说明
 * \return 详细信息，如果错误码不存在则返回“未知错误”
 */
const char* SLAPI SLGetErrorDesc(SLERRCODE errCode);

/*
 * \brief 设置全局的配置信息<此API仅供内部使用>
 * \param pstrConfig Json格式的配置信息，详细请见文档
 * \param nLen 配置信息的长度
 * \return 是否设置成功
 */
bool SLAPI SLSetGlobalConfig(const char* pstrConfig, unsigned int nLen);

/*
 * \brief 设置全局的语言环境
 * \param eType 语言类型
 */
void SLAPI SLSetLanguage(SLLanguageType eType);


/** \brief 被控制端事件
 *
 */
enum SLCLIENT_EVENT
{
	SLCLIENT_EVENT_ONCONNECT = 0,	//!< 连接成功
	SLCLIENT_EVENT_ONDISCONNECT,	//!< 断开连接
	SLCLIENT_EVENT_ONLOGIN,			//!< 登录成功
	SLCLIENT_EVENT_ONLOGINFAIL,		//!< 登录失败
	SLCLIENT_EVENT_ONCHANNELSFULL,	//!< 通道数已满
	SLCLIENT_EVENT_ONCHECKCFAIL,	//!< 检查通道数失败
};

/** \brief 被控端绑定开机设备事件
*
*/
enum SLCLIENT_WOI_EVENT
{
	SLCLIENT_WOI_EVENT_ONDISCOVER = 0,	//发现开机设备
	SLCLIENT_WOI_EVENT_ONBIND,			//绑定开机设备
	SLCLIENT_WOI_EVENT_ONUNBIND,		//解绑开机设备
};

/** \brief 被控端UU事件
*
*/
enum SLCLIENT_UU_EVENT
{
	SLCLIENT_UU_EVENT_ONUPGRADESTEP = 0,	//UU升级步骤
	SLCLIENT_UU_EVENT_ONSENDMOUSE,			//UU发送鼠标消息
	SLCLIENT_UU_EVENT_ONSENDKEYBOARD,		//UU发送键盘消息
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
 * \brief 销毁一个被控制端环境
 * \param client 要销毁的被控制端环境
 */
bool SLAPI SLDestroyClient( SLCLIENT client );

/*
 * \brief 被控制端回调事件
 * \param client 被控制端环境
 * \param event 事件
 * \param custom 用户自定义参数
 */
typedef void (SLAPI *SLCLIENT_CALLBACK)(SLCLIENT client, SLCLIENT_EVENT event, SLPOINTER custom);

/*
 * \brief 设置被控制端事件回调函数
 * \param client 被控制端环境
 * \param pfnCallback 回调函数地址
 * \param custom 用户自定义参数，回调时内部程序会将此参数一并回调
 * \return 是否设置成功
 */
bool SLAPI SLSetClientCallback(SLCLIENT client, SLCLIENT_CALLBACK pfnCallback, SLPOINTER custom);

/*
 * \brief 被控制端登录服务器
 * \param client 被控制端环境
 * \param pstrOpenID 开发者的ID号
 * \param pstrOpenKey 开发者ID对应的验证码
 * \return 是否登录成功
 */
bool SLAPI SLClientLoginWithOpenID(SLCLIENT client, const char* pstrOpenID, const char* pstrOpenKey, const char* pstrDomain = "", bool bUseSSL = false);
  
/** \brief Short name for SLClientLoginWithOpenID
 *
 */
bool SLAPI SLLoginWithOpenID(SLCLIENT client, const char* pstrOpenID, const char* pstrOpenKey, const char* pstrDomain = "", bool bUseSSL = false);

  
/*
 * \brief 被控制端登录服务器
 * \param client 被控制端环境
 * \param szAddr 服务器地址
 * \param szLic lincense
 * \return 是否登录成功
 */
bool SLAPI SLClientLoginWithLicense(SLCLIENT client, const char* szAddr, const char* szLic);

/*
 * \brief 被控制端注销登录服务器
 * \param client 被控制端环境
 * \return 是否注销登录成功
 */
bool SLAPI SLClientLogout(SLCLIENT client);

/*
 * \brief 被控制端是否登录中
 * \param client 被控制端环境
 */
bool SLAPI SLClientIsOnLoginned(SLCLIENT client);

/*
 * \brief 在被控制端环境中创建一个会话
 * \param client 被控制端环境
 * \return 会话值，如果创建失败，则返回SLSESSION_INVAILD
 */
SLSESSION SLAPI SLCreateClientSession(SLCLIENT client, ESLSessionType eType);

/*
 * \brief 销毁一个会话
 * \param client 被控制端环境
 * \param session 会话
 * \return 是否销毁成功
 */
bool SLAPI SLDestroyClientSession(SLCLIENT client, SLSESSION session);

/*
* \brief 打开被控端日志
* \param client 被控制端环境
* \param path 路径
* \return 是否设置成功
*/
bool SLAPI SLOpenClientLog(SLCLIENT client, const char* path, const char* name = 0);

/*
* \brief 设置代理
* \param client 被控制端环境
* \param proxy 代理设置
* \return 是否设置成功
*/
bool SLAPI SLSetClientProxy(SLCLIENT client, const SLPROXY_INFO& proxy);

/*
* \brief 测试代理
* \param client 被控制端环境
* \param proxy 代理设置
* \return 测试代理是否连接成功
*/
bool SLAPI SLTestClientPorxy(SLCLIENT client, const SLPROXY_INFO& proxy);

/*
 * \brief 枚举被控端当前有多少个会话
 * \param client 被控制端环境
 * \param pSessionArray 会话数组（输出参数）
 * \param nArraySize 数组长度
 * \return 一个有多少个会话
 */
unsigned int SLAPI SLEnumClientSession(SLCLIENT client, SLSESSION* pSessionArray, unsigned int nArraySize);

/*
 * \brief 获取被控制端连接地址
 * \remark 必须在登录成功后再获取才能获取正确的值，即当回调事件SLCLIENT_EVENT_ONLOGIN发生后调用。通过该值主控制端才能使用该会话的服务
 * \return 地址
 */
const char* SLAPI SLGetClientAddress(SLCLIENT client);

/*
 * \brief 获取被控制端某个会话的值
 * \remark 通过该值主控制端才能使用该会话的服务
 * \return 会话值，如果会话不存在则返回NULL
 */
const char* SLAPI SLGetClientSessionName(SLCLIENT client, SLSESSION session);

/*
 * \brief 获得被控制端会话插件对象
 * \param client 被控制端环境
 * \param session 会话
 * \return 插件对象，如果获取失败，则返回SLPLUGIN_INVAILD
 */
SLPLUGIN SLAPI SLGetClientSessionPlugin(SLCLIENT client, SLSESSION session);

/*
* \brief 获得被控制端会话的连接信息
* \param remote 被控制端环境
* \param session 会话
* \param connectType 连接类型
* \param localType 是否是在同一局域网（公网IP相同） 0:公网IP不一致 1:公网IP一致
* \return 是否获得成功
*/
bool SLAPI SLGetClientSessionConnection(SLCLIENT client, SLSESSION session, unsigned long& connectType, unsigned long& localType);

/*
 * \brief 被控制端某个会话发送数据
 * \param client 被控制端环境
 * \param session 会话
 * \param lpData 发送的数据
 * \param nLen 发送的数据长度
 * \return 发送的字节数
 * \remark 目前只适用于DataTrans类型的会话
 */
unsigned long SLAPI SLClientSessionSendData(SLCLIENT client, SLSESSION session, const char* lpData, unsigned long nLen);

/*
 * \brief 被控制端某个会话接收数据
 * \param client 被控制端环境
 * \param session 会话
 * \param lpData 接收数据的缓冲区
 * \param nLen 准备接收的数据长度
 * \return 实际接收到的字节数
 * \remark 目前只适用于DataTrans类型的会话
 */
unsigned long SLAPI SLClientSessionRecvData(SLCLIENT client, SLSESSION session, char* lpData, unsigned long nLen);

/*
 * \brief 获取被控制端某个会话某个属性值
 * \return 是否获取成功
 */
bool SLAPI SLGetClientSessionOpt(SLCLIENT client, SLSESSION session, ESLSessionOpt eOpt, char* pOptVal, unsigned int nOptLen);

/*
 * \brief 设置被控制端某个会话某个属性值
 * \return 是否设置成功
 */
bool SLAPI SLSetClientSessionOpt(SLCLIENT client, SLSESSION session, ESLSessionOpt eOpt, const char* pOptVal, unsigned int nOptLen);

/*
 * \brief 开启WEB服务
 * \return 是否成功
 */
bool SLAPI SLStartWebServer(SLCLIENT client, unsigned int nPort=0, bool bUseSSL = false, const char* pCert = "", const char* pPrivateKey = "");

/*
 * \brief 关闭WEB服务
 * \return 是否成功
 */
bool SLAPI SLStopWebServer(SLCLIENT client);

/*
 * \brief web服务过滤方法，返回true表示已经处理了当前事件，底层将不会再处理
 * \param client 被控制端环境
 * \param data 指向数据的指针
 * \param size 数据长度
 */
typedef bool (SLAPI *SLWEB_FILTER)(SLCLIENT client,const void* data,unsigned int size);

/*
 * \brief 设置web服务过滤方法
 * \param client 被控制端环境
 * \param filter 函数指针
 */
bool SLAPI SlSetWebServerFilter(SLCLIENT client,SLWEB_FILTER filter);

/*
 * \brief 向web客户端发送数据
 * \param client 被控制端环境
 * \param data 指向数据的指针
 * \param size 数据长度
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
* \brief 远程桌面中主动发起聊天
* \param client 被控制端环境
* \param session 桌面会话
*/
bool SLAPI SLClientStartChat(SLCLIENT client, SLSESSION session, bool bShow = true);

/*
* \brief 远程桌面中主动发起聊天
* \param client 被控制端环境
* \param session 桌面会话
* \param bEnable 切换控制/观看模式
*/
bool SLAPI SLClientEnableControl(SLCLIENT client, SLSESSION session, bool bEnable);

/*
 * \brief 服务模式中的桌面代理发送消息<此API仅供内部使用>
 * \param client 被控制端环境
 * \param session 桌面会话
 * \param cmd 消息类型
 * \param buf 消息数据
 * \param size 消息大小
 */
bool SLAPI SLClientSendDesktopAgentMsg(SLCLIENT client, SLSESSION session, SLUINT32 cmd, const void* buf, SLUINT32 size);

/*
 * \brief 界面模式中启动桌面代理实例<此API仅供内部使用>
 * \param client 被控制端环境
 * \param nPort 绑定服务端口
 * \param nID 代理ID
 */
bool SLAPI SLClientRunDesktopAgent(SLCLIENT client, int nPort, int nID);

/*
 * \brief 远程桌面时启动拖曳服务<此API仅供内部使用>
 * \param client 被控制端环境
 */
bool SLAPI SLClientRunDragServer(SLCLIENT client);

/*
 * \brief 创建一个对象实例<此API仅供内部使用>
 */
SLOBJINTERFACE SLAPI SLCreateObjInterface(SLObjInterfaceType eType);

/*
 * \brief 销毁一个AVI数据转化器<此API仅供内部使用>
 * \param interface 由SLCreateInterface创建出来的实例对象
 */
bool SLAPI SLDestroyObjInterface(SLOBJINTERFACE inter);

/*
 * \brief 根据查询信息获得具体的系统信息
 * \param client 被控制端环境
 * \param session 系统会话
 * \param pstrQuery 查询参数
 * \param pstrContent 查询内容
 * \return 具体的系统信息
 */
const char* SLAPI SLGetClientSysinfo(SLCLIENT client, SLSESSION session, const char* pstrQuery, const char* pstrContent);

bool SLAPI SLAddPrintServerPort(const char* pstrServerName);
bool SLAPI SLDeletePrintServerPort(const char* pstrServerName);

/************************************************************************/
/* 控制端相关API                                                        */
/************************************************************************/
/**
 * \brief 主控制端事件
 */
enum SLREMOTE_EVENT
{
  SLREMOTE_EVENT_ONCONNECT = 0, 		//!< 连接成功
  SLREMOTE_EVENT_ONDISCONNECT, 			//!< 断开连接
  SLREMOTE_EVENT_ONDISCONNECT_FOR_FULL, //!< 断开连接(因为连接数满了)  
};

/*
 * \brief 创建一个控制端环境
 * \return 返回被控制端环境值，如果创建失败则返回SLREMOTE_INVAILD
 */
SLREMOTE SLAPI SLCreateRemote(void);

/*
 * \brief 销毁一个控制端环境
 * \param remote 控制端环境
 * \return 是否销毁成功
 */
bool SLAPI SLDestroyRemote(SLREMOTE remote);

/*
* \brief 打开控制端日志
* \param remote 控制端环境
* \param path 路径
* \return 是否设置成功
*/
bool SLAPI SLOpenRemoteLog(SLREMOTE remote, const char* path, const char* name = 0);

/*
* \brief 设置代理
* \param client 被控制端环境
* \param remote 控制端环境
* \return 是否设置成功
*/
bool SLAPI SLSetRemoteProxy(SLREMOTE remote, const SLPROXY_INFO& proxy);

/*
* \brief 测试代理
* \param Remote 控制端环境
* \param proxy 代理设置
* \return 测试代理是否连接成功
*/
bool SLAPI SLTestRemotePorxy(SLCLIENT remote, const SLPROXY_INFO& proxy);

/*
 * \brief 主控制端回调事件
 * \param remote 主控制端环境
 * \param event 事件
 * \param custom 用户自定义参数
 */
typedef void (SLAPI *SLREMOTE_CALLBACK)(SLREMOTE remote, SLSESSION session, SLREMOTE_EVENT event, SLPOINTER custom);

/*
 * \brief 设置主控制端事件回调函数
 * \param remote 主控制端环境
 * \param pfnCallback 回调函数地址
 * \param custom 用户自定义参数，回调时内部程序会将此参数一并回调
 * \return 是否设置成功
 */
bool SLAPI SLSetRemoteCallback(SLREMOTE remote, SLREMOTE_CALLBACK pfnCallback, SLPOINTER custom);

/*
 * \brief 创建主控制端会话
 * \param remote 控制端环境
 * \param eType 会话类型
 * \param pstrAddress 远程被控制端地址
 * \param pstrSession 远程桌面会话名
 * \return 会话
 */
SLSESSION SLAPI SLCreateRemoteSession(SLREMOTE remote, ESLSessionType eType, const char* pstrAddress, const char* pstrSession);

/*
 * \brief 创建主控制端空会话(无连接)
 * \param remote 控制端环境
 * \param eType 会话类型
 * \remark 和SLCreateRemoteSession不同的是创建一个空会话，不进行连接，后面必须再使用SLConnectRemoteSession来连接会话
 * \return 会话
 */
SLSESSION SLAPI SLCreateRemoteEmptySession(SLREMOTE remote, ESLSessionType eType);

/*
 * \brief 连接主控端会话
 * \param remote 控制端环境
 * \param session 会话
 * \param pstrAddress 远程被控制端地址
 * \param pstrSession 远程桌面会话名
 * \return 会话
 */
bool SLAPI SLConnectRemoteSession(SLREMOTE remote, SLSESSION session, const char* pstrAddress, const char* pstrSession);

/*
 * \brief 连接主控端会话--被控对象是控控
 * \param remote 控制端环境
 * \param session 会话
 * \param kvm_info 被控控控配置信息
 * \return 是否连接成功
 */
bool SLAPI SLConnectKVMRemoteSession(SLREMOTE remote, SLSESSION session, const SLKVM_INFO& kvm_info);

/*
 * \brief 销毁一个会话
 * \param remote 控制端环境
 * \param session 会话
 * \return 是否销毁成功
 */
bool SLAPI SLDestroyRemoteSession(SLREMOTE remote, SLSESSION session);

/*
 * \brief 获得主控制端会话插件对象
 * \param remote 主控制端环境
 * \param session 会话
 * \return 插件对象，如果获取失败，则返回SLPLUGIN_INVAILD
 */
SLPLUGIN SLAPI SLGetRemoteSessionPlugin(SLREMOTE remote, SLSESSION session);

/*
 * \brief 获得主控制端会话的连接信息
 * \param remote 主控制端环境
 * \param session 会话
 * \param connectType 连接类型
 * \param localType 是否是在同一局域网（公网IP相同） 0:公网IP不一致 1:公网IP一致
 * \return 是否获得成功
 */
bool SLAPI SLGetRemoteSessionConnection(SLREMOTE remote, SLSESSION session, unsigned long& connectType, unsigned long& localType);

/*
 * \brief 主控制端某个会话发送数据
 * \param remote 主控制端环境
 * \param session 会话
 * \param lpData 发送的数据
 * \param nLen 发送的数据长度
 * \return 发送的字节数
 * \remark 目前只适用于DataTrans类型的会话
 */
unsigned long SLAPI SLRemoteSessionSendData(SLREMOTE remote, SLSESSION session, const char* lpData, unsigned long nLen);

/*
 * \brief 主控制端某个会话接收数据
 * \param remote 主控制端环境
 * \param session 会话
 * \param lpData 接收数据的缓冲区
 * \param nLen 接收数据缓冲区长度
 * \return 实际接收到的字节数
 * \remark 目前只适用于DataTrans类型的会话
 */
unsigned long SLAPI SLRemoteSessionRecvData(SLREMOTE remote, SLSESSION session, char* lpData, unsigned long nLen);

/*
 * \brief 获取主控制端某个会话某个属性值
 * \return 是否设置成功
 */
bool SLAPI SLGetRemoteSessionOpt(SLREMOTE remote, SLSESSION session, ESLSessionOpt eOpt, char* pOptVal, unsigned int nOptLen);

/*
 * \brief 设置主控制端某个会话某个属性值
 * \return 是否设置成功
 */
bool SLAPI SLSetRemoteSessionOpt(SLREMOTE remote, SLSESSION session, ESLSessionOpt eOpt, const char* pOptVal, unsigned int nOptLen);

/*
* \brief 获取远程会话的帧数
* \return 帧数
*/
unsigned long SLAPI SLGetRemoteDesktopFrameCount(SLREMOTE remote, SLSESSION session);
/*
 * \brief 设置远程桌面窗口的大小
 * \return 是否设置成功
 */
bool SLAPI SLSetDesktopSessionPos(SLREMOTE remote, SLSESSION session, int x,int y,int width,int height);

/*
 * \brief Show desktop window
 * \return 是否设置成功
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
* \brief 设置远程CMD窗口的大小
* \return 是否设置成功
*/
bool SLAPI SLSetCmdSessionPos(SLREMOTE remote, SLSESSION session, int x, int y, int width, int height);

/*
* \brief 设置远程摄像头窗口的大小
* \return 是否设置成功
*/
bool SLAPI SLSetCameraSessionPos(SLREMOTE remote, SLSESSION session, int x, int y, int width, int height);

/*
* \brief 打开远程摄像头
* \return 是否打开成功
*/
bool SLAPI SLRemoteCameraOpen(SLREMOTE remote, SLSESSION session, unsigned long dev_id);

/*
* \brief 关闭远程摄像头
* \return 是否关闭成功
*/
bool SLAPI SLRemoteCameraClose(SLREMOTE remote, SLSESSION session);

/*
* \brief 设置远程摄像头清晰度
* \return 是否设置成功
*/
bool SLAPI SLRemoteCameraSetDefinition(SLREMOTE remote, SLSESSION session, ESLVideoDefinition eVD);

/*
* \brief 获取摄像头列表
* \param infos 摄像头结构体数组，若为空，则此函数仅返回列表大小
* \param nSize 数组大小
* \return 返回列表大小
*/
unsigned int SLAPI SLRemoteCameraGetList(SLREMOTE remote, SLSESSION session, CAMERA_INFO* infos = 0, unsigned int nSize = 0);

/*
* \brief 设置远程开机服务器地址与控制端口
* \return 是否设置成功
*/
bool SLSetRemoteWOIControl(SLREMOTE remote, const char* pstrAddress, unsigned int nPort);

/*
* \brief 发送远程开机指令
* \return 是否发送成功
*/
bool SLAPI SLSendWakeupCommand(SLREMOTE remote, const char* pstrMac, const char* pstrPassword);

/*
* \brief 远程唤醒回调事件
* \param remote 主控制端环境
* \param code http响应code
* \param pstrResponse http响应具体内容
* \param custom 用户自定义参数
*/
typedef void (SLAPI *SLREMOTE_WOI_CALLBACK)(SLREMOTE remote, int code, const char* pstrResponse, SLPOINTER custom);

/*
* \brief 设置主控制端远程唤醒事件回调函数
* \param remote 主控制端环境
* \param pfnCallback 回调函数地址
* \param custom 用户自定义参数，回调时内部程序会将此参数一并回调
* \return 是否设置成功
*/
bool SLAPI SLSetRemoteWOICallback(SLREMOTE remote, SLREMOTE_WOI_CALLBACK pfnCallback, SLPOINTER custom);

/*
* \brief 检查远程客户端的系统信息
* \param remote 主控制端环境
* \param session 对应的session
* \param pstrQuery 查询参数
* \param pstrContent 查询内容
* \return 此次操作的ID
*/
unsigned int SLAPI SLGetRemoteSysinfo(SLREMOTE remote, SLSESSION session, const char* pstrQuery, const char* pstrContent);

/*
* \brief 检查远程客户端的系统信息
* \param remote 主控制端环境
* \param session 对应的session
* \param pstrQuery 查询参数
* \param pstrContent 查询内容
* \return 此次操作的ID
*/
unsigned int SLAPI SLGetScreenshot(SLREMOTE remote, SLSESSION session, int width, int height);

/*
* \brief 设置远程桌面工具栏是否可见
* \param remote 主控制端环境
* \param session 对应的session
* \param eType 枚举隐藏的对象
* \return 是否设置成功
*/
bool SLAPI SLHideRemoteDesktopToolbarItem(SLREMOTE remote, SLSESSION session, SLDesktopControlType eType);

/*
* \brief 获取远程桌面屏幕,会话,分辨率的列表信息
* \param remote 主控制端环境
* \param session 对应的session
* \param infos 基础信息结构，若为空，则此函数仅返回列表大小
* \param nSize 数组大小
* \return 返回列表大小
*/
unsigned int SLAPI SLGetRemoteDesktopDevList(SLREMOTE remote, SLSESSION session, SLDesktopDevType eType, SLBASE_INFO* infos = 0, unsigned int nSize = 0);

/*
* \brief 发送远程桌面控制命令
* \param remote 主控制端环境
* \param session 对应的session
* \param eType 对应的操作命令
* \param nIndex 索引值,只针对于切换屏幕，切换会话，切换分辨率等选择性的命令有效
* \return 是否成功
*/
bool SLAPI SLSendRemoteDesktopCommand(SLREMOTE remote, SLSESSION session, SLDesktopCommandType eType, unsigned int nIndex = 0);

/*
* \brief 获得远程桌面当前状态
* \param remote 主控制端环境
* \param session 对应的session
* \param eType 对应的操作命令
* \param nState 状态值或当前选中索引值
* \return 是否成功
*/
bool SLAPI SLGetRemoteDesktopCurState(SLREMOTE remote, SLSESSION session, SLDesktopStateType eType, unsigned int& nState);

/*
* \brief 截屏
* \param remote 主控制端环境
* \param session 对应的session
* \param filepath 保存文件全路径
* \return 是否成功
*/
bool SLAPI SLRemoteDesktopScreenShot(SLREMOTE remote, SLSESSION session, const char* filepath);

/*
* \brief 截屏
* \param remote 主控制端环境
* \param session 对应的session
* \param filepath 被控端对应的操作平台
* \return 是否成功
*/
bool SLAPI SLSetRemoteDesktopPlatform(SLREMOTE remote, SLSESSION session, SLPlatformType eType);

/*
* \brief 发送远程桌面控制命令
* \param remote 主控制端环境
* \param session 对应的session
* \param key 对应的键盘字符串
* \param isDown 是否是键盘按下
* \return 是否成功
*/
bool SLAPI SLSendRemoteDesktopKeyUpDown(SLREMOTE remote, SLSESSION session, const char* key, bool isDown);

/*
* \brief 将远程桌面和远程声音绑定或者解绑
* \param remote 主控制端环境
* \param session 对应的桌面session
* \param soundSession 对应的声音session
* \return 是否成功
*/
bool SLAPI SLRemoteDesktopBindSound(SLREMOTE remote, SLSESSION session, SLSESSION soundSession);

/*
* \brief 设置远程SSH窗口的大小
* \return 是否设置成功
*/
bool SLAPI SLSetSshSessionPos(SLREMOTE remote, SLSESSION session, int x, int y, int width, int height);

/*
* \brief 设置远程远程文件管理窗口的大小
* \return 是否设置成功
*/
bool SLAPI SLSetFileMgrSessionPos(SLREMOTE remote, SLSESSION session, int x, int y, int width, int height);

/*
* \brief 设置远程桌面水印图片
* \param remote 主控制端环境
* \param session 对应的桌面session
* \param x 水印坐标偏移量(大于0表示左边距，小于0表示右边距)
* \param y 水印坐标偏移量(大于0表示上边距，小于0表示下边距)
* \param width 水印图像宽度
* \param height 水印图像高度
* \param alpha 透明度(0-255)
* \param buf 水印图像缓存(ARGB)
* \param buflen 水印图像缓存长度
* \return 是否成功
*/
bool SLAPI SLSetRemoteDesktopWatermark(SLREMOTE remote, SLSESSION session, int x, int y, int width, int height, int alpha, const char* buf, unsigned long buflen);

/*
* \brief 获取远程桌面图像位图缓冲区及缓冲区大小
* \param remote 主控制端环境
* \param session 对应的桌面session
* \param buf 桌面位图缓冲区，若为空，此函数返回缓冲区大小
* \param buflen 桌面位图缓冲区大小
* \return 缓冲区大小
*/
unsigned int SLAPI SLGetRemoteDesktopBuffer(SLREMOTE remote, SLSESSION session, char* buf, unsigned int buflen);

#ifdef __cplusplus
}
#endif


#endif //__ORAY_SLSDK_H__
