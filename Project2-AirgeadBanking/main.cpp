/*
 * File: main.cpp
 * Project: CS-210 Project 2 - Airgead Banking
 * Author: Ricky Buchanan Jr.
 * Date: June 7 2026
 * Description: Runs the Airgead Banking investment calculator application.
 *              Gets user input, creates an InvestmentCalculator object,
 *              and displays investment growth reports.
 */

#include <iostream>
#include <iomanip>
#include <limits>
#include <sstream>
#include <string>
#include "InvestmentCalculator.h"

using namespace std;

// Gets and validates a non-negative decimal value from the user.
double getPositiveDouble(const string& t_prompt) {
    double userInput;

    cout << t_prompt;
    cin >> userInput;

    while (cin.fail() || userInput < 0.0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Invalid input. Please enter a non-negative number: ";
        cin >> userInput;
    }

    return userInput;
}

// Gets and validates a positive whole number from the user.
int getPositiveInt(const string& t_prompt) {
    int userInput;

    cout << t_prompt;
    cin >> userInput;

    while (cin.fail() || userInput <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Invalid input. Please enter a positive whole number: ";
        cin >> userInput;
    }

    return userInput;
}

// Formats a number as currency with commas and two decimal places.
string formatMoney(double t_amount) {
    ostringstream outputStream;
    string moneyString;
    int decimalPosition;

    outputStream << fixed << setprecision(2) << t_amount;
    moneyString = outputStream.str();

    decimalPosition = static_cast<int>(moneyString.find('.'));

    for (int insertPosition = decimalPosition - 3; insertPosition > 0; insertPosition -= 3) {
        moneyString.insert(insertPosition, ",");
    }

    return "$" + moneyString;
}

// Prints one row of the yearly investment report.
void printDetails(int t_year, double t_yearEndBalance, double t_interestEarned) {
    cout << left << setw(8) << t_year;
    cout << right << setw(20) << formatMoney(t_yearEndBalance);
    cout << setw(30) << formatMoney(t_interestEarned) << endl;
}

// Displays one investment report using the requested monthly deposit amount.
void displayReport(InvestmentCalculator t_calculator,
    double t_monthlyDeposit,
    const string& t_reportTitle) {
    double previousBalance = t_calculator.getInitialAmount();
    double yearEndBalance;
    double interestEarned;

    cout << endl;
    cout << t_reportTitle << endl;
    cout << "==========================================================" << endl;
    cout << left << setw(8) << "Year"
        << right << setw(20) << "Year End Balance"
        << setw(30) << "Year End Earned Interest" << endl;
    cout << "----------------------------------------------------------" << endl;

    for (int year = 1; year <= t_calculator.getNumYears(); ++year) {
        yearEndBalance = t_calculator.calculateBalance(year, t_monthlyDeposit);
        interestEarned = yearEndBalance - previousBalance - (t_monthlyDeposit * 12);

        printDetails(year, yearEndBalance, interestEarned);

        previousBalance = yearEndBalance;
    }
}

int main() {
    char runAgain = 'y';

    // Allows the user to test multiple investment scenarios and accounts for capitalization of "Y".
    while (runAgain == 'y' || runAgain == 'Y') {
        double initialAmount;
        double monthlyDeposit;
        double interestRate;
        int numYears;

        // Displays the data input screen and collects investment values.
        cout << "**********************************" << endl;
        cout << "********** Data Input ************" << endl;

        initialAmount = getPositiveDouble("Initial Investment Amount: $");
        monthlyDeposit = getPositiveDouble("Monthly Deposit: $");
        interestRate = getPositiveDouble("Annual Interest: %");
        numYears = getPositiveInt("Number of Years: ");

        // Pauses the program before displaying the reports.
        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();

        // Creates the calculator object using the user's input.
        InvestmentCalculator calculator(initialAmount, monthlyDeposit, interestRate, numYears);

        // Displays both required investment reports.
        displayReport(calculator, 0.0,
            "Balance and Interest Without Additional Monthly Deposits");

        displayReport(calculator, calculator.getMonthlyDeposit(),
            "Balance and Interest With Additional Monthly Deposits");

        // Gives the user the option to test another scenario.
        cout << endl;
        cout << "Would you like to test another investment? (y/n): ";
        cin >> runAgain;
        cout << endl;
    }

    cout << "Thank you for using the Airgead Banking app." << endl;

    return 0;
}