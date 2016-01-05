#pragma once
#include <string>
#include <list>
#include "DataCenter.h"

//接口中均为 0:返回正确  其他值错误
class CLogicBaseImpl
{
public:      
	//菜单项
    void GetMenuCommandString(int nIndex, string &strText);   //nIndex: 0 - 4;
	void ExecuteMenuCommand(int nIndex);   //nIndex: 0 - 4;

protected:
	CLogicBaseImpl();
    ~CLogicBaseImpl();
};

BOOL ChangeWindowMessageFilterEx2(HWND hWnd, UINT uMessage, BOOL bAllow = TRUE);

