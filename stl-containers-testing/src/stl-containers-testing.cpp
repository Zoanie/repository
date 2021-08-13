//============================================================================
// Name        : stl-containers-testing.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : Hello World in C++, Ansi-style
//============================================================================

// C++ STL list, unique()

#include <list>
#include <iostream>

using namespace std;



int main(void)
{
	cout << "https://www.tenouk.com/cpluscodesnippet/" << endl; // prints https://www.tenouk.com/cpluscodesnippet/

	// container
	list <int> ls1;

	// iterators
	list <int>::iterator ls1Iter, ls2Iter, ls3Iter;

	not_equal_to<int> mypred;


	// push/insert data
	ls1.push_back(-12);
	ls1.push_back(12);
	ls1.push_back(12);
	ls1.push_back(22);
	ls1.push_back(22);
	ls1.push_back(13);
	ls1.push_back(-12);
	ls1.push_back(14);



	// print the data and do some operations
	cout<<"ls1 data, the initial list: ";
	for(ls1Iter = ls1.begin(); ls1Iter != ls1.end(); ls1Iter++)
		cout<<" "<<*ls1Iter;
	cout<<endl;

	cout<<"\nOperation1: list <int> ls2 = ls1;"<<endl;
	cout<<"Operation2: ls2.unique();"<<endl;
	list <int> ls2 = ls1;
	ls2.unique();

	cout<<"ls2 data, after removing successive duplicate elements: ";
	for(ls2Iter = ls2.begin(); ls2Iter != ls2.end(); ls2Iter++)
		cout<<" "<<*ls2Iter;
	cout<<endl;

	cout<<"\nOperation1: list <int> ls3 = ls2;"<<endl;
	cout<<"Operation2: ls3.unique(mypred);"<<endl;
	list <int> ls3 = ls2;
	ls3.unique(mypred);

	cout<<"ls3 data, after removing successive unequal elements: ";
	for(ls3Iter = ls3.begin(); ls3Iter != ls3.end(); ls3Iter++)
		cout<<" "<<*ls3Iter;
	cout<<endl;

	return 0;

}
