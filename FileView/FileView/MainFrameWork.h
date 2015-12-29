#pragma once

#include "stdafx.h"
#include "WndMessageBox.h"

extern UINT WM_TASKBAR_RESTART;

int SSMessageBox(HWND hwnd, LPCTSTR lpTip, MessagBoxStyle ms = MESSAGEBOX_STYPE_OK, DWORD dwTextColor = 0xffff0000);
int GetRootPath(std::string &rootPath);

class CWndMgrTool;
class CMainFrameWork
{
public:	
	virtual ~CMainFrameWork(void);

	void Init();
    void UnInit();

	void Exit_App();	

public:
	static CMainFrameWork *SingleInstance();

	LRESULT OnTrayIcon(UINT nMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnTaskBarRestart(UINT nMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnPopWndBubble(UINT nMsg, WPARAM wParam, LPARAM lParam);

    void InitNotifyIconData();
    void UnInitNotifyIconData();
    void ShowNotifyIconMenu();

	void InitLm();
	void UninitLm();

    void ShowManagerTool();

    CWndMgrTool *GetWndMgrTool();

public:
    HWND m_hWnd;

protected:
	CMainFrameWork(void);	

    ATOM MyRegisterClass(HINSTANCE hInstance);
    BOOL InitMyClassInstance(HINSTANCE hInstance);

private:
	static CMainFrameWork *m_SingleMainFrame;

    NOTIFYICONDATA m_NotifyIconData;
    CWndMgrTool *m_pManagerTool;

private:
	class destroy
	{
	public:
		destroy();
		~destroy();
	};
};

