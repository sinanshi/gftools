cmake_minimum_required(VERSION 3.2)
project(gftools VERSION 0.0)


#list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)


find_package(Boost COMPONENTS program_options iostreams filesystem REQUIRED)
if (Boost_FOUND)
  include_directories(${BOOST_INCLUDE_DIRS})
endif()

find_package(Eigen3 REQUIRED)
include_directories(${Eigen3_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11) 
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11

enable_testing()

set(GLOBAL_OUTPUT_PATH ${PROJECT_BINARY_DIR}/output)

#if(NOT BGEN_SETUP)
#  #  Adding BGEN library
#  include(ExternalProject)
#
#  ExternalProject_Add(
#    bgen
#    HG_REPOSITORY https://bitbucket.org/gavinband/bgen
#    HG_TAG "master"
#
#    SOURCE_DIR "${PROJECT_BINARY_DIR}/3rdparty/bgen"
#    CONFIGURE_COMMAND ./waf-1.8.13 configure 
#    BINARY_DIR "${PROJECT_BINARY_DIR}/3rdparty/bgen"
#    BUILD_COMMAND ./waf-1.8.13 && cd 3rd_party/zstd-1.1.0/lib && make
#    INSTALL_COMMAND ""
#    )
#
#  set(BGEN_SETUP TRUE CACHE BOOL "bgen setup status")
#endif()

#include_directories(${PROJECT_BINARY_DIR}/3rdparty/bgen/3rd_party/zstd-1.1.0/lib)
#set(BGEN_INCLUDE_DIRS ${PROJECT_BINARY_DIR}/3rdparty/bgen/genfile/include/)
#set(BGEN_LIBRARIES ${PROJECT_BINARY_DIR}/3rdparty/bgen/build/libbgen.a)
#set(ZSTD_LIBRARIES ${PROJECT_BINARY_DIR}/3rdparty/bgen/3rd_party/zstd-1.1.0/lib/libzstd.so)
#link_directories(${PROJECT_BINARY_DIR}/3rdparty/bgen/3rd_party/zstd-1.1.0/lib)
#include_directories(${BGEN_INCLUDE_DIRS})

add_subdirectory(src)
add_subdirectory(tests)
#add_subdirectory(app)
