set(EXECUTABLE "Exercise_7_4")
add_executable(${EXECUTABLE} Exercise_7_4.cpp)
set_target_properties(${EXECUTABLE}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/../bin
)