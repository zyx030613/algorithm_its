// VCAEVENT_AudioDiagnoseNew.cpp : 实现文件
//

#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAEVENT_FaceRecNew.h"

#define DEFAULT_ZORO			0			//默认值 0
#define SENSITIVITY_MIN			0			//灵敏度最小值
#define SENSITIVITY_MAX			5			//灵敏度最大值
#define AUDIO_DIAGNOSE_RULEID	9			//音频诊断ruleid用9
#define LEN_3					3			//长度为3
#define POINT_NUM_MIN			2			//点数最小值
#define POINT_NUM_MAX			15			//点数最大值
#define SIZE_MIN_VALUE			0			//尺寸最小值
#define SIZE_MAX_VALUE			100			//尺寸最大值
// CLS_VCAEVENT_FaceRecNew 对话框

IMPLEMENT_DYNAMIC(CLS_VCAEVENT_FaceRecNew, CDialog)

CLS_VCAEVENT_FaceRecNew::CLS_VCAEVENT_FaceRecNew(CWnd* pParent /*=NULL*/)
: CLS_VCAEventBasePage(CLS_VCAEVENT_FaceRecNew::IDD, pParent)
{

}

CLS_VCAEVENT_FaceRecNew::~CLS_VCAEVENT_FaceRecNew()
{
}

void CLS_VCAEVENT_FaceRecNew::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHK_FACEREC_NEW_ENABLE, m_chkEnable);
	DDX_Control(pDX, IDC_EDT_FACEREC_NEW_MAX_SIZE, m_edtMaxSize);
	DDX_Control(pDX, IDC_EDT_FACEREC_NEW_MIN_SIZE, m_edtMinSize);
	DDX_Control(pDX, IDC_CBO_FACEREC_NEW_ALGO_LEVEL, m_cboAlgoLevel);
	DDX_Control(pDX, IDC_CBO_FACEREC_NEW_SENSITIVITY, m_cboSensitivity);
	DDX_Control(pDX, IDC_CBO_FACEREC_NEW_PIC_SCAL, m_cboPicScal);
	DDX_Control(pDX, IDC_EDT_FACEREC_NEW_SNAP_SPACE, m_edtSnapSpace);
	DDX_Control(pDX, IDC_CBO_FACEREC_NEW_SNAP_TIMES, m_cboSnapTimes);
	DDX_Control(pDX, IDC_CBO_FACEREC_NEW_POLYGON_POINT_NUM, m_cboPolygonPointNum);
	DDX_Control(pDX, IDC_EDT_FACEREC_NEW_POLYGON_AREA, m_edtPolygonArea);
	DDX_Control(pDX, IDC_SLD_FACEREC_NEW_MAX_SIZE, m_sldMaxSize);
	DDX_Control(pDX, IDC_SLD_FACEREC_NEW_MIN_SIZE, m_sldMinSize);
	DDX_Control(pDX, IDC_CHK_FACEREC_NEW_TARGET_BOX, m_chkTargetBox);
}


BEGIN_MESSAGE_MAP(CLS_VCAEVENT_FaceRecNew, CDialog)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTN_FACEREC_NEW_SET, &CLS_VCAEVENT_FaceRecNew::OnBnClickedBtnFacerecNewSet)
	ON_BN_CLICKED(IDC_BTN_FACEREC_NEW_POLYGON_AREA_DRAW, &CLS_VCAEVENT_FaceRecNew::OnBnClickedBtnFacerecNewPolygonAreaDraw)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLD_FACEREC_NEW_MAX_SIZE, &CLS_VCAEVENT_FaceRecNew::OnNMCustomdrawSldFacerecNewMaxSize)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLD_FACEREC_NEW_MIN_SIZE, &CLS_VCAEVENT_FaceRecNew::OnNMCustomdrawSldFacerecNewMinSize)
END_MESSAGE_MAP()


// CLS_VCAEVENT_FaceRecNew 消息处理程序


BOOL CLS_VCAEVENT_FaceRecNew::OnInitDialog()
{
	CLS_VCAEventBasePage::OnInitDialog();

	UpdateUIText();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CLS_VCAEVENT_FaceRecNew::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_VCAEventBasePage::OnShowWindow(bShow, nStatus);

	if (bShow)
	{
		UpdatePageUI();
	}
}


void CLS_VCAEVENT_FaceRecNew::OnLanguageChanged()
{	
	UpdateUIText();
	UpdatePageUI();
}

void CLS_VCAEVENT_FaceRecNew::UpdateUIText()
{
	SetDlgItemTextEx(IDC_CHK_FACEREC_NEW_ENABLE, IDS_VCA_FACE_SNAPSHOT_ENABLE);
	SetDlgItemTextEx(IDC_STC_FACEREC_NEW_MAX_SIZE, IDS_VCAEVENT_MAX_FACE_SIZE);
	SetDlgItemTextEx(IDC_STC_FACEREC_NEW_MIN_SIZE, IDS_VCAEVENT_MIN_FACE_SIZE);
	SetDlgItemTextEx(IDC_STC_FACEREC_NEW_ALGO_LEVEL, IDS_VCAEVENT_ALGO_RUN_LEVEL);
	SetDlgItemTextEx(IDC_STC_FACEREC_NEW_SENSITIVITY, IDS_CONFIG_ITS_ILLEGALPARK_SENSITIVITY);
	SetDlgItemTextEx(IDC_STC_FACEREC_NEW_PIC_SCAL, IDS_VCAEVENT_PICTURE_SCALING);
	SetDlgItemTextEx(IDC_STC_FACEREC_NEW_SNAP_SPACE, IDS_CONFIG_FTP_INTERVAL);
	SetDlgItemTextEx(IDC_STC_FACEREC_NEW_SNAP_TIMES, IDS_VCAEVENT_SNAP_TIMES);
	SetDlgItemTextEx(IDC_STC_FACEREC_NEW_POLYGON_POINT_NUM, IDS_VCAEVENT_POLYGON_POINT_NUM);
	SetDlgItemTextEx(IDC_STC_FACEREC_NEW_POLYGON_AREA, IDS_VCAEVENT_POLYGON);
	SetDlgItemTextEx(IDC_BTN_FACEREC_NEW_POLYGON_AREA_DRAW, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_BTN_FACEREC_NEW_SET, IDS_SET);
	SetDlgItemTextEx(IDC_CHK_FACEREC_NEW_TARGET_BOX, IDS_VCAEVENT_SHOW_TARGET_BOX);

	m_cboAlgoLevel.ResetContent();
	const CString cstLevel[] = {"0","1","2","3","4","5"};
	for (int i = 0; i < sizeof(cstLevel)/sizeof(CString); i++)
	{
		m_cboAlgoLevel.InsertString(i, cstLevel[i]);
	}
	m_cboAlgoLevel.SetCurSel(0);

	m_cboSensitivity.ResetContent();
	const CString cstSens[] = {"0","1","2","3","4","5"};
	for (int i = 0; i < sizeof(cstSens)/sizeof(CString); i++)
	{
		m_cboSensitivity.InsertString(i, cstSens[i]);
	}
	m_cboSensitivity.SetCurSel(0);

	m_cboSnapTimes.ResetContent();
	const CString cstSnapTimes[] = {"1","2","3","4","5","6","7","8"};
	for (int i = 0; i < sizeof(cstSnapTimes)/sizeof(CString); i++)
	{
		m_cboSnapTimes.InsertString(i, cstSnapTimes[i]);
	}
	m_cboSnapTimes.SetCurSel(0);

	m_cboPicScal.ResetContent();
	const CString cstPicScal[] = {"1","2","3","4","5","6","7","8","9","10"};
	for (int i = 0; i < sizeof(cstPicScal)/sizeof(CString); i++)
	{
		m_cboPicScal.InsertString(i, cstPicScal[i]);
	}
	m_cboPicScal.SetCurSel(0);

	CString cstTemp = "";
	m_cboPolygonPointNum.ResetContent();
	for (int i = (POINT_NUM_MIN - 2); i <= (POINT_NUM_MAX - 2); i++)
	{	
		cstTemp.Format("%d",i + 2);
		m_cboPolygonPointNum.InsertString(i, cstTemp);
	}
	m_cboPolygonPointNum.SetCurSel(0);

	m_edtMaxSize.SetLimitText(LEN_3);
	m_edtMinSize.SetLimitText(LEN_3);
	m_edtSnapSpace.SetLimitText(LEN_32 - 1);

	m_sldMaxSize.SetRange(SIZE_MIN_VALUE + 1, SIZE_MAX_VALUE);
	m_sldMaxSize.SetPos(DEFAULT_ZORO + 1);
	SetDlgItemInt(IDC_STC_FACEREC_NEW_MAX_SIZE_NUM, m_sldMaxSize.GetPos());

	m_sldMinSize.SetRange(SIZE_MIN_VALUE, SIZE_MAX_VALUE - 1);
	m_sldMinSize.SetPos(DEFAULT_ZORO);
	SetDlgItemInt(IDC_STC_FACEREC_NEW_MIN_SIZE_NUM, m_sldMinSize.GetPos());	
}

void CLS_VCAEVENT_FaceRecNew::UpdatePageUI()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_FaceRecNew::Invalid Logon id or Channel number(%d,%d)", m_iLogonID,m_iChannelNO);
		return;
	}

	FaceDetectArithmetic fda = {0};
	fda.iSceneID = m_iSceneID;

	int iByteReturn = 0;
	int iRet = NetClient_GetDevConfig(m_iLogonID, NET_CLIENT_FACE_DETECT_ARITHMETIC, m_iChannelNO, &fda, sizeof(FaceDetectArithmetic), &iByteReturn);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCAEVENT_FaceRecNew::NetClient_GetDevConfig[NET_CLIENT_FACE_DETECT_ARITHMETIC] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
	else
	{
		m_chkEnable.SetCheck(fda.iSnapEnable);
		m_chkTargetBox.SetCheck(fda.iDisplayTarget);

		m_cboAlgoLevel.SetCurSel(fda.iLevel);
		m_cboPicScal.SetCurSel(fda.iPicScale - 1);
		m_cboPolygonPointNum.SetCurSel(fda.iPointNum - 2);
		m_cboSensitivity.SetCurSel(fda.iSensitiv);
		m_cboSnapTimes.SetCurSel(fda.iSnapTimes - 1);

		m_sldMaxSize.SetPos(fda.iMaxSize);
		SetDlgItemInt(IDC_STC_FACEREC_NEW_MAX_SIZE_NUM, m_sldMaxSize.GetPos());
		m_sldMinSize.SetPos(fda.iMinSize);
		SetDlgItemInt(IDC_STC_FACEREC_NEW_MIN_SIZE_NUM, m_sldMinSize.GetPos());

		SetDlgItemInt(IDC_EDT_FACEREC_NEW_SNAP_SPACE, fda.iSnapSpace);

		CString cstPolygonBuf = "";
		int iPointNum = fda.iPointNum;
		if ((iPointNum >= POINT_NUM_MIN) && (iPointNum <= POINT_NUM_MAX))
		{
			for(int i = 0; i < iPointNum; i++)
			{
				cstPolygonBuf.AppendFormat("(%d, %d)", fda.ptArea[i].x, fda.ptArea[i].y);
			}
			SetDlgItemText(IDC_EDT_FACEREC_NEW_POLYGON_AREA, cstPolygonBuf);
		}

		AddLog(LOG_TYPE_SUCC,"","CLS_VCAEVENT_FaceRecNew::NetClient_GetDevConfig[NET_CLIENT_FACE_DETECT_ARITHMETIC] (%d, %d)", m_iLogonID, m_iChannelNO);
	}
} 

void CLS_VCAEVENT_FaceRecNew::OnBnClickedBtnFacerecNewSet()
{
	if (m_iLogonID == -1 || m_iChannelNO == -1)
	{
		AddLog(LOG_TYPE_MSG, "", "CLS_VCAEVENT_FaceRecNew::Invalid Logon id or Channel number(%d,%d)", m_iLogonID,m_iChannelNO);
		return;
	}

	FaceDetectArithmetic fda = {0};

	fda.iBufSize = sizeof(FaceDetectArithmetic);
	fda.iDisplayTarget = m_chkEnable.GetCheck();
	fda.iLevel = m_cboAlgoLevel.GetCurSel();
	fda.iMaxSize = m_sldMaxSize.GetPos();
	fda.iMinSize = m_sldMinSize.GetPos();
	fda.iPicScale = m_cboPicScal.GetCurSel() + 1;
	fda.iPointNum = m_cboPolygonPointNum.GetCurSel() + 2;
	fda.iSceneID = m_iSceneID;
	fda.iSensitiv = m_cboSensitivity.GetCurSel();
	fda.iSnapEnable = m_chkTargetBox.GetCheck();
	fda.iSnapSpace = GetDlgItemInt(IDC_EDT_FACEREC_NEW_SNAP_SPACE);
	fda.iSnapTimes = m_cboSnapTimes.GetCurSel() + 1;
	
	POINT ptPolygon[MAX_FACE_DETECT_AREA_COUNT] = {0} ;
	CString cstPolygon = "";
	GetDlgItemText(IDC_EDT_FACEREC_NEW_POLYGON_AREA, cstPolygon);
	GetPointsFromString(cstPolygon, fda.iPointNum, ptPolygon);
	for (int i = 0; i < fda.iPointNum; i++)
	{
		fda.ptArea[i] = ptPolygon[i];
	}

	int iRet = NetClient_SetDevConfig(m_iLogonID, NET_CLIENT_FACE_DETECT_ARITHMETIC, m_iChannelNO, &fda, sizeof(FaceDetectArithmetic));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL,"","CLS_VCAEVENT_FaceRecNew::NetClient_SetDevConfig[NET_CLIENT_FACE_DETECT_ARITHMETIC] (%d, %d), error(%d)", m_iLogonID, m_iChannelNO, GetLastError());
	}
	else
	{
		AddLog(LOG_TYPE_SUCC,"","CLS_VCAEVENT_FaceRecNew::NetClient_SetDevConfig[NET_CLIENT_FACE_DETECT_ARITHMETIC] (%d, %d)", m_iLogonID, m_iChannelNO);
	}
}

void CLS_VCAEVENT_FaceRecNew::OnBnClickedBtnFacerecNewPolygonAreaDraw()
{
	if (NULL == m_pDlgVideoView)
	{
		m_pDlgVideoView = new CLS_VideoViewForDraw();
		if (NULL == m_pDlgVideoView)
		{
			return ;
		}
	}

	m_pDlgVideoView->Init(m_iLogonID, m_iChannelNO, m_iStreamNO);
	m_pDlgVideoView->SetDrawType(DrawType_perimeter);
	int iPointNum = 0;
	int iDirection = 0;
	char cPointBuf[MAX_POINTBUF_LEN] = {0};
	int iSetRet = m_pDlgVideoView->SetPointRegionParam(cPointBuf, &iPointNum, &iDirection);
	if (-1 == iSetRet)
	{
		delete m_pDlgVideoView;
		m_pDlgVideoView = NULL;
		return ;
	}
	if (IDOK == m_pDlgVideoView->DoModal())
	{
		if (iPointNum > 1)
		{
			m_edtPolygonArea.SetWindowText(cPointBuf);
			m_cboPolygonPointNum.SetCurSel(iPointNum - 2);
		}
		else
		{
			m_edtPolygonArea.SetWindowText(_T(""));
			m_cboPolygonPointNum.SetCurSel(-1);
		}
	}
	else
	{
		// TODO: Nothing
	}
	delete m_pDlgVideoView;
	m_pDlgVideoView = NULL;
}

void CLS_VCAEVENT_FaceRecNew::OnNMCustomdrawSldFacerecNewMaxSize(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	int iMinSize = m_sldMinSize.GetPos();
	int iMaxSize = m_sldMaxSize.GetPos();
	SetDlgItemInt(IDC_STC_FACEREC_NEW_MAX_SIZE_NUM, iMaxSize);
	if (iMinSize >= iMaxSize)
	{
		m_sldMinSize.SetPos(iMaxSize - 1);
		SetDlgItemInt(IDC_STC_FACEREC_NEW_MIN_SIZE_NUM, m_sldMinSize.GetPos());
	}

	*pResult = 0;
}

void CLS_VCAEVENT_FaceRecNew::OnNMCustomdrawSldFacerecNewMinSize(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	int iMinSize = m_sldMinSize.GetPos();
	int iMaxSize = m_sldMaxSize.GetPos();
	SetDlgItemInt(IDC_STC_FACEREC_NEW_MIN_SIZE_NUM, iMinSize);
	if (iMaxSize <= iMinSize)
	{
		m_sldMaxSize.SetPos(iMinSize + 1);
		SetDlgItemInt(IDC_STC_FACEREC_NEW_MAX_SIZE_NUM, m_sldMaxSize.GetPos());
	}

	*pResult = 0;
}
