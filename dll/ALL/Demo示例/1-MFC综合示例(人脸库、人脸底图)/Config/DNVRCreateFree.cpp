#include "stdafx.h"
#include "DNVRCreateFree.h"

IMPLEMENT_DYNAMIC(CLS_DNVRCreateFree, CDialog)
#define		MAX_COORS_SCALE		10000
#define		MIN_VIDEO_SIZE		32	

CLS_DNVRCreateFree::CLS_DNVRCreateFree(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DNVRCreateFree::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
	m_iStreamNo = 0;
	memset(&m_stViewSegInfo,0,sizeof(m_stViewSegInfo));
}

CLS_DNVRCreateFree::~CLS_DNVRCreateFree()
{
}

void CLS_DNVRCreateFree::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);	
	DDX_Control(pDX, IDC_COMBO_PIC_COUNT, m_cboPicCount);
	DDX_Control(pDX, IDC_COMBO_OUTPUT_DEVICE_ID, m_cboDevideId);
	for (int i=0; i<MAX_PIC_NUM; i++)
	{
		DDX_Control(pDX, IDC_COMBO_CHAN_NO1 + i, m_cboChanNo[i]);
		DDX_Control(pDX, IDC_EDIT_COORDS_X1 + i, m_edtCoordsX[i]);
		DDX_Control(pDX, IDC_EDIT_COORDS_Y1 + i, m_edtCoordsY[i]);
		DDX_Control(pDX, IDC_EDIT_WIDTH1 + i, m_edtWidth[i]);
		DDX_Control(pDX, IDC_EDIT_HEIGHT1 + i, m_edtHeight[i]);
	}
}

BEGIN_MESSAGE_MAP(CLS_DNVRCreateFree, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_PIC_COUNT, &CLS_DNVRCreateFree::OnCbnSelchangeComboPicCount)
	ON_CONTROL_RANGE(CBN_SELCHANGE,IDC_COMBO_CHAN_NO1,IDC_COMBO_CHAN_NO9,&CLS_DNVRCreateFree::OnCbnSelchangeComboChanNo)
	ON_BN_CLICKED(IDC_BUTTON_CREATEFREE_SET_ALL, &CLS_DNVRCreateFree::OnBnClickedButtonCreatefreeSetAll)
	ON_BN_CLICKED(IDC_BUTTON1_GETPARAM, &CLS_DNVRCreateFree::OnBnClickedButton1Getparam)
	ON_CONTROL_RANGE(EN_CHANGE,IDC_EDIT_COORDS_X1,IDC_EDIT_COORDS_X9,&CLS_DNVRCreateFree::OnEdtCheckLegal)
	ON_CONTROL_RANGE(EN_CHANGE,IDC_EDIT_COORDS_Y1,IDC_EDIT_COORDS_Y9,&CLS_DNVRCreateFree::OnEdtCheckLegal)
	ON_CONTROL_RANGE(EN_CHANGE,IDC_EDIT_WIDTH1,IDC_EDIT_WIDTH9,&CLS_DNVRCreateFree::OnEdtCheckLegal)
	ON_CONTROL_RANGE(EN_CHANGE,IDC_EDIT_HEIGHT1,IDC_EDIT_HEIGHT9,&CLS_DNVRCreateFree::OnEdtCheckLegal)
	ON_CBN_SELCHANGE(IDC_COMBO_OUTPUT_DEVICE_ID, &CLS_DNVRCreateFree::OnCbnSelchangeComboOutputDeviceId)
END_MESSAGE_MAP()

BOOL CLS_DNVRCreateFree::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	UI_UpdateDialog();

	return TRUE;
}

void CLS_DNVRCreateFree::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo)
{
	m_iLogonID = _iLogonID;
	m_iChannelNo = _iChannelNo<0?0:_iChannelNo;
	m_iStreamNo = _iStreamNo<0?0:_iStreamNo;
}

void CLS_DNVRCreateFree::OnLanguageChanged( int _iLanguage)
{
	UI_UpdateDialog();
}

void CLS_DNVRCreateFree::UI_UpdateDialog()
{
	SetDlgItemTextEx(IDC_STATIC_OUTPUT_DEVICE_ID,IDS_PLAYBACK_DEVICE_ID);
	SetDlgItemTextEx(IDC_STATIC_PIC_COUNT,IDS_CONFIG_PIC_COUNT);
	SetDlgItemTextEx(IDC_STATIC_CHAN_NO,IDS_CONFIG_DNVR_ALMSCH_CHANNELNO);
	SetDlgItemTextEx(IDC_STATIC_COORDS_X,IDS_CONFIG_COORDS_X);
	SetDlgItemTextEx(IDC_STATIC_COORDS_Y,IDS_CONFIG_COORDS_Y);
	SetDlgItemTextEx(IDC_STATIC_WIDTH,IDS_CONFIG_WIDTH);
	SetDlgItemTextEx(IDC_STATIC_HEIGHT,IDS_CONFIG_HEIGHT);
	SetDlgItemTextEx(IDC_BUTTON_CREATEFREE_SET_ALL,IDS_SET);
	SetDlgItemTextEx(IDC_BUTTON1_GETPARAM,IDS_CFG_LOG_NVS_REFRESH);

	m_cboDevideId.InsertString(0, "VGA/HDMI0");
	m_cboDevideId.InsertString(1, "HDMI1");
	m_cboDevideId.InsertString(2, "VC");
	m_cboDevideId.SetCurSel(0);
	for (int i=0; i<MAX_PIC_NUM; i++)
	{
		m_cboPicCount.InsertString(i, IntToCString(i+1));
		for (int j=0; j<MAX_VIEW_NUM; j++)
		{
			m_cboChanNo[i].InsertString(j, IntToCString(j+1));
		}
		m_cboChanNo[i].SetCurSel(i);

		m_edtCoordsX[i].SetLimitText(5);
		m_edtCoordsY[i].SetLimitText(5);
		m_edtWidth[i].SetLimitText(5);
		m_edtHeight[i].SetLimitText(5);
	}
	m_cboPicCount.SetCurSel(0);
	SetWidgetEnable(0);
}

void CLS_DNVRCreateFree::SetWidgetEnable(int _iPicNo)
{
	BOOL bEnable = TRUE;
	for (int i=0; i<MAX_PIC_NUM; i++)
	{
		if (i > _iPicNo)
		{
			bEnable = FALSE;
		}
		m_cboChanNo[i].EnableWindow(bEnable);
		m_edtCoordsX[i].EnableWindow(bEnable);
		m_edtCoordsY[i].EnableWindow(bEnable);
		m_edtWidth[i].EnableWindow(bEnable);
		m_edtHeight[i].EnableWindow(bEnable);
	}
}

void CLS_DNVRCreateFree::OnCbnSelchangeComboPicCount()
{
	SetWidgetEnable(m_cboPicCount.GetCurSel());
}

void CLS_DNVRCreateFree::OnMainNotify( int _ulLogonID,int _iWparam, void* _iLParam, void* _iUser)
{
	switch(_iWparam)
	{
	case WCM_GET_CREATEFREEVO:
		{
			VoViewSegment* tParam = (VoViewSegment*)_iLParam;
			if (NULL == tParam)
			{
				return;
			}
			memcpy(&m_stViewSegInfo[tParam->iVoDevId], tParam, sizeof(VoViewSegment));
			if (m_cboDevideId.GetCurSel() == tParam->iVoDevId -1)
			{
				OnCbnSelchangeComboOutputDeviceId();
			}
		}
		break;
	default:
		break;
	}
}

void CLS_DNVRCreateFree::OnCbnSelchangeComboOutputDeviceId()
{
	int iVoDevId = m_cboDevideId.GetCurSel() + 1;
	VoViewSegment tParam = m_stViewSegInfo[iVoDevId];
	int iPicCnt = tParam.iPicCnt;
	iPicCnt = (iPicCnt==0)?1:iPicCnt;
	m_cboPicCount.SetCurSel(iPicCnt-1);
	SetWidgetEnable(iPicCnt-1);
	for (int i=0; i<tParam.iPicCnt; i++)
	{
		m_cboChanNo[i].SetCurSel(tParam.tPicPar[i].ChnNo);
		SetDlgItemInt(IDC_EDIT_COORDS_X1 + i, tParam.tPicPar[i].RectParam.iX);
		SetDlgItemInt(IDC_EDIT_COORDS_Y1 + i, tParam.tPicPar[i].RectParam.iY);
		SetDlgItemInt(IDC_EDIT_WIDTH1 + i, tParam.tPicPar[i].RectParam.iWidth);
		SetDlgItemInt(IDC_EDIT_HEIGHT1 + i, tParam.tPicPar[i].RectParam.iHeight);
	}
}

void CLS_DNVRCreateFree::OnBnClickedButton1Getparam()
{
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_CREATEFREEVO, m_iChannelNo, &m_iChannelNo, sizeof(m_iChannelNo));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig(%d,%d)",m_iLogonID, NET_CLIENT_CREATEFREEVO);
	}
}

void CLS_DNVRCreateFree::OnBnClickedButtonCreatefreeSetAll()
{
	//设备分辨率大小
	int iVWidth = 1500;
	int iVHeight = 1150;
	
	int iBegX[MAX_PIC_NUM] = {0};
	int iBegY[MAX_PIC_NUM] = {0};
	int iEndX[MAX_PIC_NUM] = {0};
	int iEndY[MAX_PIC_NUM] = {0};

	VoViewSegment tParam = {0};
	tParam.iSize = sizeof(tParam);
	tParam.iVoDevId = m_cboDevideId.GetCurSel() + 1;
	tParam.iPicCnt = m_cboPicCount.GetCurSel() + 1;
	for (int i = 0; i<tParam.iPicCnt; i++)
	{
		CString cstrTmp = "";
		if (-1 == m_cboChanNo[i].GetCurSel())
		{
			MessageBox("请选择通道号!","提示",MB_OK|MB_TOPMOST);
			m_cboChanNo[i].SetFocus();
			return;
		}
		iBegX[i] = GetDlgItemInt(IDC_EDIT_COORDS_X1 + i);
		int	iWidth = GetDlgItemInt(IDC_EDIT_WIDTH1 + i);
		iEndX[i] = iBegX[i] + iWidth;
		if(MAX_COORS_SCALE < iEndX[i])
		{
			cstrTmp.Format("多画面%d横坐标、宽度的和大于10000，请重新设置!", i+1);
			MessageBox(cstrTmp,"提示",MB_OK|MB_TOPMOST);
			m_edtCoordsX[i].SetFocus();
			return;
		}
		if (iWidth < iVWidth)
		{
			cstrTmp.Format("多画面%d宽度不能小于%d，请重新设置!", i+1, iVWidth);
			MessageBox(cstrTmp,"提示",MB_OK|MB_TOPMOST);
			m_edtWidth[i].SetFocus();
			return;
		}
		iBegY[i] = GetDlgItemInt(IDC_EDIT_COORDS_Y1 + i);
		int iHeight = GetDlgItemInt(IDC_EDIT_HEIGHT1 + i);
		iEndY[i] = iBegY[i] + iHeight;
		if(MAX_COORS_SCALE < iEndY[i])
		{
			cstrTmp.Format("多画面%d纵坐标、高度的和大于10000，请重新设置!", i+1);
			MessageBox(cstrTmp,"提示",MB_OK|MB_TOPMOST);
			m_edtCoordsY[i].SetFocus();
			return;
		}
		if (iHeight < iVHeight)
		{
			cstrTmp.Format("多画面%d高度不能小于%d，请重新设置!", i+1, iVHeight);
			MessageBox(cstrTmp,"提示",MB_OK|MB_TOPMOST);
			m_edtHeight[i].SetFocus();
			return;
		}

		if (0 != i)
		{
			for (int j=i-1; j>=0; j--)
			{
				if ((iBegX[i] >= iEndX[j] || iBegX[j] >= iBegX[i]) || (iBegY[i] >= iEndY[j] || iBegY[j] >= iBegY[i]))
				{
					//do nothing 画面不重叠情况
				}
				else
				{
					cstrTmp.Format("多画面%d和多画面%d有重叠区域，请重新设置!", j+1, i+1);
					MessageBox(cstrTmp,"提示",MB_OK|MB_TOPMOST);
					return;
				}
			}
		}

		tParam.tPicPar[i].ChnNo = m_cboChanNo[i].GetCurSel();
		tParam.tPicPar[i].RectParam.iX = GetDlgItemInt(IDC_EDIT_COORDS_X1 + i);
		tParam.tPicPar[i].RectParam.iY = GetDlgItemInt(IDC_EDIT_COORDS_Y1 + i);
		tParam.tPicPar[i].RectParam.iWidth = GetDlgItemInt(IDC_EDIT_WIDTH1 + i);
		tParam.tPicPar[i].RectParam.iHeight = GetDlgItemInt(IDC_EDIT_HEIGHT1 + i);
	}
	// 发送协议
	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_CREATEFREEV, m_iChannelNo, &tParam, sizeof(tParam));
	if (0 != iRet)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetDevConfig(%d,%d,%d)",m_iLogonID, NET_CLIENT_CREATEFREEV, m_iChannelNo);
	}	
}

void CLS_DNVRCreateFree::OnCbnSelchangeComboChanNo(UINT _ID)
{
	int iRepeatNum = 0;
	int iIndex = _ID - IDC_COMBO_CHAN_NO1;
	int iCurrentSel = m_cboChanNo[iIndex].GetCurSel();
	for (int i=0; i<MAX_PIC_NUM; i++)
	{
		if (i == iIndex)
		{
			continue;
		}

		if (iCurrentSel == m_cboChanNo[i].GetCurSel())
		{
			iRepeatNum++;
		}

		if (2 == iRepeatNum)
		{
			m_cboChanNo[iIndex].SetCurSel(-1);
		}
	}
}

void CLS_DNVRCreateFree::OnEdtCheckLegal(UINT _ID)
{
	int iTmp = GetDlgItemInt(_ID);
	CString cstr = ""; 
	GetDlgItemText(_ID,cstr);
	int len = (int)strlen(cstr);
	if (MAX_COORS_SCALE < GetDlgItemInt(_ID))
	{
		cstr = cstr.Left(len - 1);
		SetDlgItemInt(_ID, _ttoi(cstr));
	}

	if ("0" == cstr.Left(1) && 1 != len)
	{
		cstr = cstr.Right(len - 1);
		SetDlgItemInt(_ID, _ttoi(cstr));
	}
}
