// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

//#define UI_USE_ZIP

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ

#include <afxwin.h>

// Windows ͷ�ļ�:
#include <windows.h>

#include "resource.h"

// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <Shlwapi.h>
#include <Strsafe.h>
#include <shlobj.h>

#include <stdio.h>
#include <string>
using namespace std;

#include "logging.h"

#pragma comment(lib, "shlwapi.lib")

#include "fs.h"
#include "tool.h"

#pragma comment(lib, "fs_x86.lib")
#pragma comment(lib, "lock_x86.lib")
#pragma comment(lib, "lua_x86.lib")


#include "UIlib.h"
using namespace DuiLib;

#ifdef UNICODE
#define string_t	std::wstring
#else
#define string_t	std::string
#endif


#define  WM_EXIT_APP				(WM_USER + 0X0010)
#define  WM_NIDTIP					(WM_USER + 0x0011)











