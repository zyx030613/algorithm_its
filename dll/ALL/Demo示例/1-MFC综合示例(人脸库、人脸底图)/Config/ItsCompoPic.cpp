// ItsCompoPic.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "ItsCompoPic.h"


// Cls_ItsCompoPic 对话框

IMPLEMENT_DYNAMIC(Cls_ItsCompoPic, CDialog)

Cls_ItsCompoPic::Cls_ItsCompoPic(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(Cls_ItsCompoPic::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannel = -1;
}

Cls_ItsCompoPic::~Cls_ItsCompoPic()
{
}

void Cls_ItsCompoPic::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBO_ONE_IMAGE, m_cboOneImage);
	DDX_Control(pDX, IDC_CBO_TWO_IMAGE, m_cboTwoImage);
	DDX_Control(pDX, IDC_CBO_THREE_IMAGE, m_cboThreeImage);
	DDX_Control(pDX, IDC_EDT_PICRATE, m_editPicRate);
	DDX_Control(pDX, IDC_CBO_CUTOUT_RANGE, m_cboCutoutRange);
	DDX_Control(pDX, IDC_CBO_CUTOUT_TYPE, m_cboCutoutType);
	DDX_Control(pDX, IDC_CHK_PICENABLE, m_chkPicEnable);
	DDX_Control(pDX, IDC_BTN_COMPOSET, m_btnCompoSet);
	DDX_Control(pDX, IDC_BTN_CUTOUT_SET, m_btnCutoutSet);
	DDX_Control(pDX, IDC_BTN_ONESET, m_btnOneSet);
	DDX_Control(pDX, IDC_BTN_TWOSET, m_btnTwoSet);
}


BEGIN_MESSAGE_MAP(Cls_ItsCompoPic, CLS_BasePage)
	ON_BN_CLICKED(IDC_BTN_PICSET, &Cls_ItsCompoPic::OnBnClickedBtnPicset)
	ON_BN_CLICKED(IDC_BTN_COMPOSET, &Cls_ItsCompoPic::OnBnClickedBtnComposet)
	ON_BN_CLICKED(IDC_BTN_CUTOUT_SET, &Cls_ItsCompoPic::OnBnClickedBtnCutoutSet)
	ON_BN_CLICKED(IDC_CHK_PICENABLE, &Cls_ItsCompoPic::OnBnClickedChkPicenable)
	ON_BN_CLICKED(IDC_BTN_TWOSET, &Cls_ItsCompoPic::OnBnClickedBtnTwoset)
	ON_BN_CLICKED(IDC_BTN_ONESET, &Cls_ItsCompoPic::OnBnClickedBtnOneset)
	ON_BN_CLICKED(IDC_BTN_PIC_RECEIVE, &Cls_ItsCompoPic::OnBnClickedBtnPicReceive)
END_MESSAGE_MAP()


// Cls_ItsCompoPic 消息处理程序

BOOL Cls_ItsCompoPic::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();
	UI_UpdateDialog();
	m_cboCutoutRange.AddString("25%");
	m_cboCutoutRange.AddString("100%");

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void Cls_ItsCompoPic::OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo)
{
	m_iLogonID = _iLogonID;
	m_iChannel = _iChannelNo;
	UI_UpdatePic();
	UI_UpdateCompo();
	UI_UpdateCutout();
	UI_UpdateTwo();
	UI_UpdateOne();
	UI_UpdatePicRecv();
}

void Cls_ItsCompoPic::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialog();
}

void Cls_ItsCompoPic::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_CHK_PICENABLE, IDS_ITS_ENABLED);
	SetDlgItemTextEx(IDC_BTN_PICSET, IDS_CFG_USER_SET);
	SetDlgItemTextEx(IDC_STC_COMPO_PIC, IDS_ITS_COMPO_PIC);
	SetDlgItemTextEx(IDC_STC_PIC_RATE, IDS_ITS_PIC_RATE);
	SetDlgItemTextEx(IDC_BTN_COMPOSET, IDS_CFG_USER_SET);
	SetDlgItemTextEx(IDC_STC_CUTOUT_RANGE, IDS_ITS_CUTOUT_RANGE);
	SetDlgItemTextEx(IDC_STC_CUTOUT_TYPE, IDS_ITS_CUTOUT_TYPE);
	SetDlgItemTextEx(IDC_BTN_CUTOUT_SET, IDS_CFG_USER_SET);
	SetDlgItemTextEx(IDC_BTN_ONESET, IDS_CFG_USER_SET);
	SetDlgItemTextEx(IDC_BTN_TWOSET, IDS_CFG_USER_SET);
	SetDlgItemTextEx(IDC_STC_ONE_PIC, IDS_ITS_ONE_PIC);
	SetDlgItemTextEx(IDC_STC_TWO_PIC, IDS_ITS_TWO_PIC);
	SetDlgItemTextEx(IDC_STC_THREE_PIC, IDS_ITS_THREE_PIC);

	SetDlgItemTextEx(IDC_GPO_PIC_RECEIVE, IDS_ITS_PIC_EXPORT);
	SetDlgItemTextEx(IDC_STC_PIC_RCV_CLIENT_IP, IDS_ADV_CONNECT_INFO_CLIENT_IP);
	SetDlgItemTextEx(IDC_BTN_PIC_RECEIVE, IDS_CFG_USER_SET);


	InsertString(m_cboOneImage, 0, IDS_ITS_ONEPIC_ZERO);
	InsertString(m_cboOneImage, 1, IDS_ITS_ONEPIC_ONE);
	InsertString(m_cboOneImage, 2, IDS_ITS_ONEPIC_TWO);
	InsertString(m_cboOneImage, 3, IDS_ITS_ONEPIC_THREE);

	InsertString(m_cboTwoImage, 0, IDS_ITS_TWOPIC_ZERO);
	InsertString(m_cboTwoImage, 1, IDS_ITS_TWOPIC_ONE);

	InsertString(m_cboThreeImage, 0, IDS_ITS_THREEPIC_ZERO);
	InsertString(m_cboThreeImage, 1, IDS_ITS_THREEPIC_ONE);
	InsertString(m_cboThreeImage, 2, IDS_ITS_THREEPIC_TWO);
	InsertString(m_cboThreeImage, 3, IDS_ITS_THREEPIC_THREE);
	InsertString(m_cboThreeImage, 4, IDS_ITS_THREEPIC_FOUR);
	InsertString(m_cboThreeImage, 5, IDS_ITS_THREEPIC_FIVE);
	InsertString(m_cboThreeImage, 6, IDS_ITS_THREEPIC_SIX);
	InsertString(m_cboThreeImage, 7, IDS_ITS_THREEPIC_SEVEN);
	InsertString(m_cboThreeImage, 8, IDS_ITS_THREEPIC_EIGHT);
	InsertString(m_cboThreeImage, 9, IDS_ITS_THREEPIC_NINE);
	InsertString(m_cboThreeImage, 10, IDS_ITS_THREEPIC_TEN);
	InsertString(m_cboThreeImage, 11, IDS_ITS_THREEPIC_ELEVEN);

	InsertString(m_cboCutoutType, 0, IDS_ITS_PLATE);
	InsertString(m_cboCutoutType, 1, IDS_ITS_FLAG);
	InsertString(m_cboCutoutType, 2, IDS_ITS_FACE);

	
}

void Cls_ItsCompoPic::OnBnClickedBtnPicset()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	ITS_EnalbeParam tEnableParam = {0};
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHK_PICENABLE);
	if(NULL != pBtn)
	{
		tEnableParam.iEnable = pBtn->GetCheck();
	}
	tEnableParam.iType = ITS_ENABLE_TYPE;
	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_ENABLE_CMD_SET, m_iChannel, &tEnableParam, sizeof(tEnableParam));
	if(0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo[ITS_ENABLE_CMD_SET] (%d, %d)", m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo[ITS_ENABLE_CMD_SET] (%d, %d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
	}

}
BOOL Cls_ItsCompoPic::UI_UpdatePic()
{
	if (m_iLogonID < 0)
		return FALSE;
	ITS_EnalbeParam tEnableParam = {0};
	tEnableParam.iType = ITS_ENABLE_TYPE;
	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_ENABLE_CMD_GET, m_iChannel, &tEnableParam, sizeof(tEnableParam));
	if(0 == iRet)
	{
		CButton* pBtn = (CButton*)GetDlgItem(IDC_CHK_PICENABLE);
		if(NULL != pBtn)
		{
			pBtn->SetCheck(tEnableParam.iEnable);
			if( 0 == m_chkPicEnable.GetCheck() )
			{
				m_btnCompoSet.EnableWindow(FALSE);
				m_btnCutoutSet.EnableWindow(FALSE);
				m_btnOneSet.EnableWindow(FALSE);
				m_btnTwoSet.EnableWindow(FALSE);
			}
			else
			{
				m_btnCompoSet.EnableWindow(TRUE);
				m_btnCutoutSet.EnableWindow(TRUE);
				m_btnOneSet.EnableWindow(TRUE);
				m_btnTwoSet.EnableWindow(TRUE);
			}
		}
		
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSExtraInfo[ITS_ENABLE_CMD_GET] (%d, %d)", m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSExtraInfo[ITS_ENABLE_CMD_GET] (%d, %d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
		return FALSE;
	}
	return TRUE;
}

void Cls_ItsCompoPic::OnBnClickedBtnComposet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	TITS_MergeInfo tMergeInfo = {0};
	memset(&tMergeInfo, 0, sizeof(TITS_MergeInfo));
	tMergeInfo.m_iSize = sizeof(tMergeInfo);
	tMergeInfo.m_iMergeType = ITS_MERGE_TYPE_TWO;
	tMergeInfo.m_iMergeMode = m_cboThreeImage.GetCurSel();
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLINET_PICTURE_MERGE, m_iChannel, &tMergeInfo, sizeof(tMergeInfo));
	if(0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetDevConfig[NET_CLINET_PICTURE_MERGE](%d, %d)", m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig[NET_CLINET_PICTURE_MERGE](%d, %d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
	}
}

BOOL Cls_ItsCompoPic::UI_UpdateCompo()
{
	if (m_iLogonID < 0)
		return FALSE;
	int iRet = -1;
	TITS_MergeInfo tMergeInfo = {0};
	tMergeInfo.m_iMergeType = ITS_MERGE_TYPE_TWO;
	int ilpBytesReturned = 0; 
	iRet =  NetClient_GetDevConfig(m_iLogonID, NET_CLINET_PICTURE_MERGE, m_iChannel, &tMergeInfo, sizeof(tMergeInfo), &ilpBytesReturned);
	if(0 == iRet)
	{
		SetDlgItemInt(IDC_EDT_PICRATE, tMergeInfo.m_iResizePercent);
		m_cboThreeImage.SetCurSel(tMergeInfo.m_iMergeMode);
		AddLog(LOG_TYPE_SUCC, "", "NetClient_GetDevConfig[NET_CLINET_PICTURE_MERGE](%d,%d)", m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetDevConfig[NET_CLINET_PICTURE_MERGE](%d,%d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
		return FALSE;
	}
	return TRUE;
}

void Cls_ItsCompoPic::OnBnClickedBtnCutoutSet()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	ITS_PicCutInfo tPicCutInfo = {0};
	tPicCutInfo.iChannelNo = m_iChannel;
	tPicCutInfo.iCutScale = m_cboCutoutRange.GetCurSel();
	tPicCutInfo.iCutType = m_cboCutoutType.GetCurSel();
	tPicCutInfo.iSize = sizeof(tPicCutInfo);
	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_PICCUT_CMD_SET, m_iChannel, &tPicCutInfo, tPicCutInfo.iSize);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetITSExtraInfo[NET_CLINET_PICTURE_MERGE](%d, %d)", m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetITSExtraInfo[NET_CLINET_PICTURE_MERGE](%d, %d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
	}
}

BOOL Cls_ItsCompoPic::UI_UpdateCutout()
{
	if (m_iLogonID < 0)
		return FALSE;
	ITS_PicCutInfo tPicCutInfo = {0};
	tPicCutInfo.iSize = sizeof(tPicCutInfo);
	tPicCutInfo.iChannelNo = m_iChannel;
	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_PICCUT_CMD_GET, m_iChannel, &tPicCutInfo, tPicCutInfo.iSize);
	if(0 == iRet)
	{
		m_cboCutoutRange.SetCurSel(tPicCutInfo.iCutScale);
		m_cboCutoutType.SetCurSel(tPicCutInfo.iCutType);
		AddLog(LOG_TYPE_SUCC, "", "NetClient_GetITSExtraInfo[NET_CLINET_PICTURE_MERGE](%d,%d)", m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetITSExtraInfo[NET_CLINET_PICTURE_MERGE](%d, %d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
		return FALSE;
	}
	return TRUE;
}
void Cls_ItsCompoPic::OnBnClickedChkPicenable()
{
	if( 0 == m_chkPicEnable.GetCheck() )
		{
			m_btnCompoSet.EnableWindow(FALSE);
			m_btnCutoutSet.EnableWindow(FALSE);	
			m_btnOneSet.EnableWindow(FALSE);
			m_btnTwoSet.EnableWindow(FALSE);
		}
		else
		{
			m_btnCompoSet.EnableWindow(TRUE);
			m_btnCutoutSet.EnableWindow(TRUE);
			m_btnOneSet.EnableWindow(TRUE);
			m_btnTwoSet.EnableWindow(TRUE);
		}
}

void Cls_ItsCompoPic::OnBnClickedBtnTwoset()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	int iRet = -1;
	TITS_MergeInfo tMergeInfo = {0};
	memset(&tMergeInfo, 0, sizeof(TITS_MergeInfo));
	tMergeInfo.m_iSize = sizeof(tMergeInfo);
	tMergeInfo.m_iMergeType = ITS_MERGE_TYPE_ONE;
	tMergeInfo.m_iMergeMode = m_cboTwoImage.GetCurSel();
	iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLINET_PICTURE_MERGE, m_iChannel, &tMergeInfo, sizeof(tMergeInfo));
	if(0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetDevConfig[NET_CLINET_PICTURE_MERGE](%d, %d)", m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig[NET_CLINET_PICTURE_MERGE](%d, %d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
	}
}
BOOL Cls_ItsCompoPic::UI_UpdateTwo()
{
	if (m_iLogonID < 0)
		return FALSE;
	int iRet = -1;
	TITS_MergeInfo tMergeInfo = {0};
	tMergeInfo.m_iMergeType = ITS_MERGE_TYPE_ONE;
	int ilpBytesReturned = 0;
	iRet =  NetClient_GetDevConfig(m_iLogonID, NET_CLINET_PICTURE_MERGE, m_iChannel, &tMergeInfo, sizeof(tMergeInfo), &ilpBytesReturned);
	if(0 == iRet)
	{
		SetDlgItemInt(IDC_EDT_PICRATE, tMergeInfo.m_iResizePercent);
		m_cboTwoImage.SetCurSel(tMergeInfo.m_iMergeMode);
		AddLog(LOG_TYPE_SUCC, "", "NetClient_GetDevConfig[NET_CLINET_PICTURE_MERGE](%d,%d)", m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetDevConfig[NET_CLINET_PICTURE_MERGE](%d,%d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
		return FALSE;
	}
	return TRUE;
}



void Cls_ItsCompoPic::OnBnClickedBtnOneset()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	int iRet = -1;
	TITS_MergeInfo tMergeInfo = {0};
	memset(&tMergeInfo, 0, sizeof(TITS_MergeInfo));
	tMergeInfo.m_iSize = sizeof(tMergeInfo);
	tMergeInfo.m_iMergeType = ITS_MERGE_TYPE_ZERO;
	tMergeInfo.m_iMergeMode = m_cboOneImage.GetCurSel();
	tMergeInfo.m_iResizePercent = GetDlgItemInt(IDC_EDT_PICRATE);
	iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLINET_PICTURE_MERGE, m_iChannel, &tMergeInfo, sizeof(tMergeInfo));
	if(0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetDevConfig[NET_CLINET_PICTURE_MERGE](%d, %d)", m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig[NET_CLINET_PICTURE_MERGE](%d, %d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
	}
}

BOOL Cls_ItsCompoPic::UI_UpdateOne()
{
	if (m_iLogonID < 0)
		return FALSE;
	int iRet = -1;
	TITS_MergeInfo tMergeInfo = {0};
	tMergeInfo.m_iMergeType = ITS_MERGE_TYPE_ZERO;
	int ilpBytesReturned = 0;
	iRet =  NetClient_GetDevConfig(m_iLogonID, NET_CLINET_PICTURE_MERGE, m_iChannel, &tMergeInfo, sizeof(tMergeInfo), &ilpBytesReturned);
	if(0 == iRet)
	{
		SetDlgItemInt(IDC_EDT_PICRATE, tMergeInfo.m_iResizePercent);
		m_cboOneImage.SetCurSel(tMergeInfo.m_iMergeMode);
		AddLog(LOG_TYPE_SUCC, "", "NetClient_GetDevConfig[NET_CLINET_PICTURE_MERGE](%d,%d)", m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetDevConfig[NET_CLINET_PICTURE_MERGE](%d,%d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
		return FALSE;
	}
	return TRUE;
}


void Cls_ItsCompoPic::OnBnClickedBtnPicReceive()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Logon id(%d)", m_iLogonID);
		return;
	}

	if (m_iChannel < 0)
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid ChannelNo(%d)", m_iChannel);
		return;
	}

	CString cstrClientIP;
	GetDlgItemText(IDC_EDT_PIC_RCV_CLIENT_IP, cstrClientIP);
	if (1 != IsValidIP(cstrClientIP.GetBuffer()))
	{
		AddLog(LOG_TYPE_MSG, "", "Invalid Ip(%s)", cstrClientIP);
		cstrClientIP.ReleaseBuffer();
		return;
	}
	cstrClientIP.ReleaseBuffer();

	ItsPicRevcClient tItsPicRevcClient = {0};
	tItsPicRevcClient.iSize = sizeof(ItsPicRevcClient);
	memcpy_s(tItsPicRevcClient.cIP, LENGTH_IPV4, cstrClientIP, LENGTH_IPV4);

	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_PICREVCLIENT, m_iChannel, (void*)&tItsPicRevcClient, sizeof(ItsPicRevcClient));
	
	if(0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_SetITSExtraInfo[PICREVCLIENT](%d, %d)", m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetITSExtraInfo[PICREVCLIENT](%d, %d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
	}
	return;
}

void Cls_ItsCompoPic::UI_UpdatePicRecv()
{
	ItsPicRevcClient tItsPicRevcClient = {0};
	tItsPicRevcClient.iSize = sizeof(ItsPicRevcClient);

	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_PICREVCLIENT, m_iChannel, (void*)&tItsPicRevcClient, sizeof(ItsPicRevcClient));

	if(0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "", "NetClient_GetITSExtraInfo[PICREVCLIENT](%d, %d)", m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetITSExtraInfo[PICREVCLIENT](%d, %d), error(%d)", m_iLogonID, m_iChannel, GetLastError());
		return;
	}
	
	CString cstrClientIp = tItsPicRevcClient.cIP;

	SetDlgItemText(IDC_EDT_PIC_RCV_CLIENT_IP, cstrClientIp);
}
