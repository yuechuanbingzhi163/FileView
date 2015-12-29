#pragma once

#include "windows.h"
#include <string>

#define  LOG(format, ...)  CLog::WriteLog(format, ##__VA_ARGS__)

using namespace std;

class CLog
{
public:
	static void Init();
	static void WriteLog(LPCTSTR lpstrFormat, ...);

private:
	CLog();
	~CLog();	

private:
	static CRITICAL_SECTION m_Critical_section;
	static HANDLE m_hFile;
	static string m_hFileDir;

private:
	class destroy
	{
	public:
		destroy();
		~destroy();
	};
};