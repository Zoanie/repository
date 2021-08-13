//============================================================================
// Name        : binary-search.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://www.geeksforgeeks.com/binary-search/
//============================================================================

// C++ program to implement recursive Binary Search
#include <bits/stdc++.h>
using namespace std;

// A recursive binary search function. It returns the arr[] index location
// of search element x in given array arr[left_index...right_index], if present,
// otherwise -1
int recursiveBinarySearch(int arr[], int left_index, int right_index, int x)
{
	// Search as long as the right index is >= to the left index - otherwise x is not present
	if (right_index >= left_index) {
		int mid = left_index + (right_index - left_index) / 2;

		// If x is present at the middle
		if (x == arr[mid])
			return mid;

		// If x is smaller than mid, then
		// it can only be present in left subarray
		if (x < arr[mid]) {
			// change right index to mid - 1
			return recursiveBinarySearch(arr, left_index, mid - 1, x);
		}
		else {  // Else x can only be present in right subarray
			// change left index to mid + 1
			return recursiveBinarySearch(arr, mid + 1, right_index, x);
		}
	}

	// We reach here when x is not present in the array
	return -1;
}

// A iterative binary search function. It returns the arr[] index location
// of search element x in given array arr[left_index...right_index], if present,
// otherwise -1
int iterativeBinarySearch(int arr[], int left_index, int right_index, int x)
{
	// Search as long as the right index is >= to the left index - otherwise x is not present
	while (right_index >= left_index) {
		int mid = left_index + (right_index - left_index) / 2;

		// If x is present at the middle
		if (arr[mid] == x)
			return mid;

		// If x is smaller than mid, then
		// it can only be present in left subarray
		if (x < arr[mid]) {
			// change right index to mid - 1
			right_index = mid -1;
		}
		else {  // Else x can only be present in right subarray
			// change left index to mid + 1
			left_index = mid + 1;
		}
	}

	// We reach here when x is not present in the array
	return -1;
}

// Inserts a key in arr[] of given capacity. n is current
// size of arr[]. This function returns n+1 if insertion
// is successful, else n.
int insertSorted(int arr[], int n, int key, int capacity)
{
    // Cannot insert more elements if n is already
    // more than or equal to capcity
    if (n >= capacity)
        return n;

    int i;
    for (i = n - 1; (i >= 0 && arr[i] > key); i--)
        arr[i + 1] = arr[i];

    arr[i + 1] = key;

    return (n + 1);
}

int binarySearch(vector<int>vec, int key)
{
int l,mid,h;
	l=0;
	h=vec.size()-1;
	while(l<=h)
	{
		// Note: using mid = (l+h)/2 will cause an overflow if the sum l+h is greater than INT_MAX
		//
		mid=l + ((h-l)/2);
		if(key==vec[mid])
			return mid;
		else if(key<vec[mid])
			h=mid-1;
		else
			l=mid+1;
	}
	return -1;
}

int main(void)
{
	int arr[20] = { 2, 3, 4, 10, 40, 45, 51, 63, 64, 75, 90, 99 };
	int capacity = sizeof(arr) / sizeof(arr[0]);
	int num_elements = 12;
	int insert_key = 48;
	int search_key = 64;

	cout<< "\nBefore Insertion: ";
	for (int i = 0; i < 12; i++)
		cout << arr[i] << " ";
	cout << endl;

	int result = recursiveBinarySearch(arr, 0, num_elements - 1, search_key);
	(result == -1) ? cout << "Recursive Binary Search finds element " << search_key << " is not present in array"
			: cout << "Recursive Binary Search finds element " << search_key << " is present at index " << result << endl;

	// Inserting key
	cout << "\nInserting key " << insert_key << endl;
	num_elements = insertSorted(arr, num_elements, insert_key, capacity);

	cout << "\nAfter Insertion: ";
	for (int i = 0; i < num_elements; i++)
		cout << arr[i]<< " ";
	cout << endl;


	result = iterativeBinarySearch(arr, 0, num_elements - 1, search_key);
	(result == -1) ? cout << "Iterative Binary Search finds element " << search_key << " is not present in array"
			: cout << "Iterative Binary Search finds element " << search_key << " is present at index " << result << endl;
	return 0;
}
