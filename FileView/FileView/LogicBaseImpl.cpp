#include "stdafx.h"
#include "LogicBaseImpl.h"

CLogicBaseImpl::CLogicBaseImpl()
{

}

CLogicBaseImpl::~CLogicBaseImpl(void)
{   
}

void CLogicBaseImpl::GetMenuCommandString( int nIndex, string &strText )
{
	char szTemp[20] = {0};
	sprintf_s(szTemp, sizeof(szTemp), "菜单%d", nIndex);
	strText = szTemp;
}

void CLogicBaseImpl::ExecuteMenuCommand( int nIndex )
{
	char szTemp[20] = {0};
	sprintf_s(szTemp, sizeof(szTemp), "菜单%d", nIndex);
	MessageBox(NULL, szTemp, "提示", MB_OKCANCEL);
}

BOOL ChangeWindowMessageFilterEx2( HWND hWnd, UINT uMessage, BOOL bAllow /*= TRUE*/ )
{
	typedef BOOL (WINAPI * ChangeWindowMessageFilterExFn)(HWND, UINT , DWORD, PCHANGEFILTERSTRUCT pChangeFilterStruct);

	HMODULE hUserMod = NULL;
	BOOL bResult = FALSE;
	hUserMod = ::LoadLibrary("user32.dll");
	if (hUserMod == NULL)
	{
		return FALSE;
	}

	ChangeWindowMessageFilterExFn pFnChangeWindowMessageFilterEx = (ChangeWindowMessageFilterExFn)GetProcAddress(hUserMod, "ChangeWindowMessageFilterEx");
	if (pFnChangeWindowMessageFilterEx == NULL)
	{
		FreeLibrary(hUserMod);
		return FALSE;
	}

	bResult = pFnChangeWindowMessageFilterEx(hWnd, uMessage, bAllow ? MSGFLT_ALLOW : MSGFLT_DISALLOW, NULL);
	FreeLibrary(hUserMod);

	return bResult;
}
