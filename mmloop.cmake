# set build type
set(CMAKE_BUILD_TYPE "Debug")

if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall")
else( CMAKE_BUILD_TYPE STREQUAL "Debug" )
        set(CMAKE_BUILD_TYPE "Release")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -fopenmp")
endif( CMAKE_BUILD_TYPE STREQUAL "Debug" )

#test support c++11 or not
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

message("Build Type:" ${CMAKE_BUILD_TYPE} ${CMAKE_CXX_FLAGS})

#for windows
IF(WIN32)
    ADD_DEFINITIONS("-D_WINDOWS -D__WIN__ -D_CRT_SECURE_NO_DEPRECATE")
    ADD_DEFINITIONS("-D_WIN32_WINNT=0x0501")
ELSE()
	set(CMAKE_LEGACY_CYGWIN_WIN32 0)
	ADD_DEFINITIONS("-D_MSYS")
ENDIF(WIN32)

SET (PLATFORM X86)

## 指定include 路径
message("Project path:" ${PROJECT_SOURCE_DIR})

set(TOP_INCLUDE ${PROJECT_SOURCE_DIR})
set(TOP_SRC ${PROJECT_SOURCE_DIR})
set(TEST_SRC ${PROJECT_SOURCE_DIR})
set(LINK_DIR ${PROJECT_SOURCE_DIR}/../libuv/Release)
link_directories(${LINK_DIR})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
