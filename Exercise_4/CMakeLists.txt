set(EXECUTABLE "print_filter_c")
add_executable(${EXECUTABLE} print_filter_c.c)
set_target_properties(${EXECUTABLE}
    PROPERTIES
    LINKER_LANGUAGE C
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/../bin
)

set(EXECUTABLE "print_filter_cpp")
add_executable(${EXECUTABLE} print_filter_cpp.cpp)
set_target_properties(${EXECUTABLE}
    PROPERTIES
    LINKER_LANGUAGE CXX
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/../bin
)