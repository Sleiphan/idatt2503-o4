set(EXECUTABLE "fuzzer")
add_executable(${EXECUTABLE} fuzzer.c print_filter_c_fuzz.c)
set_target_properties(${EXECUTABLE}
    PROPERTIES
    LINKER_LANGUAGE C
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/../bin
)
target_include_directories(${EXECUTABLE} PRIVATE .)
target_compile_options(${EXECUTABLE} PRIVATE -fsanitize=address,fuzzer)
target_link_options(${EXECUTABLE} PRIVATE -fsanitize=address,fuzzer)
