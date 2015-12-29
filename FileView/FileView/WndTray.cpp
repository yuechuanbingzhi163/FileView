#include "StdAfx.h"
#include "WndTray.h"
#include "MainFrameWork.h"

CWndTray::CWndTray(void)
{
}


CWndTray::~CWndTray(void)
{
}

void CWndTray::Notify( TNotifyUI &msg )
{
	__super::Notify(msg);

	if (msg.sType == DUI_MSGTYPE_CLICK)
	{
		if (msg.pSender->GetName() == _T("btn_user_tool"))
		{
			
		}
		else if (msg.pSender->GetName() == _T("btn_mgr_tool"))
		{
			OnBtnMgrTool();
		}
		else if (msg.pSender->GetName() == _T("btn_quit"))
		{
			Close();
            CMainFrameWork::SingleInstance()->Exit_App();
		}
	}
}

LRESULT CWndTray::OnCreate( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	__super::OnCreate(uMsg, wParam, lParam, bHandled);

	CListUI *pList = static_cast<CListUI*>(m_PaintManager.FindControl(_T("menulist")));
	pList->GetHeader()->SetVisible(false);

	return 0;
}

LRESULT CWndTray::OnKillFocus( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	if( (HWND)wParam == m_hWnd ) bHandled = FALSE;
	else {
		Close();
		bHandled = FALSE;
	}
	return 0;
}

void CWndTray::OnBtnMgrTool()
{    
    Close();
}
    



