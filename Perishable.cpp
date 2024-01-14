
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Utils.h"
#include "Perishable.h"

using namespace std;

namespace sdds
{
	//Default constructor setting members to empty state
	Perishable::Perishable() : Item()
	{
		m_instruction = nullptr;
		m_expiry.formatted(false);
	}

	//Copy constructor, also calling base Item constructor, which calls the copy assignment operator
	Perishable::Perishable(const Perishable& source) : Item(source)
	{
		m_instruction = nullptr;
		*this = source;
	}

	//Copy assignment operator that copies all resources and members over
	Perishable& Perishable::operator =(const Perishable& source)
	{
		if (this != &source)
		{
			(Item&)*this = source;
			m_expiry = source.m_expiry;
			ut.alocpy(m_instruction, source.m_instruction);
		}

		return *this;
	}

	//Destructor deallocating dynamic memory
	Perishable::~Perishable()
	{
		delete[] m_instruction;
	}

	//Returns constant Date m_expiry
	const Date& Perishable::expiry(void) const
	{
		return m_expiry;
	}

	//Overloaded readSku that reads a different sku compared to Item
	int Perishable::readSku(istream& cin)
	{
		m_sku = ut.getint(10000, 39999, "SKU: ");
		cin.clear();
		cin.ignore(1000, '\n');

		return m_sku;
	}

	//Overloaded save, which calls base save first, then reads the rest of the data from the file
	ofstream& Perishable::save(ofstream& ofstr) const
	{
		Item::save(ofstr);
		ofstr << '\t';
		if (m_instruction != nullptr && m_instruction[0] != '\0')
		{
			ofstr << m_instruction;
		}
		ofstr << '\t' << m_expiry;

		return ofstr;
	}

	//Overloaded load that calls base Item load, then prompts input for thr rest
	ifstream& Perishable::load(ifstream& ifstr)
	{
		char instruction[MAX_INSTRUCTION_LEN];
		Date expiry;

		instruction[0] = '\0';
		Item::load(ifstr);
		ut.extractCharFile(ifstr, '\t');
		if (ifstr.peek() != '\t')
		{
			ifstr.get(instruction, MAX_INSTRUCTION_LEN, '\t');
		}
		else if (ifstr.peek() == '\t')
		{
			if (m_instruction != nullptr)
			{
				delete[] m_instruction;
				m_instruction = nullptr;
			}
			ut.extractCharFile(ifstr, '\t');
		}
		ifstr >> expiry;
		ut.extractCharFile(ifstr, '\n');

		if (ifstr)
		{
			if (instruction[0] != '\0')
			{
				ut.alocpy(m_instruction, instruction);
			}
			m_expiry = expiry;
		}
		else
		{
			m_state = "Input file stream read (perishable) failed!";
		}

		return ifstr;
	}

	//Overloaded display that calls Base Item display, the display the rest of the info
	ostream& Perishable::display(ostream& cout) const
	{
		Date tempDate = m_expiry;
		tempDate.formatted(true);

		if (m_instruction == nullptr && !m_state)
		{
			cout << m_state;
		}
		else
		{
			if (linear())
			{
				cout.fill(' ');
				Item::display(cout);
				if (m_instruction != nullptr && m_instruction[0] != '\0')
				{
					cout << "*";
				}
				else
				{
					cout << ' ';
				}
				cout << tempDate;
			}
			else
			{
				cout << "Perishable ";
				Item::display(cout) << "Expiry date: ";
				cout << tempDate;
				if (m_instruction != nullptr && m_instruction[0] != '\0')
				{
					cout << endl << "Handling Instructions: " << m_instruction;
				}
				cout << endl << endl;;
			}
		}

		return cout;
	}

	//Overloaded read that calls base Item read, then prompts for other fields
	istream& Perishable::read(istream& cin)
	{
		char instruction[MAX_INSTRUCTION_LEN];

		Item::read(cin);
		delete[] m_instruction;
		m_instruction = nullptr;
		m_expiry.formatted(true);
		cout << "Expiry date (YYMMDD): ";
		m_expiry.formatted(false);
		m_expiry.read(cin);
		cin.ignore(1000, '\n');
		cout << "Handling Instructions, ENTER to skip: ";
		if (cin.peek() != '\n')
		{
			cin.get(instruction, MAX_INSTRUCTION_LEN, '\n');
			ut.alocpy(m_instruction, instruction);
		}
		else
		{
			m_instruction = nullptr;
		}

		if (!cin)
		{
			m_state = "Perishable console date entry failed!";
			cout << endl << m_state << endl;
		}
		cout << endl;
		return cin;
	}
}