#ifndef _MESSAGEMANAGER_H
#define _MESSAGEMANAGER_H
#include <list>
using namespace std;

//100->200 解决参数改变消息不进的问题 20161229
//20170424 解决热度图消息参数覆盖的，需要使用demo 转发的问题 内存过大申请失败的问题
#define		MESSAGE_MEMORY_SIZE		12000	
#define		MESSAGE_MEMORY_COUNT	100

class CLS_MessageManager
{
public:
	static CLS_MessageManager* Instance();
	static void Destroy();
	void* MallocMemory(int _iSize);
	void FreeMemory(void* _pMemory);
	
private:
	CRITICAL_SECTION m_csList;
	CLS_MessageManager(void);
	~CLS_MessageManager(void);

private:
	static CLS_MessageManager* s_pInstance;
	list<void*> m_lstFreeMemory;
};
#endif
