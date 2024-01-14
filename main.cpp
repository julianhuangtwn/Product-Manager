/*
This program utilizes various OOP concepts, it manages files, which mainly
store item information that are separated into perishable and non-perishable.
Both are derived from a pure abstract class, and each objects are stored dynamically
in arrays.

Items can be manipulated, such as listing all current items, adding or removing an item, 
sort, and also a "ship item" that ships items when quantity on hand is enough

Some items which are perishable will have a Date associated with them, with the expiry date
stored in the Date objects

When there error in certain situations, the error codes and messages are stored in a 
Status object, where they usually store the actual status of the items themselves
*/
#include <iostream>
#include <fstream>
#include "AidMan.h"
#include "Utils.h"

using namespace sdds;
using namespace std;


// Displays the final version of the file when user quits
void displayFile(const char* file);

// Copies file contents from source to destination,
// Mainly just for keeping the original file
void copyfile(const char* to, const char* from);



// Displays the final version of the file when user quits
void displayFile(const char* file) {
	ifstream in(file);
	char ch;
	cout << "File: " << file << endl;
	while (in.get(ch)) cout << ch;
}

// Copies file contents from source to destination,
// Mainly just for keeping the original file
void copyfile(const char* destination, const char* source) {
	ifstream in(source);
	ofstream out(destination);
	char ch;
	while (in.get(ch)) out.put(ch);
}


// Copies original to data.dat. Runs the program, then when finished, displays files
int main() {
	copyfile("data.dat", "original.dat");
	AidMan().run();
	displayFile("data.dat");
	cout << endl << "------------------------------------------------" << endl;
	displayFile("shippingOrder.txt");
	return 0;
}