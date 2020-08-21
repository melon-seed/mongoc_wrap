cmake_minimum_required(VERSION 3.0.0)

project(MangoLib)


SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

include_directories(include)
include_directories(include/libbson-1.0)
include_directories(include/libmongoc-1.0)

link_directories(lib)

add_library(mmongoc SHARED
            src/library.c)
            
target_link_libraries(mmongoc
                      bson-1.0
                      mongoc-1.0)



add_executable(test1
               test/test_main.c)

target_link_libraries(test1 
mmongoc)