#ifndef SIMPLEWATCH_HPP
#define SIMPLEWATCH_HPP

class Time; // forward declaration

class SimpleWatch {
public:
    void showTime(const Time& time);
    void setTime(Time& time, int h, int m, int s);
};

#endif // SIMPLEWATCH_HPP

