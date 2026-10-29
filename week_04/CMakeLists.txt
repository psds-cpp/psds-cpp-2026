cmake_minimum_required(VERSION 3.14) # Минимальная требуемая версия CMake
project(04_week) # Необходим для инициализации cmake

set(CMAKE_CXX_STANDARD 20) # Версия стандарта C++
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Гарантирует использование указанной версии стандарта

set(EXAMPLES_DIR examples) # Определим переменную с именем директории
set(TASKS_DIR tasks)

add_subdirectory(tasks)

# Создать исполняемый файл для каждого примера
if (BUILD_EXAMPLES_04_WEEK)
#    add_example(class_examples ${EXAMPLES_DIR}/class_examples.cpp)
endif()