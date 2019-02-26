// PlatformConfig.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "ITSPlatformConfig.h"

#define DEFAULT_SEL_INDEX		-1

IMPLEMENT_DYNAMIC(CLS_ITSPlatformConfig, CDialog)

CLS_ITSPlatformConfig::CLS_ITSPlatformConfig(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ITSPlatformConfig::IDD, pParent)
{
	m_iLogonId = -1;
	m_iChannelNo = -1;
}

CLS_ITSPlatformConfig::~CLS_ITSPlatformConfig()
{
}

void CLS_ITSPlatformConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBO_PICUNLOAD_CUSTOM_PICNAME, m_cboCustomNameEnable);
	DDX_Control(pDX, IDC_CBO_PICUNLOAD_SEPARATOR, m_cboSeparator);
	DDX_Control(pDX, IDC_CBO_PICUNLOAD_VERSION, m_cboVersion);
	DDX_Control(pDX, IDC_CBO_PICUNLOAD_RESPONSE, m_cboResponseEnable);
	DDX_Control(pDX, IDC_CHK_1_HOST_ID, m_chkPicNameSection[PIC_NAME_SECTION_HOST_ID]);
	DDX_Control(pDX, IDC_CHK_2_ROAD_ID, m_chkPicNameSection[PIC_NAME_SECTION_ROAD_ID]);
	DDX_Control(pDX, IDC_CHK_3_DEV_ID, m_chkPicNameSection[PIC_NAME_SECTION_DEV_ID]);
	DDX_Control(pDX, IDC_CHK_4_DETECT_AREA_ID, m_chkPicNameSection[PIC_NAME_SECTION_DETECT_AREA_ID]);
	DDX_Control(pDX, IDC_CHK_5_DIRECTION_ID, m_chkPicNameSection[PIC_NAME_SECTION_DIRECTION_ID]);
	DDX_Control(pDX, IDC_CHK_6_CAP_TIME, m_chkPicNameSection[PIC_NAME_SECTION_CAP_TIME]);
	DDX_Control(pDX, IDC_TIME_PICDEL_STARTTIME, m_timeStartTime);
	DDX_Control(pDX, IDC_EDT_PICDEL_ENDTIME, m_timeEndTime);
}


BEGIN_MESSAGE_MAP(CLS_ITSPlatformConfig, CDialog)
	ON_BN_CLICKED(IDC_BTN_PALTFORM_CFG_SET, &CLS_ITSPlatformConfig::OnBnClickedBtnPaltformCfgSet)
	ON_BN_CLICKED(IDC_BTN_PICUNLOAD_SET, &CLS_ITSPlatformConfig::OnBnClickedBtnPicunloadSet)
	ON_BN_CLICKED(IDC_BTN_PICDEL_SET, &CLS_ITSPlatformConfig::OnBnClickedBtnPicdelSet)
END_MESSAGE_MAP()


BOOL CLS_ITSPlatformConfig::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	((CEdit*)GetDlgItem(IDC_EDT_PALTFORM_ID))->SetLimitText(LEN_64);
	((CEdit*)GetDlgItem(IDC_EDT_PALTFORM_PORT))->SetLimitText(LEN_8);
	((CEdit*)GetDlgItem(IDC_EDT_PICUNLOAD_SERVER_PORT))->SetLimitText(LEN_8);
	((CEdit*)GetDlgItem(IDC_EDT_PICDEL_NUM))->SetLimitText(LEN_8);
	((CEdit*)GetDlgItem(IDC_EDT_PICDEL_KEEPDAY))->SetLimitText(LEN_8);
	
	UI_UpdateDialog();

	return TRUE;
}

void CLS_ITSPlatformConfig::OnChannelChanged( int _iLogonID,int _iChannelNo,int /*_iStreamNo*/ )
{
	m_iLogonId = _iLogonID;
	m_iChannelNo = (_iChannelNo < 0) ? 0 : _iChannelNo;
	UI_UpdateDialog();
	UI_UpdatePlatformCfg();
	UI_UpdatePicunload();
	UI_UpdatePicdel();
}

void CLS_ITSPlatformConfig::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_ITSPlatformConfig::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_GBO_PALTFORM_CFG, IDS_PLATFOM_CONFIG);
	SetDlgItemTextEx(IDC_STC_PALTFORM_ID, IDS_PLATFORM_ID);
	SetDlgItemTextEx(IDC_STC_PALTFORM_IP, IDS_PLATFORM_IP);
	SetDlgItemTextEx(IDC_STC_PALTFORM_PORT, IDS_PLATFORM_PORT);
	SetDlgItemTextEx(IDC_GBO_PICUNLOAD, IDS_PIC_UPLOAD);
	SetDlgItemTextEx(IDC_STC_PICUNLOAD_SERVER_IP, IDS_SERVER_IP);
	SetDlgItemTextEx(IDC_STC_PICUNLOAD_SERVER_PORT, IDS_SERVER_PORT);
	SetDlgItemTextEx(IDC_STC_PICUNLOAD_CUSTOM_PICNAME, IDS_CUSTOM_PIC_NAME);
	SetDlgItemTextEx(IDC_STC_PICUNLOAD_SEPARATOR, IDS_FILE_NAME_SEPARATOR);
	SetDlgItemTextEx(IDC_STC_PICUNLOAD_VERSION, IDS_VERSION_DEMO);
	SetDlgItemTextEx(IDC_STC_PICUNLOAD_RESPONSE, IDS_DATA_RESPONSE);
	SetDlgItemTextEx(IDC_CHK_1_HOST_ID, IDS_HOST_ID);
	SetDlgItemTextEx(IDC_CHK_2_ROAD_ID, IDS_ROAD_ID);
	SetDlgItemTextEx(IDC_CHK_3_DEV_ID, IDS_CONFIG_ITS_DEVICENUM);
	SetDlgItemTextEx(IDC_CHK_4_DETECT_AREA_ID, IDS_DETECT_AREA_ID);
	SetDlgItemTextEx(IDC_CHK_5_DIRECTION_ID, IDS_DIRECTION_ID);
	SetDlgItemTextEx(IDC_CHK_6_CAP_TIME, IDS_CAO_TIME);
	SetDlgItemTextEx(IDC_STC_PICUNLOAD_PICNAME_CONTENT, IDS_PIC_NAME_SECTION);
	SetDlgItemTextEx(IDC_GBO_PICDEL, IDS_PIC_DEL);
	SetDlgItemTextEx(IDC_STC_PICDEL_NUM, IDS_PIC_DEL_NUM);
	SetDlgItemTextEx(IDC_STC_PICDEL_KEEPDAY, IDS_PIC_SAVE_TIME);
	SetDlgItemTextEx(IDC_STC_PICDEL_STARTTIME, IDS_PIC_DEL_BEGAIN_TIME);
	SetDlgItemTextEx(IDC_STC_PICDEL_ENDTIME, IDS_PIC_DEL_END_TIME);
	SetDlgItemTextEx(IDC_BTN_PICUNLOAD_SET, IDS_SET);
	SetDlgItemTextEx(IDC_BTN_PICDEL_SET, IDS_SET);
	SetDlgItemTextEx(IDC_BTN_PALTFORM_CFG_SET, IDS_SET);

	int iTempIndex = DEFAULT_SEL_INDEX;
	
	iTempIndex = m_cboCustomNameEnable.GetCurSel();
	m_cboCustomNameEnable.ResetContent();
	m_cboCustomNameEnable.SetItemData(m_cboCustomNameEnable.AddString(GetTextEx(IDS_CONFIG_VIDEOPARAM_DISABLE)), 0);
	m_cboCustomNameEnable.SetItemData(m_cboCustomNameEnable.AddString(GetTextEx(IDS_CONFIG_VIDEOPARAM_ENABLE)), 1);
	iTempIndex = (iTempIndex < m_cboCustomNameEnable.GetCount()) ? iTempIndex : DEFAULT_SEL_INDEX;
	m_cboCustomNameEnable.SetCurSel(iTempIndex);

	iTempIndex = m_cboSeparator.GetCurSel();
	m_cboSeparator.ResetContent();
	m_cboSeparator.SetItemData((m_cboSeparator.AddString(_T("_"))), E_SEPARATOR_LINE);
	iTempIndex = (iTempIndex < m_cboSeparator.GetCount()) ? iTempIndex : DEFAULT_SEL_INDEX;
	m_cboSeparator.SetCurSel(iTempIndex);

	iTempIndex = m_cboResponseEnable.GetCurSel();
	m_cboResponseEnable.ResetContent();
	m_cboResponseEnable.SetItemData((m_cboResponseEnable.AddString(GetTextEx(IDS_ITS_YES))), 1);
	m_cboResponseEnable.SetItemData((m_cboResponseEnable.AddString(GetTextEx(IDS_ITS_NO))), 0);
	iTempIndex = (iTempIndex < m_cboResponseEnable.GetCount()) ? iTempIndex : DEFAULT_SEL_INDEX;
	m_cboResponseEnable.SetCurSel(iTempIndex);

	iTempIndex = m_cboVersion.GetCurSel();
	m_cboVersion.ResetContent();
	m_cboVersion.SetItemData((m_cboVersion.AddString(GetTextEx(IDS_VERSION_70_DOWN))), 0);
	m_cboVersion.SetItemData((m_cboVersion.AddString(GetTextEx(IDS_VERSION_71_UP))), 1);
	iTempIndex = (iTempIndex < m_cboVersion.GetCount()) ? iTempIndex : DEFAULT_SEL_INDEX;
	m_cboVersion.SetCurSel(iTempIndex);

	CTime timeNow = CTime::GetCurrentTime();
	timeNow = CTime(timeNow.GetYear(), timeNow.GetMonth(), timeNow.GetDay(), 0, 0, 0);
	m_timeStartTime.SetFormat(_T("HH:mm:ss"));
	m_timeStartTime.SetTime(&timeNow);

	m_timeEndTime.SetFormat(_T("HH:mm:ss"));
	timeNow = CTime(timeNow.GetYear(), timeNow.GetMonth(), timeNow.GetDay(), 23, 59, 59);
	m_timeEndTime.SetTime(&timeNow);
}

void CLS_ITSPlatformConfig::OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType, void* _pPara, int _iUserData)
{
	switch(_iParaType)
	{
	case PARA_ITS_PLATCFGINFO:
		{
			UI_UpdatePlatformCfg();
		}
		break;
	case PARA_ITS_PICUPLOADCFG:
		{
			UI_UpdatePicunload();
		}
		break;
	case PARA_ITS_DELPICSTRATEGY:
		{
			UI_UpdatePicdel();	
		}
		break;
	default:
		break;
	}
}

//设置中间件配置
void CLS_ITSPlatformConfig::OnBnClickedBtnPaltformCfgSet()
{
	if (m_iLogonId < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonId);
		return;
	}

	int iRet = RET_FAILED;
	ITSPlatformCfgInfo tITSPlatformCfgInfo = {0};
	tITSPlatformCfgInfo.iSize = sizeof(ITSPlatformCfgInfo);
	GetDlgItem(IDC_EDT_PALTFORM_ID)->GetWindowText(tITSPlatformCfgInfo.cPlatID, sizeof(tITSPlatformCfgInfo.cPlatID) - 1);
	GetDlgItem(IDC_IPADDR_PALTFORM_IP)->GetWindowText(tITSPlatformCfgInfo.cPlatIp, sizeof(tITSPlatformCfgInfo.cPlatIp));
	tITSPlatformCfgInfo.iPlatPort = GetDlgItemInt(IDC_EDT_PALTFORM_PORT);

	iRet = NetClient_SetITSExtraInfo(m_iLogonId, ITS_EXTRAINFO_CMD_PLATCFGINFO, m_iChannelNo, &tITSPlatformCfgInfo, sizeof(ITSPlatformCfgInfo));
	if (RET_SUCCESS != iRet)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo ITS_EXTRAINFO_CMD_PLATCFGINFO(%d，%d)",m_iLogonId, m_iChannelNo);
		goto EXIT_FUNC;
	}

	AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo ITS_EXTRAINFO_CMD_PLATCFGINFO(%d，%d)",m_iLogonId, m_iChannelNo);

EXIT_FUNC:
	return;
}

//设置图像上传参数
void CLS_ITSPlatformConfig::OnBnClickedBtnPicunloadSet()
{
	if (m_iLogonId < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonId);
		return;
	}

	int iRet = RET_FAILED;

	ITSPicUploadCfgInfo tITSPicUploadCfgInfo = {0};

	tITSPicUploadCfgInfo.iSize = sizeof(ITSPicUploadCfgInfo);

	GetDlgItem(IDC_IPADDR_PICUNLOAD_SERVER_IP)->GetWindowText(tITSPicUploadCfgInfo.cPlatIp, sizeof(tITSPicUploadCfgInfo.cPlatIp));
	tITSPicUploadCfgInfo.iPlatPort = GetDlgItemInt(IDC_EDT_PICUNLOAD_SERVER_PORT);
	tITSPicUploadCfgInfo.iVersion = (int)m_cboVersion.GetItemData(m_cboVersion.GetCurSel());
	tITSPicUploadCfgInfo.iResponse = (int)m_cboResponseEnable.GetItemData(m_cboResponseEnable.GetCurSel());
	tITSPicUploadCfgInfo.iCustomFileName = (int)m_cboCustomNameEnable.GetItemData(m_cboCustomNameEnable.GetCurSel());
	CString cstrNameSection;
	for (int i = PIC_NAME_SECTION_MIN; i < PIC_NAME_SECTION_MAX; ++i)
	{
		if (TRUE == m_chkPicNameSection[i].GetCheck())
		{
			cstrNameSection += IntToString(i) + _T(",");
		}
	}
	if (!cstrNameSection.IsEmpty())
	{
		cstrNameSection = cstrNameSection.Left(cstrNameSection.GetLength() - 1);
	}

	strncpy_s(tITSPicUploadCfgInfo.cNameSection, LEN_64, cstrNameSection, LEN_64);
	CString cstrSeparator = GetSeparatorType((SeparatorType)m_cboSeparator.GetItemData(m_cboSeparator.GetCurSel()));
	strncpy_s(tITSPicUploadCfgInfo.cSeparator, LEN_16, cstrSeparator, LEN_16);

	iRet = NetClient_SetITSExtraInfo(m_iLogonId, ITS_EXTRAINFO_CMD_PICUPLOADCFG, m_iChannelNo, &tITSPicUploadCfgInfo, sizeof(ITSPicUploadCfgInfo));
	if (RET_SUCCESS != iRet)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo ITS_EXTRAINFO_CMD_PICUPLOADCFG(%d，%d)",m_iLogonId, m_iChannelNo);
		goto EXIT_FUNC;
	}

	AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo ITS_EXTRAINFO_CMD_PICUPLOADCFG(%d，%d)",m_iLogonId, m_iChannelNo);

EXIT_FUNC:
	return;
}

CString CLS_ITSPlatformConfig::GetSeparatorType(SeparatorType _enumSeparatorType)
{
	CString cstrSeparatorType;
	switch (_enumSeparatorType)
	{
	case E_SEPARATOR_LINE:
		cstrSeparatorType = _T("_");
		break;
	default:
		AddLog(LOG_TYPE_MSG,"","GetSeparatorType Illeage SeparatorType(%d)",(int)_enumSeparatorType);
		break;
	}

	return cstrSeparatorType;
}

//设置图片删除策略
void CLS_ITSPlatformConfig::OnBnClickedBtnPicdelSet()
{
	if (m_iLogonId < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonId);
		return;
	}

	int iRet = RET_FAILED;
	ITSDelPicStrategy tITSDelPicStrategy = {0};
	tITSDelPicStrategy.iSize = sizeof(ITSDelPicStrategy);
	tITSDelPicStrategy.iDelNum = GetDlgItemInt(IDC_EDT_PICDEL_NUM);
	tITSDelPicStrategy.iKeepDay = GetDlgItemInt(IDC_EDT_PICDEL_KEEPDAY);

	GetTimeWidgetValue(&m_timeStartTime, &tITSDelPicStrategy.tDelStartTime);
	GetTimeWidgetValue(&m_timeEndTime, &tITSDelPicStrategy.tDelStopTime);

	iRet = NetClient_SetITSExtraInfo(m_iLogonId, ITS_EXTRAINFO_CMD_DELPICSTRATEGY, m_iChannelNo, &tITSDelPicStrategy, sizeof(ITSDelPicStrategy));
	if (RET_SUCCESS != iRet)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo ITS_EXTRAINFO_CMD_DELPICSTRATEGY(%d，%d)",m_iLogonId, m_iChannelNo);
		goto EXIT_FUNC;
	}
	AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo ITS_EXTRAINFO_CMD_DELPICSTRATEGY(%d，%d)",m_iLogonId, m_iChannelNo);

EXIT_FUNC:
	return;


}

int CLS_ITSPlatformConfig::GetTimeWidgetValue( CDateTimeCtrl* _ptimeWidget, NVS_FILE_TIME* _ptNvsTime )
{
	if (NULL == _ptimeWidget || NULL == _ptNvsTime)
	{
		AddLog(LOG_TYPE_MSG,"","GetTimeWidgetValue Illegal parameter !");
		return RET_FAILED;
	}

	int iRet = RET_FAILED;

	__try
	{
		CTime timeTemp;
		_ptimeWidget->GetTime(timeTemp);
		_ptNvsTime->iYear = timeTemp.GetYear();
		_ptNvsTime->iMonth = timeTemp.GetMonth();
		_ptNvsTime->iDay = timeTemp.GetDay();
		_ptNvsTime->iHour = timeTemp.GetHour();
		_ptNvsTime->iMinute = timeTemp.GetMinute();
		_ptNvsTime->iSecond = timeTemp.GetSecond();

		iRet = RET_SUCCESS;
	}
	__except(EXCEPTION_EXECUTE_HANDLER) 
	{
		AddLog(LOG_TYPE_FAIL,"","GetTimeWidgetValue System func Err !");
		iRet = RET_FAILED;
	}

	return iRet;
}

int CLS_ITSPlatformConfig::SetTimeWidgetValue( CDateTimeCtrl* _ptimeWidget, NVS_FILE_TIME _tNvsTime )
{
	if (NULL == _ptimeWidget)
	{
		AddLog(LOG_TYPE_MSG,"","SetTimeWidgetValue Illegal parameter !");
		return RET_FAILED;
	}

	int iRet = RET_FAILED;

	__try
	{
		CTime timeNow = CTime::GetCurrentTime();
		timeNow = CTime(timeNow.GetYear(), timeNow.GetMonth(), timeNow.GetDay(), _tNvsTime.iHour, _tNvsTime.iMinute, _tNvsTime.iSecond);
		_ptimeWidget->SetTime(&timeNow);
		iRet = RET_SUCCESS;
	}
	__except(EXCEPTION_EXECUTE_HANDLER) 
	{
		AddLog(LOG_TYPE_FAIL,"","SetTimeWidgetValue System func Err !");
		iRet = RET_FAILED;
	}

	return iRet;
}

void CLS_ITSPlatformConfig::UI_UpdatePlatformCfg()
{
	if (m_iLogonId < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonId);
		return;
	}

	int iRet = RET_FAILED;
	ITSPlatformCfgInfo tITSPlatformCfgInfo = {0};
	tITSPlatformCfgInfo.iSize = sizeof(ITSPlatformCfgInfo);
	iRet = NetClient_GetITSExtraInfo(m_iLogonId, ITS_EXTRAINFO_CMD_PLATCFGINFO, m_iChannelNo, &tITSPlatformCfgInfo, sizeof(ITSPlatformCfgInfo));
	if (RET_SUCCESS != iRet)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSExtraInfo ITS_EXTRAINFO_CMD_PLATCFGINFO(%d，%d)",m_iLogonId, m_iChannelNo);
		goto EXIT_FUNC;
	}

	AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSExtraInfo ITS_EXTRAINFO_CMD_PLATCFGINFO(%d，%d)",m_iLogonId, m_iChannelNo);

	GetDlgItem(IDC_EDT_PALTFORM_ID)->SetWindowText(tITSPlatformCfgInfo.cPlatID);
	GetDlgItem(IDC_IPADDR_PALTFORM_IP)->SetWindowText(tITSPlatformCfgInfo.cPlatIp);
	SetDlgItemInt(IDC_EDT_PALTFORM_PORT, tITSPlatformCfgInfo.iPlatPort);

EXIT_FUNC:
	return;

}

void CLS_ITSPlatformConfig::UI_UpdatePicunload()
{
	if (m_iLogonId < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonId);
		return;
	}

	int iRet = RET_FAILED;
	CString cstrNameSection;
	CString cstrSeparator;
	ITSPicUploadCfgInfo tITSPicUploadCfgInfo = {0};
	tITSPicUploadCfgInfo.iSize = sizeof(ITSPicUploadCfgInfo);
	iRet = NetClient_GetITSExtraInfo(m_iLogonId, ITS_EXTRAINFO_CMD_PICUPLOADCFG, m_iChannelNo, &tITSPicUploadCfgInfo, sizeof(ITSPicUploadCfgInfo));
	if (RET_SUCCESS != iRet)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSExtraInfo ITS_EXTRAINFO_CMD_PICUPLOADCFG(%d，%d)",m_iLogonId, m_iChannelNo);
		goto EXIT_FUNC;
	}

	AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSExtraInfo ITS_EXTRAINFO_CMD_PICUPLOADCFG(%d，%d)",m_iLogonId, m_iChannelNo);

	GetDlgItem(IDC_IPADDR_PICUNLOAD_SERVER_IP)->SetWindowText(tITSPicUploadCfgInfo.cPlatIp);
	SetDlgItemInt(IDC_EDT_PICUNLOAD_SERVER_PORT, tITSPicUploadCfgInfo.iPlatPort);
	m_cboVersion.SetCurSel(GetCboSel(&m_cboVersion, tITSPicUploadCfgInfo.iVersion));
	m_cboResponseEnable.SetCurSel(GetCboSel(&m_cboResponseEnable, tITSPicUploadCfgInfo.iResponse));
	m_cboCustomNameEnable.SetCurSel(GetCboSel(&m_cboCustomNameEnable, tITSPicUploadCfgInfo.iCustomFileName));

	cstrNameSection =  tITSPicUploadCfgInfo.cNameSection;
	for (int i = PIC_NAME_SECTION_MIN; i < PIC_NAME_SECTION_MAX; ++i)
	{
		m_chkPicNameSection[i].SetCheck(BST_UNCHECKED);
	}

	while (-1 != cstrNameSection.Find(_T(',')))
	{
		int iPos = cstrNameSection.Find(_T(','));
		CString cstrTempSel = cstrNameSection.Left(iPos);
		int iTempSel = _ttoi(cstrTempSel);
		if (iTempSel >= PIC_NAME_SECTION_MIN && iTempSel < PIC_NAME_SECTION_MAX)
		{
			m_chkPicNameSection[iTempSel].SetCheck(BST_CHECKED);
		}

		cstrNameSection = cstrNameSection.Right(cstrNameSection.GetLength() - iPos - 1);

		if (-1 == cstrNameSection.Find(_T(',')) && !cstrNameSection.IsEmpty())
		{
			cstrNameSection += _T(',');
		}
	}

	m_cboSeparator.SetCurSel(DEFAULT_SEL_INDEX);
	cstrSeparator = tITSPicUploadCfgInfo.cSeparator;
	if (_T('_') == cstrSeparator)
	{
		m_cboSeparator.SetCurSel(GetCboSel(&m_cboSeparator, E_SEPARATOR_LINE));
	}

EXIT_FUNC:
	return;
}

void CLS_ITSPlatformConfig::UI_UpdatePicdel()
{
	if (m_iLogonId < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonId);
		return;
	}

	int iRet = RET_FAILED;
	ITSDelPicStrategy tITSDelPicStrategy = {0};
	tITSDelPicStrategy.iSize = sizeof(ITSDelPicStrategy);

	iRet = NetClient_GetITSExtraInfo(m_iLogonId, ITS_EXTRAINFO_CMD_DELPICSTRATEGY, m_iChannelNo, &tITSDelPicStrategy, sizeof(ITSDelPicStrategy));
	if (RET_SUCCESS != iRet)
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSExtraInfo ITS_EXTRAINFO_CMD_DELPICSTRATEGY(%d，%d)",m_iLogonId, m_iChannelNo);
		goto EXIT_FUNC;
	}
	AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSExtraInfo ITS_EXTRAINFO_CMD_DELPICSTRATEGY(%d，%d)",m_iLogonId, m_iChannelNo);

	SetDlgItemInt(IDC_EDT_PICDEL_NUM, tITSDelPicStrategy.iDelNum);
	SetDlgItemInt(IDC_EDT_PICDEL_KEEPDAY, tITSDelPicStrategy.iKeepDay);
	SetTimeWidgetValue(&m_timeStartTime, tITSDelPicStrategy.tDelStartTime);
	SetTimeWidgetValue(&m_timeEndTime, tITSDelPicStrategy.tDelStopTime);

EXIT_FUNC:
	return;
}