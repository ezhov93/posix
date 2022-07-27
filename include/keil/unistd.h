#ifndef POSIX_UNISTD_H
#define POSIX_UNISTD_H

#include <stdlib.h>
#include <sys/types.h>
#include "io.h"

/* These are also defined in stdio.h. */
#ifndef SEEK_SET
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#endif

/* These are also defined in stdio.h. */
#ifndef STDIN_FILENO
#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2
#endif

unsigned sleep(unsigned seconds);
int usleep(useconds_t usec);

/*
static inline int ftruncate(int fd, off_t lenght) {
	return chsize(fd,lenght);
}
*/
void swab(const void *restrict, void *restrict, ssize_t);

#endif // POSIX_UNISTD_H
