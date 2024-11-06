set(EXECUTABLE "caesar_for_website")
add_executable(${EXECUTABLE} caesar_for_website.cpp)
set_target_properties(${EXECUTABLE}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/../bin
)

set(EXECUTABLE "Exercise_8_2")
add_executable(${EXECUTABLE} Exercise_8_2.cpp hex.cpp)
set_target_properties(${EXECUTABLE}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/../bin
)
target_include_directories(${EXECUTABLE} PRIVATE .)