//============================================================================
// Name        : quicksort.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://www.udemy.com/course/datastructurescncpp/learn/lecture/13191520#questions/12460534
//============================================================================

#include <iostream>

using namespace std;

template <class T>
void Print(T& vec, int n, string s){
    cout << s << ": [" << flush;
    for (int i=0; i<n; i++){
        cout << vec[i] << flush;
        if (i < n-1){
            cout << ", " << flush;
        }
    }
    cout << "]" << endl;
}

void swap(int* x, int* y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

/*
 * Quicksort component algorithm to divide or partition array, using INT_MAX or Infinity above high index
 */
int partitionA(int A[], int low, int high)
{
    int pivot = A[low];		// best case timing is with a pivot that is in the middle of the array
    int low_idx = low;
    int high_idx = high;

    do {
        // Increment low_idx as long as elements are smaller/equal to pivot
        do {low_idx++;} while (A[low_idx] <= pivot);

        // Decrement high_idx as long as elements are larger than pivot
        do {high_idx--;} while (A[high_idx] > pivot);

        if (low_idx < high_idx){
        	// swap values to sort elements above and below pivot value
            swap(&A[low_idx], &A[high_idx]);
        }
    } while (low_idx < high_idx);

    // swap pivot data location with found center position
    swap(&A[low], &A[high_idx]);
    return high_idx;
}

/*
 * Quicksort algorithm using INT_MAX or Infinity above high index
 */
void QuickSortA(int A[], int low, int high)
{
	/*
	 * Recursively partition input array into two ranges until array cannot be split anymore.
	 */
    if (low < high){
        int mid_pivot = partitionA(A, low, high);	// returns only sorted index, the new middle pivot index
        QuickSortA(A, low, mid_pivot);				// sort set of array below middle pivot
        QuickSortA(A, mid_pivot+1, high);			// sort set of array above middle pivot
    }
}

// Last Element is Pivot + without using INT_MAX or INFINITY
int partitionLast(int A[], int low, int high)
{
    int pivot = A[high];	// pivot selected as last element
    int i = low - 1;		// note: arg low is zero, which means that index i starts out at (-1)

    for (int j=low; j<=high-1; j++){
    	// Compare array elements from low to high index with pivot, move element less than pivot to array start
        if (A[j] < pivot){
            i++;
            //cout << "Swapping A[" << i << "]=" << A[i] << " with A[" << j << "]=" << A[j] << endl;
            swap(&A[i], &A[j]);
        }
    }
    //cout << "Swapping pivot A[" << high << "]=" << A[high] << " with A[" << i+1 << "]=" << A[i+1] << endl;
    swap(&A[i+1], &A[high]);
    return i+1;
}

/*
 * Quicksort algorithm using last index pivot w/o INT_MAX or Infinity
 */
void QuickSortLast(int A[], int low, int high)
{
	/*
	 * Recursively partition input array into two ranges until array cannot be split anymore.
	 */
    if (low < high){
        int pivot = partitionLast(A, low, high); // A[pivot] in sorted position
        QuickSortLast(A, low, pivot-1); 	// Sort elements in range: A[low], A[pivot-1]
        QuickSortLast(A, pivot+1, high); 	// Sort elements in range: A[pivot+1], A[high]
    }
}

// First Element is Pivot + without using INT_MAX or INFINITY
int partition(int A[], int low, int high)
{
    int pivot = A[low];
    int low_idx = low + 1;	// start at 1 above pivot
    int high_idx = high;

    // Without using INT_MAX at array end, the logic is a bit more complex
    while (true) {
    	// Increment low_idx as long as elements are smaller/equal to pivot AND low_idx is lte high_idx
        while (A[low_idx] <= pivot && low_idx <= high_idx){
            low_idx++;
        }
    	// Increment high_idx as long as elements are greater/equal to pivot AND high_idx is gte low_idx
        while (A[high_idx] >= pivot && high_idx >= low_idx){
            high_idx--;
        }
        // Partition is complete if high_idx becomes less than low_idx
        if (high_idx < low_idx){
            break;
        } else {
        	// swap values to sort elements above and below pivot value
            swap(&A[low_idx], &A[high_idx]);
        }
    }

    // swap pivot data location with found center position
    swap(&A[low], &A[high_idx]);
    return high_idx;	// high_idx is partition pivot
}

/*
 * Quicksort algorithm w/o INT_MAX or Infinity
 */
void QuickSort(int A[], int low, int high)
{
	/*
	 * Recursively partition input array into two ranges until array cannot be split anymore.
	 */
    if (low < high) {
        int pivot = partition(A, low, high);
        QuickSort(A, low, pivot-1); 	// Sort elements in range: A[low], A[pivot-1]
        QuickSort(A, pivot+1, high); 	// Sort elements in range: A[pivot+1], A[high]
    }
}

int main()
{
	cout << "https://www.udemy.com/course/datastructurescncpp/learn/lecture/13191520#questions/12460534" << endl; // prints https://www.udemy.com/course/datastructurescncpp/learn/lecture/13191520#questions/12460534

    cout << "\nQuickSort Algorithm:\n" << endl;

    cout << "Using INT_MAX or Infinity" << endl;
    int A[] = {3, 7, 9, 10, 6, 5, 12, 4, 11, 2, 32767};
    int n = sizeof(A)/sizeof(A[0]);
    Print(A, n-1, "\t\tA");

    QuickSortA(A, 0, n-1);
    Print(A, n-1, "   Sorted A");
    cout << endl;

    cout << "Last Element as Pivot + w/o INT_MAX or Infinity" << endl;
    int B[] = {11, 13, 7, 12, 16, 9, 24, 5, 10, 3};
    Print(B, sizeof(B)/sizeof(B[0]), "\t\tB");

    QuickSortLast(B, 0, sizeof(B)/sizeof(B[0])-1);
    Print(B, sizeof(B)/sizeof(B[0]), "   Sorted B");
    cout << endl;

    cout << "First Element as Pivot + w/o INT_MAX or Infinity" << endl;
    int C[] = {11, 13, 7, 12, 16, 9, 24, 5, 10, 3};
    Print(C, sizeof(C)/sizeof(C[0]), "\t\tC");

    QuickSort(C, 0, sizeof(C)/sizeof(C[0])-1);
    Print(C, sizeof(C)/sizeof(C[0]), "   Sorted C");

    return 0;
}
