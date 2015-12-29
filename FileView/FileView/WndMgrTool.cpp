#include "StdAfx.h"
#include "WndMgrTool.h"
#include "MainFrameWork.h"

void SetClipBoardSelfData(LPCTSTR lpData);

DUI_BEGIN_MESSAGE_MAP(CWndMgrTool, CNotifyPump)
    DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK,OnClick)   
	DUI_ON_CLICK_CTRNAME("btn_close", OnBtnClose)
 DUI_END_MESSAGE_MAP()


CWndMgrTool::CWndMgrTool(void)
{
	m_pFs = NULL;
	m_pProgressFlash = NULL;
}

CWndMgrTool::~CWndMgrTool(void)
{
}

void CWndMgrTool::Notify( TNotifyUI &msg )
{
	__super::Notify(msg);

    if (msg.sType == DUI_MSGTYPE_CLICK)
    {
        
    }
	else if (msg.sType == DUI_MSGTYPE_HEADERCLICK)
	{
		
	}
    else if (msg.sType == DUI_MSGTYPE_MENU)
    {       
    //         CTreeNodeDevice *pNode = static_cast<CTreeNodeDevice*>(msg.pSender);
    //         TREENODETYPE nodeType = pNode->GetNodeType();

			 //if (nodeType == TREE_NODE_TYPE_CLOUD_ACCOUNT_INFO)
			 //{
				// CMenuWnd *pMenu = new CMenuWnd;
				// DuiLib::CPoint point = msg.ptMouse;
				// ClientToScreen(m_hWnd, &point);
				// pMenu->Init(NULL, _T("commonmenu.xml"), point, &m_PaintManager);

				// CMenuUI *rootMenu = pMenu->GetMenuUI();					 
				// 
				// CMenuElementUI *pLogoutItem = new CMenuElementUI;
				// pLogoutItem->SetName(_T("menu_item_logout"));
				// pLogoutItem->SetText(_T("注销"));				 
				// rootMenu->Add(pLogoutItem);			

				// pMenu->ResizeMenu();			                    
			 //}
    }
    else if (msg.sType == DUI_MSGTYPE_ITEMDBCLICK)
    {
         
    }
    else if (msg.sType == DUI_MSGTYPE_TIMER)
    {
       
    }
	else if (msg.sType == DUI_MSGTYPE_DRAG_PUT)
	{
		//if (StrCmp(msg.pSender->GetClass(), _T("CListContainerElementLicense")) == 0)
		//{
		//	m_pCurTransferLicenseListItem = static_cast<CListContainerElementLicense*>(msg.pSender);

		//	POINT pt = *((POINT*)msg.lParam);

		//	do 
		//	{
		//		RECT rcDeviceTree = m_pTreeViewShouQuanDevice->GetPos();
		//		if (!::PtInRect(&rcDeviceTree, pt))
		//		{
		//			break;
		//		}

		//		m_pCurTransferLicenseTreeNode = NULL;

		//		CTreeNodeDevice *pTreeNode = NULL;
		//		int nCount = m_pTreeViewShouQuanDevice->GetCount();
		//		for (int i=0; i<nCount; i++)
		//		{
		//			pTreeNode = static_cast<CTreeNodeDevice*>(m_pTreeViewShouQuanDevice->GetItemAt(i));
		//			rcDeviceTree = pTreeNode->GetPos();
		//			if (::PtInRect(&rcDeviceTree, pt))
		//			{
		//				m_pCurTransferLicenseTreeNode = pTreeNode;
		//				break;
		//			}
		//		}

		//		if (m_pCurTransferLicenseTreeNode == NULL)
		//		{
		//			break;
		//		}

		//		if (m_pCurTransferLicenseTreeNode->GetNodeType() == TREE_NODE_TYPE_CLOUD_ACCOUNT_ROOT ||
		//			m_pCurTransferLicenseTreeNode->GetNodeType() == TREE_NODE_TYPE_LOCAL_ROOT ||
		//			m_pCurTransferLicenseTreeNode->GetNodeType() == TREE_NODE_TYPE_NET_ROOT ||
		//			m_pCurTransferLicenseTreeNode->GetNodeType() == TREE_NODE_TYPE_DEVELOPER_INFO ||
		//			((m_pCurTransferLicenseTreeNode->GetNodeType() == TREE_NODE_TYPE_LOCK_INFO) && (m_pCurTransferLicenseTreeNode->GetLockIter()->szLockType == "remote")))
		//		{
		//			SSMessageBox(m_hWnd, "许可只可以在云账户和本地锁之间转移");
		//			break;
		//		}

		//		list<VLOCK>::iterator lockIter1= m_pCurTransferLicenseListItem->GetLockIter();
		//		list<VLOCK>::iterator lockIter2 = m_pCurTransferLicenseTreeNode->GetLockIter();

		//		if (lockIter1->szLockType == lockIter2->szLockType)
		//		{
		//			SSMessageBox(m_hWnd, "许可只可以在云账户和本地锁之间转移");
		//			break;
		//		}

		//		m_hShouQuanThread = CreateThread(NULL, 0, _ThreadTransferLicense3, this, CREATE_SUSPENDED, NULL);
		//		m_pProgressFlash = new CWndProgressFlash;
		//		m_pProgressFlash->Init(m_hShouQuanThread);
		//		m_pProgressFlash->Create(m_hWnd, NULL, UI_WNDSTYLE_FRAME, 0);
		//		m_pProgressFlash->CenterWindow();
		//		m_pProgressFlash->ShowModal();
		//		delete m_pProgressFlash;

		//		int k= 0;

		//	} while (false);			
		//}
	}
}

LRESULT CWndMgrTool::OnCreate( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	__super::OnCreate(uMsg, wParam, lParam, bHandled);    

	return 0;
}

LRESULT CWndMgrTool::OnSysCommand( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
    if (wParam == SC_CLOSE)
    {
        bHandled = TRUE;
        CMainFrameWork::SingleInstance()->UnInit();
        return 0;
    }
#if defined(WIN32) && !defined(UNDER_CE)
    BOOL bZoomed = ::IsZoomed(*this);
    LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
    if( ::IsZoomed(*this) != bZoomed )
    {
        CControlUI* pbtnMax     = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("maxbtn")));       // 最大化按钮
        CControlUI* pbtnRestore = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("restorebtn")));   // 还原按钮

        // 切换最大化按钮和还原按钮的状态
        if (pbtnMax && pbtnRestore)
        {
            pbtnMax->SetVisible(TRUE == bZoomed);       // 此处用表达式是为了避免编译器BOOL转换的警告
            pbtnRestore->SetVisible(FALSE == bZoomed);
        }

    }
#else
    LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
#endif
    return lRes;
}

LRESULT CWndMgrTool::HandleCustomMessage( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
    switch(uMsg)
    {	
    case WM_MENUCLICK:
        {
            CDuiString *strMenuName = (CDuiString *)wParam;
			if (*strMenuName == "menu_item_sync_cloud_infos")
			{
				
			}
			else if (*strMenuName == "menu_item_set_default_user")
			{
			}
			break;	
        }    
    }

    return __super::HandleCustomMessage(uMsg, wParam, lParam, bHandled);
}

void CWndMgrTool::OnBtnClose( TNotifyUI &msg )
{
	CMainFrameWork::SingleInstance()->UnInit();
}

void SetClipBoardSelfData( LPCTSTR lpData )
{
	::OpenClipboard(NULL);
	::EmptyClipboard();
	size_t  dataLen = _tcslen(lpData);
	HANDLE h = ::GlobalAlloc(GMEM_FIXED, (dataLen + 1) * sizeof(TCHAR));
	TCHAR *p = (TCHAR *)GlobalLock(h);
	StrCpy(p, lpData);
	SetClipboardData(CF_TEXT, h);
	::GlobalUnlock(h);
	::CloseClipboard();
}
