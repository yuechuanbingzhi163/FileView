#include "stdafx.h"
#include "CTreeDeviceNode.h"

CTreeNodeDevice::CTreeNodeDevice( )
{ 
    SetFixedHeight(25);
    GetItemButton()->SetVisible( false);   

    SetUserData(_T("tree_device_node"));

	m_pControlStar = new CControlUI;
	m_pControlStar->SetToolTip("缺省账户,即当前登录有效账户。");
	m_pControlStar->SetVisible(false);
	m_pControlStar->SetAttribute("padding", "2,4,0,5");
	m_pControlStar->SetFixedWidth(16);
	m_pControlStar->SetBkImage("starlog.png");

    m_pLabelText = new CLabelUI;
    m_pLabelText->SetAttribute(_T("endellipsis"), _T("true")); 
    m_pLabelText->SetAttribute(_T("textpadding"), _T("2,0,0,3"));
    m_pLabelText->SetAttribute(_T("disabledtextcolor"), _T("#ff666666"));

    m_pHorSecond = new CHorizontalLayoutUI; 
    //m_pHorSecond->SetVisible(false);     

	GetTreeNodeHoriznotal()->Add(m_pControlStar);
    GetTreeNodeHoriznotal()->Add(m_pLabelText); 
    GetTreeNodeHoriznotal()->Add(m_pHorSecond);
}

CTreeNodeDevice::~CTreeNodeDevice()
{

}

//void CTreeNodeDevice::SetNodeType( TREENODETYPE type )
//{
//    m_Node_type = type;
//
//    switch(type)
//    {
//    case TREE_NODE_TYPE_CLOUD_ACCOUNT_ROOT:
//        {  
//            GetFolderButton()->SetFixedWidth(7);
//            GetFolderButton()->SetAttribute(_T("padding"), _T("3,8,3,8"));
//            GetFolderButton()->SetNormalImage(_T("treeopen.png"));
//            GetFolderButton()->SetSelectedHotImage(_T("treeopenhot.png"));
//            GetFolderButton()->SetSelectedImage(_T("treeclose.png"));
//            GetFolderButton()->SetSelectedHotImage(_T("treeclosehot.png")); 
//
//            m_pLabelText->SetFixedWidth(90);
//
//            m_pBtnAdd = new CButtonUI;
//            m_pBtnAdd->SetUserData(_T("tree_device_cloud_login_btn"));
//            m_pBtnAdd->SetTag(1);
//            m_pBtnAdd->SetToolTip(_T("登录账户"));
//            m_pBtnAdd->SetFixedWidth(16);
//            m_pBtnAdd->SetAttribute(_T("padding"), _T("0,4,0,4"));
//            m_pBtnAdd->SetNormalImage(_T("addnor.png"));
//            m_pBtnAdd->SetHotImage(_T("addhot.png"));
//            m_pBtnAdd->SetPushedImage(_T("addpush.png"));  
//
//            m_pBtnRefresh = new CButtonUI;
//			m_pBtnRefresh->SetName("tree_device_cloud_refresh_btn");
//            m_pBtnRefresh->SetUserData(_T("tree_device_cloud_refresh_btn"));            
//            m_pBtnRefresh->SetTag(0);
//            m_pBtnRefresh->SetToolTip(_T("刷新已登录账户"));
//            m_pBtnRefresh->SetFixedWidth(16);
//            m_pBtnRefresh->SetAttribute(_T("padding"), _T("8,4,0,4"));
//            m_pBtnRefresh->SetNormalImage(_T("refreshnor.png"));
//            m_pBtnRefresh->SetHotImage(_T("refreshhot.png"));
//            m_pBtnRefresh->SetPushedImage(_T("refreshpush.png")); 
//
//            m_pFinalSpace = new CControlUI;
//            m_pFinalSpace->SetFixedWidth(10); 
//
//            m_pHorSecond->SetFixedWidth(50);
//            m_pHorSecond->Add(m_pBtnAdd); 
//            m_pHorSecond->Add(m_pBtnRefresh);
//            m_pHorSecond->Add(m_pFinalSpace);
//
//            break;
//        }
//    case TREE_NODE_TYPE_CLOUD_ACCOUNT_INFO:
//        {            
//            GetFolderButton()->SetFixedWidth(7);
//            GetFolderButton()->SetAttribute(_T("padding"), _T("3,8,3,8"));
//            GetFolderButton()->SetNormalImage(_T("treeopen.png"));
//            GetFolderButton()->SetSelectedHotImage(_T("treeopenhot.png"));
//            GetFolderButton()->SetSelectedImage(_T("treeclose.png"));
//            GetFolderButton()->SetSelectedHotImage(_T("treeclosehot.png"));
//
//            SetAttribute(_T("menu"), _T("true"));
//
//            m_pHorSecond->SetFixedWidth(1);      
//           
//            break;
//        }
//    case TREE_NODE_TYPE_LOCAL_ROOT:
//        {
//            GetFolderButton()->SetFixedWidth(7);
//            GetFolderButton()->SetAttribute(_T("padding"), _T("3,8,3,8"));
//            GetFolderButton()->SetNormalImage(_T("treeopen.png"));
//            GetFolderButton()->SetSelectedHotImage(_T("treeopenhot.png"));
//            GetFolderButton()->SetSelectedImage(_T("treeclose.png"));
//            GetFolderButton()->SetSelectedHotImage(_T("treeclosehot.png")); 
//
//            m_pLabelText->SetFixedWidth(90);
//
//            m_pBtnRefresh = new CButtonUI;
//            m_pBtnRefresh->SetUserData(_T("tree_device_btn"));
//            m_pBtnRefresh->SetTag(0);
//            m_pBtnRefresh->SetToolTip(_T("刷新"));
//            m_pBtnRefresh->SetFixedWidth(16);
//            m_pBtnRefresh->SetAttribute(_T("padding"), _T("0,4,0,4"));
//            m_pBtnRefresh->SetNormalImage(_T("refreshnor.png"));
//            m_pBtnRefresh->SetHotImage(_T("refreshhot.png"));
//            m_pBtnRefresh->SetPushedImage(_T("refreshpush.png"));  
//
//            m_pFinalSpace = new CControlUI;
//            m_pFinalSpace->SetFixedWidth(10);
//
//            m_pHorSecond->Add(m_pBtnRefresh);
//            m_pHorSecond->Add(m_pFinalSpace);
//            m_pHorSecond->SetFixedWidth(26);
//            
//            break;
//        }
//    case TREE_NODE_TYPE_NET_ROOT:
//        {
//            GetFolderButton()->SetFixedWidth(7);
//            GetFolderButton()->SetAttribute(_T("padding"), _T("3,8,3,8"));
//            GetFolderButton()->SetNormalImage(_T("treeopen.png"));
//            GetFolderButton()->SetSelectedHotImage(_T("treeopenhot.png"));
//            GetFolderButton()->SetSelectedImage(_T("treeclose.png"));
//            GetFolderButton()->SetSelectedHotImage(_T("treeclosehot.png")); 
//
//            m_pLabelText->SetFixedWidth(90);
//
//            m_pBtnRefresh = new CButtonUI;
//            m_pBtnRefresh->SetUserData(_T("tree_device_btn"));
//            m_pBtnRefresh->SetTag(0);
//            m_pBtnRefresh->SetToolTip(_T("刷新"));
//            m_pBtnRefresh->SetFixedWidth(16);
//            m_pBtnRefresh->SetAttribute(_T("padding"), _T("0,4,0,4"));
//            m_pBtnRefresh->SetNormalImage(_T("refreshnor.png"));
//            m_pBtnRefresh->SetHotImage(_T("refreshhot.png"));
//            m_pBtnRefresh->SetPushedImage(_T("refreshpush.png"));  
//
//            m_pFinalSpace = new CControlUI;
//            m_pFinalSpace->SetFixedWidth(10);
//
//            m_pHorSecond->Add(m_pBtnRefresh);
//            m_pHorSecond->Add(m_pFinalSpace);
//            m_pHorSecond->SetFixedWidth(26);
//
//            break;
//        }
//    case TREE_NODE_TYPE_LOCK_INFO:
//        {
//            GetFolderButton()->SetFixedWidth(7);
//            GetFolderButton()->SetAttribute(_T("padding"), _T("3,8,3,8"));
//            GetFolderButton()->SetNormalImage(_T("treeopen.png"));
//            GetFolderButton()->SetSelectedHotImage(_T("treeopenhot.png"));
//            GetFolderButton()->SetSelectedImage(_T("treeclose.png"));
//            GetFolderButton()->SetSelectedHotImage(_T("treeclosehot.png"));
//
//            SetAttribute(_T("menu"), _T("true"));
//
//            m_pHorSecond->SetFixedWidth(1);
//
//            break;
//        }
//    case TREE_NODE_TYPE_DEVELOPER_INFO:
//        {
//            GetFolderButton()->SetFixedWidth(20);
//            GetFolderButton()->SetAttribute(_T("padding"), _T("12,3,0,4"));
//            GetFolderButton()->SetNormalImage(_T("开发商.png"));
//            GetFolderButton()->SetSelectedHotImage(_T("开发商.png"));
//            GetFolderButton()->SetSelectedImage(_T("开发商.png"));
//            GetFolderButton()->SetSelectedHotImage(_T("开发商.png")); 
//            GetFolderButton()->SetMouseEnabled(false);     
//
//            SetAttribute(_T("menu"), _T("true"));
//
//            m_pHorSecond->SetFixedWidth(1);
//        }
//    }
//}

void CTreeNodeDevice::SetLabelText( LPCTSTR lpText)
{
    m_pLabelText->SetText(lpText);
    m_pLabelText->SetToolTip(lpText);
}

void CTreeNodeDevice::DoEvent( TEventUI& event )
{
    __super::DoEvent(event);  
}



