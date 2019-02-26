#pragma once

#define IS_DROW	0	//»­ºÚ
#define NO_DROW	1	//²»»­ºÚ
// CDlgPicPanel dialog

class CDlgPicPanel : public CDialog
{
	DECLARE_DYNAMIC(CDlgPicPanel)
private:
	
	HBRUSH       m_brushMainBack;   //±³¾°ÑÕÉ«»­Ë¢
	int			 m_iIndex;			//Ë÷ÒýºÅ
	POINT		 m_ptDown;			//Êó±ê°´ÏÂÎ»ÖÃ

public:
	CDlgPicPanel(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgPicPanel();

// Dialog Data
	enum { IDD = IDD_DIALOG_PIC_PANEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	void SetPanelID(int nID);
	int GetPanelID();

	int m_iISDrawBlack;
};
