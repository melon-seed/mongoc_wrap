cmake_minimum_required(VERSION 3.0.0)

project(MangoLib)


SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

include_directories(include)

if(WIN32)
    message("WIN32")
    include_directories("C:\\mongo-c-driver\\include")
    include_directories("C:\\mongo-c-driver\\include\\libmongoc-1.0")
    include_directories("C:\\mongo-c-driver\\include\\libbson-1.0")
    link_directories("C:\\mongo-c-driver\\lib")
    link_directories("C:\\mongo-c-driver\\bin")
else()
    message("UNIX")
    include_directories("/usr/local/include/libbson-1.0")
    include_directories("/usr/local/include/libmongoc-1.0")
    find_package (mongoc-1.0 1.6 REQUIRED)
endif()



add_library(mmongoc STATIC
            src/library.c)
            
if(WIN32)
    message("WIN32")
    target_link_libraries(mmongoc PUBLIC
                          bson-1.0
                          libbson-1.0
                          libmongoc-1.0
                          mongoc-1.0
                          )
else()
    message("UNIX")
    target_link_libraries (mmongoc 
                        PRIVATE mongo::mongoc_static)
    # target_link_libraries(mmongoc 
    #                       bson-1.0
    #                       mongoc-1.0)
endif(WIN32)
    
add_executable(test
               test/test_main.c)

target_link_libraries(test
mmongoc)