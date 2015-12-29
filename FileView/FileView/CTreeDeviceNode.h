#pragma once

#include "stdafx.h"

class CTreeNodeDevice: public CTreeNodeUI
{
public:
    CTreeNodeDevice();
    virtual ~CTreeNodeDevice();

    void SetLabelText(LPCTSTR lpText);

    void DoEvent(TEventUI& event);

private:
    CHorizontalLayoutUI *m_pHorSecond;

	CControlUI *m_pControlStar;

    CLabelUI *m_pLabelText;
    CButtonUI *m_pBtnRefresh;    
    CButtonUI *m_pBtnAdd;   
    CButtonUI *m_pBtnDelete;
    CControlUI *m_pSpace;
    CControlUI *m_pFinalSpace;
};