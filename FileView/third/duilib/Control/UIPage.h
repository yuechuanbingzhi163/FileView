#ifndef UIPage_h__
#define UIPage_h__

using namespace std;

#pragma once

namespace DuiLib
{
	class CButtonUI;	
	class CLabelUI;
	class CEditUI;

	class UILIB_API CPageUI : public CHorizontalLayoutUI
	{
	public:
		CPageUI( );
		~CPageUI( );

        void SetTotalPage(int nTotalPage);
        void SetCurPage(int nCurPage);
        int GetCurPage();


        void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

        LPCTSTR GetClass() const;
        LPVOID GetInterface(LPCTSTR pstrName);

        virtual bool OnEditGoPageEnter(void *param);
        virtual bool OnBtnGoPageClick(void *param);
        virtual bool OnBtnLeftPageClick(void *param);
        virtual bool OnBtnRightPageClick(void *param);
		virtual bool OnBtnRefreshClick(void *param);

    private:
        CEditUI *m_pEditGoPage;
        CButtonUI *m_pBtnGoPage;
        CButtonUI *m_pBtnLeftPage;
        CLabelUI *m_pLabCurPage;
        CButtonUI *m_pBtnRightPage;
		CButtonUI *m_pBtnRefresh;

        int m_nGoPage;
        int  m_nCurPage;
        int m_nTotalPage;
	};
}


#endif // UITreeView_h__
