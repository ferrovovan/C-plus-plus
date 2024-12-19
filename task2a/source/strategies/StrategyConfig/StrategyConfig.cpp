#include "StrategyConfig.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

void StrategyConfig::parse_file(std::ifstream& file) {
	std::string line;

	while (std::getline(file, line)) {
		// Убираем пробелы в начале и конце строки.
		line.erase(0, line.find_first_not_of(" \t"));
		line.erase(line.find_last_not_of(" \t") + 1);

		// Пропускаем пустые строки и строки с комментариями.
		if (line.empty() || line[0] == '#') {
			continue;
		}

		size_t delimiter_pos = line.find('=');
		if (delimiter_pos == std::string::npos) {
			continue; // Игнорируем строки без символа '='.
		}

		std::string key = line.substr(0, delimiter_pos);
		std::string value = line.substr(delimiter_pos + 1);

		// Убираем пробелы вокруг ключа и значения.
		key.erase(0, key.find_first_not_of(" \t"));
		key.erase(key.find_last_not_of(" \t") + 1);

		value.erase(0, value.find_first_not_of(" \t"));
		value.erase(value.find_last_not_of(" \t") + 1);

		try {
			// Преобразуем значение в double.
			config[key] = std::stod(value);
		} catch (const std::invalid_argument&) {
			throw std::runtime_error("Некорректное значение для ключа: " + key);
		} catch (const std::out_of_range&) {
			throw std::runtime_error("Значение ключа вне допустимого диапазона: " + key);
		}
	}
}

StrategyConfig::StrategyConfig(const std::string& config_path) {
	std::ifstream file(config_path);
	if (!file.is_open()) {
		std::cout << ("Не удалось открыть файл конфигурации.\n");
	} else {
		parse_file(file);
	}
}

double StrategyConfig::get(const std::string& key, double default_value) const {
	auto it = config.find(key);
	return it != config.end() ? it->second : default_value;
}

