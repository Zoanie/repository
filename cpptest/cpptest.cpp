/*
 * cpptest.cpp
 *
 *  Created on: Aug 1, 2020
 *      Author: Carlos Navarrette
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>      // ifstream, ofstream, filebuf
#include <cstdint>
#include <boost/lexical_cast.hpp>	// requires installation: sudo apt-get install libboost-all-dev
#include <map>
#include <deque>

using namespace std;

/* Given a positive integer N. The task is to calculate the factorial of N.
 *

 Input:
 The first line contains an integer 'T' denoting the total number of test cases.
 T testcases follow. In each test cases, it contains an integer 'N'.

 Output:
 For each testcase in a new line, print the factorial of N.

 Constraints:
 1 <= T <= 19
 0 <= N <= 18

 Example:
 Input:
 2
 1
 4

 Output:
 1
 24
 */

// Used for command line testing
void usage()
{
    cout << "Usage: ./cpptest <number test cases T, (1 <= T <= 19)> <test inputs: N1 N2 N3...NT, (0 <= N <= 18)" << endl;
}

// Test constraint: 0 <= N <= 18
uint64_t factorial(uint64_t n)
{
  if(0 == n)
	return 1;
  if(n < 0 || n > 18)
  {
	cout << "Test constraint violation, factorial number N out of range, (0 <= N <= 18)" << endl;
    return -5;
  }

  return (n*factorial(n-1));
}

// Save input arguments to file named after executable with '.txt' extension
string writeArgsToFile(int argc, char **argv)
{
ofstream ofs;
string fext = ".txt";
string fname(argv[0] + fext);

  ofs.open(fname);
  if(ofs)
  {
    for(int line=0; line<argc; line++)
    {
      ofs << *argv++ << endl;
    }
  }
  ofs.close();
  return fname;
}

class Base {
	string base_classname;
	public:

	Base(string name = "Hola") {
		base_classname = name;
		cout<<"Hola Base\n";
	}
	void f()
	{ cout<<"f() Base\n";
	}
	void g()
	{ cout<<"g() Base\n";
	}
	virtual void h()
	{ cout<<"virtual h() Base\n";
	}
	virtual ~Base()
	{
		cout<<"Adios Base\n";
	}
};

class Derived: public Base
{
	string derived_classname;
	public:
	Derived (string name="Laba Diena") : Base("D" + name)
	{
		derived_classname = name;

		cout<<"Derived sez " << derived_classname << endl;
	}
	void f() {
		cout<<"f() Derived\n";
	};
	void g()
	{ cout<<"g() Derived\n";
	}
	virtual void h()
	{ cout<<"***********virtual h() Derived**********\n";
	}
	virtual ~Derived()
	{
		cout<<"Adios Derived\n";
	}
};



int main(int argc, char *argv[])
{
	cout << "Create Derived obj..." << endl;
	Derived obj;
	cout << "Call Base obj f()..." << endl;
	obj.Base::f();

	cout << "Create Derived obj2..." << endl;
	Derived obj2;
	cout << "Create Base pointer to  obj2..." << endl;
	Base *pbase = &obj2;

	cout << "Call Base->f()..." << endl;
	pbase->f();
	cout << "Call Base->g()..." << endl;
	pbase->g();
	cout << "Call Base->h()..." << endl;
	pbase->h();

	cout << "Call (Derived obj2)->h()..." << endl;
	obj2.f();
	cout << "Call (Derived obj2)->h()..." << endl;
	obj2.g();
	cout << "Call (Derived obj2)->h()..." << endl;
	obj2.h();

	cout << "Closing the show..." << endl;
	return 0;

	int T = 0;
	int N = 0;
	string fline;
	ifstream ifs;
	string fname;

    // This program is designed to receive input data from command line or std input.
    // If the number of input arguments is less that 3, then assume command line input.
	if(argc < 3)
	{
		// read from std input
		getline(cin, fline);
	}
	else
	{
		// Setup to read input arguments from the command line.
		fname = writeArgsToFile(argc, argv);

		ifs.open(fname);

		// first argument is the executable filename, we can skip over it
		getline(ifs, fline);

		// second argument is the number of test cases T
		getline(ifs, fline);
	}

	try {
		T = boost::lexical_cast<int>(fline);
	}
	catch (boost::bad_lexical_cast &e) {
		cout << "Exception caught : " << e.what() << endl;
		if(ifs.is_open())
		{
			ifs.close();
		}
		exit(-2);  // s/b a def
	}

	if(1 > T || 19 < T)
	{
		cout << "Test constraint violation. Number tests cases T out of range, (1 <= T <= 19)" << endl;
		usage();
		if(ifs.is_open())
		{
			ifs.close();
		}
		return (-3);  // s/b a def
	}

	uint64_t Nfactorial = 0;
	// not a good choice: map<int, uint64_t> testResult;
    deque<pair<int, uint64_t> > testResult;

    // Pushing elements inside
    // the queue container
	int numTests = T;

	while(numTests--)
	{
		if(argc < 3)
			getline(cin, fline);
		else
			getline(ifs, fline);

		try {
			N = boost::lexical_cast<int>(fline);
		}
		catch (boost::bad_lexical_cast &e) {
			cout << "Exception caught : " << e.what() << endl;
			if(ifs.is_open())
			{
				ifs.close();
			}
			exit(-4);  // s/b a def
		}

		// Uses recursion
		Nfactorial = factorial((uint64_t)N);

		testResult.push_back(pair<int, uint64_t>(N, Nfactorial));

	}

    /*
     * Input check
	cout << "Input:" << endl;
	cout << T << endl;
	for(auto& key_and_val : testResult) {
		cout << key_and_val.first << endl;
	}
	cout << endl;
	*/

	//cout << "Output:" << endl;
	for(auto& key_and_val : testResult) {
		cout << key_and_val.second << endl;
	}

	if(ifs.is_open())
	{
		ifs.close();
	}

	return 0;
}
