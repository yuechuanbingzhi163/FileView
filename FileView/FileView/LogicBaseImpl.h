#pragma once
#include <string>
#include <list>
#include "DataCenter.h"

//�ӿ��о�Ϊ 0:������ȷ  ����ֵ����
class CLogicBaseImpl
{
public:      
	//�˵���
    void GetMenuCommandString(int nIndex, string &strText);   //nIndex: 0 - 4;
	void ExecuteMenuCommand(int nIndex);   //nIndex: 0 - 4;

protected:
	CLogicBaseImpl();
    ~CLogicBaseImpl();
};

BOOL ChangeWindowMessageFilterEx2(HWND hWnd, UINT uMessage, BOOL bAllow = TRUE);

