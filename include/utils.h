#ifndef POSIX_Utils_H
#define POSIX_Utils_H

#include "time.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define MICROSECONDS_PER_SECOND (1000000LL)
#define NANOSECONDS_PER_SECOND (1000000000LL)
#define NANOSECONDS_PER_MICROSECONDS (1000LL)
#define NANOSECONDS_PER_TICK (NANOSECONDS_PER_SECOND / CLOCKS_PER_SEC)

size_t Utils_strnlen(const char *const str, size_t maxLength);
int Utils_absoluteTimespecToDeltaTicks(
    const struct timespec *const absoluteTime,
    const struct timespec *const currentTime, clock_t *const result);
int Utils_timespecToTicks(const struct timespec *const ts,
                          clock_t *const result);
void Utils_nanosecondsToTimespec(int64_t llSource,
                                 struct timespec *const destination);
int Utils_timespecAdd(const struct timespec *const x,
                      const struct timespec *const y,
                      struct timespec *const result);
int Utils_timespecAddNanoseconds(const struct timespec *const x,
                                 int64_t nanoseconds,
                                 struct timespec *const result);
int Utils_timespecSubtract(const struct timespec *const x,
                           const struct timespec *const y,
                           struct timespec *const result);
int Utils_timespecCompare(const struct timespec *const x,
                          const struct timespec *const y);
bool Utils_validateTimespec(const struct timespec *const ts);

#endif // POSIX_Utils_H
