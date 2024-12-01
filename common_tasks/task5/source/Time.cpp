#include "Time.hpp"

int Time::object_count = 0;

Time::Time() { // Default Constructor
	++object_count;
	std::cout << "Default Constructor called. Current object count: " << object_count << "\n";
	hours = 0; minutes = 0; seconds = 0;
}

Time::Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {
	++object_count;
	std::cout << "Constructor called. Current object count: " << object_count << "\n";
	Normalize();  // Нормализация времени после инициализации
}

Time::Time(const Time& other) { // Copy Constructor
	++object_count;
	std::cout << "Copy Constructor called. Current object count: " << object_count << "\n";
	this->seconds = other.seconds;
	this->minutes = other.minutes;
	this->hours = other.hours;
}

Time::~Time() { // Destructor
	--object_count;
	std::cout << "Destructor called. Current object count: " << object_count << "\n";
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

/*  Операторы  */
// Операторы сложения
Time operator + (const Time& t, int s) {  // вариант "внешняя функция"
	return Time(t.GetHours(), t.GetMinutes(), t.GetSeconds() + s);
}
	
Time operator + (int s, const Time& t) {  // вариант "внешняя функция"
	return Time(t.GetHours(), t.GetMinutes(), t.GetSeconds() + s);
}

Time Time::operator + (int s) const {
	return Time(this->hours, this->minutes, this->seconds + s);
}
Time Time::operator + (const Time& other) const {
	Time result(hours + other.hours, minutes + other.minutes, seconds + other.seconds);
	result.Normalize(); // Нормализация результата
	return result;
}


// Операторы вычитания
Time operator - (const Time& t, int s) {  // вариант "внешняя функция"
	return Time(t.GetHours(), t.GetMinutes(), t.GetSeconds() - s);
}

Time operator - (int s, const Time& t) {  // вариант "внешняя функция"
	return Time(t.GetHours(), t.GetMinutes(), t.GetSeconds() - s);
}

Time Time::operator - (int s) const {
	return Time(this->hours, this->minutes, this->seconds - s);
}
Time Time::operator - (const Time& other) const {
	Time result(hours - other.hours, minutes - other.minutes, seconds - other.seconds);
	result.Normalize(); // Нормализация результата
	return result;
}


