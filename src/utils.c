#include <limits.h>
#include <stddef.h>
#include <errno.h>
#include <utils.h>

size_t Utils_strnlen(const char *const str, size_t maxlength) {
  const char *charPointer = str;
  size_t length = 0;

  if (str != NULL) {
    while ((*charPointer != '\0') && (length < maxlength)) {
      length++;
      charPointer++;
    }
  }

  return length;
}

int Utils_absoluteTimespecToDeltaTicks(
    const struct timespec *const absoluteTime,
    const struct timespec *const currentTime, clock_t *const result) {
  int status = 0;
  struct timespec difference = {0};

  if ((absoluteTime == NULL) || (currentTime == NULL) || (result == NULL))
    status = EINVAL;

  if (status == 0) {
    status = Utils_timespecSubtract(absoluteTime, currentTime, &difference);
    if (status == 1)
      status = ETIMEDOUT;
    else if (status == -1)
      status = EINVAL;
  }
  if (status == 0)
    status = Utils_timespecToTicks(&difference, result);

  return status;
}

int Utils_timespecToTicks(const struct timespec *const ts,
                          clock_t *const result) {
  int status = 0;
  int64_t totalTicks = 0;
  long nanoseconds = 0;

  if ((ts == NULL) || (result == NULL))
    status = EINVAL;
  else if ((status == 0) && (Utils_validateTimespec(ts) == false))
    status = EINVAL;

  if (status == 0) {
    totalTicks = (int64_t)CLOCKS_PER_SEC * (ts->tv_sec);
    nanoseconds = ts->tv_nsec / (long)NANOSECONDS_PER_TICK +
                  (long)(ts->tv_nsec % (long)NANOSECONDS_PER_TICK != 0);
    totalTicks += (int64_t)nanoseconds;
    if (totalTicks < 0) {
      status = EINVAL;
    } else {
      uint32_t tickTypeSize = sizeof(clock_t);
      if (tickTypeSize == sizeof(uint32_t)) {
        if (totalTicks > UINT_MAX) {
          status = EINVAL;
        }
      }
    }
    *result = (clock_t)totalTicks;
  }
  return status;
}

void Utils_nanosecondsToTimespec(int64_t source,
                                 struct timespec *const destination) {
  long carrySec = 0;
  destination->tv_sec = (time_t)(source / NANOSECONDS_PER_SECOND);
  destination->tv_nsec = (long)(source % NANOSECONDS_PER_SECOND);
  if (destination->tv_nsec < 0L) {
    carrySec = (destination->tv_nsec / (long)NANOSECONDS_PER_SECOND) + 1L;
    destination->tv_sec -= (time_t)(carrySec);
    destination->tv_nsec += carrySec * (long)NANOSECONDS_PER_SECOND;
  }
}

int Utils_timespecAdd(const struct timespec *const x,
                      const struct timespec *const y,
                      struct timespec *const result) {
  uint64_t partialSec = 0;
  int status = 0;

  if ((result == NULL) || (x == NULL) || (y == NULL) || (x->tv_sec < 0) ||
      (x->tv_nsec < 0) || (y->tv_sec < 0) || (y->tv_nsec < 0))
    status = -1;

  if (status == 0) {
    result->tv_nsec = x->tv_nsec + y->tv_nsec;
    if ((result->tv_nsec < x->tv_nsec) || (result->tv_nsec < y->tv_nsec)) {
      status = 1;
    } else {
      partialSec = (result->tv_nsec) / NANOSECONDS_PER_SECOND;
      result->tv_nsec = (result->tv_nsec) % NANOSECONDS_PER_SECOND;
      result->tv_sec = x->tv_sec + y->tv_sec + partialSec;
      if ((result->tv_sec < x->tv_sec) || (result->tv_sec < y->tv_sec) ||
          (result->tv_sec < partialSec))
        status = 1;
    }
  }

  return status;
}

int Utils_timespecAddNanoseconds(const struct timespec *const x,
                                 int64_t lnanoseconds,
                                 struct timespec *const result) {
  int64_t totalNSec = 0;
  int status = 0;
  if ((result == NULL) || (x == NULL))
    status = -1;
  if (status == 0) {
    totalNSec = x->tv_nsec + lnanoseconds;
    if (totalNSec < 0) {
      status = 1;
    } else {
      result->tv_nsec = totalNSec % NANOSECONDS_PER_SECOND;
      result->tv_sec = x->tv_sec + (totalNSec / NANOSECONDS_PER_SECOND);
      if (result->tv_sec < 0) {
        status = 1;
      }
    }
  }
  return status;
}

int Utils_timespecSubtract(const struct timespec *const x,
                           const struct timespec *const y,
                           struct timespec *const result) {
  int compareResult = 0;
  int status = 0;

  if ((result == NULL) || (x == NULL) || (y == NULL))
    status = -1;

  if (status == 0) {
    compareResult = Utils_timespecCompare(x, y);
    if (compareResult == -1) {
      status = 1;
      result->tv_sec = 0;
      result->tv_nsec = 0;
    } else {
      result->tv_sec = x->tv_sec - y->tv_sec;
      result->tv_nsec = x->tv_nsec - y->tv_nsec;
      if (result->tv_nsec < 0) {
        result->tv_sec--;
        result->tv_nsec += (long)NANOSECONDS_PER_SECOND;
      }
      if (result->tv_nsec < 0) {
        status = -1;
      }
    }
  }
  return status;
}

int Utils_timespecCompare(const struct timespec *const x,
                          const struct timespec *const y) {
  int status = 0;
  if ((x == NULL) && (y == NULL)) {
    status = 0;
  } else if (y == NULL) {
    status = 1;
  } else if (x == NULL) {
    status = -1;
  } else if (x->tv_sec > y->tv_sec) {
    status = 1;
  } else if (x->tv_sec < y->tv_sec) {
    status = -1;
  } else {
    if (x->tv_nsec > y->tv_nsec) {
      status = 1;
    } else if (x->tv_nsec < y->tv_nsec) {
      status = -1;
    } else {
      status = 0;
    }
  }

  return status;
}

bool Utils_validateTimespec(const struct timespec *const ts) {
  bool ret = false;
  if (ts != NULL) {
    if ((ts->tv_nsec >= 0) && (ts->tv_nsec < NANOSECONDS_PER_SECOND)) {
      ret = true;
    }
  }
  return ret;
}
