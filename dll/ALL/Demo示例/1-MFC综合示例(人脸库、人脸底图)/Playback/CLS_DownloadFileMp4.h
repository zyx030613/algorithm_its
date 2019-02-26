
#ifndef __H_DOWNLOAD_MP4_H__
#define __H_DOWNLOAD_MP4_H__

#include "../Common/CommonFun.h"
#include "../Include/NVSSDK_INTERFACE.h"
#include "../Include/MP4_INTERFACE.h"

using namespace NVSSDK_INTERFACE;
using namespace MP4_INTERFACE;

#define TEMP_SRC_FILE_EXTENSION		".tmp"

#define WM_DOWNLOAD_FINSH_MSG          (WM_USER + 0x3021)

enum FILE_DOWNLOAD_STATUS
{
	n_DLStatus_Reserved = -1,	//δ֪״̬
	n_DLStatus_wait     =  0,	//׼������
	n_DLStatus_Doing,			//��������
	n_DLStatus_Pause,			//��ͣ����
	n_DLStatus_DL_Complete,		//���سɹ�
	n_DLStatus_DL_Fail,			//����ʧ��
	n_DLStatus_Converting,		//����ת��
	n_DLStatus_Convert_Complete,//ת���ɹ�
	n_DLStatus_Convert_Fail,	//ת��ʧ��
	n_DLStatus_Finish			//ȫ�����
};

enum SDV_CONVERT_STATUS
{
	CONVERT_STATUS_READY = 0,	//׼��ת��
	CONVERT_STATUS_SUCCESS,		//ת���ɹ�
	CONVERT_STATUS_FAILED		//ת��ʧ��
};

#define DOWN_LOAD_SPEED_PAUSE			0
#define DOWN_LOAD_SPEED_START			16
#define DOWN_LOAD_SPEED_32				32
#define DOWN_LOAD_POS_RESERVE			-1

#define RATIO_BYTE_CONVERT				1024

class CLS_DownloadFileMp4
{
public:
	CLS_DownloadFileMp4(HWND _pParent, int _iLogonId, DOWNLOAD_FILE _tDownLoadInfo, BOOL _blBreakContinue = FALSE);
	~CLS_DownloadFileMp4();

private:
	int				m_iLogonId;					//��½ID
	DOWNLOAD_FILE	m_tDownLoadInfo;			//������Ϣ
	int				m_iConnectId;				//����ID
	int				m_iDownLoadStatus;			//����״̬
	BOOL			m_blBreakContinue;			//�ϵ�����
	int				m_iDownLoadPos;				//���ؽ���
	BOOL			m_blKeepSdvFile;
	HWND			m_hParents;

public:
	static unsigned int __stdcall FileConvertThread(LPVOID _Param);

public:
	int	StartDownLoad(BOOL blRestart = FALSE);					//��ʼ����
	int StartBreakContineDownLoad();
	int StopDowmLoad(BOOL _blDownLoadSuccess = TRUE, BOOL _blKeepSdvFile = FALSE, BOOL _blConvertToMp4 = TRUE);	//ֹͣ����
	BOOL CheckDownLoadInfo(int _iLogonId, char* _pcRemoteFileName);	//�ж��Ƿ�Ϊ��ǰ����
	BOOL CheckDownLoadInfo(int _iConnectId);						//�ж��Ƿ�Ϊ��ǰ����
	int SetDownLoadSpeed(DOWNLOAD_CONTROL _tDownLoadControl);		//���������ٶ�0����ͣ����, 16:Ĭ�������ٶȿ�ʼ����
	char* GetDownLoadProgress(char* _pcProgress, int _iLen);		//��ȡ���ؽ���
	BOOL CheckBreakContinue();
	int GetConnectId();		
	int GetLogonId();
	CString GetFileName();										//��ȡ�����ļ���ȫ����
	int GetDownLoadStatus();									//��ȡ����״̬
	int InnerDealConvertResult(int _iConvertSatus, BOOL _blKeepSdvFile);

};

#endif
