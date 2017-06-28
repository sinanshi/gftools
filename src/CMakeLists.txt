file(GLOB src_files "*.cpp")
include_directories(".")

add_library(gftools ${src_files})
target_link_libraries(gftools ${Boost_LIBRARIES} ${BGEN_LIBRARIES})
