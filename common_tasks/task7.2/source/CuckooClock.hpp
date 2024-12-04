#ifndef CUCKOO_CLOCK_HPP
#define CUCKOO_CLOCK_HPP

#include "Clock.hpp"

class CuckooClock : public Clock {
public:
	CuckooClock() : Clock() {
		cout << "CuckooClock constructor called\n";
	}

	CuckooClock(int h, int m, int s) : Clock(h, m, s) {
		cout << "CuckooClock parameterized constructor called\n";
	}

	~CuckooClock() {
		cout << "CuckooClock destructor called\n";
	}

	void chime() const {
		cout << "Cuckoo! Cuckoo!\n";
	}
};
#endif
