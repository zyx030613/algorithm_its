#pragma once


// PSEConfig dialog

class PSEConfig : public CDialog
{
	DECLARE_DYNAMIC(PSEConfig)

public:
	PSEConfig(CWnd* pParent = NULL);   // standard constructor
	virtual ~PSEConfig();

// Dialog Data
	enum { IDD = IDD_DLG_CFG_PSE_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
