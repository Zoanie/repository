//============================================================================
// Name        : first-repeating-char.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://www.udemy.com/course/master-the-coding-interview-data-structures-algorithms/learn/lecture/12314712#questions
//============================================================================

#include <iostream>
#include <set>
#include <boost/optional/optional_io.hpp>

using namespace std;

/*
 * Google Question: Return the first recurring number.
 *
 * Given an array = [2,5,1,2,3,5,1,2,4]
 * It should return 2
 *
 * Given an array = [2,1,1,2,3,5,1,2,4]
 * It should return 1
 *
 * Given an array = [2,3,4,5]
 * It should return undefined
 */

int array1[] = {2,5,1,2,3,5,1,2,4};
int array2[] = {2,1,1,2,3,5,1,2,4};
int array3[] = {2,3,4,5};
int array0[] = {};

struct IntArrayArgs {
	int *array;
	int arraySize;
};

boost::optional<int> firstRepeatingNum(int *array, int numElements)
{
	set <int> NumLookupDB;
	int firstRepeatingNumber = 0;

	if(nullptr == array || numElements < 1)
		return boost::optional<int>();

	pair<set<int>::iterator,bool> insertTest;
	for(int idx = 0; idx < numElements; idx++)
	{
		firstRepeatingNumber = array[idx];
		insertTest = NumLookupDB.insert(firstRepeatingNumber);
		if(insertTest.second == false)
			return firstRepeatingNumber;
	}

	return boost::optional<int>();
}

int main() {
	boost::optional<int> retArg;

	cout << "https://www.udemy.com/course/master-the-coding-interview-data-structures-algorithms/learn/lecture/12314712#questions" << endl; // prints https://www.udemy.com/course/master-the-coding-interview-data-structures-algorithms/learn/lecture/12314712#questions

	retArg = firstRepeatingNum(array1, sizeof(array1)/sizeof(int));
	if(!retArg)
		cout << "Array1: Undefined data in input arguments" << endl;
	else
		cout << "Array1: First repeating number is " << retArg << endl;

	retArg = firstRepeatingNum(array2, sizeof(array2)/sizeof(int));
	if(!retArg)
		cout << "Array2: Undefined data in input arguments" << endl;
	else
		cout << "Array2: First repeating number is " << retArg << endl;

	retArg = firstRepeatingNum(array3, sizeof(array3)/sizeof(int));
	if(!retArg)
		cout << "Array3: Undefined data in input arguments" << endl;
	else
		cout << "Array3: First repeating number is " << retArg << endl;


	return 0;
}
