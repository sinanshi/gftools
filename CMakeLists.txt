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

add_subdirectory(src)
add_subdirectory(tests)
