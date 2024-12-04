#ifndef CLOCK_HPP
#define CLOCK_HPP

#include "Time.hpp"
using namespace std;

class Clock {
protected:
	Time time;

public:
	Clock() : time() {
		cout << "Clock base constructor called\n";
	}

	Clock(int h, int m, int s) : time(h, m, s) {
		cout << "Clock parameterized constructor called\n";
	}

	~Clock() {
		cout << "Clock destructor called\n";
	}

	void displayTime() const { time.PrintTime(); }
};

#endif
