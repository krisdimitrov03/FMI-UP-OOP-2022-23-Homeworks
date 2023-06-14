#pragma once

#include "./Outside_Resources/Date.h"
#include "./Outside_Resources/Time.h"

class DateTime
{
	Date date;
	Time time;

public:
	DateTime() = default;
	DateTime(
		unsigned day,
		unsigned month,
		unsigned year,
		size_t hours,
		size_t mins,
		size_t seconds
	);

	const Date& getDate() const;
	const Time& getTime() const;

	void setDate(unsigned day, unsigned month, unsigned year);
	void setTime(size_t hours, size_t mins, size_t seconds);

	void print() const;
};