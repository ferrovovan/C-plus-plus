# Makefile для Задания 1
CC = g++
CFLAGS = -std=c++17 -Wall -Wextra
TARGET = solve_quadratic

all: $(TARGET)

$(TARGET): solve_quadratic.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGET)

