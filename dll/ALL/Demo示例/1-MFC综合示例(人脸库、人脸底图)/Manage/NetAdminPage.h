#ifndef _NETADMIN_WINDOW_H
#define _NETADMIN_WINDOW_H

#include "../BasePage.h"
#include "../Include/NETADMIN_INTERFACE.h"
#include "afxwin.h"
#include "../Common/SortListCtrl.h"

// CLS_NetAdminPage dialog
 
typedef struct
{
	CListCtrl* m_plvCtrl;
	int	m_iSubItem;	//ÁÐ
	int m_iSort; //1:ÉýÐò -1:½µÐò
}SORT_DATA;

class CLS_NetAdminPage : public CLS_BasePage
{
	DECLARE_DYNAMIC(CLS_NetAdminPage)

public:
	CLS_NetAdminPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLS_NetAdminPage();

// Dialog Data
	enum { IDD = IDD_DLG_MNG_ADMIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	virtual void OnLanguageChanged(int _iLanguage);
	static void __stdcall SeachNotify(PTDEVICE _pDevice);
	afx_msg void OnDestroy();
	afx_msg LRESULT OnSeachMsg(WPARAM wParam, LPARAM lParam);
	afx_msg void OnCbnSelchangeComboInterface();
	afx_msg void OnBnClickedBtnRefresh();
	afx_msg void OnCbnSelchangeComboDeviceType();
	afx_msg void OnNMDblclkListServer(NMHDR *pNMHDR, LRESULT *pResult);

private:
	void AddServer(PTDEVICE _pDevice);
	void Refresh();
	void Make_M7_PM(int _iPM, char* _pcID, char* _pcID1);
	void InitProductModel();
	CString GetProductModel(int _iModel);
	void InitDeviceType();
	CString GetDeviceType(int _iType);
	void UI_UpdateDialog();
	
public:
	static HWND s_hWnd;

private:
	map<int,char*>  m_mapProductModel;
	map<int,char*>  m_mapDeviceType;
	CSortListCtrl m_lvServer;
	CComboBox m_cboInterface;
	SORT_DATA m_tSortData;
	CComboBox m_cboDeviceType;
};

#endif
