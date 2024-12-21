#pragma once

#include "Strategy.hpp"
#include <vector>
#include <memory> // std::move
#include <string>

using Strategies_vector = std::vector<std::unique_ptr<Strategy>>;
using StrategyNames = std::vector<std::string>;

class MetaStrategy : public Strategy {
public:
	virtual ~MetaStrategy() = default;
	explicit MetaStrategy(const std::string& strategy_name)
	: Strategy(strategy_name) {};

	virtual Decision decide(const ChoiceHistory& history) = 0;

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
