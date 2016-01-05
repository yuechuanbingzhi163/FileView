#include "stdafx.h"
#include "MainFrameWork.h"
#include "WndMessageBox.h"
#include "DumpCatch.h"
#include "LogicBaseImpl.h"

HINSTANCE g_Hinstance = NULL;

int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);    

	::OleInitialize(NULL);
	::CoInitialize(NULL);

	//CatchDumpFile::CDumpCatch dumpCatch;

	//CLog::Init();

	g_Hinstance = hInstance;

	BOOL bRet = ChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ALLOW);
	bRet = ChangeWindowMessageFilter(0x0049, MSGFLT_ALLOW);
	bRet = ChangeWindowMessageFilter(WM_COPYDATA, MSGFLT_ALLOW);

	CPaintManagerUI ::SetInstance(hInstance);

	CMainFrameWork::SingleInstance()->Init();  

	CMainFrameWork::SingleInstance()->ShowManagerTool();

	CPaintManagerUI::MessageLoop();

	::CoUninitialize();
	::OleUninitialize();    

	return 0;
}