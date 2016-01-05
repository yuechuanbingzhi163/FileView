#include "StdAfx.h"
#include "MainFrameWork.h"
#include "WndTray.h"
#include "WndMgrTool.h"
#include <tlhelp32.h>
#include "LogicBaseImpl.h"

static UINT WM_TASKBAR_RESTART = 0;

static TCHAR szClassName[] = _T("CMainFrameWork");
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

extern HINSTANCE g_Hinstance;

CMainFrameWork * CMainFrameWork::m_SingleMainFrame = NULL;

CMainFrameWork::CMainFrameWork(void):m_pManagerTool(NULL)
{

}

void CMainFrameWork::Init()
{
    MyRegisterClass(g_Hinstance);
    InitMyClassInstance(g_Hinstance);

    //InitNotifyIconData();
}

void CMainFrameWork::UnInit()
{
    if (m_pManagerTool != NULL)
    {
        m_pManagerTool->ShowWindow(false);
        m_pManagerTool->Close(0);
    }

    //CMainFrameWork::m_SingleMainFrame->UnInitNotifyIconData();

    ::DestroyWindow(m_hWnd);
    PostQuitMessage(0);
}

CMainFrameWork::~CMainFrameWork(void)
{

}

CMainFrameWork * CMainFrameWork::SingleInstance()
{
	if (m_SingleMainFrame == NULL)
	{
		m_SingleMainFrame = new CMainFrameWork;	        

		WM_TASKBAR_RESTART =  ::RegisterWindowMessage(_T("TaskBarCreated"));		

		static destroy des;
	}

	return m_SingleMainFrame;
}

void CMainFrameWork::Exit_App()
{
    ::PostMessage(m_hWnd, WM_EXIT_APP, NULL, NULL); 
}

LRESULT CMainFrameWork::OnTaskBarRestart( UINT nMsg, WPARAM wParam, LPARAM lParam)
{
    InitNotifyIconData();

	return 0;
}

LRESULT CMainFrameWork::OnTrayIcon( UINT nMsg, WPARAM wParam, LPARAM lParam)
{
    if (LOWORD(lParam) == WM_RBUTTONUP)
    {
        ShowNotifyIconMenu();
    }
    else if (LOWORD(lParam) == WM_LBUTTONUP)
    {
        ShowManagerTool();
    }

    return 0;
}

void CMainFrameWork::InitNotifyIconData()
{
    ZeroMemory(&m_NotifyIconData, sizeof(NOTIFYICONDATA));
    m_NotifyIconData.cbSize = sizeof(NOTIFYICONDATA);
    m_NotifyIconData.hWnd = m_hWnd;
    m_NotifyIconData.uCallbackMessage = WM_NIDTIP;
    m_NotifyIconData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    m_NotifyIconData.hIcon = ::LoadIcon(g_Hinstance, MAKEINTRESOURCE(IDI_SMALL));
    m_NotifyIconData.uID = IDI_SMALL;
	sprintf_s(m_NotifyIconData.szTip, _T("%s"), _T("用户工具"));
    Shell_NotifyIcon(NIM_ADD, &m_NotifyIconData);
}

void CMainFrameWork::UnInitNotifyIconData()
{
    Shell_NotifyIcon(NIM_DELETE, &m_NotifyIconData);
}

void CMainFrameWork::ShowNotifyIconMenu()
{   

}

void CMainFrameWork::ShowManagerTool()
{
        m_pManagerTool = new CWndMgrTool;
        m_pManagerTool->Create(NULL, _T("用户工具"), WS_OVERLAPPEDWINDOW, 0);
        m_pManagerTool->CenterWindow();
        m_pManagerTool->ShowWindow();   		
}

ATOM CMainFrameWork::MyRegisterClass( HINSTANCE hInstance )
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = NULL;
    wcex.hCursor = NULL;
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szClassName;
    wcex.hIconSm = NULL;

    return RegisterClassEx(&wcex);
}

BOOL CMainFrameWork::InitMyClassInstance( HINSTANCE hInstance )
{       
    m_hWnd = CreateWindow(szClassName, NULL, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

    if (!m_hWnd)
    {
        return FALSE;
    }

    ::SetWindowLongPtr(m_hWnd, GWL_USERDATA, (LONG_PTR)this);

    ::ShowWindow(m_hWnd, SW_HIDE);
    ::UpdateWindow(m_hWnd);

    return TRUE;
}

CWndMgrTool * CMainFrameWork::GetWndMgrTool()
{
    return m_pManagerTool;
}

CMainFrameWork::destroy::destroy()
{

}

CMainFrameWork::destroy::~destroy()
{
	if (CMainFrameWork::m_SingleMainFrame != NULL)
	{        
		delete CMainFrameWork::m_SingleMainFrame;
	}
}


int SSMessageBox( HWND hwnd, LPCTSTR lpTip, MessagBoxStyle ms, DWORD dwTextColor )
{
    CWndMessageBox *pWnd = new CWndMessageBox(lpTip, ms, dwTextColor);
    pWnd->Create(hwnd, _T("提 示"), UI_WNDSTYLE_DIALOG, 0);
    pWnd->CenterWindow();
    int nRet = pWnd->ShowModal();
	delete pWnd;
	return nRet;
}

LRESULT CALLBACK WndProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    CMainFrameWork *pWnd = (CMainFrameWork*)::GetWindowLongPtr(hwnd, GWL_USERDATA);
    
    PAINTSTRUCT ps;
    HDC hdc;

    if (uMsg == WM_TASKBAR_RESTART)
    {
        pWnd->OnTaskBarRestart(uMsg, wParam, lParam);
    }

    switch (uMsg)
    {
    case WM_NIDTIP:
        {
            pWnd->OnTrayIcon(uMsg, wParam, lParam);
            break;
        }
    case WM_EXIT_APP:
        {
            pWnd->UnInit();
            break;
        }
    case WM_PAINT:
        {
            hdc = BeginPaint(hwnd, &ps);
            EndPaint(hwnd, &ps);
            break;
        }
    case WM_DESTROY:
        {
            break;
        }
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}




