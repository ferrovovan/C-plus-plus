#ifndef EYE4EYE_H
#define EYE4EYE_H

#include "../Strategy.hpp"
#include <algorithm>

class Eye4Eye : public Strategy {
public:
    Eye4Eye() : Strategy("Eye4Eye") {}
	Decision decide(const ChoiceHistory &history) override {
		(void)history;  // Оповещаем компилятор, что параметр явно не используется)
		if (history.empty()) {
			return 'C';  // Если история пуста, кооперируем
		}

		const Choices& last_choice = history.back();  // Получаем последний раунд
		int betrayals = std::count(last_choice.begin(), last_choice.end(), 'D');  // Считаем предателей в последнем раунде

		if (betrayals == 2) return 'D';  // Если предателей два, предаем
		return 'C';  // В остальных случаях кооперируем
	}
};

#endif

