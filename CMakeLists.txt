cmake_minimum_required(VERSION 3.8)
project(libcuckoo)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -std=c11")

set(LIBCUCKOO_SRC
    src/cuckoo.c
    src/hashing.c
)

# Create a library with properties and import paths
add_library(libcuckoo STATIC ${LIBCUCKOO_SRC})
target_include_directories(libcuckoo PUBLIC "include")
target_include_directories(libcuckoo PRIVATE "src")
set_target_properties(libcuckoo PROPERTIES PREFIX "")

add_executable(cuckoo_test test/main.c)
target_link_libraries(cuckoo_test libcuckoo)