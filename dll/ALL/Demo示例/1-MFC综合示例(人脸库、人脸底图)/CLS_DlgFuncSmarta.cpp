// CLS_DlgFuncSmarta.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "CLS_DlgFuncSmarta.h"


// CLS_DlgFuncSmarta 对话框

IMPLEMENT_DYNAMIC(CLS_DlgFuncSmarta, CDialog)

CLS_DlgFuncSmarta::CLS_DlgFuncSmarta(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DlgFuncSmarta::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = -1;
	m_iStreamNo = -1;
}

CLS_DlgFuncSmarta::~CLS_DlgFuncSmarta()
{
}

void CLS_DlgFuncSmarta::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLS_DlgFuncSmarta, CDialog)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

BOOL CLS_DlgFuncSmarta::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	for (int i = IDC_CHK_FUNC_ONELINE; i <= IDC_CHK_FUNC_FAIGHTING; i++)
	{
		GetDlgItem(i)->EnableWindow(FALSE);
	}
	return TRUE;
}

void CLS_DlgFuncSmarta::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);
	if (bShow)
	{
		InitDialogItemText();
		GetFuncSmartAnalyze();
	}
}

void CLS_DlgFuncSmarta::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	if (m_iLogonID == _iLogonID && m_iChannelNo == _iChannelNo && m_iStreamNo == _iStreamNo)
	{
		return;
	}

	m_iLogonID = _iLogonID;
	m_iChannelNo = _iChannelNo;
	m_iStreamNo = _iStreamNo;
	GetFuncSmartAnalyze();
}

void CLS_DlgFuncSmarta::OnLanguageChanged( int _iLanguage )
{
	InitDialogItemText();
}

void CLS_DlgFuncSmarta::GetFuncSmartAnalyze()
{
	for (int i = 0; i <= 21; i++)
	{
		((CButton*)GetDlgItem(i + IDC_CHK_FUNC_ONELINE))->SetCheck(FALSE);
	}

	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DlgFuncSmarta::GetFuncSmartAnalyze] Error  LogonID!");
		return;
	}
	int iByteReturn = -1;
	FuncAbilityLevel stFunAbilityLevel = {0};
	stFunAbilityLevel.iSize = sizeof(stFunAbilityLevel);
	stFunAbilityLevel.iMainFuncType = MAIN_FUNC_TYPE_VCA;
	stFunAbilityLevel.iSubFuncType = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_GET_FUNC_ABILITY, m_iChannelNo, (void*)&stFunAbilityLevel, sizeof(stFunAbilityLevel), &iByteReturn);
	if (iRet < 0 || strlen(stFunAbilityLevel.cParam) < 1)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_DlgFuncSmarta::GetFuncSmartAnalyze] GetDevConfig NET_CLIENT_GET_FUNC_ABILITY Failed! m_iLogonID %d", m_iLogonID);
		return;
	}
	CString csSmartAnalyzeTempParam = stFunAbilityLevel.cParam;
	int iAnalyzeTempParam = _ttoi(csSmartAnalyzeTempParam);
	for (int i = 0; i <= 21; i++)
	{
		BOOL blTempChk = (iAnalyzeTempParam & 0x01<<i)?TRUE:FALSE;
		((CButton*)GetDlgItem(i + IDC_CHK_FUNC_ONELINE))->SetCheck(blTempChk);
	}
}

void CLS_DlgFuncSmarta::InitDialogItemText()
{
	SetDlgItemTextEx(IDD_DLG_CFG_FUNC_SMARTA    ,	IDS_CONFIG_DVR_VCA );
	SetDlgItemTextEx(IDC_GPO_FUNC_DSTGROUPSET   ,	IDS_CFG_FUNC_TARGETBOX );
	SetDlgItemTextEx(IDC_CHK_FUNC_ONELINE       ,	IDS_VCA_TRIPWIRE_EX );
	SetDlgItemTextEx(IDC_CHK_FUNC_TWOLINE       ,	IDS_VCA_ALARM_EVENT_DBTRIPWIRE );
	SetDlgItemTextEx(IDC_CHK_FUNC_CHKAROUND     ,	IDS_VCA_ALARM_EVENT_PERIMETER );
	SetDlgItemTextEx(IDC_CHK_FUNC_HOVER         ,	IDS_VCA_ALARM_EVENT_LOITER );
	SetDlgItemTextEx(IDC_CHK_FUNC_CARSTOP       ,	IDS_VCA_ALARM_EVENT_PARKING );
	SetDlgItemTextEx(IDC_CHK_FUNC_RUNNING       ,	IDS_VCA_ALARM_EVENT_RUN );
	SetDlgItemTextEx(IDC_CHK_FUNC_PEOPLEDENSITY ,	IDS_VCA_ALARM_EVENT_HIGH_DENSITY );
	SetDlgItemTextEx(IDC_CHK_FUNC_STOLEN        ,	IDS_CFG_FUNC_STOLEN );
	SetDlgItemTextEx(IDC_CHK_FUNC_LOST          ,	IDS_VCA_ALARM_EVENT_OBJSTOLEN );
	SetDlgItemTextEx(IDC_CHK_FUNC_FACEANALY     ,	IDS_VCA_ALARM_EVENT_FACEREC );
	SetDlgItemTextEx(IDC_CHK_FUNC_VIDEOCHK      ,	IDS_VCA_ALARM_EVENT_VIDEODETECT );
	SetDlgItemTextEx(IDC_CHK_FUNC_SMARTFALLOW   ,	IDS_VCA_ALARM_EVENT_TRACK );
	SetDlgItemTextEx(IDC_CHK_FUNC_FLOWSTA       ,	IDS_ITS_TRAFFIC_STATIS );
	SetDlgItemTextEx(IDC_CHK_FUNC_PEOPLEGROUP   ,	IDS_VCA_EVENT_CROWD_NEW );
	SetDlgItemTextEx(IDC_CHK_FUNC_OUTWORKER     ,	IDS_VCA_EVENT_LEAVE_DETECT );
	SetDlgItemTextEx(IDC_CHK_FUNC_WATERLEVEL    ,	IDS_CFG_FUNC_WATER_LEVEL );
	SetDlgItemTextEx(IDC_CHK_FUNC_AUDIOCHK      ,	IDS_VCA_EVENT_AUDIO_DIAGNOSE_NEW );
	SetDlgItemTextEx(IDC_CHK_FUNC_FACEMOSAIK    ,	IDS_CFG_FUNC_FACE_COVER );
	SetDlgItemTextEx(IDC_CHK_FUNC_RIVERFLOAT    ,	IDS_VCA_EVENT_RIVER );
	SetDlgItemTextEx(IDC_CHK_FUNC_STOLENORUNLOAD,	IDS_VCA_EVENT_DREDGE );
	SetDlgItemTextEx(IDC_CHK_FUNC_VIOLATECARSTOP,	IDS_CONFIG_ITS_ILLEGALPARK );
	SetDlgItemTextEx(IDC_CHK_FUNC_FAIGHTING     ,	IDS_VCA_EVENT_FIGHT );
}
