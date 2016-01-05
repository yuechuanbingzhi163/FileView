#pragma once

#include "stdafx.h"

string GetDescByFileType(LPCTSTR lpFileExtension);


class CListContainerElementFile: public CListContainerElementUI
{
public:
    CListContainerElementFile( );
    virtual ~CListContainerElementFile();

	LPCTSTR GetClass() const;

	void SetFileEntry(file_entry &FileEntry);
	file_entry GetFileEntry();

	void SetIconName(LPCTSTR lpIconName);

private:
	file_entry m_FileEntry;

	CLabelUI *m_pFileName;
	CLabelUI *m_pFileType;
	CLabelUI *m_pFileSize;
	CLabelUI *m_pFileDate;
};