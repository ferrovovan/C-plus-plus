#ifndef MATRIXREADER_HPP
#define MATRIXREADER_HPP

#include <string>
#include <unordered_map>
#include <tuple>
#include <stdexcept>
#include "../utils/HashUtils.hpp"

class MatrixReader {
public:
	using Key = std::pair<char, int>; // 'C' или 'D' и количество амогусов
	using MatrixMap = std::unordered_map<Key, int>;

	// Конструкторы
	MatrixReader();
	explicit MatrixReader(const std::string& file_path);

	// Получение результата для конкретного сочетания
	int getResult(char prisoner_choice, int amogus_count) const;

	// Получение всей матрицы
	const MatrixMap& getMatrix() const;

private:
	MatrixMap matrix;

	// Вспомогательный метод для загрузки данных из файла
	void loadMatrix(const std::string& file_path);

	// Парсинг строки
	void parseLine(const std::string& line);
};

#endif // MATRIXREADER_HPP
