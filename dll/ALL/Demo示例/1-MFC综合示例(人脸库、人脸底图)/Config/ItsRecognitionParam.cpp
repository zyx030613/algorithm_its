// Config\ECOPRecoParamPage.cpp : implementation file
//

#include "stdafx.h"
#include "ItsRecognitionParam.h"


// CLS_ECOPRecoParamPage dialog

IMPLEMENT_DYNAMIC(CLS_ItsRecognitionParam, CDialog)

CLS_ItsRecognitionParam::CLS_ItsRecognitionParam(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ItsRecognitionParam::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannel = -1;
}

CLS_ItsRecognitionParam::~CLS_ItsRecognitionParam()
{
}

void CLS_ItsRecognitionParam::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ROADWAYID, m_cboRoadwayID);
	DDX_Control(pDX, IDC_CHECK_RECOPARAM_ENABLE, m_chkEnable);
	DDX_Control(pDX, IDC_EDIT_MAXPLATE, m_edtMaxPlate);
	DDX_Control(pDX, IDC_EDIT_MAXPLATEWIDTH, m_edtMaxPlateWidth);
	DDX_Control(pDX, IDC_EDIT_MINPLATEWIDTH, m_edtMinPlateWidth);
	DDX_Control(pDX, IDC_EDIT_ENGINENUM, m_edtEngineNum);
	DDX_Control(pDX, IDC_EDIT_AREATYPE, m_edtAreaType);
	DDX_Control(pDX, IDC_EDIT_PLATETYPE, m_edtPlateType);
	DDX_Control(pDX, IDC_EDIT_SPEED, m_edtSpeed);
	DDX_Control(pDX, IDC_EDIT_MAXSKIP, m_edtMaxSkip);
	DDX_Control(pDX, IDC_EDIT_MINVALID, m_edtMinValid);
	DDX_Control(pDX, IDC_EDIT_FRAMEPERCENT, m_edtFramePercent);
	DDX_Control(pDX, IDC_EDIT_MINCAPDIFF, m_edtMinCapDiff);
	DDX_Control(pDX, IDC_EDIT_CALIINFO, m_edtCaliInfo);
	DDX_Control(pDX, IDC_BUTTON_RECOPARAM, m_btnRecoParam);
	DDX_Control(pDX, IDC_CHECK_NOPLATE, m_chkNoPlate);
	DDX_Control(pDX, IDC_COMBO_LICENSE_TYPE, m_cboLicenseType);
	DDX_Control(pDX, IDC_CHECK_NOPLATE, m_chkNoPlate);
	DDX_Control(pDX, IDC_EDIT_FIRSTCHINESE, m_edtFirstChinese);
	DDX_Control(pDX, IDC_EDIT_CHINESE_CONFIG, m_edtFirstChineseConfig);
	DDX_Control(pDX, IDC_EDIT_FIRSTWORD, m_edtFirstWord);
	DDX_Control(pDX, IDC_EDIT_WORD_CONFIG, m_edtFirstWordConfig);
	DDX_Control(pDX, IDC_EDIT_WORDCOUNT, m_edtWordCount);
	DDX_Control(pDX, IDC_EDIT_WORD1, m_edtWord[0]);
	DDX_Control(pDX, IDC_EDIT_WORD2, m_edtWord[1]);
	DDX_Control(pDX, IDC_EDIT_WORD3, m_edtWord[2]);
	DDX_Control(pDX, IDC_EDIT_WORD4, m_edtWord[3]);
	DDX_Control(pDX, IDC_EDIT_WORD5, m_edtWord[4]);
	DDX_Control(pDX, IDC_EDIT_WORD6, m_edtWord[5]);
	DDX_Control(pDX, IDC_EDIT_WORD7, m_edtWord[6]);
	DDX_Control(pDX, IDC_EDIT_WORD8, m_edtWord[7]);
	DDX_Control(pDX, IDC_EDT_WORDNUM1, m_edtWordNum[0]);
	DDX_Control(pDX, IDC_EDT_WORDNUM2, m_edtWordNum[1]);
	DDX_Control(pDX, IDC_EDT_WORDNUM3, m_edtWordNum[2]);
	DDX_Control(pDX, IDC_EDT_WORDNUM4, m_edtWordNum[3]);
	DDX_Control(pDX, IDC_EDT_WORDNUM5, m_edtWordNum[4]);
	DDX_Control(pDX, IDC_EDT_WORDNUM6, m_edtWordNum[5]);
	DDX_Control(pDX, IDC_EDT_WORDNUM7, m_edtWordNum[6]);
	DDX_Control(pDX, IDC_EDT_WORDNUM8, m_edtWordNum[7]);

}


BEGIN_MESSAGE_MAP(CLS_ItsRecognitionParam, CLS_BasePage)
	ON_CBN_SELCHANGE(IDC_COMBO_ROADWAYID, &CLS_ItsRecognitionParam::OnCbnSelchangeComboRoadwayid)
	ON_BN_CLICKED(IDC_BUTTON_RECOPARAM, &CLS_ItsRecognitionParam::OnBnClickedButtonRecoparam)
	ON_BN_CLICKED(IDC_BUTTON_NOPLATE, &CLS_ItsRecognitionParam::OnBnClickedButtonNoplate)
	ON_BN_CLICKED(IDC_BUTTON_LICENSE, &CLS_ItsRecognitionParam::OnBnClickedButtonLicense)
	ON_BN_CLICKED(IDC_BUTTON_OPTIMIZE, &CLS_ItsRecognitionParam::OnBnClickedButtonOptimize)
	ON_BN_CLICKED(IDC_CHECK_RECOPARAM_ENABLE, &CLS_ItsRecognitionParam::OnBnClickedCheckRecoparamEnable)
	ON_EN_CHANGE(IDC_EDIT_WORDCOUNT, &CLS_ItsRecognitionParam::OnEnChangeEditWordcount)
	ON_CBN_SELCHANGE(IDC_COMBO_LICENSE_TYPE, &CLS_ItsRecognitionParam::OnCbnSelchangeComboLicenseType)
	ON_EN_CHANGE(IDC_EDIT_FIRSTCHINESE, &CLS_ItsRecognitionParam::OnEnChangeEditFirstchinese)
END_MESSAGE_MAP()


// CLS_ECOPRecoParamPage message handlers
BOOL CLS_ItsRecognitionParam::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();
	for (int i=0; i<4; i++)
	{
		CString strNo;
		strNo.Format("%d",i);
		m_cboRoadwayID.AddString(strNo);
	}
	m_cboRoadwayID.SetCurSel(0);

	m_edtMaxPlate.SetLimitText(10);
	m_edtMaxPlateWidth.SetLimitText(10);
	m_edtMinPlateWidth.SetLimitText(10);
	m_edtEngineNum.SetLimitText(2);
	m_edtAreaType.SetLimitText(2);
	m_edtPlateType.SetLimitText(2);
	m_edtSpeed.SetLimitText(2);
	m_edtMaxSkip.SetLimitText(4);
	m_edtMinValid.SetLimitText(4);
	m_edtFramePercent.SetLimitText(4);
	m_edtMinCapDiff.SetLimitText(4);
	m_edtCaliInfo.SetLimitText(75);
	m_edtFirstChinese.SetLimitText(3);
	m_edtFirstChineseConfig.SetLimitText(5);
	m_edtFirstWord.SetLimitText(10);
	m_edtFirstWordConfig.SetLimitText(5);

	m_edtWordCount.SetLimitText(5);

	for (int i=0; i<8; i++)
	{
		m_edtWord[i].SetLimitText(2);
		m_edtWordNum[i].SetLimitText(5);
	}
	UI_UpdateDialog();

	return TRUE;
}

void CLS_ItsRecognitionParam::UI_UpdateWordNumber()
{
	int iWordNumber = 0;
	int iI = 0;
	iWordNumber = GetDlgItemInt(IDC_EDIT_WORDCOUNT);
	if(iWordNumber < 0)
	{
		iWordNumber = 0;
	}
	else if(iWordNumber > 8)
	{
		iWordNumber = 8;
	}
	SetDlgItemInt(IDC_EDIT_WORDCOUNT, iWordNumber);
	for(iI = 0; iI < iWordNumber; iI++)
	{
		m_edtWord[iI].EnableWindow(TRUE);
		m_edtWordNum[iI].EnableWindow(TRUE);
	}
	for(iI = iWordNumber; iI < 8; iI++)
	{
		m_edtWord[iI].EnableWindow(FALSE);
		m_edtWordNum[iI].EnableWindow(FALSE);
	}
}

void CLS_ItsRecognitionParam::OnChannelChanged( int _iLogonID,int _iChannelNo,int /*_iStreamNo*/ )
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
	UI_UpdateRecoParam();
	UI_UpdateEnableNoPlate();
	//UI_UpdateLicense();
	UI_UpdateOptimize();
	UI_UpdateWordNumber();
}

void CLS_ItsRecognitionParam::UI_UpdateEnable()
{
	if( 0 == m_chkEnable.GetCheck() )
	{
		m_edtMaxPlate.EnableWindow(FALSE);
		m_edtMaxPlateWidth.EnableWindow(FALSE);	
		m_edtMinPlateWidth.EnableWindow(FALSE);
		m_edtSpeed.EnableWindow(FALSE);
		m_edtMaxSkip.EnableWindow(FALSE);
		m_edtMinValid.EnableWindow(FALSE);
		m_edtEngineNum.EnableWindow(FALSE);
		m_edtAreaType.EnableWindow(FALSE);
		m_edtPlateType.EnableWindow(FALSE);
		m_edtMinCapDiff.EnableWindow(FALSE);
		m_edtCaliInfo.EnableWindow(FALSE);
		m_edtFramePercent.EnableWindow(FALSE);
		m_btnRecoParam.EnableWindow(FALSE);
	}
	else
	{
		m_edtMaxPlate.EnableWindow(TRUE);
		m_edtMaxPlateWidth.EnableWindow(TRUE);	
		m_edtMinPlateWidth.EnableWindow(TRUE);
		m_edtSpeed.EnableWindow(TRUE);
		m_edtMaxSkip.EnableWindow(TRUE);
		m_edtMinValid.EnableWindow(TRUE);
		m_edtEngineNum.EnableWindow(TRUE);
		m_edtAreaType.EnableWindow(TRUE);
		m_edtPlateType.EnableWindow(TRUE);
		m_edtMinCapDiff.EnableWindow(TRUE);
		m_edtCaliInfo.EnableWindow(TRUE);
		m_edtFramePercent.EnableWindow(TRUE);
		m_btnRecoParam.EnableWindow(TRUE);
	}
}


void CLS_ItsRecognitionParam::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_ItsRecognitionParam::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_ROADWAYID,IDS_CONFIG_ECOP_ROADWAYID);
	SetDlgItemTextEx(IDC_STATIC_RECOPARAM,IDS_ITS_RECOPARAM);
	SetDlgItemTextEx(IDC_CHECK_RECOPARAM_ENABLE,IDS_CONFIG_ECOP_RECOPARAM_ENABLE);
	SetDlgItemTextEx(IDC_STATIC_MAXPLATE,IDS_CONFIG_ECOP_MAXPLATE);
	SetDlgItemTextEx(IDC_STATIC_MAXPLATEWIDTH,IDS_CONFIG_ECOP_MAXPLATEWIDTH);
	SetDlgItemTextEx(IDC_STATIC_MINPLATEWIDTH,IDS_CONFIG_ECOP_MINPLATEWIDTH);
	SetDlgItemTextEx(IDC_STATIC_ENGINENUM,IDS_CONFIG_ECOP_ENGINENUM);
	SetDlgItemTextEx(IDC_STATIC_AREATYPE,IDS_CONFIG_ECOP_AREATYPE);
	SetDlgItemTextEx(IDC_STATIC_PLATETYPE,IDS_CONFIG_ECOP_PLATETYPE);
	SetDlgItemTextEx(IDC_STATIC_SPEED,IDS_CONFIG_ECOP_SPEED);
	SetDlgItemTextEx(IDC_STATIC_MAXSKIP,IDS_CONFIG_ECOP_MAXSKIP);
	SetDlgItemTextEx(IDC_STATIC_MINVALID,IDS_CONFIG_ECOP_MINVALID);
	SetDlgItemTextEx(IDC_STATIC_FRAMEPERCENT,IDS_CONFIG_ECOP_FRAMEPERCENT);
	SetDlgItemTextEx(IDC_STATIC_MINCAPDIFF,IDS_CONFIG_ECOP_MINCAPDIFF);
	SetDlgItemTextEx(IDC_STATIC_CALIINFO,IDS_CONFIG_ECOP_CALIINFO);
	SetDlgItemTextEx(IDC_BUTTON_RECOPARAM,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_LICENSE,IDS_CONFIG_ITS_LICENSE);
	SetDlgItemTextEx(IDC_STATIC_LICENSE_TYPE,IDS_CONFIG_ITS_LICENSE_TYPE);
	SetDlgItemTextEx(IDC_STATIC_WORDCOUNT,IDS_CONFIG_ITS_WORDCOUNT);
	SetDlgItemTextEx(IDC_CHECK_NOPLATE,IDS_CONFIG_ITS_NOPLATE);
	SetDlgItemTextEx(IDC_STATIC_ENABLENOPLATE,IDS_CONFIG_ITS_ENABLENOPLATE);
	SetDlgItemTextEx(IDC_BUTTON_NOPLATE,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_OPTIMIZE,IDS_CONFIG_ITS_OPTIMIZE);
	SetDlgItemTextEx(IDC_STATIC_FIRSTCHINESE,IDS_CONFIG_ITS_FIRSTCHINESE);
	SetDlgItemTextEx(IDC_STATIC_CHINESE_CONFIG,IDS_CONFIG_ITS_CONFIG);
	SetDlgItemTextEx(IDC_STATIC_FIRSTWORD,IDS_CONFIG_ITS_FIRSTWORD);
	SetDlgItemTextEx(IDC_STATIC_WORD_CONFIG,IDS_CONFIG_ITS_CONFIG);
	SetDlgItemTextEx(IDC_BUTTON_OPTIMIZE,IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_LICENSE,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_LICENSE2, IDS_CONFIG_ITS_LICENSE);   
	InsertString(m_cboLicenseType, 0, GetTextEx(IDS_NEEDCHECK));
	InsertString(m_cboLicenseType, 1, GetTextEx(IDS_INVALIDLICENSETYPE));	

}

BOOL CLS_ItsRecognitionParam::UI_UpdateRecoParam()
{
	if (m_iLogonID < 0)
		return FALSE;

	ITS_RecoParamEx tRecognize = {0};
	tRecognize.iRoadwayID = m_cboRoadwayID.GetCurSel();
	int iRet = NetClient_GetITSRecoParam(m_iLogonID,&tRecognize,sizeof(tRecognize));
	if (0 == iRet)
	{
		m_chkEnable.SetCheck(tRecognize.iEnable?BST_CHECKED:BST_UNCHECKED);
		SetDlgItemInt(IDC_EDIT_MAXPLATE, tRecognize.iMaxPlateNO);
		SetDlgItemInt(IDC_EDIT_MAXPLATEWIDTH, tRecognize.iMaxPlateWidth);
		SetDlgItemInt(IDC_EDIT_MINPLATEWIDTH, tRecognize.iMinPlateWidth);
		SetDlgItemInt(IDC_EDIT_ENGINENUM, tRecognize.iEngineNum);
		SetDlgItemInt(IDC_EDIT_AREATYPE, tRecognize.iAreaType);
		SetDlgItemInt(IDC_EDIT_PLATETYPE, tRecognize.iPlateType);
		SetDlgItemInt(IDC_EDIT_SPEED, tRecognize.iSpeed);
		SetDlgItemInt(IDC_EDIT_MAXSKIP, tRecognize.iMaxSkip);
		SetDlgItemInt(IDC_EDIT_MINVALID, tRecognize.iMinValid);
		SetDlgItemInt(IDC_EDIT_FRAMEPERCENT, tRecognize.iFramePercent);
		SetDlgItemInt(IDC_EDIT_MINCAPDIFF, tRecognize.iMinCapDiff);
		SetDlgItemText(IDC_EDIT_CALIINFO, tRecognize.cCaliInfo);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSRecoParam[ITS_RECOPARAM_CMD_GET] (%d,%d)",m_iLogonID,sizeof(tRecognize));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSRecoParam[ITS_RECOPARAM_CMD_GET] (%d,%d)",m_iLogonID,sizeof(tRecognize));
	}
	return TRUE;
}


void CLS_ItsRecognitionParam::OnCbnSelchangeComboRoadwayid()
{
	UI_UpdateRecoParam();
	UI_UpdateEnableNoPlate();
	//UI_UpdateLicense();
	UI_UpdateOptimize();
}

void CLS_ItsRecognitionParam::OnBnClickedButtonRecoparam()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	int iTemp;
	ITS_RecoParamEx tRecognize = {0};
	tRecognize.iRoadwayID = m_cboRoadwayID.GetCurSel();
	int iRet1 = NetClient_GetITSExtraInfo(m_iLogonID, ITS_RECOPARAM_CMD_GET, m_iChannel, &tRecognize, sizeof(tRecognize));
	if(iRet1 == 0)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSExtraInfo[ITS_RECOPARAM_CMD_GET] (%d,%d)",m_iLogonID,sizeof(tRecognize));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSExtraInfo[ITS_RECOPARAM_CMD_GET] (%d,%d)",m_iLogonID,sizeof(tRecognize));
	}
	tRecognize.iEnable = (m_chkEnable.GetCheck() == BST_CHECKED)?1:0;
	tRecognize.iMaxPlateNO = GetDlgItemInt(IDC_EDIT_MAXPLATE);
	tRecognize.iMaxPlateWidth = GetDlgItemInt(IDC_EDIT_MAXPLATEWIDTH);
	tRecognize.iMinPlateWidth = GetDlgItemInt(IDC_EDIT_MINPLATEWIDTH);
	if(tRecognize.iMaxPlateWidth < tRecognize.iMinPlateWidth)
	{
		iTemp = tRecognize.iMaxPlateWidth;
		tRecognize.iMaxPlateWidth = tRecognize.iMinPlateWidth;
		tRecognize.iMinPlateWidth = iTemp;
	}
	SetDlgItemInt(IDC_EDIT_MAXPLATEWIDTH,tRecognize.iMaxPlateWidth);
	SetDlgItemInt(IDC_EDIT_MINPLATEWIDTH,tRecognize.iMinPlateWidth);
	tRecognize.iEngineNum = GetDlgItemInt(IDC_EDIT_ENGINENUM);
	tRecognize.iAreaType = GetDlgItemInt(IDC_EDIT_AREATYPE);
	tRecognize.iPlateType = GetDlgItemInt(IDC_EDIT_PLATETYPE);
	tRecognize.iSpeed = GetDlgItemInt(IDC_EDIT_SPEED);
	tRecognize.iMaxSkip = GetDlgItemInt(IDC_EDIT_MAXSKIP);
	tRecognize.iMinValid = GetDlgItemInt(IDC_EDIT_MINVALID);
	tRecognize.iFramePercent = GetDlgItemInt(IDC_EDIT_FRAMEPERCENT);
	tRecognize.iMinCapDiff = GetDlgItemInt(IDC_EDIT_MINCAPDIFF);
	GetDlgItemText(IDC_EDIT_CALIINFO, tRecognize.cCaliInfo, 75);
	int iRet2 = NetClient_SetITSRecoParam(m_iLogonID,&tRecognize,sizeof(tRecognize));
	if (0 == iRet2)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSRecoParam[ITS_RECOPARAM_CMD_SET] (%d,%d)",m_iLogonID,sizeof(tRecognize));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSRecoParam[ITS_RECOPARAM_CMD_SET] (%d,%d)",m_iLogonID,sizeof(tRecognize));
	}
}

void CLS_ItsRecognitionParam::OnBnClickedButtonNoplate()
{
		if (m_iLogonID < 0)
		{
			AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
			return;
		}

		int iEnable = (m_chkNoPlate.GetCheck() == BST_CHECKED)?1:0;
		int iRet = NetClient_SetITSLicensePlateOptimize(m_iLogonID, ITS_LICENSEPLATE_OPTIMIZE_CMD_SET_NOPLATE_ENABLE, &iEnable, sizeof(iEnable));
		if (0 == iRet)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSLicensePlateOptimize[ITS_LICENSEPLATE_OPTIMIZE_CMD_SET_NOPLATE_ENABLE] (%d,%d,%d)",m_iLogonID,iEnable,m_iChannel);
		} 
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSLicensePlateOptimize [ITS_LICENSEPLATE_OPTIMIZE_CMD_SET_NOPLATE_ENABLE](%d,%d,%d),error(%d)",m_iLogonID,iEnable,m_iChannel,GetLastError());
		}
}
BOOL CLS_ItsRecognitionParam::UI_UpdateEnableNoPlate()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iEnable = -1;
	int iRet = NetClient_GetITSLicensePlateOptimize(m_iLogonID, ITS_LICENSEPLATE_OPTIMIZE_CMD_GET_NOPLATE_ENABLE, &iEnable, sizeof(iEnable));
	if (0 == iRet)
	{
		m_chkNoPlate.SetCheck(iEnable?BST_CHECKED:BST_UNCHECKED);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSLicensePlateOptimize[ITS_LICENSEPLATE_OPTIMIZE_CMD_GET_NOPLATE_ENABLE] (%d,%d,%d)",m_iLogonID,iEnable,m_iChannel);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSLicensePlateOptimize[ITS_LICENSEPLATE_OPTIMIZE_CMD_GET_NOPLATE_ENABLE] (%d,%d,%d), error(%d)",m_iLogonID,iEnable,m_iChannel,GetLastError());
		return FALSE;
	}
	return TRUE;
}
void CLS_ItsRecognitionParam::OnBnClickedButtonLicense()
{
	CString csProvinceName = "京津冀湘沪鄂渝粤川晋黔辽云甘黑青浙陕宁苏台皖藏闽新桂豫港澳赣蒙吉鲁琼";
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	ITS_LicenseOptimizeOther pa = {0};
	pa.iType = m_cboLicenseType.GetCurSel();
	pa.iCount = GetDlgItemInt(IDC_EDIT_WORDCOUNT);
	for(int i = 0; i<pa.iCount; i++)
	{
		GetDlgItemText(m_edtWord[i].GetDlgCtrlID(), pa.cModifyChar[i],5);
		CString csTemp = pa.cModifyChar[i];
		if (NULL == strstr(csProvinceName, csTemp))
		{
			MessageBox(GetTextEx(IDS_CONFIG_ALARM_MESSAGE),GetTextEx(IDS_CONFIG_PROMPT),MB_OK);
			return;
		}
		 pa.iOtherCharWeight[i] = GetDlgItemInt(m_edtWordNum[i].GetDlgCtrlID());
		 if(pa.iOtherCharWeight[i] < 0)
		 {
			pa.iOtherCharWeight[i] = 0;
		 }
		 else if(pa.iOtherCharWeight[i] > 10000)
		 {
			 pa.iOtherCharWeight[i] = 10000;
		 }
	}
	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_LICENSEOPTIMIZEOTHER_CMD_SET, m_iChannel, &pa, sizeof(pa));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo[ITS_LICENSEOPTIMIZEOTHER_CMD_SET] (%d,%d)",m_iLogonID,m_iChannel);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo[ITS_LICENSEOPTIMIZEOTHER_CMD_SET] (%d,%d), error(%d)",m_iLogonID,m_iChannel,GetLastError());
	}
}

BOOL CLS_ItsRecognitionParam::UI_UpdateLicense()
{
	if (m_iLogonID < 0)
		return FALSE;

	ITS_LicenseOptimizeOther pa = {0};
	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_LICENSEOPTIMIZEOTHER_CMD_GET, m_iChannel, &pa, sizeof(pa));
	if (0 == iRet)
	{
		//m_cboLicenseType.SetCurSel(pa.iType);
		SetDlgItemInt(IDC_EDIT_WORDCOUNT, pa.iCount);
		for(int i = 0; i<pa.iCount; i++)
		{
			SetDlgItemText(m_edtWordNum[i].GetDlgCtrlID(), pa.cModifyChar[i]);
			SetDlgItemInt(m_edtWordNum[i].GetDlgCtrlID(), pa.iOtherCharWeight[i]);
		}
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSExtraInfo[ITS_LICENSEOPTIMIZEOTHER_CMD_SET] (%d,%d)",m_iLogonID,m_iChannel);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSExtraInfo[ITS_LICENSEOPTIMIZEOTHER_CMD_SET] (%d,%d), error(%d)",m_iLogonID,m_iChannel,GetLastError());
		return FALSE;
	}
	return TRUE;
}

void CLS_ItsRecognitionParam::OnBnClickedButtonOptimize()
{
	CString csProvinceName = "京津冀湘沪鄂渝粤川晋黔辽云甘黑青浙陕宁苏台皖藏闽新桂豫港澳赣蒙吉鲁琼";
	CString csLetter = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	TITSLicensePlateOptimizeFirstHZInfo pa = {0};
	GetDlgItemText(IDC_EDIT_FIRSTCHINESE, pa.cModifyChar, 3);
	GetDlgItemText(IDC_EDIT_FIRSTWORD, pa.cModifyAlpha, 3);
	CString csTemp = pa.cModifyChar;
	CString csTemp1 = pa.cModifyAlpha;
	if ((NULL == strstr(csProvinceName, csTemp))||(NULL == strstr(csLetter, csTemp1)))
	{
		MessageBox(GetTextEx(IDS_CONFIG_ALARM_MESSAGE),GetTextEx(IDS_CONFIG_PROMPT),MB_OK);
		return;
	}
	pa.iMinCharConfid = GetDlgItemInt(IDC_EDIT_CHINESE_CONFIG);
	if(pa.iMinCharConfid < 0)
	{
		pa.iMinCharConfid = 0;
	}
	else if(pa.iMinCharConfid > 10000)
	{
		pa.iMinCharConfid = 10000;
	}
	GetDlgItemText(IDC_EDIT_FIRSTWORD, pa.cModifyAlpha, 3);
	pa.iMinAlphaConfig = GetDlgItemInt(IDC_EDIT_WORD_CONFIG);
	if(pa.iMinAlphaConfig < 0)
	{
		pa.iMinAlphaConfig = 0;
	}
	else if(pa.iMinAlphaConfig > 10000)
	{
		pa.iMinAlphaConfig = 10000;
	}
	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_OPTIM_CMD_SET, m_iChannel, &pa, sizeof(pa));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo [ITS_OPTIM_CMD_SET](%d)",m_iLogonID);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo[ITS_OPTIM_CMD_SET] (%d), error(%d)",m_iLogonID, GetLastError());
	}
}

BOOL CLS_ItsRecognitionParam::UI_UpdateOptimize()
{
	if (m_iLogonID < 0)
		return FALSE;
	TITSLicensePlateOptimizeFirstHZInfo pa = {0};
	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_OPTIM_CMD_GET, m_iChannel, &pa, sizeof(pa));
	if (0 == iRet)
	{
		SetDlgItemText(IDC_EDIT_FIRSTWORD, pa.cModifyAlpha);
		SetDlgItemInt(IDC_EDIT_WORD_CONFIG, pa.iMinAlphaConfig);
		SetDlgItemText(IDC_EDIT_FIRSTCHINESE, pa.cModifyChar);
		SetDlgItemInt(IDC_EDIT_CHINESE_CONFIG, pa.iMinCharConfid);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSExtraInfo[ITS_OPTIM_CMD_GET] (%d,%d)",m_iLogonID,m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSExtraInfo[ITS_OPTIM_CMD_GET] (%d,%d), error(%d)",m_iLogonID,m_iChannel,GetLastError());
		return FALSE;
	}
	return TRUE;
}
void CLS_ItsRecognitionParam::OnBnClickedCheckRecoparamEnable()
{
	//UI_UpdateEnable();
}

void CLS_ItsRecognitionParam::OnEnChangeEditWordcount()
{
	UI_UpdateWordNumber();
}

void CLS_ItsRecognitionParam::OnCbnSelchangeComboLicenseType()
{
	//UI_UpdateLicense();
}

void CLS_ItsRecognitionParam::OnEnChangeEditFirstchinese()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CLS_BasePage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
