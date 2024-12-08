#include "StrategyFactory.hpp"

/* Тривиальные стратегии */
#include "concrete/AlwaysCooperate.cpp"
#include "concrete/AlwaysDefect.cpp"
#include "concrete/Eye4eye.cpp"
#include "concrete/RandomChoice.cpp"

/* Нетривиальные стратегии */
// #include "concrete/???.hpp"

#include <stdexcept>

// Получение словаря зарегистрированных стратегий
std::unordered_map<std::string, StrategyFactory::StrategyCreator>& StrategyFactory::getCreators() {
	static std::unordered_map<std::string, StrategyCreator> creators;
	return creators;
}

// Регистрация стратегии
void StrategyFactory::registerStrategy(const std::string& name, StrategyCreator creator) {
	auto& creators = getCreators();
	creators[name] = std::move(creator);
}

// Создание стратегии
std::unique_ptr<Strategy> StrategyFactory::create(const std::string& name) {
	auto& creators = getCreators();
	auto it = creators.find(name);
	if (it == creators.end()) {
		throw std::runtime_error("Strategy not found: " + name);
	}
	return it->second();
}

// Регистрация стратегий
namespace {  // Анонимное пространство имён
	bool registerStrategies() {
		StrategyFactory::registerStrategy("AlwaysCooperate", []() { return std::make_unique<AlwaysCooperate>(); });
		StrategyFactory::registerStrategy("AlwaysDefect", []() { return std::make_unique<AlwaysDefect>(); });
		StrategyFactory::registerStrategy("Eye4Eye", []() { return std::make_unique<Eye4Eye>(); });
		StrategyFactory::registerStrategy("RandomChoice", []() { return std::make_unique<RandomChoice>(); });
		return true;
	}

	const bool registered = registerStrategies();
}

