/*
 * File: InvestmentCalculator.h
 * Project: CS-210 Project 2 - Airgead Banking
 * Author: Ricky Buchanan Jr.
 * Date: June 2026
 * Description: Declares the InvestmentCalculator class used to calculate
 *              compound interest with and without monthly deposits.
 */

#ifndef CS210_PROJECT_2_INVESTMENTCALCULATOR_H_
#define CS210_PROJECT_2_INVESTMENTCALCULATOR_H_

class InvestmentCalculator {
public:
    InvestmentCalculator(double t_initialAmount,
        double t_monthlyDeposit,
        double t_interestRate,
        int t_numYears);

    double calculateBalance(int t_numYears, double t_monthlyDeposit) const;

    double getInitialAmount() const;
    double getMonthlyDeposit() const;
    int getNumYears() const;

private:
    double m_initialAmount;
    double m_monthlyDeposit;
    double m_interestRate;
    int m_numYears;

    double calculateMonthlyInterest(double t_openingAmount,
        double t_depositAmount) const;
};

#endif