set(EXECUTABLE "Problem_10_5")
add_executable(${EXECUTABLE} Problem_10_5.cpp)
set_target_properties(${EXECUTABLE}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/../bin
)
