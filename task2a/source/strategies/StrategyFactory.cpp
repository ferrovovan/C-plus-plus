#include "StrategyFactory.hpp"
#include <stdexcept>

/* Тривиальные стратегии */
#include "concrete/AlwaysCooperate.cpp"
#include "concrete/AlwaysDefect.cpp"
#include "concrete/Eye4eye.cpp"
#include "concrete/RandomChoice.cpp"

/* Нетривиальные стратегии */
#include "concrete/AdaptiveCooperator/AdaptiveCooperator.hpp"


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

// Создание стратегии с параметрами
std::unique_ptr<Strategy> StrategyFactory::create(const std::string& name, const std::string& config_path) {
	auto& creators = getCreators();
	auto it = creators.find(name);
	if (it == creators.end()) {
		throw std::runtime_error("Strategy not found: " + name);
	}
	// Передаем путь конфигурации в создание стратегии
	return it->second(config_path); // Передаем конфиг в creator
}

// Регистрация стратегий
namespace {  // Анонимное пространство имён
	bool registerStrategies() {
		StrategyFactory::registerStrategy("AlwaysCooperate", [](const std::string& config_path) {
			return std::make_unique<AlwaysCooperate>();
		});
		StrategyFactory::registerStrategy("AlwaysDefect", [](const std::string& config_path) {
			return std::make_unique<AlwaysDefect>();
		});
		StrategyFactory::registerStrategy("Eye4Eye", [](const std::string& config_path) {
			return std::make_unique<Eye4Eye>();
		});
		StrategyFactory::registerStrategy("RandomChoice", [](const std::string& config_path) {
			return std::make_unique<RandomChoice>();
		});
		StrategyFactory::registerStrategy("AdaptiveCooperator", [](const std::string& config_path) {
			return std::make_unique<AdaptiveCooperator>(config_path);  // Передача config_path
		});
		return true;
	}

	const bool registered = registerStrategies();
}

