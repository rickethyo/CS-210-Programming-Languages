/*
 * File: Clock.h
 * Project: CS-210 Project One - Chada Tech Clocks
 * Author: Ricky Buchanan Jr.
 * Date: May 24 2026
 * Description: Declares clock functions for setting, updating, and formatting time.
 */

#ifndef CLOCK_H
#define CLOCK_H

#include <string>

void setTime(int initialHour, int initialMinute, int initialSecond);
void addHour();
void addMinute();
void addSecond();

std::string get12HourFormat();
std::string get24HourFormat();
std::string pad(int value);
std::string getSuffix();

#endif