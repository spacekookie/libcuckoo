cmake_minimum_required(VERSION 2.8.13)
project(libcuckoo)

include(CTest)

set(LIBCUCKOO_SRC
    src/cuckoo.c
    src/insert.c
    src/hashing.c
)

add_library(libcuckoo-static STATIC ${LIBCUCKOO_SRC})
target_include_directories(libcuckoo-static PUBLIC "include")
set_target_properties(libcuckoo-static PROPERTIES OUTPUT_NAME "cuckoo")

add_library(libcuckoo SHARED ${LIBCUCKOO_SRC})
target_include_directories(libcuckoo PUBLIC "include")
set_target_properties(libcuckoo PROPERTIES PREFIX "")

if (BUILD_TESTING)
enable_testing()
add_subdirectory (test)
endif ()

INSTALL (
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION include )

#install (TARGETS libcuckoo LIBRARY DESTINATION lib)
#install (TARGETS libcuckoo-static LIBRARY DESTINATION lib)

install (TARGETS libcuckoo
         ARCHIVE DESTINATION lib
         LIBRARY DESTINATION lib)

install (TARGETS libcuckoo-static
         ARCHIVE DESTINATION lib
         LIBRARY DESTINATION lib)
