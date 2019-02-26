
#include "stdafx.h"
#include "NetClientDemo.h"
#include "FaceLibManage.h"

typedef enum{
	ITEM_LIB_INDEX = 0,					//序号
	ITEM_LIB_NAME,						//库名称
	ITEM_LIB_VALUE,						//识别阀值
	ITEM_LIB_UPLOAD,					//识别信息
	ITEM_LIB_DESCRIP,					//描述
}ITEM_FACE_LIB;


IMPLEMENT_DYNAMIC(CLS_DlgCfgFaceLibMng, CDialog)

CLS_DlgCfgFaceLibMng::CLS_DlgCfgFaceLibMng(CWnd* pParent /*=NULL*/)
	: CLS_BasePage(CLS_DlgCfgFaceLibMng::IDD, pParent)
{

}

CLS_DlgCfgFaceLibMng::~CLS_DlgCfgFaceLibMng()
{
}

void CLS_DlgCfgFaceLibMng::DoDataExchange(CDataExchange* pDX)
{
	CLS_BasePage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCBO_FACE_LIB_DISPATCH, m_cboDispath);
	DDX_Control(pDX, IDC_EDT_FACE_LIB_NAME, m_edtName);
	DDX_Control(pDX, IDC_SLD_FACE_LIB_REG, m_sldReg);
	DDX_Control(pDX, IDC_STC_FACE_LIB_VALUE, m_stcValue);
	DDX_Control(pDX, IDC_EDT_FACE_LIB_DESCRIP, m_edtDescrip);
	DDX_Control(pDX, IDC_LST_FACE_LIB, m_lstLibInfo);
}


BEGIN_MESSAGE_MAP(CLS_DlgCfgFaceLibMng, CLS_BasePage)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTN_FACE_LIB_ADD, &CLS_DlgCfgFaceLibMng::OnBnClickedBtnFaceLibAdd)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLD_FACE_LIB_REG, &CLS_DlgCfgFaceLibMng::OnNMCustomdrawSldFaceLibReg)
	ON_BN_CLICKED(IDC_BTN_FACE_LIB_MDY, &CLS_DlgCfgFaceLibMng::OnBnClickedBtnFaceLibMdy)
	ON_BN_CLICKED(IDC_BTN_FACE_LIB_DEL, &CLS_DlgCfgFaceLibMng::OnBnClickedBtnFaceLibDel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LST_FACE_LIB, &CLS_DlgCfgFaceLibMng::OnLvnItemchangedLstFaceLib)
	ON_BN_CLICKED(IDC_BTN_FACE_LIB_QUERY, &CLS_DlgCfgFaceLibMng::OnBnClickedBtnFaceLibQuery)
END_MESSAGE_MAP()


BOOL CLS_DlgCfgFaceLibMng::OnInitDialog()
{
	CLS_BasePage::OnInitDialog();

	UI_UpdataText();

	UI_Init();

	return TRUE;
}

void CLS_DlgCfgFaceLibMng::UI_Init()
{
	m_cboDispath.ResetContent();
	m_cboDispath.InsertString(0, GetTextEx(IDS_NOT_UPLOAD));
	m_cboDispath.InsertString(1, GetTextEx(IDS_UPLOAD));
	m_cboDispath.SetCurSel(0);

	m_sldReg.SetRange(0, 100);

	m_lstLibInfo.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_lstLibInfo.InsertColumn(ITEM_LIB_INDEX, GetTextEx(IDS_NUM), LVCFMT_LEFT, 40, -1);
	m_lstLibInfo.InsertColumn(ITEM_LIB_NAME, GetTextEx(IDS_PE_NAME), LVCFMT_LEFT, 180, -1);
	m_lstLibInfo.InsertColumn(ITEM_LIB_VALUE, GetTextEx(IDS_THRESHOLD), LVCFMT_LEFT, 100, -1);	
	m_lstLibInfo.InsertColumn(ITEM_LIB_UPLOAD, GetTextEx(IDS_REG_INFO), LVCFMT_LEFT, 100, -1);	
	m_lstLibInfo.InsertColumn(ITEM_LIB_DESCRIP, GetTextEx(IDS_DESCRIPTION), LVCFMT_LEFT, 200, -1);

	m_sldReg.SetPos(0);
	m_sldReg.SetTicFreq(1);
	m_stcValue.SetWindowText(0);
}

void CLS_DlgCfgFaceLibMng::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CLS_BasePage::OnShowWindow(bShow, nStatus);
}

void CLS_DlgCfgFaceLibMng::OnLanguageChanged(int _iLanguage)
{
	UI_UpdataText();
}

void CLS_DlgCfgFaceLibMng::UI_UpdataText()
{
	SetDlgItemTextEx(IDC_STC_FACE_LIB_NAME, IDS_PE_NAME);
	SetDlgItemTextEx(IDC_STC_FACE_LIB_DISPATCH, IDS_THRESHOLD);
	SetDlgItemTextEx(IDC_STC_FACE_LIB_REG, IDS_REG_INFO);
	SetDlgItemTextEx(IDC_STC_FACE_LIB_DESCRIP, IDS_DESCRIPTION);
	SetDlgItemTextEx(IDC_BTN_FACE_LIB_ADD, IDS_ADD);
	SetDlgItemTextEx(IDC_BTN_FACE_LIB_MDY, IDS_MODIFY);
	SetDlgItemTextEx(IDC_BTN_FACE_LIB_DEL, IDS_DELETE);
	SetDlgItemTextEx(IDC_BTN_FACE_LIB_QUERY, IDS_PLAYBACK_QUERY);
	//列表更新语言
	SetListCtrlColumn(m_lstLibInfo, ITEM_LIB_INDEX, GetTextEx(IDS_NUM));
	SetListCtrlColumn(m_lstLibInfo, ITEM_LIB_NAME, GetTextEx(IDS_PE_NAME));
	SetListCtrlColumn(m_lstLibInfo, ITEM_LIB_VALUE, GetTextEx(IDS_THRESHOLD));
	SetListCtrlColumn(m_lstLibInfo, ITEM_LIB_UPLOAD, GetTextEx(IDS_REG_INFO));
	SetListCtrlColumn(m_lstLibInfo, ITEM_LIB_DESCRIP, GetTextEx(IDS_DESCRIPTION));
	//
	int iSel = m_cboDispath.GetCurSel();
	m_cboDispath.ResetContent();
	m_cboDispath.InsertString(0, GetTextEx(IDS_NOT_UPLOAD));
	m_cboDispath.InsertString(1, GetTextEx(IDS_UPLOAD));
	m_cboDispath.SetCurSel(iSel);
}

void CLS_DlgCfgFaceLibMng::UI_UpdataList()
{
	if (NULL == NetClient_FaceConfig)
	{
		return;
	}

	m_lstLibInfo.DeleteAllItems();
	int iPageNo = 0;
	while (TRUE)
	{
		FaceLibQuery tQuery = {0};
		tQuery.iSize = sizeof(FaceLibQuery);
		tQuery.iChanNo = m_iChannelNO;
		tQuery.iPageNo = iPageNo;
		tQuery.iPageCount = FACE_MAX_PAGE_COUNT;

		FaceLibQueryResult tResult[FACE_MAX_PAGE_COUNT] = {0};
		int iRet = NetClient_FaceConfig(m_iLogonID, FACE_CMD_LIB_QUERY, m_iChannelNO, &tQuery, sizeof(FaceLibQuery), &tResult, sizeof(FaceLibQueryResult));
		if (RET_SUCCESS != iRet)
		{
			AddLog(LOG_TYPE_FAIL,"","NetClient_FaceConfig failed, ret(%d), pageNo(%d).", iRet, iPageNo);
			break;
		}
		
		for (int iIdx = 0; iIdx < FACE_MAX_PAGE_COUNT && iIdx < tResult[0].iPageCount; ++iIdx)
		{
			if (tResult[iIdx].tFaceLib.iSize > 0)
			{
				UI_UpdateListItem(tResult[iIdx].tFaceLib);
			}
		}

		iPageNo++;
		int iPageCount = tResult[0].iTotal / FACE_MAX_PAGE_COUNT;
		if (tResult[0].iTotal % FACE_MAX_PAGE_COUNT > 0)
		{
			iPageCount = iPageCount + 1;
		}
		
		if (iPageNo >= iPageCount)
		{
			break;
		}
	}
}

void CLS_DlgCfgFaceLibMng::UI_UpdateListItem(FaceLibInfo& sLibInfo, int iLibIndex /*= -1*/)
{
	int iIndex = iLibIndex;
	if (-1 == iLibIndex)
	{
		iIndex = m_lstLibInfo.GetItemCount();
		m_lstLibInfo.InsertItem(iIndex,_T(""));
	}
	m_lstLibInfo.SetItemData(iIndex, sLibInfo.iLibKey);

	m_lstLibInfo.SetItemText(iIndex, ITEM_LIB_INDEX, IntToCString(iIndex + 1));
	m_lstLibInfo.SetItemText(iIndex, ITEM_LIB_NAME, sLibInfo.cName);
	m_lstLibInfo.SetItemText(iIndex, ITEM_LIB_VALUE, IntToCString(sLibInfo.iThreshold));
	m_lstLibInfo.SetItemText(iIndex, ITEM_LIB_UPLOAD, sLibInfo.iAlarmType ? GetTextEx(IDS_UPLOAD):GetTextEx(IDS_NOT_UPLOAD));
	m_lstLibInfo.SetItemText(iIndex, ITEM_LIB_DESCRIP, sLibInfo.cExtrInfo);
}

void CLS_DlgCfgFaceLibMng::OnBnClickedBtnFaceLibAdd()
{
	if (NULL == NetClient_FaceConfig)
	{
		return;
	}

	if (GetWidgetText(IDC_EDT_FACE_LIB_NAME).IsEmpty())
	{
		return;
	}

	FaceLibEdit sEdit = {0};
	sEdit.iSize = sizeof(FaceLibEdit);
	sEdit.iChanNo = m_iChannelNO;
	sEdit.tFaceLib.iSize = sizeof(FaceLibInfo);
	sEdit.tFaceLib.iThreshold = m_sldReg.GetPos();
	sEdit.tFaceLib.iLibKey = 0;
	sEdit.tFaceLib.iAlarmType = m_cboDispath.GetCurSel();
	strcpy_s(sEdit.tFaceLib.cName, sizeof(sEdit.tFaceLib.cName), GetWidgetText(IDC_EDT_FACE_LIB_NAME));
	strcpy_s(sEdit.tFaceLib.cExtrInfo, sizeof(sEdit.tFaceLib.cExtrInfo), GetWidgetText(IDC_EDT_FACE_LIB_DESCRIP));

	FaceReply sReply = {0};
	int iRet = NetClient_FaceConfig(m_iLogonID, FACE_CMD_LIB_EDIT, m_iChannelNO, &sEdit, sizeof(FaceLibEdit), &sReply, sizeof(FaceReply));
	if (RET_SUCCESS == iRet && RET_SUCCESS == sReply.iResult)
	{
		UI_UpdataList();
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_FaceConfig failed, cmd(%d), ret(%d),result(%d).", FACE_CMD_LIB_EDIT, iRet, sReply.iResult);
	}	
}

void CLS_DlgCfgFaceLibMng::OnNMCustomdrawSldFaceLibReg(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	SetDlgItemInt(IDC_STC_FACE_LIB_VALUE, m_sldReg.GetPos());
	*pResult = 0;
}

void CLS_DlgCfgFaceLibMng::OnBnClickedBtnFaceLibMdy()
{
	POSITION pPos = m_lstLibInfo.GetFirstSelectedItemPosition();
	if (NULL == pPos || NULL == NetClient_FaceConfig)
	{
		return;
	}

	if (GetWidgetText(IDC_EDT_FACE_LIB_NAME).IsEmpty())
	{
		return;
	}
	int iPos = m_lstLibInfo.GetNextSelectedItem(pPos);

	FaceLibEdit sEdit = {0};
	sEdit.iSize = sizeof(FaceLibEdit);
	sEdit.iChanNo = m_iChannelNO;
	sEdit.tFaceLib.iSize = sizeof(FaceLibInfo);
	sEdit.tFaceLib.iThreshold = m_sldReg.GetPos();
	sEdit.tFaceLib.iLibKey = m_lstLibInfo.GetItemData(iPos);
	sEdit.tFaceLib.iAlarmType = m_cboDispath.GetCurSel();
	strcpy_s(sEdit.tFaceLib.cName, sizeof(sEdit.tFaceLib.cName), GetWidgetText(IDC_EDT_FACE_LIB_NAME));
	strcpy_s(sEdit.tFaceLib.cExtrInfo, sizeof(sEdit.tFaceLib.cExtrInfo), GetWidgetText(IDC_EDT_FACE_LIB_DESCRIP));

	FaceReply sReply = {0};
	sReply.iSize = sizeof(FaceReply);
	int iRet = NetClient_FaceConfig(m_iLogonID, FACE_CMD_LIB_EDIT, m_iChannelNO, &sEdit, sizeof(FaceLibEdit), &sReply, sizeof(FaceReply));
	if (RET_SUCCESS == iRet && RET_SUCCESS == sReply.iResult)
	{
		UI_UpdataList();
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_FaceConfig failed, cmd(%d), ret(%d),result(%d).", FACE_CMD_LIB_EDIT, iRet, sReply.iResult);
	}
}

void CLS_DlgCfgFaceLibMng::OnBnClickedBtnFaceLibDel()
{
	POSITION pPos = m_lstLibInfo.GetFirstSelectedItemPosition();
	if (NULL == pPos || NULL == NetClient_FaceConfig)
	{
		return;
	}
	int iPos = m_lstLibInfo.GetNextSelectedItem(pPos);

	FaceLibDelete sDelete = {0};
	sDelete.iSize = sizeof(FaceLibDelete);
	sDelete.iChanNo = m_iChannelNO;
	sDelete.iLibKey = m_lstLibInfo.GetItemData(iPos);

	FaceReply sReply = {0};
	sReply.iSize = sizeof(FaceReply);
	int iRet = NetClient_FaceConfig(m_iLogonID, FACE_CMD_LIB_DELETE, m_iChannelNO, &sDelete, sizeof(FaceLibEdit), &sReply, sizeof(FaceReply));
	if (RET_SUCCESS == iRet && RET_SUCCESS == sReply.iResult)
	{
		UI_UpdataList();
	}
	else
	{
		AddLog(LOG_TYPE_FAIL,"","NetClient_FaceConfig failed, cmd(%d), ret(%d),result(%d).", FACE_CMD_LIB_DELETE, iRet, sReply.iResult);
	}
}

void CLS_DlgCfgFaceLibMng::OnLvnItemchangedLstFaceLib(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	int iPos = pNMLV->iItem;
	m_edtName.SetWindowText(m_lstLibInfo.GetItemText(iPos, ITEM_LIB_NAME));
	m_edtDescrip.SetWindowText(m_lstLibInfo.GetItemText(iPos, ITEM_LIB_DESCRIP));
	m_sldReg.SetPos(atoi(m_lstLibInfo.GetItemText(iPos, ITEM_LIB_VALUE)));
	m_cboDispath.SetCurSel(GetTextEx(IDS_UPLOAD) == m_lstLibInfo.GetItemText(iPos, ITEM_LIB_UPLOAD) ? 1 : 0);
	*pResult = 0;
}

void CLS_DlgCfgFaceLibMng::OnBnClickedBtnFaceLibQuery()
{
	UI_UpdataList();
}
