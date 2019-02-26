#ifndef _EZOOM_MANAGER_H
#define _EZOOM_MANAGER_H

#include "EZoomView.h"

#define MAX_EZOOM_NUM 4

class CLS_EZoomManager
{
public:
	static CLS_EZoomManager* Instance();
	static void Destroy();
	BOOL AddEZoom(unsigned int _uiConnID, RECT* _prcVideo);
	BOOL DeleteEZoom(unsigned int _uiConnID);
	BOOL DeleteAllEZoom();

private:
	CLS_EZoomManager();
	~CLS_EZoomManager(void);
	static CLS_EZoomManager* s_pInstance;
	CLS_EZoomView *m_pdlgEZoom[MAX_EZOOM_NUM];
};
#endif