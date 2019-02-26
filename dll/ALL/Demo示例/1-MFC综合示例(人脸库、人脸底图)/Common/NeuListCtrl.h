#if !defined(AFX_NEULISTCTRL_H__B99644D0_C056_4A16_AF1C_06E2F3321668__INCLUDED_)
#define AFX_NEULISTCTRL_H__B99644D0_C056_4A16_AF1C_06E2F3321668__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NeuListCtrl.h : header file
//

#define MESSAGE_NONE 909090
#define MESSAGE_SELECT 90
#define COLOR_CANCEL RGB(255,255,255)

#include <afxcoll.h>
#include <afxtempl.h>
#include "HeaderCtrlClEX.h"
//#include "../Config/CLS_VirtualBasePage.h"

enum enCONTROLTYPE { EDITBOX,COMBOBOX,LISTBOX,CHECKBOX,BUTTON,DATECTRL,NONE} ;

typedef void (CALLBACK *pEventHandler)(LPVOID lpVoid,int iIndex);
typedef void (CALLBACK *pClickItem)(LPVOID lpVoid, int _iIndex, int _iSubItem);//点击行事件回调

struct ControlMessageInfo
{
	int m_iMessageID;
	pEventHandler fun;
	ControlMessageInfo()
	{
		m_iMessageID = MESSAGE_NONE;
	}
};
struct SubItemControlsInfo
{
	enCONTROLTYPE m_enControlType;
	int m_iItemIndex;
	CWnd * m_pWnd;
	COLORREF m_BKColor;
	SubItemControlsInfo()
	{
		m_enControlType = NONE;
		m_iItemIndex = -1;
		m_pWnd = NULL;
		m_BKColor = RGB(255,255,255);
	}
	CArray<ControlMessageInfo,ControlMessageInfo> m_arrControlMessageInfo;
};

/////////////////////////////////////////////////////////////////////////////
// CNeuListCtrl window

class CNeuListCtrl : public CListCtrl
{
// Construction
public:
	CNeuListCtrl();

// Attributes
public:

// Operations
public:
	CMap<DWORD , DWORD& , COLORREF , COLORREF&> MapItemColor;
public:
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeCombo();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNeuListCtrl)
	public:
	virtual BOOL DestroyWindow();
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void AttachEvent_HandlerForItemControl(int iIndex,UINT unMessage,pEventHandler fun);
	void ShowControls(BOOL bShow);//控制list ctrl上控件的显示不显示
	void EnableControls(BOOL bEnable);//控制list ctrl上控件的使能不使能
	void SetControlBKColor(int index ,COLORREF col);
	virtual ~CNeuListCtrl();
	BOOL Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID );
	void SetRowHeigt(int _iHeight);//设置行高
	int m_iRowHeight;   //行高
	CHeaderCtrlClEX    *m_pHeaderCtrl;
	void SetItemColor(DWORD iItem, COLORREF color);
	CString GetItemTextEx(int nItem ,int nSubItem ) const;
	// Generated message map functions
protected:
	CString m_strMinVal;
	//{{AFX_MSG(CNeuListCtrl)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CFont m_fnControl;//控件字体
	CFont *m_pMainList;//设置行高

	DECLARE_MESSAGE_MAP()
protected:
	CPtrArray *m_pControlPtrArray;
private:
	BOOL DetachControl(int index);
	int ControlIndexDuplicating(int iIndex);
	int m_iCurSelctedItemIndex;//当前选择的行
	int m_iSubItem;
	int m_iControlIDCounter;
	pClickItem m_pClickItemCallBack;
	void *m_pClickData;

	HWND m_hParent;

	BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	/************************************************************************
	Function：     StrToTime
	Description：  将字符串转换为时间.
	Input：        
	Output：       
	Return：
	Others：           
	************************************************************************/
	CTime StrToTime(CString &cstrTime);

public:
	void SetParentHwnd(HWND _hWndParent);

	/************************************************************************
	Function：     SetCurSelectedItem
	Description：  设置当前选中项
	Input：  _iCurSelected 当前选中项      
	Output：       
	Return：
	Others：           
	************************************************************************/
	void SetCurSelectedItem(int _iCurSelected);
	/************************************************************************
	Function：     GetCurSelectedItem
	Description：  获取当前选中项.
	Input：        
	Output：       
	Return：当前选中项
	Others：           
	************************************************************************/
	int GetCurSelectedItem();

	/************************************************************************
	Function：     SetHeaderHeight
	Description：  设置表头字高
	Input：        
	Output：       
	Return：
	Others：           
	************************************************************************/
	void SetHeaderHeight(float Height);

	/************************************************************************
	Function：     PreSubclassWindow
	Description：  用于给listctrl表头发消息
	Input：        
	Output：       
	Return：
	Others：           
	************************************************************************/
	virtual void PreSubclassWindow();

	/************************************************************************
	Function：     AdjustControlsAccordingToHeaderWidth
	Description：  调整控件的宽度适应listctrl的某一项宽度
	Input：        
	Output：       
	Return：
	Others：           
	************************************************************************/
	void AdjustControlsAccordingToHeaderWidth(HD_NOTIFY * pNotify);

	/************************************************************************
	Function：     GetItemTextEx
	Description：  获取某一项的内容
	Input：        
	Output：       
	Return：
	Others：           
	************************************************************************/
	int GetItemTextEx(int nItem ,int nSubItem ,LPTSTR lpszText ,int nLen) const;

	/************************************************************************
	Function：     MapControlsForSubItems
	Description：  将控件上的值设置到list ctrl上
	Input：        
	Output：       
	Return：
	Others：           
	************************************************************************/
	void MapControlsForSubItems();

	/************************************************************************
	Function：     AddToControlsData
	Description：  给控件添加数据
	Input：        
	Output：       
	Return：
	Others：           
	************************************************************************/
	BOOL AddToControlsData(int iIndex, CString strData);

	/************************************************************************
	Function：     GetAndDisplayControlsData
	Description：  获取控件上的值，显示在list ctrl上
	Input：        
	Output：       
	Return：
	Others：           
	************************************************************************/
	void GetAndDisplayControlsData();

	/************************************************************************
	Function：     ResetContent
	Description：  清空combox内容
	Input：        
	Output：       
	Return：
	Others：           
	************************************************************************/
	void ResetContent();

	/************************************************************************
	Function：     ReleaseControls
	Description：  释放控件
	Input：        
	Output：       
	Return：
	Others：           
	************************************************************************/
	void ReleaseControls();

	/************************************************************************
	Function：     SetHeaderFontHW
	Description：  //设置表头字体大小
	Input：        
	Output：       
	Return：
	Others：           
	************************************************************************/
	void SetHeaderFontHW(int nHeight,int nWith); 

	/************************************************************************
	Function：     SetItemControl
	Description：  在listctrl上添加combox等控件
	Input：        
	Output：       
	Return：
	Others：           
	************************************************************************/
	void SetItemControl(enCONTROLTYPE enControlType,int iIndex);//

	/************************************************************************
	Function：     DeleteColumn
	Description： 删除列
	Input：        
	Output：       
	Return：
	Others：           
	************************************************************************/
	BOOL DeleteColumn(int nCol);

	/************************************************************************
	Function：     InsertColumn
	Description： 重载插入列
	Output：       
	Return：
	Others：           
	************************************************************************/
	int InsertColumn(_In_ int nCol, _In_ const LVCOLUMN* pColumn);
	int InsertColumn(_In_ int nCol, _In_z_ LPCTSTR lpszColumnHeading,
		_In_ int nFormat = LVCFMT_LEFT, _In_ int nWidth = -1, _In_ int nSubItem = -1);

	/************************************************************************
	Function：     DeleteAllColumns
	Description：  删除所有列
	Input：        
	Output：       
	Return：
	Others：           
	************************************************************************/
	BOOL DeleteAllColumns();

	/************************************************************************
	Function：     GetColumnCount
	Description：  得到列数
	Input：        
	Output：       
	Return：
	Others：           
	************************************************************************/
	int GetColumnCount() const;

	/************************************************************************
	Function：     MoveControlToFocusItem
	Description：  将要显示的控件移动到指定行
	Input：    _iIndex    指定行
	Output：       
	Return：
	Others：           
	************************************************************************/
	void MoveControlToFocusItem(int _iIndex);

	/************************************************************************
	Function：     OnMouseWheel
	Description：  处理滚轮事件
	Input：    
	Output：       
	Return：
	Others：           
	************************************************************************/
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

	void SetClickItemCallBack(pClickItem _callbackFunc, void* _pData)
	{
		m_pClickItemCallBack = _callbackFunc;
		m_pClickData = _pData;
	};
	/************************************************************************
	Function：     SetClickItemCallBack
	Description：  处理点击表格行事件
	************************************************************************/

	/************************************************************************
	Function：     SetLimitTextLength
	Description：  限制Edit输入长度
	Input：		   _iColumn:列号， _iLength:限制长度
	Output：       
	Return：
	Others：           
	************************************************************************/
	void SetLimitTextLength(int _iColumn, int _iLength);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEULISTCTRL_H__B99644D0_C056_4A16_AF1C_06E2F3321668__INCLUDED_)
