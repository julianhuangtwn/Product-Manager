
#pragma once
#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H

#define MAX_DESC_LEN 1000

#include <iostream>
#include <fstream>
#include "Status.h"
#include "iProduct.h"

namespace sdds
{
	class Item : public iProduct
	{
		double m_price;
		int m_currQuantity;
		int m_quantityNeeded;
		char* m_description;
		bool m_linear;

	protected:
		Status m_state;
		int m_sku;

		//Function returns m_linear
		bool linear(void) const;

	public:
		//Constructor setting default empty values
		Item(void);

		//Copy constructor calling copy assignment operator
		Item(const Item& source);

		//Copy assignment operator hndling dynamic m_description copy 
		Item& operator =(const Item& source);

		//Destructor deleting dynamic memory used
		~Item(void);

		//Return m_quantityNeeded
		int qtyNeeded(void) const;

		//Return m_currQuantity
		int qty(void) const;

		//Return m_description
		const char* desc(void) const;

		// Return m_sku
		int sku(void) const;

		//Return m_price
		operator double() const;

		//Return true of none of the members are in their empty state
		operator bool() const;

		//Overloaded -= that subtracts m_currQuantity with qty
		int operator -=(int qty);

		//Overloaded += that adds m_currQuantity with qty
		int operator +=(int qty);

		//Sets linear to isLinear
		void linear(bool isLinear);

		//Calls m_state.clear()
		void clear(void);

		//Overloaded == that returns if m_sku is equal to sku
		bool operator ==(const int sku) const;

		//Overloaded == that returns if m_description contains substring description
		bool operator ==(const char* description) const;

		//Overloaded save from iProduct that writes a line to a file
		ofstream& save(ofstream& ofstr) const;

		//Overloaded load that reads file lines
		ifstream& load(ifstream& ifstr);

		//Overloaded display that displays all info, in either linear form or not
		ostream& display(ostream& cout) const;

		//Overloaded readSku reads sku input
		int readSku(istream& cin);

		//Overloaded read reads remaining input
		istream& read(istream& cin);
	};
}

#endif