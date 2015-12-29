// fs.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "fs.h"

int _tloop(void* fs);

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc < 3)
	{
		printf("param invalid.\neg.fs [-o|-c] <filename> <mbytes>\n");
		return 0;
	}

	void* fs = 0;
	if (strcmpi(argv[1], "-o") == 0)
	{
		fs = fs_dopen(argv[2]);
		if (fs == 0)
		{
			printf("open disk %s failed.\n", argv[2]);
			return 0;
		}
	}
	else if (strcmpi(argv[1], "-c") == 0)
	{
		if (argc < 4)
		{
			printf("param invalid.\neg.fs -c <filename> <size>\n");
			return 0;
		}
		fs = fs_dcreate(argv[2], atol(argv[3])*1024*1024);
		if (fs == 0)
		{
			printf("crate disk %s failed.\n", argv[2]);
			return 0;
		}
	}
	else
	{
		printf("param invalid.\neg.fs [-o|-c] <filename> <mbytes>\n");
		return 0;
	}

	_tloop(fs);

	fs_dclose(fs);
	printf("disk %s closed.\n", argv[2]);
	return 0;
}

int parse(vector<string>* argv, string param, char* separator)
{
	argv->clear();
	if (param.empty())
		return 0;
	char* token = strtok((char*)param.c_str(), separator);
	while (token != 0)
	{
		argv->push_back(token);
		token = strtok(0, separator);
	}
	return (int)argv->size();
}

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

int copy(void* fs, int argc, vector<string>& argv);
int cat(void* fs, int argc, vector<string>& argv);
int remove(void* fs, int argc, vector<string>& argv);

int _tloop(void* fs)
{
	HANDLE input = GetStdHandle(STD_INPUT_HANDLE);
	while (1)
	{
		char buf[256];
		printf("fs>");

		DWORD bytes = 0;
		if (!ReadConsole(input, buf, 255, &bytes, 0))
			break;
		while (bytes > 0 && buf[bytes-1] < ' ')
			bytes--;
		buf[bytes] = 0;

		vector<string> argv;
		int argc = parse(&argv, buf, "- /");
		if (argc < 1)
			continue;

		if (strcmpi(argv[0].c_str(), "quit") == 0)
		{
			break;
		}
		else if (strcmpi(argv[0].c_str(), "format") == 0)
		{
			// format
			if (fs_dformat(fs) != 0)
			{
				printf("format error.\n");
				continue;
			}
			printf("format ok.\n");
		}
		else if (strcmpi(argv[0].c_str(), "mkdir") == 0)
		{
			// mkdir <path>
			if (argc < 2)
			{
				printf("mkdir param invalid.\neg. mkdir <path>\n");
				continue;
			}
			if (fs_mkdir(fs, argv[1].c_str()) != 0)
			{
				printf("mkdir error.\n");
				continue;
			}
			printf("mkdir ok.\n");
		}
		else if (strcmpi(argv[0].c_str(), "rmdir") == 0)
		{
			// rmdir <path>
			if (argc < 2)
			{
				printf("rmdir param invalid.\neg. rmdir <path>\n");
				continue;
			}
			if (fs_rmdir(fs, argv[1].c_str()) != 0)
			{
				printf("rmdir error.\n");
				continue;
			}
			printf("rmdir ok.\n");
		}
		else if (strcmpi(argv[0].c_str(), "lsdir") == 0)
		{
			// lsdir <path>
			if (argc < 2)
			{
				printf("lsdir param invalid.\neg. lsdir <path>\n");
				continue;
			}
			void* dir = fs_ropen(fs, argv[1].c_str());
			if (dir == 0)
			{
				printf("open directory failed.\n");
				continue;
			}

			file_entry entry;
			while (fs_lsdir(fs, dir, &entry))
			{
				int i = printf("%s", entry.filename);
				int j = 30 - (i % 30);
				for (int x = 0; x < j; x++)
					printf(" ");

				if (entry.is_dir)
					i = printf("<dir>");
				else
					i = printf("%d", entry.size);
				j = 16 - (i % 16);
				for (int x = 0; x < j; x++)
					printf(" ");

				int d, m, y, h, mn, s;
				from_time(entry.create_time, &h, &m, &s);
				from_date(entry.create_date, &d, &mn, &y);
				printf("%02d/%02d/%04d  %02d:%02d", d, mn, y, h, m);
				printf("\n");
			}
			fs_rclose(fs, dir);
			printf("lsdir ok.\n");
		}
		else if (strcmpi(argv[0].c_str(), "copy") == 0)
		{
			// copy [-l] <src> [-l] <dest>
			copy(fs, argc, argv);
		}
		else if (strcmpi(argv[0].c_str(), "cat") == 0)
		{
			// cat <filename>
			cat(fs, argc, argv);
		}
		else if (strcmpi(argv[0].c_str(), "remove") == 0)
		{
			// remove <filename>
			remove(fs, argc, argv);
		}
		else
		{
			printf("invalid command.\n");
		}
	}

	return 0;
}

int copy(void* fs, FILE* lf, const char* filename)
{
	void* vf = fs_fopen(fs, filename, "wb");
	if (vf == 0)
		return -1;
	while (!feof(lf))
	{
		char buf[4096];
		int size = fread(buf, 1, 4096, lf);
		if (size > 0)
		{
			int bytes = fs_fwrite(fs, buf, 1, size, vf);
			if (size != bytes)
			{
				fs_fclose(fs, vf);
				return -1;
			}
		}
	}
	fs_fclose(fs, vf);
	return 0;
}

int copy(void* fs, const char* filename, FILE* lf)
{
	void* vf = fs_fopen(fs, filename, "rb");
	if (vf == 0)
		return -1;
	while (!fs_feof(fs, vf))
	{
		char buf[4096];
		int size = fs_fread(fs, buf, 1, 4096, vf);
		if (size > 0)
		{
			int bytes = fwrite(buf, 1, size, lf);
			if (size != bytes)
			{
				fs_fclose(fs, vf);
				return -1;
			}
		}
	}
	fs_fclose(fs, vf);
	return 0;
}

int copy(void* fs, int argc, vector<string>& argv)
{
	if (argc < 3)
	{
		printf("copy param invalid.\neg. copy [-l] <src> [-l] <dest>\n");
		return 0;
	}
	if (strcmpi(argv[1].c_str(), "l") == 0)
	{
		// local -> fs
		if (argc < 4)
		{
			printf("copy param invalid.\neg. copy [-l] <src> <dest>\n");
			return 0;
		}
		FILE* lf = fopen(argv[2].c_str(), "rb");
		if (lf == 0)
		{
			printf("open file %s failed.\n", argv[2].c_str());
			return 0;
		}
		if (copy(fs, lf, argv[3].c_str()) != 0)
		{
			printf("copy file %s failed.\n", argv[2].c_str());
		}
		fclose(lf);
	}
	if (strcmpi(argv[2].c_str(), "l") == 0)
	{
		// fs -> local
		if (argc < 4)
		{
			printf("copy param invalid.\neg. copy <src> [-l] <dest>\n");
			return 0;
		}
		FILE* lf = fopen(argv[3].c_str(), "wb");
		if (lf == 0)
		{
			printf("open file %s failed.\n", argv[3].c_str());
			return 0;
		}
		if (copy(fs, argv[1].c_str(), lf) != 0)
		{
			printf("copy file %s failed.\n", argv[2].c_str());
		}
		fclose(lf);
	}

	return 0;
}

int cat(void* fs, int argc, vector<string>& argv)
{
	// cat <filename>
	if (argc < 2)
	{
		printf("cat param invalid.\neg. cat <filename>\n");
		return 0;
	}
	void* vf = fs_fopen(fs, argv[1].c_str(), "rb");
	if (vf == 0)
	{
		printf("open file %s failed.\n", argv[1].c_str());
		return -1;
	}
	while (!fs_feof(fs, vf))
	{
		char buf[4097];
		int size = fs_fread(fs, buf, 1, 4096, vf);
		if (size > 0)
		{
			buf[size] = 0;
			printf("%s", buf);
		}
	}
	printf("\n");
	fs_fclose(fs, vf);
	return 0;
}


int remove(void* fs, int argc, vector<string>& argv)
{
	// remove <filename>
	if (argc < 2)
	{
		printf("remove param invalid.\neg. remove <filename>\n");
		return 0;
	}
	if (fs_fremove(fs, argv[1].c_str()) != 0)
	{
		printf("remove file %s failed.\n", argv[1].c_str());
		return -1;
	}
	return 0;
}

