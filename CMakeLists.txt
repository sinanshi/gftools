cmake_minimum_required(VERSION 3.2)
project(gftools VERSION 0.0)

find_package(Boost COMPONENTS program_options iostreams filesystem REQUIRED)
if (Boost_FOUND)
  include_directories(${BOOST_INCLUDE_DIRS})
endif()


set(CMAKE_CXX_STANDARD 11) 
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11

enable_testing()



set(GLOBAL_OUTPUT_PATH ${PROJECT_BINARY_DIR}/output)

include(ExternalProject)

ExternalProject_Add(
  bgen
  HG_REPOSITORY https://bitbucket.org/gavinband/bgen
  HG_TAG "master"

  SOURCE_DIR "${PROJECT_BINARY_DIR}/3rdparty/bgen"
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  CONFIGURE_COMMAND ""
  )

ExternalProject_Add_Step(
  bgen custom_build
  COMMAND cd 3rdparty/bgen && ./waf-1.8.13 configure && ./waf-1.8.13
  )

set(BGEN_INCLUDE_DIRS ${PROJECT_BINARY_DIR}/3rdparty/bgen/genfile/include/)
set(BGEN_LIBRARIES ${PROJECT_BINARY_DIR}/3rdparty/bgen/build/libbgen.a)
include_directories(${BGEN_INCLUDE_DIRS})


add_subdirectory(src)
add_subdirectory(tests)
