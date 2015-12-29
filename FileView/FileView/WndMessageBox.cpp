#include "StdAfx.h"
#include "WndMessageBox.h"

CWndMessageBox::CWndMessageBox(LPCTSTR lpTip, MessagBoxStyle ms , DWORD dwTipColor)
{
    m_strMessageText = lpTip;
    m_MessageBox_Style = MESSAGEBOX_STYPE_OK;
    m_dwTipColor = dwTipColor;
	m_IsFinalMessageValid = false;
}


CWndMessageBox::~CWndMessageBox(void)
{
}

void CWndMessageBox::Notify( TNotifyUI &msg )
{
	__super::Notify(msg);

	if (msg.sType == DUI_MSGTYPE_CLICK)
	{
		if (msg.pSender->GetName() == _T("btn_close"))
		{
			Close(MB_OKCANCEL);
		}
        else if (msg.pSender->GetName() == _T("btn_ok"))
        {
            Close(MB_OK);
        }
        else if (msg.pSender->GetName() == _T("btn_cancel"))
        {
            Close(MB_OKCANCEL);
        }
	}
}

LRESULT CWndMessageBox::OnCreate( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	__super::OnCreate(uMsg, wParam, lParam, bHandled);

    CTabLayoutUI *pTabBtn = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("tab_btn")));
    CButtonUI *pBtnTip = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_tip")));

    if (m_MessageBox_Style == MESSAGEBOX_STYPE_OK)
    {
        pTabBtn->SelectItem(1);
    }
    else if (m_MessageBox_Style == MESSAGEBOX_STYPE_OK_CANCEL)
    {
        pTabBtn->SelectItem(0);
    }

    pBtnTip->SetText(m_strMessageText.c_str());
    pBtnTip->SetTextColor(m_dwTipColor);

	return 0;
}

void CWndMessageBox::OnFinalMessage( HWND hWnd )
{
	if (m_IsFinalMessageValid)
	{
		__super::OnFinalMessage(hWnd); 
		delete this;
	}	
}

void CWndMessageBox::SetIsFinalMessageValid( bool b )
{
	m_IsFinalMessageValid = b;
}



