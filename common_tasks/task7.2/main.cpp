#include <iostream>
#include "CuckooClock.hpp"
#include "WallClock.hpp"
#include "SmartWatch.hpp"
#include "SigmaClock.hpp"

void print_green(const std::string& message) {
	std::cout << "\033[0;32m" << message << "\033[0m\n";
}

int main() {
	print_green("Creating CuckooClock:\n");
	CuckooClock cuckoo(10, 15, 0);
	cuckoo.displayTime();
	cuckoo.chime();

	print_green("\nCreating WallClock:\n");
	WallClock wall(11, 30, 45);
	wall.displayTime();

	print_green("\nCreating SmartWatch:\n");
	SmartWatch smart(14, 45, 30);
	smart.displayTime();
	smart.displayNotifications();

	print_green("\nCreating SigmaClock:\n");
	SigmaClock sigma;
	sigma.displayTime();

	print_green("\nDestructors will be called automatically.\n");
	return 0;
}


