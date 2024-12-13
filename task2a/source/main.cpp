#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <filesystem>

#include "utils/CommandLineParser.hpp"
#include "Simulation/Simulation.hpp"
#include "strategies/StrategyFactory.hpp"
#include "GameMatrix/GameMatrix.hpp"
#include "History/History.hpp"

void print_args(const SimulationParams *params) {
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

int main(int argc, char* argv[]) {
	try {
		// Обрабатываем аргументы командной строки и получаем параметры симуляции
		SimulationParams params = CommandLineParser::parse(argc, argv);

		// Выводим параметры симуляции
		print_args(&params);

		// Создаём стратегии через фабрику
		std::vector<std::unique_ptr<Strategy>> strategies;
		for (const auto& strategy_name : params.strategies) {
			std::string config_path = params.configDir + "/" + strategy_name + ".conf";
			if (!std::filesystem::exists(config_path)) {} // заглушка
			strategies.push_back(StrategyFactory::create(strategy_name));
		}

		// Создаём объект симуляции
		Simulation simulation(std::move(strategies), params.matrixFile, params.steps);

		// Запускаем симуляцию в выбранном режиме
		if (params.mode == "detailed") {
			simulation.run_detailed_mode();
		} else if (params.mode == "fast") {
			simulation.run_fast_mode();
		} else if (params.mode == "tournament") {
			simulation.run_tournament();
		} else {
			throw std::invalid_argument("Неизвестный режим симуляции: " + params.mode);
		}

	} catch (const std::exception& ex) {
		std::cerr << "Ошибка: " << ex.what() << std::endl;
		return 1;
	}

	return 0;
}

