#ifndef POSIX_ERRNO_H
#define POSIX_ERRNO_H

// Undefine all errnos to avoid redefinition errors with system errnos.
#undef EPERM
#undef ENOENT
#undef EBADF
#undef EAGAIN
#undef ENOMEM
#undef EEXIST
#undef EBUSY
#undef EINVAL
#undef ENOSPC
#undef ERANGE
#undef ENAMETOOLONG
#undef EDEADLK
#undef EOVERFLOW
#undef ENOSYS
#undef EMSGSIZE
#undef ENOTSUP
#undef ETIMEDOUT

// Definition of POSIX errnos.
#define EPERM 1         // Operation not permitted.
#define ENOENT 2        // No such file or directory.
#define EBADF 9         // Bad file descriptor.
#define EAGAIN 11       // Resource unavailable, try again.
#define ENOMEM 12       // Not enough space.
#define EEXIST 17       // File exists.
#define EBUSY 16        // Device or resource busy.
#define EINVAL 22       // Invalid argument.
#define ENOSPC 28       // No space left on device.
#define ERANGE 34       // Result too large.
#define ENAMETOOLONG 36 // File name too long.
#define EDEADLK 45      // Resource deadlock would occur.
#define EOVERFLOW 75    // Value too large to be stored in data type.
#define ENOSYS 88       // Function not supported.
#define EMSGSIZE 90     // Message too long.
#define ENOTSUP 95      // Operation not supported.
#define ETIMEDOUT 116   // Connection timed out.

extern int errno;

#endif // POSIX_ERRNO_H