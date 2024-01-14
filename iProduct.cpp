
#include <iostream>
#include "iProduct.h"

using namespace std;

namespace sdds
{
	//Blank destructor, purpose is just to have virtual enabling the correct destructor to be called
	iProduct::~iProduct()
	{
		;
	}

	//Returns display function call
	ostream& operator <<(ostream& cout, const iProduct& source)
	{
		return (source.display(cout));
	}

	//Returns read function call
	istream& operator >>(istream& cin, iProduct& destination)
	{
		return (destination.read(cin));
	}
}