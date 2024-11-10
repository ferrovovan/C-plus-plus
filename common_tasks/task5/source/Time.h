#include <iostream>

class Time {
private:
	int hours, minutes, seconds;
	static int object_count;
public:
	Time();
	Time(int h, int m, int s);
	Time(const Time& t): Time(t.hours, t.minutes, t.seconds){}
	~Time();

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
	Time operator + (int s) const;

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

	static int GetObjectCount() {
		return object_count;
	}

	void Normalize();
	int ToSeconds() const;
	void SetHours(int hours);
	void PrintTime(){
		std::cout << "H:" << this->GetHours()
			<< " M:" << this->GetMinutes()
			<< " S:" << this->GetSeconds()
			<< std::endl;
	}
};

