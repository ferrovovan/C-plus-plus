# Найдем GoogleTest
find_package(GTest REQUIRED)

# Создаем исполнимый файл для тестов
add_executable(PrisonersDilemmaTest test_Utils.cpp)

# Линкуем только бизнес-логику, а не весь проект
target_link_libraries(PrisonersDilemmaTest PRIVATE CommandLineParser_Lib GTest::GTest GTest::Main)

# Добавляем тесты в CTest
add_test(NAME PrisonersDilemmaTest COMMAND PrisonersDilemmaTest)
