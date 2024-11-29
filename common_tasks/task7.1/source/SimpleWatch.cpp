#include "SimpleWatch.hpp"
#include "Time.hpp"
#include <iostream>

void SimpleWatch::showTime(const Time& time) {
    int hours = time.hours;
//    if ( not Watch::is24HourFormat and hours > 12)
//        hours -= 12;
    std::cout << "SimpleWatch: " << hours << ":" << time.minutes << ":" << time.seconds << std::endl;
}

void SimpleWatch::setTime(Time& time, int h, int m, int s) {
    time.hours = h;
    time.minutes = m;
    time.seconds = s;
}

