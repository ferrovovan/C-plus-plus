#ifndef SIMULATIONPARAMS_HPP
#define SIMULATIONPARAMS_HPP

#include <string>
#include <vector>

struct SimulationParams {
	std::vector<std::string> strategies; // Список стратегий
	std::string mode;       // Режим симуляции (по умолчанию — detailed)
	int steps;                     // Количество шагов (по умолчанию — 100)
	std::string configDir;               // Директория с конфигурационными файлами стратегий
	std::string matrixFile;             // Файл с матрицей игры
};

#endif // SIMULATIONPARAMS_HPP
