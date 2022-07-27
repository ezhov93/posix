#include "unity_fixture.h"

static void _runAllTests() {
  RUN_TEST_GROUP(TestPosixUtils);
  RUN_TEST_GROUP(TestPosixClock);
}

int main(int argc, const char* argv[]) {
  return UnityMain(argc, argv, _runAllTests);
}