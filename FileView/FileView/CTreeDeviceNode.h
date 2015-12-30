#pragma once

#include "stdafx.h"


class CTreeNodeDevice: public CTreeNodeUI
{
public:
    CTreeNodeDevice();
    virtual ~CTreeNodeDevice();   

	void SetDirText(LPCTSTR lpDir);
	string GetDirText();

private:
	string m_strDIR;


	CLabelUI *m_pLabText;

};