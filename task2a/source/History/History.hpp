#ifndef HISTORY_HPP
#define HISTORY_HPP

#include "../types.hpp"
#include <vector>
#include <string>

using Names_vector = std::vector<std::string>;

class History {
private:
	ChoiceHistory choiceHistory; // Хранение истории решений по раундам
	Names_vector strategyNames;
public:
	// Конструкторы
	explicit History(const Names_vector& strategyNames);
	explicit History(
		const Names_vector& strategyNames,
		const ChoiceHistory& initialHistory
	);

	// Добавить результаты нового раунда
	void add_round(const Choices& choices);

	// Получить всю историю
	const ChoiceHistory& get_history() const;
	//
	const Choices& get_last_moves() const;
	// Только для оппонентов
	ChoiceHistory get_oponents_moves(const std::string& strategyName) const;

	// Вывести историю (для отладки)
	void print() const;
};

#endif // HISTORY_HPP
