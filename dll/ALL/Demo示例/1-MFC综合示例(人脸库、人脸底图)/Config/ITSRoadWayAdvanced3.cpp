// ITSRoadWayAdvanced3.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "ITSRoadWayAdvanced3.h"
#define ITS_AREA_SUM 5
#define  ITS_ROADNUM_MAX 4
#define ITS_AREAID_MAX 12
#define ITS_RADARAREAID_MAX 8
// CLS_ITSRoadWayAdvanced3 对话框

IMPLEMENT_DYNAMIC(CLS_ITSRoadWayAdvanced3, CDialog)

CLS_ITSRoadWayAdvanced3::CLS_ITSRoadWayAdvanced3(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ITSRoadWayAdvanced3::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannel = -1;
}

CLS_ITSRoadWayAdvanced3::~CLS_ITSRoadWayAdvanced3()
{
}

void CLS_ITSRoadWayAdvanced3::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBO_ROADSUM, m_cboRoadSum);
	DDX_Control(pDX, IDC_CBO_ROADNUM, m_cboRoadNum);
	DDX_Control(pDX, IDC_EDT_RADAR_MATCHTM, m_edtRadarMtachTm);
	DDX_Control(pDX, IDC_EDT_MAX, m_edtMax);
	DDX_Control(pDX, IDC_EDT_MIN, m_edtMin);
	DDX_Control(pDX, IDC_CBO_RADAR_AREAID, m_cboRadarAreaID);
	DDX_Control(pDX, IDC_EDT_RIGHTRECT, m_edtRadarRightRect);
	DDX_Control(pDX, IDC_EDT_LEFTRECT, m_edtRadarLeftRect);
	DDX_Control(pDX, IDC_EDT_RADARLINE, m_edtRadarLine);
	DDX_Control(pDX, IDC_CBO_AREAID, m_cboAreaID);
	DDX_Control(pDX, IDC_CBO_AreaNum, m_cboAreaNum);
	DDX_Control(pDX, IDC_EDT_RECT, m_edtRect);
	DDX_Control(pDX, IDC_CHECK_ROADWAYNO, m_chkRoadwayNo);
}


BEGIN_MESSAGE_MAP(CLS_ITSRoadWayAdvanced3, CLS_BasePage)
	ON_BN_CLICKED(IDC_BTN_TRIGGER_SET, &CLS_ITSRoadWayAdvanced3::OnBnClickedBtnTriggerSet)
	ON_BN_CLICKED(IDC_BTN_INFO_SET, &CLS_ITSRoadWayAdvanced3::OnBnClickedBtnInfoSet)
	ON_CBN_SELCHANGE(IDC_CBO_ROADNUM, &CLS_ITSRoadWayAdvanced3::OnCbnSelchangeCboRoadnum)
	ON_BN_CLICKED(IDC_BTN_PARAM_SET, &CLS_ITSRoadWayAdvanced3::OnBnClickedBtnParamSet)
	ON_CBN_SELCHANGE(IDC_CBO_AREAID, &CLS_ITSRoadWayAdvanced3::OnCbnSelchangeCboAreaid)
	ON_CBN_SELCHANGE(IDC_CBO_RADAR_AREAID, &CLS_ITSRoadWayAdvanced3::OnCbnSelchangeCboRadarAreaid)
	ON_CBN_SELCHANGE(IDC_CBO_ROADSUM, &CLS_ITSRoadWayAdvanced3::OnCbnSelchangeCboRoadsum)
	ON_BN_CLICKED(IDC_CHECK_ROADWAYNO, &CLS_ITSRoadWayAdvanced3::OnBnClickedCheckRoadwayno)
END_MESSAGE_MAP()


// CLS_ITSRoadWayAdvanced3 消息处理程序

BOOL CLS_ITSRoadWayAdvanced3::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();
	UI_UpdateDialog();
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL CLS_ITSRoadWayAdvanced3::UI_UpdateRoadway()
{
	if (m_iLogonID < 0)
		return FALSE;
	int iRoadwayID = m_cboRoadNum.GetCurSel();
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

void CLS_ITSRoadWayAdvanced3::OnChannelChanged( int _iLogonID,int _iChannelNo,int /*_iStreamNo*/ )
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
	UI_UpdateDialog();
	
}
void CLS_ITSRoadWayAdvanced3::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}
void CLS_ITSRoadWayAdvanced3::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STC_ADVANCE3, IDS_ITS_ADVANCE3);
	SetDlgItemTextEx(IDC_CHECK_ROADWAYNO,IDS_CONFIG_ITS_ROADWAY_ENABLE);
	SetDlgItemTextEx(IDC_STC_ROADSUM, IDS_ITS_ROADSUM);
	SetDlgItemTextEx(IDC_STC_ROADNUM, IDS_ITS_ROADWAY_ID);
	SetDlgItemTextEx(IDC_STC_RADARTRIGGER, IDS_ITS_RADARTRIGGER);
	SetDlgItemTextEx(IDC_STC_RADAR_MATCHTM, IDS_ITS_RADAR_MATCHTM);
	SetDlgItemTextEx(IDC_STC_RADAR_SPEED, IDS_ITS_RADAR_SPEED);
	SetDlgItemTextEx(IDC_STC_MAX, IDS_ITS_MAX);
	SetDlgItemTextEx(IDC_STC_MIN, IDS_ITS_MIN);
	SetDlgItemTextEx(IDC_BTN_TRIGGER_SET, IDS_SET);
	SetDlgItemTextEx(IDC_STC_RADAEINFO, IDS_ITS_RADARINFO);
	SetDlgItemTextEx(IDC_STC_RADAR_AREAID, IDS_ITS_RADAR_AREAID);
	SetDlgItemTextEx(IDC_STC_LEFTRECT, IDS_ITS_LEFTRECT);
	SetDlgItemTextEx(IDC_STC_RIGHTRECT, IDS_ITS_RIGHTRECT);
	SetDlgItemTextEx(IDC_STC_RADARLINE, IDS_ITS_RADARLINE);
	SetDlgItemTextEx(IDC_BTN_INFO_SET, IDS_SET);
	SetDlgItemTextEx(IDC_STC_AREA_PARAM, IDS_ITS_AREA_PARAM);
	SetDlgItemTextEx(IDC_STC_AREAID, IDS_ITS_AREAID);
	SetDlgItemTextEx(IDC_STC_RECTNUM, IDS_ITS_RECTNUM);
	SetDlgItemTextEx(IDC_STC_RECT, IDS_ITS_RECT);
	SetDlgItemTextEx(IDC_CHK_PARAM_ENABLE, IDS_CONFIG_ITS_ENABLE);
	SetDlgItemTextEx(IDC_BTN_PARAM_SET, IDS_SET);
	InsertString(m_cboRoadSum,0,"1");
	InsertString(m_cboRoadSum,1,"2");
	InsertString(m_cboRoadSum,2,"3");
	InsertString(m_cboRoadSum,3,"4");
	for(int i = 0;i < ITS_ROADNUM_MAX; i++)
	{
		InsertString(m_cboRoadNum, i,  IntToString(i));
	}
	for(int i = 0;i < ITS_AREAID_MAX; i++)
	{
		InsertString(m_cboAreaID, i,  IntToString(i));
	}
	m_cboAreaID.SetCurSel(0);
   for(int i = 0; i < ITS_RADARAREAID_MAX; i++)
   {
	   InsertString(m_cboRadarAreaID, i,  IntToString(i + 1));
   }
   for(int i = 0;i < ITS_AREAID_MAX - 1; i++)
   {
		 InsertString(m_cboAreaNum, i,  IntToString(i + 4));
   }

   UI_UpdateTrigger();
   UI_UpdateRadarInfo();
   UI_UpdateParam();
}
void CLS_ITSRoadWayAdvanced3::OnBnClickedBtnTriggerSet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	int iBytesReturned = 0;
	ITS_ComPoundParam tComPoundParam = {0};
	NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_ITS_COMPOUNDPARAM, m_iChannel, &tComPoundParam, sizeof(tComPoundParam), &iBytesReturned);
	tComPoundParam.iITSRoadID = m_cboRoadNum.GetCurSel();
	tComPoundParam.iRadarMatchTime = GetDlgItemInt(IDC_EDT_RADAR_MATCHTM);
	tComPoundParam.iRadarMaxSpeed = GetDlgItemInt(IDC_EDT_MAX);
	tComPoundParam.iRadarMinSpeed = GetDlgItemInt(IDC_EDT_MIN);
	tComPoundParam.iSize = sizeof(tComPoundParam);
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_ITS_COMPOUNDPARAM, m_iChannel, &tComPoundParam, sizeof(tComPoundParam));
	if( iRet == 0)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig[NET_CLIENT_ITS_COMPOUNDPARAM] (%d,%d)", m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig[NET_CLIENT_ITS_COMPOUNDPARAM] (%d,%d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
	}
}

BOOL CLS_ITSRoadWayAdvanced3::UI_UpdateTrigger()
{
	if(m_iLogonID < 0)
		return FALSE;
	int iBytesReturned = 0;
	ITS_ComPoundParam tComPoundParam = {0};
	tComPoundParam.iITSRoadID = m_cboRoadNum.GetCurSel();
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_ITS_COMPOUNDPARAM, m_iChannel, &tComPoundParam, sizeof(tComPoundParam), &iBytesReturned);
	if(iRet == 0)
	{
		SetDlgItemInt(IDC_EDT_RADAR_MATCHTM, tComPoundParam.iRadarMatchTime);
		SetDlgItemInt(IDC_EDT_MAX, tComPoundParam.iRadarMaxSpeed);
		SetDlgItemInt(IDC_EDT_MIN, tComPoundParam.iRadarMinSpeed);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig[NET_CLIENT_ITS_COMPOUNDPARAM] (%d,%d)", m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevConfig[NET_CLIENT_ITS_COMPOUNDPARAM] (%d,%d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
		return FALSE;
	}
	return TRUE;
}
void CLS_ITSRoadWayAdvanced3::OnBnClickedBtnInfoSet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	ITS_RaderCfgInfo tRadarCfgInfo = {0};
	tRadarCfgInfo.iSize = sizeof(ITS_RaderCfgInfo);
	tRadarCfgInfo.iRoadwayID = m_cboRoadNum.GetCurSel();
	tRadarCfgInfo.iRaderAreaID = m_cboRadarAreaID.GetCurSel() + 1;
	tRadarCfgInfo.iRaderAreaLeftEdge = GetDlgItemInt(IDC_EDT_LEFTRECT);
	tRadarCfgInfo.iRaderAreaRightEdge = GetDlgItemInt(IDC_EDT_RIGHTRECT);
	tRadarCfgInfo.iRaderAreaLine = GetDlgItemInt(IDC_EDT_RADARLINE);
	tRadarCfgInfo.iSize = sizeof(tRadarCfgInfo);
	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_RADERINFO_CMD_SET, m_iChannel, &tRadarCfgInfo, sizeof(tRadarCfgInfo));
	if(iRet == 0)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo[ITS_RADERINFO_CMD_SET] (%d,%d)", m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo[ITS_RADERINFO_CMD_SET] (%d,%d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
	}
}
BOOL CLS_ITSRoadWayAdvanced3::UI_UpdateRadarInfo()
{
	if(m_iLogonID < 0)
		return FALSE;

	ITS_RaderCfgInfo tRadarCfgInfo = {0};
	tRadarCfgInfo.iRoadwayID = m_cboRoadNum.GetCurSel();
	tRadarCfgInfo.iSize = sizeof(tRadarCfgInfo);
	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_RADERINFO_CMD_GET, m_iChannel, &tRadarCfgInfo, sizeof(tRadarCfgInfo));
	if(iRet == 0)
	{
		SetDlgItemInt(IDC_CBO_RADAR_AREAID, tRadarCfgInfo.iRaderAreaID);
		SetDlgItemInt(IDC_EDT_LEFTRECT, tRadarCfgInfo.iRaderAreaLeftEdge);
		SetDlgItemInt(IDC_EDT_RIGHTRECT, tRadarCfgInfo.iRaderAreaRightEdge);
		SetDlgItemInt(IDC_EDT_RADARLINE, tRadarCfgInfo.iRaderAreaLine);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSExtraInfo[ITS_RADERINFO_CMD_GET] (%d,%d)", m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSExtraInfo[ITS_RADERINFO_CMD_GET] (%d,%d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
		return FALSE;
	}

	return TRUE;
}

void CLS_ITSRoadWayAdvanced3::OnCbnSelchangeCboRoadnum()
{
	UI_UpdateTrigger();
	UI_UpdateRadarInfo();
	UI_UpdateParam();
	UI_UpdateRoadway();
}

void CLS_ITSRoadWayAdvanced3::OnBnClickedBtnParamSet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	TITS_DetectArea tDetectArea = {0};

	int iGetret = NetClient_GetITSExtraInfo(m_iLogonID, ITS_DETECTAREA_CMD_GET, m_iChannel, &tDetectArea, sizeof(tDetectArea));
	if (iGetret == 0)
	{
		CButton* pBtn = (CButton*)GetDlgItem(IDC_CHK_PARAM_ENABLE);
		if(NULL != pBtn)
		{
			tDetectArea.m_iEnabled = pBtn->GetCheck();
		}
		tDetectArea.m_iRegionID = GetDlgItemInt(IDC_CBO_AREAID);
		tDetectArea.m_iPointCount = GetDlgItemInt(IDC_CBO_AreaNum);
		CString str;
		GetDlgItemText(IDC_EDT_RECT,str);
		int ilen=str.GetLength();
		int j = 0,i = 0,iN = 0;
		int iNum = 0; 
		int iSum = 0;
		int iArray[30] = {0};
		char ctemp;
		for(j=0;j<ilen;j++)
		{   
			ctemp=(char)str.GetAt(j);
			if(ctemp != ':' && ctemp != ',')
			{
				iSum = iSum*10 + (int)(ctemp - '0');
			}
			else
			{
				if(iNum < 31)
				{
					iArray[iNum++] = iSum;
					iSum = 0;
				}

			}
		}
		if((j == ilen)&&(ctemp != ':' && ctemp != ','))
			iArray[iNum++] = iSum;
		for(i = 0, iN = 0; i < iNum; i++)
		{
			tDetectArea.m_arrPoint[iN].iX = iArray[i++];
			tDetectArea.m_arrPoint[iN++].iY = iArray[i];
		}
		int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_DETECTAREA_CMD_SET, m_iChannel, &tDetectArea, sizeof(tDetectArea));
		if(iRet == 0)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo[ITS_DETECTAREA_CMD_SET] (%d,%d)", m_iLogonID, m_iChannel);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo[ITS_DETECTAREA_CMD_SET] (%d,%d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
		}
	}
}

BOOL CLS_ITSRoadWayAdvanced3::UI_UpdateParam()
	{
		if(m_iLogonID < 0)
			return FALSE;

		TITS_DetectArea tDetectArea = {0};
		tDetectArea.m_iRegionID = m_cboAreaID.GetCurSel();
		int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_DETECTAREA_CMD_GET, m_iChannel, &tDetectArea, sizeof(tDetectArea));
		if(iRet == 0)
		{
			CButton* pBtn = (CButton*)GetDlgItem(IDC_CHK_PARAM_ENABLE);
			if(NULL != pBtn)
			{
				pBtn->SetCheck(tDetectArea.m_iEnabled);
			}
			SetDlgItemInt(IDC_CBO_AreaNum, tDetectArea.m_iPointCount);
			CString str;
			CString getstr;
			for(int i = 0;i < tDetectArea.m_iPointCount;i++)
			{
				getstr.Format("%d:%d,",tDetectArea.m_arrPoint[i].iX,tDetectArea.m_arrPoint[i].iY);
				str = str + getstr;
			}
			m_edtRect.SetWindowText(str);
			AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSExtraInfo[ITS_DETECTAREA_CMD_GET] (%d,%d)", m_iLogonID, m_iChannel);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSExtraInfo[ITS_DETECTAREA_CMD_GET] (%d,%d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
			return FALSE;
		}

		return TRUE;
	}


void CLS_ITSRoadWayAdvanced3::OnCbnSelchangeCboAreaid()
{
	UI_UpdateParam();
}

void CLS_ITSRoadWayAdvanced3::OnCbnSelchangeCboRadarAreaid()
{
		//UI_UpdateRadarInfo();
}

void CLS_ITSRoadWayAdvanced3::OnCbnSelchangeCboRoadsum()
{
	int iNumber = 0;
	int iI = 0;
	iNumber = m_cboRoadSum.GetCurSel() + 1;
	m_cboRoadNum.ResetContent();
	for(iI = 0;iI < iNumber;iI++)
	{
		InsertString(m_cboRoadNum, iI,  IntToString(iI));
	}
}

void CLS_ITSRoadWayAdvanced3::OnBnClickedCheckRoadwayno()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	TITSRoadwayInfo pa = {0};
	pa.iRoadwayID = m_cboRoadNum.GetCurSel();
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
