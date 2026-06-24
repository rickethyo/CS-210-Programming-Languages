/*
 * File: Main.cpp
 * Project: CS-210 Project One - Chada Tech Clocks
 * Author: Ricky Buchanan Jr.
 * Date: May 24 2026
 * Description: Runs the user menu and displays the 12-hour and 24-hour clocks.
 */

#include <iostream>
#include <limits>
#include <string>
#include "Clock.h"

using namespace std;

const int ADD_HOUR_CHOICE = 1;
const int ADD_MINUTE_CHOICE = 2;
const int ADD_SECOND_CHOICE = 3;
const int EXIT_CHOICE = 4;

// Pulls a valid integer from the user.
int getValidInput(const string& prompt, int minimumValue, int maximumValue) {
	int userInput;

	cout << prompt;
	cin >> userInput;

	// Loop repeats until the user enters a valid clock integer.
	while (cin.fail() || userInput < minimumValue || userInput > maximumValue) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "Invalid input. Please enter a number from "
			<< minimumValue << " to " << maximumValue << ": ";
		cin >> userInput;
	}

	return userInput;
}

// Displays both the 12-hour and 24-hour clocks with borders per Chada Tech requirements.
void displayClocks() {
	cout << endl;
	cout << "**************************     **************************" << endl;
	cout << "*      12-Hour Clock     *     *      24-Hour Clock     *" << endl;
	cout << "*       " << get12HourFormat() << "      *     ";
	cout << "*        " << get24HourFormat() << "        *" << endl;
	cout << "**************************     **************************" << endl;
	cout << endl;
}

// Displays the user menu with borders per Chada Tech requirements.
void displayMenu() {
	cout << "**************************" << endl;
	cout << "* 1 - Add One Hour       *" << endl;
	cout << "* 2 - Add One Minute     *" << endl;
	cout << "* 3 - Add One Second     *" << endl;
	cout << "* 4 - Exit Program       *" << endl;
	cout << "**************************" << endl;
}

// Applies the user's menu choice to the clock.
void processMenuChoice(int userChoice) {
	switch (userChoice) {
	case ADD_HOUR_CHOICE:
		addHour();
		break;
	case ADD_MINUTE_CHOICE:
		addMinute();
		break;
	case ADD_SECOND_CHOICE:
		addSecond();
		break;
	case EXIT_CHOICE:
		cout << "Exiting program." << endl;
		break;
	}
}

int main() {
	int initialHour;
	int initialMinute;
	int initialSecond;
	int userChoice;

	cout << "Enter the initial time." << endl;

	initialHour = getValidInput("Hour (0-23): ", 0, 23);
	initialMinute = getValidInput("Minute (0-59): ", 0, 59);
	initialSecond = getValidInput("Second (0-59): ", 0, 59);

	setTime(initialHour, initialMinute, initialSecond);

	do {
		displayClocks();
		displayMenu();

		userChoice = getValidInput("Enter your choice: ", ADD_HOUR_CHOICE, EXIT_CHOICE);

		processMenuChoice(userChoice);

	} while (userChoice != EXIT_CHOICE);

	return 0;
}
