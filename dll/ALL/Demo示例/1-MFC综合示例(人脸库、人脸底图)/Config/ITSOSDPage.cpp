// ITSOSDPage.cpp : implementation file
//

#include "stdafx.h"
#include "ITSOSDPage.h"

#define MAX_ZOOM_SCALE		500 //µç×Ó·Å´ó×î´ó±ÈÀý500

IMPLEMENT_DYNAMIC(CLS_ITSOSDPage, CDialog)

CLS_ITSOSDPage::CLS_ITSOSDPage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ITSOSDPage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannel = -1;
}

CLS_ITSOSDPage::~CLS_ITSOSDPage()
{
}

void CLS_ITSOSDPage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_TIME, m_chkEnable[0]);
	DDX_Control(pDX, IDC_CHECK_ROADNAME, m_chkEnable[1]);
	DDX_Control(pDX, IDC_CHECK_LANNAME, m_chkEnable[2]);
	DDX_Control(pDX, IDC_CHECK_LANDIR, m_chkEnable[3]);
	DDX_Control(pDX, IDC_CHECK_SPEED, m_chkEnable[4]);
	DDX_Control(pDX, IDC_CHECK_LIMITSPEED, m_chkEnable[5]);
	DDX_Control(pDX, IDC_CHECK_OVERSPEED, m_chkEnable[6]);
	DDX_Control(pDX, IDC_CHECK_LICENSE, m_chkEnable[7]);
	DDX_Control(pDX, IDC_CHECK_DEVICENUM, m_chkEnable[8]);
	DDX_Control(pDX, IDC_CHECK_REDLTTM, m_chkEnable[9]);
	DDX_Control(pDX, IDC_CHECK_CHECKTIME, m_chkEnable[10]);
	DDX_Control(pDX, IDC_CHECK_CHECKNO, m_chkEnable[11]);
	DDX_Control(pDX, IDC_CHECK_AREASHOW, m_chkEnable[12]);
	DDX_Control(pDX, IDC_CHECK_OSDDBGINFO, m_chkEnable[13]);
	DDX_Control(pDX, IDC_CHECK_AREAINFOSHOW, m_chkEnable[14]);
	DDX_Control(pDX, IDC_EDIT_OSD_X, m_edtOSDX);
	DDX_Control(pDX, IDC_EDIT_OSD_Y, m_edtOSDY);
	DDX_Control(pDX, IDC_CHECK_PARESET, m_chkEnable[15]);
	DDX_Control(pDX, IDC_CHECK_DEVSTAT, m_chkEnable[16]);
	DDX_Control(pDX, IDC_BUTTON_OSD, m_btnOSD);
	DDX_Control(pDX, IDC_CHK_COLOR, m_chkEnable[17]);
	DDX_Control(pDX, IDC_CHECK_CARCOLOR, m_chkEnable[18]);
	DDX_Control(pDX, IDC_CHECK_ROADNO, m_chkEnable[19]);
	DDX_Control(pDX, IDC_CHECK_IllegalType, m_chkEnable[20]);
	DDX_Control(pDX, IDC_CHECK_ROADUPDOWN, m_chkEnable[21]);
	DDX_Control(pDX, IDC_CHECK_SECURITYCODE, m_chkEnable[22]);
	DDX_Control(pDX, IDC_CHECK_CARFLAG, m_chkEnable[23]);
	DDX_Control(pDX, IDC_CBO_OVERLAYLOCATION, m_cboLocation);
	DDX_Control(pDX, IDC_CBO_FONTCOLOR, m_cboFontColor);
	DDX_Control(pDX, IDC_CBO_FONTSIZE, m_cboFontSize);
	DDX_Control(pDX, IDC_COMBO4, m_cboPicOverlay);
	DDX_Control(pDX, IDC_EDIT_LEFTMARGIN, m_editLeftMargin);
	DDX_Control(pDX, IDC_EDITRIGHTMARGIN, m_editRightMargin);
	DDX_Control(pDX, IDC_CHECK_AFTERREDLT, m_chkEnable[24]);
	DDX_Control(pDX, IDC_CHECK_ILLEGAICODE, m_chkEnable[25]);
	DDX_Control(pDX, IDC_CHECK_VEHICLETYPE, m_chkEnable[26]);
	DDX_Control(pDX, IDC_CHECK_REDENDTM, m_chkEnable[27]);
	DDX_Control(pDX, IDC_CHECK_FASTENSB, m_chkEnable[28]);
	DDX_Control(pDX, IDC_CHECK_MAINFACE, m_chkEnable[29]);
	DDX_Control(pDX, IDC_CHECK_COPILOTFACE, m_chkEnable[30]);
	DDX_Control(pDX, IDC_CHECK_TIME3, m_chkEnable2[0]);
	DDX_Control(pDX, IDC_EDIT_TIME, m_editTime);
	DDX_Control(pDX, IDC_EDIT_OROADNAME, m_editORoadname);
	DDX_Control(pDX, IDC_CHECK_OROADNAME, m_chkEnable2[1]);
	DDX_Control(pDX, IDC_CHECK_OLANNAME, m_chkEnable2[2]);
	DDX_Control(pDX, IDC_CHECK_KEEPTYPE, m_chkOneOverLay);
}


BEGIN_MESSAGE_MAP(CLS_ITSOSDPage, CLS_BasePage)
	ON_BN_CLICKED(IDC_BUTTON_OSD, &CLS_ITSOSDPage::OnBnClickedButtonOsd)
	ON_BN_CLICKED(IDC_BTN_LOCATIONSET, &CLS_ITSOSDPage::OnBnClickedBtnLocationset)
	ON_BN_CLICKED(IDC_BTN_FONTSET, &CLS_ITSOSDPage::OnBnClickedBtnFontset)
	ON_BN_CLICKED(IDC_BTN_TYPESET, &CLS_ITSOSDPage::OnBnClickedBtnTypeset)
	ON_BN_CLICKED(IDC_BTN_MARGINSET, &CLS_ITSOSDPage::OnBnClickedBtnMarginset)
	ON_BN_CLICKED(IDC_CHECK_TIME3, &CLS_ITSOSDPage::OnBnClickedCheckTime3)
	ON_BN_CLICKED(IDC_BTN_RENAMESET, &CLS_ITSOSDPage::OnBnClickedBtnRenameset)
	ON_BN_CLICKED(IDC_CHECK_OROADNAME, &CLS_ITSOSDPage::OnBnClickedCheckOroadname)
	ON_BN_CLICKED(IDC_CHECK_OLANNAME, &CLS_ITSOSDPage::OnBnClickedCheckOlanname)
	ON_BN_CLICKED(IDC_CHECK_KEEPTYPE, &CLS_ITSOSDPage::OnBnClickedCheckKeeptype)
	ON_CBN_SELCHANGE(IDC_COMBO4, &CLS_ITSOSDPage::OnCbnSelchangeCombo4)
END_MESSAGE_MAP()


// CLS_ITSOSDPage message handlers
BOOL CLS_ITSOSDPage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	m_edtOSDX.SetLimitText(5);
	m_edtOSDY.SetLimitText(5);

	
	UI_UpdateDialog();

	return TRUE;
}

void CLS_ITSOSDPage::OnChannelChanged( int _iLogonID,int _iChannelNo,int /*_iStreamNo*/ )
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

void CLS_ITSOSDPage::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_ITSOSDPage::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_ITS_OSD,IDS_CONFIG_OSD);
	SetDlgItemTextEx(IDC_CHECK_TIME,IDS_CONFIG_ITS_TIME);
	SetDlgItemTextEx(IDC_CHECK_ROADNAME,IDS_CONFIG_ITS_ROADNAME);
	SetDlgItemTextEx(IDC_CHECK_LANNAME,IDS_CONFIG_ITS_LANNAME);
	SetDlgItemTextEx(IDC_CHECK_LANDIR,IDS_CONFIG_ITS_LANDIR);
	SetDlgItemTextEx(IDC_CHECK_SPEED,IDS_CONFIG_ITS_SPEED);
	SetDlgItemTextEx(IDC_CHECK_LIMITSPEED,IDS_CONFIG_ITS_LIMITSPEED);
	SetDlgItemTextEx(IDC_CHECK_OVERSPEED,IDS_CONFIG_ITS_OVERSPEED);
	SetDlgItemTextEx(IDC_CHECK_LICENSE,IDS_CONFIG_ITS_LICENSE);
	SetDlgItemTextEx(IDC_CHECK_DEVICENUM,IDS_CONFIG_ITS_DEVICENUM);
	SetDlgItemTextEx(IDC_CHECK_REDLTTM,IDS_CONFIG_ITS_REDLTTM);
	SetDlgItemTextEx(IDC_CHECK_CHECKTIME,IDS_CONFIG_ITS_CHECKTIME);
	SetDlgItemTextEx(IDC_CHECK_CHECKNO,IDS_CONFIG_ITS_CHECKNO);
	SetDlgItemTextEx(IDC_CHECK_AREASHOW,IDS_CONFIG_ITS_AREASHOW);
	SetDlgItemTextEx(IDC_CHECK_OSDDBGINFO,IDS_CONFIG_ITS_OSDDBGINFO);
	SetDlgItemTextEx(IDC_CHECK_AREAINFOSHOW,IDS_CONFIG_ITS_AREAINFOSHOW);
	SetDlgItemTextEx(IDC_CHECK_PARESET,IDS_CONFIG_ITS_PARESET);
	SetDlgItemTextEx(IDC_CHECK_DEVSTAT,IDS_CONFIG_ITS_DEVSTAT);
	SetDlgItemTextEx(IDC_BUTTON_OSD,IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_OPTIMIZE,IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_LICENSE,IDS_SET);
	SetDlgItemTextEx(IDC_CHK_COLOR,IDS_CONFIG_COLOR_OSD);

	SetDlgItemTextEx(IDC_CHECK_CARCOLOR,IDS_CONFIG_ITS_OSD_CARCOLOR);
	SetDlgItemTextEx(IDC_CHECK_ROADNO,IDS_CONFIG_ITS_OSD_ROADNO);
	SetDlgItemTextEx(IDC_CHECK_IllegalType,IDS_CONFIG_ITS_OSD_ILLEGALTYPE);
	SetDlgItemTextEx(IDC_CHECK_ROADUPDOWN,IDS_CONFIG_ITS_OSD_ROADUPDOWN);
	SetDlgItemTextEx(IDC_CHECK_SECURITYCODE,IDS_CONFIG_ITS_OSD_SECURITYCODE);
	SetDlgItemTextEx(IDC_CHECK_CARFLAG,IDS_CONFIG_ITS_OSD_CARFLAG);
	SetDlgItemTextEx(IDC_STATIC_FONTSIZE, IDS_ITS_FONT_SIZE);
	SetDlgItemTextEx(IDC_STATIC_FONTCOLOR, IDS_ITS_FONT_COLOR);
	SetDlgItemTextEx(IDC_STATIC_OVERLAYLOCATION, IDS_ITS_OVERLAYLOCATION);
	SetDlgItemTextEx(IDC_BTN_LOCATIONSET, IDS_CFG_USER_SET);
	SetDlgItemTextEx(IDC_BTN_FONTSET, IDS_ITS_FONTSET);
	SetDlgItemTextEx(IDC_STATIC_LEFTMARGIN, IDS_ITS_LEFT_MARGIN);
	SetDlgItemTextEx(IDC_STATIC_UPMARGIN, IDS_ITS_UP_MARGIN);
	SetDlgItemTextEx( IDC_STATIC_PICTUREOVERLAY, IDS_ITS_PICTURE_OVERLAY);
	SetDlgItemTextEx(IDC_BTN_TYPESET, IDS_CFG_USER_SET);
	SetDlgItemTextEx(IDC_STATIC_MAINOSD, IDS_ITS_MAIN_OSD);

	SetDlgItemTextEx(IDC_STC_ZOOM_PRECENT, IDS_ITS_ZOOM_PRECENT);
	SetDlgItemTextEx(IDC_STC_CHR_NUM_PER_ROW, IDS_ITS_CHR_NUM_PER_ROW);
	SetDlgItemTextEx(IDC_STC_NEXT_ROW_BEGAIN, IDS_ITS_NEXT_ROW_BEGAIN);
	SetDlgItemTextEx(IDC_STC_POSTION_NUM, IDS_ITS_POSTION_NUM);

	SetDlgItemTextEx(IDC_CHECK_ENABLED, IDS_ITS_ENABLED);
	SetDlgItemTextEx(IDC_BTN_MARGINSET, IDS_CFG_USER_SET);
	SetDlgItemTextEx(IDC_CHECK_ALL, IDS_ITS_CHACK_ALL);
	SetDlgItemTextEx(IDC_STATIC_RENAME, IDS_ITS_RENAME);
	SetDlgItemTextEx(IDC_CHECK_AFTERREDLT, IDS_ITS_AFTERREDLT);
	SetDlgItemTextEx(IDC_CHECK_ILLEGAICODE, IDS_ITS_ILLEGALCODE);
	SetDlgItemTextEx(IDC_CHECK_VEHICLETYPE, IDS_ITS_VEHICLETYPE);
	SetDlgItemTextEx(IDC_CHECK_REDENDTM, IDS_ITS_REDENDTM);
	SetDlgItemTextEx(IDC_CHECK_FASTENSB, IDS_ITS_FASTENSB);
	SetDlgItemTextEx(IDC_CHECK_MAINFACE, IDS_ITS_MAINFACE);
	SetDlgItemTextEx(IDC_CHECK_COPILOTFACE, IDS_ITS_COPILOTFACE);
	SetDlgItemTextEx(IDC_CHECK_TIME2,IDS_CONFIG_ITS_TIME);
	SetDlgItemTextEx(IDC_CHECK_KEEPTYPE, IDS_ITS_KEEPTYPE);
	SetDlgItemTextEx(IDC_BTN_RENAMESET, IDS_CFG_USER_SET);
	SetDlgItemTextEx(IDC_CHECK_OROADNAME, IDS_ITS_OROADNAME);
	SetDlgItemTextEx(IDC_CHECK_OLANNAME, IDS_CONFIG_ITS_ROADWAY_ROADWAYNAME);
	SetDlgItemTextEx(IDC_CHECK_TIME3, IDS_LOG_TIME);
	SetDlgItemTextEx(IDC_STATIC_IMAGEOVERLAY, IDS_ITS_IMAGAOVERLAY);
	//
	InsertString(m_cboLocation,0,IDS_ITS_IMAGE_MID );
	InsertString(m_cboLocation,1,IDS_ITS_IMAGE_DOWN);
	InsertString(m_cboLocation,2,IDS_ITS_IMAGE_UP);
	//
	InsertString(m_cboPicOverlay,0,IDS_ITS_ONE_PICTURE);
	InsertString(m_cboPicOverlay,1,IDS_ITS_CAMERA_IMAGE);
	//
	InsertString(m_cboFontColor,0,IDS_ITS_COLOR_RED);
	InsertString(m_cboFontColor,1,IDS_ITS_COLOR_GREEN);
	InsertString(m_cboFontColor,2,IDS_ITS_COLOR_BLUE );
	InsertString(m_cboFontColor,3,IDS_ITS_COLOR_WHITE);
	//
	InsertString(m_cboFontSize,0,"1");
	InsertString(m_cboFontSize,1,"2");
	InsertString(m_cboFontSize,2,"3");
	InsertString(m_cboFontSize,3,"4");
	InsertString(m_cboFontSize,4,"5");

	UI_UpdateFontSize();
	UI_UpdateOSD();
	UI_UpdateLocationset();
	UI_UpdateType();
	UI_UpdateFont();
	UI_UpdateMargin();
	UI_UpdateRename();
	UI_UpdateCheck();
}


BOOL CLS_ITSOSDPage::UI_UpdateOSD()
{
	if (m_iLogonID < 0)
		return FALSE;
	
	ITS_WordOverLay tWordOverLay = {0};
	tWordOverLay.iChannelNo = m_iChannel;
	for(int i = 0; i < ITS_CHK_MAX1; i++)
	{
		tWordOverLay.iOsdType = i;
		int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_ITSWORDOVERLAY_CMD_GET, m_iChannel, &tWordOverLay, sizeof(tWordOverLay));
		if(0 == iRet)
		{
			m_chkEnable[i].SetCheck(tWordOverLay.iEnable);
			if (0 == i)
			{
				SetDlgItemInt(IDC_EDIT_OSD_X, tWordOverLay.iPosX);
				SetDlgItemInt(IDC_EDIT_OSD_Y, tWordOverLay.iPosY);
				SetDlgItemInt(IDC_EDT_ZOOM_PRECENT, tWordOverLay.iZoomScale);
				SetDlgItemInt(IDC_EDT_CHR_NUM_PER_ROW, tWordOverLay.iLineCharNum);
				SetDlgItemInt(IDC_EDT_NEXT_ROW_BEGAIN, tWordOverLay.iBlankCharNum);
				SetDlgItemInt(IDC_EDT_POSTION_NUM, tWordOverLay.iOsdPosNo);
			}
		}
		else
		{
			return FALSE;
			break;
		}
	}
	return TRUE;
}

void CLS_ITSOSDPage::OnBnClickedButtonOsd()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	ITS_WordOverLay tWordOverLay = {0};
	tWordOverLay.iChannelNo = m_iChannel;

	for(int i = 0; i < ITS_CHK_MAX1; i++)
	{
		tWordOverLay.iOsdType = i;
		NetClient_GetITSExtraInfo(m_iLogonID, ITS_ITSWORDOVERLAY_CMD_GET, m_iChannel, &tWordOverLay, sizeof(tWordOverLay));
		tWordOverLay.iEnable = m_chkEnable[i].GetCheck();
		if(false == tWordOverLay.iEnable)
		{
			continue;
		}

		if (0 == i)//only time set pos
		{
			tWordOverLay.iPosX = GetDlgItemInt(IDC_EDIT_OSD_X);
			tWordOverLay.iPosY = GetDlgItemInt(IDC_EDIT_OSD_Y);
		}

		tWordOverLay.iZoomScale = GetDlgItemInt(IDC_EDT_ZOOM_PRECENT);
		if (tWordOverLay.iZoomScale > MAX_ZOOM_SCALE || tWordOverLay.iZoomScale < 0)
		{
			AddLog(LOG_TYPE_MSG,"","Invalid ZoomScale(%d)",tWordOverLay.iZoomScale);
			return;
		}
		tWordOverLay.iLineCharNum = GetDlgItemInt(IDC_EDT_CHR_NUM_PER_ROW);
		tWordOverLay.iBlankCharNum = GetDlgItemInt(IDC_EDT_NEXT_ROW_BEGAIN);
		tWordOverLay.iOsdPosNo = GetDlgItemInt(IDC_EDT_POSTION_NUM);

		NetClient_SetITSExtraInfo(m_iLogonID, ITS_ITSWORDOVERLAY_CMD_SET, m_iChannel, &tWordOverLay, sizeof(tWordOverLay));
	}
}

void CLS_ITSOSDPage::OnBnClickedBtnLocationset()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	ITS_DevCommonInfo tDevCommInfo = {0};
	int iOutLen = 0;
	tDevCommInfo.iType = 3;
	tDevCommInfo.iSize = sizeof(tDevCommInfo);
	int iNum = m_cboLocation.GetCurSel();
	CString str;
	str.Format("%d" , iNum);
	//GetDlgItem(IDC_CBO_OVERLAYLOCATION)->GetWindowText(str);
	//tDevCommInfo.cCommonInfo = str.GetBuffer(0);
	//memcpy(tDevCommInfo.cCommonInfo, str.GetBuffer());
	strcpy_s(tDevCommInfo.cCommonInfo, str);
	//tDevCommInfo.cCommonInfo[0] = m_cboLocation.GetCurSel();
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_ITS_DEV_COMMONINFO, m_iChannel, &tDevCommInfo, sizeof(tDevCommInfo));
	if(0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetDevConfig [NET_CLIENT_ITS_DEV_COMMONINFO](%d,%d)",m_iLogonID,m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetDevConfig [NET_CLIENT_ITS_DEV_COMMONINFO](%d,%d), error(%d)",m_iLogonID,m_iChannel,GetLastError());
	}
}

BOOL CLS_ITSOSDPage::UI_UpdateLocationset()
{
	if (m_iLogonID < 0)
		return FALSE;
	ITS_DevCommonInfo tDevCommInfo = {0};
	tDevCommInfo.iSize = sizeof(tDevCommInfo);
	tDevCommInfo.iType = 3;
	int iOutLen = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_ITS_DEV_COMMONINFO, m_iChannel, &tDevCommInfo, sizeof(tDevCommInfo), &iOutLen);
	if(0 == iRet)
	{
		CString str;
		str.Format("%s", tDevCommInfo.cCommonInfo);
		m_cboLocation.SetCurSel(_ttoi(str));
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetDevConfig[NET_CLIENT_ITS_DEV_COMMONINFO] (%d,%d)",m_iLogonID,m_iChannel);
	}
	else
	{
			AddLog(LOG_TYPE_FAIL,"","NetClient_GetDevConfig[NET_CLIENT_ITS_DEV_COMMONINFO] (%d,%d), error(%d)",m_iLogonID,m_iChannel,GetLastError());
			return FALSE;
	}	
	return TRUE;
}
//?$)A((????!A???!A???????
void CLS_ITSOSDPage::OnBnClickedBtnFontset()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
   int iOSDType = OSDTYPE_ITS;
   int iColor = m_cboFontColor.GetCurSel();
	int iRet = NetClient_SetOSDTypeColor(m_iLogonID, m_iChannel, iOSDType, iColor);
	if(0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC, "","NetClient_SetOSDTypeColor(%d,%d,%d,%d)",m_iLogonID, m_iChannel, iOSDType, iColor);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"", "NetClient_SetOSDTypeColor(%d,%d,%d,%d), error(%d)",m_iLogonID, m_iChannel, iOSDType, iColor,GetLastError());
	}
	int iSize = m_cboFontSize.GetCurSel() + 1;
	int iRet2 = NetClient_GetOSDTypeFontSize(m_iLogonID, m_iChannel, iOSDType, &iSize);
	if(0 == iSize)
	{
		AddLog(LOG_TYPE_SUCC, "","NetClient_GetOSDTypeFontSize(%d,%d,%d,%d)",m_iLogonID, m_iChannel, iOSDType, iSize);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL, "","NetClient_GetOSDTypeFontSize(%d,%d,%d,%d), error(%d)",m_iLogonID, m_iChannel, iOSDType, iSize, GetLastError());
	}
}
//?$)A((???????($??
void CLS_ITSOSDPage::OnBnClickedBtnTypeset()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	ITSPicMergeOverLay tWordOvaerLay = {0};
	tWordOvaerLay.iBufSize = sizeof(tWordOvaerLay);
	tWordOvaerLay.iLaneID = m_iChannel;
	tWordOvaerLay.iOsdType = m_cboPicOverlay.GetCurSel();
	int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_PICMERGEOVERLAY, m_iChannel, &tWordOvaerLay, sizeof(tWordOvaerLay));
	if(0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSRecoParam(%d)",m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSRecoParam(%d),error(%d)",m_iLogonID,GetLastError());
	}
}

void CLS_ITSOSDPage::UI_UpdateCheck()
{
	int iGet = -1;
	iGet = m_cboPicOverlay.GetCurSel();
	if(iGet == 0)
		m_chkOneOverLay.EnableWindow(FALSE);
	else if(iGet == 1)
		m_chkOneOverLay.EnableWindow(TRUE);
}

BOOL CLS_ITSOSDPage::UI_UpdateType()
{
	if (m_iLogonID < 0)
		return FALSE;
	ITSPicMergeOverLay tWordOvaerLay = {0};
	tWordOvaerLay.iBufSize = sizeof(tWordOvaerLay);
	tWordOvaerLay.iLaneID = m_iChannel;
	int iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_PICMERGEOVERLAY, m_iChannel, &tWordOvaerLay, sizeof(tWordOvaerLay));
	if(0 == iRet)
	{
		m_cboPicOverlay.SetCurSel(tWordOvaerLay.iOsdType);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSRecoParam(%d)",m_iLogonID);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSRecoParam(%d), error(%d)",m_iLogonID,GetLastError());
		return FALSE;
	}
	return TRUE;
}
//????$)A!A????????????? 
BOOL  CLS_ITSOSDPage::UI_UpdateFont()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iOSDType = OSDTYPE_ITS;
	int iColor = -1;
	int iRet = NetClient_GetOSDTypeColor(m_iLogonID, m_iChannel, iOSDType, &iColor);
	if(0 == iRet)
	{
		m_cboFontColor.SetCurSel(iColor);
		m_cboPicOverlay.SetCurSel(iOSDType);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetOSDTypeColor(%d,%d)",m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetOSDTypeColor(%d,%d),error(%d)", m_iLogonID, m_iChannel,GetLastError());
		return FALSE;
	}
	return TRUE;
}
//s????$)A!A????(.??
BOOL  CLS_ITSOSDPage::UI_UpdateFontSize()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iOSDType = OSDTYPE_ITS;
	int iSize = -1;
	int iRet = NetClient_GetOSDTypeColor(m_iLogonID, m_iChannel, iOSDType, &iSize);
	if(0 == iRet)
	{
		m_cboFontSize.SetCurSel(iSize - 1);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetOSDTypeColor(%d,%d,%d,%d)", m_iLogonID, m_iChannel, iOSDType, iSize);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetOSDTypeColor(%d,%d,%d,%d), error(%d)", m_iLogonID, m_iChannel, iOSDType, iSize, GetLastError());
		return FALSE;
	}
	
	return TRUE;
}
void CLS_ITSOSDPage::OnBnClickedBtnMarginset()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	int iEnabled = -1;
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_ENABLED);
	if(NULL != pBtn)
	{
		iEnabled = pBtn->GetCheck();
	}
	int iPositionX = GetDlgItemInt(IDC_EDIT_LEFTMARGIN);
	int iPositionY = GetDlgItemInt(IDC_EDIT_UPMARGIN) + 1; //$)AP-RiPhR*#,0SPLXJb:,Re#,KyRT=+KySP5DV5My:sE2R;N;
	int iOSDType = OSDTYPE_ITS;
	int iRet = NetClient_SetOsdType(m_iLogonID, m_iChannel, iPositionX, iPositionY, iOSDType, iEnabled);
	if(0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetOsdType(%d,%d,%d,%d,%d,%d)",m_iLogonID, m_iChannel, iPositionX, iPositionY, iOSDType, iEnabled);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetOsdType(%d,%d,%d,%d,%d,%d),error(%d)",m_iLogonID, m_iChannel, iPositionX, iPositionY, iOSDType, iEnabled,GetLastError());
	}
}

BOOL CLS_ITSOSDPage:: UI_UpdateMargin()
{
	if (m_iLogonID < 0)
		return FALSE;
	int iEnabled = -1;
	int iPositionX = -1;
	int iPositionY = -1;
	int iOSDType = OSDTYPE_ITS; 
	int iRet = NetClient_GetOsdType(m_iLogonID, m_iChannel, iOSDType, &iPositionX, &iPositionY, &iEnabled);
	if(0 == iRet)
	{
		SetDlgItemInt(IDC_EDIT_LEFTMARGIN, iPositionX);
		SetDlgItemInt(IDC_EDIT_UPMARGIN, iPositionY);
		CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_ENABLED);
		if(NULL != pBtn)
		{
			 pBtn->SetCheck(iEnabled);
		}
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetOsdType(%d,%d,%d,%d,%d)",m_iLogonID, m_iChannel, iPositionX, iPositionY, iEnabled);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetOsdType(%d,%d,%d,%d,%d), error(%d)",m_iLogonID, m_iChannel, iPositionX, iPositionY, iEnabled,GetLastError());
		return FALSE;
	}
	return TRUE;
}

void CLS_ITSOSDPage::OnBnClickedCheckTime3()
{
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_TIME);
	if(NULL != pEdit)
	{
		if( 0 == m_chkEnable2[0].GetCheck() )
		{
			pEdit->SetReadOnly(TRUE);
		}
		else
		{
			pEdit->SetReadOnly(FALSE);
		}
	}
}

void CLS_ITSOSDPage::OnBnClickedBtnRenameset()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	ITS_WordOverLay tWordOverLay = {0};
	tWordOverLay.iChannelNo = m_iChannel;
	for(int i = 0;i < ITS_CHK_MAX2;i++)
	{
			tWordOverLay.iOsdType = i;
			NetClient_GetITSExtraInfo(m_iLogonID, ITS_ITSWORDOVERLAY_CMD_GET, m_iChannel, &tWordOverLay, sizeof(tWordOverLay));
			tWordOverLay.iEnable = m_chkEnable2[i].GetCheck();
			if(i == 0)
			{
				CString cstext;
				GetDlgItemText(IDC_EDIT_TIME,cstext);
				strcpy(tWordOverLay.pcOsdName, cstext);
				NetClient_SetITSExtraInfo(m_iLogonID, ITS_ITSWORDOVERLAY_CMD_SET,m_iChannel, &tWordOverLay, sizeof(tWordOverLay));
			}
			else if(i == 1)
			{
				CString cstext;
				GetDlgItemText(IDC_EDIT_OROADNAME,cstext);
				strcpy(tWordOverLay.pcOsdName, cstext);
				NetClient_SetITSExtraInfo(m_iLogonID, ITS_ITSWORDOVERLAY_CMD_SET,m_iChannel, &tWordOverLay, sizeof(tWordOverLay));
			}
			else
			{
				CString cstext;
				GetDlgItemText(IDC_EDIT_OLANNAME,cstext);
				strcpy(tWordOverLay.pcOsdName, cstext);
				NetClient_SetITSExtraInfo(m_iLogonID, ITS_ITSWORDOVERLAY_CMD_SET,m_iChannel, &tWordOverLay, sizeof(tWordOverLay));
			}
	}
}
void CLS_ITSOSDPage::OnBnClickedCheckOroadname()
{
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_OROADNAME);
	if(NULL != pEdit)
	{
		if( 0 == m_chkEnable2[1].GetCheck() )
		{
			pEdit->SetReadOnly(TRUE);
		}
		else
		{
			pEdit->SetReadOnly(FALSE);
		}
	}
}

void CLS_ITSOSDPage::OnBnClickedCheckOlanname()
{
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_OLANNAME);
	if(NULL != pEdit)
	{
		if( 0 == m_chkEnable2[2].GetCheck() )
		{
			pEdit->SetReadOnly(TRUE);
		}
		else
		{
			pEdit->SetReadOnly(FALSE);
		}
	}	
}

BOOL CLS_ITSOSDPage::UI_UpdateRename()
{
	if (m_iLogonID < 0)
		return FALSE;

	ITS_WordOverLay tWordOverLay = {0};
	tWordOverLay.iChannelNo = m_iChannel;
	for(int i = 0;i < ITS_CHK_MAX2;i++)
	{
		tWordOverLay.iOsdType = i;
		NetClient_GetITSExtraInfo(m_iLogonID, ITS_ITSWORDOVERLAY_CMD_GET, m_iChannel, &tWordOverLay, sizeof(tWordOverLay));
		m_chkEnable2[i].SetCheck(tWordOverLay.iEnable);
		if(0 == i)
		{
			CString cstext;
			cstext.Format("%s", tWordOverLay.pcOsdName);
			SetDlgItemText(IDC_EDIT_TIME,cstext);
		}
		else if(1 == i)
		{
			CString cstext;
			cstext.Format("%s", tWordOverLay.pcOsdName);
			SetDlgItemText(IDC_EDIT_OROADNAME,cstext);
		}
		else
		{
			CString cstext;
			cstext.Format("%s", tWordOverLay.pcOsdName);
			SetDlgItemText(IDC_EDIT_OLANNAME,cstext);
		}
	}
	return TRUE;
}
void CLS_ITSOSDPage::OnBnClickedCheckKeeptype()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	ITSPicMergeOverLay tItsPicMergeOverLay = {0};
	tItsPicMergeOverLay.iBufSize = sizeof(tItsPicMergeOverLay);
	tItsPicMergeOverLay.iLaneID = m_iChannel;
	int iGetRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_PICMERGEOVERLAY, m_iChannel, &tItsPicMergeOverLay, sizeof(tItsPicMergeOverLay));
	if(iGetRet != 0)
	{
		return;
	}
	else
	{
		tItsPicMergeOverLay.iOneOSD = m_chkOneOverLay.GetCheck();
		int iRet = NetClient_SetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_PICMERGEOVERLAY, m_iChannel, &tItsPicMergeOverLay, sizeof(tItsPicMergeOverLay));
		if(iRet == 0)
		{
			AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSExtraInfo[ITS_EXTRAINFO_CMD_PICMERGEOVERLAY](%d,%d)",m_iLogonID, m_iChannel);
		}
		else
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSExtraInfo[ITS_EXTRAINFO_CMD_PICMERGEOVERLAY](%d,%d), error(%d)",m_iLogonID, m_iChannel, GetLastError());
		}
	}
}
 BOOL CLS_ITSOSDPage::UI_UpdateCheckKeeptype()
 {
	 if(m_iLogonID < 0)
	 return FALSE;

	ITSPicMergeOverLay tItsPicMergeOverLay = {0};
	tItsPicMergeOverLay.iBufSize = sizeof(tItsPicMergeOverLay);
	tItsPicMergeOverLay.iLaneID = m_iChannel;
	int iGetRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_EXTRAINFO_CMD_PICMERGEOVERLAY, m_iChannel, &tItsPicMergeOverLay, sizeof(tItsPicMergeOverLay));
	if(iGetRet == 0)
	{
		m_chkOneOverLay.SetCheck(tItsPicMergeOverLay.iOneOSD);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSExtraInfo[ITS_EXTRAINFO_CMD_PICMERGEOVERLAY](%d,%d)",m_iLogonID, m_iChannel);
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSExtraInfo[ITS_EXTRAINFO_CMD_PICMERGEOVERLAY](%d,%d), error(%d)",m_iLogonID, m_iChannel, GetLastError());
		return FALSE;
	}

	return TRUE;
 }
 void CLS_ITSOSDPage::OnCbnSelchangeCombo4()
 {
	UI_UpdateCheck();
 }
