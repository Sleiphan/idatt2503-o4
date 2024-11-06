set(EXECUTABLE "Problem_2")
add_executable(${EXECUTABLE} Problem_2.cpp)
set_target_properties(${EXECUTABLE}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/../bin
)

set(EXECUTABLE "Problem_3")
add_executable(${EXECUTABLE} Problem_3.cpp galois_field.cpp)
set_target_properties(${EXECUTABLE}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/../bin
)
target_include_directories(${EXECUTABLE} PRIVATE .)

set(EXECUTABLE "Problem_4")
add_executable(${EXECUTABLE} Problem_4.cpp galois_field.cpp)
set_target_properties(${EXECUTABLE}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/../bin
)
target_include_directories(${EXECUTABLE} PRIVATE .)
