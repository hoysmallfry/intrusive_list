#include <utility>

#include <iostream>

#include "intrusive/list_hook.hpp"
#include "intrusive/list.hpp"

class test_object:
	public intrusive::list_hook<void>
{
public:
	test_object(int pData) :
	  mData(std::move(pData))
	  {}

	int data() const
	{
		return mData;
	}
	void data(int pValue)
	{
		mData = std::move(pValue);
	}

private:
	int mData;
};

// standard compliant insertion operator prints out a test object given.
std::ostream& operator << (std::ostream& pStream, test_object& pObject)
{
	if(!pStream)
		throw std::exception("Bad stream.");

	pStream << pObject.data();

	return pStream;
}

int main()
{
	try
	{
		intrusive::list<test_object, void> testObjects;

		// anonymous scope. x, y, and z will die after this scope.
		{
			test_object x(4);
			test_object y(52);
			test_object z(0);

			std::cout << "Start: " << testObjects << "\n";

			// manually push x, y, z into the intrusive list.
			testObjects.push_back(x);
			testObjects.push_back(y);
			testObjects.push_back(z);

			std::cout << "After Insertion: " << testObjects << "\n";

			// x is manually removed.
			testObjects.remove(x);

			std::cout << "After Removal: " << testObjects << "\n";
		}

		std::cout << "After Intrusion: " << testObjects << "\n";
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what();
	}

	return 0;
}
