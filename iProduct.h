
#ifndef SDDS_IPRODUCT_H
#define SDDS_IPRODUCT_H

#include <iostream>

using namespace std;

namespace sdds
{
	class iProduct
	{
	public:
		// Reads sku input
		virtual int readSku(std::istream& istr) = 0;

		// Reduce quantity on hand
		virtual int operator -=(int qty) = 0;

		// Increase quantity on hand
		virtual int operator +=(int qty) = 0;

		// Return m_description
		virtual const char* desc(void) const = 0;

		// Return m_sku
		virtual int sku(void) const = 0;

		// Return m_price
		virtual operator double() const = 0;

		// Return true of none of the members are in their empty state
		virtual operator bool() const = 0;

		// Return m_quantityNeeded
		virtual int qtyNeeded() const = 0;

		// Return m_currQualtity
		virtual int qty() const = 0;

		// Sets m_linear to isLinear
		virtual void linear(bool isLinear) = 0;

		// Saves the iProduct into a file
		virtual std::ofstream& save(std::ofstream& ofstr) const = 0;

		// Loads an iProduct from a file
		virtual std::ifstream& load(std::ifstream& ifstr) = 0;

		// Displays the iProduct on the screen
		virtual std::ostream& display(std::ostream& ostr) const = 0;

		// Reads input to store in iProduct
		virtual std::istream& read(std::istream& istr) = 0;

		// Return true if the SKU is a match to the iProduct's SKU
		virtual bool operator ==(const int sku) const = 0;

		// Returns true if the description is found in the iPorduct's description
		virtual bool operator ==(const char* description) const = 0;

		// Blank destructor, purpose is just to have virtual enabling the correct destructor to be called
		virtual ~iProduct();
	};

	//Returns display function call
	ostream& operator <<(ostream& cout, const iProduct& source);

	//Returns read function call
	istream& operator >>(istream& cin, iProduct& destination);
}


#endif