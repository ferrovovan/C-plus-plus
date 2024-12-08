#ifndef ALWAYSDEFECT_H
#define ALWAYSDEFECT_H

#include "../Strategy.hpp"

class AlwaysDefect : public Strategy {
public:
	Decision decide(const ChoiceHistory &history) override {
		(void)history;  // Оповещаем компилятор, что параметр явно не используется
		return 'D';
	}
};

#endif

