#include <errno.h>
#include <stddef.h>
// #define _POSIX_C_SOURCE 199309L
#include <time.h>

#include "unity.h"
#include "utils.h"

#ifdef USE_CEEDLING
void __attribute__((weak)) setUp() {}
void __attribute__((weak)) tearDown() {}
#endif

static void clockSleep_(const struct timespec *const sleepTime,
                        struct timespec *const elapsedTime, int flags) {
  int status = 0;
  struct timespec startTime = {};
  struct timespec endTime = {};

  status = clock_gettime(CLOCK_MONOTONIC, &startTime);
  TEST_ASSERT_EQUAL_INT(0, status);

  status = clock_nanosleep(CLOCK_MONOTONIC, flags, sleepTime, NULL);
  TEST_ASSERT_EQUAL_INT(0, status);

  status = clock_gettime(CLOCK_MONOTONIC, &endTime);
  TEST_ASSERT_EQUAL_INT(0, status);

  TEST_ASSERT_TRUE(0 <= startTime.tv_sec);
  TEST_ASSERT_EQUAL_INT(true, Utils_validateTimespec(&startTime));
  TEST_ASSERT_TRUE(0 <= endTime.tv_sec);
  TEST_ASSERT_EQUAL_INT(true, Utils_validateTimespec(&endTime));

  TEST_ASSERT_EQUAL_INT(
      0, Utils_timespecSubtract(&endTime, &startTime, elapsedTime));
}

void test_TestPosixClock_clock_gettime_nanosleep_() {
#ifndef _WIN32
  static const size_t delay = 1000000;
  struct timespec sleepTime = {.tv_sec = 0, .tv_nsec = delay};
  struct timespec elapsedTime = {};

  clockSleep_(&sleepTime, &elapsedTime, 0);

  TEST_ASSERT_TRUE(0 <= elapsedTime.tv_sec);
  TEST_ASSERT_TRUE(1 > elapsedTime.tv_sec);
  TEST_ASSERT_TRUE(delay <= elapsedTime.tv_nsec);
#endif
}

void test_TestPosixClock_clock_getres_() {
#ifndef _WIN32
  int status = 0;
  struct timespec xResolution = {};

  status = clock_getres(CLOCK_MONOTONIC, &xResolution);
  TEST_ASSERT_EQUAL_INT(0, status);

  TEST_ASSERT_EQUAL_INT(true, Utils_validateTimespec(&xResolution));
#endif
}

void test_TestPosixClock_clock_nanosleep_absolute_() {
#ifndef _WIN32
  static const size_t delay = 7000000;

  int status = 0;
  struct timespec wakeTime = {};
  struct timespec elapsedTime = {};

  status = clock_gettime(CLOCK_MONOTONIC, &wakeTime);
  TEST_ASSERT_EQUAL_INT(0, status);

  status = Utils_timespecAddNanoseconds(&wakeTime, delay, &wakeTime);
  TEST_ASSERT_EQUAL_INT(0, status);

  clockSleep_(&wakeTime, &elapsedTime, TIMER_ABSTIME);

  TEST_ASSERT_TRUE(0 <= elapsedTime.tv_sec);
  TEST_ASSERT_TRUE(1 > elapsedTime.tv_sec);
  TEST_ASSERT_TRUE(delay <= elapsedTime.tv_nsec);
#endif
}

void test_TestPosixClock_clock_nanosleep_min_resolution_() {
#ifndef _WIN32
  int status = 0;
  struct timespec xResolution = {};
  struct timespec sleepTime = {};
  struct timespec elapsedTime = {};

  status = clock_getres(CLOCK_MONOTONIC, &xResolution);
  TEST_ASSERT_EQUAL_INT(0, status);

  sleepTime.tv_sec = xResolution.tv_sec / 2;
  sleepTime.tv_nsec = xResolution.tv_nsec / 2;

  clockSleep_(&sleepTime, &elapsedTime, 0);

  TEST_ASSERT_EQUAL_INT(
      0, Utils_timespecSubtract(&elapsedTime, &xResolution, &elapsedTime));
#endif
}

void test_TestPosixClock_clock_nanosleep_invalid_rqtp_() {
#ifndef _WIN32
  int status = 0;
  struct timespec sleepTime;

  sleepTime.tv_sec = 0;
  sleepTime.tv_nsec = -3;

  status = clock_nanosleep(CLOCK_MONOTONIC, 0, &sleepTime, NULL);
  TEST_ASSERT_EQUAL_INT(EINVAL, status);

  sleepTime.tv_sec = 0;
  sleepTime.tv_nsec = NANOSECONDS_PER_SECOND;

  status = clock_nanosleep(CLOCK_MONOTONIC, 0, &sleepTime, NULL);
  TEST_ASSERT_EQUAL_INT(EINVAL, status);
#endif
}

void test_TestPosixClock_clock_nanosleep_absolute_in_past_() {
#ifndef _WIN32
  int status = 0;
  struct timespec wakeTime = {};
  struct timespec elapsedTime = {};

  status = clock_gettime(CLOCK_MONOTONIC, &wakeTime);
  TEST_ASSERT_EQUAL_INT(0, status);

  status = Utils_timespecAddNanoseconds(&wakeTime, -5000000, &wakeTime);
  TEST_ASSERT_EQUAL_INT(0, status);

  clockSleep_(&wakeTime, &elapsedTime, TIMER_ABSTIME);

  TEST_ASSERT_TRUE(0 == elapsedTime.tv_sec);
  TEST_ASSERT_TRUE(2000000 > elapsedTime.tv_nsec);
#endif
}

void test_TestPosixClock_nanosleep_() {
#ifndef _WIN32
  static const size_t delay = 1000000;
  int status = 0;
  struct timespec sleepTime = {.tv_sec = 0, .tv_nsec = 1000000};
  struct timespec startTime = {};
  struct timespec endTime = {};
  struct timespec elapsedTime = {};

  status = clock_gettime(CLOCK_MONOTONIC, &startTime);
  TEST_ASSERT_EQUAL_INT(0, status);

  status = nanosleep(&sleepTime, NULL);
  TEST_ASSERT_EQUAL_INT(0, status);

  clock_gettime(CLOCK_MONOTONIC, &endTime);
  TEST_ASSERT_EQUAL_INT(0, status);

  TEST_ASSERT_EQUAL_INT(
      0, Utils_timespecSubtract(&endTime, &startTime, &elapsedTime));

  TEST_ASSERT_TRUE(0 <= elapsedTime.tv_sec);
  TEST_ASSERT_TRUE(1 > elapsedTime.tv_sec);
  TEST_ASSERT_TRUE(1000000 <= elapsedTime.tv_nsec);
#endif
}

void test_TestPosixClock_nanosleep_invalid_params_() {
#ifndef _WIN32
  struct timespec sleepTime = {.tv_sec = 0, .tv_nsec = NANOSECONDS_PER_SECOND};

  TEST_ASSERT_EQUAL_INT(-1, nanosleep(NULL, NULL));
  TEST_ASSERT_EQUAL_INT(EINVAL, errno);

  TEST_ASSERT_EQUAL_INT(-1, nanosleep(&sleepTime, NULL));
  TEST_ASSERT_EQUAL_INT(EINVAL, errno);
#endif
}

#ifndef USE_CEEDLING
#include "unity_fixture.h"

TEST_GROUP(TestPosixClock);

TEST_SETUP(TestPosixClock) {}

TEST_TEAR_DOWN(TestPosixClock) {}

TEST_GROUP_RUNNER(TestPosixClock) {
  RUN_TEST_CASE(TestPosixClock, clock_gettime_nanosleep);
  RUN_TEST_CASE(TestPosixClock, clock_getres);
  RUN_TEST_CASE(TestPosixClock, clock_nanosleep_absolute);
  RUN_TEST_CASE(TestPosixClock, clock_nanosleep_min_resolution);
  RUN_TEST_CASE(TestPosixClock, clock_nanosleep_invalid_rqtp);
  RUN_TEST_CASE(TestPosixClock, clock_nanosleep_absolute_in_past);
  RUN_TEST_CASE(TestPosixClock, nanosleep);
  RUN_TEST_CASE(TestPosixClock, nanosleep_invalid_params);
}

TEST(TestPosixClock, clock_gettime_nanosleep) {
  test_TestPosixClock_clock_gettime_nanosleep_();
}

TEST(TestPosixClock, clock_getres) { test_TestPosixClock_clock_getres_(); }

TEST(TestPosixClock, clock_nanosleep_absolute) {
  test_TestPosixClock_clock_nanosleep_absolute_();
}

TEST(TestPosixClock, clock_nanosleep_min_resolution) {
  test_TestPosixClock_clock_nanosleep_min_resolution_();
}

TEST(TestPosixClock, clock_nanosleep_invalid_rqtp) {
  test_TestPosixClock_clock_nanosleep_invalid_rqtp_();
}

TEST(TestPosixClock, clock_nanosleep_absolute_in_past) {
  test_TestPosixClock_clock_nanosleep_absolute_in_past_();
}

TEST(TestPosixClock, nanosleep) { test_TestPosixClock_nanosleep_(); }

TEST(TestPosixClock, nanosleep_invalid_params) {
  test_TestPosixClock_nanosleep_invalid_params_();
}
#endif