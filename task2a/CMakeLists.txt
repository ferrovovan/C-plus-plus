cmake_minimum_required(VERSION 3.10)

project(PrisonersDilemmaSim)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES "source/*.cpp")

# Добавляем исполнимый файл
add_executable(PrisonersDilemmaSim ${SOURCES})

# Устанавливаем флаги компилятора
target_compile_options(PrisonersDilemmaSim PRIVATE -Wall -pedantic)

