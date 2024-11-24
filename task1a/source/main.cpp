#include <iostream>
#include "BitArray.hpp"

int main() {
	std::cout << "Простой тест BitArray!" << std::endl;

	BitArray bitArray(8);  // Создаем массив из 8 бит
	std::cout << "bitArray: " << bitArray.to_string() << std::endl;
	bitArray.set(7, true);  // Устанавливаем 3-й бит в 1
	bitArray.set(3, true);  // Устанавливаем 3-й бит в 1
	bitArray.set(0, true);  // Устанавливаем 0-й бит в 1
	std::cout << "Установили биты в позициях 7, 3, 0 = 1: " << bitArray[3] << std::endl;
	std::cout << "bitArray: " << bitArray.to_string() << std::endl;

	return 0;
}

