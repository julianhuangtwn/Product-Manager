
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include "Item.h"
#include "Utils.h"


using namespace std;

namespace sdds
{
	//Function returns m_linear
	bool Item::linear() const
	{
		return m_linear;
	}

	//Constructor setting default empty values
	Item::Item()
	{
		m_price = 0;
		m_currQuantity = 0;
		m_quantityNeeded = 0;
		m_description = nullptr;
		m_linear = false;
		m_sku = 0;
	}

	//Copy constructor calling copy assignment operator
	Item::Item(const Item& source)
	{
		m_description = nullptr;
		*this = source;
	}

	//Copy assignment operator hndling dynamic m_description copy 
	Item& Item::operator =(const Item& source)
	{
		if (this != &source)
		{
			m_price = source.m_price;
			m_currQuantity = source.m_currQuantity;
			m_quantityNeeded = source.m_quantityNeeded;
			ut.alocpy(m_description, source.m_description);
			m_linear = source.m_linear;
			m_sku = source.m_sku;
		}

		return *this;
	}

	//Destructor deleting dynamic memory used
	Item::~Item()
	{
		delete[] m_description;
	}

	//Return m_quantityNeeded
	int Item::qtyNeeded(void) const
	{
		return m_quantityNeeded;
	}

	//Return m_currQuantity
	int Item::qty() const
	{
		return m_currQuantity;
	}

	// Return m_description
	const char* Item::desc(void) const
	{
		return m_description;
	}

	// Return m_sku
	int Item::sku(void) const
	{
		return m_sku;
	}

	//Return m_price
	Item::operator double() const
	{
		return m_price;
	}

	//Return true of none of the members are in their empty state
	Item::operator bool() const
	{
		return (m_price != 0 
			&& m_currQuantity != 0 
			&& m_quantityNeeded != 0 
			&& m_description != nullptr 
			&& m_description[0] != '\0'
			&& m_sku != 0);
	}

	//Overloaded -= that subtracts m_currQuantity with qty
	int Item::operator -=(int qty)
	{
		if (m_currQuantity - qty < 0)
		{
			m_currQuantity = 0;
			qty = m_currQuantity;
		}
		else
		{
			m_currQuantity -= qty;
		}

		return qty;
	}

	//Overloaded += that adds m_currQuantity with qty
	int Item::operator +=(int qty)
	{
		m_currQuantity += qty;

		return qty;
	}

	//Sets m_linear to isLinear
	void Item::linear(bool isLinear)
	{
		m_linear = isLinear;
	}

	//Calls m_state.clear()
	void Item::clear()
	{
		m_state.clear();
	}

	//Overloaded == that returns if m_sku is equal to sku
	bool Item::operator ==(const int sku) const
	{
		return (m_sku == sku);
	}

	//Overloaded == that returns if m_description contains substring description
	bool Item::operator ==(const char* description) const
	{
		return (m_description != nullptr && 
			description != nullptr && 
			strstr(m_description, description) != nullptr);
	}

	//Overloaded save from iProduct that writes a line to a file
	ofstream& Item::save(ofstream& ofstr) const
	{
		if (*this)
		{
			ofstr << m_sku << '\t' << m_description << '\t' << m_currQuantity << '\t' << m_quantityNeeded << '\t';
			ofstr.setf(ios::fixed);
			ofstr.precision(2);
			ofstr << m_price;
		}

		return ofstr;
	}

	//Overloaded load that reads file lines
	ifstream& Item::load(ifstream& ifstr)
	{
		int sku, currQuantity, quantityNeeded;
		double price;
		char description[MAX_DESC_LEN];

		if (m_description != nullptr)
		{
			delete[] m_description;
			m_description = nullptr;
		}

		ifstr >> sku;
		ut.extractCharFile(ifstr, '\t');
		ifstr.get(description, MAX_DESC_LEN, '\t');
		ut.extractCharFile(ifstr, '\t');
		ifstr >> currQuantity;
		ut.extractCharFile(ifstr, '\t');
		ifstr >> quantityNeeded;
		ut.extractCharFile(ifstr, '\t');
		ifstr >> price;
		if (ifstr.peek() == '\n')
		{
			ifstr.ignore(1, '\n');
		}

		if (ifstr)
		{
			m_sku = sku;
			m_currQuantity = currQuantity;
			m_quantityNeeded = quantityNeeded;
			m_price = price;
			ut.alocpy(m_description, description);
		}
		else
		{
			m_state = "Input file stream read failed!";
		}

		return ifstr;
	}
	 
	//Overloaded display that displays all info, in either linear form or not
	ostream& Item::display(ostream& cout) const
	{
		int i;

		if (!m_state)
		{
			cout << m_state;
		}
		else
		{
			if (m_linear)
			{
				cout.fill(' ');
				cout.width(5);
				cout << m_sku << " | ";
				cout.width(35);
				//This specifically displays up to 35 characters
				for (i = 0; m_description[i] != '\0' && i != 35; i++)
				{
					cout.width(1);
					cout << left << m_description[i];
				}
				while (i != 35)
				{
					cout << ' ';
					i++;
				}
				cout << " | ";
				cout.width(4);
				cout << right << m_currQuantity << " | ";
				cout.width(4);
				cout << m_quantityNeeded << " | ";
				cout.setf(ios::fixed);
				cout.precision(2);
				cout.width(7);
				cout << m_price << " |";
			}
			else
			{
				cout << "AMA Item:" << endl;
				cout << m_sku << ": " << m_description << endl;
				cout << "Quantity Needed: ";
				cout << m_quantityNeeded << endl;
				cout << "Quantity Available: ";
				cout << m_currQuantity << endl;
				cout << "Unit Price: $";
				cout.setf(ios::fixed);
				cout.precision(2);
				cout << m_price << endl;
				cout << "Needed Purchase Fund: $";
				cout << m_price * (m_quantityNeeded - m_currQuantity) << endl;
			}
		}

		return cout;
	}

	//Overloaded readSku reads sku input
	int Item::readSku(istream& cin)
	{
		m_sku = ut.getint(40000, 99999, "SKU: ");
		cin.clear();
		cin.ignore(1000, '\n');
		return m_sku;
	}

	//Overloaded read reads remaining input
	istream& Item::read(istream& cin)
	{
		char description[MAX_DESC_LEN];
		double price;
		bool valid = false;

		if (m_description != nullptr)
		{
			delete[] m_description;
		}
		clear();

		cout << "AMA Item:" << endl;
		cout << "SKU: " << m_sku << endl;
		cout << "Description: ";
		cin.getline(description, MAX_DESC_LEN, '\n');
		m_quantityNeeded = ut.getint(1, 9999, "Quantity Needed: ");
		m_currQuantity = ut.getint(0, m_quantityNeeded, "Quantity On Hand: ");
		cout << "Unit Price: $";
		//Specific input verifier for double
		do
		{
			cin >> price;
			if (!cin)
			{
				cout << "Invalid number, retry: ";
				cin.clear();
				cin.ignore(1000, '\n');
			}
			else if (price < 0 || price > 9999)
			{
				cout << "Value out of range [0.00<=val<=9999.00]: ";
			}
			else
			{
				valid = true;
			}
		} while (price < 0 || price > 9999 || !valid);
		m_price = price;

		if (!cin)
		{
			cin.setstate(ios::failbit);
			m_state = "Console entry failed!";
		}
		else
		{
			m_description = new char[strlen(description) + 1];
			strcpy(m_description, description);
		}

		return cin;
	}
}