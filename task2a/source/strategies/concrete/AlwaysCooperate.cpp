#ifndef ALWAYSCOOPERATE_HPP
#define ALWAYSCOOPERATE_HPP

#include "../Strategy.hpp"

class AlwaysCooperate : public Strategy {
public:
	Decision decide(const ChoiceHistory &history) override {
		(void)history;  // Оповещаем компилятор, что параметр явно не используется
		return 'C';
	}
};

#endif

