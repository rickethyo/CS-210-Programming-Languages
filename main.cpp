/*
 * File: main.cpp
 * Project: CS-210 Project 3 - Corner Grocer
 * Author: Ricky Buchanan Jr.
 * Date: June 21, 2026
 * Description: Runs the Corner Grocer item-tracking program. The program
 *              reads grocery purchase records, creates a backup file,
 *              and displays item frequency information through a menu.
 */

#include <cctype>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <string>

#include "GroceryItem.h"

using namespace std;

// Uses CAP_CASE for constants and camelCase for functions and variables
// to follow the course naming conventions.
const int SEARCH_ITEM = 1;
const int DISPLAY_FREQUENCIES = 2;
const int DISPLAY_HISTOGRAM = 3;
const int EXIT_PROGRAM = 4;

const string INPUT_FILE_NAME = "InputFile.txt";
const string BACKUP_FILE_NAME = "frequency.dat";

// Converts a string to lowercase for case-insensitive comparisons.
// @param text - the string to convert
// @returns - a lowercase copy of the string
string convertToLowercase(const string& text);

// Displays the Corner Grocer menu options.
void displayMenu();

// Gets and validates the user's menu selection.
// @returns - a valid menu choice from 1 through 4
int getMenuChoice();

// Reads the input file and stores each grocery item's frequency.
// @param inputFileName - the name of the grocery purchase input file
// @param itemFrequencies - the map used to store grocery item objects
// @returns - true if the file was successfully read, otherwise false
bool loadItemFrequencies(
    const string& inputFileName,
    map<string, GroceryItem>& itemFrequencies
);

// Creates the required backup file containing item frequencies.
// @param inputFileName - the name of the grocery purchase input file
// @param outputFileName - the name of the backup output file
// @returns - true if the backup file was successfully created, otherwise false
bool createBackupFile(
    const string& inputFileName,
    const string& outputFileName
);

// Prompts the user for an item and displays its purchase frequency.
// @param inputFileName - the name of the grocery purchase input file
void searchForItem(const string& inputFileName);

// Displays every grocery item and its numeric frequency.
// @param inputFileName - the name of the grocery purchase input file
void displayAllFrequencies(const string& inputFileName);

// Displays every grocery item as a text-based histogram.
// @param inputFileName - the name of the grocery purchase input file
void displayItemHistogram(const string& inputFileName);

int main() {
    int menuChoice;

    // Creates the required backup file before the user interacts with the menu.
    if (!createBackupFile(INPUT_FILE_NAME, BACKUP_FILE_NAME)) {
        cout << "The program could not initialize successfully." << endl;
        return 1;
    }

    // Repeats the menu until the user selects the exit option.
    do {
        displayMenu();
        menuChoice = getMenuChoice();

        cout << endl;

        if (menuChoice == SEARCH_ITEM) {
            searchForItem(INPUT_FILE_NAME);
        }
        else if (menuChoice == DISPLAY_FREQUENCIES) {
            displayAllFrequencies(INPUT_FILE_NAME);
        }
        else if (menuChoice == DISPLAY_HISTOGRAM) {
            displayItemHistogram(INPUT_FILE_NAME);
        }
        else if (menuChoice == EXIT_PROGRAM) {
            cout << "Thank you for using the Corner Grocer Item Tracker."
                << endl;
        }

    } while (menuChoice != EXIT_PROGRAM);

    return 0;
}

void displayMenu() {
    cout << endl;
    cout << "========================================" << endl;
    cout << "      CORNER GROCER ITEM TRACKER" << endl;
    cout << "========================================" << endl;
    cout << "1. Search for an item" << endl;
    cout << "2. Display all item frequencies" << endl;
    cout << "3. Display item histogram" << endl;
    cout << "4. Exit" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Enter your selection: ";
}

int getMenuChoice() {
    int menuChoice;

    cin >> menuChoice;

    // Clears invalid input and continues prompting until 1 through 4 is entered.
    while (cin.fail() ||
        menuChoice < SEARCH_ITEM ||
        menuChoice > EXIT_PROGRAM) {

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Invalid selection. Please enter a number from 1 through 4: ";
        cin >> menuChoice;
    }

    // Removes the remaining newline so getline() can be used later.
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return menuChoice;
}
// Converts each character to lowercase so search always returns a result regardless of capitilization.
string convertToLowercase(const string& text) {
    string lowercaseText = text;

    
    for (string::size_type i = 0; i < lowercaseText.length(); ++i) {
        lowercaseText.at(i) = static_cast<char>(
            tolower(static_cast<unsigned char>(lowercaseText.at(i)))
            );
    }

    return lowercaseText;
}

bool loadItemFrequencies(
    const string& inputFileName,
    map<string, GroceryItem>& itemFrequencies) {

    ifstream inputFile;
    string itemName;

    inputFile.open(inputFileName);

    if (!inputFile.is_open()) {
        cout << "Error: Could not open " << inputFileName << "." << endl;
        return false;
    }

    // Removes old data before rebuilding the frequencies from the input file.
    itemFrequencies.clear();

    while (inputFile >> itemName) {
        string itemKey = convertToLowercase(itemName);
        map<string, GroceryItem>::iterator itemPosition;

        // Lowercase keys allow later searches to ignore capitalization.
        itemPosition = itemFrequencies.find(itemKey);

        if (itemPosition == itemFrequencies.end()) {
            // Creates a new grocery item when the item is first encountered.
            itemFrequencies.emplace(
                itemKey,
                GroceryItem(itemName, 1)
            );
        }
        else {
            // Increases the stored quantity when the item appears again.
            itemPosition->second.incrementQuantity();
        }
    }

    inputFile.close();

    return true;
}

bool createBackupFile(
    const string& inputFileName,
    const string& outputFileName) {

    map<string, GroceryItem> itemFrequencies;
    map<string, GroceryItem>::const_iterator itemPosition;
    ofstream outputFile;

    // Loads the current purchase records before creating the backup.
    if (!loadItemFrequencies(inputFileName, itemFrequencies)) {
        return false;
    }

    outputFile.open(outputFileName);

    if (!outputFile.is_open()) {
        cout << "Error: Could not create " << outputFileName << "." << endl;
        return false;
    }

    // Writes each grocery item and its accumulated quantity to frequency.dat.
    for (itemPosition = itemFrequencies.begin();
        itemPosition != itemFrequencies.end();
        ++itemPosition) {

        outputFile << itemPosition->second.getItemName() << " "
            << itemPosition->second.getItemQuantity() << endl;
    }

    outputFile.close();

    return true;
}

void searchForItem(const string& inputFileName) {
    map<string, GroceryItem> itemFrequencies;
    map<string, GroceryItem>::const_iterator itemPosition;
    string itemName;
    string searchKey;

    // Rereads the source file so the search uses the latest purchase records.
    if (!loadItemFrequencies(inputFileName, itemFrequencies)) {
        return;
    }

    cout << "Enter the item you wish to search for: ";
    getline(cin, itemName);

    // Converts the user's search to lowercase to make it case-insensitive.
    searchKey = convertToLowercase(itemName);
    itemPosition = itemFrequencies.find(searchKey);

    // Tries a simple singular or plural variation if no exact match is found to account for instances
    // of the user forgetting an 's'.
    if (itemPosition == itemFrequencies.end()) {
        if (!searchKey.empty() && searchKey.back() == 's') {
            searchKey.pop_back();
        }
        else {
            searchKey += "s";
        }

        itemPosition = itemFrequencies.find(searchKey);
    }

    if (itemPosition != itemFrequencies.end()) {
        cout << itemPosition->second.getItemName() << " purchased "
            << itemPosition->second.getItemQuantity()
            << " time(s)." << endl;
    }
    else {
        cout << itemName
            << " was not found in the purchase records." << endl;
    }
}

void displayAllFrequencies(const string& inputFileName) {
    map<string, GroceryItem> itemFrequencies;
    map<string, GroceryItem>::const_iterator itemPosition;

    // Rereads the source file so the report includes the latest records.
    if (!loadItemFrequencies(inputFileName, itemFrequencies)) {
        return;
    }

    cout << "ITEM PURCHASE FREQUENCIES" << endl;
    cout << "-------------------------" << endl;

    // Displays each item beside its numeric purchase frequency.
    for (itemPosition = itemFrequencies.begin();
        itemPosition != itemFrequencies.end();
        ++itemPosition) {

        cout << itemPosition->second.getItemName() << " "
            << itemPosition->second.getItemQuantity() << endl;
    }
}

void displayItemHistogram(const string& inputFileName) {
    map<string, GroceryItem> itemFrequencies;
    map<string, GroceryItem>::const_iterator itemPosition;
    int itemCount;

    // Rereads the source file so the histogram includes the latest records.
    if (!loadItemFrequencies(inputFileName, itemFrequencies)) {
        return;
    }

    cout << "ITEM PURCHASE HISTOGRAM" << endl;
    cout << "-----------------------" << endl;

    for (itemPosition = itemFrequencies.begin();
        itemPosition != itemFrequencies.end();
        ++itemPosition) {

        cout << itemPosition->second.getItemName() << " ";

        // Prints one asterisk for each recorded purchase of the current item.
        for (itemCount = 0;
            itemCount < itemPosition->second.getItemQuantity();
            ++itemCount) {

            cout << "*";
        }

        cout << endl;
    }
}