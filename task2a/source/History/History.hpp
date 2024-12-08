#ifndef HISTORY_HPP
#define HISTORY_HPP

#include "../types.hpp"
#include <vector>

class History {
private:
	ChoiceHistory choiceHistory; // Хранение истории решений по раундам
public:
	// Конструкторы
	History() = default;
	explicit History(const ChoiceHistory& initialHistory);

	// Добавить результаты нового раунда
	void add_round(const Choices& choices);

	// Получить всю историю
	const ChoiceHistory& get_history() const;

	// Вывести историю (для отладки)
	void print() const;
};

#endif // HISTORY_HPP
