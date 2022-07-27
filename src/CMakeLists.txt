file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${Posix_SOURCE_DIR}/include/*.h")

add_library(Posix
        utils.c
        ${HEADER_LIST}
        )

target_include_directories(Posix PUBLIC ../include)

target_link_libraries(Posix)

target_compile_features(Posix PUBLIC cxx_std_17 c_std_11)

source_group(
        TREE "${PROJECT_SOURCE_DIR}/include"
        PREFIX "Header Files"
        FILES ${HEADER_LIST})
