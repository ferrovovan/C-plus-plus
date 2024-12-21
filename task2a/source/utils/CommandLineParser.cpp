#include "CommandLineParser.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <filesystem>

SimulationParams CommandLineParser::parse(int argc, char* argv[]) {
	SimulationParams params;

	// Разбор аргументов командной строки
	auto args = parseArguments(argc, argv);
	// auto = ArgsMap

	// Обработка каждого параметра
	if (args.count("strategies")) {
		parse_Strategies(args.at("strategies"), params);
	}
	validateStrategies(params);

	if (args.count("--mode"))
		parse_Mode(args, params);
	else {
		if (params.strategies.size() > 3) {  // Умолчание для большого количества стратегий
			params.mode = "tournament";
		}
		else params.mode = "detailed";
	}

	if (args.count("--steps"))
		parse_Steps(args, params);
	else
		params.steps = 20;

	if (args.count("--configs"))
		parse_ConfigDir(args, params);
	else
		params.configDir = "";

	if (args.count("--matrix"))
		parse_MatrixFile(args, params);
	else
		params.matrixFile = "";

	return params;
}

ArgsMap CommandLineParser::parseArguments(int argc, char* argv[])   {
	ArgsMap args;

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
		throw std::invalid_argument("Недостаточно стратегий. Укажите минимум три.");
	}
}

void CommandLineParser::parse_Mode(const ArgsMap& args, SimulationParams& params)   {
	params.mode = args.at("--mode");
	if (params.mode != "detailed" && params.mode != "fast" && params.mode != "tournament") {
		std::cerr << "Ошибка: режим симуляции должен быть одним из [detailed|fast|tournament]." << std::endl;
		throw std::invalid_argument("mode choice error");
	}
	if (params.mode == "tournament" and params.strategies.size() < 4) {
		throw std::invalid_argument("Ошибка: при выборе \"tournament\". Должно быть больше 3 стратегий.");
	}
	if (params.mode != "tournament" and params.strategies.size() != 3) {
		throw std::invalid_argument("Ошибка: при выборе \"" + params.mode + "\". Должно быть ровно 3 стратегий.");
	}
}

void CommandLineParser::debug_args(const ArgsMap& args) {
	for (const auto& arg : args) {
		std::cout << "Arg: " << arg.first << " Value: " << arg.second << std::endl;
	}
}

void CommandLineParser::parse_Steps(const ArgsMap& args, SimulationParams& params)
{
	params.steps = std::stoi(args.at("--steps"));
	if (params.steps <= 0) {
		throw std::invalid_argument("Ошибка: количество шагов должно быть положительным числом.");
	}
}

void CommandLineParser::parse_ConfigDir(const ArgsMap& args, SimulationParams& params)   {
	params.configDir = args.at("--configs");
	if (!std::filesystem::is_directory(params.configDir)) {
		throw std::invalid_argument("Ошибка: указанная директория конфигурации не существует.");
	}
}

void CommandLineParser::parse_MatrixFile(const ArgsMap& args, SimulationParams& params)   {
	params.matrixFile = args.at("--matrix");
	if (!std::filesystem::exists(params.matrixFile)) {
		throw std::invalid_argument("Ошибка: указанный файл матрицы не найден.");
	}
}

