
project(OpenTLD)

cmake_minimum_required(VERSION 2.6)
 add_compile_options(-std=c++11)
find_package(OpenCV REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

#-------------------------------------------------------------------------------
#version
#------------------------------------------------------------------------------
#build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING
        "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
        FORCE)
endif(NOT CMAKE_BUILD_TYPE)

option(BUILD_QOPENTLD "Build with Qt-config-dialog." OFF)
option(USE_SYSTEM_LIBS "Use the installed version of libconfig++." ON)
option(WITH_OPENMP "Use OpenMP." ON)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

#-------------------------------------------------------------------------------
#add subdirectories
add_subdirectory(src/3rdparty/cvblobs)

if(NOT USE_SYSTEM_LIBS)
    add_subdirectory(src/3rdparty/libconfig)
endif(NOT USE_SYSTEM_LIBS)

add_subdirectory(src/libopentld)
add_subdirectory(src/opentld)


find_package(OpenCV)

set(bin_dir "${PROJECT_SOURCE_DIR}")
set(src_dir "${PROJECT_BINARY_DIR}")

set(OPENTLD_INCLUDE_DIRS
    ${src_dir}/src/3rdparty/cvblobs
    ${src_dir}/src/3rdparty/libconfig
    ${src_dir}/src/libopentld/tld
    ${src_dir}/src/libopentld/mftracker
    ${src_dir}/src/libopentld/imacq
    ${src_dir}/src/opentld/main)
INCLUDE_DIRECTORIES(${OPENTLD_INCLUDE_DIRS})

SET(OPENTLD_LIB_DIRS ${LIBRARY_OUTPUT_PATH})
LINK_DIRECTORIES(${OPENTLD_LIB_DIRS})

set(OPENTLD_LIBS cvblobs libconfig libopentld)



