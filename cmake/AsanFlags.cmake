set(CMAKE_CXX_FLAGS_ASAN "-g -fsanitize=address,undefined"
    CACHE STRING "Compiler flags in Asan build"
    FORCE
)