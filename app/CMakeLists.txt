add_executable(bgen2vcf bgen2vcf.cpp)
target_link_libraries(bgen2vcf ${BGEN_LIBRARIES} zstd z)
