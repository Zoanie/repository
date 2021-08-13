//========irst====================================================================
// Name        : next-permutation.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : Smokum if ya gotum
// Description : C++ code problem & solution from leetcode.com
//============================================================================

#include <iostream>
#include <vector>
//#include <math.h>
//#include <mutex>
#include <algorithm>
#include <functional>
#include <bits/stdc++.h>

using namespace std;

/*
 *
Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be in-place (https://en.wikipedia.org/wiki/In-place_algorithm) and use only constant extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.


1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1

Notes:
    An in-place algorithm is an algorithm which transforms input using no auxiliary data structure.
    In-place algorithm updates input sequence only through replacement or swapping of elements

Next permutation algorithm notes: https://www.nayuki.io/page/next-lexicographical-permutation-algorithm

1 - Firstly, identify the longest suffix that is non-increasing (i.e. weakly decreasing). Find this suffix
	by scanning the sequence from right to left. Note that each suffix must have at least one element.

2 - If found, the element immediately to the left of found suffix is known as the pivot. Note that if there
	no such element, then the entire sequence is non-increasing - it is already the last permutation.

		o Find largest index i such that array[i − 1] < array[i].
		  (If no such i exists, then this is already the last permutation.)
		  ex: 54321 (1 < 2, 2 < 3, 3 < 4, 4 < 5)

3 - The pivot is necessarily less than the head of the suffix. So some element in the suffix is greater
	than the pivot. If we swap the pivot with the smallest element in the suffix that is greater than
	the pivot, then the prefix is minimized.

		o Find largest index j such that j ≥ i and array[j] > array[i − 1].
		o Swap array[j] and array[i − 1].

4 - Finally, we sort the suffix in non-decreasing (i.e. weakly increasing) order because we increased the
	prefix, so we want to make the new suffix as low as possible. In fact, we can avoid sorting and simply
	reverse the suffix, because the replaced element respects the weakly decreasing order.

		o Reverse the suffix starting at array[i].
*/

// Functor for find_if()
class NumberIncreasingTest
{
private:
	int lastTestNumber;
	bool firstTest;

public:
	NumberIncreasingTest() { lastTestNumber = 0; firstTest = true; }

	void initTest() { lastTestNumber = 0; firstTest = true; }

	int operator() (int testNum) {

		if(firstTest)
		{
			firstTest = false;
			lastTestNumber = testNum;
			return false;
		}

		//cout << "testing " << num << " < " << last_num << endl;
		if(testNum >= lastTestNumber)
		{
			lastTestNumber = testNum;
			return false;
		}
		return true;
	}
};

class Solution {
private:
	NumberIncreasingTest TestNumberIncreasing;

public:
	Solution() {
	}
    void nextPermutation(vector<int>& numsVec) {
    	int found_index = -1;
    	int rev_index = -1;
    	int fwd_index = -1;

    	displayVector("Input Test Vector", numsVec);

    	TestNumberIncreasing.initTest();
    	/*
    	 * One way to find a number in a vector according to a function:
    	 */
    	//cout << "Vec reverse search first non-increasing number" << endl;
    	auto it = find_if(numsVec.rbegin(), numsVec.rend(), TestNumberIncreasing);
    	if(it != numsVec.rend())
    	{
    		rev_index = std::distance(numsVec.rbegin(), it);
    		//cout << "Found first non-increasing number = " << *it << endl;
    		//cout << "  o Pivot reverse index = " << rev_index << endl;
    		fwd_index = (numsVec.size()-1) - rev_index;
    		//cout << "  o Pivot forward index = " << fwd_index << endl;

    		int pivotNum = numsVec[fwd_index];
    		int swap_index = 0;
        	int smallestGreaterNum = pivotNum;
        	//int found_index = (-1);
        	//auto it = numsVec.end();
        	bool first = true;

    		for(auto it = numsVec.begin()+fwd_index; it != numsVec.end(); it++)
    		{
    			if(*it <= pivotNum)
    				continue;

    			found_index = std::distance(numsVec.begin(), it);

    	    	//cout << "Found nsgn candidate = " << *it << ", index = " << found_index << endl;
    	    	// Test for candidate value to be smallest of all numbers greater than the test number
    	    	if(first)
    	    	{
    	    		first = false;
        	    	//cout << "Setting first nsgn = " << *it << ", index = " << found_index << endl;
    	    		smallestGreaterNum = *it;
    	    		swap_index = found_index;
    	    	}
    	    	else if(*it <= smallestGreaterNum)
    	    	{
        	    	//cout << "Setting new nsgn = " << *it << ", index = " << found_index << endl;
    	    		smallestGreaterNum = *it;
    	    		swap_index = found_index;
    	    	}
    	    }
    		// Next step is to swap the pivot with the smallest element in the suffix that is greater than the pivot
    		// and rightmost/highest index in the suffix
    		//cout << "Swapping numsVec[" << swap_index << "] = numsVec[" << fwd_index << "]" << endl;
    		swap(numsVec[swap_index], numsVec[fwd_index]);
    		//displayVector("Swapped Vector", numsVec);

    		// Final step is to sort the suffix
        	sort(numsVec.begin()+fwd_index+1, numsVec.end(), less<int>());
    		displayVector("Result Next Permutation Vector", numsVec);

    	}
    	else
    	{
    		//cout << "Vector already last permutation" << endl;
        	sort(numsVec.begin(), numsVec.end(), less<int>());
    		displayVector("Result Next Permutation Vector", numsVec);
    	}
    }

    void displayVector(const string name, vector<int>& numsVec)
    {
    	int numCount = numsVec.size();
    	cout << name << endl;
    	for(auto n : numsVec)
    	{
    		cout << n;
    		if(--numCount)
    			cout << ",";
    	}
    	cout << endl;
    }

};

int main() {
	cout << "https://leetcode.com/problems/next-permutation/" << endl;

	//vector<int> test1Vector{3,2,1,7,6,5,4};	// 3241567
	//vector<int> test2Vector{1,2,3};
	//vector<int> test3Vector{0,1,2,5,3,3,0};
	//vector<int> test4Vector{9,8,7,6,5,4};

	vector<int> test1Vector{1,2,3};
	vector<int> test2Vector{3,2,1};
	vector<int> test3Vector{1,1,5};
	vector<int> test4Vector{0,1,2,5,3,3,0};


	Solution Permutation;
//	cout << endl;
	Permutation.nextPermutation(test1Vector);
	cout << endl;
	Permutation.nextPermutation(test2Vector);
	cout << endl;
	Permutation.nextPermutation(test3Vector);
	cout << endl;
	Permutation.nextPermutation(test4Vector);
	cout << endl;

	return 0;
}
