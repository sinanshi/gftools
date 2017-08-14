file(GLOB src_files "*.cpp")
file(GLOB header_files "*.h")
include_directories(".")

add_library(gftools SHARED ${src_files})
target_link_libraries(gftools ${Boost_LIBRARIES}) #${BGEN_LIBRARIES})
target_link_libraries(gftools Eigen3::Eigen)
install(TARGETS gftools DESTINATION lib)
install(FILES ${header_files} DESTINATION "include/gftools")
