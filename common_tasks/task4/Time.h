#include <iostream>

class Time {
private:
	int hours, minutes, seconds;
	static int object_count;
public:
	Time(); // Default Constructor
	Time(int h, int m, int s);
	Time(const Time& t); // Copy Constructor
	~Time(); // Destructor

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

	Time operator + (const Time& other) const { // Оператор сложения
		return Time(hours + other.hours, minutes + other.minutes, seconds + other.seconds);
	}

	Time operator - (const Time& other) const { // Оператор вычитания
		return Time(hours - other.hours, minutes - other.minutes, seconds - other.seconds);
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
	int ToSeconds() const { return hours * 3600 + minutes * 60 + seconds; }
	void SetHours(int hours){ this->hours = hours; }
	void SetMinutes(int minutes){ this->minutes = minutes; }
	void SetSeconds(int seconds{ this->seconds = seconds; };

	void PrintTime(){
		std::cout << "H:" << this->GetHours()
		         << " M:" << this->GetMinutes()
		         << " S:" << this->GetSeconds()
		         << std::endl;
	}
};

