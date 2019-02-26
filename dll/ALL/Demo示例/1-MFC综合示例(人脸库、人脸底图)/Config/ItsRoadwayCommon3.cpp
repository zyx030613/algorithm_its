// CLS_ECOPCapturePage.cpp : implementation file
//

#include "stdafx.h"
#include "ItsRoadwayCommon3.h"


// CLS_ECOPCapturePage dialog

IMPLEMENT_DYNAMIC(CLS_ItsRoadwayCommon3, CDialog)

CLS_ItsRoadwayCommon3::CLS_ItsRoadwayCommon3(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ItsRoadwayCommon3::IDD, pParent)
{
	m_iLogonID = -1;
}

CLS_ItsRoadwayCommon3::~CLS_ItsRoadwayCommon3()
{
}

void CLS_ItsRoadwayCommon3::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ROADWAYID, m_cboRoadwayID);
	DDX_Control(pDX, IDC_EDIT_CAPTURE_TYPE, m_edtCaptureType);
	DDX_Control(pDX, IDC_EDIT_FIRSTPLACE, m_edtFirstPlace);
	DDX_Control(pDX, IDC_EDIT_SECONDPLACE, m_edtSecondPlace);
	DDX_Control(pDX, IDC_EDIT_THIRDPLACE, m_edtThirdPlace);
	DDX_Control(pDX, IDC_BUTTON_CAPTURE, m_btnCapture);
	DDX_Control(pDX, IDC_COMBO_COMNO, m_cboComNo);
	DDX_Control(pDX, IDC_EDIT_LIGHTID, m_edtLightID);
	DDX_Control(pDX, IDC_EDIT_FLOODID, m_edtFloodID);
	DDX_Control(pDX, IDC_CBO_FIRST_CAP_DELAY, m_cboFirstCapDelay);
	DDX_Control(pDX, IDC_CBO_SECOND_CAP_DELAY, m_cboSecondCapDelay);
	DDX_Control(pDX, IDC_CBO_THIRD_CAP_DELAY, m_cboThirdCapDelay);
	DDX_Control(pDX, IDC_CBO_FOURTH_CAP_DELAY, m_cboFourthCapDelay);
	DDX_Control(pDX, IDC_CBO_FIFTH_CAP_DELAY, m_cboFifthCapDelay);
	DDX_Control(pDX, IDC_CMB_FLASH_MODE, m_cboFlashModel);
	DDX_Control(pDX, IDC_CHECK_ROADWAYNO, m_chkRoadwayNo);
}


BEGIN_MESSAGE_MAP(CLS_ItsRoadwayCommon3, CLS_BasePage)
	ON_CBN_SELCHANGE(IDC_COMBO_ROADWAYID, &CLS_ItsRoadwayCommon3::OnCbnSelchangeComboRoadwayid)
	ON_BN_CLICKED(IDC_BUTTON_CAPTURE, &CLS_ItsRoadwayCommon3::OnBnClickedButtonCapture)
	ON_BN_CLICKED(IDC_BUTTON_CHNLIGHT, &CLS_ItsRoadwayCommon3::OnBnClickedButtonChnlight)
	ON_BN_CLICKED(IDC_BTN_CAP_DELAY, &CLS_ItsRoadwayCommon3::OnBnClickedBtnCapDelay)
	ON_BN_CLICKED(IDC_CHECK_ROADWAYNO, &CLS_ItsRoadwayCommon3::OnBnClickedCheckRoadwayno)
END_MESSAGE_MAP()


// CLS_ECOPCapturePage message handlers
BOOL CLS_ItsRoadwayCommon3::OnInitDialog()
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

	//lisht
	m_cboRoadwayID.SetCurSel(0);

	m_cboComNo.AddString("0--RS232");
	m_cboComNo.AddString("1--RS232");
	m_cboComNo.AddString("2--RS485");
	m_cboComNo.AddString("3");

	m_edtLightID.SetLimitText(13);
	m_edtFloodID.SetLimitText(31);
	//

	UI_UpdateDialog();

	return TRUE;
}

BOOL CLS_ItsRoadwayCommon3::UI_UpdateRoadway()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iRoadwayID = m_cboRoadwayID.GetCurSel();
	TITSRoadwayInfo pa = {0};
	pa.iRoadwayID = iRoadwayID;
	int iRet = NetClient_GetITSRoadwayParam(m_iLogonID, ITS_ROADWAY_CMD_GET_ENABLE, &pa, sizeof(pa));
	if (0 == iRet)
	{
		m_chkRoadwayNo.SetCheck(pa.iEnable?BST_CHECKED:BST_UNCHECKED);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pa));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pa));
	}
	return TRUE;
}

void CLS_ItsRoadwayCommon3::OnChannelChanged( int _iLogonID,int /*_iChannelNo*/,int /*_iStreamNo*/ )
{
	m_iLogonID = _iLogonID;

	UI_UpdateCapture();
	UI_UpdateChnLight();
	UI_UpdateCapDelay();
	UI_UpdateRoadway();
}

void CLS_ItsRoadwayCommon3::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_ItsRoadwayCommon3::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_ROADWAYID,IDS_CONFIG_ECOP_ROADWAYID);
	SetDlgItemTextEx(IDC_STATIC_CAPTURE,IDS_ITS_COMMON3);
	SetDlgItemTextEx(IDC_CHECK_ROADWAYNO,IDS_CONFIG_ITS_ROADWAY_ENABLE);
	SetDlgItemTextEx(IDC_STATIC_CAPTURE_TYPE,IDS_CONFIG_ECOP_CAPTURE_TYPE);
	SetDlgItemTextEx(IDC_STATIC_FIRSTPLACE,IDS_CONFIG_ECOP_FIRSTPLACE);
	SetDlgItemTextEx(IDC_STATIC_SECONDPLACE,IDS_CONFIG_ECOP_SECONDPLACE);
	SetDlgItemTextEx(IDC_STATIC_THIRDPLACE,IDS_CONFIG_ECOP_THIRDPLACE);
	SetDlgItemTextEx(IDC_BUTTON_CAPTURE,IDS_SET);

	SetDlgItemTextEx(IDC_STATIC_CHNLIGHT,IDS_CONFIG_ECOP_CHNLIGHT);
	SetDlgItemTextEx(IDC_STATIC_COMNO,IDS_CONFIG_ECOP_COMNO);
	SetDlgItemTextEx(IDC_STATIC_LIGHTID,IDS_CONFIG_ECOP_LIGHTID);
	SetDlgItemTextEx(IDC_STATIC_FLOODID,IDS_CONFIG_ECOP_FLOADID);
	SetDlgItemTextEx(IDC_BUTTON_CHNLIGHT,IDS_SET);
	SetDlgItemTextEx(IDC_CHK_FORCE_RED,IDS_ITS_FORCE_RED);
	SetDlgItemTextEx(IDC_STA_FLASH_MODE,IDS_ITS_FLASH_MODE);

	SetDlgItemTextEx(IDC_STC_FIRST_CAP_DELAY,IDS_ITS_FIRST_CAP_DELAY);
	SetDlgItemTextEx(IDC_STC_SECOND_CAP_DELAY,IDS_ITS_SECOND_CAP_DELAY);
	SetDlgItemTextEx(IDC_STC_THIRD_CAP_DELAY,IDS_ITS_THIRD_CAP_DELAY);
	SetDlgItemTextEx(IDC_STC_FOURTH_CAP_DELAY,IDS_ITS_FOURTH_CAP_DELAY);
	SetDlgItemTextEx(IDC_STC_FIFTH_CAP_DELAY,IDS_ITS_FIFTH_CAP_DELAY);
	SetDlgItemTextEx(IDC_BTN_CAP_DELAY,IDS_SET);
	SetDlgItemTextEx(IDC_STC_DELAY_CAP, IDS_ITS_DELAY_CAPTURE);
	//
	InsertString(m_cboFirstCapDelay, 0, IDS_DISTANCE);
	InsertString(m_cboFirstCapDelay, 1, IDS_CONFIG_ITS_TIME);
	//
	InsertString(m_cboSecondCapDelay, 0, IDS_DISTANCE);
	InsertString(m_cboSecondCapDelay, 1, IDS_CONFIG_ITS_TIME);
	//
	InsertString(m_cboThirdCapDelay, 0, IDS_DISTANCE);
	InsertString(m_cboThirdCapDelay, 1, IDS_CONFIG_ITS_TIME);
	//
	InsertString(m_cboFourthCapDelay, 0, IDS_DISTANCE);
	InsertString(m_cboFourthCapDelay, 1, IDS_CONFIG_ITS_TIME);
	//
	InsertString(m_cboFifthCapDelay, 0, IDS_DISTANCE);
	InsertString(m_cboFifthCapDelay, 1, IDS_CONFIG_ITS_TIME);
	//
	InsertString(m_cboFlashModel,0,IDS_ITS_RELECANCE);
	InsertString(m_cboFlashModel,1,IDS_ITS_TURN);
}

BOOL CLS_ItsRoadwayCommon3::UI_UpdateCapture()
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

void CLS_ItsRoadwayCommon3::OnCbnSelchangeComboRoadwayid()
{
	UI_UpdateCapture();
	UI_UpdateChnLight();
	UI_UpdateCapDelay();
	UI_UpdateRoadway();
}

void CLS_ItsRoadwayCommon3::OnBnClickedButtonCapture()
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
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSRoadwayParam[ITS_ROADWAY_CMD_SET_CAPTURE] (%d)", m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSRoadwayParam[ITS_ROADWAY_CMD_SET_CAPTURE] (%d) error(%d)", m_iLogonID, GetLastError());
	}
}

void CLS_ItsRoadwayCommon3::OnBnClickedButtonChnlight()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	TITSRoadwayLight_V1 tLight = {0};
	tLight.m_stLight.iRoadwayID= m_cboRoadwayID.GetCurSel();
	tLight.m_stLight.iComNo = m_cboComNo.GetCurSel();
	tLight.m_stLight.iFloodID = GetDlgItemInt(IDC_EDIT_FLOODID);
	GetDlgItemText(IDC_EDIT_LIGHTID, tLight.m_stLight.cLightID, 31);
	tLight.iFlashLampType = m_cboFlashModel.GetCurSel();
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHK_FORCE_RED);
	if(NULL != pBtn)
	{
		tLight.m_iCompelRedlight = pBtn->GetCheck();
	}	
	int iRet = NetClient_SetITSRoadwayParam(m_iLogonID,ITS_ROADWAY_CMD_SET_LIGHT,&tLight,sizeof(tLight));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSRoadwayParam[ITS_ROADWAY_CMD_SET_LIGHT](%d)", m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSRoadwayParam[ITS_ROADWAY_CMD_SET_LIGHT](%d),error(%d)", m_iLogonID, GetLastError());
	}
}

void CLS_ItsRoadwayCommon3::UI_UpdateChnLight()
{
	if (m_iLogonID < 0)
		return;

	TITSRoadwayLight_V1 tLight = {0};
	tLight.m_stLight.iRoadwayID = m_cboRoadwayID.GetCurSel();
	int iRet = NetClient_GetITSRoadwayParam(m_iLogonID,ITS_ROADWAY_CMD_GET_LIGHT,&tLight,sizeof(tLight));
	if (0 == iRet)
	{
		m_cboRoadwayID.SetCurSel(tLight.m_stLight.iRoadwayID);
		m_cboComNo.SetCurSel(tLight.m_stLight.iComNo);
		SetDlgItemInt(IDC_EDIT_FLOODID, tLight.m_stLight.iFloodID);
		SetDlgItemText(IDC_EDIT_LIGHTID, tLight.m_stLight.cLightID);
		m_cboFlashModel.SetCurSel(tLight.iFlashLampType);
		CButton* pBtn = (CButton*)GetDlgItem(IDC_CHK_FORCE_RED);
		if(NULL != pBtn)
		{
			pBtn->SetCheck(tLight.m_iCompelRedlight);
		}
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSRoadwayParam[ITS_ROADWAY_CMD_GET_LIGHT] (%d)",m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSRoadwayParam[ITS_ROADWAY_CMD_GET_LIGHT] (%d) error(%d)",m_iLogonID, GetLastError());
	}
	return;
}

void CLS_ItsRoadwayCommon3::OnBnClickedBtnCapDelay()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	TITSRoadwayDelayDistance tParam = {0};
	tParam.iSize = sizeof(TITSRoadwayDelayDistance);
	tParam.iLaneId = m_cboRoadwayID.GetCurSel();
	tParam.iDelayCapTypeFirst = m_cboFirstCapDelay.GetCurSel();
	tParam.iDelayCapTypeSec = m_cboSecondCapDelay.GetCurSel();
	tParam.iDelayCapTypeTrd = m_cboThirdCapDelay.GetCurSel();
	tParam.iDelayCapTypeFourth = m_cboFourthCapDelay.GetCurSel();
	tParam.iDelayCapTypeFifth = m_cboFifthCapDelay.GetCurSel();

	tParam.iSignalDelayDistance = GetDlgItemInt(IDC_EDT_FIRST_CAP_DELAY);
	tParam.iDelayCapDistanceS = GetDlgItemInt(IDC_EDT_SECOND_CAP_DELAY);
	tParam.iDelayCapDistanceT = GetDlgItemInt(IDC_EDT_THIRD_CAP_DELAY);
	tParam.iDelayCapDistanceFourth = GetDlgItemInt(IDC_EDT_FOURTH_CAP_DELAY);
	tParam.iDelayCapDistanceFifth = GetDlgItemInt(IDC_EDT_FIFTH_CAP_DELAY);

	int iRet = NetClient_SetITSRoadwayParam(m_iLogonID,ITS_ROADWAY_CMD_CHNLDELAYDIS,&tParam,sizeof(tParam));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSRoadwayParam[ITS_ROADWAY_CMD_CHNLDELAYDIS](%d)", m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSRoadwayParam[ITS_ROADWAY_CMD_CHNLDELAYDIS](%d),error(%d)", m_iLogonID, GetLastError());
	}
}

void CLS_ItsRoadwayCommon3::UI_UpdateCapDelay()
{
	if (m_iLogonID < 0)
		return;

	TITSRoadwayDelayDistance tParam = {0};
	tParam.iSize = sizeof(TITSRoadwayDelayDistance);
	tParam.iLaneId = m_cboRoadwayID.GetCurSel();

	int iRet = NetClient_GetITSRoadwayParam(m_iLogonID,ITS_ROADWAY_CMD_CHNLDELAYDIS,&tParam,sizeof(tParam));
	if (0 == iRet)
	{
		m_cboFirstCapDelay.SetCurSel(tParam.iDelayCapTypeFirst);
		m_cboSecondCapDelay.SetCurSel(tParam.iDelayCapTypeSec);
		m_cboThirdCapDelay.SetCurSel(tParam.iDelayCapTypeTrd);
		m_cboFourthCapDelay.SetCurSel(tParam.iDelayCapTypeFourth);
		m_cboFifthCapDelay.SetCurSel(tParam.iDelayCapTypeFifth);

		SetDlgItemInt(IDC_EDT_FIRST_CAP_DELAY, tParam.iSignalDelayDistance);
		SetDlgItemInt(IDC_EDT_SECOND_CAP_DELAY, tParam.iDelayCapDistanceS);
		SetDlgItemInt(IDC_EDT_THIRD_CAP_DELAY, tParam.iDelayCapDistanceT);
		SetDlgItemInt(IDC_EDT_FOURTH_CAP_DELAY, tParam.iDelayCapDistanceFourth);
		SetDlgItemInt(IDC_EDT_FIFTH_CAP_DELAY, tParam.iDelayCapDistanceFifth);
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSRoadwayParam[ITS_ROADWAY_CMD_CHNLDELAYDIS](%d)", m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSRoadwayParam[ITS_ROADWAY_CMD_CHNLDELAYDIS](%d),error(%d)", m_iLogonID, GetLastError());
	}
}



void CLS_ItsRoadwayCommon3::OnBnClickedCheckRoadwayno()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	TITSRoadwayInfo pa = {0};
	pa.iRoadwayID = m_cboRoadwayID.GetCurSel();
	int iRet = NetClient_GetITSRoadwayParam(m_iLogonID, ITS_ROADWAY_CMD_GET_ENABLE, &pa, sizeof(pa));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pa));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pa));
	}
	pa.iEnable = (m_chkRoadwayNo.GetCheck() == BST_CHECKED)?1:0;
	iRet = NetClient_SetITSRoadwayParam(m_iLogonID, ITS_ROADWAY_CMD_SET_ENABLE, &pa, sizeof(pa));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pa));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSRoadwayParam (%d,%d)",m_iLogonID,sizeof(pa));
	}
}
