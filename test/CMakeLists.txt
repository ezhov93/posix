add_library(unity STATIC IMPORTED)
set_target_properties(unity PROPERTIES
  IMPORTED_LOCATION 
  "C:/usr/lib/libunity.a"
  INTERFACE_INCLUDE_DIRECTORIES 
  "C:/usr/include/unity/" 
)


add_executable(testrun
        testrunner.c
        test_clock.c
        test_utils.c
        )

target_compile_features(testrun PRIVATE cxx_std_17 c_std_11)

target_link_libraries(testrun PRIVATE Posix unity)

add_test(NAME TestClock COMMAND testrun)
add_test(NAME TestUtils COMMAND testrun)

#add_test(NAME testuarttest COMMAND testrun)