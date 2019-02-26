
#include "stdafx.h"
#include "NetClientDemo.h"
#include "LinkOSD.h"
#include "../Common/CommonFun.h"
#include <Shlwapi.h>
// CLS_LinkOSD 对话框

IMPLEMENT_DYNAMIC(CLS_LinkOSD, CDialog)

CLS_LinkOSD::CLS_LinkOSD(CWnd* pParent /*=NULL*/)
	: CDialog(CLS_LinkOSD::IDD, pParent)
{

}

CLS_LinkOSD::~CLS_LinkOSD()
{
}

void CLS_LinkOSD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_DEV_IP, m_edtDevIP);
	DDX_Control(pDX, IDC_CBO_OSD_CH, m_cboOSDCH);
	DDX_Control(pDX, IDC_CBO_OSD_AREA, m_cboOSDArea);
	DDX_Control(pDX, IDC_CBO_OSD_COLOR, m_cboOSDColor);
	DDX_Control(pDX, IDC_CHK_ALARM_INFO, m_chkAlarmInfo);
	DDX_Control(pDX, IDC_CHK_ALARM_TIME, m_cboAlarmTime);
	DDX_Control(pDX, IDC_CHK_CUSTOM, m_chkUserDefine);
	DDX_Control(pDX, IDC_EDT_CUSTOM, m_edtUserDefine);
	DDX_Text(pDX,IDC_EDT_DEV_IP,m_cstrDevIP);
	DDX_Text(pDX,IDC_EDT_CUSTOM,m_cstrUserDefine);
}


BEGIN_MESSAGE_MAP(CLS_LinkOSD, CDialog)
END_MESSAGE_MAP()


// CLS_LinkOSD 消息处理程序

BOOL CLS_LinkOSD::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemTextEx(IDC_STC_DEV_IP, IDS_CONFIG_LINK_IP);
	SetDlgItemTextEx(IDC_STC_OSD_CH, IDS_CONFIG_LINK_OSD_CH);
	SetDlgItemTextEx(IDC_STC_OSD_AREA, IDS_CONFIG_LINK_OSD_AREA);
	SetDlgItemTextEx(IDC_STC_OSD_COLOR, IDS_CONFIG_LINK_OSD_COLOR);
	SetDlgItemTextEx(IDC_STC_OSD_INFO, IDS_CONFIG_LINK_OSD_INFO);
	SetDlgItemTextEx(IDC_CHK_ALARM_INFO, IDS_CONFIG_LINK_ALARM_INFO);
	SetDlgItemTextEx(IDC_CHK_ALARM_TIME, IDS_CONFIG_LINK_ALARM_TIME);
	SetDlgItemTextEx(IDC_CHK_CUSTOM, IDS_CONFIG_LINK_USERDEFINE);
	
	InitDlgData();

	return TRUE;
}

void CLS_LinkOSD::InitDlgData()
{
	//初始化叠加通道
	for (int i = 0; i < MAX_OSD_CHANNELNUM; i++)
	{
		CString cstrNo = "";
		cstrNo.Format("%d",i+i);
		m_cboOSDCH.InsertString(i,cstrNo);
	}
	m_cboOSDCH.SetCurSel(0);
	//初始化叠加区域
	for (int i = 0; i < MAX_OSD_BLOCKNUM; i++)
	{
		CString cstrNo = "";
		cstrNo.Format("%d",i+i);
		m_cboOSDArea.InsertString(i,cstrNo);
	}
	m_cboOSDArea.SetCurSel(0);
	//初始化字体颜色
	CString cstrOsdSize;
	int iColString[MAX_COLOUR_NUM] = {IDS_VCA_COL_WHITE,
		IDS_VCA_COL_BLACK,IDS_VCA_COL_RED,IDS_VCA_COL_BLUE,
		IDS_VCA_COL_GREEN};
	for (int i = 0; i < MAX_COLOUR_NUM; i++)
	{
		cstrOsdSize.LoadString(iColString[i]);
		m_cboOSDColor.AddString(cstrOsdSize);
	}
	m_cboOSDColor.SetCurSel(0);
}

void CLS_LinkOSD::SetDlgInfo(AlarmInLink* _pAlarmInLink)
{
	UpdateData(TRUE);


	//_pAlarmInLink->iDisappearType = m_cboLinkOsdRecover.GetItemData(m_cboLinkOsdRecover.GetCurSel());

	CString cstrRecoveryParam = "";
	m_cboAlarmTime.GetWindowText(cstrRecoveryParam);
	if (cstrRecoveryParam != "")
	{
		_pAlarmInLink->iDisappearTime = StrToInt(cstrRecoveryParam);
	}
	else
	{
		_pAlarmInLink->iDisappearTime = -1;
	}


	ParamData tData = {0};

	//IP地址
	CString cstrIP; 
	m_edtDevIP.GetWindowText(cstrIP);
	if (cstrIP == "")
	{
		return;
	}
	strcpy_s(tData.cIP, cstrIP);

	//叠加通道
	CString cstrChannel; 
	m_cboOSDCH.GetWindowText(cstrChannel);
	tData.iChannelNo = StrToInt(cstrChannel);

	//叠加区域
	CString cstrZone; 
	m_cboOSDArea.GetWindowText(cstrZone);
	tData.iAreaNo = StrToInt(cstrZone);

	//字体颜色
	int iColor; 
	iColor = m_cboOSDColor.GetCurSel() + 1;
	tData.iColor = iColor;

	//叠加报警信息
	int iAlarmInfo; 
	if (m_chkAlarmInfo.GetCheck())
	{
		iAlarmInfo = 1;
	} 
	else
	{
		iAlarmInfo = 0;
	}
	tData.iAlarmInfo = iAlarmInfo;

	//叠加叠加报警时间
	int iAlarmTime; 
	if (m_cboAlarmTime.GetCheck())
	{
		iAlarmTime = 1;
	} 
	else
	{
		iAlarmTime = 0;
	}
	tData.iAlarmTime = iAlarmTime;

	//自定义选择
	int iText; 
	if (m_chkUserDefine.GetCheck())
	{
		iText = 1;
	} 
	else
	{
		iText = 0;
	}
	tData.iAlarmCustom = iText;

	//自定义内容
	CString strTextInfo; 
	m_edtUserDefine.SetWindowText(strTextInfo);
	strcpy_s(tData.cText, strTextInfo);

	CString cstrParam;
	StructToString(&tData, cstrParam);

	strcpy_s(_pAlarmInLink->cParam, (LPSTR)(LPCTSTR)cstrParam);
	//设备IP地址
	//m_cstrDevIP
	//叠加通道
	//m_cboOSDCH
	//叠加区域
	//m_cboOSDArea
	//字体颜色
	//m_cboOSDColor
	//叠加信息
	//
	m_chkAlarmInfo.SetCheck(TRUE);
	m_cboAlarmTime.SetCheck(TRUE);
	m_chkUserDefine.SetCheck(TRUE);
	if (m_chkUserDefine)
	{
		m_cstrUserDefine = "";
	}

	UpdateData(FALSE);
}

void CLS_LinkOSD::GetDlgInfo(AlarmInLink* _pAlarmInLink)
{
	UpdateData(TRUE);

	//联动字符叠加信息
	LPCTSTR lpszSource = _pAlarmInLink->cParam;
	CString cstrSource = lpszSource;
	ParamData tData = {0};
	StringToStruct(cstrSource, &tData);

	//IP地址
	CString cstrIP;
	cstrIP.Format(_T("%s"), tData.cIP);
	m_edtDevIP.SetWindowText(cstrIP);

	//叠加通道
	int iChannel = tData.iChannelNo;
	int iChannelIndex = m_cboOSDCH.FindString(0, (IntToStr(iChannel)).c_str());	
	m_cboOSDCH.SetCurSel(iChannelIndex);

	//叠加区域
	int iZone = tData.iAreaNo;
	int iZoneIndex = m_cboOSDArea.FindString(0, (IntToStr(iZone)).c_str());	
	m_cboOSDArea.SetCurSel(iZoneIndex);

	//字体颜色
	int iColor = tData.iColor;
	m_cboOSDColor.SetCurSel(iColor - 1);


	//叠加报警信息
	int iAlarmInfo = tData.iAlarmInfo;
	if (iAlarmInfo == 1)
	{
		m_chkAlarmInfo.SetCheck(BST_CHECKED);
	} 
	else
	{
		m_chkAlarmInfo.SetCheck(BST_UNCHECKED);
	}

	//叠加叠加报警时间
	int iAlarmTime = tData.iAlarmTime; 
	if (iAlarmTime == 1)
	{
		m_cboAlarmTime.SetCheck(BST_CHECKED);
	} 
	else
	{
		m_cboAlarmTime.SetCheck(BST_UNCHECKED);
	}


	//自定义选择
	int iText = tData.iAlarmCustom;
	if (iText == 1)
	{
		m_chkUserDefine.SetCheck(BST_CHECKED);
	} 
	else
	{
		m_chkUserDefine.SetCheck(BST_UNCHECKED);
	}	
	//OnBnClickedChkUserDefine();

	//自定义内容
	CString cstrTextInfo;
	cstrTextInfo.Format(_T("%s"), tData.cText); 
	m_edtUserDefine.SetWindowText(cstrTextInfo);	
	//设备IP地址
	//m_cstrDevIP
	//叠加通道
	//m_cboOSDCH
	//叠加区域
	//m_cboOSDArea
	//字体颜色
	//m_cboOSDColor
	//叠加信息
	//
	m_chkAlarmInfo.GetCheck();
	m_cboAlarmTime.GetCheck();
	m_chkUserDefine.GetCheck();
	if (m_chkUserDefine)
	{
		m_cstrUserDefine = "";
	}

	UpdateData(FALSE);
}

BOOL CLS_LinkOSD::StringToStruct( CString _strSrc,ParamData* _pDest )
{
	if (NULL == _pDest)
	{
		return FALSE;
	}

// 	CLS_TString tData;
// 	tData.Split(_strSrc);
// 	strcpy_s(_pDest->cIP,(LPSTR)(LPCTSTR)tData.GetValue(_T("ip")));
// 	_pDest->iChannelNo = tData.GetIntValue(_T("channel"));
// 	_pDest->iAreaNo = tData.GetIntValue(_T("area"));
// 	_pDest->iColor = tData.GetIntValue(_T("color"));
// 	_pDest->iAlarmInfo = tData.GetIntValue(_T("info"));
// 	_pDest->iAlarmTime = tData.GetIntValue(_T("time"));
// 	_pDest->iAlarmCustom = tData.GetIntValue(_T("custom"));
// 	strcpy_s(_pDest->cText,(LPSTR)(LPCTSTR)tData.GetValue(_T("text")));

	return TRUE;
}

BOOL CLS_LinkOSD::StructToString(ParamData* _pSrc,CString& _strDest)
{
	if (NULL == _pSrc)
	{
		return FALSE;
	}

// 	CLS_TString tData;
// 	tData.Append(_T("ip"),_pSrc->cIP);
// 	tData.Append(_T("channel"),_pSrc->iChannelNo);
// 	tData.Append(_T("area"),_pSrc->iAreaNo);
// 	tData.Append(_T("color"),_pSrc->iColor);
// 	tData.Append(_T("info"),_pSrc->iAlarmInfo);
// 	tData.Append(_T("time"),_pSrc->iAlarmTime);
// 	tData.Append(_T("custom"),_pSrc->iAlarmCustom);
// 	tData.Append(_T("text"),_pSrc->cText);
// 	tData.Combine(_strDest);

	return TRUE;
}