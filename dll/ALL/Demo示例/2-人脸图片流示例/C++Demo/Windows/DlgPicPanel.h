#pragma once

#define IS_DROW	0	//����
#define NO_DROW	1	//������
// CDlgPicPanel dialog

class CDlgPicPanel : public CDialog
{
	DECLARE_DYNAMIC(CDlgPicPanel)
private:
	
	HBRUSH       m_brushMainBack;   //������ɫ��ˢ
	int			 m_iIndex;			//������
	POINT		 m_ptDown;			//��갴��λ��

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
