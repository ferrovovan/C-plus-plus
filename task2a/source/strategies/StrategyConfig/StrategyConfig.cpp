#include "StrategyConfig.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

StrategyConfig::StrategyConfig(const std::string& config_path) {
	std::ifstream file(config_path);
	if (!file.is_open()) {
		throw std::runtime_error("Не удалось открыть конфигурационный файл: " + config_path);
	}

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream stream(line);
		std::string key;
		double value;

		if (std::getline(stream, key, '=') && stream >> value) {
			config[key] = value;
		}
	}
}

double StrategyConfig::get(const std::string& key, double default_value) const {
	auto it = config.find(key);
	return it != config.end() ? it->second : default_value;
}

