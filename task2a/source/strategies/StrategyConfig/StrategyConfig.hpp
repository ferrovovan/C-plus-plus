#ifndef STRATEGYCONFIG_HPP
#define STRATEGYCONFIG_HPP

#include <string>
#include <unordered_map>
#include <fstream>

class StrategyConfig {
private:
	std::unordered_map<std::string, double> config; // Хранение параметров
	void parse_file(std::ifstream& file);

public:
	explicit StrategyConfig(const std::string& config_path);
	double get(const std::string& key, double default_value = 0.0) const; // Получить параметр
};

#endif // STRATEGYCONFIG_HPP
