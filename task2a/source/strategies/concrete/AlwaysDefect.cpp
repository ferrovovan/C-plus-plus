#ifndef ALWAYSDEFECT_HPP
#define ALWAYSDEFECT_HPP

#include "../Strategy.hpp"

class AlwaysDefect : public Strategy {
public:
	AlwaysDefect() : Strategy("AlwaysDefect") {}
	Decision decide(const ChoiceHistory& history) override {
		(void)history;  // Параметр не используется
		return 'D';
	}
};

#endif

