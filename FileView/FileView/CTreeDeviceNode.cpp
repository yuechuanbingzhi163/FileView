#include "stdafx.h"
#include "CTreeDeviceNode.h"

CTreeNodeDevice::CTreeNodeDevice( )
{ 
    SetFixedHeight(25); 	

	GetFolderButton()->SetFixedWidth(7);
	GetFolderButton()->SetAttribute(_T("padding"), _T("3,8,3,8"));
	GetFolderButton()->SetNormalImage(_T("treeopen.png"));
	GetFolderButton()->SetSelectedHotImage(_T("treeopenhot.png"));
	GetFolderButton()->SetSelectedImage(_T("treeclose.png"));
	GetFolderButton()->SetSelectedHotImage(_T("treeclosehot.png")); 	

	SetAttribute(_T("checkboxattr"), _T("width=\"16\" height=\"16\" enabled=\"false\" padding=\"4,4,4,5\" bkimage=\"file='dir_icon_small' \""));

	GetFolderButton()->SetVisible(false);

	GetItemButton()->SetTextColor(0xff444444);
	//GetItemButton()->SetVisible(false);
	//m_pLabText = new CLabelUI;
	//m_pLabText->SetTextColor(0xff444444);	
	//m_pLabText->SetMouseEnabled(false);
	//GetTreeNodeHoriznotal()->Add(m_pLabText);
}

CTreeNodeDevice::~CTreeNodeDevice()
{

}

void CTreeNodeDevice::SetDirText(LPCTSTR lpDir)
{
	m_strDIR = lpDir;

	GetItemButton()->SetText(m_strDIR.c_str());
	GetItemButton()->SetToolTip(m_strDIR.c_str());
}

std::string CTreeNodeDevice::GetDirText()
{
	return m_strDIR;
}

void CTreeNodeDevice::SetFolderButtonVisible( bool b /*= true*/ )
{
	GetFolderButton()->SetVisible(b);
}





