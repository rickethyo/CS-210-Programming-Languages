/*
 * File: Clock.cpp
 * Project: CS-210 Project One - Chada Tech Clocks
 * Author: Ricky Buchanan Jr.
 * Date: May 24 2026
 * Description: Implements clock functions for time updates and formatting.
 */

#include "Clock.h"

#include <iomanip>
#include <sstream>

int hour;
int minute;
int second;

// Stores the initial time values as integer values.
void setTime(int initialHour, int initialMinute, int initialSecond) {
	hour = initialHour;
	minute = initialMinute;
	second = initialSecond;
}

// Adds one hour and rolls over to zero after 23 hours.
void addHour() {
	hour++;

	if (hour > 23) {
		hour = 0;
	}
}

// Adds one minute and rolls over to the next hour after 59.
void addMinute() {
	minute++;

	if (minute > 59) {
		minute = 0;
		addHour();
	}
}

// Adds one second and rolls over to the next minute after 59.
void addSecond() {
	second++;

	if (second > 59) {
		second = 0;
		addMinute();
	}
}

// Adds a leading zero to one-digit time values.
std::string pad(int value) {
	std::ostringstream output;

	output << std::setfill('0') << std::setw(2) << value;

	return output.str();
}

// Returns AM or PM for the current hour.
std::string getSuffix() {
	if (hour >= 12) {
		return "PM";
	}

	return "AM";
}

// Returns the time formatted as a 24-hour clock string.
std::string get24HourFormat() {
	return pad(hour) + ":" + pad(minute) + ":" + pad(second);
}

// Returns the time formatted as a 12-hour clock string.
std::string get12HourFormat() {
	int displayHour;

	displayHour = hour % 12;

	if (displayHour == 0) {
		displayHour = 12;
	}

	return pad(displayHour) + ":" + pad(minute) + ":" + pad(second) + " " + getSuffix();
}
