#ifndef RANDOMCHOICE_HPP
#define RANDOMCHOICE_HPP

#include "../Strategy.hpp"
#include <cstdlib>  // Для std::rand
#include <ctime>    // Для std::time

class RandomChoice : public Strategy {
public:
	RandomChoice() {  // Конструктор
		std::srand(std::time(nullptr));  // Инициализация генератора случайных чисел
	}

	Decision decide(const ChoiceHistory &history) override {
		(void)history;  // Оповещаем компилятор, что параметр явно не используется)
		return (std::rand() % 2 == 0) ? 'C' : 'D';
	}
};

#endif

