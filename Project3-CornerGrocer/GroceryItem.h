/*
 * File: GroceryItem.h
 * Project: CS-210 Project 3 - Corner Grocer
 * Author: Ricky Buchanan Jr.
 * Date: June 21, 2026
 * Description: Declares the GroceryItem class, which stores the name
 *              and purchase quantity of an individual grocery item.
 */

#pragma once

#include <string>

class GroceryItem {
public:
    // Initializes a grocery item with a name and starting quantity.
    // @param itemName - the name of the grocery item
    // @param itemQuantity - the starting purchase quantity
    GroceryItem(std::string itemName, int itemQuantity);

    // Returns the name of the grocery item.
    // @returns - the grocery item's name
    std::string getItemName() const;

    // Returns the purchase quantity of the grocery item.
    // @returns - the grocery item's purchase quantity
    int getItemQuantity() const;

    // Increases the grocery item's purchase quantity by one.
    void incrementQuantity();

private:
    std::string itemName;
    int itemQuantity;
};