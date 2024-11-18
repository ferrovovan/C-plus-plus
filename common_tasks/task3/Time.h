#include <iostream>

class Time {
private:
	int hours, minutes, seconds;
public:
	Time(){}; // конструктор изначальный
	Time(int h, int m, int s); // перегрузка конструктора
	//Time(const Time&); // конструктор копирования

	// приём "делегирование конструктора" для конструктора копирования.
	Time(const Time& t): Time(t.hours, t.minutes, t.seconds){}
	~Time(){} // деструктор

	Time& operator = (const Time& other){
		this->hours = other.hours; // явное указания на член класса
		minutes = other.minutes;   // неявное указание
		seconds = other.seconds;
		return *this;
	}

	Time& operator += (int s) {
		seconds += s;
		Normalize();
		return *this;
	}

	Time& operator += (const Time& other) {
		hours += other.hours;
		minutes += other.minutes;
		seconds += other.seconds;
		Normalize();
		return *this;
	}

	
	// Оператор вычитания
	Time operator - (const Time& other) const {
		Time result(hours - other.hours, minutes - other.minutes, seconds - other.seconds);
		result.Normalize();
		return result;
	}

	// Оператор вычитания с присваиванием
	Time& operator -= (int s) {
		seconds -= s;
		Normalize();
		return *this;
	}
	// Оператор сравнения
	bool operator==(const Time& other) const {
		return hours == other.hours && minutes == other.minutes && seconds == other.seconds;
	}


	int GetHours() const { return hours; }
	int GetMinutes() const { return minutes; }
	int GetSeconds() const { return seconds; }

	void Normalize();
	int ToSeconds() const;
	void PrintTime(){
		std::cout << "H:" << this->GetHours()
			<< " M:" << this->GetMinutes()
			<< " S:" << this->GetSeconds()
			<< std::endl;
	}
};

