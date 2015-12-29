#pragma once
#include "stdafx.h"

#include "windows.h"
#include <string>

#include <shlwapi.h>
#include <Dbghelp.h>

#pragma comment(lib,"shlwapi.lib")
#pragma comment(lib, "Dbghelp.lib")

#ifdef _UNICODE
#define st_string std::wstring
#else
#define st_string std::string
#endif

namespace CatchDumpFile 
{
	class CDumpCatch
	{
	public:
		CDumpCatch();
		~CDumpCatch();
	private:

		static LPTOP_LEVEL_EXCEPTION_FILTER WINAPI TempSetUnhandledExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter);
		static BOOL ReleaseDumpFile(const st_string& strPath, EXCEPTION_POINTERS *pException);
		static LONG WINAPI UnhandledExceptionFilterEx(struct _EXCEPTION_POINTERS *pException);
		static void MyPureCallHandler(void);
		static void MyInvalidParameterHandler(const wchar_t * expression, const wchar_t * function, const wchar_t * file, unsigned int line, uintptr_t pReserved);
		
		BOOL AddExceptionHandle();
		BOOL RemoveExceptionHandle();
		BOOL PreventSetUnhandledExceptionFilter();

		void SetInvalidHandle();
		void UnSetInvalidHandle();
	private:
		LPTOP_LEVEL_EXCEPTION_FILTER m_preFilter;
		_invalid_parameter_handler m_preIph;
		_purecall_handler m_prePch;    
	};
};