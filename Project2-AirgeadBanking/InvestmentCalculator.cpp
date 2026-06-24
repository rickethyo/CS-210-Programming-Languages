/*
 * File: InvestmentCalculator.cpp
 * Project: CS-210 Project 2 - Airgead Banking
 * Author: Ricky Buchanan Jr.
 * Date: June 7 2026
 * Description: Implements the InvestmentCalculator class methods used to
 *              calculate compound interest balances.
 */

#include "InvestmentCalculator.h"

 // Constructor stores the user-provided investment values.
InvestmentCalculator::InvestmentCalculator(double t_initialAmount,
    double t_monthlyDeposit,
    double t_interestRate,
    int t_numYears) {
    m_initialAmount = t_initialAmount;
    m_monthlyDeposit = t_monthlyDeposit;
    m_interestRate = t_interestRate;
    m_numYears = t_numYears;
}

// Calculates one month of interest using the current balance and deposit amount.
double InvestmentCalculator::calculateMonthlyInterest(double t_openingAmount,
    double t_depositAmount) const {
    return (t_openingAmount + t_depositAmount) * ((m_interestRate / 100.0) / 12.0);
}

// Calculates the ending balance after a given number of years.
double InvestmentCalculator::calculateBalance(int t_numYears, double t_monthlyDeposit) const {
    double balance = m_initialAmount;
    double monthlyInterest;

    for (int month = 1; month <= t_numYears * 12; ++month) {
        monthlyInterest = calculateMonthlyInterest(balance, t_monthlyDeposit);
        balance = balance + t_monthlyDeposit + monthlyInterest;
    }

    return balance;
}

// Returns the initial investment amount.
double InvestmentCalculator::getInitialAmount() const {
    return m_initialAmount;
}

// Returns the monthly deposit amount.
double InvestmentCalculator::getMonthlyDeposit() const {
    return m_monthlyDeposit;
}

// Returns the number of investment years.
int InvestmentCalculator::getNumYears() const {
    return m_numYears;
}