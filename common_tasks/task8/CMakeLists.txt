cmake_minimum_required(VERSION 3.10)

project(TimeProject)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем, что исходники находятся в папке source
include_directories(source)

# Добавляем исполнимый файл
add_executable(main main.cpp)


