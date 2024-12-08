#include "CommandLineParser.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <filesystem>

SimulationParams CommandLineParser::parse(int argc, char* argv[]) {
	SimulationParams params;

	// Разбор аргументов командной строки
	auto args = parseArguments(argc, argv);
	// auto = std::map<std::string, std::string>

	// Обработка каждого параметра
	if (args.count("strategies")) {
		parse_Strategies(args.at("strategies"), params);
	}
	validateStrategies(params);

	if (args.count("--mode")) {
		parse_Mode(args, params);
	} else if (params.strategies.size() > 3) {
		params.mode = "tournament"; // Умолчание для большого количества стратегий
	}

	if (args.count("--steps")) {
		parse_Steps(args, params);
	}

	if (args.count("--configs")) {
		parse_ConfigDir(args, params);
	}

	if (args.count("--matrix")) {
		parse_MatrixFile(args, params);
	}

	return params;
}

std::map<std::string, std::string> CommandLineParser::parseArguments(int argc, char* argv[])   {
	std::map<std::string, std::string> args;

	for (int i = 1; i < argc; ++i) {
		std::string arg = argv[i];
		if (arg.rfind("--", 0) == 0) { // длинный параметр
			size_t pos = arg.find('=');
			if (pos != std::string::npos) {
				std::string key = arg.substr(0, pos);
				std::string value = arg.substr(pos + 1);
				args[key] = value;
			} else {
				args[arg] = ""; // Аргумент без значения
			}
		} else {
			args["strategies"].append(arg + " ");
		}
	}

	return args;
}

void CommandLineParser::parse_Strategies(const std::string& strategiesStr, SimulationParams& params)   {
	std::istringstream iss(strategiesStr);
	for (std::string strategy; iss >> strategy;) {
		params.strategies.push_back(strategy);
	}
}

void CommandLineParser::validateStrategies(const SimulationParams& params)   {
	if (params.strategies.size() < 3) {
		std::cerr << "Ошибка: недостаточно стратегий. Укажите минимум три." << std::endl;
		exit(1);
	}
}

void CommandLineParser::parse_Mode(const std::map<std::string, std::string>& args, SimulationParams& params)   {
	params.mode = args.at("--mode");
	if (params.mode != "detailed" && params.mode != "fast" && params.mode != "tournament") {
		std::cerr << "Ошибка: режим симуляции должен быть одним из [detailed|fast|tournament]." << std::endl;
		exit(1);
	}
}

void CommandLineParser::parse_Steps(const std::map<std::string, std::string>& args, SimulationParams& params)   {
	params.steps = std::stoi(args.at("--steps"));
	if (params.steps <= 0) {
		std::cerr << "Ошибка: количество шагов должно быть положительным числом." << std::endl;
		exit(1);
	}
}

void CommandLineParser::parse_ConfigDir(const std::map<std::string, std::string>& args, SimulationParams& params)   {
	params.configDir = args.at("--configs");
	if (!std::filesystem::is_directory(params.configDir)) {
		std::cerr << "Ошибка: указанная директория конфигурации не существует." << std::endl;
		exit(1);
	}
}

void CommandLineParser::parse_MatrixFile(const std::map<std::string, std::string>& args, SimulationParams& params)   {
	params.matrixFile = args.at("--matrix");
	if (!std::filesystem::exists(params.matrixFile)) {
		std::cerr << "Ошибка: указанный файл матрицы не найден." << std::endl;
		exit(1);
	}
}

