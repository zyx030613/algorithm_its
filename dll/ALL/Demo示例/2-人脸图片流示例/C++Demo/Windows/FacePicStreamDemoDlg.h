
// ITSFaceSnapDemoDlg.h : ͷ�ļ�
//
#include "resource.h"
#include "DlgPicPanel.h"
#include "NetClientTypes.h"
#include <list>
using namespace std;

#pragma once

#define MAX_SNAP_NUM	27
#define MAX_SNAP_FACEPIC_NUM	200000	//Сͼ��������200000��


class CFacePicStreamDemoDlg : public CDialog
{
// ����
public:
	CFacePicStreamDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

	virtual ~CFacePicStreamDemoDlg();	//��������

// �Ի�������
	enum { IDD = IDD_FACEPICSTREAMDEMO_DLG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()

private:
	CString GetSaveFacePicName(FacePicStream* _ptData, int _iFaceIndex, int _iAlaramType=-1);

public:
	afx_msg void OnBnClickedButtonStartRecv();
	afx_msg void OnCbnSelchangeComboSnapNum();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedButtonLogOn();
	afx_msg void OnBnClickedButtonStopRecv();
	afx_msg void OnBnClickedButtonLogOff();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	int InitUIInfo(); //��ʼ��������Ϣ
	int MultiScreen(int _iRows);    //��̬��������Сͼ��Ƶ��
	int ShowPicWindow(int _iRows);  //������ʾ����Сͼ��
	int CloseThreadFunction();     //���̹߳رպ���
	int InitSDK();					//��ʼ��NVSSDK
	int InitLoglist();				//��ʼ����־��ӡ
	void StartRecvPicStream();
	void StopRecvPicStream();
	static int __stdcall OnPicStreamNotify(unsigned int _uiRecvID, long _lCommand, void* _pvBuf, int _iBufLen, void* _pvUser);
	void ProcessPicStream(unsigned int _uiRecvID, long _lCommand, void* _pvBuf, int _iBufLen);
	afx_msg void OnBnClickedRadioDirectMode();
	afx_msg void OnBnClickedRadioActiveMode();
	static DWORD WINAPI DealDataThread(void* _pvPara);
	int  CloseThread();
	void DealPicData();
	int ShowPicture(CWnd* _pDlgWindow, int _DataLen, unsigned char* _pucPicData);
	int DealFacePicData(FacePicStream* _ptData);	
	int DealFullPicData(FacePicStream* _ptData);
	int SavePicture(int _DataLen, unsigned char* _pucPicData, CString _strPicName);
	int	DrawBackGround();
	void FreePicData(FacePicStream* _ptData);

private:
	CDlgPicPanel* m_pDlgPicPanel[MAX_SNAP_NUM];
	CStatic m_staticBigPic;
	CComboBox m_cboSnapNum;
	int m_iFaceIndex;
	int m_iSaveFacePicCount;
	HBRUSH       m_brushMainBack;   //������ɫ��ˢ
	CIPAddressCtrl m_ipaddDevIp;
	CEdit  m_editDevPort;
	CEdit  m_editUserName;
	CEdit  m_editPassword;
	CEdit  m_edtFactoryID;
	CListCtrl m_lstLog;
	HANDLE m_hThread;
	bool   m_bTermiThread;
	CRITICAL_SECTION m_CriticalSec;
	int m_iLogonID;
	unsigned int m_uiRecvID;
	char m_cDevIP[16];
	BOOL m_blISDrawBlack;
	BOOL m_blFullScreen;
	CWnd* m_hParentWnd;	
	RECT m_rcOldWindowRect;
	int m_iConnetMode;
	CButton m_RdoDirectMode;
	CButton m_RdoActiveMode;
	list <FacePicStream*> m_lstPicData;
	bool m_blRecvData;
};



