#ifndef POSIX_FCNTL_H
#define POSIX_FCNTL_H

#include "io.h"

// @ File creation flags for use in the oflag value to open() and openat()
// Close the file descriptor upon exec()
#define O_CLOEXEC 0x0001
// Create file if it does not exist.
#define O_CREAT 0x0002
// Fail if file is a non-directory file.
#define O_DIRECTORY 0x0004
// Exclusive use flag.
#define O_EXCL 0x0008
// Do not assign controlling terminal.
#define O_NOCTTY 0x0010
// Do not follow symbolic links.
#define O_NOFOLLOW 0x0020
// Truncate flag.
#define O_TRUNC 0x0040
// termios structure provides conforming behavior.
#define O_TTY_INIT 0x0080

// @ File status flags for open(), openat(), and fcntl().
// Set append mode.
#define O_APPEND 0x0100
// Write according to synchronized I/O data integrity completion.
#define O_DSYNC 0x0200
// Non-blocking mode.
#define O_NONBLOCK 0x0400
// Synchronized read I/O operations.
#define O_RSYNC 0x0800
// Write according to synchronized I/O file integrity completion.
#define O_SYNC 0x0200

// Mask for file access modes.
#define O_ACCMODE 0xF000

// @ File access modes for open(), openat(), and fcntl().
// Open for execute only (non-directory files)
#define O_EXEC 0x1000
// Open for reading only.
#define O_RDONLY 0x2000
// Open for reading and writing.
#define O_RDWR 0xA000
// Open directory for search only.
#define O_SEARCH 0x4000
// Open for writing only.
#define O_WRONLY 0x8000

#endif // POSIX_FCNTL_H
