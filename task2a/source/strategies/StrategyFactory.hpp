#ifndef STRATEGYFACTORY_HPP
#define STRATEGYFACTORY_HPP

#include "Strategy.hpp"
#include "MetaStrategy.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <functional>

class StrategyFactory {
public:
	using StrategyCreator = std::function<std::unique_ptr<Strategy>(const std::string&)>;

	// Регистрация стратегии
	static void registerStrategy(const std::string& name, StrategyCreator creator);

	// Создание стратегии
	static std::unique_ptr<Strategy> create(const std::string& name, const std::string& config_path);

private:
	// Словарь для хранения зарегистрированных стратегий
	static std::unordered_map<std::string, StrategyCreator>& getCreators();
};

#endif
