cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(PrisonersDilemmaSim)


# Список исходных файлов для основной библиотеки
file(GLOB_RECURSE SOURCES "source/*.cpp")

# Создание библиотеки для основного кода (можно использовать её в обоих — основной программе и тестах)
add_library(PrisonersDilemmaLib STATIC ${SOURCES})
add_library(CommandLineParser_Lib STATIC "source/utils/CommandLineParser.cpp")
add_library(GameMatrix_Lib STATIC "source/GameMatrix/GameMatrix.cpp" "source/GameMatrix/MatrixReader.cpp")

# Добавляем исполнимый файл для основной программы
add_executable(PrisonersDilemmaSim source/main.cpp)

# Линкуем исполнимый файл с основной библиотекой
target_link_libraries(PrisonersDilemmaSim PRIVATE PrisonersDilemmaLib)

# Устанавливаем флаги компилятора
target_compile_options(PrisonersDilemmaSim PRIVATE -Wall -pedantic)

# Добавляем возможность включать тесты
option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
	enable_testing()
	add_subdirectory(tests)
endif()
