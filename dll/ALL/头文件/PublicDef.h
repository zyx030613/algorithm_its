
#ifndef PUBLICDEF_H
#define PUBLICDEF_H

#include "GlobalTypes.h"

#if (!defined(_WIN32) && !defined(_WIN64))
#include "util_type.h"
#ifndef __cdecl
#define __cdecl		/**<  */
#endif
#ifndef __stdcall
#define __stdcall	/**<  */
#endif
#endif

/*********************************************************************************************/
#define CALLING_CONVENTION			__cdecl
#define MAX_PLAYER_NUM				128/*64*/
#define MAX_SYC_GROUP_NUM			4				//同步回放最大组个数
#define MAX_SYC_PLAYER_NUM			16				//同步回放最大player个数
#define MSG_PLAYSDKM4				(WM_USER+0x01FF)//回放器库消息的默认值
/*********************************************************************************************/


/**********************************************************************************************
* 功能宏定义                                                                 
**********************************************************************************************/
#define	SAFE_CLOSE_THREAD(x) if (NULL != (x))	{WaitForSingleObject((x),INFINITE); CloseHandle((x)); (x) = NULL;}
#define	SAFE_CLOSE_HANDLE(x) if (NULL != (x))	{CloseHandle((x)); (x) = NULL;}
#define SAFE_DELETE(x)	if ((x) != NULL)	{delete (x); (x) = NULL;}
#define SAFE_FREE(x)	if ((x) != NULL)	{free((x)); (x) = NULL;}
#define SAFE_DELETE_ARRAY(x)	if ((x) != NULL)	{delete [] (x); (x) = NULL;}
#define SAFE_CLOSE_FILE(x) if ((x) != NULL)	{fclose((x)); (x) = NULL;}
/*********************************************************************************************/



/**********************************************************************************************
* Number of Show Video                                                                   
**********************************************************************************************/
#define	MAX_DRAW_NUM				8
/*********************************************************************************************/


/**********************************************************************************************
* SDK Return Value                                                                   
**********************************************************************************************/
#define TD_OK						0
#define TD_APPLYMEMORY_FAILED		-5
/*********************************************************************************************/


/**********************************************************************************************
* 回放器库消息的LPARAM参数取值列表                                                                     
**********************************************************************************************/
#define LPARAM_FILE_PLAY_END		0		//播放完毕
#define LPARAM_FILE_SEARCH_END		1		//寻找到文件末尾
#define LPARAM_NEED_DECRYPT_KEY		2		//需要解密密码
#define LPARAM_DECRYPT_KEY_FAILED	3		//解密密码错误
#define LPARAM_DECRYPT_SUCCESS		4		//解密成功
#define LPARAM_STREAM_SEARCH_END	5		//流缓冲区中没有数据了
#define LPARAM_VOD_STREAM_END		6		//VOD文件流播放完毕
/*********************************************************************************************/

/**********************************************************************************************
* return value for encrypt frame                                                                      
**********************************************************************************************/
#define ENCRYPT_SUCCESS				0		// encrypt sucess
#define ENCRYPT_INVALID_PARAM		(-1)	// error param
#define ENCRYPT_KEY_NOT_READY		(-2)	// invalid key
#define ENCRYPT_FAILED				(-3)	// encrypt failed
/*********************************************************************************************/

/**********************************************************************************************
* Decrypt frame return value                                                                     
**********************************************************************************************/
#define DECRYPT_SUCCESS				0		//解密成功
#define DECRYPT_INVALID_PARAM		(-1)	//参数错误
#define DECRYPT_KEY_NOT_READY		(-2)	//没有设定解密密钥
#define DECRYPT_FRAME_NOT_ENCRYPT	(-3)	//帧不是加密帧
#define DECRYPT_FAILED				(-4)	//帧解密失败
/*********************************************************************************************/


/**********************************************************************************************
* Record File                                                                       
**********************************************************************************************/
#define REC_FILE_TYPE_NORMAL		0
#define REC_FILE_TYPE_AVI			1
#define REC_FILE_TYPE_ASF			2
#define REC_FILE_TYPE_AUDIO			3
#define REC_FILE_TYPE_WAV			4
#define REC_FILE_TYPE_MP3			5
/*********************************************************************************************/


/**********************************************************************************************
* Player Control Code Used By TC_PlayerControl                                                             
**********************************************************************************************/
#define CTRL_VOD_SETOVERFLAG			0		//set vod play end flag
#define CTRL_VOD_CLEANBUFF				1		//clean vod buffer
#define CTRL_RESETDECODE				2		//resetdecode clean yuv
#define CTRL_RESVERSE_PLAY				3		//reverse play
#define CTRL_REGIST_USERDATA_NOTIFY		4		//regist usrdata notify
#define CTRL_REGIST_DRAW_NOTIFY			5		//regist draw notify
#define CTRL_REGIST_RAW_FRAME_NOTIFY	6		//regist rwa frame notify
#define CTRL_SEEK_BY_ABSTIME			7		//seek play by abs time
#define CTRL_SEEK_BY_RELATIVETIME		8		//seek play by Relative time
#define CTRL_REGIST_DRAW_YUV_NOTIFY		9		//regist draw yuv data notify
#define CTRL_GET_CUDA_INFO				10		//get cuda context
#define CTRL_DRAW_FACE_PARAM			11		//draw face ident rect
/*********************************************************************************************/

//CTRL_REGIST_USERDATA_NOTIFY
typedef struct tagUserDataNotify
{
	int iSize;
	DEVUSERDATA_NOTIFY pNotifyFun;
	void* pvUdata;
}UserDataNotify;


typedef struct tagDrawParam
{
	HDC hDrawDc;
	unsigned int iTimeStamp;
	int iDcWidth;
	int iDcHeight;
	RECT rcShow;
}DrawParam;
typedef void (*DRAW_NOTIFY_V4)(unsigned int _ulID, DrawParam* _ptDrawParam,  void* _iUser);

//CTRL_REGIST_DRAW_NOTIFY
typedef struct tagDrawNotify
{
	int iSize;
	DRAW_NOTIFY_V4 pNotifyFun;
	void* pvUdata;
}DrawNotify;

typedef struct tagYuvDataInfo
{
	unsigned char* pucYuvBuf;
	int iYuvBufLen;
	int iWidth;
	int iHeight;
	unsigned int uiTime;
} YuvDataInfo;

typedef void (*DRAW_YUV_CallBack)(long _lPlayerHandle, YuvDataInfo* _ptYuv, int _iSize, void* _pvUdata);
typedef struct tagDrawYuvNotify
{
	int iSize;
	DRAW_YUV_CallBack pYuvCallBack;
	void* pvUdata;
} DrawYuvNotify;

typedef struct tagCudaInfo
{
	int iSize;
	int iGpuId;
	void* pvCudaCtx;
} CudaInfo;

typedef struct tagDrawFaceInfo
{
	int iSize;
	int	iType;
	int iEnable;
} DrawFaceInfo;

/**********************************************************************************************
* Draw Face                                                                      
**********************************************************************************************/
#define DRAW_FACE_TYPE_RECT			0
#define DRAW_FACE_TYPE_TEXT			1
#define DRAW_FACE_TYPE_MAX			2
/*********************************************************************************************/


/**********************************************************************************************
* Audio type                                                                      
**********************************************************************************************/
#define T_AUDIO8					0
#define T_YUV420					1
#define T_YUV422					2
/*********************************************************************************************/


/**********************************************************************************************
* Play Mode                                                                      
**********************************************************************************************/
#define	PLAYMODE_FILE				0		//文件播放模式
#define	PLAYMODE_VOD_FILE			1		//VOD播放模式
#define	PLAYMODE_STREAM				2		//流播放模式
/*********************************************************************************************/


/**********************************************************************************************
* Sleep Time                                                                     
**********************************************************************************************/
#define	SLEEP_1						1		//1毫秒
#define	SLEEP_100					100		//100毫秒
/*********************************************************************************************/


/**********************************************************************************************
* 返回值错误码含义                                                                        
**********************************************************************************************/
#define RET_INVALID_PLAYERID		-1		//非法PLAYER ID
#define RET_ERR_PLAYMODE			-2		//错误的播放模式
#define RET_INVALID_PARAM			-3		//非法参数
/*********************************************************************************************/


/**********************************************************************************************
* 刷新功能控制码                                                                        
**********************************************************************************************/
#define CTRL_REFRESHPLAYER			0		//初始化PLAYER窗口为黑色背景

#define PLAY_SPEED_VALUE_1			1		//2倍速速度值
#define PLAY_SPEED_VALUE_2			2		//4倍速速度值
#define PLAY_SPEED_VALUE_3			3		//8倍速速度值
#define PLAY_SPEED_VALUE_4			4		//16倍速速度值

#define PLAY_SPEED_2X_RATE			2		//2倍速速率
#define PLAY_SPEED_4X_RATE			4		//4倍速速率
#define PLAY_SPEED_8X_RATE			8		//8倍速速率
#define PLAY_SPEED_16X_RATE			16		//16倍速速率
/*********************************************************************************************/


/**********************************************************************************************
* Mode Rule                                                                    
**********************************************************************************************/
#define MODERULE_AUTO_ADJUST_DRAW_NO				(0x00)	//自适应不同分辨率数据--否
#define MODERULE_AUTO_ADJUST_DRAW_YES				(0x01)	//自适应不同分辨率数据--是
#define MODERULE_AUTO_ADJUST_STREAM_PLAY_SPEED_YES	(0x11)	//自适应调整流模式的播放速率--是
#define MODERULE_AUTO_ADJUST_STREAM_PLAY_SPEED_NO	(0x10)	//自适应调整流模式的播放速率--否
#define MODERULE_STREAM_ADAPTIVE					(0x24)	//设置为自适应模式
#define MODERULE_STREAM_PLAY_BALANCE				(0x23)	//设置为均衡模式
#define MODERULE_STREAM_PLAY_NO_DELAY				(0x22)	//设置为无延时模式
#define MODERULE_STREAM_PLAY_HIGH_SMOOTH			(0x21)	//设置为高流畅模式
#define MODERULE_STREAM_PLAY_LOW_DELAY				(0x20)	//设置为低延时模式
#define MODERULE_AVIDEO								(0x30)	//设置为音视频
#define MODERULE_PURE_AUDIO							(0x31)	//设置为纯音频模式
#define MODERULE_FAST_FORWARD_SKIP_I				(0x40)	//设置为快进跳I帧
#define MODERULE_FAST_FORWARD_NO_SKIP_I				(0x41)	//设置为快进不跳I帧
#define MODERULE_SINGLE_FILE						(0x50)	//设置为单一文件模式
#define MODERULE_MUTI_FILE							(0x51)	//设置为多文件模式
#define MODERULE_FIX_RATIO							(0x60)	//按比例视频比例显示
#define MODERULE_FIX_WINDOW							(0x61)	//填充窗口显示
#define MODERULE_VIDEO_OPTIMIZE_CLOSE				(0x70)	//视频效果优化关闭
#define MODERULE_VIDEO_OPTIMIZE_OPEN				(0x71)	//视频效果优化开启
/*********************************************************************************************/


/*********************************************************************************************/
typedef void (CALLING_CONVENTION* pfCBPlayEnd)(int _iID);
typedef void (CALLING_CONVENTION* pfCBGetDecAV)(int _iID, const DecAVInfo* _pDecAVInfo, void* _iUser);
typedef void (CALLING_CONVENTION* pfCBVideoEdit)(int _iNotifyCode);
typedef int  (CALLING_CONVENTION* pfCBDrawFun)(long _lHandle,HDC _hDc,void* _lUserData);
typedef int  (CALLING_CONVENTION* pfCBDrawFunEx)(long _lHandle,HDC _hDc, long _lWidth, long _lHeight, void* _lUserData);
#ifdef __WIN__
typedef int  (CALLING_CONVENTION* pfCBCommonEventNotify)(int _iPlayerID, int _iEventMessage);
#endif
typedef int  (CALLING_CONVENTION* pfCBCommonEventNotifyEx)(int _iPlayerID, int _iEventMessage, void* _lpUserData);
typedef void (__stdcall* pfAudioCaptureCbk)(unsigned char* _pucData, int _iLen, void* _pvUserData);
typedef void (__stdcall* pfRawFrameCbk)(int _iPlayerID, unsigned char* _pucData, int _iLen, void* _pvUserData);

//音频采集，用于对讲
typedef int (*RECORD_VOICE_NOTIFY)(unsigned char *_pucAuidoBuffer, int _iAudioLen);
/*********************************************************************************************/



//按需创建播放器的类型标志
typedef enum __tagPlayModeCmd
{
	E_NORMAL_PLAYER				= -1,
	E_FILE_ONLYDECODE			= 0,			//文件模式仅解码
	E_STREAM_ONLYDECODE			= 1,			//流模式仅解码
	E_YUV_PLAYER				= 2,			//YUV播放器
	E_RGB_PLAYER				= 3,			//RGB播放器
	E_SYC_PLAYER				= 4,			//同步播放器
	E_VOD_RAWNOTIFY				= 5,			//前端回放原始流回调
	E_HWDECODE_PLAYER			= 6,			//硬解
	E_CUDA_STREAMPLAYER			= 7,            //CUDA
	E_NORMAL_FILEPLAYER			= 8,            //文件模式播放器
	E_NORMAL_STREAMPLAYER		= 9,            //流模式播放器
	E_NORMAL_VODPLAYER			= 10,           //VOD模式播放器
	E_CUDA_FILE_ONLYDECODE		= 11,           //CUDA文件模式仅解码
	E_CUDA_FILEPLAYER			= 12,			//CUDA文件模式播放器
	E_UNIVERSAL_STREAMPLAYER	= 13			//万能流播放器
}PlayModeCmd, *LPPlayModeCmd;

#define MAX_FILENAME_LEN	256
typedef struct tagFilePlayer
{
	int iSize;
	HWND  hWnd; 
	char cFileName[MAX_FILENAME_LEN];
} FilePlayer, *pFilePlayer;

typedef struct tagStreamPlayer
{
	int iSize;
	HWND  hWnd; 
	unsigned char ucVideoHeadBuf[PLAY_VIDEO_HEADER_LEN];
} StreamPlayer, *pStreamPlayer, VodPlayer, *pVodPlayer;

typedef struct tagCudaPlayer
{
	int iSize;
	int iGpuID;
	HWND  hWnd; 
	unsigned char ucVideoHeadBuf[PLAY_VIDEO_HEADER_LEN];
}CudaPlayer, pCudaPlayer;

typedef struct tagCudaFilePlayer
{
	int iSize;
	int iGpuID;
	HWND  hWnd;		//窗口句柄传NULL，只解码不显示
	char cFileName[MAX_FILENAME_LEN];
} CudaFilePlayer, *pCudaFilePlayer;

typedef struct tagUniversalStreamPlayer
{
	int iSize;
	HWND  hWnd; 
} UniversalStreamPlayer, *pUniversalStreamPlayer;


typedef struct tagRECTEx
{
	double		left;					//原视频百分比
	double		top;					//原视频百分比
	double		right;					//原视频百分比
	double		bottom;					//原视频百分比
}RECTEX, *PRECTEX;


struct FILE_PLAYER
{
	char*		m_pcFileName;			//文件名
	int			m_iDownloadBufSize;		//下载缓冲区大小
	int			m_iFileTrueSize;		//文件大小
	int*		m_piNowFileSize;		//当前文件大小
	int			m_iLastFrmNo;			//最后一帧帧序号
	int*		m_piCompleteFlag;		//是否结束接收
};


struct STREAM_PLAYER
{
	char		m_VideoHeader[88];		//视频头
	int			m_iStreamBufferSize;	//拼帧缓存区大小 传0为默认
};


typedef struct __tagPlayerHeader
{
	int			iSize;
	HWND		hwnd;					//显示句柄
	int			iWidth;
	int			iHeight;
} TPlayerHeader, *PTPlayerHeader;

typedef void (CALLING_CONVENTION* FISHEYE_CallBack)(int _iID, int _iSubID, HDC _pvDC, unsigned int _uiWidth, unsigned int _uiHeight, void* _pvUsrData);

//鱼眼相机安装方式 
#define FEC_MOUNTING_WALL			1	//壁装方式（法线水平）
#define FEC_MOUNTING_FLOOR			2	//地面安装(法线向上）
#define FEC_MOUNTING_CEILING		3	//顶装方式(法线向下）

//鱼眼相机矫正方式
#define FEC_CORRECT_PTZ		0x100		//PTZ 
#define FEC_CORRECT_180		0x200		//180度矫正
#define FEC_CORRECT_360		0x300		//360全景矫正
#define FEC_CORRECT_LAT		0x400		//纬度展开

//设置鱼眼矫正参数CMD
#define CMD_CORRECT_PTZPARA				1		//PTZ矫正参数
#define CMD_CORRECT_CYCLERADIUS			2		//鱼眼图像圆心参数,用于圆心,此命令只支持获取
#define CMD_CORRECT_WIDESCANOFFSET		3		//180或者360度矫正参数
#define CMD_RESERVE_LAST_FRAME			0XFF	//是否保留最后一帧,0-不保留,1-保留. 默认不保留,视频画面显示黑屏.

//PTZ返回到对应图像类型的轮廓点
#define PTZ_RET_TYPE_NONE	 0x0000		//不需要返回轮廓点，只返回图像
#define PTZ_RET_TYPE_FISH	 0x1000		//PTZ返回到鱼眼图像的轮廓点
#define PTZ_RET_TYPE_180	 0x2000		//PTZ返回到180度矫正图像的轮廓点，暂不支持
#define PTZ_RET_TYPE_360	 0x3000		//PTZ返回到360度矫正图像的轮廓点
#define PTZ_RET_TYPE_LAT	 0x4000		//PTZ返回到纬度展开矫正图像的轮廓点
typedef struct tagCorrectPtzPara
{
	int				iSize;
	int				iPtzID;				//Ptz窗口编号,范围0-7
	int				iPTZPositionX;		//PTZ 显示的中心位置X坐标
	int				iPTZPositionY;		//PTZ 显示的中心位置Y坐标
	int				iZoom;				//PTZ 显示的范围参数
	int				iPTZRstWidth;		//PTZ 返回图像的宽度
	int				iPTZRstHeight;		//PTZ 返回图像的高度
	int				iPTZRetType;		//PTZ 返回到对应图像类型
} CorrectPtzPara, *pCorrectPtzPara;

typedef struct tagCorrectCyclePara
{
	int		iSize;					
	int		iRadiusLeft;		//圆的最左边X坐标，使用万分比表示
	int		iRadiusRight;		//圆的最右边X坐标，使用万分比表示 
	int		iRadiusTop;			//圆的最上边Y坐标，使用万分比表示
	int		iRadiusBottom;		//圆的最下边Y坐标，使用万分比表示
} CorrectCyclePara, *pCorrectCyclePara;

typedef struct tagCorrectWideScanPara
{
	int		iSize;					
	float   fWideScanOffset;        // 180或者360度校正的偏移角度
} CorrectWideScanPara, *pCorrectWideScanPara;

typedef struct tagCreateCorrectPara
{
	int					iSize;					
	int					iPlaceType;		//鱼眼相机安装方式
	int					iCorrectType;	//鱼眼相机矫正方式
	CorrectCyclePara	tCycleRadius;	//鱼眼图像圆心参数
	CorrectWideScanPara	tWideScanPara;	//80或者360度校正的偏移角度
	CorrectPtzPara		tPtzPara;		//PTZ矫正参数
	HWND				hWnd;			//窗口显示句柄
} CreateCorrectPara, *pCreateCorrectPara;

//抓拍类型
#define CAPTURE_PICTURE_TYPE_BMP		1
#define CAPTURE_PICTURE_TYPE_JPG		2 
#define CAPTURE_PICTURE_TYPE_FEC_BMP	3
#define CAPTURE_PICTURE_TYPE_FEC_JPG	4 

#define DEFAULT_CYCLE_RADIUS_LEFT		0
#define DEFAULT_CYCLE_RADIUS_RIGHT		10000
#define DEFAULT_CYCLE_RADIUS_TOP		0
#define DEFAULT_CYCLE_RADIUS_BOTTOM		10000

#define MAX_FEC_TRACK_COUNT		8
#define START_ALL_FEC_TRACK		-1
#define STOP_ALL_FEC_TRACK		-1
typedef struct tagFECTrackInfo
{
	int			iSize;
	int			iWindowCount;						//需要跟踪的窗口数目，目前最多支持8PTZ跟踪
	int			iPtzSubID[MAX_FEC_TRACK_COUNT];		//每个PTZ跟踪对应的校正ID，PTZ校正时由接口TC_CreateFishEyeCorrect返回的SubID
} FECTrackInfo, *pFECTrackInfo;

#define CMD_AV_MODE_MIN							0
#define CMD_VIDEO_SHOW_MAIN_MODE		CMD_AV_MODE_MIN + 0
#define CMD_VIDEO_SHOW_SUB_MODE			CMD_AV_MODE_MIN + 1
#define CMD_AV_DEC_SHOW_MODE			CMD_AV_MODE_MIN + 2
#define CMD_AV_DEC_HWDECODE_PARAM		CMD_AV_MODE_MIN + 3  // HwDecodeParam
#define CMD_AV_MODE_MAX					CMD_AV_MODE_MIN + 4

#define SHOW_MAIN_MODE_DRAW		0	//draw 显示
#define SHOW_MAIN_MODE_D3D		1	//d3d 显示
#define SHOW_SUB_MODE_YUV420	0	//420 显示
#define SHOW_SUB_MODE_YUV422	1	//422 显示

#define VIDEO_DLIB_HISI				0
#define VIDEO_DLIB_FFMPEG			1
#define VIDEO_DLIB_CUDA				2
#define COMMON_AUDIO_DLIB_HISI				0
#define COMMON_AUDIO_DLIB_OPENSOURCE		1
#define AAC_AUDIO_DLIB_FAAD					0
#define AAC_AUDIO_DLIB_FFMPEG				1
typedef struct tagAVDecodeMode
{
	int			iSize;
	int			iVideoDecLibType;			//视频解码库类型：Hisi，Ffmpeg
	int			iCommonAudioDecLibType;		//通用音频解码库类型：Hisi，开源库
	int			iAACAudioDecLibType;		//AAC音频解码库类型：faad，Ffmpeg
	int			iVideoShowMainMode;			//视频显示主模式：Draw，D3D
	int			iVideoShowSubMode;			//视频显示子模式：Yuv420，Yuv422
} AVDecodeMode, *pAVDecodeMode;


#define HWDEC_ENABLE_STREAM	0x1
#define HWDEC_ENABLE_VOD	0x2
#define HWDEC_ENABLE_FILE	0x4

#define HWDEC_LIMIT_LOCAL	0
#define HWDEC_LIMIT_GLOBAL	1

//CMD_AV_DEC_HWDECODE_PARAM
typedef struct tagHwDecodeParam
{
	int iSize;
	int iLimitType; //HWDEC_LIMIT_LOCAL or HWDEC_LIMIT_GLOBAL 
	int iMaxCount;  //if iLimitType == HWDEC_LIMIT_GLOBAL, iMaxCount should less than 2
	int iEnableFlag;//HWDEC_ENABLE_STREAM | HWDEC_ENABLE_VOD | HWDEC_ENABLE_FILE
}HwDecodeParam;

#endif
