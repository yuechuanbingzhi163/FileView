#include "stdafx.h"
#include "CListContainerElementLicense.h"

CListContainerElementFile::CListContainerElementFile(  )
{
	SetFixedHeight(25);
	SetAttribute("menu", "true");

	m_pFileName = new CLabelUI;
	m_pFileName->SetTextColor(0xff444444);
	m_pFileName->SetAttribute("textpadding", "24,0,0,0");
	m_pFileType = new CLabelUI;
	m_pFileType->SetTextColor(0xff444444);
	m_pFileSize = new CLabelUI;
	m_pFileSize->SetTextColor(0xff444444);
	m_pFileDate = new CLabelUI;
	m_pFileDate->SetTextColor(0xff444444);

	AddAt(m_pFileName, 0);
	AddAt(m_pFileType, 1);
	AddAt(m_pFileSize, 2);
	AddAt(m_pFileDate, 3);
}

CListContainerElementFile::~CListContainerElementFile()
{

}

void CListContainerElementFile::SetFileEntry(file_entry &FileEntry)
{
	m_FileEntry = FileEntry;

	m_pFileName->SetText(m_FileEntry.filename);
	
	if (m_FileEntry.is_dir)
	{
		m_pFileType->SetText("文件夹");
	}
	else
	{
		string strDesc = "文件";
		LPTSTR lpTemp = m_FileEntry.filename + _tcslen(m_FileEntry.filename);
		int i = _tcslen(m_FileEntry.filename);
		bool b = false;
		while (i >= 0)
		{
			if (*lpTemp == '.')
			{
				b = true;
				break;
			}
			else
			{
				lpTemp--;
				i--;
			}
		}

		if (b)
		{
			strDesc = GetDescByFileType(lpTemp);
		}

		m_pFileType->SetText(strDesc.c_str());		
	}

	if (m_FileEntry.is_dir != 1)
	{
		char szSize[10] = {0};
		sprintf_s(szSize, sizeof(szSize), ("%d"), m_FileEntry.size);
		m_pFileSize->SetText(szSize);
	}	

	char szTime[60] = {0};
	int d, m, y, h, mn, s;
	from_time(m_FileEntry.create_time, &h, &m, &s);
	from_date(m_FileEntry.create_date, &d, &mn, &y);
	sprintf_s(szTime, sizeof(szTime), "%04d/%02d/%02d  %02d:%02d:%02d", y, mn, d, h, m, s);
	m_pFileDate->SetText(szTime);
}

void CListContainerElementFile::SetIconName(LPCTSTR lpIconName)
{
	TCHAR bkImg[MAX_PATH] = {0};
	StringCchPrintf(bkImg, _countof(bkImg), _T("file='%s' dest='%d,%d,%d,%d'"), lpIconName, 4, 4, 20, 20);
	m_pFileName->SetAttribute("bkimage", bkImg);
}

file_entry CListContainerElementFile::GetFileEntry()
{
	return m_FileEntry;
}

LPCTSTR CListContainerElementFile::GetClass() const
{
	return _T("CListContainerElementFIle");
}

std::string GetDescByFileType( LPCTSTR lpFileExtension )
{
	string strRet = "文件";

	do 
	{
		if (lpFileExtension == NULL)
		{
			break;
		}

		LPCTSTR lpTemp = lpFileExtension + 1;
		if (lpTemp != NULL)
		{
			strRet = lpTemp;
			strRet += "文件";
		}

		LONG lRet = 0;
		HKEY hkey = HKEY_CLASSES_ROOT;

		CRegKey regRoot;
		lRet = regRoot.Open(hkey, lpFileExtension, KEY_READ);
		if (lRet == ERROR_SUCCESS)
		{
			TCHAR strRootValue[MAX_PATH] = {0};
			ULONG ulSize = MAX_PATH;
			regRoot.QueryStringValue(_T(""), strRootValue, &ulSize);

			if (StrCmp(strRootValue, _T("")) != 0)
			{
				CRegKey regModule;
				lRet = regModule.Open(hkey,  strRootValue, KEY_READ);

				if (lRet == ERROR_SUCCESS)
				{
					TCHAR strDesc[MAX_PATH] = {0};
					ULONG ulDescSize = MAX_PATH;
					regModule.QueryStringValue(_T(""), strDesc, &ulDescSize);
					if (StrCmp(strDesc, "") != 0)
					{
						strRet = strDesc;
					}
				}
			}
		}

	} while (FALSE);

	return strRet;
}
