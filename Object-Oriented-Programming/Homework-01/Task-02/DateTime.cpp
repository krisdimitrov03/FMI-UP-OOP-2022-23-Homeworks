#include "DateTime.h"

DateTime::DateTime(
    unsigned day,
    unsigned month,
    unsigned year,
    size_t hours,
    size_t mins,
    size_t seconds
) : date(day, month, year), time(hours, mins, seconds) {};

const Date& DateTime::getDate() const
{
    return date;
}

const Time& DateTime::getTime() const
{
    return time;
}

void DateTime::setDate(unsigned day, unsigned month, unsigned year)
{
    date.setYear(year);
    date.setMonth(month);
    date.setDay(day);
}

void DateTime::setTime(size_t hours, size_t mins, size_t seconds)
{
    time.setHours(hours);
    time.setMins(mins);
    time.setSeconds(seconds);
}

void DateTime::print() const {
    time.print(false);
    std::cout << " ";
    date.print();
}