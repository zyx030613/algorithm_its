
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
#define MAX_SYC_GROUP_NUM			4				//ͬ���ط���������
#define MAX_SYC_PLAYER_NUM			16				//ͬ���ط����player����
#define MSG_PLAYSDKM4				(WM_USER+0x01FF)//�ط�������Ϣ��Ĭ��ֵ
/*********************************************************************************************/


/**********************************************************************************************
* ���ܺ궨��                                                                 
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
* �ط�������Ϣ��LPARAM����ȡֵ�б�                                                                     
**********************************************************************************************/
#define LPARAM_FILE_PLAY_END		0		//�������
#define LPARAM_FILE_SEARCH_END		1		//Ѱ�ҵ��ļ�ĩβ
#define LPARAM_NEED_DECRYPT_KEY		2		//��Ҫ��������
#define LPARAM_DECRYPT_KEY_FAILED	3		//�����������
#define LPARAM_DECRYPT_SUCCESS		4		//���ܳɹ�
#define LPARAM_STREAM_SEARCH_END	5		//����������û��������
#define LPARAM_VOD_STREAM_END		6		//VOD�ļ����������
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
#define DECRYPT_SUCCESS				0		//���ܳɹ�
#define DECRYPT_INVALID_PARAM		(-1)	//��������
#define DECRYPT_KEY_NOT_READY		(-2)	//û���趨������Կ
#define DECRYPT_FRAME_NOT_ENCRYPT	(-3)	//֡���Ǽ���֡
#define DECRYPT_FAILED				(-4)	//֡����ʧ��
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
#define	PLAYMODE_FILE				0		//�ļ�����ģʽ
#define	PLAYMODE_VOD_FILE			1		//VOD����ģʽ
#define	PLAYMODE_STREAM				2		//������ģʽ
/*********************************************************************************************/


/**********************************************************************************************
* Sleep Time                                                                     
**********************************************************************************************/
#define	SLEEP_1						1		//1����
#define	SLEEP_100					100		//100����
/*********************************************************************************************/


/**********************************************************************************************
* ����ֵ�����뺬��                                                                        
**********************************************************************************************/
#define RET_INVALID_PLAYERID		-1		//�Ƿ�PLAYER ID
#define RET_ERR_PLAYMODE			-2		//����Ĳ���ģʽ
#define RET_INVALID_PARAM			-3		//�Ƿ�����
/*********************************************************************************************/


/**********************************************************************************************
* ˢ�¹��ܿ�����                                                                        
**********************************************************************************************/
#define CTRL_REFRESHPLAYER			0		//��ʼ��PLAYER����Ϊ��ɫ����

#define PLAY_SPEED_VALUE_1			1		//2�����ٶ�ֵ
#define PLAY_SPEED_VALUE_2			2		//4�����ٶ�ֵ
#define PLAY_SPEED_VALUE_3			3		//8�����ٶ�ֵ
#define PLAY_SPEED_VALUE_4			4		//16�����ٶ�ֵ

#define PLAY_SPEED_2X_RATE			2		//2��������
#define PLAY_SPEED_4X_RATE			4		//4��������
#define PLAY_SPEED_8X_RATE			8		//8��������
#define PLAY_SPEED_16X_RATE			16		//16��������
/*********************************************************************************************/


/**********************************************************************************************
* Mode Rule                                                                    
**********************************************************************************************/
#define MODERULE_AUTO_ADJUST_DRAW_NO				(0x00)	//����Ӧ��ͬ�ֱ�������--��
#define MODERULE_AUTO_ADJUST_DRAW_YES				(0x01)	//����Ӧ��ͬ�ֱ�������--��
#define MODERULE_AUTO_ADJUST_STREAM_PLAY_SPEED_YES	(0x11)	//����Ӧ������ģʽ�Ĳ�������--��
#define MODERULE_AUTO_ADJUST_STREAM_PLAY_SPEED_NO	(0x10)	//����Ӧ������ģʽ�Ĳ�������--��
#define MODERULE_STREAM_ADAPTIVE					(0x24)	//����Ϊ����Ӧģʽ
#define MODERULE_STREAM_PLAY_BALANCE				(0x23)	//����Ϊ����ģʽ
#define MODERULE_STREAM_PLAY_NO_DELAY				(0x22)	//����Ϊ����ʱģʽ
#define MODERULE_STREAM_PLAY_HIGH_SMOOTH			(0x21)	//����Ϊ������ģʽ
#define MODERULE_STREAM_PLAY_LOW_DELAY				(0x20)	//����Ϊ����ʱģʽ
#define MODERULE_AVIDEO								(0x30)	//����Ϊ����Ƶ
#define MODERULE_PURE_AUDIO							(0x31)	//����Ϊ����Ƶģʽ
#define MODERULE_FAST_FORWARD_SKIP_I				(0x40)	//����Ϊ�����I֡
#define MODERULE_FAST_FORWARD_NO_SKIP_I				(0x41)	//����Ϊ�������I֡
#define MODERULE_SINGLE_FILE						(0x50)	//����Ϊ��һ�ļ�ģʽ
#define MODERULE_MUTI_FILE							(0x51)	//����Ϊ���ļ�ģʽ
#define MODERULE_FIX_RATIO							(0x60)	//��������Ƶ������ʾ
#define MODERULE_FIX_WINDOW							(0x61)	//��䴰����ʾ
#define MODERULE_VIDEO_OPTIMIZE_CLOSE				(0x70)	//��ƵЧ���Ż��ر�
#define MODERULE_VIDEO_OPTIMIZE_OPEN				(0x71)	//��ƵЧ���Ż�����
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

//��Ƶ�ɼ������ڶԽ�
typedef int (*RECORD_VOICE_NOTIFY)(unsigned char *_pucAuidoBuffer, int _iAudioLen);
/*********************************************************************************************/



//���贴�������������ͱ�־
typedef enum __tagPlayModeCmd
{
	E_NORMAL_PLAYER				= -1,
	E_FILE_ONLYDECODE			= 0,			//�ļ�ģʽ������
	E_STREAM_ONLYDECODE			= 1,			//��ģʽ������
	E_YUV_PLAYER				= 2,			//YUV������
	E_RGB_PLAYER				= 3,			//RGB������
	E_SYC_PLAYER				= 4,			//ͬ��������
	E_VOD_RAWNOTIFY				= 5,			//ǰ�˻ط�ԭʼ���ص�
	E_HWDECODE_PLAYER			= 6,			//Ӳ��
	E_CUDA_STREAMPLAYER			= 7,            //CUDA
	E_NORMAL_FILEPLAYER			= 8,            //�ļ�ģʽ������
	E_NORMAL_STREAMPLAYER		= 9,            //��ģʽ������
	E_NORMAL_VODPLAYER			= 10,           //VODģʽ������
	E_CUDA_FILE_ONLYDECODE		= 11,           //CUDA�ļ�ģʽ������
	E_CUDA_FILEPLAYER			= 12,			//CUDA�ļ�ģʽ������
	E_UNIVERSAL_STREAMPLAYER	= 13			//������������
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
	HWND  hWnd;		//���ھ����NULL��ֻ���벻��ʾ
	char cFileName[MAX_FILENAME_LEN];
} CudaFilePlayer, *pCudaFilePlayer;

typedef struct tagUniversalStreamPlayer
{
	int iSize;
	HWND  hWnd; 
} UniversalStreamPlayer, *pUniversalStreamPlayer;


typedef struct tagRECTEx
{
	double		left;					//ԭ��Ƶ�ٷֱ�
	double		top;					//ԭ��Ƶ�ٷֱ�
	double		right;					//ԭ��Ƶ�ٷֱ�
	double		bottom;					//ԭ��Ƶ�ٷֱ�
}RECTEX, *PRECTEX;


struct FILE_PLAYER
{
	char*		m_pcFileName;			//�ļ���
	int			m_iDownloadBufSize;		//���ػ�������С
	int			m_iFileTrueSize;		//�ļ���С
	int*		m_piNowFileSize;		//��ǰ�ļ���С
	int			m_iLastFrmNo;			//���һ֡֡���
	int*		m_piCompleteFlag;		//�Ƿ��������
};


struct STREAM_PLAYER
{
	char		m_VideoHeader[88];		//��Ƶͷ
	int			m_iStreamBufferSize;	//ƴ֡��������С ��0ΪĬ��
};


typedef struct __tagPlayerHeader
{
	int			iSize;
	HWND		hwnd;					//��ʾ���
	int			iWidth;
	int			iHeight;
} TPlayerHeader, *PTPlayerHeader;

typedef void (CALLING_CONVENTION* FISHEYE_CallBack)(int _iID, int _iSubID, HDC _pvDC, unsigned int _uiWidth, unsigned int _uiHeight, void* _pvUsrData);

//���������װ��ʽ 
#define FEC_MOUNTING_WALL			1	//��װ��ʽ������ˮƽ��
#define FEC_MOUNTING_FLOOR			2	//���氲װ(�������ϣ�
#define FEC_MOUNTING_CEILING		3	//��װ��ʽ(�������£�

//�������������ʽ
#define FEC_CORRECT_PTZ		0x100		//PTZ 
#define FEC_CORRECT_180		0x200		//180�Ƚ���
#define FEC_CORRECT_360		0x300		//360ȫ������
#define FEC_CORRECT_LAT		0x400		//γ��չ��

//�������۽�������CMD
#define CMD_CORRECT_PTZPARA				1		//PTZ��������
#define CMD_CORRECT_CYCLERADIUS			2		//����ͼ��Բ�Ĳ���,����Բ��,������ֻ֧�ֻ�ȡ
#define CMD_CORRECT_WIDESCANOFFSET		3		//180����360�Ƚ�������
#define CMD_RESERVE_LAST_FRAME			0XFF	//�Ƿ������һ֡,0-������,1-����. Ĭ�ϲ�����,��Ƶ������ʾ����.

//PTZ���ص���Ӧͼ�����͵�������
#define PTZ_RET_TYPE_NONE	 0x0000		//����Ҫ���������㣬ֻ����ͼ��
#define PTZ_RET_TYPE_FISH	 0x1000		//PTZ���ص�����ͼ���������
#define PTZ_RET_TYPE_180	 0x2000		//PTZ���ص�180�Ƚ���ͼ��������㣬�ݲ�֧��
#define PTZ_RET_TYPE_360	 0x3000		//PTZ���ص�360�Ƚ���ͼ���������
#define PTZ_RET_TYPE_LAT	 0x4000		//PTZ���ص�γ��չ������ͼ���������
typedef struct tagCorrectPtzPara
{
	int				iSize;
	int				iPtzID;				//Ptz���ڱ��,��Χ0-7
	int				iPTZPositionX;		//PTZ ��ʾ������λ��X����
	int				iPTZPositionY;		//PTZ ��ʾ������λ��Y����
	int				iZoom;				//PTZ ��ʾ�ķ�Χ����
	int				iPTZRstWidth;		//PTZ ����ͼ��Ŀ��
	int				iPTZRstHeight;		//PTZ ����ͼ��ĸ߶�
	int				iPTZRetType;		//PTZ ���ص���Ӧͼ������
} CorrectPtzPara, *pCorrectPtzPara;

typedef struct tagCorrectCyclePara
{
	int		iSize;					
	int		iRadiusLeft;		//Բ�������X���꣬ʹ����ֱȱ�ʾ
	int		iRadiusRight;		//Բ�����ұ�X���꣬ʹ����ֱȱ�ʾ 
	int		iRadiusTop;			//Բ�����ϱ�Y���꣬ʹ����ֱȱ�ʾ
	int		iRadiusBottom;		//Բ�����±�Y���꣬ʹ����ֱȱ�ʾ
} CorrectCyclePara, *pCorrectCyclePara;

typedef struct tagCorrectWideScanPara
{
	int		iSize;					
	float   fWideScanOffset;        // 180����360��У����ƫ�ƽǶ�
} CorrectWideScanPara, *pCorrectWideScanPara;

typedef struct tagCreateCorrectPara
{
	int					iSize;					
	int					iPlaceType;		//���������װ��ʽ
	int					iCorrectType;	//�������������ʽ
	CorrectCyclePara	tCycleRadius;	//����ͼ��Բ�Ĳ���
	CorrectWideScanPara	tWideScanPara;	//80����360��У����ƫ�ƽǶ�
	CorrectPtzPara		tPtzPara;		//PTZ��������
	HWND				hWnd;			//������ʾ���
} CreateCorrectPara, *pCreateCorrectPara;

//ץ������
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
	int			iWindowCount;						//��Ҫ���ٵĴ�����Ŀ��Ŀǰ���֧��8PTZ����
	int			iPtzSubID[MAX_FEC_TRACK_COUNT];		//ÿ��PTZ���ٶ�Ӧ��У��ID��PTZУ��ʱ�ɽӿ�TC_CreateFishEyeCorrect���ص�SubID
} FECTrackInfo, *pFECTrackInfo;

#define CMD_AV_MODE_MIN							0
#define CMD_VIDEO_SHOW_MAIN_MODE		CMD_AV_MODE_MIN + 0
#define CMD_VIDEO_SHOW_SUB_MODE			CMD_AV_MODE_MIN + 1
#define CMD_AV_DEC_SHOW_MODE			CMD_AV_MODE_MIN + 2
#define CMD_AV_DEC_HWDECODE_PARAM		CMD_AV_MODE_MIN + 3  // HwDecodeParam
#define CMD_AV_MODE_MAX					CMD_AV_MODE_MIN + 4

#define SHOW_MAIN_MODE_DRAW		0	//draw ��ʾ
#define SHOW_MAIN_MODE_D3D		1	//d3d ��ʾ
#define SHOW_SUB_MODE_YUV420	0	//420 ��ʾ
#define SHOW_SUB_MODE_YUV422	1	//422 ��ʾ

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
	int			iVideoDecLibType;			//��Ƶ��������ͣ�Hisi��Ffmpeg
	int			iCommonAudioDecLibType;		//ͨ����Ƶ��������ͣ�Hisi����Դ��
	int			iAACAudioDecLibType;		//AAC��Ƶ��������ͣ�faad��Ffmpeg
	int			iVideoShowMainMode;			//��Ƶ��ʾ��ģʽ��Draw��D3D
	int			iVideoShowSubMode;			//��Ƶ��ʾ��ģʽ��Yuv420��Yuv422
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
