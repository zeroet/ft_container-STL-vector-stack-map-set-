#include "vector.hpp"
#include <vector>
#include <iostream>
#include <string>


int main()
{
	int a[] = {1, 2, 3};

	std::vector<int> v = {1, 2, 3};
	ft::vector<int> myv2(1, 10);

	std::vector<int>::iterator it;
	for (it = v.begin(); it != v.end(); it++)
		std::cout << *it << std::endl;



  ft::vector<int> reserveVector(10, 20);
  reserveVector.reserve(30);
  std::cout << reserveVector.max_size() << std::endl;
  std::cout << reserveVector.capacity() << std::endl;

  ft::vector<int> hi(1);
  if (hi.empty() == false)
	  std::cout << "empty is 0" << std::endl;
  else
	  std::cout << "not empty vector" << std::endl;


  ft::vector<int> foo(3, 10);
  ft::vector<int> bar(10, 3);


  std::cout << foo.at(2) << std::endl;
  std::cout << bar[2] << std::endl;


  std::cout << "Size of foo: " << int(foo.size()) << '\n';
  std::cout << "Size of bar: " << int(bar.size()) << '\n';

	ft::vector<int> myvector;

	myvector.push_back(1);
	myvector.push_back(2);
	myvector.push_back(3);
	myvector.push_back(4);
	myvector.push_back(5);

  std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";

	std::cout << myvector.back() << std::endl;
	std::cout << myvector.front() << std::endl;
	std::cout << myvector[0] << std::endl;
	
	return (0);
}

