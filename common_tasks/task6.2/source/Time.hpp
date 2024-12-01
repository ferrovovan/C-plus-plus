#include <iostream>
#include <stdexcept>

class Time {
private:
	int hours, minutes, seconds;
	static int object_count;
	
	void Normalize() noexcept;
public:
	Time() noexcept; // Default Constructor
	Time(int h, int m, int s);
	Time(const Time& t) noexcept; // Copy Constructor
	~Time() noexcept; // Destructor


	Time& operator = (const Time& other) noexcept {
		this->hours = other.hours; // явное указания на член класса
		minutes = other.minutes;   // неявное указание
		seconds = other.seconds;
		return *this;
	}
	
	Time operator + (int s) const;
	Time operator + (const Time& other) const noexcept;
	Time& operator += (int s);
	Time& operator += (const Time& other) noexcept;

	Time operator - (int s) const;
	Time operator - (const Time& other) const;
	Time& operator -= (const Time& other);
	Time& operator -= (int s);

	/* Операторы сравнения */
	bool operator==(const Time& other) const noexcept{
		return hours == other.hours && minutes == other.minutes && seconds == other.seconds;
	}
	bool operator > (const Time& other) const noexcept{
		return this->ToSeconds() > other.ToSeconds();
	}
	bool operator < (const Time& other) const noexcept{
		return this->ToSeconds() < other.ToSeconds();
	}


	int GetHours()   const noexcept { return hours; }
	int GetMinutes() const noexcept { return minutes; }
	int GetSeconds() const noexcept { return seconds; }

	static int GetObjectCount() noexcept {
		return object_count;
	}

	int ToSeconds() const noexcept { return hours * 3600 + minutes * 60 + seconds; }
	void SetHours(int hours);
	void PrintTime();
};

