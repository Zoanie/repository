//============================================================================
// Name        : geeks-output-testing.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include<iostream>
using namespace std;

/*
 * In C++, scope resolution operator is ::. It is used for following purposes
 * 1) To access a global variable when there is a local variable with same name:
 * 2) To define a function outside a class.
 * 3) To access a class’s static variables.
 * 4) In case of multiple Inheritance:
 * 5) For namespace.
 */

int x = 10;
void fun()
{
	int x = 2;
	{
		int x = 1;
		// (1) Access to a global variable when there is a local variable with the same name
		cout << "global x=" << ::x << ", local x=" << x << endl;
	}
	::x = x;
}

class A
{
protected:
    int x;
public:
    A() { x = 10; }
   // Only function
   void fun();
};

class B
{
protected:
    int x;
public:
    B() { x = 20; }
};

class C: public A, public B
{
public:
   void fun()
   {
	  // (4) Use of scope resolution operator in multiple inheritance.
      cout << "A's x is " << A::x << endl;
      cout << "B's x is " << B::x << endl;
   }
};
// (2) Definition outside class using ::
void A::fun()
{
   cout << "fun() called";
}

// (3) Access to a class' static variables:
class Test
{
    static int x;
    int private_z;

public:
    static int y;

    Test(int z = 0)
	{
    	private_z = z;
    	y++;
    	cout << "Test ctor #" << y << ",  z=" << z << endl;
	}

    // Local parameter input variable 'x' hides class member
    // 'x', but we can access it using ::
    void func(int x)
    {
       // We can access class's static variable
       // even if there is a local variable
       cout << "Value of static x is " << Test::x << endl;
       cout << "Value of static y is " << y << endl;
       cout << "Value of local x is " << x << endl;
    }
};

class Example2 {
  public:
    int total;
    Example2 (int initial_value) : total(initial_value) { };
    void accumulate (int x) { total += x; };
};

// In C++, static members must be explicitly defined
// like this
int Test::x = 1;
int Test::y = 0;

int main() {

    char *A[] = { "abcx", "dbba", "cccc"};
    //char varA = *(A+1);
    //char varB = *A+1;
    char var = *(A+1) - *A+1;

    cout << (*A + var);
    return 0;
	//cout << "https://www.geeksforgeeks.org/output-of-c-program-set-1/?ref=lbp" << endl; // prints https://www.geeksforgeeks.org/output-of-c-program-set-1/?ref=lbp
	fun();
	C c;
	c.fun();
	Test t[5];

	t[3] = 24;

	t[45].func(45);
	return 0;
}
