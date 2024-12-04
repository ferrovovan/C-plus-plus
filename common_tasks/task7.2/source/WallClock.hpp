#ifndef WALL_CLOCK_HPP
#define WALL_CLOCK_HPP

#include "Clock.hpp"

class WallClock : public Clock {
public:
	WallClock() : Clock() {
		cout << "WallClock constructor called\n";
	}

	WallClock(int h, int m, int s) : Clock(h, m, s) {
		cout << "WallClock parameterized constructor called\n";
	}

	~WallClock() {
		cout << "WallClock destructor called\n";
	}
};
#endif
