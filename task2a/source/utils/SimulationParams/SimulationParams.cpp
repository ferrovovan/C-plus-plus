#include "SimulationParams.hpp"
#include <iostream>

inline void print_args(const SimulationParams* params) {
	std::cout << "Параметры симуляции:" << std::endl;
	std::cout << "Стратегии: ";
	for (const auto& strategy : params->strategies) {
		std::cout << strategy << " ";
	}
	std::cout << "\nРежим симуляции: " << params->mode
	          << "\nЧисло шагов: " << params->steps
	          << "\nДиректория конфигурации: " << params->configDir
	          << "\nФайл матрицы: " << (params->matrixFile.empty() ? "не указан" : params->matrixFile)
	          << std::endl;
	std::cout << std::endl;
}
