cmake_minimum_required( VERSION 3.19 )

project(ChineseOCRLite)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions("-Wall")
add_definitions(-DUNICODE -D_UNICODE)

option(USE_SYSTEM_ARGS_PARSE "build with system libargs-parse" OFF)

find_package( OpenMP REQUIRED )
if(OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

if(USE_SYSTEM_ARGS_PARSE)
    find_package( args-parser )
else()
    add_subdirectory(args-parser)
endif(USE_SYSTEM_ARGS_PARSE)
message(STATUS "args-parser_INCLUDE_DIRS: ${args-parser_INCLUDE_DIRECTORIES}")

find_package( ncnn REQUIRED )
find_package( OpenCV REQUIRED )

if (NOT OpenCV_FOUND)
    message(FATAL_ERROR "opencv Not Found!")
else()
    message(STATUS "OpenCV_LIBS: ${OpenCV_LIBS}")
    message(STATUS "OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")
endif (NOT OpenCV_FOUND)

include_directories(${args-parser_INCLUDE_DIRECTORIES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ncnn/include/ncnn)
#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/ncnn/lib)

set(SRC
        src/main.cpp
        src/ocr.cpp
        src/RRLib.cpp
        )

add_executable(chineseocr-ncnn ${SRC})
target_link_libraries(chineseocr-ncnn ncnn ${OpenCV_LIBS})
