#include <iostream>
#include <stdexcept>

class Time {
private:
	int hours, minutes, seconds;
	static int object_count;
	
	void Normalize() noexcept;
public:
	Time() noexcept;
	Time(int h, int m, int s) noexcept;
	Time(const Time& t) noexcept: Time(t.hours, t.minutes, t.seconds){}
	~Time() noexcept;
	
	int GetHours() const noexcept { return hours; }
	int GetMinutes() const noexcept { return minutes; }
	int GetSeconds() const noexcept { return seconds; }

	Time& operator = (const Time& other) noexcept{
		this->hours = other.hours; // явное указания на член класса
		minutes = other.minutes;   // неявное указание
		seconds = other.seconds;
		return *this;
	}

	Time& operator += (int s) noexcept {
		seconds += s;
		Normalize();
		return *this;
	}
	Time operator + (int s) const noexcept {
		return Time(this->hours, this->minutes, this->seconds + s);
	}

	Time& operator += (const Time& other) noexcept {
		hours += other.hours;
		minutes += other.minutes;
		seconds += other.seconds;
		Normalize();
		return *this;
	}

	// Оператор вычитания
	Time operator - (int s) const noexcept {
		return Time(this->hours, this->minutes, this->seconds - s);
	}
	
	Time operator - (const Time& other) const noexcept {
		return Time(hours - other.hours, minutes - other.minutes, seconds - other.seconds);
	}

	// Оператор вычитания с присваиванием
	Time& operator -= (int s) noexcept {
		seconds -= s;
		Normalize();
		return *this;
	}
	// Оператор сравнения
	bool operator==(const Time& other) const noexcept {
		return hours == other.hours && minutes == other.minutes && seconds == other.seconds;
	}

	static int GetObjectCount() noexcept {
		return object_count;
	}
	
	int ToSeconds() const noexcept;
	void SetHours(int hours);
	void PrintTime(){
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
};

