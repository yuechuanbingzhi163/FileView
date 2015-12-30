#include "StdAfx.h"
#include "WndMgrTool.h"
#include "MainFrameWork.h"

void SetClipBoardSelfData(LPCTSTR lpData);

DUI_BEGIN_MESSAGE_MAP(CWndMgrTool, CNotifyPump)
    DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK,OnClick)   
	DUI_ON_CLICK_CTRNAME("btn_close", OnBtnClose)
	DUI_ON_MSGTYPE_CTRNAME(DUI_MSGTYPE_ITEMSELECT, "tree_file", OnTreeFileSelChanged)
 DUI_END_MESSAGE_MAP()


CWndMgrTool::CWndMgrTool(void)
{
	m_pFs = NULL;
	m_pProgressFlash = NULL;
	m_pCurSelTreeNode = NULL;
}

CWndMgrTool::~CWndMgrTool(void)
{
}

void CWndMgrTool::Notify( TNotifyUI &msg )
{
	__super::Notify(msg);

    if (msg.sType == DUI_MSGTYPE_CLICK)
    {
        
    }
	else if (msg.sType == DUI_MSGTYPE_HEADERCLICK)
	{
		
	}
    else if (msg.sType == DUI_MSGTYPE_MENU)
    {       
		if (msg.pSender == m_pListFile)
		{
			 CMenuWnd *pMenu = new CMenuWnd;
			 DuiLib::CPoint point = msg.ptMouse;
			 ClientToScreen(m_hWnd, &point);
			 pMenu->Init(NULL, _T("commonmenu.xml"), point, &m_PaintManager);

			 CMenuUI *rootMenu = pMenu->GetMenuUI();					 
			 
			 CMenuElementUI *pLogoutItem = new CMenuElementUI;
			 pLogoutItem->SetName(_T("list_file_new_dir"));
			 pLogoutItem->SetText(_T("新建文件夹"));				 
			 rootMenu->Add(pLogoutItem);			

			 pMenu->ResizeMenu();		
		}

		if (StrCmp(msg.pSender->GetClass(), "CListContainerElementFIle") == 0)
		{
			m_pCurSelListItem = static_cast<CListContainerElementLicense*>(msg.pSender);

			CMenuWnd *pMenu = new CMenuWnd;
			DuiLib::CPoint point = msg.ptMouse;
			ClientToScreen(m_hWnd, &point);
			pMenu->Init(NULL, _T("commonmenu.xml"), point, &m_PaintManager);

			CMenuUI *rootMenu = pMenu->GetMenuUI();					 

			CMenuElementUI *pLogoutItem = new CMenuElementUI;
			pLogoutItem->SetName(_T("list_file_delete"));
			pLogoutItem->SetText(_T("删除"));				 
			rootMenu->Add(pLogoutItem);			

			pMenu->ResizeMenu();		
		}
    }
    else if (msg.sType == DUI_MSGTYPE_ITEMDBCLICK)
    {
         
    }
    else if (msg.sType == DUI_MSGTYPE_TIMER)
    {
       
    }
	else if (msg.sType == DUI_MSGTYPE_DRAG_PUT)
	{
		//if (StrCmp(msg.pSender->GetClass(), _T("CListContainerElementLicense")) == 0)
		//{
		//	m_pCurTransferLicenseListItem = static_cast<CListContainerElementLicense*>(msg.pSender);

		//	POINT pt = *((POINT*)msg.lParam);

		//	do 
		//	{
		//		RECT rcDeviceTree = m_pTreeViewShouQuanDevice->GetPos();
		//		if (!::PtInRect(&rcDeviceTree, pt))
		//		{
		//			break;
		//		}

		//		m_pCurTransferLicenseTreeNode = NULL;

		//		CTreeNodeDevice *pTreeNode = NULL;
		//		int nCount = m_pTreeViewShouQuanDevice->GetCount();
		//		for (int i=0; i<nCount; i++)
		//		{
		//			pTreeNode = static_cast<CTreeNodeDevice*>(m_pTreeViewShouQuanDevice->GetItemAt(i));
		//			rcDeviceTree = pTreeNode->GetPos();
		//			if (::PtInRect(&rcDeviceTree, pt))
		//			{
		//				m_pCurTransferLicenseTreeNode = pTreeNode;
		//				break;
		//			}
		//		}

		//		if (m_pCurTransferLicenseTreeNode == NULL)
		//		{
		//			break;
		//		}

		//		if (m_pCurTransferLicenseTreeNode->GetNodeType() == TREE_NODE_TYPE_CLOUD_ACCOUNT_ROOT ||
		//			m_pCurTransferLicenseTreeNode->GetNodeType() == TREE_NODE_TYPE_LOCAL_ROOT ||
		//			m_pCurTransferLicenseTreeNode->GetNodeType() == TREE_NODE_TYPE_NET_ROOT ||
		//			m_pCurTransferLicenseTreeNode->GetNodeType() == TREE_NODE_TYPE_DEVELOPER_INFO ||
		//			((m_pCurTransferLicenseTreeNode->GetNodeType() == TREE_NODE_TYPE_LOCK_INFO) && (m_pCurTransferLicenseTreeNode->GetLockIter()->szLockType == "remote")))
		//		{
		//			SSMessageBox(m_hWnd, "许可只可以在云账户和本地锁之间转移");
		//			break;
		//		}

		//		list<VLOCK>::iterator lockIter1= m_pCurTransferLicenseListItem->GetLockIter();
		//		list<VLOCK>::iterator lockIter2 = m_pCurTransferLicenseTreeNode->GetLockIter();

		//		if (lockIter1->szLockType == lockIter2->szLockType)
		//		{
		//			SSMessageBox(m_hWnd, "许可只可以在云账户和本地锁之间转移");
		//			break;
		//		}

		//		m_hShouQuanThread = CreateThread(NULL, 0, _ThreadTransferLicense3, this, CREATE_SUSPENDED, NULL);
		//		m_pProgressFlash = new CWndProgressFlash;
		//		m_pProgressFlash->Init(m_hShouQuanThread);
		//		m_pProgressFlash->Create(m_hWnd, NULL, UI_WNDSTYLE_FRAME, 0);
		//		m_pProgressFlash->CenterWindow();
		//		m_pProgressFlash->ShowModal();
		//		delete m_pProgressFlash;

		//		int k= 0;

		//	} while (false);			
		//}
	}
}

LRESULT CWndMgrTool::OnCreate( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	__super::OnCreate(uMsg, wParam, lParam, bHandled);    

	m_pTreeFile = static_cast<CTreeViewUI*>(m_PaintManager.FindControl("tree_file"));
	m_pListFile = static_cast<CListUI*>(m_PaintManager.FindControl("list_file"));

	m_pListFile->SetAttribute("menu", "true");

	m_DragDrop.DragDropRegister(m_hWnd);
	m_DragDrop.AddTargetControl(m_pTreeFile);
	m_DragDrop.AddTargetControl(m_pListFile);

	OpenVdFile("D:\\SourceCode\\FileView\\FileView\\Debug\\test.svd");

	return 0;
}

LRESULT CWndMgrTool::OnSysCommand( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
    if (wParam == SC_CLOSE)
    {
        bHandled = TRUE;
        CMainFrameWork::SingleInstance()->UnInit();
        return 0;
    }
#if defined(WIN32) && !defined(UNDER_CE)
    BOOL bZoomed = ::IsZoomed(*this);
    LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
    if( ::IsZoomed(*this) != bZoomed )
    {
        CControlUI* pbtnMax     = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("maxbtn")));       // 最大化按钮
        CControlUI* pbtnRestore = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("restorebtn")));   // 还原按钮

        // 切换最大化按钮和还原按钮的状态
        if (pbtnMax && pbtnRestore)
        {
            pbtnMax->SetVisible(TRUE == bZoomed);       // 此处用表达式是为了避免编译器BOOL转换的警告
            pbtnRestore->SetVisible(FALSE == bZoomed);
        }

    }
#else
    LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
#endif
    return lRes;
}

LRESULT CWndMgrTool::HandleCustomMessage( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
    switch(uMsg)
    {	
    case WM_MENUCLICK:
        {
            CDuiString *strMenuName = (CDuiString *)wParam;
			if (*strMenuName == "list_file_new_dir")
			{
				CreateNewDirectroy();
			}
			else if (*strMenuName == "list_file_delete")
			{
				DeleteFile();
			}
			break;	
        } 
	case WM_DRAG_FILE_INTO_TARGET:
		{
			HDROP hDrop = (HDROP)wParam;
			CControlUI *pControl = (CControlUI *)lParam;

			char szFilePath[MAX_PATH] = {0};
			UINT nNumOfFiles = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);
			for (UINT nIndex=0; nIndex < nNumOfFiles; nIndex++)
			{
				DragQueryFile(hDrop, nIndex, szFilePath, MAX_PATH);
				break;
			}

			if (PathFileExists(szFilePath))
			{
				if (pControl == m_pTreeFile)
				{
					OpenVdFile(szFilePath);
				}
				else if (pControl == m_pListFile)
				{

				}
			}

			break;
		}
    }

    return __super::HandleCustomMessage(uMsg, wParam, lParam, bHandled);
}

void CWndMgrTool::OnBtnClose( TNotifyUI &msg )
{
	if (m_pFs != 0)
	{
		st_close(m_pFs);
		m_pFs = nullptr;
	}

	CMainFrameWork::SingleInstance()->UnInit();
}

void CWndMgrTool::OpenVdFile(LPCTSTR lpPath)
{
	if (!PathFileExists(lpPath))
	{
		return;
	}
	
	PTSTR lp = PathFindExtension(lpPath);

	if (lp == NULL)
	{
		SSMessageBox(m_hWnd, "请选择svd文件");
		return;
	}

	string strExtension = lp+1;
	if (strcmp(strExtension.c_str(), "svd") != 0)
	{
		SSMessageBox(m_hWnd, "请选择svd文件");
		return;
	}

	if (m_pFs != 0)
	{
		st_close(m_pFs);
		m_pFs = nullptr;
		m_pTreeFile->RemoveAll();
		m_pListFile->RemoveAll();
	}

	string_t strIconName;
	HBITMAP hBmp;

	strIconName = _T("dir_icon_small");

	if (m_PaintManager.GetImage(strIconName.c_str()) == NULL)
	{
		hBmp = GetIconByFileType(NULL, true);
		m_PaintManager.AddImage(strIconName.c_str(), hBmp, 16, 16, true);
	}

	m_pFs = st_open(lpPath);
	if (m_pFs != nullptr)
	{
		CTreeNodeDevice *pRoot = new CTreeNodeDevice;
		pRoot->SetDirText("C:");
		m_pTreeFile->Add(pRoot);

		EnumAllChildrenDir("C:", pRoot);

		m_pTreeFile->SelectItem(0);
		m_pCurSelTreeNode = pRoot;
	}	
}

void CWndMgrTool::EnumAllChildrenDir(LPCTSTR lpPath, CTreeNodeDevice *pCurNode)
{
	if (m_pFs != 0 && pCurNode != NULL)
	{
		void *dir = fs_ropen(m_pFs, lpPath);
		if (dir != 0)
		{
			file_entry entry;
			while (fs_lsdir(m_pFs, dir, &entry))
			{
				if(entry.is_dir)
				{
					CTreeNodeDevice *pChild = new CTreeNodeDevice;
					pChild->SetDirText(entry.filename);
					pCurNode->Add(pChild);

					string strNewPath = lpPath;
					strNewPath += "\\";
					strNewPath += entry.filename;
					EnumAllChildrenDir(strNewPath.c_str(), pChild);
				}
			}

			fs_rclose(m_pFs, dir);
		}
	}	
}

void CWndMgrTool::OnTreeFileSelChanged(TNotifyUI &msg)
{
	m_pListFile->RemoveAll();

	int nOldCurIndex = (int)msg.lParam;
	int nNewCurIndex = (int)msg.wParam;

	m_pCurSelTreeNode = static_cast<CTreeNodeDevice*>(m_pTreeFile->GetItemAt(nNewCurIndex));

	string path;
	MakeAbsolutePath(m_pCurSelTreeNode, path);

	void *dir = fs_ropen(m_pFs, path.c_str());
	if (dir != 0)
	{
		file_entry entry;
		while (fs_lsdir(m_pFs, dir, &entry))
		{
			CreateListFileItem(entry);			
		}

		fs_rclose(m_pFs, dir);
	}
}

void CWndMgrTool::MakeAbsolutePath(CTreeNodeDevice *pNode, string &Path)
{
	CTreeNodeDevice *pTempNode = pNode;
	list<string> listDirName;

	while(pTempNode != NULL)
	{
		listDirName.push_front(pTempNode->GetDirText());
		pTempNode = static_cast<CTreeNodeDevice*>(pTempNode->GetParentNode());
	}

	list<string>::iterator iter = listDirName.begin();
	for (iter; iter != listDirName.end(); iter++)
	{
		Path += *iter;
		Path += "\\";
	}	
}

void CWndMgrTool::CreateListFileItem(file_entry &FileEntry)
{
	CListContainerElementLicense *pItem = new CListContainerElementLicense;
	pItem->SetFileEntry(FileEntry);

	string_t strIconName;
	HBITMAP hBmp;
	int nWidth = 0;
	int nHeight =0;

	if (FileEntry.is_dir)
	{
		strIconName = "dir_icon_small";		
	}
	else
	{
		string_t strName = FileEntry.filename;

		LPTSTR lpTemp = StrRChr(strName.c_str(), NULL, _T('.'));

		if (lpTemp == NULL)
		{
			strIconName = _T("NULL_icon_small");

			if (m_PaintManager.GetImage(strIconName.c_str()) == NULL)
			{
				hBmp = GetIconByFileType(NULL, false);			

				BITMAP bmp;
				GetObject(hBmp, sizeof(BITMAP), &bmp);
				nWidth = bmp.bmWidth;
				nHeight = bmp.bmHeight;

				m_PaintManager.AddImage(strIconName.c_str(), hBmp, nWidth, nHeight, true);
			}
		}
		else
		{
			strIconName = lpTemp + 1;
			strIconName += _T("_icon_small");

			if (m_PaintManager.GetImage(strIconName.c_str()) == NULL)
			{
				hBmp = GetIconByFileType(lpTemp, false);

				BITMAP bmp;
				GetObject(hBmp, sizeof(BITMAP), &bmp);
				nWidth = bmp.bmWidth;
				nHeight = bmp.bmHeight;

				m_PaintManager.AddImage(strIconName.c_str(), hBmp, nWidth, nHeight, true);
			}
		}
	}

	pItem->SetIconName(strIconName.c_str());

	if (FileEntry.is_dir)
	{
		int nCount = m_pListFile->GetCount();		
		int nFileStartIndex = 0;
		for (int i=0; i<nCount; i++)
		{
			CListContainerElementLicense *pItem = static_cast<CListContainerElementLicense*>(m_pListFile->GetItemAt(i));
			file_entry FileEntry = pItem->GetFileEntry();
			if (FileEntry.is_dir != 1)
			{
				nFileStartIndex = i;
				break;
			}			
		}

		m_pListFile->AddAt(pItem, nFileStartIndex);		
	}
	else
	{
		m_pListFile->Add(pItem);
	}	
}

void CWndMgrTool::CreateNewDirectroy()
{
	string strDirName = "新建文件夹";

	string strUpperPath;
	MakeAbsolutePath(m_pCurSelTreeNode, strUpperPath);

	string strNewPath = strUpperPath;	
	strNewPath += strDirName;

	do 
	{
		void *dir = fs_ropen(m_pFs, strNewPath.c_str());
		if (dir == 0)
		{
			break;			//该目录没有			
		}

		fs_rclose(m_pFs, dir);

		char szDirName[MAX_PATH] = {0};
		for (int i=1; i<1000; i++)
		{
			sprintf_s(szDirName, sizeof(szDirName), "新建文件夹(%d)", i);
			strNewPath = strUpperPath;			
			strNewPath += szDirName;

			dir = fs_ropen(m_pFs, strNewPath.c_str());
			if (dir == 0)
			{
				strDirName = szDirName;
				break;			//该目录没有			
			}
			else
			{
				fs_rclose(m_pFs, dir);
			}
		}
	} while (false);

	int nRet = fs_mkdir(m_pFs, strNewPath.c_str());

	CTreeNodeDevice *pNewDevice = new CTreeNodeDevice;
	pNewDevice->SetDirText(strDirName.c_str());
	m_pCurSelTreeNode->Add(pNewDevice);

	string strCurAbsolutePath;
	MakeAbsolutePath(m_pCurSelTreeNode, strCurAbsolutePath);
	void *dir = fs_ropen(m_pFs, strCurAbsolutePath.c_str());
	if (dir != 0)
	{
		file_entry entry;
		while (fs_lsdir(m_pFs, dir, &entry))
		{
			if(entry.is_dir)
			{
				if (strcmp(entry.filename, strDirName.c_str()) == 0)
				{
					CreateListFileItem(entry);
					break;
				}
			}
		}

		fs_rclose(m_pFs, dir);
	}
}

void CWndMgrTool::DeleteFile()
{
	file_entry FileEntry = m_pCurSelListItem->GetFileEntry();
	
	string strFilePath;
	MakeAbsolutePath(m_pCurSelTreeNode, strFilePath);
	strFilePath += FileEntry.filename;

	if (FileEntry.is_dir == 0)
	{		
		int nRet = fs_fremove(m_pFs, strFilePath.c_str());
		if (nRet == 0)
		{
			SSMessageBox(m_hWnd, "删除文件失败！");
			return;
		}
		else
		{
			m_pListFile->Remove(m_pCurSelListItem);
			m_pCurSelListItem = NULL;

			return;
		}
	}
	else
	{
		int nRet = fs_rmdir(m_pFs, strFilePath.c_str());
		if (nRet == 0)
		{
			SSMessageBox(m_hWnd, "删除文件夹失败！");
			return;
		}
		else
		{
			m_pListFile->Remove(m_pCurSelListItem);
			m_pCurSelListItem = NULL;

			int nChildCount = m_pCurSelTreeNode->GetCountChild();
			CTreeNodeDevice *pChildNode = NULL;
			for (int i=0; i<nChildCount; i++)
			{
				pChildNode = static_cast<CTreeNodeDevice*>(m_pCurSelTreeNode->GetChildNode(i));
				string strText = pChildNode->GetDirText();
				if (StrCmp(strText.c_str(), FileEntry.filename) == 0)
				{
					m_pTreeFile->Remove(pChildNode);
					break;
				}
			}

			return;
		}
	}
}




















void SetClipBoardSelfData( LPCTSTR lpData )
{
	::OpenClipboard(NULL);
	::EmptyClipboard();
	size_t  dataLen = _tcslen(lpData);
	HANDLE h = ::GlobalAlloc(GMEM_FIXED, (dataLen + 1) * sizeof(TCHAR));
	TCHAR *p = (TCHAR *)GlobalLock(h);
	StrCpy(p, lpData);
	SetClipboardData(CF_TEXT, h);
	::GlobalUnlock(h);
	::CloseClipboard();
}


HBITMAP GetIconByFileType(LPCTSTR lpFileType, bool IsDirectory/* = false*/)
{
	HBITMAP hRet = NULL;

	HICON  hLargeIcon = NULL;
	ICONINFO iconInfo;
	int nWidth = 0; 
	int nHeight = 0;

	LONG lRet = 0;

	if (IsDirectory) //为文件夹
	{
		TCHAR strSystemDir[MAX_PATH] = {0};
		GetSystemDirectory(strSystemDir, MAX_PATH);
		lstrcat(strSystemDir, _T("\\shell32.dll"));

		ExtractIconEx(strSystemDir, 3, NULL, &hLargeIcon, 1);	
	}
	else			//为文件
	{
		if (lpFileType == NULL)
		{
			TCHAR strSystemDir[MAX_PATH] = {0};
			GetSystemDirectory(strSystemDir, MAX_PATH);
			lstrcat(strSystemDir, _T("\\shell32.dll"));

			ExtractIconEx(strSystemDir, 0, NULL, &hLargeIcon, 1);						
		}
		else
		{
			if (*lpFileType == _T('.'))
			{
				HKEY hkey = HKEY_CLASSES_ROOT;

				CRegKey regRoot;
				lRet = regRoot.Open(hkey, lpFileType);
				if (lRet == ERROR_SUCCESS)
				{
					TCHAR strRootValue[MAX_PATH] = {0};
					ULONG ulSize = MAX_PATH;
					regRoot.QueryStringValue(_T(""), strRootValue, &ulSize);

					if (StrCmp(strRootValue, _T("")) != 0)
					{
						CRegKey regModule;
						lRet = regModule.Open(hkey,  strRootValue);

						if (lRet == ERROR_SUCCESS)
						{
							CRegKey regIcon;
							lRet = regIcon.Open(regModule, _T("DefaultIcon"));

							if (lRet == ERROR_SUCCESS)
							{									
								TCHAR strIcon[MAX_PATH + 10] = {0};
								ULONG ulIcon = MAX_PATH + 10;
								lRet = regIcon.QueryStringValue(_T(""), strIcon, &ulIcon);								

								if (lRet == ERROR_INVALID_DATA)
								{
									int i = 0;
								}

								LPTSTR lpDot = StrRChr(strIcon, NULL, _T(','));
								if (lpDot == NULL)
								{
									TCHAR strSystemDir[MAX_PATH] = {0};
									GetSystemDirectory(strSystemDir, MAX_PATH);
									lstrcat(strSystemDir, _T("\\shell32.dll"));

									ExtractIconEx(strSystemDir, 2, NULL, &hLargeIcon, 1);		
								}
								else
								{
									LPCTSTR lpNum = lpDot + 1;
									*lpDot = _T('\0');
									LPTSTR lpExePath = strIcon;

									if (StrCmp(lpNum, _T("")) != NULL)
									{
										if (*(lpExePath) == _T('"'))
										{
											lpExePath = lpExePath + 1;
										}

										if (*(lpExePath + _tcslen(lpExePath) - 1) == _T('"') )
										{
											*(lpExePath + _tcslen(lpExePath) - 1) = _T('\0');
										}

										TCHAR strExpand[MAX_PATH + 10] = {0};

										ExpandEnvironmentStrings(lpExePath, strExpand, MAX_PATH +10);

										int iconIndex = _tstoi(lpNum);											
										ExtractIconEx(strExpand, iconIndex, NULL, &hLargeIcon, 1);	
										int i = 0;
									}
									else
									{
										TCHAR strSystemDir[MAX_PATH] = {0};
										GetSystemDirectory(strSystemDir, MAX_PATH);
										lstrcat(strSystemDir, _T("\\shell32.dll"));

										ExtractIconEx(strSystemDir, 0, NULL, &hLargeIcon, 1);											
									}

								}							
							}
						}
					}

				}
			}
		}
	}

	if (hLargeIcon == NULL)
	{
		TCHAR strSystemDir[MAX_PATH] = {0};
		GetSystemDirectory(strSystemDir, MAX_PATH);
		lstrcat(strSystemDir, _T("\\shell32.dll"));

		ExtractIconEx(strSystemDir, 0, NULL, &hLargeIcon, 1);
	}

	if (hLargeIcon != NULL)
	{
		GetIconInfo(hLargeIcon, &iconInfo);		

		BITMAP bmp;
		GetObject(iconInfo.hbmColor, sizeof(BITMAP), &bmp);

		nWidth = bmp.bmWidth;
		nHeight = bmp.bmHeight;

		HDC dcMem;
		dcMem = ::CreateCompatibleDC(NULL);			
		HGDIOBJ hObMem = ::SelectObject(dcMem, iconInfo.hbmColor);				

		HDC dcImage;
		dcImage = ::CreateCompatibleDC(NULL);
		::SetBkMode(dcMem, TRANSPARENT);
		HGDIOBJ hObjImage = ::SelectObject(dcImage, iconInfo.hbmMask);				

		BITMAPINFO bmi;
		ZeroMemory(&bmi, sizeof(BITMAPINFO));
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = nWidth;
		bmi.bmiHeader.biHeight = nHeight;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 32;         // four 8-bit components
		bmi.bmiHeader.biCompression = BI_RGB;
		bmi.bmiHeader.biSizeImage = nWidth * nHeight * sizeof(DWORD);

		BYTE *pvBits;          // pointer to DIB section
		hRet = ::CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void **)&pvBits, NULL, 0);	

		HDC dcRet;
		dcRet = ::CreateCompatibleDC(NULL);
		//::SetBkColor(dcRet, RGB(255,255,255));
		//::SetBkMode(dcRet, TRANSPARENT);
		HGDIOBJ hObjRet = ::SelectObject(dcRet, hRet);			

		::BitBlt(dcRet, 0, 0, nWidth, nHeight, dcImage, 0, 0, SRCCOPY);			
		::BitBlt(dcRet, 0, 0, nWidth, nHeight, dcMem, 0, 0, SRCINVERT);	

		BITMAPINFO MaskBmi;
		ZeroMemory(&MaskBmi, sizeof(BITMAPINFO));
		MaskBmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		MaskBmi.bmiHeader.biWidth = nWidth;
		MaskBmi.bmiHeader.biHeight = nHeight;
		MaskBmi.bmiHeader.biPlanes = 1;
		MaskBmi.bmiHeader.biBitCount = 32;         // four 8-bit components
		MaskBmi.bmiHeader.biCompression = BI_RGB;
		MaskBmi.bmiHeader.biSizeImage = nWidth * nHeight * sizeof(DWORD);

		BYTE *pvMaskBits = new BYTE[nWidth * nHeight * sizeof(DWORD)];
		::GetDIBits(dcImage, iconInfo.hbmMask, 0, nHeight, pvMaskBits, &MaskBmi, DIB_RGB_COLORS);

		for (int i=0; i<nWidth * nHeight; i++)
		{
			if( *(DWORD*)(&pvMaskBits[i*4]) == 0xFFFFFF )
			{
				pvBits[i*4] = (BYTE)0;
				pvBits[i*4 + 1] = (BYTE)0;
				pvBits[i*4 + 2] = (BYTE)0; 
				pvBits[i*4 + 3] = (BYTE)0;
			}
			else
			{
				//pvBits[i*4] = (BYTE)255;
				//pvBits[i*4 + 1] = (BYTE)255;
				//pvBits[i*4 + 2] = (BYTE)255; 
				pvBits[i*4 + 3] = (BYTE)255;
			}
		}

		delete pvMaskBits;

		::SelectObject(dcImage, hObjImage);
		::SelectObject(dcRet, hObjRet);

		::DeleteDC(dcImage);
		::DeleteDC(dcMem);
		::DeleteDC(dcRet);
	}


	return hRet;
}
