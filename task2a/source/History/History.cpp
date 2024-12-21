#include "History.hpp"
#include <iostream>
#include <string>

History::History(const Names_vector& strategyNames)
	: strategyNames(strategyNames) {
	choiceHistory = ChoiceHistory();
}
// Конструктор с начальной историей
History::History(const Names_vector& strategyNames,
	const ChoiceHistory& initialHistory)
	: choiceHistory(initialHistory), strategyNames(strategyNames) {}

// Добавить результаты нового раунда
void History::add_round(const Choices& choices) {
	if (choices.size() != 3) {
		throw std::invalid_argument("Каждый раунд должен содержать ровно 3 решения.");
	}
	choiceHistory.push_back(choices);
}

// Получить всю историю
const ChoiceHistory& History::get_history() const {
	return choiceHistory;
}
const Choices& History::get_last_moves() const {
	if (choiceHistory.empty()) {
		throw std::runtime_error("История пуста. Нет последних ходов.");
	}
	return choiceHistory.back();
}


ChoiceHistory History::get_oponents_moves(
	const std::string& strategyName) const
{/*
	auto it = std::find(strategyNames.cbegin(), strategyNames.cend(), strategyName);
	// std::vector<std::__cxx11::basic_string<char> >::const_iterator it = -1;
	if (it == strategyNames.end()) {
		throw std::invalid_argument("Указанной стратегии нет в списке имён.");
	}
	size_t targetIndex = std::distance(strategyNames.begin(), it);
	*/

	size_t targetIndex = 1;

	// Создаём историю только для оппонентов
	ChoiceHistory opponentsMoves;
	for (const auto& round : choiceHistory) {
		Choices filteredRound;
		for (size_t i = 0; i < round.size(); ++i) {
			if (i != targetIndex) { // Добавляем только ходы оппонентов
				filteredRound.push_back(round[i]);
			}
		}
		opponentsMoves.push_back(filteredRound);
	}

	return opponentsMoves;
}

// Вывести историю (для отладки)
void History::print() const {
	for (std::string strategyName : strategyNames) {
		std::cout << strategyName << " ";
	}
	std::cout << std::endl;

	for (size_t i = 0; i < choiceHistory.size(); ++i) {
		std::cout << "Раунд " << i + 1 << ": ";
		for (const auto& decision : choiceHistory[i]) {
			std::cout << decision << " ";
		}
		std::cout << std::endl;
	}
}

