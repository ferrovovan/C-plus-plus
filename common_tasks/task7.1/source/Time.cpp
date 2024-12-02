#include "Time.hpp"

int Time::object_count = 0;

Time::Time() noexcept { // Default Constructor
	hours = 0; minutes = 0; seconds = 0;
	++object_count;
	std::cout << "Default Constructor called. Current object count: " << object_count << "\n";
}

Time::Time(int h, int m, int s) {
	if (h < 0) {
		throw std::invalid_argument("Часы должны быть в неотрицательными \">0\".");
	}
	if (m < 0) {
		throw std::invalid_argument("Минуты должны быть в неотрицательными \">0\".");
	}
	if (s < 0) {
		throw std::invalid_argument("Секунды должны быть в неотрицательными \">0\".");
	}

	hours = h;
	minutes = m;
	seconds = s;
	Normalize();

	++object_count;
	std::cout << "Constructor called. Current object count: " << object_count << "\n";
}

Time::Time(const Time& other) noexcept { // Copy Constructor
	this->seconds = other.seconds;
	this->minutes = other.minutes;
	this->hours = other.hours;
	++object_count;
	std::cout << "Copy Constructor called. Current object count: " << object_count << "\n";
}

Time::~Time() noexcept{ // Destructor
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

/*  Операторы  */
// Операторы сложения
Time operator + (const Time& t, int s) {  // вариант "внешняя функция"
	if (s < 0) {
		throw std::invalid_argument("Секунды должны быть в неотрицательными \">0\".");
	}
	return Time(t.GetHours(), t.GetMinutes(), t.GetSeconds() + s);
}
	
Time operator + (int s, const Time& t) {  // вариант "внешняя функция"
	if (s < 0) {
		throw std::invalid_argument("Секунды должны быть в неотрицательными \">0\".");
	}
	return Time(t.GetHours(), t.GetMinutes(), t.GetSeconds() + s);
}

Time Time::operator + (int s) const {
	if (s < 0) {
		throw std::invalid_argument("Секунды должны быть в неотрицательными \">0\".");
	}
	return Time(this->hours, this->minutes, this->seconds + s);
}
Time Time::operator + (const Time& other) const noexcept {
	Time result(hours + other.hours, minutes + other.minutes, seconds + other.seconds);
	return result;
}

Time& Time::operator+=(int s) {
	if (s < 0) {
		throw std::invalid_argument("Секунды должны быть неотрицательными.");
	}
	seconds += s;
	Normalize();
	return *this;
}

Time& Time::operator+=(const Time& other) noexcept {
	hours += other.hours;
	minutes += other.minutes;
	seconds += other.seconds;
	Normalize();
	return *this;
}


// Операторы вычитания
Time operator - (const Time& t, int s) {  // вариант "внешняя функция"
	if (s < 0)
		throw std::invalid_argument("Секунды должны быть в неотрицательными \">0\".");
	int result_seconds = t.ToSeconds() - s;
	if (result_seconds < 0)
		throw std::invalid_argument("Из меньшего вычитается большее.");

	return Time(0, 0, result_seconds);
}

Time operator - (int s, const Time& t) {  // вариант "внешняя функция"
	if (s < 0)
		throw std::invalid_argument("Секунды должны быть в неотрицательными \">0\".");
	int result_seconds = s - t.ToSeconds();
	if (result_seconds < 0)
		throw std::invalid_argument("Из меньшего вычитается большее.");

	return Time(0, 0, result_seconds);
}

Time Time::operator - (int s) const {
	if (s < 0)
	      	throw std::invalid_argument("Секунды должны быть в неотрицательными \">0\".");
	int result_seconds = this->ToSeconds() - s;
	if (result_seconds < 0)
		throw std::invalid_argument("Из меньшего вычитается большее.");

	return Time(0, 0, result_seconds);
}
Time Time::operator - (const Time& other) const  {
	int result_seconds = this->ToSeconds() - other.ToSeconds();
	if (result_seconds < 0)
		throw std::invalid_argument("Из меньшего вычитается большее Time.");

	return Time(0, 0, result_seconds);
}

Time& Time::operator -= (int s) {
	if (s < 0) {
		throw std::invalid_argument("Секунды должны быть неотрицательными.");
	}
	int result_seconds = this->ToSeconds() - s;
	if (result_seconds < 0)
		throw std::invalid_argument("Из меньшего вычитается большее.");
	seconds -= s;
	Normalize();
	return *this;
}

Time& Time::operator -= (const Time& other) {
	int result_seconds = this->ToSeconds() - other.ToSeconds();
	if (result_seconds < 0)
		throw std::invalid_argument("Из меньшего вычитается большее Time.");
	this->seconds -= result_seconds;
	this->Normalize();
	return *this;
}

/* Прочие методы */
void Time::SetHours(int hours) {
	if (23 < hours || hours < 0)
		throw std::invalid_argument("Задаваемое значение \"hours\" вне диапазона от 0 до 23.");
	this->hours = hours;
}

void Time::PrintTime() {
	try {
		std::cout.exceptions(std::ostream::failbit | std::ostream::badbit);
		std::cout << "H:" << this->GetHours()
		         << " M:" << this->GetMinutes()
		         << " S:" << this->GetSeconds()
		         << std::endl;
	} catch (const std::ios_base::failure& e) {
		std::cerr << "Output error: " << e.what() << std::endl;
	}
}

