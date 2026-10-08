function(add_psds_executable NAME)
    add_executable(${NAME} ${ARGN})
    set_target_properties(${NAME} PROPERTIES COMPILE_FLAGS "-Wall -Werror -Wextra")
endfunction()

function(add_gtest TARGET)
    add_psds_executable(${TARGET} ${ARGN})
    target_link_libraries(${TARGET} PRIVATE GTest::gtest GTest::gmock GTest::gtest_main)
    set_target_properties(${TARGET} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_TASKS_DIR}
    )
endfunction()

function(add_gtest_asan TARGET)
    add_psds_executable(${TARGET} ${ARGN})
    target_compile_options(${TARGET} PRIVATE -g -fsanitize=address,undefined)
    target_link_libraries(${TARGET} PRIVATE GTest::gtest GTest::gmock GTest::gtest_main)
    target_link_options(${TARGET} PRIVATE -fsanitize=address,undefined)
    set_target_properties(${TARGET} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_TASKS_DIR}
    )
endfunction()

function(add_example NAME)
    if(BUILD_EXAMPLES)
        add_psds_executable(${NAME} ${ARGN})
        set_target_properties(${NAME} PROPERTIES FOLDER "examples")
    endif()
endfunction()