#pragma once

class CWndTray : public WindowImplBase
{
public:
	CWndTray(void);
	~CWndTray(void);

	void OnFinalMessage( HWND hWnd ) { __super::OnFinalMessage(hWnd); delete this; };
	CDuiString GetSkinFolder() { return _T("..\\third\\res"); };
	CDuiString GetSkinFile() { return _T("CWndTray.xml"); };
	LPCTSTR GetWindowClassName() const { return _T("CWndTray"); };

#ifdef UI_USE_ZIP
	UILIB_RESOURCETYPE GetResourceType() const { return UILIB_ZIPRESOURCE;};
	LPCTSTR GetResourceID() const { return  MAKEINTRESOURCE(IDR_ZIPRES1);};
#endif // UI_USE_ZIP
	

	void Notify( TNotifyUI &msg );
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    void OnBtnMgrTool();
};

