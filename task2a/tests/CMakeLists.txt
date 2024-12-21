# Найдём GoogleTest
find_package(GTest REQUIRED)

# Создаём исполняемый файл для всех тестов
add_executable(PrisonersDilemmaTest
	test_Utils.cpp
	test_GameMatrix.cpp
)

# Линкуем зависимости
target_link_libraries(PrisonersDilemmaTest PRIVATE
	CommandLineParser_Lib
	GameMatrix_Lib
	GTest::GTest
	GTest::Main
)

# Добавляем тесты в CTest
add_test(NAME PrisonersDilemmaTest COMMAND PrisonersDilemmaTest)
