
#include "stdafx.h"
#include "NetClientDemo.h"
#include "LinkOut.h"
#include "../Common/CommonFun.h"

// CLS_LinkOut 对话框

IMPLEMENT_DYNAMIC(CLS_LinkOut, CDialog)

CLS_LinkOut::CLS_LinkOut(int _iLogonID, CWnd* pParent /*=NULL*/)
	: CDialog(CLS_LinkOut::IDD, pParent)
{
	m_iLogonID = _iLogonID;
}

CLS_LinkOut::~CLS_LinkOut()
{
}

void CLS_LinkOut::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHK_SELALL, m_chkSelAll);
	for (int i=0;i<16;i++ )
	{
		DDX_Control(pDX, IDC_CHK_CH1+i, m_chkCH[i]);
	}
	
}


BEGIN_MESSAGE_MAP(CLS_LinkOut, CDialog)
	ON_BN_CLICKED(IDC_CHK_SELALL, &CLS_LinkOut::OnBnClickedChkSelectAll)
	ON_CONTROL_RANGE(BN_CLICKED,IDC_CHK_CH1,IDC_CHK_CH16,&CLS_LinkOut::OnBnClickedChkChannel)
END_MESSAGE_MAP()


// CLS_LinkOut 消息处理程序

BOOL CLS_LinkOut::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemTextEx(IDC_STC_SELECT_CH, IDS_CONFIG_LINK_SELECT_CHANNEL);
	SetDlgItemTextEx(IDC_CHK_SELALL, IDS_CONFIG_LINK_SELECT_ALL);

	return TRUE;
}

void CLS_LinkOut::SetDlgInfo(char* _cParam,int _iSize)
{
	if (m_chkSelAll)//通道全选按钮选中
	{
		m_chkSelAll.SetCheck(TRUE);
		for (int i=0; i<16;i++)
		{
			m_chkCH[i].SetCheck(TRUE);
		}
	}
	else
	{
		int iSel = 1;
		m_chkCH[iSel].SetCheck(TRUE);
	}
}

void CLS_LinkOut::GetDlgInfo(char* _cParam,int _iSize)
{
	int iSelAll = m_chkSelAll.GetCheck();
	if (iSelAll)
	{
		
	}
	else
	{
		for (int i=0; i<16;i++)
		{
			int iSel = m_chkCH[i].GetCheck();
		}
	}
}

void CLS_LinkOut::SetData(AlarmInLink* _pAlarmInLink)
{
	if (_pAlarmInLink == NULL)
	{
		return;
	}

//	CLS_DlgLinkBase::SetData(_pAlarmInLink);

	//联动通道
	LPCTSTR lpszSource = _pAlarmInLink->cParam;
	CString strData  = _pAlarmInLink->cParam;;
// 	strData.Split(lpszSource);
// 	int iChannel = strData.GetIntValue("channel");


// 	int iIndex = strData.Find(',');
// 	if (iIndex < 0)
// 	{
// 		return;
// 	}

//	CString cstrParam = strData.Left(iIndex);

	int iParamIndex = strData.Find('=');
	if (iParamIndex < 0)
	{
		return;
	}
	CString strKey = strData.Left(iParamIndex);
	CString strValue = strData.Right(strData.GetLength()-iParamIndex-1);

	int iChannel  = atoi(strValue.GetBuffer());

	for (int i = 0; i < MAX_CHANNELS; i++)
	{
		if ((iChannel&(1<<i)) == 0)
		{
			m_chkCH[i].SetCheck(BST_UNCHECKED);
		}
		else
		{
			m_chkCH[i].SetCheck(BST_CHECKED);
		}
	}

	OnBnClickedChkChannel(IDC_CHK_CH1);
}

BOOL CLS_LinkOut::GetData(AlarmInLink* _pAlarmInLink)
{
	if (_pAlarmInLink == NULL)
	{
		return FALSE;
	}

//	CLS_DlgLinkBase::GetData(_pAlarmInLink);

	
	int iCheck = 0;
	for (int i = 0; i < MAX_CHANNELS; i++)
	{
		if (m_chkCH[i].GetCheck())
		{
			iCheck = iCheck|(1<<i);
		}
	}

	if (iCheck == 0)
	{
		return FALSE;
	}

	CString strData;
 	strData.Format("channel=%d", iCheck);
 	//CString cstrParam = strData.Combine();

	strcpy_s(_pAlarmInLink->cParam, (LPSTR)(LPCTSTR)strData);

	return TRUE;
}

void CLS_LinkOut::OnBnClickedChkSelectAll()
{
	int iCheck = m_chkSelAll.GetCheck();
	for (int i=0; i < MAX_CHANNELS; i++)
	{
		m_chkCH[i].SetCheck(iCheck);
	}
}

void CLS_LinkOut::OnBnClickedChkChannel(UINT _uiID)
{
	int index = _uiID - IDC_CHK_CH1;
	if (m_chkCH[index].GetCheck() == BST_UNCHECKED)
	{
		if (m_chkSelAll.GetCheck() == BST_CHECKED)
		{
			m_chkSelAll.SetCheck(BST_UNCHECKED);
		}
	}
	else
	{
		int i = 0;
		for (i = 0; i < MAX_CHANNELS; i++)
		{
			if (m_chkCH[i].GetCheck() == BST_UNCHECKED)
			{
				return;
			}
		}
		m_chkSelAll.SetCheck(BST_CHECKED);
	}
}

