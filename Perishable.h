
#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H

#include <iostream>
#include <fstream>
#include "Date.h"
#include "Item.h"

using namespace std;

#define MAX_INSTRUCTION_LEN 500

namespace sdds
{
	class Perishable : public Item
	{
		Date m_expiry;
		char* m_instruction;

	public:
		//Default constructor setting members to empty state
		Perishable();

		//Copy constructor, also calling base Item constructor, which calls the copy assignment operator
		Perishable(const Perishable& source);

		//Copy assignment operator that copies all resources and members over
		Perishable& operator =(const Perishable& source);

		//Destructor deallocating dynamic memory
		~Perishable();

		//Returns constant Date m_expiry
		const Date& expiry(void) const;

		//Overloaded readSku that reads a different sku compared to Item
		int readSku(istream& cin);

		//Overloaded save, which calls base save first, then reads the rest of the data from the file
		ofstream& save(ofstream& ofstr) const;

		//Overloaded load that calls base Item load, then prompts input for thr rest
		ifstream& load(ifstream& ifstr);

		//Overloaded display that calls Base Item display, the display the rest of the info
		ostream& display(ostream& cout) const;

		//Overloaded read that calls base Item read, then prompts for other fields
		istream& read(istream& cin);
	};
}

#endif