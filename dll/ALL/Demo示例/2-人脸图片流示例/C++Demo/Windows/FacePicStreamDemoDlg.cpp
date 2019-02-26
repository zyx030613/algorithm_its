
// ITSFaceSnapDemoDlg.cpp : ʵ���ļ�

#include "stdafx.h"
#include "FacePicStreamDemo.h"
#include "FacePicStreamDemoDlg.h"
#include "NetSdk.h"
#include "LogManager.h"
#include "FaceAttrInfoDefine.h"

#include <io.h>
#include <direct.h>


static CString IntToCString(int _iValue)
{
	CString cstrTemp;
	cstrTemp.Format("%d", _iValue);
	return cstrTemp;
}

static CString GetFaceAttrInfoName(int _iAttr, int _iValue)
{
	CString cstrAttrName;
	if (_iAttr >= 0 && _iAttr < MAX_FACE_ATTR_NUM)
	{
		cstrAttrName = g_strFaceAttrName[_iAttr];
	}
	else
	{
		cstrAttrName.Format("Attr%d", _iAttr);
	}

	cstrAttrName += _T("-");

	switch (_iAttr)
	{
	case FACE_ATTR_Sex:
		{
			if (_iValue >= 0 && _iValue < MAX_ATTR_SEX_NUM)
			{
				cstrAttrName += g_strAttrSexName[_iValue];
			}
			else
			{
				cstrAttrName += IntToCString(_iValue);
			}
		}
		break;
	case FACE_ATTR_Mask:
	case FACE_ATTR_Beard:
	case FACE_ATTR_OpenEye:
	case FACE_ATTR_OpenMouth:
		{
			if (_iValue >= 0 && _iValue < MAX_ATTR_COMMON_NUM)
			{
				cstrAttrName += g_strAttrCommonName[_iValue];
			}
			else
			{
				cstrAttrName += IntToCString(_iValue);
			}
		}
		break;
	case FACE_ATTR_Glasses:
		{
			if (_iValue >= 0 && _iValue < MAX_ATTR_GLASSES_NUM)
			{
				cstrAttrName += g_strAttrGlassesName[_iValue];
			}
			else
			{
				cstrAttrName += IntToCString(_iValue);
			}
		}
		break;
	case FACE_ATTR_Race:
		{
			if (_iValue >= 0 && _iValue < MAX_ATTR_RACE_NUM)
			{
				cstrAttrName += g_strAttrRaceName[_iValue];
			}
			else
			{
				cstrAttrName += IntToCString(_iValue);
			}
		}
		break;
	case FACE_ATTR_Expression:
		{
			if (_iValue >= 0 && _iValue < MAX_ATTR_EXPRESSION_NUM)
			{
				cstrAttrName += g_strAttrExpressionName[_iValue];
			}
			else
			{
				cstrAttrName += IntToCString(_iValue);
			}
		}
		break;
	case FACE_ATTR_Smile:
		{
			if (FACE_ATTR_SMILE_THRESHOLD_VALUE > _iValue)
			{
				cstrAttrName += g_strAttrSmileName[ATTR_SMILE_No];
			}
			else
			{
				cstrAttrName += g_strAttrSmileName[ATTR_SMILE_Yes];
			}
		}
		break;
	case FACE_ATTR_Nation:
		{
			if (ATTR_NATION_Han == _iValue)
			{
				cstrAttrName += g_strAttrNationName[ATTR_NATION_Han];
			}
			else
			{
				cstrAttrName += g_strAttrNationName[ATTR_NATION_Other];
				cstrAttrName += IntToCString(_iValue);
			}

		}
		break;
	case FACE_ATTR_Objtype:
		{
			if (_iValue >= 0 && _iValue < MAX_ATTR_OBJTYPE_NUM)
			{
				cstrAttrName += g_strAttrObjTypeName[_iValue];
			}
			else
			{
				cstrAttrName += IntToCString(_iValue);
			}
		}
		break;
	default:
		{
			cstrAttrName += IntToCString(_iValue);
		}
	}

	return cstrAttrName;
}

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define VIDEO_BORDER_COLOR_NORMAL      RGB(220,220,220)//��ɫ
#define VIDEO_BORDER_COLOR_SELECTED    RGB(255,0,0)	//��ɫ
#define WIDTH_ROWS					   9	        //ÿ���ŷ�9��ͼƬ
#define RET_SUCCESS 0  //�ɹ�
#define RET_FAILED -1  //ʧ��
#define ROW_ONE   1	   //��ʾ1����Ƶ��
#define ROW_TWO   2    //��ʾ2����Ƶ��
#define ROW_THREE 3    //��ʾ3����Ƶ��
#define MAX_ROW_TWO_WINDOWS 18  //����������ʾ����18������

CString g_cstrFaceDevIP;
const int CONST_iNUMBERCOLUMNWidth = 50;

#define MAX_ACTIVE_WAIT_TIME	30		//30s
#define MAX_FULL_PIC_SIZE	1024 * 1024 * 8
#define MAX_FACE_PIC_SIZE	1024 * 1024 * 3

void SleepPro(int _iMsValue)
{
	DWORD  dw = GetTickCount();
	MSG   msg;   	
	while(GetTickCount() < dw + _iMsValue)
	{		
		Sleep(10);
		if (::PeekMessage(&msg,NULL,0,0,PM_REMOVE))   
		{   
			::TranslateMessage(&msg);   
			::DispatchMessage(&msg);   
		}   
	}
}

//��õ�ǰʱ����ַ���
void GetLocalTimeString(char* _pcTime)
{
	if (NULL == _pcTime)
	{
		return;
	}

	SYSTEMTIME localTime;
	GetLocalTime(&localTime);

	sprintf_s(_pcTime, 32, "%04d-%02d-%02d %02d:%02d:%02d",
		localTime.wYear,localTime.wMonth,localTime.wDay,
		localTime.wHour, localTime.wMinute, localTime.wSecond);
}

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������0
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

CFacePicStreamDemoDlg::CFacePicStreamDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFacePicStreamDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	for (int i = 0; i < MAX_SNAP_NUM; ++i)
	{
		m_pDlgPicPanel[i] = NULL;
	}
	m_hThread = NULL;
	m_bTermiThread = false;
	m_iLogonID = -1;
	m_uiRecvID = -1;
	m_iFaceIndex = -1;
	m_iSaveFacePicCount = 0;
	memset(m_cDevIP, 0 ,sizeof(m_cDevIP));
	m_blISDrawBlack = FALSE;
	m_hParentWnd = pParent;
	m_blFullScreen = FALSE;
	memset(&m_rcOldWindowRect, 0, sizeof(m_rcOldWindowRect));
	InitializeCriticalSection(&m_CriticalSec);  //��ʼ���ٽ���
	m_iConnetMode = SERVER_NORMAL;
	m_lstPicData.clear();
	m_blRecvData = false;
}

CFacePicStreamDemoDlg::~CFacePicStreamDemoDlg()
{
}

void CFacePicStreamDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SNAP_NUM, m_cboSnapNum);
	DDX_Control(pDX, IDC_IPADDRESS_DEV_IP, m_ipaddDevIp);
	DDX_Control(pDX, IDC_EDIT_DEV_PORT, m_editDevPort);
	DDX_Control(pDX, IDC_EDIT_USER_NAME, m_editUserName);
	DDX_Control(pDX, IDC_EDIT_USER_PASSWORD, m_editPassword); 
	DDX_Control(pDX, IDC_EDIT_FACTORY_ID, m_edtFactoryID);  
	DDX_Control(pDX, IDC_STATIC_BIG_PIC, m_staticBigPic); 
	DDX_Control(pDX, IDC_LIST_LOG, m_lstLog);
	DDX_Control(pDX, IDC_RADIO_DIRECT_MODE, m_RdoDirectMode);
	DDX_Control(pDX, IDC_RADIO_ACTIVE_MODE, m_RdoActiveMode);
}

BEGIN_MESSAGE_MAP(CFacePicStreamDemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_START_RECV, &CFacePicStreamDemoDlg::OnBnClickedButtonStartRecv)
	ON_CBN_SELCHANGE(IDC_COMBO_SNAP_NUM, &CFacePicStreamDemoDlg::OnCbnSelchangeComboSnapNum)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_LOG_ON, &CFacePicStreamDemoDlg::OnBnClickedButtonLogOn)
	ON_BN_CLICKED(IDC_BUTTON_STOP_RECV, &CFacePicStreamDemoDlg::OnBnClickedButtonStopRecv)
	ON_BN_CLICKED(IDC_BUTTON_LOG_OFF, &CFacePicStreamDemoDlg::OnBnClickedButtonLogOff)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_RADIO_DIRECT_MODE, &CFacePicStreamDemoDlg::OnBnClickedRadioDirectMode)
	ON_BN_CLICKED(IDC_RADIO_ACTIVE_MODE, &CFacePicStreamDemoDlg::OnBnClickedRadioActiveMode)
END_MESSAGE_MAP()


// CITSFaceSnapDemoDlg ��Ϣ�������

BOOL CFacePicStreamDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�
	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	m_brushMainBack	= ::CreateSolidBrush(RGB(0,0,0));

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_RdoDirectMode.SetCheck(BST_CHECKED);
	int iRet = LoadLib();  //����NVSSDK��̬��
	if (RET_SUCCESS != iRet)
	{
		CString cstrInfo;
		cstrInfo.Format("[DemoDlg::InitSDK] ����NVSSDK�⺯�� LoadNVSSDK()����ʧ��");
		CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_FAIL, g_cstrFaceDevIP, cstrInfo, GetLastError());
	}
	InitUIInfo();  //��ʼ������
	InitLoglist();  //��ʼlist����

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CFacePicStreamDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFacePicStreamDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{
		CDialog::OnPaint();

		CPaintDC dc(GetDlgItem(IDC_STATIC_BIG_PIC));
		CRect  rect;
		m_staticBigPic.GetClientRect(rect);
		dc.FillSolidRect(rect,RGB(0,0,0));
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CFacePicStreamDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CFacePicStreamDemoDlg::InitUIInfo()
{
	m_cboSnapNum.ResetContent();
	m_cboSnapNum.SetItemData(m_cboSnapNum.AddString("9ͼ��ʾ"), 1);
	m_cboSnapNum.SetItemData(m_cboSnapNum.AddString("18ͼ��ʾ"), 2);
	m_cboSnapNum.SetItemData(m_cboSnapNum.AddString("27ͼ��ʾ"), 3);
	m_cboSnapNum.SetCurSel(0);

	SetDlgItemText(IDC_IPADDRESS_DEV_IP, "192.168.1.2");
	SetDlgItemText(IDC_EDIT_DEV_PORT, "3000");
	SetDlgItemText(IDC_EDIT_USER_NAME, "admin");
	SetDlgItemText(IDC_EDIT_USER_PASSWORD, "1111");
	SetDlgItemText(IDC_EDIT_FACTORY_ID, "ID");

	for (int i = 0; i < MAX_SNAP_NUM; ++i)  //��PicPanel�Ի���Ƕ�����Ի�����
	{	
		m_pDlgPicPanel[i] = new CDlgPicPanel(this);
		if(m_pDlgPicPanel[i])
		{
			m_pDlgPicPanel[i]->SetPanelID(i);
			m_pDlgPicPanel[i]->Create(IDD_DIALOG_PIC_PANEL,this);
			m_pDlgPicPanel[i]->SetParent(this);
		}
	}

	return 0;
}

void CFacePicStreamDemoDlg::OnCbnSelchangeComboSnapNum()
{
	int iRows = -1;
	iRows = (int)m_cboSnapNum.GetItemData(m_cboSnapNum.GetCurSel());
	ShowPicWindow(iRows);
	m_iFaceIndex = -1;

}

int CFacePicStreamDemoDlg::InitLoglist()
{
	m_lstLog.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	LONG lStyle;
	lStyle = GetWindowLong(m_lstLog.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
	lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
	lStyle |= LVS_REPORT; //����style
	SetWindowLong(m_lstLog.m_hWnd, GWL_STYLE, lStyle);//����style
	m_lstLog.InsertColumn(0, "���", LVCFMT_LEFT, CONST_iNUMBERCOLUMNWidth);
	RECT rectList={0};
	m_lstLog.GetWindowRect(&rectList);
	ScreenToClient(&rectList);
	int iInfoColumnWidth = rectList.right - rectList.left - CONST_iNUMBERCOLUMNWidth - 30;//-30,�����������һ�����ˮƽ������
	m_lstLog.InsertColumn(1, "��־��Ϣ", LVCFMT_LEFT, iInfoColumnWidth);
	CLS_LogManager::GetInstance()->SetListCtrl(&m_lstLog);
	return 0;
}

void CFacePicStreamDemoDlg::OnBnClickedButtonStartRecv()
{
	if (m_iLogonID < 0 || LOGON_SUCCESS != NetClient_GetLogonStatus(m_iLogonID))
	{
		CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_FAIL, g_cstrFaceDevIP, "��ȴ���½�ɹ������ԣ�", GetLastError());
		return;
	}

	if (m_blRecvData)
	{
		CString cstrInfo;
		cstrInfo = "���ڽ�������!";
		CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_SUCC, g_cstrFaceDevIP, cstrInfo, GetLastError());
		return;
	}

	return StartRecvPicStream();
}

//��̬��������Сͼ��Ƶ��
int CFacePicStreamDemoDlg::MultiScreen(int _iRows)
{
	RECT rtWin ={0};

	GetDlgItem(IDC_STATIC_FACE_PIC)->GetWindowRect(&rtWin);
	ScreenToClient(&rtWin);

	int iWidth = (rtWin.right-rtWin.left)/WIDTH_ROWS;
	int iHeight = (rtWin.bottom-rtWin.top)/_iRows;
 	
	RECT rcTemp = {0};
	for (int i = 0; i < _iRows; ++i)			//��
	{
		for (int j = 0; j < WIDTH_ROWS; ++j)	//��
		{
			rcTemp.left=2;
			rcTemp.top = 2;
			rcTemp.right=iWidth;
			rcTemp.bottom=iHeight;
			OffsetRect(&rcTemp,rtWin.left+j*iWidth,rtWin.top+i*iHeight);

			int iIndex = i*WIDTH_ROWS + j;

			CString csrtTemp;
			csrtTemp.Format("m_pDlgPicPanel[%d]\n", (iIndex));
			OutputDebugString(csrtTemp);

			if (m_pDlgPicPanel[iIndex])
			{
				m_pDlgPicPanel[iIndex]->ShowWindow(SW_SHOW);
				m_pDlgPicPanel[iIndex]->MoveWindow(&rcTemp);
				m_pDlgPicPanel[iIndex]->RedrawWindow();
			}
		}
	}

	for (int i = _iRows*WIDTH_ROWS; i < MAX_SNAP_NUM; ++i)
	{
		if (m_pDlgPicPanel[i])
		{
			m_pDlgPicPanel[i]->ShowWindow(SW_HIDE);
		}
	}

	return 0;
}

void CFacePicStreamDemoDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: ������ʾ9ͼ��ֻ��1��
	ShowPicWindow(1);
	
}

int CFacePicStreamDemoDlg::ShowPicWindow(int _iRows)
{
	// TODO: ѡ��ͬ��ͼ����ʾ��̬������Ƶ��
	int iRet = RET_FAILED;
	iRet = MultiScreen(_iRows);

	return iRet;
}

//���ص���������ȡ��¼״̬
void Notify_Main(int _iLogonID, long  _iWparam, void* _iLParam,void* _iUserData)
{
	long iMsgType = LOWORD(_iWparam);
	switch (iMsgType)
	{
	case WCM_LOGON_NOTIFY:
		{
			printf("WCM_LOGON_NOTIFY\n");
			if(_iLParam == LOGON_SUCCESS)
			{
				//Sleep(100);

				CString cstrInfo;
				cstrInfo = "��¼�ɹ�";
				CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_SUCC, g_cstrFaceDevIP, cstrInfo, GetLastError());
			}
			else
			{
				CString cstrInfo;
				cstrInfo = "��¼ʧ��";
				CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_FAIL, g_cstrFaceDevIP, cstrInfo, GetLastError());
				g_cstrFaceDevIP.Empty();
			}
		}
		break;
	default:
		break;
	}
}

void CFacePicStreamDemoDlg::OnBnClickedButtonLogOn()
{
	InitSDK();
	// TODO: ��¼�豸
	int		iDevPort = -1;
	CString cstrDevPort;
	CString cstrDevIp;	
	CString cstrUserName;
	CString cstrPassword;
	CString cstrFactoryID;
	m_editDevPort.GetWindowText(cstrDevPort);
	iDevPort = atoi(cstrDevPort);
	m_ipaddDevIp.GetWindowText(cstrDevIp);
	m_editUserName.GetWindowText(cstrUserName);
	m_editPassword.GetWindowText(cstrPassword);
	m_edtFactoryID.GetWindowText(cstrFactoryID);
	g_cstrFaceDevIP += cstrDevIp;
	strncpy(m_cDevIP, cstrDevIp, sizeof(m_cDevIP));
	//��¼�豸
	if (SERVER_ACTIVE == m_iConnetMode)
	{
		DsmOnline tOnline = {0};
		tOnline.iSize = sizeof(DsmOnline);
		strncpy_s(tOnline.cProductID, LEN_32, cstrFactoryID.GetBuffer(), LEN_32);
		NetClient_GetDsmRegstierInfo(DSM_CMD_GET_ONLINE_STATE, &tOnline, sizeof(DsmOnline));
		int iOutTime = 0;
		while (DSM_STATE_ONLINE != tOnline.iOnline)
		{
			if (iOutTime >= MAX_ACTIVE_WAIT_TIME)
			{
				CString cstrInfo;
				cstrInfo = "�豸û��ע��!";
				CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_FAIL, g_cstrFaceDevIP, cstrInfo, GetLastError());
				break;
			}
			SleepPro(1000);
			NetClient_GetDsmRegstierInfo(DSM_CMD_GET_ONLINE_STATE, &tOnline, sizeof(DsmOnline));
			iOutTime++;
		}
		LogonActiveServer tActive = {0};
		tActive.iSize = sizeof(LogonActiveServer);
		strncpy_s(tActive.cUserName, cstrUserName.GetBuffer(), LEN_16);
		strncpy_s(tActive.cUserPwd, cstrPassword.GetBuffer(), LEN_16);
		strncpy_s(tActive.cProductID, cstrFactoryID.GetBuffer(), LEN_32);
		int iLogonId = NetClient_Logon_V4(SERVER_ACTIVE, &tActive, sizeof(LogonActiveServer));
		if(iLogonId < 0)
		{
			CString cstrInfo;
			cstrInfo = "��¼ʧ��";
			CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_FAIL, g_cstrFaceDevIP, cstrInfo, GetLastError());
		}
		else
		{
			m_iLogonID = iLogonId;
		}
	} 
	else
	{
		int iLogonId = NetClient_Logon("", cstrDevIp.GetBuffer(), cstrUserName.GetBuffer(), cstrPassword.GetBuffer(), "", iDevPort);
		if(iLogonId < 0)
		{
			CString cstrInfo;
			cstrInfo = "��¼ʧ��";
			CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_FAIL, g_cstrFaceDevIP, cstrInfo, GetLastError());
		}
		else
		{
			m_iLogonID = iLogonId;
		}
	}

	m_staticBigPic.ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);  //�޸ľ�̬����

	//�����̵߳�������ص�����
	DWORD dwId;
	CloseThread();
	if (!m_bTermiThread)
	{
		m_bTermiThread = true;
		m_hThread = CreateThread(NULL, NULL, DealDataThread, this, 0, &dwId);
	}	

	cstrDevIp.ReleaseBuffer();
	cstrUserName.ReleaseBuffer();
	cstrPassword.ReleaseBuffer();
}

void CFacePicStreamDemoDlg::OnBnClickedButtonStopRecv()
{
	if (!m_blRecvData)
	{
		CString cstrInfo;
		cstrInfo = "û�н������ݣ�����ֹͣ!";
		CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_SUCC, g_cstrFaceDevIP, cstrInfo, GetLastError());
		return;
	}

	return StopRecvPicStream();
}

void CFacePicStreamDemoDlg::OnBnClickedButtonLogOff()
{
	// TODO: �˳���¼������������ݵ��߳�
	g_cstrFaceDevIP.Empty();
	m_iFaceIndex = -1;
	m_iSaveFacePicCount = 0;

	if (BST_UNCHECKED != IsDlgButtonChecked(IDC_BUTTON_START_RECV))
	{
		int iStopRet = NetClient_StopCaptureData(m_uiRecvID);//ʹ��NetClient_StartRecv�з��ص�ID�š�
		if (RET_SUCCESS != iStopRet)
		{
			CString cstrInfo;
			cstrInfo.Format("[DemoDlg::LogOff] �ӿ�NetClient_StopCaptureData����ʧ��");
			CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_FAIL, g_cstrFaceDevIP, cstrInfo, GetLastError());
		}
		int iStopRecvRet = NetClient_StopRecv(m_uiRecvID);	
		if(RET_SUCCESS != iStopRecvRet)
		{
			CString cstrInfo;
			cstrInfo.Format("[DemoDlg::LogOff] �ӿ�NetClient_StopRecv����ʧ��");
			CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_FAIL, g_cstrFaceDevIP, cstrInfo, GetLastError());
		}
	}
	
	int iLogoffRet = NetClient_Logoff(m_iLogonID);//ע���û�
	if (RET_SUCCESS != iLogoffRet)
	{
		CString cstrInfo;
		cstrInfo.Format("[DemoDlg::LogOff] �ӿ�NetClient_Logoff����ʧ��");
		CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_FAIL, g_cstrFaceDevIP, cstrInfo, GetLastError());
	}
	CloseThreadFunction();
	//����Сͼ����
 	for (int iIndex = 0; iIndex < MAX_SNAP_NUM; iIndex++)
 	{
 		m_pDlgPicPanel[iIndex]->m_iISDrawBlack = IS_DROW;
		m_pDlgPicPanel[iIndex]->RedrawWindow();
 	}
	m_blISDrawBlack = TRUE;
	RedrawWindow();
	m_blRecvData = false;
	CString cstrInfo;
	cstrInfo.Format("�˳���¼!");
	CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_SUCC, g_cstrFaceDevIP, cstrInfo, GetLastError());
}

//�ر����̺߳���
int CFacePicStreamDemoDlg::CloseThreadFunction()
{	
	if (m_bTermiThread)
	{
		m_bTermiThread = false; 
		CloseThread();
	}	
	return 0;
}

//��ʼ��SDK
int CFacePicStreamDemoDlg::InitSDK()
{
	if (NULL == NetClient_Startup_V4)
	{
		return RET_FAILED;
	}

	int iRet = RET_FAILED;
	if (SERVER_ACTIVE == m_iConnetMode)
	{
		int iListeningPort = GetDlgItemInt(IDC_EDIT_DEV_PORT);
		iRet = NetClient_Startup_V4(iListeningPort, 0, 0);//��ʼ��SDK
	}
	else
	{
		iRet = NetClient_Startup_V4(0, 0, 0);//��ʼ��SDK
	}

	if (RET_SUCCESS != iRet)
	{
		CString cstrInfo;
		cstrInfo.Format("[DemoDlg::InitSDK] �ӿ�NetClient_Startup_V4����ʧ��");
		CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_FAIL, g_cstrFaceDevIP, cstrInfo, GetLastError());
		goto EXIT;
	}
	iRet = NetClient_SetNotifyFunction_V4(Notify_Main, NULL, NULL, NULL, NULL);//�������ص�����
	if (RET_SUCCESS != iRet)
	{
		CString cstrInfo;
		cstrInfo.Format("[DemoDlg::InitSDK] �ӿ�NetClient_SetNotifyFunction_V4����ʧ��");
		CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_FAIL, g_cstrFaceDevIP, cstrInfo, GetLastError());
		goto EXIT;
	}

EXIT:
	return iRet;
}

HBRUSH CFacePicStreamDemoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here

	// TODO:  Return a different brush if the default is not desired

	switch(nCtlColor)
	{
	case CTLCOLOR_SCROLLBAR:
		break;
	case CTLCOLOR_STATIC: //�����о�̬�ı��ؼ�������
		if(pWnd->m_hWnd == m_staticBigPic.GetSafeHwnd())
		{ 
			pDC->SetBkColor(RGB(0,0,0)); 
			return (HBRUSH)m_brushMainBack; 
		}
		break;
	default:;
	}
	return hbr;
}

void CFacePicStreamDemoDlg::OnCancel()
{
	StopRecvPicStream();
	CloseThreadFunction();
	DeleteCriticalSection(&m_CriticalSec);

	CDialog::OnCancel();
}

void CFacePicStreamDemoDlg::StartRecvPicStream()
{
	if (NULL == NetClient_StartRecvNetPicStream)
	{
		return;
	}

	NetPicPara tPara = {0};
	tPara.iStructLen = sizeof(NetPicPara);
	tPara.iChannelNo = 0;
	tPara.cbkPicStreamNotify = OnPicStreamNotify;
	tPara.pvUser = this;
	int iRet = NetClient_StartRecvNetPicStream(m_iLogonID, &tPara, sizeof(NetPicPara), &m_uiRecvID);
	if (0 != iRet)
	{
		CString cstrInfo;
		cstrInfo.Format("�ӿ�NetClient_StartRecvNetPicStream����ʧ��");
		CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_FAIL, g_cstrFaceDevIP, cstrInfo, GetLastError());
	}
	else
	{
		m_blRecvData = true;
	}
}

void CFacePicStreamDemoDlg::StopRecvPicStream()
{
	if (m_uiRecvID < 0)
	{
		return;
	}

	if (NULL == NetClient_StopRecvNetPicStream)
	{
		return;
	}

	int iRet = NetClient_StopRecvNetPicStream(m_uiRecvID);
	if (0 != iRet)
	{
		CString cstrInfo;
		cstrInfo.Format("�ӿ�NetClient_StopRecvNetPicStream����ʧ��");
		CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_FAIL, g_cstrFaceDevIP, cstrInfo, GetLastError());
	}
	else
	{
		m_blRecvData = false;
	}
}

int CFacePicStreamDemoDlg::OnPicStreamNotify(unsigned int _uiRecvID, long _lCommand, void* _pvBuf, int _iBufLen, void* _pvUser)
{
	if (NULL != _pvUser)
	{
		CFacePicStreamDemoDlg* pThis = (CFacePicStreamDemoDlg*)_pvUser;
		pThis->ProcessPicStream(_uiRecvID, _lCommand, _pvBuf, _iBufLen);
	}

	return 0;
}

void CFacePicStreamDemoDlg::ProcessPicStream(unsigned int _uiRecvID, long _lCommand, void* _pvBuf, int _iBufLen)
{
	if (NULL == _pvBuf)
	{
		return;
	}

	if (_uiRecvID != m_uiRecvID)
	{
		return;
	}

	if (NET_PICSTREAM_CMD_FACE != _lCommand)
	{
		return;
	}

	if (_iBufLen <= 0)
	{
		return;
	}

	FacePicStream* ptTemp = (FacePicStream*)_pvBuf;

	//����ͼƬ���ṹ���ڴ��Լ�����ֵ
	FacePicStream* ptData = (FacePicStream*)malloc(sizeof(FacePicStream));
	if (NULL == ptData)
	{
		CString cstrInfo;
		cstrInfo.Format("1������ͼƬ���ṹ���ڴ�ʧ��!");
		CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_FAIL, g_cstrFaceDevIP, cstrInfo, GetLastError());
		return;
	}
	memset(ptData, 0, sizeof(FacePicStream));
	memcpy(ptData, ptTemp, min(sizeof(FacePicStream), _iBufLen));
	ptData->ptFullData = NULL;
	for (int i = 0; i < MAX_FACE_PICTURE_COUNT; ++i)
	{
		ptData->ptFaceData[i] = NULL;
	}

	//ȫ��ͼ
	if (NULL != ptTemp->ptFullData)
	{
		//����ȫ��ͼ�ṹ���ڴ��Լ�����ֵ
		ptData->ptFullData = (PicData*)malloc(sizeof(PicData));
		if (NULL == ptData->ptFullData)
		{
			CString cstrInfo;
			cstrInfo.Format("2������ȫ��ͼ�ṹ���ڴ�ʧ��!");
			CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_FAIL, g_cstrFaceDevIP, cstrInfo, GetLastError());
			goto FREE_DATA;
		}
		memcpy(ptData->ptFullData, ptTemp->ptFullData, min(ptTemp->iSizeOfFull, sizeof(PicData)));

		//����ȫ��ͼ�����ڴ��Լ���������
		ptData->ptFullData->pcPicData = NULL;
		ptData->ptFullData->pcPicData = (char*)malloc(ptTemp->ptFullData->iDataLen);
		if (NULL == ptData->ptFullData->pcPicData)
		{
			CString cstrInfo;
			cstrInfo.Format("3������ȫ��ͼ�����ڴ�ʧ��!");
			CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_FAIL, g_cstrFaceDevIP, cstrInfo, GetLastError());
			goto FREE_DATA;
		}
		memcpy(ptData->ptFullData->pcPicData, ptTemp->ptFullData->pcPicData, ptTemp->ptFullData->iDataLen);
	}
	
	//Сͼ
	for (int i = 0; i < ptData->iFaceCount && i < MAX_FACE_PICTURE_COUNT; ++i)
	{
		if(NULL == ptTemp->ptFaceData[i])
		{
			continue;
		}

		//��������Сͼ�ṹ���ڴ��Լ�����ֵ
		ptData->ptFaceData[i] = (FacePicData*)malloc(sizeof(FacePicData));
		if (NULL == ptData->ptFaceData[i])
		{
			CString cstrInfo;
			cstrInfo.Format("4����������Сͼ�ṹ���ڴ�ʧ��!");
			CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_FAIL, g_cstrFaceDevIP, cstrInfo, GetLastError());
			goto FREE_DATA;
		}
		memcpy(ptData->ptFaceData[i], ptTemp->ptFaceData[i], min(ptTemp->iSizeOfFace, sizeof(FacePicData)));

		//�������������ڴ��Լ�����ֵ
		int iFaceAttrCount = min(ptTemp->ptFaceData[i]->iFaceAttrCount, LEN_256);
		int iAttrSize = min(ptTemp->ptFaceData[i]->iFaceAttrStructSize, sizeof(FaceAttribute));
		for (int j = 0; j < iFaceAttrCount; ++j)
		{
			ptData->ptFaceData[i]->ptFaceAttr[j] = (FaceAttribute*)malloc(iAttrSize);
			if (NULL == ptData->ptFaceData[i]->ptFaceAttr[j])
			{
				CString cstrInfo;
				cstrInfo.Format("5���������������ڴ�ʧ��!");
				CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_FAIL, g_cstrFaceDevIP, cstrInfo, GetLastError());
				goto FREE_DATA;
			}
			memcpy(ptData->ptFaceData[i]->ptFaceAttr[j], ptTemp->ptFaceData[i]->ptFaceAttr[j], iAttrSize);
		}

		//��������Сͼ�����ڴ��Լ���������
		ptData->ptFaceData[i]->pcPicData = NULL;
		ptData->ptFaceData[i]->pcPicData = (char*)malloc(ptTemp->ptFaceData[i]->iDataLen);
		if (NULL == ptData->ptFaceData[i]->pcPicData)
		{
			CString cstrInfo;
			cstrInfo.Format("6����������Сͼ�����ڴ�ʧ��!");
			CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_FAIL, g_cstrFaceDevIP, cstrInfo, GetLastError());
			goto FREE_DATA;
		}
		memcpy(ptData->ptFaceData[i]->pcPicData, ptTemp->ptFaceData[i]->pcPicData, ptTemp->ptFaceData[i]->iDataLen);

		//ʱ���
		ptData->ptFaceData[i]->ullPts = ptTemp->ptFaceData[i]->ullPts;
		CString cstrDate;
		cstrDate.Format("ʱ�����index=%d, pts=%d.", i, ptTemp->ptFaceData[i]->ullPts);
		CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_MSG, g_cstrFaceDevIP, cstrDate, 0);

		//������ͼ
		if (FACE_ALARM_TYPE_BLACKLIST == ptTemp->ptFaceData[i]->iAlramType)
		{
			ptData->ptFaceData[i]->iSimilatity = ptTemp->ptFaceData[i]->iSimilatity;
			ptData->ptFaceData[i]->iLibKey = ptTemp->ptFaceData[i]->iLibKey;
			ptData->ptFaceData[i]->iFaceKey = ptTemp->ptFaceData[i]->iFaceKey;
			ptData->ptFaceData[i]->iNegPicLen = ptTemp->ptFaceData[i]->iNegPicLen;
			ptData->ptFaceData[i]->iNegPicType = ptTemp->ptFaceData[i]->iNegPicType;
			ptData->ptFaceData[i]->iSex = ptTemp->ptFaceData[i]->iSex;
			ptData->ptFaceData[i]->iPlace = ptTemp->ptFaceData[i]->iPlace;
			ptData->ptFaceData[i]->iCertType = ptTemp->ptFaceData[i]->iCertType;
			//strcpy_s(ptData->ptFaceData[i].cCertNum, ptTemp->ptFaceData[i].cCertNum, sizeof(ptData->ptFaceData[i].cCertNum));
			//strcpy_s(ptData->ptFaceData[i].cBirthTime, ptTemp->ptFaceData[i].cBirthTime, sizeof(ptData->ptFaceData[i].cBirthTime));
			//strcpy_s(ptData->ptFaceData[i].cName, ptTemp->ptFaceData[i].cName, sizeof(ptData->ptFaceData[i].cName));
			//strcpy_s(ptData->ptFaceData[i].cLibName, ptTemp->ptFaceData[i].cLibName, sizeof(ptData->ptFaceData[i].cLibName));
			if (ptData->ptFaceData[i]->iNegPicLen > 0)
			{
				ptData->ptFaceData[i]->pcNegPicData = NULL;
				ptData->ptFaceData[i]->pcNegPicData = (char*)malloc(ptData->ptFaceData[i]->iNegPicLen);
				if (NULL == ptData->ptFaceData[i]->pcNegPicData)
				{
					CString cstrInfo;
					cstrInfo.Format("7������������ͼ�����ڴ�ʧ��!");
					CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_FAIL, g_cstrFaceDevIP, cstrInfo, GetLastError());
					goto FREE_DATA;
				}
				memcpy(ptData->ptFaceData[i]->pcNegPicData, ptTemp->ptFaceData[i]->pcNegPicData, ptTemp->ptFaceData[i]->iNegPicLen);
			}
		}

	}

	char cTime[64] = {0};
	char cLog[1024] = {0};
	GetLocalTimeString(cTime);
	sprintf(cLog, "FacePicStream----DemoRecvTime(%s),PicTime(20%02d%02d%02d%02d%02d%02d%d)!\n", cTime
		, ptTemp->ptFullData->tPicTime.uiYear, ptTemp->ptFullData->tPicTime.uiMonth,  ptTemp->ptFullData->tPicTime.uiDay
		, ptTemp->ptFullData->tPicTime.uiHour, ptTemp->ptFullData->tPicTime.uiMinute, ptTemp->ptFullData->tPicTime.uiSecondsr, ptTemp->ptFullData->tPicTime.uiMilliseconds);
	OutputDebugString(cLog);

	EnterCriticalSection(&m_CriticalSec);
	m_lstPicData.push_back(ptData);
	LeaveCriticalSection(&m_CriticalSec);
	return;

FREE_DATA:
	FreePicData(ptData);
}

//���̴߳���ص������ݣ�����ͼƬ��ʾ���������յ������ݻ���������
DWORD WINAPI CFacePicStreamDemoDlg::DealDataThread(void* _pvPara)
{
	CFacePicStreamDemoDlg* pThis = (CFacePicStreamDemoDlg*)_pvPara;
	if (NULL != pThis)
	{
		pThis->DealPicData();
	}

	return 0;
}

void CFacePicStreamDemoDlg::DealPicData()
{
	while(m_bTermiThread)
	{
		Sleep(1);
		EnterCriticalSection(&m_CriticalSec);

		if (m_lstPicData.empty())
		{
			goto EXIT_FUNC;
		}

		FacePicStream* ptData = m_lstPicData.front();
		if (NULL == ptData)
		{
			goto EXIT_POP_LIST;
		}

		int iBigRet = DealFullPicData(ptData);     //�����ͼ����
		if (RET_SUCCESS != iBigRet)
		{
			goto EXIT_POP_LIST;
		}

		int iFaceRet = DealFacePicData(ptData);    //��������Сͼ����
		if(RET_SUCCESS != iFaceRet)
		{
			goto EXIT_POP_LIST;
		}

EXIT_POP_LIST:		
		m_lstPicData.pop_front();
		FreePicData(ptData);

EXIT_FUNC:	
		LeaveCriticalSection(&m_CriticalSec);
	}
}

void CFacePicStreamDemoDlg::FreePicData(FacePicStream* _ptData)
{
	if (NULL != _ptData)
	{
		if (NULL != _ptData->ptFullData)
		{
			if (NULL != _ptData->ptFullData->pcPicData)
			{
				free(_ptData->ptFullData->pcPicData);
				_ptData->ptFullData->pcPicData = NULL;
			}

			free(_ptData->ptFullData);
			_ptData->ptFullData = NULL;
		}

		for (int i = 0; i < _ptData->iFaceCount && i < MAX_FACE_PICTURE_COUNT; ++i)
		{
			if (NULL != _ptData->ptFaceData[i])
			{
				int iFaceAttrCount = min(_ptData->ptFaceData[i]->iFaceAttrCount, LEN_256);
				for (int j = 0; j < iFaceAttrCount; ++j)
				{
					if (NULL != _ptData->ptFaceData[i]->ptFaceAttr[j])
					{
						free(_ptData->ptFaceData[i]->ptFaceAttr[j]);
						_ptData->ptFaceData[i]->ptFaceAttr[j] = NULL;
					}
				}	

				if (NULL != _ptData->ptFaceData[i]->pcPicData)
				{
					free(_ptData->ptFaceData[i]->pcPicData);
					_ptData->ptFaceData[i]->pcPicData = NULL;
				}

				if (NULL != _ptData->ptFaceData[i]->pcNegPicData)
				{
					free(_ptData->ptFaceData[i]->pcNegPicData);
					_ptData->ptFaceData[i]->pcNegPicData = NULL;
				}

				free(_ptData->ptFaceData[i]);
				_ptData->ptFaceData[i] = NULL;
			}
	
		}

		free(_ptData);
		_ptData = NULL;
	}
}

//�����ͼ����
int CFacePicStreamDemoDlg::DealFullPicData(FacePicStream* _ptData)      
{	
	if (NULL == _ptData)
	{
		CString cstrInfo;
		cstrInfo.Format("[DealFullPicData] �б�����Ϊ��1");
		CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_FAIL, g_cstrFaceDevIP, cstrInfo, GetLastError());
		return RET_FAILED;
	}

	if (NULL == _ptData->ptFullData)
	{
		CString cstrInfo;
		cstrInfo.Format("[DealFullPicData] �б�����Ϊ��2");
		CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_FAIL, g_cstrFaceDevIP, cstrInfo, GetLastError());
		return RET_FAILED;
	}

	int iRet = ShowPicture(&m_staticBigPic, _ptData->ptFullData->iDataLen, (unsigned char*)(_ptData->ptFullData->pcPicData));
	return iRet;
}

//��������Сͼ����
int CFacePicStreamDemoDlg::DealFacePicData(FacePicStream* _ptData)     
{
	int iRet = RET_FAILED;
	if (NULL == _ptData)
	{
		CString cstrInfo;
		cstrInfo.Format("[DealFacePicData] �б�����Ϊ��");
		CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_FAIL, g_cstrFaceDevIP, cstrInfo, GetLastError());
		return RET_FAILED;
	}

	PicTime* ptPicTime = &(_ptData->ptFullData->tPicTime);
	for (int iFaceIndex = 0; iFaceIndex < _ptData->iFaceCount && iFaceIndex  < MAX_FACE_PICTURE_COUNT; iFaceIndex++)
	{
		if (NULL == _ptData->ptFaceData[iFaceIndex])
		{
			continue;
		}

		if (_ptData->ptFaceData[iFaceIndex]->iDataLen <= 0)
		{
			continue;
		}

		CString cstrInfo;
		cstrInfo.Format("Face[%d]ͼƬ����(%d),TotalFaceCount(%d),Time(20%02d%02d%02d%02d%02d%02d%d)", iFaceIndex, _ptData->ptFaceData[iFaceIndex]->iDataLen, _ptData->iFaceCount
			, ptPicTime->uiYear, ptPicTime->uiMonth,  ptPicTime->uiDay,  ptPicTime->uiHour,  ptPicTime->uiMinute,  ptPicTime->uiSecondsr,  ptPicTime->uiMilliseconds);
		CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_SUCC, g_cstrFaceDevIP, cstrInfo, GetLastError());	

		m_iFaceIndex++;
		m_iFaceIndex = (m_iFaceIndex < 0) ? 0 : m_iFaceIndex;
		switch((int)(m_cboSnapNum.GetItemData(m_cboSnapNum.GetCurSel())))
		{
		case ROW_ONE:
			m_iFaceIndex = m_iFaceIndex % WIDTH_ROWS;
			//if (0 == m_iFaceIndex)
			//{
			//	int iDrawOneRet = DrawBackGround();
			//	if (RET_SUCCESS != iDrawOneRet)
			//	{
			//		CString cstrInfo;
			//		cstrInfo.Format("[DealFacePicData]��������һ��Сͼ����ʧ��");
			//		CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_SUCC, g_cstrFaceDevIP, cstrInfo, GetLastError());
			//	}
			//}
			break;
		case ROW_TWO:
			m_iFaceIndex = m_iFaceIndex % MAX_ROW_TWO_WINDOWS;
			//if (0 == m_iFaceIndex)
			//{
			//	int iDrawTwoRet = DrawBackGround();
			//	if (RET_SUCCESS != iDrawTwoRet)
			//	{
			//		CString cstrInfo;
			//		cstrInfo.Format("[DealFacePicData]������������Сͼ����ʧ��");
			//		CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_SUCC, g_cstrFaceDevIP, cstrInfo, GetLastError());
			//	}
			//}
			break;
		case ROW_THREE:
			m_iFaceIndex = m_iFaceIndex % MAX_SNAP_NUM;
			//if(0 == m_iFaceIndex)
			//{
			//	int iDrawThreeRet = DrawBackGround();
			//	if (RET_SUCCESS != iDrawThreeRet)
			//	{
			//		CString cstrInfo;
			//		cstrInfo.Format("[DealFacePicData]������������Сͼ����ʧ��");
			//		CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_SUCC, g_cstrFaceDevIP, cstrInfo, GetLastError());
			//	}
			//}
			break;
		default:
			break;
		}

		m_iFaceIndex = (m_iFaceIndex < MAX_SNAP_NUM) ? m_iFaceIndex : 0;
		iRet = ShowPicture(m_pDlgPicPanel[m_iFaceIndex], _ptData->ptFaceData[iFaceIndex]->iDataLen, (unsigned char*)(_ptData->ptFaceData[iFaceIndex]->pcPicData));
		if (RET_SUCCESS != iRet)
		{
			goto EXIT;
		}
		if (m_iSaveFacePicCount < MAX_SNAP_FACEPIC_NUM)	//����20000������Сͼ
		{
			CString cstrPath = GetSaveFacePicName(_ptData, iFaceIndex, _ptData->ptFaceData[iFaceIndex]->iAlramType);
			iRet = SavePicture(_ptData->ptFaceData[iFaceIndex]->iDataLen, (unsigned char*)(_ptData->ptFaceData[iFaceIndex]->pcPicData), cstrPath);
			if (RET_SUCCESS != iRet)
			{
				goto EXIT;
			}
			if (MAX_SNAP_FACEPIC_NUM == m_iSaveFacePicCount)
			{
				CString cstrInfo;
				cstrInfo.Format("[DealFacePicData]����ͼ�񱣴�����20000��");
				CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_FAIL, g_cstrFaceDevIP, cstrInfo, GetLastError());
			}

			//����������ͼ
			FacePicData tFace = *_ptData->ptFaceData[iFaceIndex];
			if (FACE_ALARM_TYPE_BLACKLIST == tFace.iAlramType && NULL != tFace.pcNegPicData)
			{
				CString cstrNegPath;
				cstrNegPath.Format("%s-S%dLK%dFK%d.jpg", cstrPath.Left(cstrPath.GetLength() - 4), tFace.iSimilatity, tFace.iLibKey, tFace.iFaceKey);
				SavePicture(tFace.iNegPicLen, (unsigned char*)(tFace.pcNegPicData), cstrNegPath);
			}
		}
	}

EXIT:
	return iRet;
}

int CFacePicStreamDemoDlg::DrawBackGround()
{
	for (int iDrawIndex = 0; iDrawIndex < MAX_SNAP_NUM; iDrawIndex++)
	{
		m_pDlgPicPanel[iDrawIndex]->m_iISDrawBlack = IS_DROW;
		m_pDlgPicPanel[iDrawIndex]->RedrawWindow();
	}

	return RET_SUCCESS;
}

//��ͼƬ������ʾ��������
int CFacePicStreamDemoDlg::ShowPicture(CWnd* _pDlgWindow, int _DataLen, unsigned char* _pucPicData)
{
	int iRet = RET_FAILED;
	IStream *pStm = NULL;
	IPicture *pPic = NULL;
	HGLOBAL hGlobal = NULL;
	CDC* pDC = NULL;
	RECT rtWnd = {0};
	OLE_XSIZE_HIMETRIC hmWidth = 0;
	OLE_YSIZE_HIMETRIC hmHeight = 0;
	if (NULL == _pDlgWindow)
	{
		OutputDebugString("NULL == _pDlgWindow!\n");
		goto EXIT;
	}

	if (NULL ==  _pucPicData)
	{
		OutputDebugString("NULL ==  _pucPicData!\n");
		goto EXIT;
	}

	if (0 == _DataLen)
	{
		OutputDebugString("0 == _DataLen!\n");
		goto EXIT;
	}

	hGlobal = GlobalAlloc(GMEM_MOVEABLE, (unsigned int)_DataLen);//�����ļ���С�����ڴ�ռ䣬�ǵ��ͷ��ڴ�
	if (NULL == hGlobal)
	{
		OutputDebugString("NULL == hGlobal!\n");
		goto EXIT;
	}

	LPVOID pvData = NULL;  //�����ղŷ�����ڴ�ռ�
	pvData = GlobalLock(hGlobal);
	if (NULL == pvData)
	{
		OutputDebugString("NULL == pvData!\n");
		goto EXIT;
	}

	//���ļ��ŵ�����
	memcpy(pvData, _pucPicData, _DataLen);
	GlobalUnlock(hGlobal);
	CreateStreamOnHGlobal(hGlobal, TRUE, &pStm);

	//�����м���ͼƬ
	if(OleLoadPicture(pStm,(LONG)_DataLen,TRUE,IID_IPicture,(LPVOID*)&pPic) != S_OK)
	{
		OutputDebugString("OleLoadPicture fail!\n");
		goto EXIT;
	}

	pPic->get_Width(&hmWidth);
	pPic->get_Height(&hmHeight);

	//ʹ��render������ʾͼƬ
	_pDlgWindow->GetWindowRect(&rtWnd);
	int iWndWidth = rtWnd.right - rtWnd.left;
	int iWndHeight = rtWnd.bottom - rtWnd.top;
	pDC = _pDlgWindow->GetDC(); 
	if (NULL == pDC)
	{
		OutputDebugString("NULL == pDC!\n");
		goto EXIT;
	}

	if(FAILED(pPic->Render(*pDC, 0, 0, iWndWidth, iWndHeight, 0, hmHeight, hmWidth, -hmHeight, NULL)))
	{
		OutputDebugString("Render fail!\n");
		goto EXIT;
	}

	iRet = RET_SUCCESS;

EXIT:
	if (NULL != pPic)
	{
		pPic->Release();
		pPic = NULL;
	}
	if (NULL != pStm)
	{
		pStm->Release();
		pStm = NULL;
	}
	if (NULL != pDC)
	{
		ReleaseDC(pDC);
		pDC = NULL;
	}
	if (NULL != hGlobal)
	{
		GlobalFree(hGlobal);
		hGlobal = NULL;
	}
	return iRet;
}

//��ͼƬ���ݱ��浽����
int CFacePicStreamDemoDlg::SavePicture(int _DataLen, unsigned char* _pucPicData, CString _strPicName)
{
	int iRet = RET_SUCCESS;
	if (NULL == _pucPicData)
	{
		return RET_FAILED;
	}

	FILE* fpPicStream = fopen((LPSTR)(LPCSTR)_strPicName, "wb");
	if(NULL == fpPicStream)
	{
		CString cstrInfo;
		cstrInfo.Format("���ļ�ʧ��(%s)!", _strPicName);
		CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_FAIL, g_cstrFaceDevIP, cstrInfo, GetLastError());
		iRet = RET_FAILED;
		goto EXIT;
	}

	if(_DataLen >= 0)
	{
		size_t iWriLen = fwrite(_pucPicData, _DataLen, 1, fpPicStream);
		if (iWriLen <= 0)
		{
			OutputDebugString("����д����ʧ��!");
		}
		fflush(fpPicStream);
	}

	fclose(fpPicStream);
	fpPicStream = NULL;

	char cTime[64] = {0};
	char cLog[1024] = {0};
	GetLocalTimeString(cTime);
	sprintf(cLog, "FacePicStream----SaveTime(%s),PicName(%s)!\n", cTime, _strPicName);
	OutputDebugString(cLog);

EXIT:	
	return iRet;
}

int CFacePicStreamDemoDlg::CloseThread()
{
	if(NULL != m_hThread)
	{
		m_bTermiThread = false;
		DWORD dwRet = WaitForSingleObject(m_hThread, INFINITE);  //INFINITE
		if(dwRet != WAIT_OBJECT_0)
		{
			TerminateThread(m_hThread, 0);
		}
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}
	return 0;
}

void CFacePicStreamDemoDlg::OnBnClickedRadioDirectMode()
{
	m_RdoDirectMode.SetCheck(BST_CHECKED);
	m_RdoActiveMode.SetCheck(BST_UNCHECKED);
	GetDlgItem(IDC_STATIC_DEV_IP)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_IPADDRESS_DEV_IP)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_DEV_PORT)->SetWindowText("ͨ�Ŷ˿�:");
	SetDlgItemText(IDC_EDIT_DEV_PORT, "3000");
	GetDlgItem(IDC_STATIC_FACTORY_ID)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_FACTORY_ID)->ShowWindow(SW_HIDE);
	m_iConnetMode = SERVER_NORMAL;
}

void CFacePicStreamDemoDlg::OnBnClickedRadioActiveMode()
{
	m_RdoDirectMode.SetCheck(BST_UNCHECKED);
	m_RdoActiveMode.SetCheck(BST_CHECKED);
	GetDlgItem(IDC_STATIC_DEV_IP)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_IPADDRESS_DEV_IP)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_DEV_PORT)->SetWindowText("�����˿�:");
	SetDlgItemText(IDC_EDIT_DEV_PORT, "6005");
	GetDlgItem(IDC_STATIC_FACTORY_ID)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_FACTORY_ID)->ShowWindow(SW_SHOW);
	m_iConnetMode = SERVER_ACTIVE;
}

CString CFacePicStreamDemoDlg::GetSaveFacePicName(FacePicStream* _ptData, int _iFaceIndex, int _iAlaramType)
{
	CString cstrFacePicName;
	if (NULL == _ptData || _iFaceIndex < 0 || _iFaceIndex >= MAX_FACE_PICTURE_COUNT) 
	{
		return cstrFacePicName;
	}
	PicTime& tPicTime = _ptData->ptFullData->tPicTime;
	FacePicData* ptFaceInfo = _ptData->ptFaceData[_iFaceIndex];
	if (NULL == ptFaceInfo)
	{
		return cstrFacePicName;
	}

	CString cstrBase = ".\\PicStream";
	if (FACE_ALARM_TYPE_BLACKLIST == _iAlaramType)
	{
		cstrBase = ".\\Recognize";
	}

	if (_access(cstrBase, 0) == -1)
	{
		//	Ŀ¼�������򴴽�֮
		int iRet = _mkdir(cstrBase);
		if (iRet != 0)
		{
			CString cstrInfo;
			cstrInfo.Format("�����洢Ŀ¼ʧ��!");
			CLS_LogManager::GetInstance()->AddLog(LOG_TYPE_FAIL, g_cstrFaceDevIP, cstrInfo, GetLastError());
			iRet = RET_FAILED;
			goto EXIT_FUNC;
		}
	}

	//�������ʱ����Ϣ
	cstrFacePicName.Format("%s\\FacePic%d_2%03d%02d%02d%02d%02d%02d%d_%d_%d",  cstrBase, m_iSaveFacePicCount++
		, tPicTime.uiYear, tPicTime.uiMonth,  tPicTime.uiDay, tPicTime.uiHour,  tPicTime.uiMinute,  tPicTime.uiSecondsr,  tPicTime.uiMilliseconds 
		, ptFaceInfo->iFaceLevel
		, ptFaceInfo->iFaceId);//���������

	//���������Ϣ
	int iAttrCpySize = min(ptFaceInfo->iFaceAttrStructSize, (int)sizeof(FaceAttribute));
	if (iAttrCpySize < 0)
	{
		goto EXIT_FUNC;
	}

	for (int i = 0; i < ptFaceInfo->iFaceAttrCount && i < LEN_256; i++)
	{
		if (NULL == ptFaceInfo->ptFaceAttr[i])
		{
			continue;
		}

		FaceAttribute tAttr = {0};
		memcpy(&tAttr, ptFaceInfo->ptFaceAttr[i], iAttrCpySize);
		if (FACE_ATTR_12 == tAttr.iType
			|| FACE_ATTR_13 == tAttr.iType
			|| FACE_ATTR_14 == tAttr.iType
			|| FACE_ATTR_15 == tAttr.iType
			||  FACE_ATTR_16 == tAttr.iType)
		{
			continue;
		}
		cstrFacePicName += _T("_") + GetFaceAttrInfoName(tAttr.iType, tAttr.iValue);  
	}

EXIT_FUNC:
	cstrFacePicName += _T(".jpg");
	return cstrFacePicName;
}
