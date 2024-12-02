#ifndef WATCH_HPP
#define WATCH_HPP

class Time; // forward declaration

class Watch {
private:
	bool is24HourFormat = true; // Переменная для формата 12/24
public:
	// Watch(bool format): is24HourFormat(format) {};
	void setFormat(bool format) { is24HourFormat = format; }

	void showTime(const Time& time);
	void setTime(Time& time, int h, int m, int s);
};

#endif // WATCH_HPP

