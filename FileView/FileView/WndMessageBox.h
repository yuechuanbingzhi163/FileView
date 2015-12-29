#pragma once
#include "stdafx.h"

enum MessagBoxStyle
{
    MESSAGEBOX_STYPE_OK_CANCEL,
    MESSAGEBOX_STYPE_OK
};

class CWndMessageBox : public WindowImplBase
{
public:
	CWndMessageBox(LPCTSTR lpTip,MessagBoxStyle ms = MESSAGEBOX_STYPE_OK, DWORD dwTipColor = 0xffff0000);
	~CWndMessageBox(void);

	void OnFinalMessage( HWND hWnd );;
	CDuiString GetSkinFolder() { return _T("..\\third\\res"); };
	CDuiString GetSkinFile() { return _T("CWndMessageBox.xml"); };
	LPCTSTR GetWindowClassName() const { return _T("CWndMessageBox"); };

#ifdef UI_USE_ZIP
	UILIB_RESOURCETYPE GetResourceType() const { return UILIB_ZIPRESOURCE;};
	LPCTSTR GetResourceID() const { return  MAKEINTRESOURCE(IDR_ZIPRES1);};
#endif // UI_USE_ZIP

	void Notify( TNotifyUI &msg );
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	void SetIsFinalMessageValid(bool b);

private:
    string_t m_strMessageText;
    MessagBoxStyle m_MessageBox_Style;
    DWORD m_dwTipColor;

	bool m_IsFinalMessageValid;
};

