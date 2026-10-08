cmake_minimum_required(VERSION 3.14) # Минимальная требуемая версия CMake
project(01_week) # Необходим для инициализации cmake

set(CMAKE_CXX_STANDARD 20) # Версия стандарта C++
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Гарантирует использование указанной версии стандарта

set(EXAMPLES_DIR examples) # Определим переменную с именем директории
set(TASKS_DIR tasks)

add_subdirectory(tasks)

# Создать исполняемый файл для каждого примера
if (BUILD_EXAMPLES_01_WEEK)
    add_example(hello_cpp ${EXAMPLES_DIR}/hello_cpp.cpp)
    add_example(sizeof_data_types ${EXAMPLES_DIR}/sizeof_data_types.cpp)
    add_example(numeric_limits ${EXAMPLES_DIR}/numeric_limits.cpp)
    add_example(overflow ${EXAMPLES_DIR}/overflow.cpp)
    add_example(floating_point_precisions ${EXAMPLES_DIR}/floating_point_precisions.cpp)
    add_example(variables ${EXAMPLES_DIR}/variables.cpp)
    add_example(literals ${EXAMPLES_DIR}/literals.cpp)
    add_example(variables_auto ${EXAMPLES_DIR}/variables_auto.cpp)
    add_example(operators ${EXAMPLES_DIR}/operators.cpp)
    add_example(type_conversions ${EXAMPLES_DIR}/type_conversions.cpp)
    add_example(shadowing_in_scopes ${EXAMPLES_DIR}/shadowing_in_scopes.cpp)
    add_example(global_and_block_scopes ${EXAMPLES_DIR}/global_and_block_scopes.cpp)
    add_example(namespaces ${EXAMPLES_DIR}/namespaces.cpp)
    add_example(arrays ${EXAMPLES_DIR}/arrays.cpp)
    add_example(enumerations ${EXAMPLES_DIR}/enumerations.cpp)
    add_example(control_flow ${EXAMPLES_DIR}/control_flow.cpp)
    add_example(loops ${EXAMPLES_DIR}/loops.cpp)
    add_example(functions ${EXAMPLES_DIR}/functions.cpp)
    add_example(functions_recursive ${EXAMPLES_DIR}/functions_recursive.cpp)
    add_example(io_streams ${EXAMPLES_DIR}/io_streams.cpp)
    add_example(main_with_args ${EXAMPLES_DIR}/main_with_args.cpp)
endif()