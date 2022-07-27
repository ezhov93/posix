#ifndef POSIX_IO_H
#define POSIX_IO_H

// #define FOPEN_MAX 4;

/*
// check user's permissions for a file
int access(const char *filename, int _AccessMode);
// mod is the command and system call used to change the access permissions of
file system objects int chmod(const char *filename, int _AccessMode);
//changesize
int chsize(int fileHandle, long size);
*/

/*
int close(int fileHandle);
int eof(int fileHandle);
long filelength(int fileHandle);
int isatty(int fileHandle);
long lseek(int fileHandle, long offset, int origin);
int open(const char *filename, int openFlag, ...);
int read(int fileHandle, void *dstBuf, unsigned int maxCharCount);
int setmode(int fileHandle, int mode);
// Function reports the offset of the current byte relative to the beginning of
// the file associated with the file descriptor.
long tell(int fileHandle);
int umask(int mode);
int write(int fileHandle, const void *buf, unsigned int maxCharCount);
void sync(void);
int syncfs(int fd);
int fcntl(int fd, int cmd, ...);
int iocntl(int fd, int cmd, ...);
*/

#endif  // POSIX_IO_H