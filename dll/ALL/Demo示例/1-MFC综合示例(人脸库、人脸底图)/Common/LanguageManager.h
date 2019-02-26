#ifndef _LANGUAGE_MANAGER_H
#define _LANGUAGE_MANAGER_H

class CLS_LanguageManager
{
public:
	static CLS_LanguageManager* Instance();
	static void Destroy();
	void SetLanguage(int _iLanguage);
	CString GetText(unsigned int _uIDResource);
	BOOL SetText(HWND _hDlg,int _iIDDlgItem,unsigned int _uIDResource);
	BOOL SetText(CWnd* pWnd,unsigned int _uIDResource);

private:
	CLS_LanguageManager(void);
	~CLS_LanguageManager(void);

private:
	static CLS_LanguageManager* s_pInstance;
	WORD m_wLanguage;
};

#endif

