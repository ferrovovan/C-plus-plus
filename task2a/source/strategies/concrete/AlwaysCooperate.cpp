#ifndef ALWAYSCOOPERATE_HPP
#define ALWAYSCOOPERATE_HPP

#include "../Strategy.hpp"

class AlwaysCooperate : public Strategy {
public:
	AlwaysCooperate() : Strategy("AlwaysCooperate") {} // Передаём имя через конструктор базового класса
	Decision decide(const ChoiceHistory& history) override {
		(void)history;  // Параметр не используется
		return 'C';
	}
};

#endif

