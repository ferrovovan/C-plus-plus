# Найдём GoogleTest
find_package(GTest REQUIRED)

# Создадим исполнимый файл для тестов
add_executable(TimeTests Time_test.cpp)

# Свяжем тесты с GoogleTest и Time
target_link_libraries(TimeTests GTest::GTest GTest::Main Time)

# Добавляем тесты в CTest
add_test(NAME TimeTests COMMAND TimeTests)

