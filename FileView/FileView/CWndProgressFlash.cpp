#include "StdAfx.h"
#include "CWndProgressFlash.h"

CWndProgressFlash::CWndProgressFlash():m_hThread(NULL)
{
    
}

CWndProgressFlash::~CWndProgressFlash(void)
{
}

void CWndProgressFlash::Notify( TNotifyUI &msg )
{
	__super::Notify(msg);

	if (msg.sType == DUI_MSGTYPE_CLICK)
	{
		
	}
	else if (msg.sType == DUI_MSGTYPE_TIMER)
	{
		if (msg.pSender == m_pMainControl)
		{
			m_nTimeCount++;
			m_nTimeCount %= 40;

			char szTemp[10] = {0};
			itoa(m_nTimeCount, szTemp, 10);

			string strFileName;
			strFileName = "spinner_";
			strFileName += szTemp;
			strFileName += ".png";

			m_pMainControl->SetBkImage(strFileName.c_str());
		}
	}
}

LRESULT CWndProgressFlash::OnClose( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	m_PaintManager.KillTimer(m_pMainControl);

	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}

LRESULT CWndProgressFlash::OnCreate( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	__super::OnCreate(uMsg, wParam, lParam, bHandled);

    m_pMainControl = static_cast<CControlUI*>(m_PaintManager.FindControl("lab_pic"));

	m_nTimeCount = 0;

	m_PaintManager.SetTimer(m_pMainControl, 0x01112, 50);	

	ResumeThread(m_hThread);

	return 0;
}

void CWndProgressFlash::Init( HANDLE hThread )
{
	m_hThread = hThread;
}




