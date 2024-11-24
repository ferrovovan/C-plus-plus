# Найдём GoogleTest
find_package(GTest REQUIRED)

# Создадим исполнимый файл для тестов
add_executable(BitArrayTest BitArrayTest.cpp)

# Свяжем тесты с GoogleTest и Time
# Линковка тестов с библиотекой BitArray и GTest
target_link_libraries(BitArrayTest PRIVATE BitArray GTest::GTest GTest::Main)

# Добавляем тесты в CTest
add_test(NAME BitArrayTest COMMAND BitArrayTest)

