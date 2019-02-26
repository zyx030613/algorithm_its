#ifndef _LOG_MANAGER_H
#define _LOG_MANAGER_H

#define LOG_TYPE_MIN				0
#define LOG_TYPE_SUCC		(LOG_TYPE_MIN+0)
#define LOG_TYPE_FAIL		(LOG_TYPE_MIN+1)
#define LOG_TYPE_MSG		(LOG_TYPE_MIN+2)
#define LOG_TYPE_MAX		(LOG_TYPE_MIN+3)

#define LOG_CAP_NONE				0
#define LOG_CAP_SUCC				0x1
#define LOG_CAP_FAIL				0x2
#define LOG_CAP_MSG					0x4
#define LOG_CAP_ADD_LIST			0x8
#define LOG_CAP_OUTPUT_STRING		0x10
#define LOG_CAP_WRITE_FILE			0x20
#define LOG_CAP_ALL					0xffffffff

class CLS_LogManager
{
public:
	static CLS_LogManager* Instance();
	static void Destroy();
	void SetListCtrl(CListCtrl* _plvLog){m_plvLog = _plvLog;}
	int SetFileName(char* _pcFileName,int _iLen);
	int SetLogCaps(unsigned int _uRemove,unsigned int _uAdd);
	unsigned int GetLogCaps(){return m_uCaps;}
	void AddLog(int _iLogType,const char* _pcHost, const char* _pcLogInfo,int _iLastError);

private:
	CLS_LogManager();
	~CLS_LogManager();

private:
	static CLS_LogManager* s_pInstance;
	CListCtrl* m_plvLog;
	FILE* m_pfLog;
	char m_cFileName[MAX_PATH];
	unsigned int m_uCaps;

};

#endif
