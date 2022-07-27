#include <stddef.h>
#include <string.h>

#include "utils.h"
#include <errno.h>
#include <sys/types.h>
#include <time.h>

#include "CxemaI6.h"

#ifdef _WIN32
clock_t Retarget_clockOverflow() { return 0; }
#elif __MINGW32__
clock_t Retarget_clockOverflow() { return 0; }
#elif __unix__
clock_t Retarget_clockOverflow() { return 0; }
#elif __linux__
clock_t Retarget_clockOverflow() { return 0; }
#elif __APPLE__
clock_t Retarget_clockOverflow() { return 0; }
#else
extern clock_t Retarget_clock();
extern clock_t Retarget_clockOverflow();
clock_t clock() { return Retarget_clock(); }
#endif

int clock_getcpuclockid(pid_t pid, clockid_t *clock_id) {

  (void)pid;
  (void)clock_id;
  return EPERM;
}

int clock_getres(clockid_t clock_id, struct timespec *res) {
  (void)clock_id;
  if (res != NULL) {
    res->tv_sec = 0;
    res->tv_nsec = NANOSECONDS_PER_TICK;
  }

  return 0;
}

int clock_gettime(clockid_t clock_id, struct timespec *tp) {
  (void)clock_id;
  uint64_t tickCount = ( uint64_t )Retarget_clockOverflow() << (sizeof(clock_t) * 8);
  tickCount += clock();
  Utils_nanosecondsToTimespec((int64_t)tickCount * NANOSECONDS_PER_TICK, tp);
  return 0;
}

int clock_nanosleep(clockid_t clock_id, int flags, const struct timespec *rqtp,
                    struct timespec *rmtp) {
  int status = 0;
  clock_t sleepTime = 0;
  struct timespec currentTime = {0};

  (void)clock_id;
  (void)rmtp;
  (void)flags;

  if (Utils_validateTimespec(rqtp) == false)
    status = EINVAL;

  if ((status == 0) && (clock_gettime(CLOCK_REALTIME, &currentTime) != 0))
    status = EINVAL;

  if (status == 0) {
    clock_t tickstart;
    if ((flags & TIMER_ABSTIME) == TIMER_ABSTIME) {
      if (clock_gettime(CLOCK_REALTIME, &currentTime) != 0)
        status = EINVAL;
      if ((status == 0) && (Utils_absoluteTimespecToDeltaTicks(
                                rqtp, &currentTime, &sleepTime) == 0)) {
        tickstart = clock();
        while (clock() - tickstart < sleepTime)
          asm volatile("nop");
      }
    } else {
      if (Utils_timespecToTicks(rqtp, &sleepTime) == 0) {
        tickstart = clock();
        while (clock() - tickstart < sleepTime)
          asm volatile("nop");
      }
    }
  }
  return status;
}

int clock_settime(clockid_t clock_id, const struct timespec *tp) {
  (void)clock_id;
  (void)tp;
  errno = EPERM;
  return -1;
}

int nanosleep(const struct timespec *rqtp, struct timespec *rmtp) {
  int status = 0;
  clock_t sleepTime = 0;
  (void)rmtp;
  if (Utils_validateTimespec(rqtp) == false) {
    errno = EINVAL;
    status = -1;
  }
  if (status == 0) {
    if (Utils_timespecToTicks(rqtp, &sleepTime) == 0) {
      size_t tickstart = clock();
      while (clock() - tickstart < sleepTime)
        asm volatile("nop");
    }
  }
  return status;
}
