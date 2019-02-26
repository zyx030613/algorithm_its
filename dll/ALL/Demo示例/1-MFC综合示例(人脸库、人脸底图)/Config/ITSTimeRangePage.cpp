// ITSTimeRangePage.cpp : implementation file
//

#include "stdafx.h"
#include "ITSTimeRangePage.h"


// CLS_ITSTimeRangePage dialog

IMPLEMENT_DYNAMIC(CLS_ITSTimeRangePage, CDialog)

CLS_ITSTimeRangePage::CLS_ITSTimeRangePage(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_ITSTimeRangePage::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
}

CLS_ITSTimeRangePage::~CLS_ITSTimeRangePage()
{
}

void CLS_ITSTimeRangePage::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TIMERANGEINDEX, m_cboTimeRangeIndex);
	DDX_Control(pDX, IDC_CHECK_TIMERANGEINDEX, m_chkTimeRangeIndex);
	DDX_Control(pDX, IDC_EDIT_TIMERANGE, m_edtTimeRange);
	DDX_Control(pDX, IDC_BUTTON_TIMERANGE, m_btnTimeRange);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_cboType);
	DDX_Control(pDX, IDC_COMBO_AUTOENABLE, m_cboAutoEnable);
	DDX_Control(pDX, IDC_EDIT_TIMERANGE_PARAM1, m_edtParam[0]);
	DDX_Control(pDX, IDC_EDIT_TIMERANGE_PARAM2, m_edtParam[1]);
	DDX_Control(pDX, IDC_EDIT_TIMERANGE_PARAM3, m_edtParam[2]);
	DDX_Control(pDX, IDC_EDIT_TIMERANGE_PARAM4, m_edtParam[3]);
	DDX_Control(pDX, IDC_BUTTON_PARAM, m_btnParam);
	DDX_Control(pDX, IDC_CHECK_AGCBLOCK_BIT0, m_chkBit[0]);
	DDX_Control(pDX, IDC_CHECK_AGCBLOCK_BIT1, m_chkBit[1]);
	DDX_Control(pDX, IDC_CHECK_AGCBLOCK_BIT2, m_chkBit[2]);
	DDX_Control(pDX, IDC_CHECK_AGCBLOCK_BIT3, m_chkBit[3]);
	DDX_Control(pDX, IDC_CHECK_AGCBLOCK_BIT4, m_chkBit[4]);
	DDX_Control(pDX, IDC_COMBO_BLOCK, m_cboBlock);
	DDX_Control(pDX, IDC_CHECK_FLASHLAMP, m_chkFlashLamp);
	DDX_Control(pDX, IDC_EDIT_BLOCK_X, m_edtBlockX);
	DDX_Control(pDX, IDC_EDIT_BLOCK_Y, m_edtBlockY);
	DDX_Control(pDX, IDC_BUTTON_BLOCK, m_btnBlock);
	DDX_Control(pDX, IDC_COMBO_DETECTMODE, m_cboDetectMode);
	DDX_Control(pDX, IDC_BUTTON_DETECTMODE, m_btnDetectMode);
	DDX_Control(pDX, IDC_COMBO_LOOPMODE, m_cboLoopMode);
	DDX_Control(pDX, IDC_BUTTON_LOOPMODE, m_btnLoopMode);
	DDX_Control(pDX, IDC_COMBO_DEVICETYPE, m_cboDeviceType);
	DDX_Control(pDX, IDC_BUTTON_DEVICETYPE, m_chkDeviceType);
	DDX_Control(pDX, IDC_EDIT_SWITCHTIME, m_edtSwitchTime);
	DDX_Control(pDX, IDC_EDIT_DELAYTIME, m_edtDelayTime);
	DDX_Control(pDX, IDC_BUTTON_SWITCH_DELAY, m_btnSwitchDelay);
	DDX_Control(pDX, IDC_COMBO_CAMERAPARAM, m_cboCameraParam);
	DDX_Control(pDX, IDC_EDIT_VALUE, m_edtValue);
	DDX_Control(pDX, IDC_BUTTON_CAMERA, m_btnCamera);
}


BEGIN_MESSAGE_MAP(CLS_ITSTimeRangePage, CLS_BasePage)
	ON_CBN_SELCHANGE(IDC_COMBO_TIMERANGEINDEX, &CLS_ITSTimeRangePage::OnCbnSelchangeComboTimerangeindex)
	ON_BN_CLICKED(IDC_BUTTON_TIMERANGE, &CLS_ITSTimeRangePage::OnBnClickedButtonTimerange)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, &CLS_ITSTimeRangePage::OnCbnSelchangeComboType)
	ON_BN_CLICKED(IDC_BUTTON_PARAM, &CLS_ITSTimeRangePage::OnBnClickedButtonParam)
	ON_BN_CLICKED(IDC_BUTTON_AGCBLOCK, &CLS_ITSTimeRangePage::OnBnClickedButtonAgcblock)
	ON_BN_CLICKED(IDC_CHECK_FLASHLAMP, &CLS_ITSTimeRangePage::OnBnClickedCheckFlashlamp)
	ON_CBN_SELCHANGE(IDC_COMBO_BLOCK, &CLS_ITSTimeRangePage::OnCbnSelchangeComboBlock)
	ON_BN_CLICKED(IDC_BUTTON_BLOCK, &CLS_ITSTimeRangePage::OnBnClickedButtonBlock)
	ON_BN_CLICKED(IDC_BUTTON_DETECTMODE, &CLS_ITSTimeRangePage::OnBnClickedButtonDetectmode)
	ON_BN_CLICKED(IDC_BUTTON_LOOPMODE, &CLS_ITSTimeRangePage::OnBnClickedButtonLoopmode)
	ON_BN_CLICKED(IDC_BUTTON_DEVICETYPE, &CLS_ITSTimeRangePage::OnBnClickedButtonDevicetype)
	ON_BN_CLICKED(IDC_BUTTON_SWITCH_DELAY, &CLS_ITSTimeRangePage::OnBnClickedButtonSwitchDelay)
	ON_CBN_SELCHANGE(IDC_COMBO_CAMERAPARAM, &CLS_ITSTimeRangePage::OnCbnSelchangeComboCameraparam)
	ON_BN_CLICKED(IDC_BUTTON_CAMERA, &CLS_ITSTimeRangePage::OnBnClickedButtonCamera)
END_MESSAGE_MAP()


// CLS_ITSTimeRangePage message handlers
BOOL CLS_ITSTimeRangePage::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	for (int i=0; i<8; i++)
	{
		CString strNo;
		strNo.Format("%d" ,i);
		m_cboTimeRangeIndex.AddString(strNo);
	}
	m_cboTimeRangeIndex.AddString("255");
	m_cboTimeRangeIndex.SetCurSel(0);

	m_edtTimeRange.SetLimitText(20);
	for (int i=0; i<4; i++)
	{
		m_edtParam[i].SetLimitText(20);
	}
	m_edtBlockX.SetLimitText(10);
	m_edtBlockY.SetLimitText(10);
	m_edtSwitchTime.SetLimitText(5);
	m_edtDelayTime.SetLimitText(5);
	m_edtValue.SetLimitText(5);

	for (int i=0; i<5; i++)
	{
		CString strNo;
		strNo.Format("%d",i);
		m_cboBlock.AddString(strNo);
	}
	m_cboBlock.SetCurSel(0);

	m_cboDeviceType.AddString("0--CSR_IK16");
	m_cboDeviceType.AddString("1--CSR90NGA");
	m_cboDeviceType.AddString("2--T324V20");
	m_cboDeviceType.AddString("3--T324E");

	m_cboCameraParam.AddString("JPEGQulity");
	m_cboCameraParam.AddString("LUT");

	UI_UpdateDialog();

	return TRUE;
}

void CLS_ITSTimeRangePage::OnChannelChanged(int _iLogonID,int _iChannelNo,int _iStreamNo)
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

	UI_UpdateTimeAgcFlash();
	UI_UpdateTimeRangeParam();
	UI_UpdateBlock();
	UI_UpdateGPEGQuality();
	UI_UpdateDetectmode();
	UI_UpdateLoopmode();
	UI_UpdateDevicetype();
	UI_UpdateSwitchDelay();
}

void CLS_ITSTimeRangePage::OnLanguageChanged(int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_ITSTimeRangePage::UI_UpdateDialog()
{
	InsertString(m_cboType,0,IDS_CONFIG_ITS_TYPE0);
	InsertString(m_cboType,1,IDS_CONFIG_ITS_TYPE1);
	InsertString(m_cboType,2,IDS_CONFIG_ITS_TYPE2);
	InsertString(m_cboType,3,IDS_CONFIG_ITS_TYPE3);
	InsertString(m_cboType,4,IDS_CONFIG_ITS_TYPE4);
	InsertString(m_cboType,5,IDS_CONFIG_ITS_TYPE5);
	InsertString(m_cboType,6,IDS_CONFIG_ITS_TYPE6);
	InsertString(m_cboType,7,IDS_CONFIG_ITS_TYPE7);
	InsertString(m_cboType,8,IDS_CONFIG_ITS_TYPE8);
	InsertString(m_cboType,9,IDS_CONFIG_ITS_TYPE9);
	InsertString(m_cboType,10,IDS_CONFIG_ITS_TYPE10);
	InsertString(m_cboType,11,IDS_CONFIG_ITS_TYPE11);
	InsertString(m_cboType,12,IDS_CONFIG_ITS_TYPE12);
	InsertString(m_cboType,13,IDS_CONFIG_ITS_TYPE13);
	InsertString(m_cboType,14,IDS_CONFIG_ITS_TYPE14);
	InsertString(m_cboType,15,IDS_CONFIG_ITS_TYPE15);
	InsertString(m_cboType,16,IDS_CONFIG_ITS_TYPE16);
	InsertString(m_cboType,17,IDS_CONFIG_ITS_TYPE17);
	InsertString(m_cboType,18,IDS_CONFIG_ITS_TYPE18);
	InsertString(m_cboType,19,IDS_CONFIG_ITS_TYPE19);
	m_cboType.AddString("20-聚焦模式");
	m_cboType.AddString("21-最小聚焦距离");
	m_cboType.AddString("22-日夜切换");
	m_cboType.AddString("23-恢复默认");
	m_cboType.AddString("24-去雾");
	m_cboType.AddString("25-AE调节速度");
	m_cboType.AddString("26-SmartIR");
	m_cboType.AddString("27-曝光补偿");
	m_cboType.AddString("28-高感度");
	m_cboType.AddString("29-慢曝光");
	m_cboType.AddString("30-自动对比度");
	m_cboType.AddString("31-图像冻结");
	m_cboType.AddString("32-红外校正");
	m_cboType.AddString("33-色彩增益");
	m_cboType.AddString("34-色彩相位");
	m_cboType.AddString("35-低照色彩抑制");
	m_cboType.AddString("36-聚焦类型");
	m_cboType.AddString("37-夜视强化");
	m_cboType.AddString("38-暗角处理");


	InsertString(m_cboAutoEnable,0,IDS_CONFIG_ITS_AUTOENABLE0);
	InsertString(m_cboAutoEnable,1,IDS_CONFIG_ITS_AUTOENABLE1);
	InsertString(m_cboAutoEnable,2,IDS_CONFIG_ITS_AUTOENABLE2);

	InsertString(m_cboDetectMode,0,IDS_CONFIG_ITS_DETECTMODE0);
	InsertString(m_cboDetectMode,1,IDS_CONFIG_ITS_DETECTMODE1);
	InsertString(m_cboDetectMode,2,IDS_CONFIG_ITS_DETECTMODE2);
	InsertString(m_cboDetectMode,3,IDS_CONFIG_ITS_DETECTMODE3);

	InsertString(m_cboLoopMode,0,IDS_CONFIG_ITS_LOOPMODE0);
	InsertString(m_cboLoopMode,1,IDS_CONFIG_ITS_LOOPMODE1);

	SetDlgItemTextEx(IDC_STATIC_TIMERANGEINDEX,IDS_CONFIG_ITS_TIMERANGE_INDEX);
	SetDlgItemTextEx(IDC_CHECK_TIMERANGEINDEX,IDS_CONFIG_ITS_TIMERANGE_ENABLE);
	SetDlgItemTextEx(IDC_STATIC_TIMERANGE,IDS_CONFIG_ITS_TIMERANGE_RANGE);
	SetDlgItemTextEx(IDC_BUTTON_TIMERANGE,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_TIMERANGEPARAM,IDS_CONFIG_ITS_TIMERANGE_PARAM);
	SetDlgItemTextEx(IDC_STATIC_TYPE,IDS_CONFIG_ITS_TIMERANGE_TYPE);
	SetDlgItemTextEx(IDC_STATIC_AUTOENABLE,IDS_CONFIG_ITS_TIMERANGE_AUTOENABLE);
	SetDlgItemTextEx(IDC_STATIC_PARAM1,IDS_CONFIG_ITS_TIMERANGE_PARAM1);
	SetDlgItemTextEx(IDC_STATIC_PARAM2,IDS_CONFIG_ITS_TIMERANGE_PARAM2);
	SetDlgItemTextEx(IDC_STATIC_PARAM3,IDS_CONFIG_ITS_TIMERANGE_PARAM3);
	SetDlgItemTextEx(IDC_STATIC_PARAM4,IDS_CONFIG_ITS_TIMERANGE_PARAM4);
	SetDlgItemTextEx(IDC_BUTTON_PARAM,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_AGCBLOCK,IDS_CONFIG_ITS_TIMERANGE_AGCBLOCK);
	SetDlgItemTextEx(IDC_BUTTON_AGCBLOCK,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_BLOCK,IDS_CONFIG_ITS_TIMERANGE_BLOCK);
	SetDlgItemTextEx(IDC_CHECK_FLASHLAMP,IDS_CONFIG_ITS_TIMERANGE_FLASHLAMP);
	SetDlgItemTextEx(IDC_BUTTON_FLASHLAMP,IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON_BLOCK,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_DETECTMODE,IDS_CONFIG_ITS_TIMERANGE_DETECTMODE);
	SetDlgItemTextEx(IDC_BUTTON_DETECTMODE,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_LOOPMODE,IDS_CONFIG_ITS_TIMERANGE_LOOPMODE);
	SetDlgItemTextEx(IDC_BUTTON_LOOPMODE,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_DEVICETYPE,IDS_CONFIG_ITS_TIMERANGE_DEVICETYPE);
	SetDlgItemTextEx(IDC_BUTTON_DEVICETYPE,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_SWITCHTIME,IDS_CONFIG_ITS_TIMERANGE_SWITCHTIME);
	SetDlgItemTextEx(IDC_STATIC_DELAYTIME,IDS_CONFIG_ITS_TIMERANGE_DELAYTIME);
	SetDlgItemTextEx(IDC_BUTTON_SWITCH_DELAY,IDS_SET);
	SetDlgItemTextEx(IDC_STATIC_CAMERAPARAM,IDS_CONFIG_ITS_TIMERANGE_CAMERAPARAM);
	SetDlgItemTextEx(IDC_STATIC_VALUE,IDS_CONFIG_ITS_TIMERANGE_VALUE);
	SetDlgItemTextEx(IDC_BUTTON_CAMERA,IDS_SET);

}

BOOL CLS_ITSTimeRangePage::UI_UpdateTimeAgcFlash()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iTimeRangeIndex = GetDlgItemInt(IDC_COMBO_TIMERANGEINDEX);
	ITS_TTimeRange pa = {0};
	int iRet = NetClient_GetITSTimeRangeEnable(m_iLogonID, m_iChannelNo, iTimeRangeIndex, &pa, sizeof(pa));
	if (0 == iRet)
	{
		m_chkTimeRangeIndex.SetCheck(pa.iEnable?BST_CHECKED:BST_UNCHECKED);
		int iBeginHour = (pa.iTimeRange)>>24&0xFF;
		int iBeginMinute = (pa.iTimeRange)>>16&0xFF;
		int iEndHour = (pa.iTimeRange)>>8&0xFF;
		int iEndMinute = (pa.iTimeRange)&0xFF;
		CString strTimeRange;
		strTimeRange.Format("%02d:%02d-%02d:%02d", iBeginHour, iBeginMinute, iEndHour, iEndMinute);
		SetDlgItemText(IDC_EDIT_TIMERANGE, strTimeRange);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSTimeRangeEnable (%d,%d)",m_iLogonID,sizeof(pa));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSTimeRangeEnable (%d,%d)",m_iLogonID,sizeof(pa));
	}
	int iAgcBlock = -1;
	iRet = NetClient_GetITSTimeRange(m_iLogonID, iTimeRangeIndex, ITS_CMD_GET_TIMERANGE_AGCBLOCK, &iAgcBlock, sizeof(iAgcBlock));
	if (0 == iRet)
	{
		for (int i=0; i<5; i++)
		{
			m_chkBit[i].SetCheck(((iAgcBlock>>i)&0x01)?BST_CHECKED:BST_UNCHECKED);
		}
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSTimeRange (%d,%d)",m_iLogonID,sizeof(iAgcBlock));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSTimeRange (%d,%d)",m_iLogonID,sizeof(iAgcBlock));
	}
	TITS_FlashEnable tFlashEnable = {0};
	iRet = NetClient_GetITSTimeRange(m_iLogonID, iTimeRangeIndex, ITS_CMD_GET_TIMERANGE_FLASHLAMP, &tFlashEnable, sizeof(tFlashEnable));
	if (0 == iRet)
	{
		m_chkFlashLamp.SetCheck(tFlashEnable.m_iFlashLampEnable?BST_CHECKED:BST_UNCHECKED);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSTimeRange (%d,%d)",m_iLogonID,sizeof(tFlashEnable));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSTimeRange (%d,%d)",m_iLogonID,sizeof(tFlashEnable));
	}
	return TRUE;
}
void CLS_ITSTimeRangePage::OnCbnSelchangeComboTimerangeindex()
{
	UI_UpdateTimeAgcFlash();
	UI_UpdateTimeRangeParam();

}
void CLS_ITSTimeRangePage::OnBnClickedButtonTimerange()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iTimeRangeIndex = GetDlgItemInt(IDC_COMBO_TIMERANGEINDEX);
	ITS_TTimeRange pa = {0};
	pa.iEnable = (m_chkTimeRangeIndex.GetCheck() == BST_CHECKED)?1:0;
	char cTimeRange[20];
	GetDlgItemText(IDC_EDIT_TIMERANGE, cTimeRange, 20);
	int iBeginHour = 0;
	int iBeginMinute = 0;
	int iEndHour = 0;
	int iEndMinute = 0;
	sscanf_s(cTimeRange, "%d:%d-%d:%d", &iBeginHour, &iBeginMinute, &iEndHour, &iEndMinute);
	pa.iTimeRange =  (iBeginHour<<24)|(iBeginMinute<<16)|(iEndHour<<8)| iEndMinute;
	int iRet = NetClient_SetITSTimeRangeEnable(m_iLogonID, m_iChannelNo, iTimeRangeIndex, &pa, sizeof(pa));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSTimeRangeEnable (%d,%d)",m_iLogonID,sizeof(pa));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSTimeRangeEnable (%d,%d)",m_iLogonID,sizeof(pa));
	}
}

BOOL CLS_ITSTimeRangePage::UI_UpdateTimeRangeParam()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iTimeRangeIndex = GetDlgItemInt(IDC_COMBO_TIMERANGEINDEX);
	int iType = m_cboType.GetCurSel();
	ITS_TTimeRangeParam pb = {0};
	int iRet = NetClient_GetHDTimeRangeParam(m_iLogonID, m_iChannelNo, iTimeRangeIndex, &pb, sizeof(pb));
	if (0 == iRet)
	{
		m_cboAutoEnable.SetCurSel(pb.iAutoEnable[iType]);
		SetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM1, pb.iParam1[iType]);
		SetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM2, pb.iParam2[iType]);
		SetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM3, pb.iParam3[iType]);
		SetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM4, pb.iParam4[iType]);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetHDTimeRangeParam (%d,%d)",m_iLogonID,sizeof(pb));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetHDTimeRangeParam (%d,%d)",m_iLogonID,sizeof(pb));
	}
	return TRUE;
}

void CLS_ITSTimeRangePage::OnCbnSelchangeComboType()
{
	UI_UpdateTimeRangeParam();
}

void CLS_ITSTimeRangePage::OnBnClickedButtonParam()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iTimeRangeIndex = GetDlgItemInt(IDC_COMBO_TIMERANGEINDEX);
	ITS_TTimeRangeParam pb = {0};
	pb.iType = m_cboType.GetCurSel();
	pb.iAutoEnable[pb.iType] = m_cboAutoEnable.GetCurSel();
	pb.iParam1[pb.iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM1);
	pb.iParam2[pb.iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM2);
	pb.iParam3[pb.iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM3);
	pb.iParam4[pb.iType] = GetDlgItemInt(IDC_EDIT_TIMERANGE_PARAM4);	
	int iRet = NetClient_SetHDTimeRangeParam(m_iLogonID, m_iChannelNo, iTimeRangeIndex, &pb, sizeof(pb));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetHDTimeRangeParam (%d,%d)",m_iLogonID,sizeof(pb));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetHDTimeRangeParam (%d,%d)",m_iLogonID,sizeof(pb));
	}
}

void CLS_ITSTimeRangePage::OnBnClickedButtonAgcblock()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	
	int iTimeRangeIndex = GetDlgItemInt(IDC_COMBO_TIMERANGEINDEX);
	int iAgcBlock = 0;
	for (int i=0; i<5; i++)
	{
		iAgcBlock += (m_chkBit[i].GetCheck() == BST_CHECKED)?(1<<i):0;
	}
	int iRet = NetClient_SetITSTimeRange(m_iLogonID, iTimeRangeIndex, ITS_CMD_SET_TIMERANGE_AGCBLOCK, &iAgcBlock, sizeof(iAgcBlock));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSTimeRange (%d,%d)",m_iLogonID,sizeof(iAgcBlock));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSTimeRange (%d,%d)",m_iLogonID,sizeof(iAgcBlock));
	}
}

void CLS_ITSTimeRangePage::OnBnClickedCheckFlashlamp()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	
	int iTimeRangeIndex = GetDlgItemInt(IDC_COMBO_TIMERANGEINDEX);
	int iEnable = (m_chkFlashLamp.GetCheck() == BST_CHECKED)?1:0;
	int iRet = NetClient_SetITSTimeRange(m_iLogonID, iTimeRangeIndex, ITS_CMD_SET_TIMERANGE_FLASHLAMP, &iEnable, sizeof(iEnable));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSTimeRange (%d,%d)",m_iLogonID,sizeof(iEnable));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSTimeRange (%d,%d)",m_iLogonID,sizeof(iEnable));
	}
}
BOOL CLS_ITSTimeRangePage::UI_UpdateBlock()
{
	if (m_iLogonID < 0)
		return FALSE;

	int iBlockID = m_cboBlock.GetCurSel();
	int iX = -1;
	int iY = -1;
	int iRet = NetClient_GetITSBlock(m_iLogonID, iBlockID, &iX, &iY);
	if (0 == iRet)
	{
		SetDlgItemInt(IDC_EDIT_BLOCK_X, iX,FALSE);
		SetDlgItemInt(IDC_EDIT_BLOCK_Y, iY,FALSE);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetITSBlock (%d,%d,%d,%d)",m_iLogonID,iBlockID,iX,iY);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetITSBlock (%d,%d,%d,%d)",m_iLogonID,iBlockID,iX,iY);
	}
	return TRUE;	
}

void CLS_ITSTimeRangePage::OnCbnSelchangeComboBlock()
{
	UI_UpdateBlock();
}

void CLS_ITSTimeRangePage::OnBnClickedButtonBlock()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}
	
	int iBlockID = m_cboBlock.GetCurSel();
	int iX = GetDlgItemInt(IDC_EDIT_BLOCK_X,NULL,FALSE);
	int iY = GetDlgItemInt(IDC_EDIT_BLOCK_Y,NULL,FALSE);
	int iRet = NetClient_SetITSBlock(m_iLogonID, iBlockID, iX, iY);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSBlock (%d,%d,%d,%d)",m_iLogonID,iBlockID,iX,iY);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSBlock (%d,%d,%d,%d)",m_iLogonID,iBlockID,iX,iY);
	}
}

void CLS_ITSTimeRangePage::OnBnClickedButtonDetectmode()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iDetectMode = m_cboDetectMode.GetCurSel();
	int iRet = NetClient_SetITSDetectMode(m_iLogonID, iDetectMode);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSDetectMode (%d,%d)",m_iLogonID,iDetectMode);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSDetectMode (%d,%d)",m_iLogonID,iDetectMode);
	}
}

void CLS_ITSTimeRangePage::OnBnClickedButtonLoopmode()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iLoopMode = m_cboLoopMode.GetCurSel();
	int iRet = NetClient_SetITSLoopMode(m_iLogonID, iLoopMode);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSLoopMode (%d,%d)",m_iLogonID,iLoopMode);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSLoopMode (%d,%d)",m_iLogonID,iLoopMode);
	}
}

void CLS_ITSTimeRangePage::OnBnClickedButtonDevicetype()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iDeviceType = m_cboDeviceType.GetCurSel();
	int iRet = NetClient_SetITSDeviceType(m_iLogonID, iDeviceType);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSDeviceType (%d,%d)",m_iLogonID,iDeviceType);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSDeviceType (%d,%d)",m_iLogonID,iDeviceType);
	}
}

void CLS_ITSTimeRangePage::OnBnClickedButtonSwitchDelay()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iSwitchTime = GetDlgItemInt(IDC_EDIT_SWITCHTIME);
	int iDelayTime = GetDlgItemInt(IDC_EDIT_DELAYTIME);
	int iRet = NetClient_SetITSSwitchTime(m_iLogonID, iSwitchTime, iDelayTime);
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSSwitchTime (%d,%d,%d)",m_iLogonID,iSwitchTime,iDelayTime);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSSwitchTime (%d,%d,%d)",m_iLogonID,iSwitchTime,iDelayTime);
	}
}

BOOL CLS_ITSTimeRangePage::UI_UpdateGPEGQuality()
{
	if (m_iLogonID < 0)
		return FALSE;

	TCameraParam tCameraParam = {0};
	tCameraParam.iParamType = m_cboCameraParam.GetCurSel();
	int iRet = NetClient_GetCameraParam(m_iLogonID, &tCameraParam,sizeof(tCameraParam));
	if (0 == iRet)
	{
		SetDlgItemInt(IDC_EDIT_VALUE, tCameraParam.iParamValue);
		AddLog(LOG_TYPE_SUCC,"","NetClient_GetCameraParam (%d,%d)",m_iLogonID,sizeof(tCameraParam));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_GetCameraParam (%d,%d)",m_iLogonID,sizeof(tCameraParam));
	}
	return TRUE;
}

void CLS_ITSTimeRangePage::OnCbnSelchangeComboCameraparam()
{
	UI_UpdateGPEGQuality();
}

void CLS_ITSTimeRangePage::OnBnClickedButtonCamera()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	TCameraParam tCameraParam = {0};
	tCameraParam.iParamType = m_cboCameraParam.GetCurSel();
	tCameraParam.iParamValue = GetDlgItemInt(IDC_EDIT_VALUE);
	int iRet = NetClient_SetCameraParam(m_iLogonID, &tCameraParam,sizeof(tCameraParam));
	if (0 == iRet)
	{
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetCameraParam (%d,%d)",m_iLogonID,sizeof(tCameraParam));
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetCameraParam (%d,%d)",m_iLogonID,sizeof(tCameraParam));
	}
}

void CLS_ITSTimeRangePage::UI_UpdateDetectmode()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iDetectMode = 0;
	int iRet = NetClient_GetITSDetectMode(m_iLogonID, &iDetectMode);
	if (0 == iRet)
	{
		m_cboDetectMode.SetCurSel(iDetectMode);
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSDetectMode (%d,%d)",m_iLogonID,iDetectMode);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSDetectMode (%d,%d)",m_iLogonID,iDetectMode);
	}	
}

void CLS_ITSTimeRangePage::UI_UpdateLoopmode()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}		

	int iLoopMode = 0;
	int iRet = NetClient_GetITSLoopMode(m_iLogonID, &iLoopMode);
	if (0 == iRet)
	{
	m_cboLoopMode.SetCurSel(iLoopMode);
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSLoopMode (%d,%d)",m_iLogonID,iLoopMode);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSLoopMode (%d,%d)",m_iLogonID,iLoopMode);
	}	
}

void CLS_ITSTimeRangePage::UI_UpdateDevicetype()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iDeviceType = 0;
	int iRet = NetClient_GetITSDeviceType(m_iLogonID, &iDeviceType);
	if (0 == iRet)
	{
		m_cboDeviceType.SetCurSel(iDeviceType);
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSDeviceType (%d,%d)",m_iLogonID,iDeviceType);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSDeviceType (%d,%d)",m_iLogonID,iDeviceType);
	}
}

void CLS_ITSTimeRangePage::UI_UpdateSwitchDelay()
{
	if (m_iLogonID < 0)
	{
		AddLog(LOG_TYPE_MSG,"","Invalid logon id(%d)",m_iLogonID);
		return;
	}

	int iSwitchTime = 0;
	int iDelayTime = 0;
	int iRet = NetClient_GetITSSwitchTime(m_iLogonID, &iSwitchTime, &iDelayTime);
	if (0 == iRet)
	{
		SetDlgItemInt(IDC_EDIT_SWITCHTIME, iSwitchTime);
		SetDlgItemInt(IDC_EDIT_DELAYTIME, iDelayTime);
		AddLog(LOG_TYPE_SUCC,"","NetClient_SetITSSwitchTime (%d,%d,%d)",m_iLogonID,iSwitchTime,iDelayTime);
	} 
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_SetITSSwitchTime (%d,%d,%d)",m_iLogonID,iSwitchTime,iDelayTime);
	}
}
