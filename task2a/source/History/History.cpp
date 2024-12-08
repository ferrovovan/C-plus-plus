#include "History.hpp"
#include <iostream>

// Конструктор с начальной историей
History::History(const std::vector<Choices>& initialHistory) 
	: choiceHistory(initialHistory) {}

// Добавить результаты нового раунда
void History::add_round(const Choices& choices) {
	if (choices.size() != 3) {
		throw std::invalid_argument("Каждый раунд должен содержать ровно 3 решения.");
	}
	choiceHistory.push_back(choices);
}

// Получить всю историю
const std::vector<Choices>& History::get_history() const {
	return choiceHistory;
}

// Вывести историю (для отладки)
void History::print() const {
	for (size_t i = 0; i < choiceHistory.size(); ++i) {
		std::cout << "Раунд " << i + 1 << ": ";
		for (const auto& decision : choiceHistory[i]) {
			std::cout << decision << " ";
		}
		std::cout << std::endl;
	}
}

