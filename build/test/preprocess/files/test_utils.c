#include "/usr/local/bundle/gems/ceedling-0.31.1/vendor/unity/src/unity.h"
#include "include/utils.h"






void __attribute__((weak)) setUp() {}

void __attribute__((weak)) tearDown() {}





static const struct timespec signedCheck_ = {.tv_sec = 1, .tv_nsec = 1};

static uint8_t isTimespecTvSecSigned_;



void test_TestPosixUtils_Utils_timespecAdd_() {

  struct timespec result = {.tv_sec = 0, .tv_nsec = 0};

  struct timespec x = {.tv_sec = 0, .tv_nsec = 0};

  struct timespec y = {.tv_sec = 0, .tv_nsec = 0};



  UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((Utils_timespecAdd(&x, &y, 

 ((void*)0)

 ))), (

 ((void*)0)

 ), (UNITY_UINT)(21), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((Utils_timespecAdd(

 ((void*)0)

 , &y, &result))), (

 ((void*)0)

 ), (UNITY_UINT)(22), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((Utils_timespecAdd(&x, 

 ((void*)0)

 , &result))), (

 ((void*)0)

 ), (UNITY_UINT)(23), UNITY_DISPLAY_STYLE_INT);



  if (isTimespecTvSecSigned_ == 1u) {

    x.tv_sec = -1;

    UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((Utils_timespecAdd(&x, &y, 

   ((void*)0)

   ))), (

   ((void*)0)

   ), (UNITY_UINT)(27), UNITY_DISPLAY_STYLE_INT);



    x.tv_sec = 0;

    y.tv_sec = -2;

    UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((Utils_timespecAdd(&x, &y, 

   ((void*)0)

   ))), (

   ((void*)0)

   ), (UNITY_UINT)(31), UNITY_DISPLAY_STYLE_INT);

  }



  if (isTimespecTvSecSigned_ == 1u) {

    x.tv_sec = 0;

    y.tv_sec = 0;



    x.tv_nsec = -1;

    UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((Utils_timespecAdd(&x, &y, 

   ((void*)0)

   ))), (

   ((void*)0)

   ), (UNITY_UINT)(39), UNITY_DISPLAY_STYLE_INT);



    x.tv_nsec = 0;

    y.tv_nsec = -2;

    UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((Utils_timespecAdd(&x, &y, 

   ((void*)0)

   ))), (

   ((void*)0)

   ), (UNITY_UINT)(43), UNITY_DISPLAY_STYLE_INT);

  }



  x.tv_sec = 1;

  y.tv_sec = 2;

  x.tv_nsec = 3;

  y.tv_nsec = 4;

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((Utils_timespecAdd(&x, &y, &result))), (

 ((void*)0)

 ), (UNITY_UINT)(50), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((UNITY_INT)((3)), (UNITY_INT)((result.tv_sec)), (

 ((void*)0)

 ), (UNITY_UINT)(51), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((UNITY_INT)((7)), (UNITY_INT)((result.tv_nsec)), (

 ((void*)0)

 ), (UNITY_UINT)(52), UNITY_DISPLAY_STYLE_INT);



  x.tv_sec = y.tv_sec = 0;

  x.tv_nsec = y.tv_nsec = 600000000;

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((Utils_timespecAdd(&x, &y, &result))), (

 ((void*)0)

 ), (UNITY_UINT)(56), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((result.tv_sec)), (

 ((void*)0)

 ), (UNITY_UINT)(57), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((UNITY_INT)((200000000)), (UNITY_INT)((result.tv_nsec)), (

 ((void*)0)

 ), (UNITY_UINT)(58), UNITY_DISPLAY_STYLE_INT);



  x.tv_sec = x.tv_nsec = 5;

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((Utils_timespecAdd(&x, &x, &x))), (

 ((void*)0)

 ), (UNITY_UINT)(61), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((UNITY_INT)((10)), (UNITY_INT)((x.tv_sec)), (

 ((void*)0)

 ), (UNITY_UINT)(62), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((UNITY_INT)((10)), (UNITY_INT)((x.tv_nsec)), (

 ((void*)0)

 ), (UNITY_UINT)(63), UNITY_DISPLAY_STYLE_INT);

}



void test_TestPosixUtils_Utils_timespecAdd_Overflow_() {

  struct timespec result = {.tv_sec = 0, .tv_nsec = 0};

  struct timespec x = {.tv_sec = 0, .tv_nsec = 0};

  struct timespec y = {.tv_sec = 0, .tv_nsec = 0};



  if (isTimespecTvSecSigned_) {

    if (sizeof(x.tv_sec) == sizeof(int)) {

      x.tv_sec = 

                0x7fffffff

                       ;

    } else if (sizeof(x.tv_sec) == sizeof(long int)) {

      x.tv_sec = 

                0x7fffffffffffffffL

                        ;

    } else if (sizeof(x.tv_sec) == sizeof(long long int)) {

      x.tv_sec = 

                0x7fffffffffffffffLL

                         ;

    } else {

      UnityFail( (("Sizeof(timespec.tv_sec does not match int, long int " "or long long int")), (UNITY_UINT)(79))

                                           ;

    }



    y.tv_sec = 2;

    y.tv_nsec = 100000000;

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((Utils_timespecAdd(&x, &y, &result))), (

   ((void*)0)

   ), (UNITY_UINT)(85), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((100000000)), (UNITY_INT)((result.tv_nsec)), (

   ((void*)0)

   ), (UNITY_UINT)(86), UNITY_DISPLAY_STYLE_INT);

  } else {

    if (sizeof(x.tv_sec) == sizeof(unsigned int)) {

      x.tv_sec = 

                0xffffffffU

                        ;

    } else if (sizeof(x.tv_sec) == sizeof(unsigned long int)) {

      x.tv_sec = 

                (2UL*0x7fffffffffffffffL +1)

                         ;

    } else if (sizeof(x.tv_sec) == sizeof(unsigned long long int)) {

      x.tv_sec = 

                (2ULL*0x7fffffffffffffffLL +1)

                          ;

    } else {

      UnityFail( (("Sizeof(timespec.tv_sec does not match int, long int " "or long long int")), (UNITY_UINT)(95))

                                           ;

    }

    y.tv_sec = 2;

    y.tv_nsec = 100000000;

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((Utils_timespecAdd(&x, &y, &result))), (

   ((void*)0)

   ), (UNITY_UINT)(100), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((100000000)), (UNITY_INT)((result.tv_nsec)), (

   ((void*)0)

   ), (UNITY_UINT)(101), UNITY_DISPLAY_STYLE_INT);

  }

  x.tv_sec = y.tv_sec = 0;

  x.tv_nsec = y.tv_nsec = 2100000000;

  UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((Utils_timespecAdd(&x, &y, &result))), (

 ((void*)0)

 ), (UNITY_UINT)(105), UNITY_DISPLAY_STYLE_INT);

}



void test_TestPosixUtils_Utils_timespecSubtract_() {

  struct timespec result = {.tv_sec = 0, .tv_nsec = 0};

  struct timespec x = {.tv_sec = 0, .tv_nsec = 0};

  struct timespec y = {.tv_sec = 0, .tv_nsec = 0};



  UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((Utils_timespecSubtract(&x, &y, 

 ((void*)0)

 ))), (

 ((void*)0)

 ), (UNITY_UINT)(113), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((Utils_timespecSubtract(

 ((void*)0)

 , &y, &result))), (

 ((void*)0)

 ), (UNITY_UINT)(114), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((Utils_timespecSubtract(&x, 

 ((void*)0)

 , &result))), (

 ((void*)0)

 ), (UNITY_UINT)(115), UNITY_DISPLAY_STYLE_INT);



  x.tv_sec = 5;

  y.tv_sec = 3;

  x.tv_nsec = y.tv_nsec = 0;

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((Utils_timespecSubtract(&x, &y, &result))), (

 ((void*)0)

 ), (UNITY_UINT)(120), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((UNITY_INT)((2)), (UNITY_INT)((result.tv_sec)), (

 ((void*)0)

 ), (UNITY_UINT)(121), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((result.tv_nsec)), (

 ((void*)0)

 ), (UNITY_UINT)(122), UNITY_DISPLAY_STYLE_INT);

  x.tv_sec = 1;

  y.tv_sec = 3;

  x.tv_nsec = y.tv_nsec = 0;

  UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((Utils_timespecSubtract(&x, &y, &result))), (

 ((void*)0)

 ), (UNITY_UINT)(126), UNITY_DISPLAY_STYLE_INT);



  x.tv_sec = y.tv_sec = 0;

  x.tv_nsec = 5;

  y.tv_nsec = 3;

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((Utils_timespecSubtract(&x, &y, &result))), (

 ((void*)0)

 ), (UNITY_UINT)(131), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((result.tv_sec)), (

 ((void*)0)

 ), (UNITY_UINT)(132), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((UNITY_INT)((2)), (UNITY_INT)((result.tv_nsec)), (

 ((void*)0)

 ), (UNITY_UINT)(133), UNITY_DISPLAY_STYLE_INT);



  x.tv_sec = y.tv_sec = 0;

  x.tv_nsec = 0;

  y.tv_nsec = 5;

  UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((Utils_timespecSubtract(&x, &y, &result))), (

 ((void*)0)

 ), (UNITY_UINT)(138), UNITY_DISPLAY_STYLE_INT);



  x.tv_sec = y.tv_sec = 0;

  x.tv_nsec = -5;

  y.tv_nsec = 3;

  UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((Utils_timespecSubtract(&x, &y, &result))), (

 ((void*)0)

 ), (UNITY_UINT)(143), UNITY_DISPLAY_STYLE_INT);



  x.tv_sec = 1;

  y.tv_sec = 0;

  x.tv_nsec = 0;

  y.tv_nsec = 2100000000;

  UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((Utils_timespecSubtract(&x, &y, &result))), (

 ((void*)0)

 ), (UNITY_UINT)(149), UNITY_DISPLAY_STYLE_INT);



  x.tv_sec = x.tv_nsec = 5;

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((Utils_timespecSubtract(&x, &x, &x))), (

 ((void*)0)

 ), (UNITY_UINT)(152), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((x.tv_sec)), (

 ((void*)0)

 ), (UNITY_UINT)(153), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((x.tv_nsec)), (

 ((void*)0)

 ), (UNITY_UINT)(154), UNITY_DISPLAY_STYLE_INT);

}



void test_TestPosixUtils_Utils_timespecAdd_Nanoseconds_() {

  struct timespec result = {.tv_sec = 0, .tv_nsec = 0};

  struct timespec x = {.tv_sec = 0, .tv_nsec = 0};

  int64_t nanosec = 0;



  UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((Utils_timespecAddNanoseconds(&x, nanosec, 

 ((void*)0)

 ))), (

 ((void*)0)

 ), (UNITY_UINT)(162), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((Utils_timespecAddNanoseconds(

 ((void*)0)

 , nanosec, &result))), (

 ((void*)0)

 ), (UNITY_UINT)(163), UNITY_DISPLAY_STYLE_INT)

                                                                             ;



  x.tv_sec = 5;

  x.tv_nsec = 500000000;

  nanosec = 4500000000LL;

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((Utils_timespecAddNanoseconds(&x, nanosec, &result))), (

 ((void*)0)

 ), (UNITY_UINT)(169), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((UNITY_INT)((10)), (UNITY_INT)((result.tv_sec)), (

 ((void*)0)

 ), (UNITY_UINT)(170), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((result.tv_nsec)), (

 ((void*)0)

 ), (UNITY_UINT)(171), UNITY_DISPLAY_STYLE_INT);



  x.tv_sec = 5;

  x.tv_nsec = 500000000;

  nanosec = -9500000000LL;

  UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((Utils_timespecAddNanoseconds(&x, nanosec, &result))), (

 ((void*)0)

 ), (UNITY_UINT)(176), UNITY_DISPLAY_STYLE_INT);



  x.tv_sec = x.tv_nsec = 5;

  nanosec = 4999999995;

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((Utils_timespecAddNanoseconds(&x, nanosec, &x))), (

 ((void*)0)

 ), (UNITY_UINT)(180), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((UNITY_INT)((10)), (UNITY_INT)((x.tv_sec)), (

 ((void*)0)

 ), (UNITY_UINT)(181), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((x.tv_nsec)), (

 ((void*)0)

 ), (UNITY_UINT)(182), UNITY_DISPLAY_STYLE_INT);

}



void test_TestPosixUtils_Utils_strnlen_() {

  static const char *const str = "This is a string used to test Utils_strnlen.";

  size_t len = strlen(str);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((Utils_strnlen(

 ((void*)0)

 , len))), (

 ((void*)0)

 ), (UNITY_UINT)(188), UNITY_DISPLAY_STYLE_UINT32);



  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((Utils_strnlen("", len))), (

 ((void*)0)

 ), (UNITY_UINT)(190), UNITY_DISPLAY_STYLE_UINT32);



  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((Utils_strnlen(str, 0))), (

 ((void*)0)

 ), (UNITY_UINT)(192), UNITY_DISPLAY_STYLE_UINT32);



  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((len - 1UL)), (UNITY_INT)(UNITY_UINT32)((Utils_strnlen(str, len - 1UL))), (

 ((void*)0)

 ), (UNITY_UINT)(194), UNITY_DISPLAY_STYLE_UINT32);



  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((len)), (UNITY_INT)(UNITY_UINT32)((Utils_strnlen(str, len + 1UL))), (

 ((void*)0)

 ), (UNITY_UINT)(196), UNITY_DISPLAY_STYLE_UINT32);

}



void test_TestPosixUtils_Utils_timespecCompare_() {

  struct timespec timeX = {.tv_sec = 0, .tv_nsec = 0};

  struct timespec timeY = {.tv_sec = 0, .tv_nsec = 0};



  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((Utils_timespecCompare(

 ((void*)0)

 , 

 ((void*)0)

 ))), (

 ((void*)0)

 ), (UNITY_UINT)(203), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((Utils_timespecCompare(

 ((void*)0)

 , &timeY))), (

 ((void*)0)

 ), (UNITY_UINT)(204), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((Utils_timespecCompare(&timeX, 

 ((void*)0)

 ))), (

 ((void*)0)

 ), (UNITY_UINT)(205), UNITY_DISPLAY_STYLE_INT);



  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((Utils_timespecCompare(&timeX, &timeY))), (

 ((void*)0)

 ), (UNITY_UINT)(207), UNITY_DISPLAY_STYLE_INT);



  timeX.tv_nsec = 1;

  UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((Utils_timespecCompare(&timeX, &timeY))), (

 ((void*)0)

 ), (UNITY_UINT)(210), UNITY_DISPLAY_STYLE_INT);

  timeX.tv_sec = 1;

  UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((Utils_timespecCompare(&timeX, &timeY))), (

 ((void*)0)

 ), (UNITY_UINT)(212), UNITY_DISPLAY_STYLE_INT);



  timeY.tv_sec = 1;

  timeY.tv_nsec = 2;

  UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((Utils_timespecCompare(&timeX, &timeY))), (

 ((void*)0)

 ), (UNITY_UINT)(216), UNITY_DISPLAY_STYLE_INT);

  timeX.tv_sec = 0;

  UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((Utils_timespecCompare(&timeX, &timeY))), (

 ((void*)0)

 ), (UNITY_UINT)(218), UNITY_DISPLAY_STYLE_INT);

}



void test_TestPosixUtils_Utils_timespecToTicks_() {

  struct timespec timeX = {.tv_sec = 0, .tv_nsec = 0};

  clock_t result;



  UnityAssertEqualNumber((UNITY_INT)((

 22

 )), (UNITY_INT)((Utils_timespecToTicks(

 ((void*)0)

 , &result))), (

 ((void*)0)

 ), (UNITY_UINT)(225), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((UNITY_INT)((

 22

 )), (UNITY_INT)((Utils_timespecToTicks(&timeX, 

 ((void*)0)

 ))), (

 ((void*)0)

 ), (UNITY_UINT)(226), UNITY_DISPLAY_STYLE_INT);



  timeX.tv_nsec = (1000000000LL) + 1;

  UnityAssertEqualNumber((UNITY_INT)((

 22

 )), (UNITY_INT)((Utils_timespecToTicks(&timeX, &result))), (

 ((void*)0)

 ), (UNITY_UINT)(229), UNITY_DISPLAY_STYLE_INT);

  timeX.tv_nsec = -1;

  UnityAssertEqualNumber((UNITY_INT)((

 22

 )), (UNITY_INT)((Utils_timespecToTicks(&timeX, &result))), (

 ((void*)0)

 ), (UNITY_UINT)(231), UNITY_DISPLAY_STYLE_INT);



  timeX.tv_sec = 1;

  timeX.tv_nsec = ((1000000000LL) / 

                 1000000L

                 ) + 1;

  clock_t expectedVal = (clock_t)timeX.tv_sec * 

                                               1000000L 

                                                              + 2;

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((Utils_timespecToTicks(&timeX, &result))), (

 ((void*)0)

 ), (UNITY_UINT)(236), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((UNITY_INT)(((int)expectedVal)), (UNITY_INT)(((int)result)), (

 ((void*)0)

 ), (UNITY_UINT)(237), UNITY_DISPLAY_STYLE_INT);

}



void test_TestPosixUtils_Utils_absoluteTimespecToDeltaTicks_() {

  struct timespec timeX = {.tv_sec = 0, .tv_nsec = 0};

  struct timespec timeY = {.tv_sec = 0, .tv_nsec = 0};

  clock_t result;



  UnityAssertEqualNumber((UNITY_INT)((

 22

 )), (UNITY_INT)((Utils_absoluteTimespecToDeltaTicks(&timeX, &timeY, 

 ((void*)0)

 ))), (

 ((void*)0)

 ), (UNITY_UINT)(245), UNITY_DISPLAY_STYLE_INT)

                                                                       ;

  UnityAssertEqualNumber((UNITY_INT)((

 22

 )), (UNITY_INT)((Utils_absoluteTimespecToDeltaTicks(

 ((void*)0)

 , &timeY, &result))), (

 ((void*)0)

 ), (UNITY_UINT)(247), UNITY_DISPLAY_STYLE_INT)

                                                                        ;

  UnityAssertEqualNumber((UNITY_INT)((

 22

 )), (UNITY_INT)((Utils_absoluteTimespecToDeltaTicks(&timeX, 

 ((void*)0)

 , &result))), (

 ((void*)0)

 ), (UNITY_UINT)(249), UNITY_DISPLAY_STYLE_INT)

                                                                        ;



  timeY.tv_sec = 1;

  UnityAssertEqualNumber((UNITY_INT)((

 110

 )), (UNITY_INT)((Utils_absoluteTimespecToDeltaTicks(&timeX, &timeY, &result))), (

 ((void*)0)

 ), (UNITY_UINT)(253), UNITY_DISPLAY_STYLE_INT)

                                                                             ;

  timeX.tv_sec = 2;

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((Utils_absoluteTimespecToDeltaTicks(&timeX, &timeY, &result))), (

 ((void*)0)

 ), (UNITY_UINT)(256), UNITY_DISPLAY_STYLE_INT)

                                                                     ;



  timeY.tv_nsec = (1000000000LL) + 1;

  UnityAssertEqualNumber((UNITY_INT)((

 22

 )), (UNITY_INT)((Utils_absoluteTimespecToDeltaTicks(&timeX, &timeY, &result))), (

 ((void*)0)

 ), (UNITY_UINT)(260), UNITY_DISPLAY_STYLE_INT)

                                                                          ;

}
