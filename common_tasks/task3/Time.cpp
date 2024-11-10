#include "Time.h"

Time::Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {
	Normalize();  // Нормализация времени после инициализации
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

// Приведение в секунды
int Time::ToSeconds() const {
	return hours * 3600 + minutes * 60 + seconds;
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
