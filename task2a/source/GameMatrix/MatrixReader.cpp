#include "MatrixReader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

MatrixReader::MatrixReader() {
	// Заполнение матрицы вручную назначенными числами
	matrix[{'C', 0}] = 7;
	matrix[{'C', 1}] = 3;
	matrix[{'C', 2}] = 0;
	matrix[{'D', 0}] = 9;
	matrix[{'D', 1}] = 5;
	matrix[{'D', 2}] = 1;
}

MatrixReader::MatrixReader(const std::string& file_path) {
	loadMatrix(file_path);
}

void MatrixReader::loadMatrix(const std::string& file_path) {
	std::ifstream file(file_path);
	if (!file.is_open()) {
		throw std::runtime_error("Не удалось открыть файл матрицы: " + file_path);
	}

	std::string line;
	// Пропускаем заголовок
	if (std::getline(file, line)) {
		while (std::getline(file, line)) {
			parseLine(line);
		}
	}

	file.close();
}

void MatrixReader::parseLine(const std::string& line) {
	std::istringstream stream(line);
	std::string prisoner_choice;
	std::string amogus_count;
	std::string result;

	if (std::getline(stream, prisoner_choice, ';') &&
		std::getline(stream, amogus_count, ';') &&
		std::getline(stream, result, ';')) {

		char choice = prisoner_choice[0];
		int count = std::stoi(amogus_count);
		int res = std::stoi(result);

		matrix[{choice, count}] = res;
	} else {
		throw std::runtime_error("Ошибка парсинга строки: " + line);
	}
}

int MatrixReader::getResult(char prisoner_choice, int amogus_count) const {
	Key key = {prisoner_choice, amogus_count};
	auto it = matrix.find(key);
	if (it != matrix.end()) {
		return it->second;
	}
	throw std::out_of_range("Нет данных для заданного сочетания: " +
							std::string(1, prisoner_choice) + ", " +
							std::to_string(amogus_count));
}

const MatrixReader::MatrixMap& MatrixReader::getMatrix() const {
	return matrix;
}

