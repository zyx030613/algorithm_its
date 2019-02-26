// CLS_ECOPCapturePage.cpp : implementation file
//

#include "stdafx.h"
#include "ECOPCapturePage.h"


// CLS_ECOPCapturePage dialog

IMPLEMENT_DYNAMIC(CLS_ECOPCapturePage, CDialog)

CLS_ECOPCapturePage::CLS_ECOPCapturePage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ECOPCapturePage::IDD, pParent)
{
	m_iLogonID = -1;
}

CLS_ECOPCapturePage::~CLS_ECOPCapturePage()
{
}

void CLS_ECOPCapturePage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ROADWAYID, m_cboRoadwayID);
	DDX_Control(pDX, IDC_EDIT_CAPTURE_TYPE, m_edtCaptureType);
	DDX_Control(pDX, IDC_EDIT_FIRSTPLACE, m_edtFirstPlace);
	DDX_Control(pDX, IDC_EDIT_SECONDPLACE, m_edtSecondPlace);
	DDX_Control(pDX, IDC_EDIT_THIRDPLACE, m_edtThirdPlace);
	DDX_Control(pDX, IDC_BUTTON_CAPTURE, m_btnCapture);
}


BEGIN_MESSAGE_MAP(CLS_ECOPCapturePage, CLS_BasePage)
	ON_CBN_SELCHANGE(IDC_COMBO_ROADWAYID, &CLS_ECOPCapturePage::OnCbnSelchangeComboRoadwayid)
	ON_BN_CLICKED(IDC_BUTTON_CAPTURE, &CLS_ECOPCapturePage::OnBnClickedButtonCapture)
END_MESSAGE_MAP()


// CLS_ECOPCapturePage message handlers
BOOL CLS_ECOPCapturePage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	for (int i=0; i<4; i++)
	{
		CString strNo;
		strNo.Format("%d",i);
		m_cboRoadwayID.AddString(strNo);
	}
	m_cboRoadwayID.SetCurSel(0);

	m_edtFirstPlace.SetLimitText(63);
	m_edtSecondPlace.SetLimitText(63);
	m_edtThirdPlace.SetLimitText(63);

	UI_UpdateDialog();

	return TRUE;
}

void CLS_ECOPCapturePage::OnChannelChanged( int _iLogonID,int /*_iChannelNo*/,int /*_iStreamNo*/ )
{
	m_iLogonID = _iLogonID;

	UI_UpdateCapture();
}

void CLS_ECOPCapturePage::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_ECOPCapturePage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_ROADWAYID,IDS_CONFIG_ECOP_ROADWAYID);
	SetDlgItemTextEx(IDC_STATIC_CAPTURE,IDS_CONFIG_ECOP_CAPTURE);
	SetDlgItemTextEx(IDC_STATIC_CAPTURE_TYPE,IDS_CONFIG_ECOP_CAPTURE_TYPE);
	SetDlgItemTextEx(IDC_STATIC_FIRSTPLACE,IDS_CONFIG_ECOP_FIRSTPLACE);
	SetDlgItemTextEx(IDC_STATIC_SECONDPLACE,IDS_CONFIG_ECOP_SECONDPLACE);
	SetDlgItemTextEx(IDC_STATIC_THIRDPLACE,IDS_CONFIG_ECOP_THIRDPLACE);
	SetDlgItemTextEx(IDC_BUTTON_CAPTURE,IDS_SET);

}

BOOL CLS_ECOPCapturePage::UI_UpdateCapture()
{
	if (m_iLogonID < 0)
		return FALSE;

	TITSRoadwayCapture tCapture = {0};
	tCapture.iRoadwayID = m_cboRoadwayID.GetCurSel();
	int iRet = NetClient_GetITSRoadwayParam(m_iLogonID,ITS_ROADWAY_CMD_GET_CAPTURE,&tCapture,sizeof(tCapture));
	if (0 == iRet)
	{
		m_cboRoadwayID.SetCurSel(tCapture.iRoadwayID);
		SetDlgItemInt(IDC_EDIT_CAPTURE_TYPE, tCapture.iType);
		SetDlgItemText(IDC_EDIT_FIRSTPLACE, tCapture.cPlace[0]);
		SetDlgItemText(IDC_EDIT_SECONDPLACE, tCapture.cPlace[1]);
		SetDlgItemText(IDC_EDIT_THIRDPLACE, tCapture.cPlace[2]);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(tCapture));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(tCapture));
	}
	return TRUE;
}

void CLS_ECOPCapturePage::OnCbnSelchangeComboRoadwayid()
{
	UI_UpdateCapture();
}

void CLS_ECOPCapturePage::OnBnClickedButtonCapture()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	TITSRoadwayCapture tCapture = {0};
	tCapture.iRoadwayID = m_cboRoadwayID.GetCurSel();
	tCapture.iType = GetDlgItemInt(IDC_EDIT_CAPTURE_TYPE);
	GetDlgItemText(IDC_EDIT_FIRSTPLACE, tCapture.cPlace[0], 63);
	GetDlgItemText(IDC_EDIT_SECONDPLACE, tCapture.cPlace[1], 63);
	GetDlgItemText(IDC_EDIT_THIRDPLACE, tCapture.cPlace[2], 63);
	int iRet = NetClient_SetITSRoadwayParam(m_iLogonID,ITS_ROADWAY_CMD_SET_CAPTURE,&tCapture,sizeof(tCapture));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(tCapture));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(tCapture));
	}
}
