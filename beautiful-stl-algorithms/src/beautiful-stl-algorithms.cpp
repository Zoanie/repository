//============================================================================
// Name        : beautiful-stl-algorithms.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://app.pluralsight.com/library/courses/beautiful-cplusplus-stl-algorithms/
//============================================================================
#define TIME_SENSITIVE_COMPILE 1

#ifdef TIME_SENSITIVE_COMPILE
/* compiling with bits include takes 753ms */
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <limits.h>
#else
/* compiling with bits include takes 1.753ms */
#include <bits/stdc++.h>
#endif

using namespace std;

/* Creating and Filling Collections */
/*
 * fill(), file_()
 * iota()
 * generate()
 * generate_n()
 * replace()
 * replace_if()
 * transform()
 */
int create_and_fill(vector<int>& vA) {
	cout << "Create & Fill STL Algorithms" << endl;

	// Fills the range [first,last) with copies of value
	fill(begin(vA), end(vA), 41);
	cout << "fill(start, end, 41) vA[] =          ";
	for(auto e : vA)
		cout << "[" << e << "]";
	cout << endl;

	// Fills the range [first,first+n) with copies of value
	cout << "fill_n(start, start+6, 42) vA[] =    ";
	fill_n(begin(vA), 6, 42);
	for(auto e : vA)
		cout << "[" << e << "]";
	cout << endl;

	// Assign the result of a function object to each value in a sequence
	cout << "generate(start, end, fcn) vA[] =     ";
	int start = 10;
	generate(begin(vA), end(vA), [&start](){return start--;});
	for(auto e : vA)
		cout << "[" << e << "]";
	cout << endl;

	// Assign the result of a function object to each value in a sequence
	cout << "generate_n(start, end, fcn) vA[] =   ";
	start = 3;
	generate_n(begin(vA), 7, [&start](){return start *= 2;});
	for(auto e : vA)
		cout << "[" << e << "]";
	cout << endl << endl;

	return 0;
}

/*
 * Replacing Values
 *
 * replace()
 * replace_if()
 */
int replace_values(vector<int>& vA)
{
	cout << "Replace Values STL Algorithms" << endl;

	// Replace each occurrence of one value in a sequence with another
	replace(begin(vA), end(vA), 96, 818);
	cout << "replace(start, end, val, replace) vA[] =  ";
	for(auto e : vA)
		cout << "[" << e << "]";
	cout << endl;

	replace_if(begin(vA), end(vA), [](int elem){return elem < 50;}, 101);
	cout << "replace_if(start, end, fcn) vA[] =        ";
	for(auto e : vA)
		cout << "[" << e << "]";
	cout << endl << endl;

	return 0;
}

/*
 * Transform Values
 *
 * iota()
 * transform()
 */
int transform_values()
{
	cout << "Transform Values STL Algorithms" << endl;
	vector<int> vA(10);
	vector<int> vB(10);

	// Create a range of sequentially increasing values
	iota(begin(vA), end(vA), 1);
	iota(begin(vB), end(vB), 11);
	cout << "iota(start, end, init) vA[] =                ";
	for(auto e : vA)
		cout << "[" << e << "]";
	cout << endl;

	// Perform an operation on a sequence
	transform(begin(vA), end(vA), begin(vA), [](int elem){return elem *2;});
	cout << "transform(start, end, dest, fcn(vA*2) vA[] = ";
	for(auto e : vA)
		cout << "[" << e << "]";
	cout << endl;

	vector<int> vC(10);
	transform(begin(vA), end(vA), begin(vB), begin(vC), [](int elem1, int elem2){return elem1 - elem2;});
	cout << "transform(vA, vAend, vB, vC, fcn(vA-vB))" << endl;
	cout << "vA[] = ";
	for(auto e : vA)
		cout << "[" << e << "]";
	cout << endl;
	cout << "vB[] = ";
	for(auto e : vB)
		cout << "[" << e << "]";
	cout << endl;
	cout << "vC[] = ";
	for(auto e : vC)
		cout << "[" << e << "]";
	cout << endl << endl;

	return 0;
}

/*
 * Eliminate Duplicates
 *
 * unique()
 */
int elimate_duplicates()
{
	cout << "Eliminate Duplicates Values STL Algorithms" << endl;
	vector<int> vA {1,2,3,3,3,6,7,7,7,10,10,12};
	cout << "vA[" << vA.size() << "] = ";
	for(auto e : vA)
		cout << "[" << e << "]";
	cout << endl;

	// Remove consecutive duplicate values from a sequence
	// Note fcn cannot alter the size of the container.
	// The indication of the new shortened range is the return iterator that is the new past-the-end element
	auto itAend = unique(begin(vA), end(vA));
	cout << "unique(vA, vAend)" << endl;
	cout << "vA[" << vA.size() << "] = ";
	for(auto it = begin(vA); it != itAend; ++it )
		cout << "[" << *it << "]";
	cout << endl;

	// Erase the old unused elements to resize the vector
	vA.erase(itAend, end(vA));
	cout << "erase(unique(vA...), vAend)" << endl;
	cout << "vA[" << vA.size() << "] = ";
	for(auto it = begin(vA); it != itAend; ++it )
		cout << "[" << *it << "]";
	cout << endl;
	//unique_copy(begin(vB))

	return 0;
}

int removeDuplicates(vector<int>& nums) {
    auto itEnd = unique(begin(nums), end(nums));

    nums.erase(itEnd, end(nums));

    return nums.size();
}

/*
 * Reverse and Swap
 *
 * reverse()
 * iter_swap()
 * reverse_copy()
 */
int reverse_and_swap()
{
string sentance = "Hello world!";
string orig(sentance.size(), 'x');
vector<int> vA(10);

	// Reverse a sequence
	cout << "Reversing a sequence container (string)" << endl;
	cout << "Before reverse, string = '" << sentance << "'" << endl;
	reverse(begin(sentance), end(sentance));
	cout << "After reverse, string = '" << sentance << "'" << endl << endl;

	// Swap the beginning value with the end value of a sequence
	iota(begin(vA), end(vA), 1);
	cout << "Swapping values in a sequence" << endl;
	cout << "Before swap, vA[" << vA.size() << "] = ";
	for(auto e : vA)
		cout << "[" << e << "]";
	cout << endl;
	iter_swap(begin(vA), end(vA)-1);
	cout << "After swap,  vA[" << vA.size() << "] = ";
	for(auto e : vA)
		cout << "[" << e << "]";
	cout << endl << endl;

	cout << "Reverse copy a sequence" << endl;
	cout << "Before reverse, string = '" << sentance << "'" << endl;
	reverse_copy(begin(sentance), end(sentance), begin(orig));
	cout << "After reverse, string = '" << orig << "'" << endl << endl;
	return 0;

}

/*
 * https://medium.com/swlh/using-sliding-window-technique-to-solve-coding-interview-questions-248b67ae3c44
 * Given an array of integers and a number k.
 * Return the highest sum of any k consecutive elements in the array
 *
Input: arr = [1, 5, 2, 3, 7, 1], k = 3
Output: 12 (the sum of subarray [2, 3, 7])

Input: arr = [5, -3, 7, -6, 8], k = 2
Output: 4 (the sum of subarray [-3, 7])

Input: arr = [5, -3, 7, -6, 8], k = 3
Output: 9 (the sum of subarray [5, -3, 7] or [7, -6, 8])
 *
 * The Sliding Window Approach
 *
 * When a window slides, only two elements change.
 * The oldest one drops off, and the newest one comes into the frame.
 */
int sliding_window_technique(int arr[], int n, int k)
{
	int highest_sum = INT_MIN;
	int test_sum = 0;

	int idxLastKelements = n - k + 1;

	// The brute force approach
	for(int i=0; i<idxLastKelements; i++) {
		int test_sum = accumulate(arr+i, arr+i+k, 0);
		highest_sum = max(highest_sum, test_sum);
	}
	cout << "Brute force approach = " << highest_sum << endl;

	// The sliding window approach
	test_sum = accumulate(arr, arr+k, 0);
	int last_element = 0;
	int new_element = 0;
	for(int i=0; i<idxLastKelements; i++) {
		test_sum = test_sum - last_element + new_element;
		last_element = arr[i];
		new_element = arr[i+k+1];
		highest_sum = max(highest_sum, test_sum);
	}

	return highest_sum;
}

int main() {
	cout << "https://app.pluralsight.com/library/courses/beautiful-cplusplus-stl-algorithms/" << endl << endl;
	elimate_duplicates();
	return 0;
	vector<int> vA(10);

	create_and_fill(vA);
	replace_values(vA);
	transform_values();
	elimate_duplicates();
	reverse_and_swap();
	int arr1[] = {1, 5, 2, 3, 7, 1, 4, -2, 9, 3, 1, 3, 6, 14, -3, -1, 5, 9, 7};
	int k = 3;
	int n = sizeof(arr1) / sizeof(int);
	int max_sum = sliding_window_technique(arr1, n, k);
	cout << "Sliding Window max sum = " << max_sum << endl;

}
