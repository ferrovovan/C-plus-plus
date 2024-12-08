#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include "../types.hpp"

class Strategy {
public:
	virtual Decision decide(const ChoiceHistory &history) = 0;
	void load_config(const std::string &config_path);
};

#endif
