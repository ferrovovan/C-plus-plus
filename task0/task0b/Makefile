# Имя исполняемого файла
TARGET = word_count

# Компилятор
CXX = g++

# Флаги компиляции
CXXFLAGS = -Wall -O2

# Исходный файл
SRC = src/word_count.cpp

# Правило по умолчанию
all: $(TARGET)

# Сборка
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Очистка
clean:
	rm -f $(TARGET)

