#pragma once
#include "CTreeDeviceNode.h"
#include "CWndProgressFlash.h"
#include "CListContainerElementLicense.h"

class CWndMgrTool : public WindowImplBase
{
public:
	CWndMgrTool(void);
	~CWndMgrTool(void);    

	void OnFinalMessage( HWND hWnd ) { __super::OnFinalMessage(hWnd); delete this; };
	CDuiString GetSkinFolder() { return _T("..\\third\\res"); };
	CDuiString GetSkinFile() { return _T("CWndMgrTool.xml"); };
	LPCTSTR GetWindowClassName() const { return _T("CWndFileVIew"); };

#ifdef UI_USE_ZIP
	UILIB_RESOURCETYPE GetResourceType() const { return UILIB_ZIPRESOURCE;};
	LPCTSTR GetResourceID() const { return  MAKEINTRESOURCE(IDR_ZIPRES1);};
#endif // UI_USE_ZIP

	void Notify( TNotifyUI &msg );
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);    


	void OnBtnClose(TNotifyUI &msg);

	void OpenVdFile(LPCTSTR lpPath);

	DUI_DECLARE_MESSAGE_MAP()
private:
	CWndProgressFlash *m_pProgressFlash;
	HANDLE  m_hThreadCommon;


private:
	void *m_pFs;
};

