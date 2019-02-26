// ItsRecognitionParam2.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "ItsRecognitionParam2.h"
#include <bitset>


// CLS_ItsRecognitionParam2 对话框

IMPLEMENT_DYNAMIC(CLS_ItsRecognitionParam2, CDialog)

CLS_ItsRecognitionParam2::CLS_ItsRecognitionParam2(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ItsRecognitionParam2::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannel = -1;
}

CLS_ItsRecognitionParam2::~CLS_ItsRecognitionParam2()
{
}

void CLS_ItsRecognitionParam2::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBO_BRANDRECO, m_cboBrandReco);
	DDX_Control(pDX, IDC_CBO_BELTCHECK, m_cboBeltCheck);
	DDX_Control(pDX, IDC_CBO_MAINFACE_CHECK, m_cboMainFaceCheck);
	DDX_Control(pDX, IDC_CBO_COFACE_CHECK, m_cboCoFaceCheck);
	DDX_Control(pDX, IDC_CBO_TYPECHECK, m_cboTypeCheck);
	DDX_Control(pDX, IDC_COMBO_ROADWAYID, m_cboRoadWayID);
	DDX_Control(pDX, IDC_EDT_MAX_PLATE_NUM, m_edtMaxPlateNum);
	DDX_Control(pDX, IDC_EDT_MAX_PLATE_WTH, m_edtMaxPlateWTH);
	DDX_Control(pDX, IDC_EDT_PIC_THRESHOLD, m_edtPicThreshold);
	DDX_Control(pDX, IDC_EDT_MIN_PLATE_WTH, m_edtMinPlateWTH);
	DDX_Control(pDX, IDC_EDT_PLATE_DEMARCATE, m_edtPlateDemarcate);
	DDX_Control(pDX, IDC_COMBO1, m_cboLaneNum);
	DDX_Control(pDX, IDC_EDT_CONF_THRESHOLD, m_edtConfThreshold);
	DDX_Control(pDX, IDC_COMBO3, m_cboRecognitionType);
	DDX_Control(pDX, IDC_CBO_PLATE_TYPE, m_cboPlateType);
	DDX_Control(pDX, IDC_COMBO6, m_cboRecoCarType);
	DDX_Control(pDX, IDC_CBO_PLATE_ANGLE, m_cboPlateAngle);
	DDX_Control(pDX, IDC_EDT_SPEED, m_edtSpeed);
	//DDX_Control(pDX, IDC_CBO_EXCHANGE_ENABLE, m_cboExchangeEnabled);
	DDX_Control(pDX, IDC_EDT_MAX_FRAMES, m_edtMaxFrames);
	DDX_Control(pDX, IDC_EDT_SINGLECONF_LIMIT, m_edtSingleConfLimit);
	DDX_Control(pDX, IDC_EDT_ALGCONF_LEVEL, m_edtAlgConfLevel);
	DDX_Control(pDX, IDC_COMBO2, m_cboEnableMark);
	DDX_Control(pDX, IDC_CBO_IDENTIFY1, m_cboIdentify1);
	DDX_Control(pDX, IDC_CBO_IDENTIFY2, m_cboIdentify2);
	DDX_Control(pDX, IDC_CBO_IDENTIFY3, m_cboIdentify3);
	DDX_Control(pDX, IDC_CBO_IDENTIFY4, m_cboIdentify4);
	DDX_Control(pDX, IDC_CBO_IDENTIFY5, m_cboIdentify5);
	DDX_Control(pDX, IDC_CBO_IDENTIFY6, m_cboIdentify6);
	DDX_Control(pDX, IDC_CBO_IDENTIFY7, m_cboIdentify7);
	DDX_Control(pDX, IDC_EDT_ENABLE, m_edtEnable);
	DDX_Control(pDX, IDC_CBO_FILTER_PLATE_TYPE, m_cboFilterPlateType);
	DDX_Control(pDX, IDC_CBO_FILTER_PLATE_STATE, m_cboFilterEnableState);
}


BEGIN_MESSAGE_MAP(CLS_ItsRecognitionParam2, CLS_BasePage)
	ON_CBN_SELCHANGE(IDC_CBO_BRANDRECO, &CLS_ItsRecognitionParam2::OnCbnSelchangeCboBrandreco)
	ON_CBN_SELCHANGE(IDC_CBO_BELTCHECK, &CLS_ItsRecognitionParam2::OnCbnSelchangeCboBeltcheck)
	ON_CBN_SELCHANGE(IDC_CBO_MAINFACE_CHECK, &CLS_ItsRecognitionParam2::OnCbnSelchangeCboMainfaceCheck)
	ON_CBN_SELCHANGE(IDC_CBO_COFACE_CHECK, &CLS_ItsRecognitionParam2::OnCbnSelchangeCboCofaceCheck)
	ON_CBN_SELCHANGE(IDC_CBO_TYPECHECK, &CLS_ItsRecognitionParam2::OnCbnSelchangeCboTypecheck)
	ON_CBN_SELCHANGE(IDC_COMBO_ROADWAYID, &CLS_ItsRecognitionParam2::OnCbnSelchangeComboRoadwayid)
	ON_BN_CLICKED(IDC_BTN_RECO_SET, &CLS_ItsRecognitionParam2::OnBnClickedBtnRecoSet)
	//ON_STN_CLICKED(IDC_STC_REGION_TYPE, &CLS_ItsRecognitionParam2::OnStnClickedStcRegionType)
	ON_BN_CLICKED(IDC_BTN_FILTER_PLATE_SET, &CLS_ItsRecognitionParam2::OnBnClickedBtnFilterPlateSet)
	ON_CBN_SELCHANGE(IDC_CBO_FILTER_PLATE_TYPE, &CLS_ItsRecognitionParam2::OnCbnSelchangeCboFilterPlateType)
END_MESSAGE_MAP()


// CLS_ItsRecognitionParam2 消息处理程序

BOOL CLS_ItsRecognitionParam2::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	UI_UpdateDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CLS_ItsRecognitionParam2::OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo)
{
	m_iLogonID = _iLogonID;
	if(_iChannelNo < 0)
	{
		m_iChannel = 0;
	}
	else
	{
		m_iChannel = _iChannelNo;
	}
	UI_UpdateBrandReco();
	UI_UpdateBeltReco();
	UI_UpdateMainFaceCheck();
	UI_UpdateCoFaceCheck();
	UI_UpdateCarTypeCheck();
	UI_UpdateReco();
	UI_UpdatePlateNumber();
	UI_UpdateFilterPlate();
}

void CLS_ItsRecognitionParam2::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_ItsRecognitionParam2::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STC_COFACE_CHECK, IDS_ITS_COFACE_CHECK);
	SetDlgItemTextEx(IDC_STC_MAINFACE_CHECK, IDS_ITS_MAINFACE_CHECK);
	SetDlgItemTextEx(IDC_STC_BRANDRECO, IDS_ITS_BRANDRECO);
	SetDlgItemTextEx(IDC_STC_TYPECHECK, IDS_ITS_TYPECHECK);
	SetDlgItemTextEx(IDC_STC_BELTCHECK, IDS_ITS_BELTCHECK);
	SetDlgItemTextEx(IDC_STC_MAX_PLATE_NUM, IDS_ITS_MAX_PLATE_NUM);
	SetDlgItemTextEx(IDC_STC_RECO_RATE, IDS_ITS_RECO_RATE);
	SetDlgItemTextEx(IDC_STC_MIN_PLATE_WTH, IDS_ITS_MIN_PLATE_WTH);
	SetDlgItemTextEx(IDC_STC_PIC_THRESHOLD, IDS_ITS_PIC_THRESHOLD);
	SetDlgItemTextEx(IDC_STC_MAX_PLATE_WTH, IDS_ITS_MAX_PLATE_WTH);
	SetDlgItemTextEx(IDC_STC_PLATE_DEMARCATE, IDS_ITS_PLATE_DEMARCATE);
	SetDlgItemTextEx(IDC_STC_LANE_NUM, IDS_ITS_ROADWAY_ID);
	SetDlgItemTextEx(IDC_STC_RECO_TYPE, IDS_ITS_RECO_TYPE);
	SetDlgItemTextEx(IDC_STC_ENABLE_MARK, IDS_ITS_ENABLE_MARK);
	SetDlgItemTextEx(IDC_STC_CONF_THRESHOLD, IDS_ITS_CONF_THRESHOLD);
	SetDlgItemTextEx(IDC_STC_REGION_TYPE, IDS_ITS_REGION_TYPE);
	SetDlgItemTextEx(IDC_STC_PLATE_TYPE, IDS_ITS_PLATE_TYPE);
	SetDlgItemTextEx(IDC_STC_RECO_CARTYPE, IDS_ITS_RECO_CARTYPE);
	SetDlgItemTextEx(IDC_STC_PLATE_ANGLE, IDS_ITS_PLATE_ANGLAE);
	SetDlgItemTextEx(IDC_STC_SPEED, IDS_CONFIG_ECOP_SPEED);
	SetDlgItemTextEx(IDC_STC_EXCHANGE_ENABLE, IDS_ITS_EXCHANGE_ENABLE);
	SetDlgItemTextEx(IDC_STC_MAX_FRAMES, IDS_ITS_MAX_FRAMES);
	SetDlgItemTextEx(IDC_STC_SINGLECONF_LIMIT, IDS_ITS_SINGLECONF_LIMIT);
	SetDlgItemTextEx(IDC_STC_ALGCONF_LEVEL, IDS_ITS_ALGCONF_LEVEL);
	SetDlgItemTextEx(IDC_BTN_RECO_SET, IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_ROADWAYID, IDS_ITS_ROADWAY_ID);
	SetDlgItemTextEx(IDC_STC_RECO, IDS_ITS_RECO);
	SetDlgItemTextEx(IDC_STC_FILTER_PLATE, IDS_FILTER_REPEAT_PLATE);
	SetDlgItemTextEx(IDC_STC_FILTER_PLATE_TYPE, IDS_CONFIG_ITS_ILLEGALPARK_TYPE);
	SetDlgItemTextEx(IDC_STC_FILTER_PLATE_INTERVAL_TIME, IDS_ALARM_INTERVAL_TIME);
	SetDlgItemTextEx(IDC_BTN_FILTER_PLATE_SET, IDS_SET);
	//
	InsertString(m_cboBeltCheck, 0, IDS_ITS_NO);
	InsertString(m_cboBeltCheck, 1, IDS_ITS_YES);
	//
	InsertString(m_cboBrandReco, 0, IDS_ITS_NO);
	InsertString(m_cboBrandReco, 1, IDS_ITS_YES);
	//
	InsertString(m_cboMainFaceCheck, 0, IDS_ITS_NO);
	InsertString(m_cboMainFaceCheck, 1, IDS_ITS_YES);
	//
	InsertString(m_cboCoFaceCheck, 0, IDS_ITS_NO);
	InsertString(m_cboCoFaceCheck, 1, IDS_ITS_YES);
	//
	InsertString(m_cboTypeCheck, 0, IDS_ITS_NO);
	InsertString(m_cboTypeCheck, 1, IDS_ITS_YES);
	//
	InsertString(m_cboEnableMark, 0, IDS_ITS_RECO_CLOSE);
	InsertString(m_cboEnableMark, 1, IDS_ITS_RECO_OPEN);
	InsertString(m_cboEnableMark, 2, IDS_ITS_OPEN_FACERECO);
	//
	InsertString(m_cboPlateType, 0, IDS_ITS_RETAIN);
	InsertString(m_cboPlateType, 1, IDS_ITS_SMALLPLATE);
	InsertString(m_cboPlateType, 2, IDS_ITS_BIGPLATE);
	InsertString(m_cboPlateType, 3, IDS_ITS_TINYPLATE);
	//
	InsertString(m_cboPlateAngle, 0, IDS_ITS_RETAIN);
	InsertString(m_cboPlateAngle, 1, IDS_ITS_NOMAL_ANGLE);
	InsertString(m_cboPlateAngle, 2, IDS_ITS_HIGH_ANGLE);
	for(int i = 0; i < 15; i++)
	{
		InsertString(m_cboRecoCarType, i, 11108+i);
	}
	for(int i = 0; i<4; i++)
	{
		CString strNo;
		strNo.Format("%d",i);
		InsertString(m_cboRoadWayID, i, strNo);
		InsertString(m_cboLaneNum, i, strNo);
	}
	m_cboRoadWayID.SetCurSel(0);
	for(int i = 0; i<2; i++)
	{
		InsertString(m_cboRecognitionType,i,11129+i);
	}
	InsertString(m_cboIdentify1,0,IDS_ITS_CHINESE_WORD);
	InsertString(m_cboIdentify1,1,IDS_ITS_ENGLISH_WORD);
	InsertString(m_cboIdentify1,2,IDS_ITS_NUMBER);
	InsertString(m_cboIdentify1,3,IDS_ITS_ENGLISH_WORD_OR_NUMBER);

	InsertString(m_cboIdentify2,0,IDS_ITS_CHINESE_WORD);
	InsertString(m_cboIdentify2,1,IDS_ITS_ENGLISH_WORD);
	InsertString(m_cboIdentify2,2,IDS_ITS_NUMBER);
	InsertString(m_cboIdentify2,3,IDS_ITS_ENGLISH_WORD_OR_NUMBER);

	InsertString(m_cboIdentify3,0,IDS_ITS_CHINESE_WORD);
	InsertString(m_cboIdentify3,1,IDS_ITS_ENGLISH_WORD);
	InsertString(m_cboIdentify3,2,IDS_ITS_NUMBER);
	InsertString(m_cboIdentify3,3,IDS_ITS_ENGLISH_WORD_OR_NUMBER);

	InsertString(m_cboIdentify4,0,IDS_ITS_CHINESE_WORD);
	InsertString(m_cboIdentify4,1,IDS_ITS_ENGLISH_WORD);
	InsertString(m_cboIdentify4,2,IDS_ITS_NUMBER);
	InsertString(m_cboIdentify4,3,IDS_ITS_ENGLISH_WORD_OR_NUMBER);

	InsertString(m_cboIdentify5,0,IDS_ITS_CHINESE_WORD);
	InsertString(m_cboIdentify5,1,IDS_ITS_ENGLISH_WORD);
	InsertString(m_cboIdentify5,2,IDS_ITS_NUMBER);
	InsertString(m_cboIdentify5,3,IDS_ITS_ENGLISH_WORD_OR_NUMBER);

	InsertString(m_cboIdentify6,0,IDS_ITS_CHINESE_WORD);
	InsertString(m_cboIdentify6,1,IDS_ITS_ENGLISH_WORD);
	InsertString(m_cboIdentify6,2,IDS_ITS_NUMBER);
	InsertString(m_cboIdentify6,3,IDS_ITS_ENGLISH_WORD_OR_NUMBER);

	InsertString(m_cboIdentify7,0,IDS_ITS_CHINESE_WORD);
	InsertString(m_cboIdentify7,1,IDS_ITS_ENGLISH_WORD);
	InsertString(m_cboIdentify7,2,IDS_ITS_NUMBER);
	InsertString(m_cboIdentify7,3,IDS_ITS_ENGLISH_WORD_OR_NUMBER);

	m_cboFilterPlateType.ResetContent();
	m_cboFilterPlateType.SetItemData(m_cboFilterPlateType.AddString(GetTextEx(IDS_PLATE_KNOWN)), FILTER_PALTE_TYPE_REPEAT_PLATE);
	m_cboFilterPlateType.SetItemData(m_cboFilterPlateType.AddString(GetTextEx(IDS_PLATE_UNKNOWN)), FILTER_PALTE_TYPE_UNKNOW_PLATE);
	m_cboFilterPlateType.SetCurSel(GetCboSel(&m_cboFilterPlateType, FILTER_PALTE_TYPE_REPEAT_PLATE));

	m_cboFilterEnableState.ResetContent();
	m_cboFilterEnableState.SetItemData(m_cboFilterEnableState.AddString(GetTextEx(IDS_CONFIG_FTP_SNAPSHOT_DISABLE)), 0);
	m_cboFilterEnableState.SetItemData(m_cboFilterEnableState.AddString(GetTextEx(IDS_CONFIG_FTP_SNAPSHOT_ENABLE)), 1);
	m_cboFilterEnableState.SetCurSel(0);
}

void CLS_ItsRecognitionParam2::OnCbnSelchangeCboBrandreco()
{
	if(m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	ITS_EnalbeParam tEnableParam = {0};
	tEnableParam.iType = ITS_TYPE_BRANDRECO;
	tEnableParam.iEnable = m_cboBrandReco.GetCurSel();
	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_ENABLE_CMD_SET, m_iChannel, &tEnableParam, sizeof(tEnableParam));
	if(iRet == 0)
	{
		AddLog(LOG_TYPE_SUCC,"", "NetClient_SetITSExtraInfo[ITS_ENABLE_CMD_SET](%d,%d)", m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"", "NetClient_SetITSExtraInfo[ITS_ENABLE_CMD_SET](%d,%d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
	}
}
BOOL CLS_ItsRecognitionParam2::UI_UpdateBrandReco()
{
	if(m_iLogonID < 0)
		return FALSE;
	ITS_EnalbeParam tEnableParam = {0};
	tEnableParam.iType = ITS_TYPE_BRANDRECO;
	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_ENABLE_CMD_GET, m_iChannel, &tEnableParam, sizeof(tEnableParam));
	if(iRet == 0)
	{
		m_cboBrandReco.SetCurSel(tEnableParam.iEnable);
		AddLog(LOG_TYPE_SUCC,"", "NetClient_GetITSExtraInfo[ITS_ENABLE_CMD_GET](%d,%d)", m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"", "NetClient_GetITSExtraInfo[ITS_ENABLE_CMD_GET](%d,%d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
		return FALSE;
	}
	return TRUE;
}
void CLS_ItsRecognitionParam2::OnCbnSelchangeCboBeltcheck()
{
	if(m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	ITS_EnalbeParam tEnableParam = {0};
	tEnableParam.iType = ITS_TYPE_BELTCHECK;
	tEnableParam.iEnable = m_cboBeltCheck.GetCurSel();
	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_ENABLE_CMD_SET, m_iChannel, &tEnableParam, sizeof(tEnableParam));
	if(iRet == 0)
	{
		AddLog(LOG_TYPE_SUCC,"", "NetClient_SetITSExtraInfo[ITS_ENABLE_CMD_SET](%d,%d)", m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"", "NetClient_SetITSExtraInfo[ITS_ENABLE_CMD_SET](%d,%d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
	}
}
BOOL CLS_ItsRecognitionParam2::UI_UpdateBeltReco()
{
	if(m_iLogonID < 0)
		return FALSE;
	ITS_EnalbeParam tEnableParam = {0};
	tEnableParam.iType = ITS_TYPE_BELTCHECK;
	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_ENABLE_CMD_GET, m_iChannel, &tEnableParam, sizeof(tEnableParam));
	if(iRet == 0)
	{
		m_cboBeltCheck.SetCurSel(tEnableParam.iEnable);
		AddLog(LOG_TYPE_SUCC,"", "NetClient_GetITSExtraInfo[ITS_ENABLE_CMD_GET](%d,%d)", m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"", "NetClient_GetITSExtraInfo[ITS_ENABLE_CMD_GET](%d,%d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
		return FALSE;
	}
	return TRUE;
}
void CLS_ItsRecognitionParam2::OnCbnSelchangeCboMainfaceCheck()
{
	if(m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	ITS_EnalbeParam tEnableParam = {0};
	tEnableParam.iType = ITS_TYPE_MAINFACE_CHECK;
	tEnableParam.iEnable = m_cboMainFaceCheck.GetCurSel();
	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_ENABLE_CMD_SET, m_iChannel, &tEnableParam, sizeof(tEnableParam));
	if(iRet == 0)
	{
		AddLog(LOG_TYPE_SUCC,"", "NetClient_SetITSExtraInfo[ITS_ENABLE_CMD_SET](%d,%d)", m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"", "NetClient_SetITSExtraInfo[ITS_ENABLE_CMD_SET](%d,%d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
	}
}
BOOL CLS_ItsRecognitionParam2::UI_UpdateMainFaceCheck()
{
	if(m_iLogonID < 0)
		return FALSE;
	ITS_EnalbeParam tEnableParam = {0};
	tEnableParam.iType = ITS_TYPE_MAINFACE_CHECK;
	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_ENABLE_CMD_GET, m_iChannel, &tEnableParam, sizeof(tEnableParam));
	if(iRet == 0)
	{
		m_cboMainFaceCheck.SetCurSel(tEnableParam.iEnable);
		AddLog(LOG_TYPE_SUCC,"", "NetClient_GetITSExtraInfo[ITS_ENABLE_CMD_GET](%d,%d)", m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"", "NetClient_GetITSExtraInfo[ITS_ENABLE_CMD_GET](%d,%d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
		return FALSE;
	}
	return TRUE;
}
void CLS_ItsRecognitionParam2::OnCbnSelchangeCboCofaceCheck()
{
	if(m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	ITS_EnalbeParam tEnableParam = {0};
	tEnableParam.iType = ITS_TYPE_COFACE_CHECK;
    tEnableParam.iEnable = m_cboCoFaceCheck.GetCurSel();
	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_ENABLE_CMD_SET, m_iChannel, &tEnableParam, sizeof(tEnableParam));
	if(iRet == 0)
	{
		AddLog(LOG_TYPE_SUCC,"", "NetClient_SetITSExtraInfo[ITS_ENABLE_CMD_SET](%d,%d)", m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"", "NetClient_SetITSExtraInfo[ITS_ENABLE_CMD_SET](%d,%d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
	}
}
BOOL CLS_ItsRecognitionParam2::UI_UpdateCoFaceCheck()
{
	if(m_iLogonID < 0)
		return FALSE;
	ITS_EnalbeParam tEnableParam = {0};
	tEnableParam.iType = ITS_TYPE_COFACE_CHECK;
	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_ENABLE_CMD_GET, m_iChannel, &tEnableParam, sizeof(tEnableParam));
	if(iRet == 0)
	{
		m_cboCoFaceCheck.SetCurSel(tEnableParam.iEnable);
		AddLog(LOG_TYPE_SUCC,"", "NetClient_GetITSExtraInfo[ITS_ENABLE_CMD_GET](%d,%d)", m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"", "NetClient_GetITSExtraInfo[ITS_ENABLE_CMD_GET](%d,%d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
		return FALSE;
	}
	return TRUE;
}
void CLS_ItsRecognitionParam2::OnCbnSelchangeCboTypecheck()
{
	if(m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	ITS_EnalbeParam tEnableParam = {0};
	tEnableParam.iType = ITS_TYPE_TYPECHECK;
	tEnableParam.iEnable = m_cboTypeCheck.GetCurSel();
	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_ENABLE_CMD_SET, m_iChannel, &tEnableParam, sizeof(tEnableParam));
	if(iRet == 0)
	{
		AddLog(LOG_TYPE_SUCC,"", "NetClient_SetITSExtraInfo[ITS_ENABLE_CMD_SET](%d,%d)", m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"", "NetClient_SetITSExtraInfo[ITS_ENABLE_CMD_SET](%d,%d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
	}
}
BOOL CLS_ItsRecognitionParam2::UI_UpdateCarTypeCheck()
{
	if(m_iLogonID < 0)
		return FALSE;
	ITS_EnalbeParam tEnableParam = {0};
	tEnableParam.iType = ITS_TYPE_TYPECHECK;
	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_ENABLE_CMD_GET, m_iChannel, &tEnableParam, sizeof(tEnableParam));
	if(iRet == 0)
	{
		m_cboTypeCheck.SetCurSel(tEnableParam.iEnable);
		AddLog(LOG_TYPE_SUCC,"", "NetClient_GetITSExtraInfo[ITS_ENABLE_CMD_GET](%d,%d)", m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"", "NetClient_GetITSExtraInfo[ITS_ENABLE_CMD_GET](%d,%d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
		return FALSE;
	}
	return TRUE;
}
void CLS_ItsRecognitionParam2::OnCbnSelchangeComboRoadwayid()
{
	UI_UpdateBrandReco();
	UI_UpdateBeltReco();
	UI_UpdateMainFaceCheck();
	UI_UpdateCoFaceCheck();
	UI_UpdateCarTypeCheck();
	UI_UpdateReco();
	UI_UpdatePlateNumber();
	UI_UpdateFilterPlate();
}

void CLS_ItsRecognitionParam2::OnBnClickedBtnRecoSet()
{
	if(m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	TITSRecoParam tItSRecoParam = {0};
	tItSRecoParam.iSize = sizeof(tItSRecoParam);
	tItSRecoParam.tRecoPara.iRoadwayID = m_cboRoadWayID.GetCurSel();
	tItSRecoParam.iAngle = m_cboPlateAngle.GetCurSel();
	tItSRecoParam.iCarNumType = m_cboRecoCarType.GetCurSel();
	CString str = "";
	GetDlgItem(IDC_EDT_PLATE_DEMARCATE)->GetWindowText(str);
	strcpy(tItSRecoParam.tRecoPara.cCaliInfo, str);
	tItSRecoParam.tRecoPara.iPlateCharType = m_cboIdentify1.GetCurSel();
	tItSRecoParam.tRecoPara.iPlateCharType = tItSRecoParam.tRecoPara.iPlateCharType << 2 | m_cboIdentify2.GetCurSel(); 
	tItSRecoParam.tRecoPara.iPlateCharType = tItSRecoParam.tRecoPara.iPlateCharType << 2 | m_cboIdentify3.GetCurSel();
	tItSRecoParam.tRecoPara.iPlateCharType = tItSRecoParam.tRecoPara.iPlateCharType << 2 | m_cboIdentify4.GetCurSel();
	tItSRecoParam.tRecoPara.iPlateCharType = tItSRecoParam.tRecoPara.iPlateCharType << 2 | m_cboIdentify5.GetCurSel();
	tItSRecoParam.tRecoPara.iPlateCharType = tItSRecoParam.tRecoPara.iPlateCharType << 2 | m_cboIdentify6.GetCurSel();
	tItSRecoParam.tRecoPara.iPlateCharType = tItSRecoParam.tRecoPara.iPlateCharType << 2 | m_cboIdentify7.GetCurSel();

	tItSRecoParam.tRecoPara.iAreaType = m_cboRecognitionType.GetCurSel();
	tItSRecoParam.tRecoPara.iConfid = GetDlgItemInt(IDC_EDT_CONF_THRESHOLD);
	tItSRecoParam.tRecoPara.iFramePercent = GetDlgItemInt(IDC_EDT_RECO_RATE);
	tItSRecoParam.tRecoPara.iMaxPlateWidth = GetDlgItemInt(IDC_EDT_MAX_PLATE_WTH);
	tItSRecoParam.tRecoPara.iMinPlateWidth = GetDlgItemInt(IDC_EDT_MIN_PLATE_WTH);
	tItSRecoParam.tRecoPara.iMaxSkip = GetDlgItemInt(IDC_EDT_MAX_FRAMES);
	tItSRecoParam.tRecoPara.iMaxPlateNO = GetDlgItemInt(IDC_EDT_MAX_PLATE_NUM);
	tItSRecoParam.tRecoPara.iSpeed = GetDlgItemInt(IDC_EDT_SPEED);
	tItSRecoParam.tRecoPara.iMinCapDiff = GetDlgItemInt(IDC_EDT_PIC_THRESHOLD);
	tItSRecoParam.iCarNumType = m_cboPlateType.GetCurSel();
	tItSRecoParam.iPlateCharConfid = GetDlgItemInt(IDC_EDT_SINGLECONF_LIMIT);
	tItSRecoParam.tRecoPara.iEnable = m_cboEnableMark.GetCurSel();
	GetDlgItem(IDC_EDT_ENABLE)->GetWindowText(str);
	strcpy(tItSRecoParam.cSymbol, str);
	tItSRecoParam.tRecoPara.iPlateType = m_cboRecoCarType.GetCurSel();
	tItSRecoParam.tRecoPara.iMinValid = GetDlgItemInt(IDC_EDT_ALGCONF_LEVEL);
	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_RECOPARAM, m_iChannel, &tItSRecoParam, sizeof(tItSRecoParam));
	if(iRet == 0)
	{
		AddLog(LOG_TYPE_SUCC,"", "NetClient_SetITSExtraInfo[ITS_EXTRAINFO_CMD_RECOPARAM](%d,%d)", m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"", "NetClient_SetITSExtraInfo[ITS_EXTRAINFO_CMD_RECOPARAM](%d,%d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
	}
}
BOOL CLS_ItsRecognitionParam2::UI_UpdateReco()
{
	if(m_iLogonID < 0)
		return FALSE;
	TITSRecoParam tItSRecoParam = {0};
	tItSRecoParam.iSize = sizeof(tItSRecoParam);
	tItSRecoParam.tRecoPara.iRoadwayID = m_cboRoadWayID.GetCurSel();
	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_RECOPARAM, m_iChannel, &tItSRecoParam, sizeof(tItSRecoParam));
	if(iRet == 0)
	{
		m_cboRecoCarType.SetCurSel(tItSRecoParam.tRecoPara.iPlateType);
		m_cboPlateAngle.SetCurSel(tItSRecoParam.iAngle);
		m_cboRecognitionType.SetCurSel(tItSRecoParam.tRecoPara.iAreaType );
		m_cboPlateType.SetCurSel(tItSRecoParam.iCarNumType);
		m_cboEnableMark.SetCurSel(tItSRecoParam.tRecoPara.iEnable);
		SetDlgItemText(IDC_EDT_ENABLE, tItSRecoParam.cSymbol);
		m_cboLaneNum.SetCurSel(tItSRecoParam.tRecoPara.iRoadwayID);
		CString str(tItSRecoParam.tRecoPara.cCaliInfo);
		GetDlgItem(IDC_EDT_PLATE_DEMARCATE)->SetWindowText(str);
		SetDlgItemInt(IDC_EDT_CONF_THRESHOLD, tItSRecoParam.tRecoPara.iConfid);
		SetDlgItemInt(IDC_EDT_RECO_RATE, tItSRecoParam.tRecoPara.iFramePercent);
		SetDlgItemInt(IDC_EDT_MAX_PLATE_WTH, tItSRecoParam.tRecoPara.iMaxPlateWidth);
		SetDlgItemInt(IDC_EDT_MIN_PLATE_WTH, tItSRecoParam.tRecoPara.iMinPlateWidth);
		SetDlgItemInt(IDC_EDT_MAX_FRAMES, tItSRecoParam.tRecoPara.iMaxSkip);
		SetDlgItemInt(IDC_EDT_MAX_PLATE_NUM, tItSRecoParam.tRecoPara.iMaxPlateNO);
		SetDlgItemInt(IDC_EDT_SPEED, tItSRecoParam.tRecoPara.iSpeed);
		SetDlgItemInt(IDC_EDT_PIC_THRESHOLD, tItSRecoParam.tRecoPara.iMinCapDiff);
		SetDlgItemInt(IDC_EDT_SINGLECONF_LIMIT, tItSRecoParam.iPlateCharConfid);
		SetDlgItemInt(IDC_EDT_ALGCONF_LEVEL, tItSRecoParam.tRecoPara.iMinValid);
		AddLog(LOG_TYPE_SUCC,"", "NetClient_GetITSExtraInfo[ITS_EXTRAINFO_CMD_RECOPARAM](%d,%d)", m_iLogonID, m_iChannel);
	}
	else
	{
			AddLog(LOG_TYPE_FAIL,"", "NetClient_SetITSExtraInfo[ITS_EXTRAINFO_CMD_RECOPARAM](%d,%d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
			return FALSE;
	}
	return TRUE;
}
BOOL CLS_ItsRecognitionParam2::UI_UpdatePlateNumber()
{
	TITSRecoParam tGetData = {0};
	tGetData.tRecoPara.iRoadwayID = m_cboRoadWayID.GetCurSel();
	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_RECOPARAM, m_iChannel, &tGetData, sizeof(TITSRecoParam));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSExtraInfo[ITS_EXTRAINFO_CMD_RECOPARAM] (%d,%d)", m_iLogonID, m_iChannel);
		int iTemp = tGetData.tRecoPara.iPlateCharType;
		m_cboIdentify7.SetCurSel(iTemp & 0x0003);
		m_cboIdentify6.SetCurSel((iTemp >> 2) & 0x0003);
		m_cboIdentify5.SetCurSel((iTemp >> 4) & 0x0003);
		m_cboIdentify4.SetCurSel((iTemp >> 6) & 0x0003);
		m_cboIdentify3.SetCurSel((iTemp >> 8) & 0x0003);
		m_cboIdentify2.SetCurSel((iTemp >> 10) & 0x0003);
		m_cboIdentify1.SetCurSel((iTemp >> 12) & 0x0003);
		return TRUE;
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSExtraInfo[ITS_EXTRAINFO_CMD_RECOPARAM] (%d,%d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
		return FALSE;
	}
}


void CLS_ItsRecognitionParam2::OnBnClickedBtnFilterPlateSet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Illeage Logid(%d)", m_iLogonID);
		return;
	}

	if (m_iChannel < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Illeage ChannelNo(%d)", m_iChannel);
		return;
	}

	ItsFilterPlate tItsFilterPlate = {0};
	tItsFilterPlate.iSize = sizeof(ItsFilterPlate);
	tItsFilterPlate.iType = (int)m_cboFilterPlateType.GetItemData(m_cboFilterPlateType.GetCurSel());
	tItsFilterPlate.iEnable = (int)m_cboFilterEnableState.GetItemData(m_cboFilterEnableState.GetCurSel());
	tItsFilterPlate.iTimeInterval = GetDlgItemInt(IDC_EDT_FILTER_PLATE_INTERVAL_TIME);

	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_FILTERPLATE, m_iChannel, (void*)&tItsFilterPlate, sizeof(ItsFilterPlate));

	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo[FILTERPLATE] (%d,%d)", m_iLogonID, m_iChannel);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo[FILTERPLATE] (%d,%d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
	}
}

void CLS_ItsRecognitionParam2::UI_UpdateFilterPlate()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Illeage Logid(%d)", m_iLogonID);
		return;
	}

	if (m_iChannel < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Illeage ChannelNo(%d)", m_iChannel);
		return;
	}

	ItsFilterPlate tItsFilterPlate = {0};
	tItsFilterPlate.iSize = sizeof(ItsFilterPlate);
	tItsFilterPlate.iType = (int)m_cboFilterPlateType.GetItemData(m_cboFilterPlateType.GetCurSel());

	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_FILTERPLATE, m_iChannel, (void*)&tItsFilterPlate, sizeof(ItsFilterPlate));

	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSExtraInfo[FILTERPLATE] (%d,%d)", m_iLogonID, m_iChannel);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSExtraInfo[FILTERPLATE] (%d,%d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
		return;
	}

	m_cboFilterEnableState.SetCurSel(GetCboSel(&m_cboFilterEnableState, tItsFilterPlate.iEnable));
	SetDlgItemInt(IDC_EDT_FILTER_PLATE_INTERVAL_TIME, tItsFilterPlate.iTimeInterval);
}

void CLS_ItsRecognitionParam2::OnCbnSelchangeCboFilterPlateType()
{
	UI_UpdateFilterPlate();
}
