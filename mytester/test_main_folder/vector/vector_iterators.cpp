#include <iostream>
#include <vector>

#include "../main.hpp"

int main ()
{
	//begin, end
	{
		vector<int> myvector;
		for (int i=1; i<=5; i++)
			myvector.push_back(i);

		std::cout << "myvector contains:";
			for (vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
		std::cout << ' ' << *it;
		std::cout << '\n';
	}
	//rbegin, rend
	{
		vector<int> myvector (5);  // 5 default-constructed ints

		int i=0;

		vector<int>::reverse_iterator rit = myvector.rbegin();
		for (; rit!= myvector.rend(); ++rit)
			*rit = ++i;

		std::cout << "myvector contains:";
		for (vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';

	}

  return 0;
}