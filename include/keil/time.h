#ifndef POSIX_TIME_H
#define POSIX_TIME_H

#include <signal.h>
#include <sys/types.h>

#define MICROSECONDS_PER_SECOND (1000000LL)
#define NANOSECONDS_PER_SECOND (1000000000LL)
#define NANOSECONDS_PER_MICROSECONDS (1000LL)
#define NANOSECONDS_PER_TICK (NANOSECONDS_PER_SECOND / CLOCKS_PER_SEC)
#define CLOCK_REALTIME 0
#define CLOCK_MONOTONIC 1
#define TIMER_ABSTIME 0x01

struct timespec {
  time_t tv_sec;
  long tv_nsec;
};

struct tm {
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;
};

struct itimerspec {
  struct timespec it_interval;
  struct timespec it_value;
};

clock_t clock(void);
int clock_getcpuclockid(pid_t pid, clockid_t *clock_id);
int clock_getres(clockid_t clock_id, struct timespec *res);
int clock_gettime(clockid_t clock_id, struct timespec *tp);
int clock_nanosleep(clockid_t clock_id, int flags, const struct timespec *rqtp,
                    struct timespec *rmtp);
int clock_settime(clockid_t clock_id, const struct timespec *tp);
int nanosleep(const struct timespec *rqtp, struct timespec *rmtp);

#endif  // POSIX_TIME_H
