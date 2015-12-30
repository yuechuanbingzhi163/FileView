#include "stdafx.h"
#include "CListContainerElementLicense.h"

CListContainerElementLicense::CListContainerElementLicense(  )
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

CListContainerElementLicense::~CListContainerElementLicense()
{

}

void CListContainerElementLicense::SetFileEntry(file_entry &FileEntry)
{
	m_FileEntry = FileEntry;

	m_pFileName->SetText(m_FileEntry.filename);
	m_pFileType->SetText("文件");
	if (m_FileEntry.is_dir)
	{
		m_pFileType->SetText("文件夹");
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

void CListContainerElementLicense::SetIconName(LPCTSTR lpIconName)
{
	TCHAR bkImg[MAX_PATH] = {0};
	StringCchPrintf(bkImg, _countof(bkImg), _T("file='%s' dest='%d,%d,%d,%d'"), lpIconName, 4, 4, 20, 20);
	m_pFileName->SetAttribute("bkimage", bkImg);
}

file_entry CListContainerElementLicense::GetFileEntry()
{
	return m_FileEntry;
}

LPCTSTR CListContainerElementLicense::GetClass() const
{
	return _T("CListContainerElementFIle");
}







