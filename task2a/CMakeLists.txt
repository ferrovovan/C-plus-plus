cmake_minimum_required(VERSION 3.10)

project(PrisonersDilemmaSim)

set(CMAKE_CXX_STANDARD 17)

# Источники проекта
file(GLOB SOURCES
    "source/*.cpp"
    "source/GameMatrix/*.cpp"
    "source/History/*.cpp"
    "source/Simulation/*.cpp"
    "source/strategies/concrete/*.cpp"
    "source/strategies/*.cpp"
    "source/utils/*.cpp"
)

# Добавляем исполнимый файл
add_executable(PrisonersDilemmaSim ${SOURCES})

# Устанавливаем флаги компилятора
target_compile_options(PrisonersDilemmaSim PRIVATE -Wall -pedantic)

