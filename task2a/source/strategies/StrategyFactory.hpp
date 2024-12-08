#ifndef STRATEGYFACTORY_HPP
#define STRATEGYFACTORY_HPP

#include "Strategy.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <functional>

class StrategyFactory {
public:
	using StrategyCreator = std::function<std::unique_ptr<Strategy>()>;

	// Регистрация стратегии
	static void registerStrategy(const std::string& name, StrategyCreator creator);

	// Создание стратегии
	static std::unique_ptr<Strategy> create(const std::string& name);

private:
	// Словарь для хранения зарегистрированных стратегий
	static std::unordered_map<std::string, StrategyCreator>& getCreators();
};

#endif
