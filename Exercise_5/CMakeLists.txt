set(EXECUTABLE "fuzzer")
add_executable(${EXECUTABLE} fuzzer.c print_filter_c_fuzz.c)
set_target_properties(${EXECUTABLE}
    PROPERTIES
    LINKER_LANGUAGE C
    C_COMPILER ${AFL_COMPILER}
    CXX_COMPILER ${AFL_COMPILER_PP}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/../bin
)
target_include_directories(${EXECUTABLE} PRIVATE .)
target_compile_options(${EXECUTABLE} PRIVATE -fsanitize=address)
target_link_options(${EXECUTABLE} PRIVATE -fsanitize=address)
