cmake_minimum_required(VERSION 3.14)

project(
        Posix
        VERSION 0.1
        DESCRIPTION "Posix impliment embended library"
        LANGUAGES C CXX
)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_EXTENSIONS OFF)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(CTest)
enable_testing()


add_subdirectory(src)
if ((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING)
        AND BUILD_TESTING)
    add_subdirectory(test)
endif ()