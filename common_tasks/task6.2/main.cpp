#include <iostream>
#include <string>  // для print_green()
#include "Time.hpp"

void print_green(const std::string& message) {
	std::cout << "\033[0;32m" << message << "\033[0m\n";
}

// Тест нормализации времени и вызова исключений при установке некорректных часов
void TestNormalizationAndSetHours() {
	try {
		std::cout << "Testing normalization and SetHours...\n";
		Time t1(10, 30, -100);  // Нормализация
		t1.PrintTime();

		t1.SetHours(-5);  // Намеренное исключение
	} catch (const std::invalid_argument& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}
}

// Тест обработки сбоев потока вывода
void TestOutputStreamException() {
	try {
		std::cout << "Testing output stream exception...\n";
		std::cout.setstate(std::ios::failbit);  // Искусственный сбой
		Time t2(23, 59, 59);
		t2.PrintTime();
	} catch (const std::ios_base::failure& e) {
		std::cerr << "Output Exception: " << e.what() << std::endl;
		std::cout.clear();  // Восстановить поток
	}
}

// Тест создания объектов времени, в том числе с некорректными параметрами
void TestTimeCreation() {
	try {
		std::cout << "Creating valid Time object...\n";
		Time t1(2, 30, 45);  // Корректное создание
		t1.PrintTime();

		std::cout << "Creating invalid Time object...\n";
		Time t2(-1, 15, 0); // Генерация исключения
		t2.PrintTime();
	} catch (const std::invalid_argument& e) {
		std::cerr << "Caught exception: " << e.what() << "\n";
	}
}

// Тест добавления некорректного значения секунд
void TestInvalidSecondsAddition() {
	try {
		std::cout << "Creating Time object and adding invalid seconds...\n";
		Time t3(3, 0, 0);
		t3 = t3 + (-3600);  // Исключение из-за отрицательных секунд
		t3.PrintTime();
	} catch (const std::invalid_argument& e) {
		std::cerr << "Caught exception: " << e.what() << "\n";
	}
}

int main() {
	print_green("\nTest1");
	TestNormalizationAndSetHours();
	print_green("\nTest2");
	TestOutputStreamException();
	print_green("\nTest3");
	TestTimeCreation();
	print_green("\nTest4");
	TestInvalidSecondsAddition();

	return 0;
}

