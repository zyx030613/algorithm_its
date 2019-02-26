// VideoInterested.cpp : implementation file
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "VideoInterested.h"


// CCLS_VideoInterested dialog

IMPLEMENT_DYNAMIC(CLS_VideoInterested, CDialog)

CLS_VideoInterested::CLS_VideoInterested(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_VideoInterested::IDD, pParent)
{
	m_iLogonID = -1;
	m_iChannelNo = 0;
	m_iStreamNO = 0;
	m_pDlgVideoView = NULL;
	m_iLeft = 0;
	m_iTop = 0;
	m_iRight = 0;
	m_iBottom = 0;
	memset(&m_tCurrentInterestRect, 0, sizeof(TInterestedArea));
}

CLS_VideoInterested::~CLS_VideoInterested()
{
	if (m_pDlgVideoView)
	{
		m_pDlgVideoView->DestroyWindow();
		delete m_pDlgVideoView;
		m_pDlgVideoView = NULL;
	}
}

void CLS_VideoInterested::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_AREA_INDEX, m_cboAreaIndex);
	DDX_Control(pDX, IDC_COMBO_AREA_ENABLE, m_cboAreaEnable);
	DDX_Control(pDX, IDC_COMBO_QP_TYPE, m_cboQpType);
	DDX_Control(pDX, IDC_EDIT_QP_VALUE, m_edtQpValue);
	DDX_Control(pDX, IDC_EDIT_Points, m_edtDarwPoint);
}

BEGIN_MESSAGE_MAP(CLS_VideoInterested, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_Draw, &CLS_VideoInterested::OnBnClickedButtonDraw)
	ON_BN_CLICKED(IDC_BUTTON_VIDEO_INTERESTED_SET, &CLS_VideoInterested::OnBnClickedButtonVideoInterestedSet)
	ON_CBN_SELCHANGE(IDC_COMBO_AREA_INDEX, &CLS_VideoInterested::OnCbnSelchangeComboAreaIndex)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CCLS_VideoInterested message handlers

BOOL CLS_VideoInterested::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	// TODO:  Add extra initialization here
	UI_UpdateDialog();

	m_edtQpValue.SetLimitText(16);
	m_edtDarwPoint.SetLimitText(16);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLS_VideoInterested::OnChannelChanged( int _iLogonID,int _iChannelNo,int _iStreamNo )
{
	m_iLogonID = _iLogonID;

	if (_iChannelNo < 0)
	{
		m_iChannelNo = 0;
	}
	else
	{
		m_iChannelNo = _iChannelNo + (_iChannelNo + 1) * _iStreamNo;
	}

	if (_iStreamNo < 0)
	{
		m_iStreamNO = 0;
	}
	else
	{
		m_iStreamNO =  _iStreamNo;
	}
}

void CLS_VideoInterested::OnLanguageChanged( int _iLanguage )
{
	UI_UpdateDialog();
}

void CLS_VideoInterested::OnBnClickedButtonDraw()
{
	// TODO: Add your control notification handler code here
	if (NULL == m_pDlgVideoView)
	{
		m_pDlgVideoView = new CLS_VideoViewForDraw();
		if (NULL == m_pDlgVideoView)
		{
			return;
		}
	}
	/*以下代码为了能从draw对话框中取出相应参数*/
	m_pDlgVideoView->Init(m_iLogonID, m_iChannelNo, m_iStreamNO);
	m_pDlgVideoView->SetDrawType(DrawType_Crowd);
	int iPointNum = 0;
	int iDirection = 0;
	char cPointBuf[MAX_POINTBUF_LEN] = {0};
	/***************************************************************************/
	//解决 视频框显示时没有划线的问题 20161129
	RECT tTemp = {0};
	tTemp.left = m_tCurrentInterestRect.iLeft;
	tTemp.top = m_tCurrentInterestRect.iTop;
	tTemp.right = m_tCurrentInterestRect.iRight;
	tTemp.bottom = m_tCurrentInterestRect.iBottom;
	m_pDlgVideoView->InitCrowdRect(tTemp);
	/***************************************************************************/
	int iSetRet = m_pDlgVideoView->SetPointRegionParam(cPointBuf, &iPointNum, &iDirection);
	if (-1 == iSetRet)
	{
		goto EXIT_FUNC;
	}

	if (IDOK == m_pDlgVideoView->DoModal())
	{
		m_edtDarwPoint.SetWindowText(cPointBuf);
		m_pDlgVideoView->GetPointCoordirate(&m_iLeft, &m_iTop, &m_iRight, &m_iBottom);
	}
	else
	{
		// TODO: Nothing
	}

EXIT_FUNC:
	delete m_pDlgVideoView;
	m_pDlgVideoView = NULL;
}

void CLS_VideoInterested::OnBnClickedButtonVideoInterestedSet()
{
	// TODO: Add your control notification handler code here
	if (m_iLogonID == -1 || m_iChannelNo == -1)
	{
		return;
	}

	TInterestedArea strInterestedArea = {0};
	strInterestedArea.iSize = sizeof(TInterestedArea);
	strInterestedArea.iIndex = (int)m_cboAreaIndex.GetItemData(m_cboAreaIndex.GetCurSel());
	strInterestedArea.iEnable = m_cboAreaEnable.GetCurSel();
	strInterestedArea.iAbsQp = m_cboQpType.GetCurSel();
	strInterestedArea.iQp = GetDlgItemInt(IDC_EDIT_QP_VALUE);
	strInterestedArea.iLeft = m_iLeft;
	strInterestedArea.iTop = m_iTop;
	strInterestedArea.iRight = m_iRight;
	strInterestedArea.iBottom = m_iBottom;

	int iFrameRate = 0;
	if (0 == NetClient_GetFrameRate(m_iLogonID, m_iChannelNo, &iFrameRate, m_iStreamNO))
	{
		strInterestedArea.iDstFrameRate = iFrameRate;
	}

	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_INTERESTED_AREA, m_iChannelNo, &strInterestedArea, sizeof(TInterestedArea));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_VideoInterested::OnBnClickedButtonVideoInterestedSet] Set fail,error = %d", GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC, "", "[CLS_VideoInterested::OnBnClickedButtonVideoInterestedSet] set success!");
	}
}

void CLS_VideoInterested::UpdatePageUI()
{
	if (m_iLogonID == -1 || m_iChannelNo == -1)
	{
		return;
	}

	TInterestedArea strInterestedArea = {0};
	strInterestedArea.iSize = sizeof(TInterestedArea);
	int iBytesReturned = 0;
	int iAreaIndex = (int)m_cboAreaIndex.GetItemData(m_cboAreaIndex.GetCurSel());
	strInterestedArea.iIndex = iAreaIndex;

	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_INTERESTED_AREA, m_iChannelNo, &strInterestedArea, sizeof(TInterestedArea), &iBytesReturned);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "[CLS_VideoInterested::OnBnClickedButtonVideoInterestedSet] Set fail,error = %d", GetLastError());
	}
	else
	{
		m_tCurrentInterestRect = strInterestedArea;
		m_cboAreaEnable.SetCurSel(strInterestedArea.iEnable);
		m_cboQpType.SetCurSel(strInterestedArea.iAbsQp);
		SetDlgItemInt(IDC_EDIT_QP_VALUE, strInterestedArea.iQp);
		CString strPointArray;
		CString strPoint[4];
		strPoint[0].Format("(%d,%d)", strInterestedArea.iLeft, strInterestedArea.iTop);
		strPoint[1].Format("(%d,%d)", strInterestedArea.iRight, strInterestedArea.iTop);
		strPoint[2].Format("(%d,%d)", strInterestedArea.iRight, strInterestedArea.iBottom);
		strPoint[3].Format("(%d,%d)", strInterestedArea.iLeft, strInterestedArea.iBottom);
		strPointArray = strPoint[0]+strPoint[1]+strPoint[2]+strPoint[3];
		m_edtDarwPoint.SetWindowText(strPointArray);
	}
}

void CLS_VideoInterested::OnParamChangeNotify(int _iLogonID, int _iChannelNo, int _iParaType,void* _pPara,int _iUserData)
{
	int iMsgType = LOWORD(_iParaType);
	switch(iMsgType)
	{
	case PARA_INTERESTED_AREA:
		UpdatePageUI();
		break;
	default:
		break;
	}
}

void CLS_VideoInterested::UI_UpdateDialog()
{
	//InsertString(m_cboEncryptType,0,IDS_CFG_VIDEO_ENCRYPT_ENCRYPT_TYPE_NONE);
	//InsertString(m_cboEncryptType,1,IDS_CFG_VIDEO_ENCRYPT_ENCRYPT_TYPE_AES);

	m_cboAreaIndex.ResetContent();
	m_cboAreaIndex.SetItemData(m_cboAreaIndex.AddString(_T("Area1")), 0);
	m_cboAreaIndex.SetItemData(m_cboAreaIndex.AddString(_T("Area2")), 1);
	m_cboAreaIndex.SetItemData(m_cboAreaIndex.AddString(_T("Area3")), 2);
	m_cboAreaIndex.SetItemData(m_cboAreaIndex.AddString(_T("Area4")), 3);
	m_cboAreaIndex.SetItemData(m_cboAreaIndex.AddString(_T("Area5")), 4);
	m_cboAreaIndex.SetItemData(m_cboAreaIndex.AddString(_T("Area6")), 5);
	m_cboAreaIndex.SetItemData(m_cboAreaIndex.AddString(_T("Area7")), 6);
	m_cboAreaIndex.SetItemData(m_cboAreaIndex.AddString(_T("Area8")), 7);
	m_cboAreaIndex.SetCurSel(0);

	m_cboAreaEnable.ResetContent();
	m_cboAreaEnable.AddString(GetTextEx(IDS_CONFIG_FTP_SNAPSHOT_DISABLE));
	m_cboAreaEnable.AddString(GetTextEx(IDS_CONFIG_ECOP_IMGDISPOSAL_ENABLE));
	m_cboAreaEnable.SetCurSel(0);

	m_cboQpType.ResetContent();
	m_cboQpType.AddString(GetTextEx(IDS_CFG_VIDEO_QPTYPE_REL));
	m_cboQpType.AddString(GetTextEx(IDS_CFG_VIDEO_QPTYPE_ABS));
	m_cboQpType.SetCurSel(0);

	SetDlgItemTextEx(IDC_STATIC_INTERESTED_AREA, IDS_CFG_VIDEO_INTERESTED);
	SetDlgItemTextEx(IDC_STATIC_INTERESTED_VIDEO, IDS_CONFIG_ECOP_IMGDISPOSAL_ENABLE);
	SetDlgItemTextEx(IDC_STATIC_QP_TYPE, IDS_CFG_VIDEO_QPTYPE);
	SetDlgItemTextEx(IDC_STATIC_QP_VALUE, IDS_CFG_VIDEO_QPVALUE);
	SetDlgItemTextEx(IDC_BUTTON_VIDEO_INTERESTED_SET, IDS_SET);
}

void CLS_VideoInterested::OnCbnSelchangeComboAreaIndex()
{
	// TODO: Add your control notification handler code here
	UpdatePageUI();
}

void CLS_VideoInterested::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);

	UpdatePageUI();
}

//解决子界面无法连接视频的Bug 20161229
void CLS_VideoInterested::OnMainNotify( int _iLogonID,int _wParam, void* _lParam, void*_iUserData )
{
	if (_iLogonID != m_iLogonID)
	{
		return;
	}

	if (NULL != m_pDlgVideoView)
	{
		m_pDlgVideoView->OnMainNotify(_iLogonID, _wParam, _lParam, _iUserData);
	}
}
