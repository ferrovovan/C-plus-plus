#pragma once

#include "Strategy.hpp"
#include <vector>
#include <memory> // std::move
#include <string>

using Strategies_vector = std::vector<std::unique_ptr<Strategy>>;
using StrategyNames = std::vector<std::string>;

class MetaStrategy : public Strategy {
public:
	explicit MetaStrategy(const std::string& strategy_name, Strategies_vector* subStrategies)
	: Strategy(strategy_name) {
		// Перемещение элементов из subStrategies в subStrategies текущего объекта
		for (std::unique_ptr<Strategy>& strategy : *subStrategies) {
		this->subStrategies.push_back(std::move(strategy));
		}
	}

	Decision decide(const ChoiceHistory& history);

protected:
	Strategies_vector subStrategies;
	// Метод для получения имён стратегий
	StrategyNames get_names() const {
		StrategyNames names;
		for (const auto& strategy : subStrategies) {
			names.push_back(strategy->get_name());
		}
		return names;
	}
};
