#include "clock_time.h"

#include <iomanip>
#include <iostream>
#include <vector>
#include <optional>
#include <fstream>
#include <sstream>

using namespace std;

Time::Time(int hours, int minutes) : hours_(hours), minutes_(minutes) {};

istringstream &operator>>(istringstream& f, Time& time) {
    string time_str;
    f >> time_str;

    tm tm = {};
    istringstream ss(time_str);
    ss >> get_time(&tm, "%H:%M");

    if (ss.fail()) {
        f.setstate(ios::failbit);
        return f;
    }

    time = Time(tm.tm_hour, tm.tm_min);
    return f;
}

ostream &operator<<(ostream& f, const Time& time) {
    tm tm;
    tm.tm_hour = time.hours_;
    tm.tm_min = time.minutes_;

    f << put_time(&tm, "%H:%M");

    return f;
}

Time Time::operator+(const Time & other) {
    int total_minutes = (hours_ * 60 + minutes_) + (other.hours_ * 60 + other.minutes_);
    return Time(total_minutes / 60, total_minutes % 60);
}

Time Time::operator-(const Time & other) {
    int total_minutes = (hours_ * 60 + minutes_) - (other.hours_ * 60 + other.minutes_);
    return Time(total_minutes / 60, total_minutes % 60);
}

bool operator<(Time& a, Time& b) {
    return (a.hours_ < b.hours_) || (a.hours_ == b.hours_ && a.minutes_ < b.minutes_);
}

int Time::get_hours() { return hours_; }
int Time::get_minutes() { return minutes_; }