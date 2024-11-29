#ifndef WATCH_HPP
#define WATCH_HPP

class Time; // forward declaration
//#include "SimpleWatch.hpp"

class Watch {
private:
    static bool is24HourFormat; // Переменная для формата 12/24
public:
    static void setFormat(bool format) { is24HourFormat = format; }

    static void showTime(const Time& time);
//    friend void SimpleWatch::showTime(const Time& time);
    static void setTime(Time& time, int h, int m, int s);
};

#endif // WATCH_HPP

