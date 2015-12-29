#pragma once
#include "stdafx.h"

class CWndProgressFlash : public WindowImplBase
{
public:
	CWndProgressFlash();
	~CWndProgressFlash(void);

	//void OnFinalMessage( HWND hWnd ) { __super::OnFinalMessage(hWnd); delete this; };
	CDuiString GetSkinFolder() { return _T("..\\third\\res"); };
	CDuiString GetSkinFile() { return _T("CWndProgressFlash.xml"); };
	LPCTSTR GetWindowClassName() const { return _T("CWndProgressFlash"); };

#ifdef UI_USE_ZIP
	UILIB_RESOURCETYPE GetResourceType() const { return UILIB_ZIPRESOURCE;};
	LPCTSTR GetResourceID() const { return  MAKEINTRESOURCE(IDR_ZIPRES1);};
#endif // UI_USE_ZIP

	void Notify( TNotifyUI &msg );
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);	

	void Init(HANDLE hThread);

private:
	HANDLE m_hThread;

    CControlUI *m_pMainControl;
	long m_nTimeCount;
};

