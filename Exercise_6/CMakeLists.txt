find_package(OpenSSL REQUIRED)

set(EXECUTABLE "password_crack")
add_executable(${EXECUTABLE} password_crack.c)
set_target_properties(${EXECUTABLE}
    PROPERTIES
    LINKER_LANGUAGE C
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/../bin
)
target_link_libraries(${EXECUTABLE} OpenSSL::SSL)

set(EXECUTABLE "crypto_auth")
add_executable(${EXECUTABLE} crypto_auth.cpp)
set_target_properties(${EXECUTABLE}
    PROPERTIES
    LINKER_LANGUAGE C
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/../bin
)
target_link_libraries(${EXECUTABLE} OpenSSL::SSL)