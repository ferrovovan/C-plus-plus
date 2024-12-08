#ifndef GAMEMATRIX_HPP
#define GAMEMATRIX_HPP

#include "MatrixReader.hpp"
#include "../types.hpp"
#include <vector>
#include <string>

class GameMatrix {
private:
	MatrixReader matrixReader; // Объект для чтения матрицы

public:
	// Конструктор с файлом матрицы
	explicit GameMatrix(const std::string &file_path);

	// Получение очков за комбинацию решений
	// для первого решения
	int getScore(Decision d1, Decision d2, Decision d3) const;

	// Рассчитать очки для всех участников
	std::vector<int> calculate_scores(const Choices &choices) const;
};

#endif // GAMEMATRIX_HPP
