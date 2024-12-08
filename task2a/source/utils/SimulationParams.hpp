#ifndef SIMULATIONPARAMS_HPP
#define SIMULATIONPARAMS_HPP

#include <string>
#include <vector>
#include <iostream>

struct SimulationParams {
	std::vector<std::string> strategies; // Список стратегий
	std::string mode = "detailed";       // Режим симуляции (по умолчанию — detailed)
	int steps = 100;                     // Количество шагов (по умолчанию — 100)
	std::string configDir;               // Директория с конфигурационными файлами стратегий
	std::string matrixFile;             // Файл с матрицей игры
};

/*
void print_SimulationParams(const SimulationParams &params) {
	std::cout << "Simulation Parameters:" << std::endl;
	std::cout << "  Strategies: ";
	for (const auto& strategy : params.strategies) {
		std::cout << strategy << " ";
	}
	std::cout << std::endl;
	std::cout << "  Mode: " << params.mode << std::endl;
	std::cout << "  Steps: " << params.steps << std::endl;
	if (!params.configDir.empty()) {
		std::cout << "  Config Directory: " << params.configDir << std::endl;
	}
	if (!params.matrixFile.empty()) {
		std::cout << "  Matrix File: " << params.matrixFile << std::endl;
	}
}
*/
#endif // SIMULATIONPARAMS_HPP
