#include "Time.hpp"

int Time::object_count = 0;

Time::Time() noexcept {
	hours = 0; minutes = 0; seconds = 0;
	++object_count;
	std::cout << "Constructor called. Current object count: " << object_count << "\n";
}
Time::Time(int h, int m, int s) noexcept : hours(h), minutes(m), seconds(s) {
	++object_count;
	Normalize();  // Нормализация времени после инициализации
	std::cout << "Constructor called. Current object count: " << object_count << "\n";
}

Time::~Time() noexcept {
	--object_count;
	std::cout << "Destructor called. Current object count: " << object_count << "\n";
}

void Time::Normalize() noexcept {
	if (seconds < 0) {
		minutes -= (-seconds + 59) / 60;
		seconds = (seconds % 60 + 60) % 60;
	} else {
		minutes += seconds / 60;
		seconds %= 60;
	}

	if (minutes < 0) {
		hours -= (-minutes + 59) / 60;
		minutes = (minutes % 60 + 60) % 60;
	} else {
		hours += minutes / 60;
		minutes %= 60;
	}

	hours = (hours % 24 + 24) % 24;
}

// Приведение в секунды
int Time::ToSeconds() const noexcept {
	return hours * 3600 + minutes * 60 + seconds;
}
// Присваивание часов
void Time::SetHours(int hours) {
	if (hours < 0)
		throw std::invalid_argument("Hours cannot be negative");
	else if (hours > 23)
		throw std::invalid_argument("Hours cannot be more than 23");
	this->hours = hours;
}

// Операторы сложения
inline Time operator + (const Time& t, int s) noexcept {  // вариант "внешняя функция"
	return Time(t.GetHours(), t.GetMinutes(), t.GetSeconds() + s);
}
	
inline Time operator + (int s, const Time& t) noexcept {  // вариант "внешняя функция"
	return Time(t.GetHours(), t.GetMinutes(), t.GetSeconds() + s);
}

// Операторы вычитания
inline Time operator - (int s, const Time& t) noexcept {  // вариант "внешняя функция"
	return Time(t.GetHours(), t.GetMinutes(), t.GetSeconds() - s);
}

inline Time operator - (const Time& t, int s) noexcept {  // вариант "внешняя функция"
	return Time(t.GetHours(), t.GetMinutes(), t.GetSeconds() - s);
}

