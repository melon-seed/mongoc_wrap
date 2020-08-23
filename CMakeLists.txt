cmake_minimum_required(VERSION 3.0.0)

project(MangoLib)


# SET(CMAKE_BUILD_TYPE "Debug")
# SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
# SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

include_directories(include)

if(WIN32)
    message("win32")
else()
    message("unix")
    find_package (mongoc-1.0 1.6 REQUIRED)
endif()



add_library(mmongoc STATIC
            src/library.c)
            
if(WIN32)
    message("win32")
else()
    target_link_libraries (mmongoc 
                        PRIVATE mongo::mongoc_static)
endif(WIN32)
    





# add_executable(test1 
#                test/test_main.c)

# target_link_libraries(test1 
#                       mmongoc)