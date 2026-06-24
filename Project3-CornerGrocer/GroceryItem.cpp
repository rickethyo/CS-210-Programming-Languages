/*
 * File: GroceryItem.cpp
 * Project: CS-210 Project 3 - Corner Grocer
 * Author: Ricky Buchanan Jr.
 * Date: June 21, 2026
 * Description: Defines the GroceryItem class methods used to store
 *              and update grocery item purchase information.
 */

#include "GroceryItem.h"

 // Initializes the grocery item's name and starting quantity.
GroceryItem::GroceryItem(std::string itemName, int itemQuantity) {
    this->itemName = itemName;
    this->itemQuantity = itemQuantity;
}

// Returns the name of the grocery item.
std::string GroceryItem::getItemName() const {
    return itemName;
}

// Returns the purchase quantity of the grocery item.
int GroceryItem::getItemQuantity() const {
    return itemQuantity;
}

// Increases the grocery item's purchase quantity by one.
void GroceryItem::incrementQuantity() {
    itemQuantity++;
}