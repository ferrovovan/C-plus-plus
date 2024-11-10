# Makefile для Задания 2
CC = g++
CFLAGS = -std=c++17 -Wall -Wextra
TARGET = common_letters

all: $(TARGET)

$(TARGET): common_letters.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGET)

