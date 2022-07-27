#include <errno.h>
#include <stddef.h>
#include <string.h>
#include <utils.h>

#include "unity.h"

#ifdef USE_CEEDLING
void __attribute__((weak)) setUp() {}
void __attribute__((weak)) tearDown() {}
#endif

static const struct timespec signedCheck_ = {.tv_sec = 1, .tv_nsec = 1};
static uint8_t isTimespecTvSecSigned_;

void test_TestPosixUtils_Utils_timespecAdd_() {
  struct timespec result = {.tv_sec = 0, .tv_nsec = 0};
  struct timespec x = {.tv_sec = 0, .tv_nsec = 0};
  struct timespec y = {.tv_sec = 0, .tv_nsec = 0};

  TEST_ASSERT_EQUAL_INT(-1, Utils_timespecAdd(&x, &y, NULL));
  TEST_ASSERT_EQUAL_INT(-1, Utils_timespecAdd(NULL, &y, &result));
  TEST_ASSERT_EQUAL_INT(-1, Utils_timespecAdd(&x, NULL, &result));

  if (isTimespecTvSecSigned_ == 1u) {
    x.tv_sec = -1;
    TEST_ASSERT_EQUAL_INT(-1, Utils_timespecAdd(&x, &y, NULL));

    x.tv_sec = 0;
    y.tv_sec = -2;
    TEST_ASSERT_EQUAL_INT(-1, Utils_timespecAdd(&x, &y, NULL));
  }

  if (isTimespecTvSecSigned_ == 1u) {
    x.tv_sec = 0;
    y.tv_sec = 0;

    x.tv_nsec = -1;
    TEST_ASSERT_EQUAL_INT(-1, Utils_timespecAdd(&x, &y, NULL));

    x.tv_nsec = 0;
    y.tv_nsec = -2;
    TEST_ASSERT_EQUAL_INT(-1, Utils_timespecAdd(&x, &y, NULL));
  }

  x.tv_sec = 1;
  y.tv_sec = 2;
  x.tv_nsec = 3;
  y.tv_nsec = 4;
  TEST_ASSERT_EQUAL_INT(0, Utils_timespecAdd(&x, &y, &result));
  TEST_ASSERT_EQUAL_INT(3, result.tv_sec);
  TEST_ASSERT_EQUAL_INT(7, result.tv_nsec);

  x.tv_sec = y.tv_sec = 0;
  x.tv_nsec = y.tv_nsec = 600000000;
  TEST_ASSERT_EQUAL_INT(0, Utils_timespecAdd(&x, &y, &result));
  TEST_ASSERT_EQUAL_INT(1, result.tv_sec);
  TEST_ASSERT_EQUAL_INT(200000000, result.tv_nsec);

  x.tv_sec = x.tv_nsec = 5;
  TEST_ASSERT_EQUAL_INT(0, Utils_timespecAdd(&x, &x, &x));
  TEST_ASSERT_EQUAL_INT(10, x.tv_sec);
  TEST_ASSERT_EQUAL_INT(10, x.tv_nsec);
}

void test_TestPosixUtils_Utils_timespecAdd_Overflow_() {
  struct timespec result = {.tv_sec = 0, .tv_nsec = 0};
  struct timespec x = {.tv_sec = 0, .tv_nsec = 0};
  struct timespec y = {.tv_sec = 0, .tv_nsec = 0};

  if (isTimespecTvSecSigned_) {
    if (sizeof(x.tv_sec) == sizeof(int)) {
      x.tv_sec = INT_MAX;
    } else if (sizeof(x.tv_sec) == sizeof(long int)) {
      x.tv_sec = LONG_MAX;
    } else if (sizeof(x.tv_sec) == sizeof(long long int)) {
      x.tv_sec = LLONG_MAX;
    } else {
      TEST_FAIL_MESSAGE("Sizeof(timespec.tv_sec does not match int, long int "
                        "or long long int");
    }

    y.tv_sec = 2;
    y.tv_nsec = 100000000;
    TEST_ASSERT_EQUAL_INT(1, Utils_timespecAdd(&x, &y, &result));
    TEST_ASSERT_EQUAL_INT(100000000, result.tv_nsec);
  } else {
    if (sizeof(x.tv_sec) == sizeof(unsigned int)) {
      x.tv_sec = UINT_MAX;
    } else if (sizeof(x.tv_sec) == sizeof(unsigned long int)) {
      x.tv_sec = ULONG_MAX;
    } else if (sizeof(x.tv_sec) == sizeof(unsigned long long int)) {
      x.tv_sec = ULLONG_MAX;
    } else {
      TEST_FAIL_MESSAGE("Sizeof(timespec.tv_sec does not match int, long int "
                        "or long long int");
    }
    y.tv_sec = 2;
    y.tv_nsec = 100000000;
    TEST_ASSERT_EQUAL_INT(1, Utils_timespecAdd(&x, &y, &result));
    TEST_ASSERT_EQUAL_INT(100000000, result.tv_nsec);
  }
  x.tv_sec = y.tv_sec = 0;
  x.tv_nsec = y.tv_nsec = 2100000000;
  TEST_ASSERT_EQUAL_INT(1, Utils_timespecAdd(&x, &y, &result));
}

void test_TestPosixUtils_Utils_timespecSubtract_() {
  struct timespec result = {.tv_sec = 0, .tv_nsec = 0};
  struct timespec x = {.tv_sec = 0, .tv_nsec = 0};
  struct timespec y = {.tv_sec = 0, .tv_nsec = 0};

  TEST_ASSERT_EQUAL_INT(-1, Utils_timespecSubtract(&x, &y, NULL));
  TEST_ASSERT_EQUAL_INT(-1, Utils_timespecSubtract(NULL, &y, &result));
  TEST_ASSERT_EQUAL_INT(-1, Utils_timespecSubtract(&x, NULL, &result));

  x.tv_sec = 5;
  y.tv_sec = 3;
  x.tv_nsec = y.tv_nsec = 0;
  TEST_ASSERT_EQUAL_INT(0, Utils_timespecSubtract(&x, &y, &result));
  TEST_ASSERT_EQUAL_INT(2, result.tv_sec);
  TEST_ASSERT_EQUAL_INT(0, result.tv_nsec);
  x.tv_sec = 1;
  y.tv_sec = 3;
  x.tv_nsec = y.tv_nsec = 0;
  TEST_ASSERT_EQUAL_INT(1, Utils_timespecSubtract(&x, &y, &result));

  x.tv_sec = y.tv_sec = 0;
  x.tv_nsec = 5;
  y.tv_nsec = 3;
  TEST_ASSERT_EQUAL_INT(0, Utils_timespecSubtract(&x, &y, &result));
  TEST_ASSERT_EQUAL_INT(0, result.tv_sec);
  TEST_ASSERT_EQUAL_INT(2, result.tv_nsec);

  x.tv_sec = y.tv_sec = 0;
  x.tv_nsec = 0;
  y.tv_nsec = 5;
  TEST_ASSERT_EQUAL_INT(1, Utils_timespecSubtract(&x, &y, &result));

  x.tv_sec = y.tv_sec = 0;
  x.tv_nsec = -5;
  y.tv_nsec = 3;
  TEST_ASSERT_EQUAL_INT(1, Utils_timespecSubtract(&x, &y, &result));

  x.tv_sec = 1;
  y.tv_sec = 0;
  x.tv_nsec = 0;
  y.tv_nsec = 2100000000;
  TEST_ASSERT_EQUAL_INT(-1, Utils_timespecSubtract(&x, &y, &result));

  x.tv_sec = x.tv_nsec = 5;
  TEST_ASSERT_EQUAL_INT(0, Utils_timespecSubtract(&x, &x, &x));
  TEST_ASSERT_EQUAL_INT(0, x.tv_sec);
  TEST_ASSERT_EQUAL_INT(0, x.tv_nsec);
}

void test_TestPosixUtils_Utils_timespecAdd_Nanoseconds_() {
  struct timespec result = {.tv_sec = 0, .tv_nsec = 0};
  struct timespec x = {.tv_sec = 0, .tv_nsec = 0};
  int64_t nanosec = 0;

  TEST_ASSERT_EQUAL_INT(-1, Utils_timespecAddNanoseconds(&x, nanosec, NULL));
  TEST_ASSERT_EQUAL_INT(-1,
                        Utils_timespecAddNanoseconds(NULL, nanosec, &result));

  x.tv_sec = 5;
  x.tv_nsec = 500000000;
  nanosec = 4500000000LL;
  TEST_ASSERT_EQUAL_INT(0, Utils_timespecAddNanoseconds(&x, nanosec, &result));
  TEST_ASSERT_EQUAL_INT(10, result.tv_sec);
  TEST_ASSERT_EQUAL_INT(0, result.tv_nsec);

  x.tv_sec = 5;
  x.tv_nsec = 500000000;
  nanosec = -9500000000LL;
  TEST_ASSERT_EQUAL_INT(1, Utils_timespecAddNanoseconds(&x, nanosec, &result));

  x.tv_sec = x.tv_nsec = 5;
  nanosec = 4999999995;
  TEST_ASSERT_EQUAL_INT(0, Utils_timespecAddNanoseconds(&x, nanosec, &x));
  TEST_ASSERT_EQUAL_INT(10, x.tv_sec);
  TEST_ASSERT_EQUAL_INT(0, x.tv_nsec);
}

void test_TestPosixUtils_Utils_strnlen_() {
  static const char *const str = "This is a string used to test Utils_strnlen.";
  size_t len = strlen(str);
  TEST_ASSERT_EQUAL_UINT32(0, Utils_strnlen(NULL, len));

  TEST_ASSERT_EQUAL_UINT32(0, Utils_strnlen("", len));

  TEST_ASSERT_EQUAL_UINT32(0, Utils_strnlen(str, 0));

  TEST_ASSERT_EQUAL_UINT32(len - 1UL, Utils_strnlen(str, len - 1UL));

  TEST_ASSERT_EQUAL_UINT32(len, Utils_strnlen(str, len + 1UL));
}

void test_TestPosixUtils_Utils_timespecCompare_() {
  struct timespec timeX = {.tv_sec = 0, .tv_nsec = 0};
  struct timespec timeY = {.tv_sec = 0, .tv_nsec = 0};

  TEST_ASSERT_EQUAL_INT(0, Utils_timespecCompare(NULL, NULL));
  TEST_ASSERT_EQUAL_INT(-1, Utils_timespecCompare(NULL, &timeY));
  TEST_ASSERT_EQUAL_INT(1, Utils_timespecCompare(&timeX, NULL));

  TEST_ASSERT_EQUAL_INT(0, Utils_timespecCompare(&timeX, &timeY));

  timeX.tv_nsec = 1;
  TEST_ASSERT_EQUAL_INT(1, Utils_timespecCompare(&timeX, &timeY));
  timeX.tv_sec = 1;
  TEST_ASSERT_EQUAL_INT(1, Utils_timespecCompare(&timeX, &timeY));

  timeY.tv_sec = 1;
  timeY.tv_nsec = 2;
  TEST_ASSERT_EQUAL_INT(-1, Utils_timespecCompare(&timeX, &timeY));
  timeX.tv_sec = 0;
  TEST_ASSERT_EQUAL_INT(-1, Utils_timespecCompare(&timeX, &timeY));
}

void test_TestPosixUtils_Utils_timespecToTicks_() {
  struct timespec timeX = {.tv_sec = 0, .tv_nsec = 0};
  clock_t result;

  TEST_ASSERT_EQUAL_INT(EINVAL, Utils_timespecToTicks(NULL, &result));
  TEST_ASSERT_EQUAL_INT(EINVAL, Utils_timespecToTicks(&timeX, NULL));

  timeX.tv_nsec = NANOSECONDS_PER_SECOND + 1;
  TEST_ASSERT_EQUAL_INT(EINVAL, Utils_timespecToTicks(&timeX, &result));
  timeX.tv_nsec = -1;
  TEST_ASSERT_EQUAL_INT(EINVAL, Utils_timespecToTicks(&timeX, &result));

  timeX.tv_sec = 1;
  timeX.tv_nsec = NANOSECONDS_PER_TICK + 1;
  clock_t expectedVal = (clock_t)timeX.tv_sec * CLOCKS_PER_SEC + 2;
  TEST_ASSERT_EQUAL_INT(0, Utils_timespecToTicks(&timeX, &result));
  TEST_ASSERT_EQUAL_INT((int)expectedVal, (int)result);
}

void test_TestPosixUtils_Utils_absoluteTimespecToDeltaTicks_() {
  struct timespec timeX = {.tv_sec = 0, .tv_nsec = 0};
  struct timespec timeY = {.tv_sec = 0, .tv_nsec = 0};
  clock_t result;

  TEST_ASSERT_EQUAL_INT(
      EINVAL, Utils_absoluteTimespecToDeltaTicks(&timeX, &timeY, NULL));
  TEST_ASSERT_EQUAL_INT(
      EINVAL, Utils_absoluteTimespecToDeltaTicks(NULL, &timeY, &result));
  TEST_ASSERT_EQUAL_INT(
      EINVAL, Utils_absoluteTimespecToDeltaTicks(&timeX, NULL, &result));

  timeY.tv_sec = 1;
  TEST_ASSERT_EQUAL_INT(
      ETIMEDOUT, Utils_absoluteTimespecToDeltaTicks(&timeX, &timeY, &result));
  timeX.tv_sec = 2;
  TEST_ASSERT_EQUAL_INT(
      0, Utils_absoluteTimespecToDeltaTicks(&timeX, &timeY, &result));

  timeY.tv_nsec = NANOSECONDS_PER_SECOND + 1;
  TEST_ASSERT_EQUAL_INT(
      EINVAL, Utils_absoluteTimespecToDeltaTicks(&timeX, &timeY, &result));
}

#ifndef USE_CEEDLING
#include "unity_fixture.h"
TEST_GROUP(TestPosixUtils);

TEST_SETUP(TestPosixUtils) {
  isTimespecTvSecSigned_ = (~signedCheck_.tv_sec < 0) ? 1u : 0u;
}

TEST_TEAR_DOWN(TestPosixUtils) {}

TEST_GROUP_RUNNER(TestPosixUtils) {
  RUN_TEST_CASE(TestPosixUtils, Utils_timespecAdd);
  RUN_TEST_CASE(TestPosixUtils, Utils_timespecAdd_Overflow);
  RUN_TEST_CASE(TestPosixUtils, Utils_timespecSubtract);
  RUN_TEST_CASE(TestPosixUtils, Utils_timespecAddNanoseconds);
  RUN_TEST_CASE(TestPosixUtils, Utils_strnlen);
  RUN_TEST_CASE(TestPosixUtils, Utils_timespecCompare);
  RUN_TEST_CASE(TestPosixUtils, Utils_timespecToTicks);
  RUN_TEST_CASE(TestPosixUtils, Utils_absoluteTimespecToDeltaTicks)
}

TEST(TestPosixUtils, Utils_timespecAdd) {
  test_TestPosixUtils_Utils_timespecAdd_();
}

TEST(TestPosixUtils, Utils_timespecAdd_Overflow) {
  test_TestPosixUtils_Utils_timespecAdd_Overflow_();
}

TEST(TestPosixUtils, Utils_timespecSubtract) {
  test_TestPosixUtils_Utils_timespecSubtract_();
}

TEST(TestPosixUtils, Utils_timespecAddNanoseconds) {
  test_TestPosixUtils_Utils_timespecAdd_Nanoseconds_();
}

TEST(TestPosixUtils, Utils_strnlen) { test_TestPosixUtils_Utils_strnlen_(); }

TEST(TestPosixUtils, Utils_timespecCompare) {
  test_TestPosixUtils_Utils_timespecCompare_();
}

TEST(TestPosixUtils, Utils_timespecToTicks) {
  test_TestPosixUtils_Utils_timespecToTicks_();
}

TEST(TestPosixUtils, Utils_absoluteTimespecToDeltaTicks) {
  test_TestPosixUtils_Utils_absoluteTimespecToDeltaTicks_();
}

#endif