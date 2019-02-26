
#include "stdafx.h"
#include "NetClientDemo.h"
#include "VCAEVENT_Lisence.h"


// CLS_VCAEVENT_Lisence 对话框
const CString CONST_cstrProvince[] ={
	"川(四川)","鄂(湖北)","赣(江西)","甘(甘肃)","挂","桂(广西)",
	"贵(贵州)","黑(黑龙江)","沪(上海)","冀(河北)", "吉(吉林)","晋(山西)", 
	"津(天津)","京(北京)","警", "军", "空", "辽(辽宁)", 
	"鲁(山东)", "蒙(内蒙古)","闽(福建)", "宁(宁夏)", "黔(贵州)", "青(青海)", 
	"琼(海南)","陕(陕西)", "蜀(四川)", "苏(江苏)", "台(台湾)", "皖(安徽)",
	"湘(湖南)", "新(新疆)", "渝(重庆)", "豫(河南)", "粤(广东)","云(云南)",
	"藏(西藏)","浙(浙江)"
};

IMPLEMENT_DYNAMIC(CLS_VCAEVENT_Lisence, CDialog)

CLS_VCAEVENT_Lisence::CLS_VCAEVENT_Lisence(CWnd* pParent /*=NULL*/)
	: CLS_VCAEventBasePage(CLS_VCAEVENT_Lisence::IDD, pParent)
{

}

CLS_VCAEVENT_Lisence::~CLS_VCAEVENT_Lisence()
{
}

void CLS_VCAEVENT_Lisence::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBO_FIRST_CHAR, m_cboFirstChar);
	DDX_Control(pDX, IDC_CBO_FIRST_LETTER, m_cboFirstLetter);
	DDX_Control(pDX, IDC_SLIDER1, m_sldVLoopSensitivity);
	DDX_Control(pDX, IDC_EDT_LISENCE_POINTS_AREA, m_edtLisenceAreaPoints);
}


BEGIN_MESSAGE_MAP(CLS_VCAEVENT_Lisence, CDialog)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTN_LISENCE_SET, &CLS_VCAEVENT_Lisence::OnBnClickedBtnLisenceSet)
	ON_BN_CLICKED(IDC_BTN_LISENCE_DRAW, &CLS_VCAEVENT_Lisence::OnBnClickedBtnLisenceDraw)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CLS_VCAEVENT_Lisence::OnNMCustomdrawSlider1)
END_MESSAGE_MAP()


// CLS_VCAEVENT_Lisence 消息处理程序

BOOL CLS_VCAEVENT_Lisence::OnInitDialog()
{
	CDialog::OnInitDialog();

	UpdateUIText();

	return TRUE;
}

void CLS_VCAEVENT_Lisence::OnLanguageChanged()
{
	UpdateUIText();
}

void CLS_VCAEVENT_Lisence::UpdateUIText()
{
	SetDlgItemTextEx(IDC_STC_FIRST_CHAR, IDS_CONFIG_ITS_FIRSTCHINESE);
	SetDlgItemTextEx(IDC_STC_FIRST_LETTER, IDS_CONFIG_ITS_FIRSTWORD);
	SetDlgItemTextEx(IDC_STC_LEVEL, IDS_CONFIG_ITS_ILLEGALPARK_SENSITIVITY);
	SetDlgItemTextEx(IDC_STC_LISENCE_AREA_POINTS, IDS_VCA_EVENT_LEAVEDETECT_AREA_POINTS);
	SetDlgItemTextEx(IDC_BTN_LISENCE_DRAW, IDS_VCA_DRAWWING);
	SetDlgItemTextEx(IDC_BTN_LISENCE_SET, IDS_SET);

	m_sldVLoopSensitivity.SetRange(0,100);
	m_sldVLoopSensitivity.SetPos(50);
	SetDlgItemInt(IDC_STC_LEVEL_TEXT, 50);
	
	m_cboFirstChar.ResetContent();
	for (int i=0; i<sizeof(CONST_cstrProvince)/sizeof(CString); i++)
	{
		m_arrayProvince.Add(CONST_cstrProvince[i]);
		m_cboFirstChar.AddString(m_arrayProvince[i]);
	}

	CString cstrTmp;
	char chLetter = 'A';
	m_cboFirstLetter.ResetContent();
	for(int i=0; i<26; i++)
	{
		cstrTmp.Format("%c",chLetter);
		m_cboFirstLetter.AddString(cstrTmp);
		chLetter++;
	}
}

void CLS_VCAEVENT_Lisence::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_VCAEventBasePage::OnShowWindow(bShow, nStatus);

	if (bShow)
	{
		UpdatePageUI();
	}
}

void CLS_VCAEVENT_Lisence::UpdatePageUI()
{
	if (m_iLogonID < 0 || m_iChannelNO < 0)
	{
		return;
	}

	int iRet = -1;

	TITSLicensePlateOptimizeFirstHZInfo strctFirstHZInfo = {0};
	iRet = NetClient_GetITSExtraInfo(m_iLogonID, ITS_OPTIM_CMD_GET, m_iChannelNO, &strctFirstHZInfo, sizeof(strctFirstHZInfo));
	if(iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetITSExtraInfo(%d,%d,%d)error = %d",m_iLogonID, ITS_OPTIM_CMD_GET, m_iChannelNO, GetLastError());
		return;
	}

	CString cstrTmp; 
	cstrTmp = strctFirstHZInfo.cModifyAlpha;

	for (int i=0; i<m_arrayProvince.GetCount(); i++)
	{
		if(m_arrayProvince[i].Find(cstrTmp) == 0)
		{
			m_cboFirstChar.SetCurSel(i);
			break;
		}
	}

	cstrTmp = strctFirstHZInfo.cModifyChar;
	char chLetter = 'A';
	for(int i=0; i<26; i++)
	{
		if (strctFirstHZInfo.cModifyChar[0] == chLetter)
		{
			m_cboFirstLetter.SetCurSel(i);
			break;
		}
		chLetter++;
	}

	TITSRoadwayReco strctRoadwayReco = {0};
	iRet = NetClient_GetITSRoadwayParam(m_iLogonID, ITS_ROADWAY_CMD_GET_RECO, &strctRoadwayReco, sizeof(strctRoadwayReco));
	if(iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetITSRoadwayParam(%d,%d,%d)error = %d",m_iLogonID, ITS_ROADWAY_CMD_GET_RECO, m_iChannelNO, GetLastError());
		return;
	}

	int iValue = 0;
	int iVHeight = 0;
	int iVWidth = 0;
	iRet = NetClient_GetVideoSize(m_iLogonID, m_iChannelNO, &iVWidth, &iVHeight, m_iStreamNO);
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetVideoSize(%d,%d,%d)error = %d",m_iLogonID, m_iChannelNO, m_iStreamNO, GetLastError());
		return;
	}


	TITSRoadwayVLoop strctRoadwayVLoop = {0};
	iRet = NetClient_GetITSRoadwayParam(m_iLogonID,ITS_ROADWAY_CMD_GET_VLOOP,&strctRoadwayVLoop,sizeof(strctRoadwayVLoop));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_GetITSRoadwayParam(%d,%d)error = %d",m_iLogonID, ITS_ROADWAY_CMD_GET_VLOOP, GetLastError());
		return;
	}

	int iPos = strctRoadwayVLoop.iSensitivity;
	m_sldVLoopSensitivity.SetPos(iPos);
	SetDlgItemInt(IDC_STC_LEVEL_TEXT, iPos);
}


void CLS_VCAEVENT_Lisence::OnBnClickedBtnLisenceSet()
{
	int iRet = -1;
	CString cstrTmp; 
	TITSLicensePlateOptimizeFirstHZInfo strctFirstHZInfo = {0};

	m_cboFirstChar.GetWindowText(cstrTmp);
	memcpy(&strctFirstHZInfo.cModifyAlpha,cstrTmp.GetBuffer(),2);
	cstrTmp.ReleaseBuffer();

	m_cboFirstLetter.GetWindowText(cstrTmp);
	memcpy(&strctFirstHZInfo.cModifyChar,cstrTmp.GetBuffer(),1);
	cstrTmp.ReleaseBuffer();

	iRet = NetClient_SetITSExtraInfo(m_iLogonID,ITS_OPTIM_CMD_SET,m_iChannelNO,&strctFirstHZInfo,sizeof(strctFirstHZInfo));
	if(iRet !=0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetITSExtraInfo(%d,%d,%d)error = %d",m_iLogonID, ITS_OPTIM_CMD_SET, m_iChannelNO, GetLastError());
		return;
	}

	TITSRoadwayVLoop strctRoadwayVLoop = {0};

	strctRoadwayVLoop.iSensitivity = m_sldVLoopSensitivity.GetPos();

	CString strPointStr;
	vca_TPolygon stRegion = {0};
	POINT   ptSet[4];
	GetDlgItemText(IDC_EDT_LISENCE_POINTS_AREA, strPointStr);
	GetPolyFromString(strPointStr, 4, stRegion);
	memcpy(ptSet, &stRegion, sizeof(ptSet));

	//保存多边形点坐标以高16位为Y坐标,低16位X坐标方式存储,四个点四边形.
	strctRoadwayVLoop.iPoint1[0][0] = ptSet[0].y;
	strctRoadwayVLoop.iPoint1[0][0] <<= 16;
	strctRoadwayVLoop.iPoint1[0][0] |= ptSet[0].x;

	strctRoadwayVLoop.iPoint2[0][0] = ptSet[1].y;
	strctRoadwayVLoop.iPoint2[0][0] <<= 16;
	strctRoadwayVLoop.iPoint2[0][0] |= ptSet[1].x;

	strctRoadwayVLoop.iPoint3[0][0] = ptSet[2].y;
	strctRoadwayVLoop.iPoint3[0][0] <<= 16;
	strctRoadwayVLoop.iPoint3[0][0] |= ptSet[2].x;

	strctRoadwayVLoop.iPoint4[0][0] = ptSet[3].y;
	strctRoadwayVLoop.iPoint4[0][0] <<= 16;
	strctRoadwayVLoop.iPoint4[0][0] |= ptSet[3].x;

	iRet = NetClient_SetITSRoadwayParam(m_iLogonID,ITS_ROADWAY_CMD_SET_VLOOP,&strctRoadwayVLoop,sizeof(strctRoadwayVLoop));
	if (iRet < 0)
	{
		AddLog(LOG_TYPE_FAIL, "", "NetClient_SetITSRoadwayParam(%d,%d)error = %d",m_iLogonID, ITS_ROADWAY_CMD_SET_VLOOP, GetLastError());
		return;
	}
}

void CLS_VCAEVENT_Lisence::OnBnClickedBtnLisenceDraw()
{
	if (NULL == m_pDlgVideoView)
	{
		m_pDlgVideoView = new CLS_VideoViewForDraw();
		if (NULL == m_pDlgVideoView)
		{
			return;
		}
	}
	/*以下代码为了能从draw对话框中取出相应参数*/
	m_pDlgVideoView->Init(m_iLogonID, m_iChannelNO, m_iStreamNO);
	m_pDlgVideoView->SetDrawType(DrawType_Crowd);
	int iPointNum = 0;
	int iDirection = 0;
	char cPointBuf[MAX_POINTBUF_LEN] = {0};
	int iSetRet = m_pDlgVideoView->SetPointRegionParam(cPointBuf, &iPointNum, &iDirection);
	if (-1 == iSetRet)
	{
		return;
	}
	if (IDOK == m_pDlgVideoView->DoModal())
	{
		m_edtLisenceAreaPoints.SetWindowText(cPointBuf);
		//SetDlgItemInt(IDC_EDIT_AREA1_POINT_NUM, iPointNum);
	}

	delete m_pDlgVideoView;
	m_pDlgVideoView = NULL;
}

void CLS_VCAEVENT_Lisence::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	int iPos = m_sldVLoopSensitivity.GetPos();
	if (iPos < 0)
	{
		iPos = 0;
	}
	else if (iPos > 100)
	{
		iPos = 100;
	}
	SetDlgItemInt(IDC_STC_LEVEL_TEXT, iPos);

	*pResult = 0;
}
