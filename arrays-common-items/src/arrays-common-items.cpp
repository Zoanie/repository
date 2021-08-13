//============================================================================
// Name        : arrays-common-items.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://www.udemy.com/course/master-the-coding-interview-data-structures-algorithms/learn/lecture/12214986#questions\n" << endl; // prints https://www.udemy.com/course/master-the-coding-interview-data-structures-algorithms/learn/lecture/12214986#questions

//============================================================================

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <bits/stdc++.h>
#include <boost/timer/timer.hpp>
//#include <boost/progress.hpp>

using namespace std;
using namespace boost::timer;

/*
 * Given 2 arrays, create a function that let's a user know (true/false) whether
 * these two arrays contain any common items.
 */
//const char array1[] = {'a', 'b', 'c', 'x', 'l', 'm', 'n', '1', '3', '5', '7','9'};
//const char array2[] = {'9', 'z', 'y', 'x', 'p', 'd', 'q', 'r', 't', 'u', '3'};
//const char array2[] = {'2', '4', '6', '8', 'p', 'd', 'q', 'r', 't', 'u', 'v'};
//char array1[10000] = {'a'};
//char array2[8000] = {'0'};

/*
 * Another idea...
 * We could use a list of bit masks in an array to represent each ascii table character.
 * There are 128 printable characters in the ascii table.  We can convert each element
 * in the array to a single bit in a 128bit object.
 */

class BitIndex
{
private:
#define BIT_MASK_SIZE	128
    bitset<BIT_MASK_SIZE> BitLookupObj;

public:
    size_t bitIndexSize()
    {
    	return BitLookupObj.size();
    }
    void setBitIndex(int bitIndex)
    {
    	BitLookupObj.set(bitIndex);
    }
    bool isBitIndexSet(const int bitIndex)
    {
    	return BitLookupObj.test(bitIndex);
    }
    bool isAnyBitSet()
    {
    	return BitLookupObj.any();
    }
    size_t findFirstBitSet()
    {
    	return BitLookupObj._Find_first();
    }
    size_t findNextBitSet(size_t previousBit)
    {
    	return BitLookupObj._Find_next(previousBit);
    }
};

/*
 * This is a different way to manage a bitmap
 * https://lemire.me/blog/2018/02/21/iterating-over-set-bits-quickly/
 */
#define BITMAP_SIZE		8
size_t bitmapsize = BITMAP_SIZE;
uint64_t bitmap[BITMAP_SIZE];

void displayBitmap()
{
	uint64_t bitset=0;
	for (size_t k = 0; k < bitmapsize; ++k) {
		bitset = bitmap[k];
		cout << "bitmap[" << k << "] = " << "0x" << hex << bitset << endl;

	    uint64_t lowestbit = bitset & -bitset;
		cout << "lowestbit = " << "0x" << hex << bitset << " & " << "0x" << (-bitset) << " = 0x" << lowestbit << endl;

		size_t p = k * 64;
		while (bitset != 0) {
			if (bitset & 0x1) {
				// callback(p);
				cout << p;
				if(bitset > 0x01)
					cout << hex << ", ";
			}
			bitset >>= 1;
			p += 1;
		}
		cout << endl;
	}
}

int main()
{
	// These are the input arrays they could be external

#define ARRAY1_SIZE	100000
#define ARRAY2_SIZE 80000

	char *array1 = new char[ARRAY1_SIZE];
	char *array2 = new char[ARRAY2_SIZE];

	if(array1 == nullptr) cout << "Unable to initialize array1" << endl;
	if(array2 == nullptr) cout << "Unable to initialize array2" << endl;

	/* little test to reverse a string
	const char *greeting = "Hi My name is Andrei";
	int greetingLen = strlen(greeting);
	char revGreeting[80];

	cout << "C-String '" << greeting << "' reversed is ";

	for(int idx=0; idx<greetingLen; idx++)
		revGreeting[greetingLen-1-idx] = greeting[idx];
	revGreeting[greetingLen] = 0;

	cout << "'" << revGreeting << "'" << endl;

	memset(bitmap, 0, sizeof(bitmap));

	bitmap[0] = 0x18;
	displayBitmap();
	*/

	// These are the item container objects
	BitIndex ItemLookupDb;
	unordered_set <char> barn;

	bool foundCommonItems = false;
	char key = 0;
	char keyFound = 0;

	int array1Items = ARRAY1_SIZE;
	int array2Items = ARRAY2_SIZE;

	for(int idx=0; idx<array1Items; idx++)
	{
		if(idx & 0x01)
			array1[idx] = 'z';
		else
			array1[idx] = 'a';

	}
	for(int idx=0; idx<array2Items; idx++)
		array2[idx] = 'a';

	array2[4000] = 'z';
	array2[2000] = 'a';

	cout << "https://www.udemy.com/course/master-the-coding-interview-data-structures-algorithms/learn/lecture/12214986#questions\n" << endl; // prints https://www.udemy.com/course/master-the-coding-interview-data-structures-algorithms/learn/lecture/12214986#questions

	cpu_timer timer;

	for(int idx=0; idx<array1Items; idx++)		// O(n)
	{
		barn.insert(array1[idx]);				// O(1)
	}

	for(int idx=0; idx<array2Items; idx++)		// O(m)
	{
		key = array2[idx];
		if(barn.find(key) != barn.end())		// O(m)
		{
			keyFound = key;
			foundCommonItems = true;
		}
	}
	cout << "Hash table runtime: " << timer.format(3);

	if(foundCommonItems)
	{
		cout << "Hash table lookup found item " << keyFound << " is common to both arrays\n" << endl;
	}
	else
	{
		cout << "Hash table lookup found no common items between arrays" << endl;
	}

	foundCommonItems = false;

	timer.start();

	for(int idx=0; idx<array1Items; idx++)		// O(n)
	{
		key = array1[idx];
		ItemLookupDb.setBitIndex(key);
	}

	for(int idx=0; idx<array2Items; idx++)		// O(n)
	{
		key = array2[idx];
		if(ItemLookupDb.isBitIndexSet(key))
		{
			keyFound = key;
			foundCommonItems = true;
		}
	}

	cout << "Bitmap loop runtime: " << timer.format(3);

	if(foundCommonItems)
	{
		cout << "Bitmap lookup found item " << keyFound << " is common to both arrays" << endl;
	}
	else
	{
		cout << "Bitmap lookup found no common items between arrays" << endl;
	}

	size_t firstBitSet = ItemLookupDb.findFirstBitSet();
	size_t bitmapSize = ItemLookupDb.bitIndexSize();
	size_t nextBitSet = firstBitSet;
	cout << "First bit set in bitmap is " << firstBitSet << endl;
	cout << "Number of bits in bitmap is " << bitmapSize << endl;
	while(nextBitSet < bitmapSize)
	{
		cout << "Bit " << nextBitSet << " is set in bitmap" << endl;
		nextBitSet = ItemLookupDb.findNextBitSet(nextBitSet);
	}


	return foundCommonItems;
}
