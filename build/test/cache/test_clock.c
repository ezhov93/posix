#include "include/utils.h"
#include "/usr/local/bundle/gems/ceedling-0.31.1/vendor/unity/src/unity.h"








void __attribute__((weak)) setUp() {}

void __attribute__((weak)) tearDown() {}





static void clockSleep_(const struct timespec *const sleepTime,

                        struct timespec *const elapsedTime, int flags) {

  int status = 0;

  struct timespec startTime = {};

  struct timespec endTime = {};



  status = clock_gettime(

                        1

                                       , &startTime);

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((status)), (

 ((void*)0)

 ), (UNITY_UINT)(21), UNITY_DISPLAY_STYLE_INT);



  status = clock_nanosleep(

                          1

                                         , flags, sleepTime, 

                                                             ((void*)0)

                                                                 );

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((status)), (

 ((void*)0)

 ), (UNITY_UINT)(24), UNITY_DISPLAY_STYLE_INT);



  status = clock_gettime(

                        1

                                       , &endTime);

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((status)), (

 ((void*)0)

 ), (UNITY_UINT)(27), UNITY_DISPLAY_STYLE_INT);



  do {if ((0 <= startTime.tv_sec)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(29)));}} while(0);

  UnityAssertEqualNumber((UNITY_INT)((

 1

 )), (UNITY_INT)((Utils_validateTimespec(&startTime))), (

 ((void*)0)

 ), (UNITY_UINT)(30), UNITY_DISPLAY_STYLE_INT);

  do {if ((0 <= endTime.tv_sec)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(31)));}} while(0);

  UnityAssertEqualNumber((UNITY_INT)((

 1

 )), (UNITY_INT)((Utils_validateTimespec(&endTime))), (

 ((void*)0)

 ), (UNITY_UINT)(32), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((Utils_timespecSubtract(&endTime, &startTime, elapsedTime))), (

 ((void*)0)

 ), (UNITY_UINT)(34), UNITY_DISPLAY_STYLE_INT)

                                                                   ;

}



void test_TestPosixClock_clock_gettime_nanosleep_() {



  static const size_t delay = 1000000;

  struct timespec sleepTime = {.tv_sec = 0, .tv_nsec = delay};

  struct timespec elapsedTime = {};



  clockSleep_(&sleepTime, &elapsedTime, 0);



  do {if ((0 <= elapsedTime.tv_sec)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(46)));}} while(0);

  do {if ((1 > elapsedTime.tv_sec)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(47)));}} while(0);

  do {if ((delay <= elapsedTime.tv_nsec)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(48)));}} while(0);



}



void test_TestPosixClock_clock_getres_() {



  int status = 0;

  struct timespec xResolution = {};



  status = clock_getres(

                       1

                                      , &xResolution);

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((status)), (

 ((void*)0)

 ), (UNITY_UINT)(58), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((UNITY_INT)((

 1

 )), (UNITY_INT)((Utils_validateTimespec(&xResolution))), (

 ((void*)0)

 ), (UNITY_UINT)(60), UNITY_DISPLAY_STYLE_INT);



}



void test_TestPosixClock_clock_nanosleep_absolute_() {



  static const size_t delay = 7000000;



  int status = 0;

  struct timespec wakeTime = {};

  struct timespec elapsedTime = {};



  status = clock_gettime(

                        1

                                       , &wakeTime);

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((status)), (

 ((void*)0)

 ), (UNITY_UINT)(73), UNITY_DISPLAY_STYLE_INT);



  status = Utils_timespecAddNanoseconds(&wakeTime, delay, &wakeTime);

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((status)), (

 ((void*)0)

 ), (UNITY_UINT)(76), UNITY_DISPLAY_STYLE_INT);



  clockSleep_(&wakeTime, &elapsedTime, 

                                      1

                                                   );



  do {if ((0 <= elapsedTime.tv_sec)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(80)));}} while(0);

  do {if ((1 > elapsedTime.tv_sec)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(81)));}} while(0);

  do {if ((delay <= elapsedTime.tv_nsec)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(82)));}} while(0);



}



void test_TestPosixClock_clock_nanosleep_min_resolution_() {



  int status = 0;

  struct timespec xResolution = {};

  struct timespec sleepTime = {};

  struct timespec elapsedTime = {};



  status = clock_getres(

                       1

                                      , &xResolution);

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((status)), (

 ((void*)0)

 ), (UNITY_UINT)(94), UNITY_DISPLAY_STYLE_INT);



  sleepTime.tv_sec = xResolution.tv_sec / 2;

  sleepTime.tv_nsec = xResolution.tv_nsec / 2;



  clockSleep_(&sleepTime, &elapsedTime, 0);



  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((Utils_timespecSubtract(&elapsedTime, &xResolution, &elapsedTime))), (

 ((void*)0)

 ), (UNITY_UINT)(101), UNITY_DISPLAY_STYLE_INT)

                                                                          ;



}



void test_TestPosixClock_clock_nanosleep_invalid_rqtp_() {



  int status = 0;

  struct timespec sleepTime;



  sleepTime.tv_sec = 0;

  sleepTime.tv_nsec = -3;



  status = clock_nanosleep(

                          1

                                         , 0, &sleepTime, 

                                                          ((void*)0)

                                                              );

  UnityAssertEqualNumber((UNITY_INT)((

 22

 )), (UNITY_INT)((status)), (

 ((void*)0)

 ), (UNITY_UINT)(115), UNITY_DISPLAY_STYLE_INT);



  sleepTime.tv_sec = 0;

  sleepTime.tv_nsec = (1000000000LL);



  status = clock_nanosleep(

                          1

                                         , 0, &sleepTime, 

                                                          ((void*)0)

                                                              );

  UnityAssertEqualNumber((UNITY_INT)((

 22

 )), (UNITY_INT)((status)), (

 ((void*)0)

 ), (UNITY_UINT)(121), UNITY_DISPLAY_STYLE_INT);



}



void test_TestPosixClock_clock_nanosleep_absolute_in_past_() {



  int status = 0;

  struct timespec wakeTime = {};

  struct timespec elapsedTime = {};



  status = clock_gettime(

                        1

                                       , &wakeTime);

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((status)), (

 ((void*)0)

 ), (UNITY_UINT)(132), UNITY_DISPLAY_STYLE_INT);



  status = Utils_timespecAddNanoseconds(&wakeTime, -5000000, &wakeTime);

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((status)), (

 ((void*)0)

 ), (UNITY_UINT)(135), UNITY_DISPLAY_STYLE_INT);



  clockSleep_(&wakeTime, &elapsedTime, 

                                      1

                                                   );



  do {if ((0 == elapsedTime.tv_sec)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(139)));}} while(0);

  do {if ((2000000 > elapsedTime.tv_nsec)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(140)));}} while(0);



}



void test_TestPosixClock_nanosleep_() {



  static const size_t delay = 1000000;

  int status = 0;

  struct timespec sleepTime = {.tv_sec = 0, .tv_nsec = 1000000};

  struct timespec startTime = {};

  struct timespec endTime = {};

  struct timespec elapsedTime = {};



  status = clock_gettime(

                        1

                                       , &startTime);

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((status)), (

 ((void*)0)

 ), (UNITY_UINT)(154), UNITY_DISPLAY_STYLE_INT);



  status = nanosleep(&sleepTime, 

                                ((void*)0)

                                    );

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((status)), (

 ((void*)0)

 ), (UNITY_UINT)(157), UNITY_DISPLAY_STYLE_INT);



  clock_gettime(

               1

                              , &endTime);

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((status)), (

 ((void*)0)

 ), (UNITY_UINT)(160), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((Utils_timespecSubtract(&endTime, &startTime, &elapsedTime))), (

 ((void*)0)

 ), (UNITY_UINT)(162), UNITY_DISPLAY_STYLE_INT)

                                                                    ;



  do {if ((0 <= elapsedTime.tv_sec)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(165)));}} while(0);

  do {if ((1 > elapsedTime.tv_sec)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(166)));}} while(0);

  do {if ((1000000 <= elapsedTime.tv_nsec)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(167)));}} while(0);



}



void test_TestPosixClock_nanosleep_invalid_params_() {



  struct timespec sleepTime = {.tv_sec = 0, .tv_nsec = (1000000000LL)};



  UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((nanosleep(

 ((void*)0)

 , 

 ((void*)0)

 ))), (

 ((void*)0)

 ), (UNITY_UINT)(175), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((UNITY_INT)((

 22

 )), (UNITY_INT)((

 (*__errno_location())

 )), (

 ((void*)0)

 ), (UNITY_UINT)(176), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((nanosleep(&sleepTime, 

 ((void*)0)

 ))), (

 ((void*)0)

 ), (UNITY_UINT)(178), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((UNITY_INT)((

 22

 )), (UNITY_INT)((

 (*__errno_location())

 )), (

 ((void*)0)

 ), (UNITY_UINT)(179), UNITY_DISPLAY_STYLE_INT);



}
