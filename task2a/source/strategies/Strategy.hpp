#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include "../types.hpp"
#include <string>

class Strategy {
private:
	std::string name; // Имя стратегии защищено от прямого доступа
protected:
	explicit Strategy(const std::string& strategy_name) : name(strategy_name) {}
public:
	virtual Decision decide(const ChoiceHistory& history) = 0;
	std::string get_name() const { return name; }
	//void load_config(const std::string& config_path);

	// Оператор присваивания
	Strategy& operator=(const Strategy& other) {
		if (this == &other) return *this; // защита от самоприсваивания
		this->name = other.name;// Здесь происходит копирование данных
		return *this;
	}
};

#endif
