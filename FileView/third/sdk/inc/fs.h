#ifndef __FS_H__
#define __FS_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef	int (*pfd_read)(void* fd, unsigned long sector, unsigned char *buffer, unsigned long sector_count);
typedef	int (*pfd_write)(void* fd, unsigned long sector, unsigned char *buffer, unsigned long sector_count);

	void*	fs_init(pfd_read fd_read, pfd_write fd_write, void* fd);
	void	fs_clear(void* fs);

	// 文件操作
	void*	fs_fopen(void* fs, const char *path, const char *modifiers);
	void	fs_fclose(void* fs, void *file);
	int		fs_fflush(void* fs, void *file);
	int		fs_fgetc(void* fs, void *file);
	int		fs_fungetc(void* fs, int c, void *file);
	char*	fs_fgets(void* fs, char *s, int n, void *f);
	int		fs_fputc(void* fs, int c, void *file);
	int		fs_fputs(void* fs, const char * str, void *file);
	int		fs_fwrite(void* fs, const void * data, int size, int count, void *file);
	int		fs_fread(void* fs, void * data, int size, int count, void *file);
	int		fs_fseek(void* fs, void *file, long offset, int origin);
	int		fs_fgetpos(void* fs, void *file, unsigned long * position);
	long	fs_ftell(void* fs, void *f);
	int		fs_feof(void* fs, void *f);
	int		fs_fremove(void* fs, const char * filename);

	// 目录操作
	typedef struct _t_file_entry{
		char            filename[260];
		unsigned char   is_dir;

		unsigned long	size;

		unsigned short  create_date;
		unsigned short  create_time;

	}file_entry;

	int		fs_mkdir(void* fs, const char *path);
	int		fs_rmdir(void* fs, const char *path);

	void*	fs_ropen(void* fs, const char *path);
	int		fs_lsdir(void* fs, void* dir, file_entry* entry);
	void	fs_rclose(void* fs, void* dir);

#ifdef __cplusplus
}
#endif

#endif
