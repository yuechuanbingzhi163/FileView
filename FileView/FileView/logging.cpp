#include "stdafx.h"
#include "logging.h"
#include <stdio.h>
#include <Shlwapi.h>
#include <tchar.h>

CRITICAL_SECTION CLog::m_Critical_section;
HANDLE CLog::m_hFile = NULL;
std::string CLog::m_hFileDir;

CLog::CLog()
{
	
}

CLog::~CLog()
{
	
}

void CLog::Init()
{
	static destroy des;

	TCHAR szPath[MAX_PATH]  = {0};
	GetModuleFileName(NULL, szPath, sizeof(szPath));
	PathRemoveFileSpec(szPath);

	StrCat(szPath, "\\log\\");
	if (!PathFileExists(szPath))
	{
		BOOL bRet = CreateDirectory(szPath, NULL);
		if (!bRet)
		{
			MessageBox(NULL, "创建日志目录失败!", "提示", MB_OK);
		}
	}
	else
	{
		m_hFileDir = szPath;
	}
}

void CLog::WriteLog( LPCTSTR lpstrFormat, ... )
{
	EnterCriticalSection(&m_Critical_section);

	SYSTEMTIME curTime;
	GetLocalTime(&curTime);

	TCHAR szTemp[MAX_PATH] = {0};
	sprintf_s(szTemp, sizeof(szTemp), "%d_%d_%d.txt", curTime.wYear, curTime.wMonth, curTime.wDay);
	
	string strLogFilePath = m_hFileDir;
	strLogFilePath += szTemp;

	if (!PathFileExists(strLogFilePath.c_str()))
	{
		if (m_hFile != NULL)
		{
			CloseHandle(m_hFile);
			m_hFile = NULL;
		}

		HANDLE hFile = CreateFile(strLogFilePath.c_str(), GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(NULL, "创建日志文件失败!", "提示", MB_OK);
		}
		else
		{
			m_hFile = hFile;
		}
	}
	else
	{
		if (m_hFile == NULL)
		{
			m_hFile = CreateFile(strLogFilePath.c_str(), GENERIC_ALL, FILE_SHARE_READ , NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (m_hFile == INVALID_HANDLE_VALUE)
			{
				MessageBox(NULL, "打开日志文件失败!", "提示", MB_OK);
				m_hFile = NULL;
			}
		}
	}

	if (m_hFile != NULL)
	{
		TCHAR szTime[100] = {0};
		sprintf_s(szTime, sizeof(szTime), "[%d/%02d/%02d %02d:%02d:%02d] ", curTime.wYear, curTime.wMonth, curTime.wDay, curTime.wHour, curTime.wMinute, curTime.wSecond);

		TCHAR szLogItem[1000] = {0};
		va_list args;
		va_start(args, lpstrFormat);
		vsnprintf(szLogItem, sizeof(szLogItem), lpstrFormat, args);
		va_end(args);

		TCHAR szLog[1100] = {0};
		sprintf_s(szLog, sizeof(szLog), "%s%s\n", szTime, szLogItem);

		SetFilePointer(m_hFile, 0, 0, FILE_END);
		WriteFile(m_hFile, (LPVOID)szLog, _tcslen(szLog) * sizeof(TCHAR), NULL, NULL);		
	}	

	LeaveCriticalSection(&m_Critical_section);
}



CLog::destroy::destroy()
{
	InitializeCriticalSection(&m_Critical_section);
}

CLog::destroy::~destroy()
{
	DeleteCriticalSection(&m_Critical_section);

	if (m_hFile != NULL)
	{
		CloseHandle(m_hFile);
		m_hFile = NULL;
	}
}
