// NeuListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "NeuListCtrl.h"

#include "shlwapi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define COMBOX_ID  790
#define EDITBOX_ID 786

/////////////////////////////////////////////////////////////////////////////
// CNeuListCtrl


CNeuListCtrl::CNeuListCtrl()
{
	m_pControlPtrArray = new CPtrArray();
	m_iCurSelctedItemIndex = -1;
	m_iControlIDCounter = 786;
	m_fnControl.CreatePointFont(72 ,"Arial");
	m_pMainList = NULL ;
	m_pClickItemCallBack = NULL;
	m_pClickData = NULL;
	m_hParent = NULL;
}

CNeuListCtrl::~CNeuListCtrl()
{
	if(m_pHeaderCtrl)
	{
		m_pHeaderCtrl->DestroyWindow();
		delete m_pHeaderCtrl;
		m_pHeaderCtrl = NULL;
	}

	ReleaseControls();
	m_fnControl.DeleteObject();

	if (m_pMainList != NULL)
	{
		m_pMainList->DeleteObject();
		m_pMainList = NULL;
	}
}

BEGIN_MESSAGE_MAP(CNeuListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CNeuListCtrl)
	ON_WM_KEYDOWN()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_CTLCOLOR()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnNMCustomdraw)
	ON_CBN_SELCHANGE(COMBOX_ID, &CNeuListCtrl::OnCbnSelchangeCombo)//790
	//}}AFX_MSG_MAP
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNeuListCtrl message handlers


BOOL CNeuListCtrl::Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID )
{
	BOOL bCreated = CListCtrl::Create(dwStyle, rect, pParentWnd,nID );
	return bCreated;
}

void CNeuListCtrl::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(m_iCurSelctedItemIndex > -1)
	{
		GetAndDisplayControlsData();
	}
	
	NM_LISTVIEW * pNMListView = (NM_LISTVIEW*) pNMHDR;
	if (pNMListView != NULL)
	{
		if(pNMListView->iItem<0 || pNMListView->iSubItem<0)
		{
			return;
		}

		int iItem = pNMListView->iItem;
		m_iCurSelctedItemIndex = iItem;
		m_iSubItem = pNMListView->iSubItem;
		//每次点击的时候取消最后一行的选中状态--add by litao
 		int iCount = this->GetItemCount();
 		if(iItem != iCount)
 		{
 			this->SetItemState(iCount-1, 0, LVIS_SELECTED|LVIS_FOCUSED);
 			this->SetItemColor(iCount-1,COLOR_CANCEL);
 		}

		if(iItem >= 0)
		{
			BOOL bChecked = TRUE;
			MapControlsForSubItems();
			ShowControls(TRUE);
			EnableControls(bChecked);
			SetItemState(m_iCurSelctedItemIndex,LVIS_SELECTED,LVIS_SELECTED);
		}
	}

	if (m_pClickItemCallBack)
	{
		m_pClickItemCallBack(m_pClickData, pNMListView->iItem, pNMListView->iSubItem);
	}

	*pResult = 0;
}

BOOL CNeuListCtrl::DestroyWindow() 
{
	if(m_pHeaderCtrl)
	{
		m_pHeaderCtrl->DestroyWindow();
		delete m_pHeaderCtrl;
		m_pHeaderCtrl = NULL;
	}
	return CListCtrl::DestroyWindow();
}

void CNeuListCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect  rc;
	GetParent()->GetClientRect(&rc);

	if (rc.Size() == CSize(0,0))
	{
	   return;
	}

	CDC     MemoryDC;
	CBitmap Bitmap;
	CBrush  Brush;

	CRect rcWnd;
	GetWindowRect(&rcWnd);
	int rcWndW = rcWnd.Width(), rcWndH = rcWnd.Height();

	// Paint to a compatible DC
	MemoryDC.CreateCompatibleDC(&dc);
	Bitmap.CreateCompatibleBitmap(&dc, rcWndW, rcWndH);
	CBitmap *pOldBitmap = MemoryDC.SelectObject(&Bitmap);

	// Fill background (does what WM_ERASEBKGND would do)
	Brush.CreateSolidBrush(GetBkColor());
	MemoryDC.FillRect(&CRect(0,0, rcWndW,rcWndH), &Brush);

	Print(&MemoryDC, PRF_CLIENT|PRF_CHILDREN);
	Print(&MemoryDC, PRF_NONCLIENT);

	// Offset the MemoryDC drawing rectangle by rcBounds 
	CRect rcDraw = rc - rc.TopLeft();

	// Dump bits to real device context.
	dc.BitBlt(rc.left,rc.top, rc.Width(),rc.Height(), &MemoryDC, rcDraw.left,rcDraw.top, SRCCOPY);

	MemoryDC.SelectObject(pOldBitmap);
	
	MemoryDC.DeleteDC();//20140313 dongfubao
	Bitmap.DeleteObject();////20140313 dongfubao
	Brush.DeleteObject();//20140313 dongfubao
	CListCtrl::OnPaint();
	m_pHeaderCtrl->Invalidate(TRUE);
}

BOOL CNeuListCtrl::OnEraseBkgnd(CDC* pDC) 
{
	return true;
}

void CNeuListCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
	
	LockWindowUpdate();
	
	///////// Check Item is in Visible Area ///////////////
	BOOL bShowItem = FALSE;
	int iTopMostItemIndex = GetTopIndex();
	for(int i=iTopMostItemIndex; i<(iTopMostItemIndex + GetCountPerPage() ); i++)
	{
		if(m_iCurSelctedItemIndex == i)
		{
			bShowItem = TRUE;
			break;
		}
	}
	
	ShowControls(FALSE);
	if(m_iCurSelctedItemIndex > -1)
	{
		GetAndDisplayControlsData();
	}
	/////////////////////////////////////////////////////	
	switch(nSBCode)
	{
		case SB_BOTTOM :
			
			break;
		case SB_ENDSCROLL:
			if(bShowItem)
			{
				ShowControls(TRUE);
				MapControlsForSubItems();
			}
			break;
		case SB_LINEDOWN :
			break;

		case SB_LINEUP:
			break;
		case SB_PAGEDOWN:
			break;
		case SB_PAGEUP	:
			break;
		case SB_THUMBPOSITION :
			break;
		case SB_THUMBTRACK	:
			break;
		case SB_TOP :
			break;
		default: 
			break;
	}
	UnlockWindowUpdate();
}

void CNeuListCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CListCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
	
	LockWindowUpdate();
	
	///////// Check Item is in Visible Area ///////////////

	BOOL bShowItem = FALSE;
	int iTopMostItemIndex = GetTopIndex();
	for(int i=iTopMostItemIndex; i<(iTopMostItemIndex + GetCountPerPage() ); i++)
	{
		if(m_iCurSelctedItemIndex == i)
		{
			bShowItem = TRUE;
			break;
		}
	}
	
	ShowControls(FALSE);
	if(m_iCurSelctedItemIndex > -1)
	{
		GetAndDisplayControlsData();
	}
	/////////////////////////////////////////////////////	
	switch(nSBCode)
	{
		case SB_BOTTOM :
			break;
		case SB_ENDSCROLL:
			if(bShowItem)
			{
				ShowControls(FALSE);
				MapControlsForSubItems();
			}
			break;
		case SB_LINERIGHT:
			break;
		case SB_LINELEFT :
			break;
		case SB_PAGELEFT:
			break;
		case SB_PAGERIGHT	:
			break;
		case SB_THUMBPOSITION :
			break;
		case SB_THUMBTRACK	:
			break;
		case SB_TOP :
			break;
		default: 
			break;
	}
	UnlockWindowUpdate();
}

void CNeuListCtrl::SetItemControl(enCONTROLTYPE enControlType,int iIndex)
{
	if(m_pControlPtrArray == NULL)
	{
		m_pControlPtrArray = new CPtrArray();
	}
	SubItemControlsInfo *pSubItemInfo = new SubItemControlsInfo();
	if (pSubItemInfo != NULL)
	{
		pSubItemInfo->m_enControlType = enControlType;
		pSubItemInfo->m_iItemIndex = iIndex;

		CFont *pFont = GetFont();
		DWORD dwStyle = WS_BORDER|WS_CHILD | WS_TABSTOP;
		CRect ControlSize (10, 10, 100, 100);
		switch(enControlType)
		{
		case EDITBOX:
			{
				pSubItemInfo->m_pWnd = new CEdit();
				((CEdit*)pSubItemInfo->m_pWnd)->Create (dwStyle|ES_NUMBER,ControlSize,this ,m_iControlIDCounter);	
				break;
			}
		case CHECKBOX:
			{
				pSubItemInfo->m_pWnd = new CButton();
				((CButton*)pSubItemInfo->m_pWnd)->Create ("",dwStyle|BS_AUTOCHECKBOX,ControlSize,this ,m_iControlIDCounter);	
				break;
			}
		case COMBOBOX:
			{
				pSubItemInfo->m_pWnd = new CComboBox();
				((CComboBox*)pSubItemInfo->m_pWnd)->Create(dwStyle|WS_VSCROLL|CBS_DROPDOWNLIST,ControlSize, this,m_iControlIDCounter);
				break;
			}
		case LISTBOX:
			{
				pSubItemInfo->m_pWnd = new CListBox();
				((CListBox*)pSubItemInfo->m_pWnd)->Create (WS_VSCROLL|dwStyle,ControlSize,this ,m_iControlIDCounter);
				break;
			}
		case BUTTON:
			{
				pSubItemInfo->m_pWnd = new CButton();
				((CButton*)pSubItemInfo->m_pWnd)->Create ("",dwStyle,ControlSize,this ,m_iControlIDCounter);
				break;
			}
		case DATECTRL:
			{
				pSubItemInfo->m_pWnd = new CDateTimeCtrl();
				((CDateTimeCtrl*)pSubItemInfo->m_pWnd)->Create (dwStyle|DTS_TIMEFORMAT|DTS_UPDOWN,ControlSize,this ,m_iControlIDCounter);
				((CDateTimeCtrl*)pSubItemInfo->m_pWnd)->SetFormat("HH:mm");//转为定时巡航用，如有需要用，需要扩展
				break;
			}
		default: 
			break;
		}

        pSubItemInfo->m_pWnd->SetFont(&m_fnControl);
		int iDupIndex = ControlIndexDuplicating(iIndex);
		if(iDupIndex > -1)
		{
			DetachControl(iDupIndex);
		}
		if (m_pControlPtrArray)
		{
			m_pControlPtrArray->Add(pSubItemInfo);
		}
		if(enControlType != NONE)
		{
			m_iControlIDCounter += 4;
		}
	}
}

BOOL CNeuListCtrl::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	switch(((NMHDR*)lParam)->code)   
	{  
	case HDN_ITEMCHANGINGA: 
	case HDN_ITEMCHANGINGW:
		break;
	case HDN_ITEMCHANGEDA:
	case HDN_ITEMCHANGEDW:
		{
			HD_NOTIFY *phdn = (HD_NOTIFY *) lParam;
			NMHEADER * pHeade = (NMHEADER *) lParam;
			AdjustControlsAccordingToHeaderWidth (phdn);
			*pResult = 0;
		}
		break;
	default: 
		break;
	} 
	return CListCtrl::OnNotify(wParam, lParam, pResult);
	//---------------------end add 
}
CTime CNeuListCtrl::StrToTime(CString &cstrTime)
{
	int iSplit = cstrTime.Find(":");
	if (iSplit < 0)
	{
		iSplit = 0;
	}
	CString cstrTmp = cstrTime.Mid(0,iSplit);
	int iHour = atoi(cstrTmp.GetBuffer());
	cstrTmp.ReleaseBuffer();
	cstrTmp = cstrTime.Mid(iSplit+1, cstrTime.GetLength());
	int iMinute = atoi(cstrTmp.GetBuffer());
	cstrTmp.ReleaseBuffer();
	CTime tm(2014, 1, 1, iHour, iMinute,0);
	return tm;
}

void CNeuListCtrl::MapControlsForSubItems()
{
	int iCount = this->GetItemCount();//如果list ctrl中没内容，就不需要获取值
	if (iCount < 1)
	{
		return ;
	}

	if (m_iCurSelctedItemIndex < 0 || iCount <= m_iCurSelctedItemIndex)
	{

		return ;
	}

	int iItem = m_iCurSelctedItemIndex;
	CRect CtrlRect;
	CRect iconRect;
	SubItemControlsInfo *pSubItemControlsInfo  = NULL;
	CString strData = "";
	if (m_pControlPtrArray)
	{
		for(int i = 0; i< m_pControlPtrArray->GetSize(); i++)
		{
			pSubItemControlsInfo = (SubItemControlsInfo *) m_pControlPtrArray->GetAt(i);

			if(pSubItemControlsInfo)
			{
				GetSubItemRect(iItem,pSubItemControlsInfo->m_iItemIndex,LVIR_LABEL,CtrlRect);
				GetSubItemRect(iItem,pSubItemControlsInfo->m_iItemIndex,LVIR_ICON,iconRect);
				
				//CtrlRect.bottom+=13;
				if(pSubItemControlsInfo->m_iItemIndex == 0)
				{
					CtrlRect.left+=iconRect.right;
				}

				if(pSubItemControlsInfo->m_pWnd)
				{
					pSubItemControlsInfo->m_pWnd->MoveWindow(&CtrlRect);
				}

				strData = GetItemText(m_iCurSelctedItemIndex,pSubItemControlsInfo->m_iItemIndex);	
				switch(pSubItemControlsInfo->m_enControlType)
				{
					case CHECKBOX:
						{
							strData = GetItemText(m_iCurSelctedItemIndex ,pSubItemControlsInfo->m_iItemIndex);
							((CButton*)pSubItemControlsInfo->m_pWnd)->SetCheck(strData == "TRUE");
							SetItemText(m_iCurSelctedItemIndex ,pSubItemControlsInfo->m_iItemIndex,strData);	
							break;	
						}
					case EDITBOX:
						{
							pSubItemControlsInfo->m_pWnd->SetWindowText(strData);
							break;
						}
					case COMBOBOX:
						{
							if (strData.GetLength()>0)
							{
								((CComboBox*)pSubItemControlsInfo->m_pWnd)->SelectString(-1,strData);
							}
							else
							{
								//一下代码是用于在初始化读取已经存在的combox内容时，能正常显示，所以在给添加combox内容时，一定要setitemdata
								DWORD_PTR i = GetItemData(m_iCurSelctedItemIndex);
								CString cstrTmp;
								cstrTmp.Format("%d",i);
								int iNum = ((CComboBox*)pSubItemControlsInfo->m_pWnd)->GetCount();
								CString cstrTmp2;
								int j = 0;
								for (; j< iNum; j++)
								{
									((CComboBox*)pSubItemControlsInfo->m_pWnd)->GetLBText(j,cstrTmp2);
									if (cstrTmp2 == cstrTmp)
									{
										break;
									}
								}
								if (j == iNum)
								{
									((CComboBox*)pSubItemControlsInfo->m_pWnd)->AddString(cstrTmp);
								}
								((CComboBox*)pSubItemControlsInfo->m_pWnd)->SelectString(-1,cstrTmp);
							}
						}
						break;
					case LISTBOX:
						{
							((CListBox*)pSubItemControlsInfo->m_pWnd)->SelectString(-1,strData);
							CtrlRect.bottom += (((CListBox*)pSubItemControlsInfo->m_pWnd)->GetCount ()-1)*2;((CListBox*)pSubItemControlsInfo->m_pWnd)->GetItemHeight(0);
							pSubItemControlsInfo->m_pWnd->MoveWindow(&CtrlRect);
							break;
						}
					case DATECTRL:
						{
							CTime tm = StrToTime(strData);
							((CDateTimeCtrl*)pSubItemControlsInfo->m_pWnd)->SetTime(&tm);
							pSubItemControlsInfo->m_pWnd->MoveWindow(&CtrlRect);
							break;
						}
					default: 
						break;
				}
			}
		}
	}
}

void CNeuListCtrl::EnableControls(BOOL bEnable)
{
	if (m_iCurSelctedItemIndex < 0)
	{
		return;
	}

	if (!m_pControlPtrArray)
	{
		return;
	}
	SubItemControlsInfo *pSubItemControlsInfo = NULL ;
	for(int i=0; i<m_pControlPtrArray->GetSize(); i++)
	{
		pSubItemControlsInfo = (SubItemControlsInfo *)m_pControlPtrArray->GetAt(i);
		if(pSubItemControlsInfo)
		{
			if(pSubItemControlsInfo->m_pWnd)
			{
				pSubItemControlsInfo->m_pWnd->EnableWindow(bEnable);
			}
		}
	}
}

void CNeuListCtrl::ShowControls(BOOL bShow)
{
	if (!m_pControlPtrArray)
	{
		return;
	}

	SubItemControlsInfo *pSubItemControlsInfo  = NULL;
	for(int i=0; i<m_pControlPtrArray->GetSize(); i++)
	{
		pSubItemControlsInfo = (SubItemControlsInfo *)m_pControlPtrArray->GetAt(i);
		if(pSubItemControlsInfo)
		{
			if(pSubItemControlsInfo->m_pWnd)
			{
				pSubItemControlsInfo->m_pWnd->ShowWindow(bShow);
			}
		}
	}
}

BOOL CNeuListCtrl::AddToControlsData(int iIndex, CString strData)
{
	if (!m_pControlPtrArray)
	{
		return FALSE;
	}
	SubItemControlsInfo *pSubItemInfo = NULL ;
	for(int i=0; i<m_pControlPtrArray->GetSize(); i++)
	{
		pSubItemInfo = (SubItemControlsInfo *)m_pControlPtrArray->GetAt(i);
		if (pSubItemInfo)
		{
			if(pSubItemInfo->m_iItemIndex == iIndex)
			{
				switch(pSubItemInfo->m_enControlType )
				{
				case EDITBOX:
				case CHECKBOX:
				case BUTTON:
					{
						pSubItemInfo->m_pWnd->SetWindowText(strData);
						break;
					}
				case COMBOBOX:
					{
						((CComboBox*)pSubItemInfo->m_pWnd)->AddString(strData);
						break;
					}
				case LISTBOX:
					{
						((CListBox*)pSubItemInfo->m_pWnd)->AddString(strData);
						break;
					}
				default:
					break;
				}
				return TRUE;
			}
		}
	}
	return FALSE;
}

HBRUSH CNeuListCtrl::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CListCtrl::OnCtlColor(pDC, pWnd, nCtlColor);
	if (m_pControlPtrArray)
	{
		SubItemControlsInfo * pItemInfo  = NULL;
		for(int i=0; i<m_pControlPtrArray->GetSize(); i++)
		{
			pItemInfo = (SubItemControlsInfo*) m_pControlPtrArray->GetAt(i);
			if (pItemInfo)
			{
				if(pWnd == pItemInfo->m_pWnd)
				{
					hbr = ::CreateSolidBrush(pItemInfo->m_BKColor);
				}
			}
		}
	}	
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CNeuListCtrl::GetAndDisplayControlsData()
{
	int iCount = this->GetItemCount();//如果list ctrl中没内容，就不需要获取值
	if (iCount == 0)
	{
		return ;
	}

	if (m_iCurSelctedItemIndex < 0 || m_iCurSelctedItemIndex >= iCount)
	{
		return;
	}

	if (!m_pControlPtrArray)
	{
		return;
	}

	CString strData = "";
	int iCurIndex = -1 ;
	for(int i=0; i<m_pControlPtrArray->GetSize(); i++)
	{
		SubItemControlsInfo *pSubItemInfo = NULL;
		pSubItemInfo = (SubItemControlsInfo *)m_pControlPtrArray->GetAt(i);
		if (pSubItemInfo)
		{
			switch(pSubItemInfo->m_enControlType)
			{
			case CHECKBOX:
				{
					strData = ((CButton*)pSubItemInfo->m_pWnd)->GetCheck()?"TRUE":"FALSE";
					SetItemText(m_iCurSelctedItemIndex ,pSubItemInfo->m_iItemIndex,strData);	
					break;	
				}
			case EDITBOX:
				{
					pSubItemInfo->m_pWnd->GetWindowText(strData);
					SetItemText(m_iCurSelctedItemIndex ,pSubItemInfo->m_iItemIndex,strData);
					break;
				}
			case COMBOBOX:
				{
					iCurIndex = ((CComboBox*)pSubItemInfo->m_pWnd)->GetCurSel();
					if(iCurIndex != LB_ERR)
					{
						((CComboBox*)pSubItemInfo->m_pWnd)->GetLBText(iCurIndex,strData);
						SetItemText(m_iCurSelctedItemIndex ,pSubItemInfo->m_iItemIndex,strData);
					}
					break;
				}
			case LISTBOX:
				{
					iCurIndex = ((CListBox*)pSubItemInfo->m_pWnd)->GetCurSel();
					if(iCurIndex != LB_ERR)
					{
						((CListBox*)pSubItemInfo->m_pWnd)->GetText(iCurIndex,strData);
						SetItemText(m_iCurSelctedItemIndex ,pSubItemInfo->m_iItemIndex,strData);
					}
					break;
				}
			case DATECTRL:
				{
					int iSelect = (int)(CDateTimeCtrl*)pSubItemInfo->m_iItemIndex ;
					CTime tm ;
					((CDateTimeCtrl*)pSubItemInfo->m_pWnd)->GetTime(tm);
					int iHour = tm.GetHour();
					int iMinute = tm.GetMinute();
					strData.Format("%02d:%02d",iHour,iMinute);
					SetItemText(m_iCurSelctedItemIndex ,pSubItemInfo->m_iItemIndex,strData);

					break;
				}
			default: 
				break;
			}
		}
	}

}

BOOL CNeuListCtrl::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	SubItemControlsInfo *pSubItemInfo = NULL;
	ControlMessageInfo MessageInfo;
	if(nCode == HDN_TRACK)
	{
		AfxMessageBox("Error");
	}
	if (m_pControlPtrArray)
	{
		for(int i=0; i<m_pControlPtrArray->GetSize(); i++)
		{
			pSubItemInfo = (SubItemControlsInfo *) m_pControlPtrArray->GetAt(i);
			if (pSubItemInfo)
			{
				if(pSubItemInfo->m_pWnd)
				{
					if(pSubItemInfo->m_pWnd->GetDlgCtrlID() == (int) nID)
					{
						for(int ii =0 ;ii < pSubItemInfo->m_arrControlMessageInfo.GetSize() ;ii++)
						{
							MessageInfo = (ControlMessageInfo)pSubItemInfo->m_arrControlMessageInfo.GetAt(ii);
							if(MessageInfo.m_iMessageID == nCode)
							{
								MessageInfo.fun(GetParent(),pSubItemInfo->m_iItemIndex);
								break;
							}
						}
					}
				}
			}
		}
	}
	return CListCtrl::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CNeuListCtrl::AttachEvent_HandlerForItemControl(int iIndex,UINT unMessage,pEventHandler fun)
{
	if (!m_pControlPtrArray)
	{
		return;
	}		
	SubItemControlsInfo *pSubItemInfo = NULL;
	for(int i=0; i<m_pControlPtrArray->GetSize(); i++)
	{
		pSubItemInfo = (SubItemControlsInfo *) m_pControlPtrArray->GetAt(i);
		if (pSubItemInfo)
		{
			if(pSubItemInfo->m_iItemIndex == iIndex)
			{	
				ControlMessageInfo MessageInfo;
				MessageInfo.m_iMessageID = unMessage;
				MessageInfo.fun = fun;
				pSubItemInfo->m_arrControlMessageInfo.Add(MessageInfo);
				break;
			}
		}
	}
}

void CNeuListCtrl::AdjustControlsAccordingToHeaderWidth(HD_NOTIFY *pNotify)
{
	if(m_iCurSelctedItemIndex < 0 )
	{
	   return ;
	}
	int iItem = pNotify->iItem;
	int iWidth = pNotify->pitem->cxy;
	int iSubItem = 0 ; 
	CRect CtrlRect;
	CRect iconRect;
	SubItemControlsInfo *pSubItemControlsInfo = NULL;
	CString strData = "";
	BOOL bSetItem = FALSE ;
	int iIncreaseWidth = 0;
	if (m_pControlPtrArray)
	{
		for(int i=0; i<m_pControlPtrArray->GetSize(); i++)
		{
			pSubItemControlsInfo = (SubItemControlsInfo *) m_pControlPtrArray->GetAt(i);

			if(pSubItemControlsInfo)
			{
				GetSubItemRect(m_iCurSelctedItemIndex,pSubItemControlsInfo->m_iItemIndex,LVIR_LABEL,CtrlRect);
				GetSubItemRect(m_iCurSelctedItemIndex,pSubItemControlsInfo->m_iItemIndex,LVIR_ICON,iconRect);
			
				if(pSubItemControlsInfo->m_iItemIndex == iItem)
				{
					bSetItem = TRUE;
					if(iItem == 0)
					{
						iIncreaseWidth = iWidth - (CtrlRect.Width()+iconRect.right);
					}
					else
					{
						iIncreaseWidth = iWidth - CtrlRect.Width();
					}
				}
				else
				{
					bSetItem = TRUE;
					CtrlRect.left +=iIncreaseWidth;
				}
				CtrlRect.right += iIncreaseWidth;
		
				if(pSubItemControlsInfo->m_pWnd)
				{
					if(bSetItem)
					{
						pSubItemControlsInfo->m_pWnd->MoveWindow(&CtrlRect);
					}
				}
				strData = GetItemText(m_iCurSelctedItemIndex,pSubItemControlsInfo->m_iItemIndex);		
				switch(pSubItemControlsInfo->m_enControlType)
				{
					case CHECKBOX:
						{
							strData = ((CButton*)pSubItemControlsInfo->m_pWnd)->GetCheck()?"TRUE":"FALSE";
							SetItemText(m_iCurSelctedItemIndex ,pSubItemControlsInfo->m_iItemIndex,strData);	
							break;	
						}	
					case EDITBOX:
						{
							pSubItemControlsInfo->m_pWnd->SetWindowText(strData);
							break;
						}
					case COMBOBOX:
						{
						   ((CComboBox*)pSubItemControlsInfo->m_pWnd)->SelectString(-1,strData);
						   break;
						}
					case LISTBOX:
						{
						   ((CListBox*)pSubItemControlsInfo->m_pWnd)->SelectString(-1,strData);
						   CtrlRect.bottom += (((CListBox*)pSubItemControlsInfo->m_pWnd)->GetCount ()-1)*((CListBox*)pSubItemControlsInfo->m_pWnd)->GetItemHeight(0);
						   pSubItemControlsInfo->m_pWnd->MoveWindow(&CtrlRect);
							break;
						}
					case DATECTRL:
						{
							if(!strData.IsEmpty())
							{
								CTime tm = StrToTime(strData);
								((CDateTimeCtrl*)pSubItemControlsInfo->m_pWnd)->SetTime(&tm);
							}
							else
							{
								CTime tm(2014,1,1,0,0,0);
								((CDateTimeCtrl*)pSubItemControlsInfo->m_pWnd)->SetTime(&tm);
							}
							pSubItemControlsInfo->m_pWnd->MoveWindow(&CtrlRect);
						}
						break;
					default: 
						break;
				}
			}
		}
	}
	EnableControls(TRUE);
	ShowControls(TRUE);
	Invalidate();
}

int CNeuListCtrl::ControlIndexDuplicating(int iIndex)
{
	if (!m_pControlPtrArray)
	{
		return -1;
	}
	SubItemControlsInfo *pInfo = NULL;
	for(int i=0; i<m_pControlPtrArray->GetSize (); i++)
	{
		pInfo = (SubItemControlsInfo *) m_pControlPtrArray->GetAt (i);
		if (pInfo)
		{
			if(pInfo->m_iItemIndex == iIndex)
			{
				return i;
			}
		}
	}
	return -1;
}

void CNeuListCtrl::ReleaseControls()
{
	if (!m_pControlPtrArray)
	{
		return;
	}
	for(int i=0; i<m_pControlPtrArray->GetSize(); i++)
	{
		DetachControl(i);
	}
	if (m_pControlPtrArray)
	{
		delete m_pControlPtrArray;//20140313 dongfubao
		m_pControlPtrArray = NULL;
	}
	m_iCurSelctedItemIndex = -1 ;
	m_iControlIDCounter = 786 ;
}

BOOL CNeuListCtrl::DetachControl(int index)
{
	if (!m_pControlPtrArray)
	{
		return FALSE;
	}
	SubItemControlsInfo *pInfo = NULL;
	pInfo = (SubItemControlsInfo *)m_pControlPtrArray->GetAt(index);
	if(pInfo)
	{
		if(pInfo->m_pWnd)
		{
			pInfo->m_pWnd->DestroyWindow();
			pInfo->m_pWnd->m_hWnd = NULL;
			delete pInfo->m_pWnd;
			pInfo->m_pWnd = NULL;
		}
		delete pInfo;
		m_pControlPtrArray->RemoveAt(index);
		return TRUE;
	}
	return FALSE;
}

void CNeuListCtrl::SetControlBKColor(int index ,COLORREF col)
{
	if (m_pControlPtrArray)
	{
		SubItemControlsInfo *pInfo = NULL;
		for(int i=0; i<m_pControlPtrArray->GetSize(); i++)
		{
			pInfo = (SubItemControlsInfo *) m_pControlPtrArray->GetAt (i);
			if (pInfo)
			{
				if(pInfo->m_iItemIndex == index)
				{
					pInfo->m_BKColor = col;
				}
			}
		}
	}	
	Invalidate();
}

void CNeuListCtrl::SetRowHeigt(int _iHeight)
{
	if(m_pMainList != NULL)
	{
		m_pMainList->DeleteObject();
		m_pMainList->CreatePointFont(_iHeight * 4,"Arial");
		SetFont(m_pMainList);
	}
	else
	{
        m_pMainList = new CFont() ;
		if (m_pMainList != NULL)
		{
			m_pMainList->CreatePointFont(_iHeight * 4,"Arial");
			SetFont(m_pMainList);
		} 
	}

}

void CNeuListCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = CDRF_DODEFAULT;
	NMLVCUSTOMDRAW *lplvdr=(NMLVCUSTOMDRAW*)pNMHDR;
	if (lplvdr != NULL)
	{
		NMCUSTOMDRAW &nmcd = lplvdr->nmcd;
		switch(lplvdr->nmcd.dwDrawStage)//判断状态
		{
		case CDDS_PREPAINT:
			{
				*pResult = CDRF_NOTIFYITEMDRAW;
				break;
			}

		case CDDS_ITEMPREPAINT://如果为画ITEM之前就要进行颜色的改变
			{
				COLORREF ItemColor;
				if(MapItemColor.Lookup((unsigned long &)nmcd.dwItemSpec, ItemColor))
					//根据在SetItemColor(DWORD iItem, COLORREF color) 设置的//ITEM号和COLORREF 在摸板中查找，然后进行颜色赋值。
				{
					//lplvdr->clrText = RGB(0,0,0);//ItemColor;
					lplvdr->clrTextBk = ItemColor;
					*pResult = CDRF_DODEFAULT;
				}
			}
			break;
		default:
			break;
		}
	}
}

void CNeuListCtrl::SetItemColor(DWORD iItem, COLORREF color)
{
	MapItemColor.SetAt(iItem, color);//设置某行的颜色。
	this->RedrawItems(iItem, iItem);//重新染色
	this->SetFocus();//设置焦点
	UpdateWindow();
}

void CNeuListCtrl::OnCbnSelchangeCombo()//获取Combox内容
{
	if (m_pControlPtrArray)
	{
		CString strTemp ;
		int iType = -1 ;
		SubItemControlsInfo *pSubItemInfo = NULL;
		for(int i=0; i<m_pControlPtrArray->GetSize(); i++)
		{
		  pSubItemInfo = (SubItemControlsInfo *) m_pControlPtrArray->GetAt(i);
		  if (pSubItemInfo)
		  {
			  if(pSubItemInfo->m_enControlType == COMBOBOX)
			  {
				  int iType = ((CComboBox*)pSubItemInfo->m_pWnd)->GetCurSel();
				  ((CComboBox*)pSubItemInfo->m_pWnd)->GetLBText(iType,strTemp);
				  int iValue = StrToInt(strTemp)-1;
				  ::PostMessage(m_hParent, MESSAGE_SELECT, iValue, m_iCurSelctedItemIndex);
			  }   
		  }
		}
	}
}

void CNeuListCtrl::ResetContent()
{
	if (m_pControlPtrArray)
	{
		SubItemControlsInfo *pSubItemInfo = NULL;

		for(int i=0; i<m_pControlPtrArray->GetSize(); i++)
		{
			pSubItemInfo = (SubItemControlsInfo *) m_pControlPtrArray->GetAt(i);
			if (pSubItemInfo)
			{
			   ((CComboBox*)pSubItemInfo->m_pWnd)->ResetContent();
			}
		}
	}
}

void CNeuListCtrl::PreSubclassWindow()
{
	ASSERT(GetHeaderCtrl() != NULL);

	CHeaderCtrl const *pHeader = GetHeaderCtrl();
	if (pHeader != NULL)
	{
		m_pHeaderCtrl = new CHeaderCtrlClEX();
		if (m_pHeaderCtrl)
		{
			m_pHeaderCtrl->SubclassWindow(pHeader->GetSafeHwnd());
		}
	}
	else
	{
		m_pHeaderCtrl = NULL;
	}
	CListCtrl::PreSubclassWindow();	
}

int CNeuListCtrl::GetColumnCount() const
{
	return GetHeaderCtrl()->GetItemCount();
}

BOOL CNeuListCtrl::DeleteAllColumns()
{
	while (GetColumnCount() > 0)
	{
		DeleteColumn(0);
	}			
	if (m_pHeaderCtrl)
	{
		m_pHeaderCtrl->m_HChar.RemoveAll();
	}

	return TRUE;
}

BOOL CNeuListCtrl::DeleteColumn(int nCol)
{
	const BOOL blRet = CListCtrl::DeleteColumn(nCol);
	if (blRet && m_pHeaderCtrl)
	{
		m_pHeaderCtrl->m_HChar.RemoveAt(nCol);
	}
	return blRet;
}

int CNeuListCtrl::InsertColumn( _In_ int nCol, _In_z_ LPCTSTR lpszColumnHeading, _In_ int nFormat /*= LVCFMT_LEFT*/, _In_ int nWidth /*= -1*/, _In_ int nSubItem /*= -1*/ )
{
	if (m_pHeaderCtrl)
	{
		m_pHeaderCtrl->m_HChar.Add(lpszColumnHeading);
		if (nFormat == LVCFMT_LEFT)
		{
			m_pHeaderCtrl->m_Format += "0";
		}
		else if (nFormat == LVCFMT_CENTER)
		{
			m_pHeaderCtrl->m_Format += "1";
		}
		else if (nFormat == LVCFMT_RIGHT)
		{
			m_pHeaderCtrl->m_Format += "2";
		}
		else
		{
			m_pHeaderCtrl->m_Format += "1";
		}
	}

	return CListCtrl::InsertColumn(nCol, lpszColumnHeading, nFormat, nWidth, nSubItem);
}

void CNeuListCtrl::SetHeaderHeight( float Height )
{
	if (m_pHeaderCtrl)
	{
		m_pHeaderCtrl->m_Height = Height;
		m_pHeaderCtrl->Invalidate();
	}

}

void CNeuListCtrl::SetHeaderFontHW( int nHeight, int nWith )
{
	if (m_pHeaderCtrl)
	{
		m_pHeaderCtrl->m_fontHeight = nHeight;
		m_pHeaderCtrl->m_fontWith = nWith;
		m_pHeaderCtrl->Invalidate();
	}
}

int CNeuListCtrl::GetItemTextEx( int nItem, int nSubItem, LPTSTR lpszText, int nLen ) const
{
	return GetItemText(nItem, nSubItem, lpszText, nLen);
}

CString CNeuListCtrl::GetItemTextEx( int nItem, int nSubItem ) const
{
	return GetItemText(nItem, nSubItem);
}

void CNeuListCtrl::MoveControlToFocusItem( int _iIndex )
{		
	int iIndex = GetTopIndex();
	int nLast = iIndex + GetCountPerPage();

	POSITION pos = GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		while (pos)
		{
			int nItem = GetNextSelectedItem(pos);
			SetItemColor(nItem,COLOR_CANCEL);//20140411
			SetItemState(nItem, 0, LVIS_SELECTED|LVIS_FOCUSED|LVIS_ACTIVATING);
		}
	}

	if (_iIndex >= 0)
	{
		m_iCurSelctedItemIndex = _iIndex;

		EnsureVisible(_iIndex,FALSE);
		SetItemState(_iIndex, LVIS_SELECTED|LVIS_FOCUSED|LVIS_ACTIVATING, LVIS_SELECTED|LVIS_FOCUSED|LVIS_ACTIVATING);
		MapControlsForSubItems();
		ShowControls(TRUE);
		EnableControls(TRUE); 
	}
	else
	{
		m_iCurSelctedItemIndex = -1;
		ShowControls(FALSE);
		EnableControls(FALSE); 
	}
}

BOOL CNeuListCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	ShowControls(FALSE);
	CListCtrl::OnMouseWheel(nFlags, zDelta, pt);
	m_iCurSelctedItemIndex = -1;
	return TRUE;
}

void CNeuListCtrl::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	CListCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
	int iCount = GetItemCount();
	if (iCount < 2)
	{
		return;
	}

	if ((nChar < 0x3a && nChar > 0x30) || (nChar < 0x6a && nChar > 0x60))
	{
		int iNum = nChar > 0x3a ? nChar - 0x60 : nChar - 0x30;
		if (iCount > iNum)
		{
			if (iNum > 0)
			{
				iNum--;
			}
			MoveControlToFocusItem(iNum);	
			ShowControls(FALSE);
			return;
		}
		return;
	}

	switch(nChar)
	{
	case VK_DOWN:
		{
			if (iCount == m_iCurSelctedItemIndex + 1)
			{
				MoveControlToFocusItem(0);	
				return;
			}
		}
		break;
	case VK_UP:
		if (m_iCurSelctedItemIndex == 0)
		{
			return;
		}
		break;
	default:
		return;
	}

	POSITION pos = GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nItemNew = -1;
		nItemNew = GetNextSelectedItem(pos);
		if (nItemNew == m_iCurSelctedItemIndex)
		{
			if (nChar == VK_UP)
			{
				nItemNew--;
			}
		}
		m_iCurSelctedItemIndex = nItemNew;
		MoveControlToFocusItem(nItemNew);			
	}
}

void CNeuListCtrl::SetLimitTextLength( int _iColumn, int _iLength )
{
	if (!m_pControlPtrArray)
	{
		return;
	}		
	SubItemControlsInfo *pSubItemInfo = NULL;
	for(int i=0; i<m_pControlPtrArray->GetSize(); i++)
	{
		pSubItemInfo = (SubItemControlsInfo *) m_pControlPtrArray->GetAt(i);
		if (pSubItemInfo)
		{
			if(pSubItemInfo->m_iItemIndex == _iColumn)
			{	
				if (pSubItemInfo->m_enControlType == EDITBOX)
				{
					((CEdit*)pSubItemInfo->m_pWnd)->SetLimitText(_iLength);
				}				
				break;
			}
		}
	}
}

int CNeuListCtrl::GetCurSelectedItem()
{
	return m_iCurSelctedItemIndex;
}

void CNeuListCtrl::SetCurSelectedItem( int _iCurSelected )
{
	m_iCurSelctedItemIndex = _iCurSelected;
}

void CNeuListCtrl::SetParentHwnd( HWND _hWndParent )
{
	m_hParent = _hWndParent;
}
