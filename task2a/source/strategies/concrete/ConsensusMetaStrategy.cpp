#ifndef CONSENSUSMETASTRATEGY_CPP
#define CONSENSUSMETASTRATEGY_CPP

#include "../MetaStrategy.hpp"
/* Тривиальные стратегии */
#include "AlwaysCooperate.cpp"
#include "AlwaysDefect.cpp"
#include "Eye4eye.cpp"
#include "RandomChoice.cpp"

/* Нетривиальные стратегии */
#include "AdaptiveCooperator/AdaptiveCooperator.hpp"

#include <unordered_map>

class ConsensusMetaStrategy : public MetaStrategy {
public:
	explicit ConsensusMetaStrategy(/*Strategies_vector* subStrategies*/)
		: MetaStrategy("ConsensusMetaStrategy")
	{
		subStrategies.push_back(std::make_unique<AlwaysCooperate>());
		subStrategies.push_back(std::make_unique<AlwaysDefect>());
		subStrategies.push_back(std::make_unique<Eye4Eye>());
		subStrategies.push_back(std::make_unique<RandomChoice>());
		subStrategies.push_back(std::make_unique<AdaptiveCooperator>(""));
	}

	Decision decide(const ChoiceHistory& history) override {
		std::unordered_map<Decision, int> voteCount{{'C', 0}, {'D', 0}};

		// Сбор голосов от подстратегий
		for (const auto& strategy : subStrategies) {
			Decision decision = strategy->decide(history);
			voteCount[decision]++;
		}

		// Решение по большинству голосов
		return (voteCount['C'] >= voteCount['D']) ? 'C' : 'D';
	}
};

#endif // CONSENSUSMETASTRATEGY_CPP

