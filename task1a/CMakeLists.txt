# set minimum cmake version
cmake_minimum_required(VERSION 3.10)

# project name and language
project(BitArrayProject LANGUAGES CXX)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Включение отладочных символов и предупреждений
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")


# Директории
# Указываем, что исходники находятся в папке source
include_directories(source)

# Добавляем исходники
add_library(BitArray STATIC source/BitArray.cpp)

# Добавляем исполнимый файл
add_executable(main source/main.cpp)
# Связываем исполнимый файл с библиотекой BitArray
target_link_libraries(main PRIVATE BitArray)

# Добавляем возможность включать тесты
option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

