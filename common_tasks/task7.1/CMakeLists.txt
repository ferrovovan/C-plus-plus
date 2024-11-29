cmake_minimum_required(VERSION 3.10)

project(TimeProject)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем, что исходники находятся в папке source
include_directories(source)

# Добавляем библиотеку Time
add_library(Time STATIC source/Time.cpp)

# Добавляем библиотеку Watch
add_library(Watch STATIC source/Watch.cpp)

# Добавляем библиотеку SimpleWatch
add_library(SimpleWatch STATIC source/SimpleWatch.cpp)

# Добавляем исполнимый файл
add_executable(main main.cpp)

# Связываем исполнимый файл с библиотеками.
target_link_libraries(main Time Watch SimpleWatch)

