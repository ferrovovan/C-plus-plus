#ifndef SIMPLEWATCH_HPP
#define SIMPLEWATCH_HPP

class Time; // forward declaration

class SimpleWatch {
private:
	bool is24HourFormat = true;
public:
	void setFormat(bool format) { is24HourFormat = format; }

	void showTime(const Time& time);
	void setTime(Time& time, int h, int m, int s);
};

#endif // SIMPLEWATCH_HPP

