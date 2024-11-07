set(EXECUTABLE "Problem_9_2")
add_executable(${EXECUTABLE} Problem_9_2.cpp)
set_target_properties(${EXECUTABLE}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/../bin
)

set(EXECUTABLE "Problem_9_3")
add_executable(${EXECUTABLE} Problem_9_3.cpp galois_field.cpp)
set_target_properties(${EXECUTABLE}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/../bin
)
target_include_directories(${EXECUTABLE} PRIVATE .)

set(EXECUTABLE "Problem_9_4")
add_executable(${EXECUTABLE} Problem_9_4.cpp galois_field.cpp)
set_target_properties(${EXECUTABLE}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/../bin
)
target_include_directories(${EXECUTABLE} PRIVATE .)
