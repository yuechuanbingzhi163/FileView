#include "StdAfx.h"
#include "UIPage.h"

#pragma warning( disable: 4251 )
namespace DuiLib
{
    CPageUI::CPageUI()
    {
        SetFixedHeight(20);
        SetFixedWidth(186);

        m_nGoPage = 0;
        m_nCurPage = 0;
        m_nTotalPage = 0;

        m_pEditGoPage = new CEditUI;
        m_pEditGoPage->SetFixedWidth(40);
        m_pEditGoPage->SetAttribute(_T("textpadding"), _T("2,1,2,1"));
        m_pEditGoPage->SetAttribute(_T("bordersize"), _T("1"));
        m_pEditGoPage->SetAttribute(_T("bordercolor"), _T("#FFBFBFBF"));
        m_pEditGoPage->SetAttribute(_T("textcolor"), _T("#ff333333"));
        m_pEditGoPage->SetAttribute(_T("tipvalue"), _T("转至..."));
        m_pEditGoPage->SetAttribute(_T("tipvaluecolor"), _T("#ff888888"));
        m_pEditGoPage->OnNotify += MakeDelegate(this, &CPageUI::OnEditGoPageEnter);

        m_pBtnGoPage = new CButtonUI;
        m_pBtnGoPage->SetFixedWidth(20);
        m_pBtnGoPage->SetText(_T("go"));
        m_pBtnGoPage->SetAttribute(_T("textpadding"), _T("2,0,2,1"));
        m_pBtnGoPage->SetAttribute(_T("bordersize"), _T("1"));
        m_pBtnGoPage->SetAttribute(_T("bordercolor"), _T("#FFBFBFBF"));
        m_pBtnGoPage->SetTextColor(0xff333333);
        m_pBtnGoPage->SetHotTextColor(0xff0099cc);        
        m_pBtnGoPage->OnNotify += MakeDelegate(this, &CPageUI::OnBtnGoPageClick);

        m_pBtnLeftPage = new CButtonUI;
        m_pBtnLeftPage->SetFixedWidth(16);
        m_pBtnLeftPage->SetAttribute(_T("padding"), _T("10,2,0,2"));        
        m_pBtnLeftPage->OnNotify += MakeDelegate(this, &CPageUI::OnBtnLeftPageClick);

        m_pLabCurPage = new CLabelUI;
        //m_pLabCurPage->SetFixedWidth(16);       
        m_pLabCurPage->SetAutoCalcWidth(true);
        m_pLabCurPage->SetTextColor(0xff333333);        

        m_pBtnRightPage = new CButtonUI;
        m_pBtnRightPage->SetFixedWidth(16);
        m_pBtnRightPage->SetAttribute(_T("padding"), _T("0,2,0,2"));        
        m_pBtnRightPage->OnNotify += MakeDelegate(this, &CPageUI::OnBtnRightPageClick);

		m_pBtnRefresh = new CButtonUI;
		m_pBtnRefresh->SetFixedWidth(16);
		m_pBtnRefresh->SetEnabled(false);
		m_pBtnRefresh->SetToolTip("刷新当前页");
		m_pBtnRefresh->SetAttribute(_T("padding"), _T("4,2,0,2"));        
		m_pBtnRefresh->OnNotify += MakeDelegate(this, &CPageUI::OnBtnRefreshClick);

        Add(m_pEditGoPage);
        Add(m_pBtnGoPage);
        Add(m_pBtnLeftPage);
        Add(m_pLabCurPage);
        Add(m_pBtnRightPage);
		Add(m_pBtnRefresh);

        SetTotalPage(m_nTotalPage);
        SetCurPage(m_nCurPage);
    }

    CPageUI::~CPageUI()
    {

    }

    void CPageUI::SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue )
    {
        if(_tcscmp(pstrName, _T("editgopagefont")) == 0 )
            m_pEditGoPage->SetFont(_ttoi(pstrValue));   
        else if(_tcscmp(pstrName, _T("gopagefont")) == 0 )
            m_pBtnGoPage->SetFont(_ttoi(pstrValue));
        else if(_tcscmp(pstrName, _T("leftpagenormalimage")) == 0 )
            m_pBtnLeftPage->SetNormalImage(pstrValue);
        else if(_tcscmp(pstrName, _T("leftpagehotimage")) == 0 )
             m_pBtnLeftPage->SetHotImage(pstrValue);
        else if(_tcscmp(pstrName, _T("leftpagepushedimage")) == 0 )
             m_pBtnLeftPage->SetPushedImage(pstrValue);
        else if(_tcscmp(pstrName, _T("leftpagedisabledimage")) == 0 )
             m_pBtnLeftPage->SetDisabledImage(pstrValue);
        else if(_tcscmp(pstrName, _T("curpagefont")) == 0 )
            m_pLabCurPage->SetFont(_ttoi(pstrValue));
        else if(_tcscmp(pstrName, _T("rightpagenormalimage")) == 0 )
            m_pBtnRightPage->SetNormalImage(pstrValue);
        else if(_tcscmp(pstrName, _T("rightpagehotimage")) == 0 )
            m_pBtnRightPage->SetHotImage(pstrValue);
        else if(_tcscmp(pstrName, _T("rightpagepushedimage")) == 0 )
            m_pBtnRightPage->SetPushedImage(pstrValue);
        else if(_tcscmp(pstrName, _T("rightpagedisabledimage")) == 0 )
            m_pBtnRightPage->SetDisabledImage(pstrValue);
		else if(_tcscmp(pstrName, _T("refreshnormalimage")) == 0 )
			m_pBtnRefresh->SetNormalImage(pstrValue);
		else if(_tcscmp(pstrName, _T("refreshhotimage")) == 0 )
			m_pBtnRefresh->SetHotImage(pstrValue);
		else if(_tcscmp(pstrName, _T("refreshpushedimage")) == 0 )
			m_pBtnRefresh->SetPushedImage(pstrValue);
		else if(_tcscmp(pstrName, _T("refreshdisabledimage")) == 0 )
			m_pBtnRefresh->SetDisabledImage(pstrValue);
        else CHorizontalLayoutUI::SetAttribute(pstrName,pstrValue);
    }

    LPCTSTR CPageUI::GetClass() const
    {
        return _T("PageUI");
    }

    LPVOID CPageUI::GetInterface( LPCTSTR pstrName )
    {
        if( _tcscmp(pstrName, _T("PageControl")) == 0 )
            return static_cast<CPageUI*>(this);
        return CHorizontalLayoutUI::GetInterface(pstrName);
    }

    bool CPageUI::OnEditGoPageEnter( void *param )
    {
        bool bRet = false;

        TNotifyUI *pMsg = (TNotifyUI*)param;
        do 
        {
            if (pMsg->sType == _T("return"))
            {                
                pMsg->sType = _T("click");
                bRet = OnBtnGoPageClick(param);
            }

        } while (false);

        return bRet;
    }

    bool CPageUI::OnBtnGoPageClick( void *param )
    {
        bool bRet = false;

        TNotifyUI *pMsg = (TNotifyUI*)param;

        do 
        {
            if (pMsg->sType == _T("click"))
            {                
                m_nGoPage = _ttoi(m_pEditGoPage->GetText().GetData());

                if (m_nGoPage <= 0 || m_nGoPage > m_nTotalPage)
                {
                    bRet = false;
                    break; 
                }

                SetCurPage(m_nGoPage);

                m_pManager->SendNotify(this, DUI_MSGTYPE_PAGE_CHANGED, NULL, m_nCurPage);
                
                bRet = true;
            }
        } while (false);

        return bRet;
    }

    bool CPageUI::OnBtnLeftPageClick( void *param )
    {
        bool bRet = false;

        TNotifyUI *pMsg = (TNotifyUI*)param;

        do 
        {
            if (pMsg->sType == _T("click"))
            {                
                m_nCurPage--;

                SetCurPage(m_nCurPage);

                m_pManager->SendNotify(this, DUI_MSGTYPE_PAGE_CHANGED, NULL, m_nCurPage);

                bRet = true;
            }
        } while (false);

        return bRet;
    }

    bool CPageUI::OnBtnRightPageClick( void *param )
    {
        bool bRet = false;

        TNotifyUI *pMsg = (TNotifyUI*)param;

        do 
        {
            if (pMsg->sType == _T("click"))
            {                
                m_nCurPage++;

                SetCurPage(m_nCurPage);

                m_pManager->SendNotify(this, DUI_MSGTYPE_PAGE_CHANGED, NULL, m_nCurPage);

                bRet = true;
            }
        } while (false);

        return bRet;
    }

    void CPageUI::SetTotalPage( int nTotalPage )
    {
        do 
        {
            if (nTotalPage < 0)
            {				
                break;
            }			

            m_nTotalPage = nTotalPage;

            if (m_nCurPage > m_nTotalPage)
            {
                m_nCurPage = 0;
            }

            TCHAR szTip[260] = {0};

            sprintf_s(szTip, _T("%d/%d"), m_nCurPage, m_nTotalPage);
            m_pLabCurPage->SetText(szTip);  
            m_pLabCurPage->SetFixedWidth(16);

            if (m_nCurPage <= 1)
            {
                m_pBtnLeftPage->SetEnabled(false);
            }
            else
            {
                m_pBtnLeftPage->SetEnabled(true);
            }

            if (m_nCurPage >= m_nTotalPage)
            {
                m_pBtnRightPage->SetEnabled(false);
            }
            else
            {
                m_pBtnRightPage->SetEnabled(true);
            } 

        } while (false);        
    }

    void CPageUI::SetCurPage( int nCurPage )
 {
        do 
        {
            if (nCurPage < 0)
            {				
                break;
            }

			if (nCurPage >= 1)
			{
				m_pBtnRefresh->SetEnabled(true);
			}
			

            if (nCurPage > m_nTotalPage)
            {
                nCurPage = m_nTotalPage;
            }

            m_nCurPage = nCurPage;            

            TCHAR szTip[260] = {0};

            sprintf_s(szTip, _T("%d/%d"), m_nCurPage, m_nTotalPage);
            m_pLabCurPage->SetText(szTip); 
            m_pLabCurPage->SetFixedWidth(16);

            if (m_nCurPage <= 1)
            {
                m_pBtnLeftPage->SetEnabled(false);
            }
            else
            {
                m_pBtnLeftPage->SetEnabled(true);
            }

            if (m_nCurPage >= m_nTotalPage)
            {
                m_pBtnRightPage->SetEnabled(false);
            }
            else
            {
                m_pBtnRightPage->SetEnabled(true);
            }                

        } while (false); 
}

    int CPageUI::GetCurPage()
    {
        return m_nCurPage;
    }

	bool CPageUI::OnBtnRefreshClick( void *param )
	{
		bool bRet = false;

		TNotifyUI *pMsg = (TNotifyUI*)param;

		do 
		{
			if (pMsg->sType == _T("click"))
			{   
				m_pManager->SendNotify(this, DUI_MSGTYPE_PAGE_CHANGED, NULL, m_nCurPage);

				bRet = true;
			}
		} while (false);

		return bRet;
	}

 }