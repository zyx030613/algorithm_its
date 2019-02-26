// DomeState.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "DomeState.h"

#define NORMAL_STATE	0
#define FAIL_STATE		1
#define NORMAL	"Normal"
#define FAIL	"Not Normal"

// CLS_DomeState dialog

IMPLEMENT_DYNAMIC(CLS_DomeState, CDialog)

CLS_DomeState::CLS_DomeState(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DomeState::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
	m_iStreamNO = 0;
}

CLS_DomeState::~CLS_DomeState()
{
}

void CLS_DomeState::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CAMERA_STATE, m_edtCameraState);
	DDX_Control(pDX, IDC_EDIT_HLimit, m_edtHLimit);
	DDX_Control(pDX, IDC_EDIT_VLimit, m_edtVLimit);
	DDX_Control(pDX, IDC_EDIT_Interface, m_edtInterface);
	DDX_Control(pDX, IDC_EDIT_TSensor, m_edtTmpSensor);
	DDX_Control(pDX, IDC_EDIT_Temp, m_edtTemperature);
	DDX_Control(pDX, IDC_EDIT_TempScale, m_edtTmpScale);
	DDX_Control(pDX, IDC_EDIT_PublishData, m_edtPublishDate);
}


BEGIN_MESSAGE_MAP(CLS_DomeState, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ASK_DOME_STATE, &CLS_DomeState::OnBnClickedButtonAskDomeState)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CLS_DomeState message handlers

BOOL CLS_DomeState::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();
	UI_UpdateDialog();
	UpdatePageUI();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_DomeState::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	m_iLogonID = _iLogonID;

	if (_iChannelNo < 0)
	{
		m_iChannelNo = 0;
	}
	else
	{
		m_iChannelNo = _iChannelNo;
	}

	if (_iStreamNo < 0)
	{
		m_iStreamNO = 0;
	}
	else
	{
		m_iStreamNO =  _iStreamNo;
	}
}

void CLS_DomeState::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialog();
	UpdatePageUI();
}

void CLS_DomeState::UpdatePageUI()
{
	if (m_iLogonID == -1 || m_iChannelNo == -1)
	{
		return;
	}

	TSystemState str = {0};
	TSystemState* pstrTSystemState = &str;
	pstrTSystemState->iSize = sizeof(TSystemState);

	int iRet = NetClient_GetDeviceState(m_iLogonID, m_iChannelNo, DEVICE_STATE_SYSTEM ,(int*)(pstrTSystemState));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DomeState::NetClient_GetDeviceState] Get fail,error = %d", GetLastError());
	}
	else
	{
		if (NORMAL_STATE == pstrTSystemState->iCamera)
		{
			SetDlgItemTextEx(IDC_EDIT_CAMERA_STATE, IDS_NORMAL);
		} 
		else
		{
			SetDlgItemTextEx(IDC_EDIT_CAMERA_STATE, IDS_ABNORMAL);
		}

		if (NORMAL_STATE == pstrTSystemState->iHLimit)
		{
			SetDlgItemTextEx(IDC_EDIT_HLimit, IDS_NORMAL);
		}
		else
		{
			SetDlgItemTextEx(IDC_EDIT_HLimit, IDS_ABNORMAL);
		}

		if (NORMAL_STATE == pstrTSystemState->iVLimit)
		{		
			SetDlgItemTextEx(IDC_EDIT_VLimit, IDS_NORMAL);
		} 
		else
		{
			SetDlgItemTextEx(IDC_EDIT_VLimit, IDS_ABNORMAL);
		}

		if (NORMAL_STATE == pstrTSystemState->iInterface)
		{
			SetDlgItemTextEx(IDC_EDIT_Interface, IDS_NORMAL);
		} 
		else
		{
			SetDlgItemTextEx(IDC_EDIT_Interface, IDS_ABNORMAL);
		}

		if (NORMAL_STATE == pstrTSystemState->iTSensor)
		{
			SetDlgItemTextEx(IDC_EDIT_TSensor, IDS_NORMAL);
		} 
		else
		{
			SetDlgItemTextEx(IDC_EDIT_TSensor, IDS_ABNORMAL);
		}

		int iTemperature = pstrTSystemState->temperature;
		SetDlgItemInt(IDC_EDIT_Temp, iTemperature);

		if (0 == pstrTSystemState->itemperatureScale)
		{
			m_edtTmpScale.SetWindowText(GetTextEx(IDS_Centigrade));
		}
		else if (1 == pstrTSystemState->itemperatureScale)
		{
			m_edtTmpScale.SetWindowText(GetTextEx(IDS_Fahrenheit));
		} 
		else
		{
			m_edtTmpScale.SetWindowText(GetTextEx(IDS_Kelvin));
		}

		CString strPublishDate;
		strPublishDate.Format("%d:%d:%d:%d:%d:%d", pstrTSystemState->strPublishData.iYear
			, pstrTSystemState->strPublishData.iMonth, pstrTSystemState->strPublishData.iDay
			, pstrTSystemState->strPublishData.iHour, pstrTSystemState->strPublishData.iMinute
			, pstrTSystemState->strPublishData.iSecond);
		m_edtPublishDate.SetWindowText(strPublishDate);
	}
}

void CLS_DomeState::OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData)
{
	switch(_iParaType)
	{
	case PARA_DOME_SYETEM:
		UpdatePageUI();
		break;
	default:
		break;
	}
}

void CLS_DomeState::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_PublishData, IDS_PUBILSH_DATE);
	SetDlgItemTextEx(IDC_STATIC_CAMERA_STATE, IDS_CAMERA_STATUS);
	SetDlgItemTextEx(IDC_STATIC_HLimit, IDS_LEVEL_LIMIT);
	SetDlgItemTextEx(IDC_STATIC_VLimit, IDS_VERTICAL_LIMIT);
	SetDlgItemTextEx(IDC_STATIC_INTERFACE, IDS_INTERFACE);
	SetDlgItemTextEx(IDC_STATIC_TSensor, IDS_SENSOR);
	SetDlgItemTextEx(IDC_STATIC_TEMP, IDS_TEMPERATURE);
	SetDlgItemTextEx(IDC_BUTTON_ASK_DOME_STATE, IDS_DOME_STATUS_INFO);
}

void CLS_DomeState::OnBnClickedButtonAskDomeState()
{
	// TODO: Add your control notification handler code here
	int iRet = NetClient_CheckDeviceState(m_iLogonID, m_iChannelNo, DEVICE_STATE_SYSTEM);
	if (iRet<0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DomeState::OnBnClickedButtonAskDomeState]NetClient_CheckDeviceState(LogonID=%d,ChanNo=%d)", m_iLogonID, m_iChannelNo);
	}
}

void CLS_DomeState::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
	UpdatePageUI();
}
