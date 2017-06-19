add_executable(testio io.cc)

add_test(io ${EXECUTABLE_OUTPUT_PATH}/testio)
#target_include_directories(testio ${CMAKE_SOURCE_DIR}/src)


target_link_libraries(testio gftools)
#target_link_libraries(testselect hamming_select)


include_directories(${Boost_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/tests ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(testio ${Boost_LIBRARIES})
