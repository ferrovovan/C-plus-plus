#ifndef SMART_WATCH_HPP
#define SMART_WATCH_HPP

#include "Clock.hpp"

class SmartWatch : public Clock {
public:
	SmartWatch() : Clock() {
		cout << "SmartWatch constructor called\n";
	}

	SmartWatch(int h, int m, int s) : Clock(h, m, s) {
		cout << "SmartWatch parameterized constructor called\n";
	}

	~SmartWatch() {
		cout << "SmartWatch destructor called\n";
	}

	void displayNotifications() const {
		cout << "No new notifications\n";
	}
};
#endif
