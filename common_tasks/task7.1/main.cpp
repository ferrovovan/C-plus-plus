#include "Time.hpp"
#include "SimpleWatch.hpp"
#include "Watch.hpp"

int main() {
	Time time(10, 30, 45);

	// Используем SimpleWatch
	SimpleWatch simpleWatch; // Получение экземпляра
	simpleWatch.showTime(time);
	simpleWatch.setTime(time, 14, 0, 0);
	simpleWatch.showTime(time);
	simpleWatch.setFormat(false);
	simpleWatch.showTime(time);

	// Используем Watch
	Watch watch;  // Создание экземпляра для инициализации is24HourFormat
	watch.showTime(time);
	watch.setTime(time, 18, 15, 30);
	watch.showTime(time);
	// Меняем формат на 12-часовой
	watch.setFormat(false);
	watch.showTime(time);
	simpleWatch.showTime(time);

	return 0;
}

