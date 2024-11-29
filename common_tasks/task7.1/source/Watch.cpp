#include "Watch.hpp"
#include "Time.hpp"
#include <iostream>

bool Watch::is24HourFormat = true;

void Watch::showTime(const Time& time) {
    int hours = time.hours;
    if ( not is24HourFormat and hours > 12)
        hours -= 12;
    std::cout << "Time: " << hours << ":" << time.minutes << ":" << time.seconds << std::endl;
}

void Watch::setTime(Time& time, int h, int m, int s) {
    time.hours = h;
    time.minutes = m;
    time.seconds = s;
}

