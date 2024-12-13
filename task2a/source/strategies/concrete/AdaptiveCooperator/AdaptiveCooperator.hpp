#ifndef ADAPTIVECOOPERATOR_HPP
#define ADAPTIVECOOPERATOR_HPP

#include "../../Strategy.hpp"
#include "../../StrategyConfig/StrategyConfig.hpp"

class AdaptiveCooperator : public Strategy {
private:
	double cooperation_threshold; // Порог для сотрудничества
	double betrayal_penalty;      // Штраф за предательство в параметрах
	int history_depth;            // Глубина анализа истории

public:
	explicit AdaptiveCooperator(const std::string& config_path);

	Decision decide(const ChoiceHistory& history) override;
};

#endif // ADAPTIVECOOPERATOR_HPP
