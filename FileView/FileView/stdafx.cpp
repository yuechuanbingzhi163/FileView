// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// FileView.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

// TODO: �� STDAFX.H ��
// �����κ�����ĸ���ͷ�ļ����������ڴ��ļ�������

void from_time(unsigned short fat_time, int *hours, int *minutes, int *seconds)
{
	*hours = (fat_time >> FAT_TIME_HOURS_SHIFT) & FAT_TIME_HOURS_MASK;
	*minutes = (fat_time >> FAT_TIME_MINUTES_SHIFT) & FAT_TIME_MINUTES_MASK;
	*seconds = (fat_time >> FAT_TIME_SECONDS_SHIFT) & FAT_TIME_SECONDS_MASK;
	*seconds = *seconds * FAT_TIME_SECONDS_SCALE;
}

void from_date(unsigned short fat_date, int *day, int *month, int *year)
{
	*day = (fat_date >> FAT_DATE_DAY_SHIFT) & FAT_DATE_DAY_MASK;
	*month = (fat_date >> FAT_DATE_MONTH_SHIFT) & FAT_DATE_MONTH_MASK;
	*year = (fat_date >> FAT_DATE_YEAR_SHIFT) & FAT_DATE_YEAR_MASK;
	*year = *year + FAT_DATE_YEAR_OFFSET;
}