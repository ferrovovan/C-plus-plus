#include "Time.h"

int Time::object_count = 0;

Time::Time() { // Default Constructor
	std::cout << "Default Constructor called. Current object count: " << object_count << "\n";
	hours = 0; minutes = 0; seconds = 0;
	++object_count;
}

Time::Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {
	std::cout << "Constructor called. Current object count: " << object_count << "\n";
	Normalize();  // Нормализация времени после инициализации
	++object_count;
}

Time(const Time& other) { // Copy Constructor
	std::cout << "Copy Constructor called. Current object count: " << object_count << "\n";
	this->seconds = other->seconds;
	this->minutes = other->minutes;
	this->hours = other->hours;
	++object_count;
}

Time::~Time() { // Destructor
	std::cout << "Destructor called. Current object count: " << object_count << "\n";
	--object_count;
}

void Time::Normalize() {
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

// Операторы сложения
Time operator + (const Time& t, int s) {  // вариант "внешняя функция"
	return Time(t.GetHours(), t.GetMinutes(), t.GetSeconds() + s);
}
	
Time operator + (int s, const Time& t) {  // вариант "внешняя функция"
	return Time(t.GetHours(), t.GetMinutes(), t.GetSeconds() + s);
}

// Операторы вычитания
Time operator - (int s, const Time& t) {  // вариант "внешняя функция"
	return Time(t.GetHours(), t.GetMinutes(), t.GetSeconds() - s);
}

Time operator - (const Time& t, int s) {  // вариант "внешняя функция"
	return Time(t.GetHours(), t.GetMinutes(), t.GetSeconds() - s);
}
