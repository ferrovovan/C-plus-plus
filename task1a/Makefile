# Компилятор
CXX = g++

# Флаги компиляции (включаем отладочные символы и предупреждения)
CXXFLAGS = -Wall -g -std=c++17

# Дополнительные флаги для профилирования (покрытие кода)
CXXFLAGS += -fprofile-arcs -ftest-coverage

# Флаги для линковки с Google Test
GTEST_LIBS = -lgtest -lgtest_main -pthread

# Директории
OBJ_DIR = build
COV_DIR = coverage
SRC_DIR = src
TEST_DIR = tests
INCLUDE_DIR = include

# Заголовочные файлы
INCLUDES = $(INCLUDE_DIR)/BitArray.h

# Исходные файлы
SRCS = $(SRC_DIR)/BitArray.cpp $(TEST_DIR)/BitArrayTest.cpp

# Объектные файлы
OBJS = $(OBJ_DIR)/BitArray.o $(OBJ_DIR)/BitArrayTest.o

# Имя тестового исполняемого файла
TEST_TARGET = run_tests

# Сборка объектных файлов
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDES)
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(OBJ_DIR)/BitArrayTest.o: $(TEST_DIR)/BitArrayTest.cpp $(INCLUDES)
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Линковка тестов с Google Test
$(TEST_TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(OBJS) $(GTEST_LIBS)

# Цель по умолчанию
all: $(TEST_TARGET)

# Запуск тестов
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Профилирование и генерация отчётов покрытия для BitArray.cpp
coating: $(TEST_TARGET) test
	@mkdir -p $(COV_DIR)
	gcov --no-json-format -o $(OBJ_DIR) $(SRC_DIR)/BitArray.cpp -i
	mv *.gcov $(COV_DIR)

# Очистка
clean:
	rm -f $(OBJS) $(TEST_TARGET)
	rm -rf $(OBJ_DIR)
	rm -f *.gcda *.gcno
	rm -rf $(COV_DIR)

