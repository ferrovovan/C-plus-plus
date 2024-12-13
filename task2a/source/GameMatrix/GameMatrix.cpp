#include "GameMatrix.hpp"
#include <stdexcept>

GameMatrix::GameMatrix()
	: matrixReader() {} // Инициализация MatrixReader)

GameMatrix::GameMatrix(const std::string &file_path)
	: matrixReader(file_path) {} // Инициализация MatrixReader

int GameMatrix::getScore(Decision d1, Decision d2, Decision d3) const {
	// Вычисление количества "амогусов"
	int amogus_count = (d2 == 'D') + (d3 == 'D');

	// Получение результата из матрицы
	return matrixReader.getResult(d1, amogus_count);
}

std::vector<int> GameMatrix::calculate_scores(const Choices &choices) const {
	if (choices.size() != 3) {
		throw std::invalid_argument("Решения должны быть предоставлены для трёх участников");
	}

	return {
		getScore(choices[0], choices[1], choices[2]),
		getScore(choices[1], choices[2], choices[0]),
		getScore(choices[2], choices[0], choices[1])
	};
}


