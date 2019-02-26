// ITSIllegalParkPage.cpp : implementation file
//

#include "stdafx.h"
#include "ITSIllegalParkPage.h"
#include "ITSSetVCAPage.h"

// CLS_ITSIllegalParkPage dialog

IMPLEMENT_DYNAMIC(CLS_ITSIllegalParkPage, CDialog)

CLS_ITSIllegalParkPage::CLS_ITSIllegalParkPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ITSIllegalParkPage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
	m_iStreamNo = 0;
}

CLS_ITSIllegalParkPage::~CLS_ITSIllegalParkPage()
{
}

void CLS_ITSIllegalParkPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_cboType);
	DDX_Control(pDX, IDC_COMBO_COUNT, m_cboCount);
	DDX_Control(pDX, IDC_EDIT_MC1, m_edtMC[0]);
	DDX_Control(pDX, IDC_EDIT_OCW1, m_edtOCW[0]);
	DDX_Control(pDX, IDC_EDIT_MC2, m_edtMC[1]);
	DDX_Control(pDX, IDC_EDIT_OCW2, m_edtOCW[1]);
	DDX_Control(pDX, IDC_EDIT_MC3, m_edtMC[2]);
	DDX_Control(pDX, IDC_EDIT_OCW3, m_edtOCW[2]);
	DDX_Control(pDX, IDC_EDIT_MC4, m_edtMC[3]);
	DDX_Control(pDX, IDC_EDIT_OCW4, m_edtOCW[3]);
	DDX_Control(pDX, IDC_EDIT_MC5, m_edtMC[4]);
	DDX_Control(pDX, IDC_EDIT_OCW5, m_edtOCW[4]);
	DDX_Control(pDX, IDC_EDIT_MC6, m_edtMC[5]);
	DDX_Control(pDX, IDC_EDIT_OCW6, m_edtOCW[5]);
	DDX_Control(pDX, IDC_EDIT_MC7, m_edtMC[6]);
	DDX_Control(pDX, IDC_EDIT_OCW7, m_edtOCW[6]);
	DDX_Control(pDX, IDC_EDIT_MC8, m_edtMC[7]);
	DDX_Control(pDX, IDC_EDIT_OCW8, m_edtOCW[7]);
	DDX_Control(pDX, IDC_BUTTON_LICENSE_SET, m_btnLicenseSet);
	DDX_Control(pDX, IDC_BUTTON_ILLEGALPARK, m_btnIllegalPark);
	DDX_Control(pDX, IDC_COMBO_CMD, m_cboSendCmd);
	DDX_Control(pDX, IDC_COMBO_COMMONINFO_TYPE, m_cboComInfo);
	DDX_Control(pDX, IDC_COMBO_ROADID, m_cboRoadId);
}


BEGIN_MESSAGE_MAP(CLS_ITSIllegalParkPage, CLS_BasePage)
	ON_BN_CLICKED(IDC_BUTTON_ILLEGALPARK, &CLS_ITSIllegalParkPage::OnBnClickedButtonIllegalpark)
	ON_BN_CLICKED(IDC_BUTTON_LICENSE_SET, &CLS_ITSIllegalParkPage::OnBnClickedButtonLicenseSet)
	ON_BN_CLICKED(IDC_BUTTON_CMD_SET, &CLS_ITSIllegalParkPage::OnBnClickedButtonCmd)
	ON_BN_CLICKED(IDC_BUTTON_COMMONINFO_SET, &CLS_ITSIllegalParkPage::OnBnClickedButtonCommoninfoSet)
	ON_CBN_SELCHANGE(IDC_COMBO_COMMONINFO_TYPE, &CLS_ITSIllegalParkPage::OnCbnSelchangeComboCommoninfoType)
	ON_BN_CLICKED(IDC_BUTTON_COMPOUND_SET, &CLS_ITSIllegalParkPage::OnBnClickedButtonCompoundSet)
	ON_CBN_SELCHANGE(IDC_COMBO_ROADID, &CLS_ITSIllegalParkPage::OnCbnSelchangeComboRoadid)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, &CLS_ITSIllegalParkPage::OnCbnSelchangeComboType)
END_MESSAGE_MAP()


// CLS_ITSIllegalParkPage message handlers
BOOL CLS_ITSIllegalParkPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();
	m_cboType.AddString("0");
	m_cboType.AddString("1");
	m_cboType.SetCurSel(0);

	for (int i=0; i<8; i++)
	{
		CString strNo;
		strNo.Format("%d", i);
		m_cboCount.AddString(strNo);
		m_edtMC[i].SetLimitText(5);
	}
	m_cboCount.SetCurSel(0);

	m_cboSendCmd.ResetContent();
	m_cboSendCmd.AddString(GetTextEx(IDS_CONFIG_ITS_CMDANDILPARK_START));
	m_cboSendCmd.AddString(GetTextEx(IDS_CONFIG_ITS_CMDANDILPARK_ENDRECORD));
	m_cboSendCmd.AddString(GetTextEx(IDS_CONFIG_ITS_CMDANDILPARK_FINISH));
	m_cboSendCmd.SetCurSel(0);

	m_cboComInfo.ResetContent();
	m_cboComInfo.AddString(GetTextEx(IDS_CONFIG_ITS_ITSPARAM_RESERVED));
	m_cboComInfo.AddString(GetTextEx(IDS_CONFIG_ITS_ITSPARAM_MACHINERYCODE));
	m_cboComInfo.AddString(GetTextEx(IDS_CONFIG_ITS_ITSPARAM_MACHINERYNAME));
	m_cboComInfo.SetCurSel(0);

	m_cboRoadId.ResetContent();
	m_cboRoadId.AddString("0");
	m_cboRoadId.AddString("1");
	m_cboRoadId.AddString("2");
	m_cboRoadId.AddString("3");
	m_cboRoadId.SetCurSel(0);
	
	UI_UpdateDialog();

	return TRUE;
}

void CLS_ITSIllegalParkPage::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
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
		m_iStreamNo = 0;
	}
	else
	{
		m_iStreamNo = _iStreamNo;
	}
	UI_ModifyChar();
	UI_UpdateParam();
}

void CLS_ITSIllegalParkPage::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_ITSIllegalParkPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_BUTTON_ILLEGALPARK,IDS_CONFIG_ITS_ILLEGALPARK);
	SetDlgItemTextEx(IDC_STATIC_LICENSE,IDS_CONFIG_ITS_ILLEGALPARK_LICENSE);
	SetDlgItemTextEx(IDC_STATIC_TYPE,IDS_CONFIG_ITS_ILLEGALPARK_TYPE);
	SetDlgItemTextEx(IDC_STATIC_COUNT,IDS_CONFIG_ITS_ILLEGALPARK_COUNT);
	SetDlgItemTextEx(IDC_STATIC_MC,IDS_CONFIG_ITS_ILLEGALPARK_MC);
	SetDlgItemTextEx(IDC_STATIC_OCW,IDS_CONFIG_ITS_ILLEGALPARK_OCW);
	SetDlgItemTextEx(IDC_BUTTON_LICENSE_SET,IDS_SET);

	SetDlgItemTextEx(IDC_STATIC_GROUPTEXT,IDS_CONFIG_ITS_CMDANDILPARK_CMD);
	SetDlgItemTextEx(IDC_STATIC_CMD,IDS_CONFIG_ITS_CMDANDILPARK_CMD);
	SetDlgItemTextEx(IDC_BUTTON_CMD_SET,IDS_SET);

	SetDlgItemTextEx(IDC_STATIC_COMMONINFO,IDS_CONFIG_ITS_ITSPARAM_COMMONINFO);
	SetDlgItemTextEx(IDC_STATIC_COMMONINFO_TYPE,IDS_CONFIG_ITS_ITSPARAM_TYPE);
	SetDlgItemTextEx(IDC_STATIC_COMMONINFO_CONTENT,IDS_CONFIG_ITS_ITSPARAM_CONTENT);
	SetDlgItemTextEx(IDC_BUTTON_COMMONINFO_SET,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_RADAR,IDS_CONFIG_ITS_ITSPARAM_COMPOUNDPARA);
	SetDlgItemTextEx(IDC_STATIC_ROADID,IDS_CONFIG_ITS_ITSPARAM_ROADID);
	SetDlgItemTextEx(IDC_STATIC_MATCH_SPEEDTIME,IDS_CONFIG_ITS_ITSPARAM_MATCHTIME);
	SetDlgItemTextEx(IDC_STATIC_RADAR_SPEEDRANGE,IDS_CONFIG_ITS_ITSPARAM_SPEEDRANGE);
	SetDlgItemTextEx(IDC_BUTTON_COMPOUND_SET,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_FOCUSSTA,IDS_CONFIG_ITS_FOCUSSTA);

}

void CLS_ITSIllegalParkPage::UI_UpdateParam()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iType = m_cboComInfo.GetCurSel();
	ITS_DevCommonInfo tDevCommonInfo = {0};
	tDevCommonInfo.iType = iType;
	int iCommand = NET_CLIENT_ITS_DEV_COMMONINFO;
	int iBufSize  = sizeof(ITS_DevCommonInfo);
	int iBytesReturned = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID, iCommand, m_iChannelNo, &tDevCommonInfo, iBufSize, &iBytesReturned);
	if (0 == iRet)
	{
		SetDlgItemText(IDC_EDIT_COMMONINFO_CONTENT, tDevCommonInfo.cCommonInfo);
		AddLog(LOG_TYPE_SUCC, "", "NetClient_GetDevConfig (%d,%d,%s)",iCommand, tDevCommonInfo.iType, tDevCommonInfo.cCommonInfo);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetDevConfig (%d,%d,%s)",iCommand, tDevCommonInfo.iType, tDevCommonInfo.cCommonInfo);
	}

	ITS_ComPoundParam tITS_ComPoundParam = {0};
	tITS_ComPoundParam.iITSRoadID = 0;//默认更新第一路
	int iCmd = NET_CLIENT_ITS_COMPOUNDPARAM;
	iBufSize = sizeof(ITS_ComPoundParam);
	iBytesReturned = 0;
	iRet = NetClient_GetDevConfig(m_iLogonID, iCmd, m_iChannelNo, &tITS_ComPoundParam, iBufSize, &iBytesReturned);
	if (0 == iRet)
	{
		m_cboRoadId.SetCurSel(tITS_ComPoundParam.iITSRoadID);
		SetDlgItemInt(IDC_EDIT_RADAR_MATCHTIME, tITS_ComPoundParam.iRadarMatchTime);
		SetDlgItemInt(IDC_EDIT_RADAR_MINSPEED, tITS_ComPoundParam.iRadarMinSpeed);
		SetDlgItemInt(IDC_EDIT_RADAR_MAXSPEED, tITS_ComPoundParam.iRadarMaxSpeed);
		AddLog(LOG_TYPE_SUCC, "", "NetClient_GetDevConfig (%d,%d,%d,%d,%d)",iCmd, tITS_ComPoundParam.iITSRoadID, tITS_ComPoundParam.iRadarMatchTime, tITS_ComPoundParam.iRadarMinSpeed, tITS_ComPoundParam.iRadarMaxSpeed);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetDevConfig (%d,%d,%d,%d,%d)",iCmd, tITS_ComPoundParam.iITSRoadID, tITS_ComPoundParam.iRadarMatchTime, tITS_ComPoundParam.iRadarMinSpeed, tITS_ComPoundParam.iRadarMaxSpeed);
	}

}

void CLS_ITSIllegalParkPage::OnBnClickedButtonIllegalpark()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	m_SetVCAPage.OnChannelChanged(m_iLogonID, m_iChannelNo, m_iStreamNo);
	m_SetVCAPage.DoModal();
}

void CLS_ITSIllegalParkPage::OnMainNotify( int _iLogonID,int _wParam, int _lParam,int _iUserData )
{
	m_SetVCAPage.OnMainNotify(_iLogonID, _wParam, _lParam, _iUserData);
}

void CLS_ITSIllegalParkPage::OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType, void* _pPara, int _iUser)
{
	STR_Para* _strPara;
	_strPara = (STR_Para*) _pPara;

	switch(_iParaType)
	{

	case PARA_COMMAND_ITS_FOCUS:
		{
			SetDlgItemInt(IDC_EDIT_FOCUSSTA, _strPara->m_iPara[0], FALSE);
		}
		break;
	default:
		break;
	}
}

void CLS_ITSIllegalParkPage::OnBnClickedButtonLicenseSet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	ITS_LicenseOptimizeOther  tITSLicenseOptimizeOther = {0};
	tITSLicenseOptimizeOther.iType =  m_cboType.GetCurSel();
	tITSLicenseOptimizeOther.iCount = m_cboCount.GetCurSel();

	GetDlgItemText(IDC_EDIT_MC1, tITSLicenseOptimizeOther.cModifyChar[0], 5);
	GetDlgItemText(IDC_EDIT_MC2, tITSLicenseOptimizeOther.cModifyChar[1], 5);
	GetDlgItemText(IDC_EDIT_MC3, tITSLicenseOptimizeOther.cModifyChar[2], 5);
	GetDlgItemText(IDC_EDIT_MC4, tITSLicenseOptimizeOther.cModifyChar[3], 5);
	GetDlgItemText(IDC_EDIT_MC5, tITSLicenseOptimizeOther.cModifyChar[4], 5);
	GetDlgItemText(IDC_EDIT_MC6, tITSLicenseOptimizeOther.cModifyChar[5], 5);
	GetDlgItemText(IDC_EDIT_MC7, tITSLicenseOptimizeOther.cModifyChar[6], 5);
	GetDlgItemText(IDC_EDIT_MC8, tITSLicenseOptimizeOther.cModifyChar[7], 5);

	tITSLicenseOptimizeOther.iOtherCharWeight[0] = GetDlgItemInt(IDC_EDIT_OCW1);
	tITSLicenseOptimizeOther.iOtherCharWeight[1] = GetDlgItemInt(IDC_EDIT_OCW2);
	tITSLicenseOptimizeOther.iOtherCharWeight[2] = GetDlgItemInt(IDC_EDIT_OCW3);
	tITSLicenseOptimizeOther.iOtherCharWeight[3] = GetDlgItemInt(IDC_EDIT_OCW4);
	tITSLicenseOptimizeOther.iOtherCharWeight[4] = GetDlgItemInt(IDC_EDIT_OCW5);
	tITSLicenseOptimizeOther.iOtherCharWeight[5] = GetDlgItemInt(IDC_EDIT_OCW6);
	tITSLicenseOptimizeOther.iOtherCharWeight[6] = GetDlgItemInt(IDC_EDIT_OCW7);
	tITSLicenseOptimizeOther.iOtherCharWeight[7] = GetDlgItemInt(IDC_EDIT_OCW8);

	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_LICENSEOPTIMIZEOTHER_CMD_SET, NULL,
		&tITSLicenseOptimizeOther, sizeof(ITS_LicenseOptimizeOther));
	if(iRet == 0)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo(ITS_LICENSEOPTIMIZEOTHER_CMD_SET)");
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo(ITS_LICENSEOPTIMIZEOTHER_CMD_SET)");
	}
}

BOOL CLS_ITSIllegalParkPage::UI_ModifyChar()
{
	if (m_iLogonID < 0)
		return FALSE;

	ITS_LicenseOptimizeOther  tITSLicenseOptimizeOther = {0};
	tITSLicenseOptimizeOther.iType = m_cboType.GetCurSel();
	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_LICENSEOPTIMIZEOTHER_CMD_GET, NULL,
		&tITSLicenseOptimizeOther, sizeof(ITS_LicenseOptimizeOther));
	if(iRet == 0)
	{
		//m_cboType.SetCurSel(tITSLicenseOptimizeOther.iType);
		m_cboCount.SetCurSel(tITSLicenseOptimizeOther.iCount);
		SetDlgItemText(IDC_EDIT_MC1, tITSLicenseOptimizeOther.cModifyChar[0]);
		SetDlgItemText(IDC_EDIT_MC2, tITSLicenseOptimizeOther.cModifyChar[1]);
		SetDlgItemText(IDC_EDIT_MC3, tITSLicenseOptimizeOther.cModifyChar[2]);
		SetDlgItemText(IDC_EDIT_MC4, tITSLicenseOptimizeOther.cModifyChar[3]);
		SetDlgItemText(IDC_EDIT_MC5, tITSLicenseOptimizeOther.cModifyChar[4]);
		SetDlgItemText(IDC_EDIT_MC6, tITSLicenseOptimizeOther.cModifyChar[5]);
		SetDlgItemText(IDC_EDIT_MC7, tITSLicenseOptimizeOther.cModifyChar[6]);
		SetDlgItemText(IDC_EDIT_MC8, tITSLicenseOptimizeOther.cModifyChar[7]);

		SetDlgItemInt(IDC_EDIT_OCW1, tITSLicenseOptimizeOther.iOtherCharWeight[0]);
		SetDlgItemInt(IDC_EDIT_OCW2, tITSLicenseOptimizeOther.iOtherCharWeight[1]);
		SetDlgItemInt(IDC_EDIT_OCW3, tITSLicenseOptimizeOther.iOtherCharWeight[2]);
		SetDlgItemInt(IDC_EDIT_OCW4, tITSLicenseOptimizeOther.iOtherCharWeight[3]);
		SetDlgItemInt(IDC_EDIT_OCW5, tITSLicenseOptimizeOther.iOtherCharWeight[4]);
		SetDlgItemInt(IDC_EDIT_OCW6, tITSLicenseOptimizeOther.iOtherCharWeight[5]);
		SetDlgItemInt(IDC_EDIT_OCW7, tITSLicenseOptimizeOther.iOtherCharWeight[6]);
		SetDlgItemInt(IDC_EDIT_OCW8, tITSLicenseOptimizeOther.iOtherCharWeight[7]);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSExtraInfo(ITS_LICENSEOPTIMIZEOTHER_CMD_GET)");
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSExtraInfo(ITS_LICENSEOPTIMIZEOTHER_CMD_GET)");
	}
	return TRUE;
}

void CLS_ITSIllegalParkPage::OnBnClickedButtonCmd()
{
	// TODO: Add your control notification handler code here
	int iStep = m_cboSendCmd.GetCurSel();
    int iCmd = COMMAND_ID_ITS_FOCUS;
	int iRet = NetClient_SendCommand(m_iLogonID, iCmd, m_iChannelNo, &iStep, sizeof(int));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SendCommand (%d,%d)",iCmd,iStep);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SendCommand (%d,%d)",iCmd,iStep);
	}

}

void CLS_ITSIllegalParkPage::OnBnClickedButtonCommoninfoSet()
{
	// TODO: Add your control notification handler code here
	int iType = m_cboComInfo.GetCurSel();
	CString cstrCommonInfo;
	GetDlgItemText(IDC_EDIT_COMMONINFO_CONTENT, cstrCommonInfo);
	ITS_DevCommonInfo tDevCommonInfo = {0};
	int iCommand = NET_CLIENT_ITS_DEV_COMMONINFO;
	tDevCommonInfo.iSize = sizeof(ITS_DevCommonInfo);
	tDevCommonInfo.iType = iType;
	memcpy_s(tDevCommonInfo.cCommonInfo, LEN_64, cstrCommonInfo.GetBuffer(), cstrCommonInfo.GetLength());
	int iBufSize  = sizeof(ITS_DevCommonInfo);
	int iRet = NetClient_SetDevConfig(m_iLogonID, iCommand, m_iChannelNo, &tDevCommonInfo, iBufSize);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetDevConfig (%d,%d,%s)",iCommand, tDevCommonInfo.iType, tDevCommonInfo.cCommonInfo);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig (%d,%d,%s)",iCommand, tDevCommonInfo.iType, tDevCommonInfo.cCommonInfo);
	}

}

void CLS_ITSIllegalParkPage::OnCbnSelchangeComboCommoninfoType()
{
	// TODO: Add your control notification handler code here
	int iType = m_cboComInfo.GetCurSel();
	ITS_DevCommonInfo tDevCommonInfo = {0};
	tDevCommonInfo.iType = iType;
	int iCommand = NET_CLIENT_ITS_DEV_COMMONINFO;
	int iBufSize  = sizeof(ITS_DevCommonInfo);
	int iBytesReturned = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID, iCommand, m_iChannelNo, &tDevCommonInfo, iBufSize, &iBytesReturned);
	if (0 == iRet)
	{
		SetDlgItemText(IDC_EDIT_COMMONINFO_CONTENT, tDevCommonInfo.cCommonInfo);
		AddLog(LOG_TYPE_SUCC, "", "NetClient_GetDevConfig (%d,%d,%s)",iCommand, tDevCommonInfo.iType, tDevCommonInfo.cCommonInfo);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetDevConfig (%d,%d,%s)",iCommand, tDevCommonInfo.iType, tDevCommonInfo.cCommonInfo);
	}

}

void CLS_ITSIllegalParkPage::OnBnClickedButtonCompoundSet()
{
	// TODO: Add your control notification handler code here
	ITS_ComPoundParam tITS_ComPoundParam = {0};
	tITS_ComPoundParam.iITSRoadID = m_cboRoadId.GetCurSel();
	tITS_ComPoundParam.iRadarMatchTime = GetDlgItemInt(IDC_EDIT_RADAR_MATCHTIME);
	tITS_ComPoundParam.iRadarMinSpeed = GetDlgItemInt(IDC_EDIT_RADAR_MINSPEED);
	tITS_ComPoundParam.iRadarMaxSpeed = GetDlgItemInt(IDC_EDIT_RADAR_MAXSPEED);
	tITS_ComPoundParam.iSize = sizeof(ITS_ComPoundParam);
	int iCmd = NET_CLIENT_ITS_COMPOUNDPARAM;
	int iRet = NetClient_SetDevConfig(m_iLogonID, iCmd, m_iChannelNo, &tITS_ComPoundParam, tITS_ComPoundParam.iSize);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetDevConfig (%d,%d,%d,%d,%d)",iCmd, tITS_ComPoundParam.iITSRoadID, tITS_ComPoundParam.iRadarMatchTime, tITS_ComPoundParam.iRadarMinSpeed, tITS_ComPoundParam.iRadarMaxSpeed);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig (%d,%d,%d,%d,%d)",iCmd, tITS_ComPoundParam.iITSRoadID, tITS_ComPoundParam.iRadarMatchTime, tITS_ComPoundParam.iRadarMinSpeed, tITS_ComPoundParam.iRadarMaxSpeed);
	}

}

void CLS_ITSIllegalParkPage::OnCbnSelchangeComboRoadid()
{
	// TODO: Add your control notification handler code here
	ITS_ComPoundParam tITS_ComPoundParam = {0};
	tITS_ComPoundParam.iITSRoadID = m_cboRoadId.GetCurSel();
	int iCmd = NET_CLIENT_ITS_COMPOUNDPARAM;
	int iBufSize = sizeof(ITS_ComPoundParam);
	int iBytesReturned = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID, iCmd, m_iChannelNo, &tITS_ComPoundParam, iBufSize, &iBytesReturned);
	if (0 == iRet)
	{
		SetDlgItemInt(IDC_EDIT_RADAR_MATCHTIME, tITS_ComPoundParam.iRadarMatchTime);
		SetDlgItemInt(IDC_EDIT_RADAR_MINSPEED, tITS_ComPoundParam.iRadarMinSpeed);
		SetDlgItemInt(IDC_EDIT_RADAR_MAXSPEED, tITS_ComPoundParam.iRadarMaxSpeed);
		AddLog(LOG_TYPE_SUCC, "", "NetClient_GetDevConfig (%d,%d,%d,%d,%d)",iCmd, tITS_ComPoundParam.iITSRoadID, tITS_ComPoundParam.iRadarMatchTime, tITS_ComPoundParam.iRadarMinSpeed, tITS_ComPoundParam.iRadarMaxSpeed);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetDevConfig (%d,%d,%d,%d,%d)",iCmd, tITS_ComPoundParam.iITSRoadID, tITS_ComPoundParam.iRadarMatchTime, tITS_ComPoundParam.iRadarMinSpeed, tITS_ComPoundParam.iRadarMaxSpeed);
	}
}

void CLS_ITSIllegalParkPage::OnCbnSelchangeComboType()
{
	UI_ModifyChar();
}
