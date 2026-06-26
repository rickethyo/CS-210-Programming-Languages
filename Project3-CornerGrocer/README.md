# CS-210 Project Three: Corner Grocer

## Project Summary

The Corner Grocer project is a simple C++ item-tracking program designed to analyze a text file containing grocery purchase records. The program reads each item from the input file, counts how many times each item appears, and stores the frequency information for later use. Users can search for a specific item, display a list of all purchased items and their frequencies, or view the purchase data as a text-based histogram.

The program also creates a backup file named `frequency.dat` containing the calculated item frequencies. This provides a way to preserve the processed data outside of the running program.

## What I Did Well

One part of the project that I felt particularly good about was organizing the program into separate components. I created a `GroceryItem` class to represent each grocery item and its purchase quantity. The class keeps its data members private and provides public member functions for accessing item information and increasing its quantity.

I also used a `map` to store grocery items. A lowercase version of each item name is used as the map key, which allows searches to ignore differences in capitalization. Furthermore, the search function ignores an `s` at the end of an item name, helping ensure that an item is not missed when the user enters a singular form instead of the plural form used in the purchase records. Before accessing an item, the program uses the map's `find()` function to determine whether the item already exists. This prevents accidental insertion during searches and makes the program's behavior easier to understand.

## Areas for Improvement

One improvement would be to separate more of the menu and file-processing logic from `main.cpp` by moving it into additional classes. The current program is organized into functions, but these responsibilities could be moved into another class, such as a grocery-tracking or inventory-management class. This would reduce the amount of responsibility handled by the main source file and make the program easier to expand in the future.

The program could also provide more detailed error handling. For example, it could give the user additional information when the input file cannot be found or opened. The file name could also be provided through a configuration setting or command-line argument instead of being written directly into the program.

For a larger dataset, the program could be enhanced to support sorting the results alphabetically or by purchase frequency. Additionally, with the introduction of purchase dates, a FIFO, or first-in, first-out, rotation system could be established.

## Challenges and Support Resources

One of the most challenging parts of the project was making item searches ignore capitalization while still displaying the item names correctly. At first, I did not realize this would be necessary until the program returned a result of zero for items that I knew were present in the purchase records. I overcame this by creating a lowercase version of each item name for use as the map key while preserving the original item name inside the `GroceryItem` object.

Another challenge was determining when to use the map's indexing operator and when to use `find()`. Using `find()` for searches prevents the program from creating an item that was not actually present in the input file. Working through this helped me better understand how C++ maps behave.

Visual Studio's debugger, compiler messages, and C++ documentation were valuable resources while developing the project. I was able to find and correct many bugs simply by following compiler messages back to their source. I can continue using these tools, along with GitHub for version control and project documentation, as part of my programming support network.

## Transferable Skills

One of the most valuable skills I gained from this project was learning how much easier a program is to manage when its responsibilities are divided between separate functions and classes. I plan to apply this directly to my Network Uploader Python project, which I originally built more as a personal tool than as a professionally structured application. As I rework it, I want to separate the user interface, file-processing logic, configuration handling, and other responsibilities into their own classes instead of allowing too much of the program to remain in one place.

This project also reinforced the importance of clear and consistent documentation. I tend to overlook comments in my personal projects because I already understand what the code is doing while I am writing it. However, that can make the code harder to return to later and more difficult for someone else to understand. When I rebuild the Network Uploader, I plan to use clearer function descriptions, more consistent comments, and better naming so the purpose of each section is easier to follow.

The experience I gained with object-oriented design, input validation, file handling, debugging, and program organization will all transfer directly to that rework. These changes should make the Network Uploader easier to maintain, test, and expand with new features in the future.


The experience I gained with object-oriented design, input validation, file handling, debugging, and program organization will all transfer directly to that rework. These changes should make the Network Uploader easier to maintain, test, and expand with new features in the future.

## Maintainability, Readability, and Adaptability

I made the program maintainable and readable by using descriptive function and variable names, consistent formatting, and comments that explain the purpose of each function and major section of the program. Comments follow a consistent pattern, and named constants are used for the menu choices instead of placing unexplained numbers throughout the code.

The `GroceryItem` class separates item data from the program's menu and file-processing logic. Its private data members protect the object's internal state, while its public member functions provide controlled access to the data.

The program is adaptable because additional menu options or output formats could be added without rewriting the entire application. The map-based structure also allows the program to process different grocery records without requiring a predefined list of items.
