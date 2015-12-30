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
#include <list>

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


//-----------------------------------------------------------------------------
// Time / Date details
//-----------------------------------------------------------------------------
#define FAT_TIME_HOURS_SHIFT            11
#define FAT_TIME_HOURS_MASK             0x1F
#define FAT_TIME_MINUTES_SHIFT          5
#define FAT_TIME_MINUTES_MASK           0x3F
#define FAT_TIME_SECONDS_SHIFT          0
#define FAT_TIME_SECONDS_MASK           0x1F
#define FAT_TIME_SECONDS_SCALE          2
#define FAT_DATE_YEAR_SHIFT             9
#define FAT_DATE_YEAR_MASK              0x7F
#define FAT_DATE_MONTH_SHIFT            5
#define FAT_DATE_MONTH_MASK             0xF
#define FAT_DATE_DAY_SHIFT              0
#define FAT_DATE_DAY_MASK               0x1F
#define FAT_DATE_YEAR_OFFSET            1980


#define  WM_EXIT_APP				(WM_USER + 0X0010)
#define  WM_NIDTIP					(WM_USER + 0x0011)

void from_time(unsigned short fat_time, int *hours, int *minutes, int *seconds);
void from_date(unsigned short fat_date, int *day, int *month, int *year);









