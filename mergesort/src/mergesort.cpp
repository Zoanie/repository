//============================================================================
// Name        : mergesort.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://www.udemy.com/course/datastructurescncpp/learn/lecture/13191534#questions/12460534
//============================================================================

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>    // std::merge, std::sort

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

/*
 * Merge a single sorted array divided into 2 parts, into a single sorted array
 */
void Merge(int A[], int low, int mid, int high){
    int i = low;
    int j = mid+1;
    int k = low;
    int B[high+1];

    /*
     * A[] is a sorted input array divided into 2 parts
     *
     * Final sort if A[] looks like this:
     *
     * [2][5][8][12][3][6][7][10]
     *  ^         ^            ^
     * low=0     mid=3       high=7
     *
     * B[] is the temporary result array
     *
     * Merge array 1 and array 2 into B[]
     *   array 1 is A[0][1][2][3]
     *   array 2 is A[4][5][6][7]
     * Both arrays are sorted from low to high (less-than order)
     *
     *
     */
    while (i <= mid && j <= high){
        if (A[i] < A[j]){
            B[k++] = A[i++];
        } else {
            B[k++] = A[j++];
        }
    }

    /*
     * Only one of the merged arrays will have element remaining not copied into B[].
     * These elements are sorted and are the highest value elements.  The next two
     * while loop statements clean up which ever of the 2 merged arrays have elements
     * remaining.  There could also be a elements remaining because the input array
     * is not divisible by 2, hence there will be remaining elements at the end,
     * depending on the location of the mid point.
     */
    while (i <= mid){
        B[k++] = A[i++];
    }
    while (j <= high){
        B[k++] = A[j++];
    }

    /*
     * Complete the merge by copying the temporary result array B[] into A[]
     */
    for (int i=low; i<=high; i++){
        A[i] = B[i];
    }
}

/*
 * Iterative merge sort.
 * Array A[] with n elements.
 *
 * Time Complexity:
 *     Best case:	O(n log(n))
 *     Worst case:	O(n log(n))
 *
 * Space Complexity:
 *     Worst case:  O(n), although some variants can use O(n/2)
 *
 * Stable sort
 */
void IterativeMergeSort(int A[], int n){
    int p;

    /*
     * example:
     *   A[] = {2, 5, 8, 12, 3, 6, 7, 10};
     *
     *   Merge by first dividing unsorted array into sorted arrays of single item elements.  Then progressively sorting these arrays
     *   with each other until only 1 array remains.  The final array may have an extra element to sort if the starting array
     *   size has an odd number of elements.
     */
    // p=2, 4, 8, 16
    for (p=2; p<=n; p=p*2){
    	// For input array size of n=8 elements:
    	//   first iteration with p=2:
    	//	   low       high
    	//     i=0; i+p-1 = 0+2-1 = 1; i+p=0+2=2
    	//     i=2; i+p-1 = 2+2-1 = 3; i+p=2+2=4
    	//     i=4; i+p-1 = 4+2-1 = 5; i+p=4+2=6
    	//     i=6; i+p-1 = 6+2-1 = 7; i+p=6+2=8
    	//     i=8; i+p-1 = 8+2-1 = 9 (9 > 8) stop
    	//   second iteration with p=4:
    	//     i=0; i+p-1 = 0+4-1 = 3; i+p=0+4=4
    	//     i=4; i+p-1 = 4+4-1 = 7; i+p=4+4=8
    	//     i=8; i+p-1 = 8+4-1 = 13 (13 > 8) stop
    	//   third iteration with p=8:
    	//     i=0; i+8-1 = 0+8-1 = 7; i+p=0+8=8
    	//     i=8; i+p-1 = 8+8-1 = 15 (15 > 8) stop
        for (int i=0; i+p-1<n; i=i+p){
            int low = i;
            int high = i+p-1;
            int mid = (low+high)/2;
/*
            if(p==8) {
            	string msg = "   Before final sort: low=" + to_string(low) + ", high=" + to_string(high) + ", mid=" + to_string(mid) + " ";
                Print(A, p, msg);
            }
*/
            Merge(A, low, mid, high);

        }
    }
    // Last iteration leaves p as 16.  This merge only occurs if input array is odd
    //cout << "p/2 = " << p/2 << ", n = " << n << endl;
    if (p/2 < n){
        Merge(A, 0, p/2-1, n-1);
    }
}

/*
 *
 */
void RecursiveMergeSort(int A[], int low, int high){
    if (low < high){
        // Calculate mid point
        int mid = low + (high-low)/2;

        // Sort sub-lists
        RecursiveMergeSort(A, low, mid);
        RecursiveMergeSort(A, mid+1, high);

        // Merge sorted sub-lists
        Merge(A, low, mid, high);
    }
}

/*
 *
 */
void stdlibMergeSort(int A[], int n){
	vector<int> resultVec(8);

	//
	/*
	 * stdlib fcn merge uses 2 pairs of stdlib input interators for the arguments.
	 *
	 * Input iterators to the initial and final positions of the first sorted sequence.
	 * The range used is [first1,last1), which contains all the elements between first1 and last1,
	 * including the element pointed by first1 but not the element pointed by last1.
	 */
	merge (A, A+4, A+4, A+8,resultVec.begin());


}

int main() {
	cout << "https://www.udemy.com/course/datastructurescncpp/learn/lecture/13191534#questions/12460534" << endl; // prints https://www.udemy.com/course/datastructurescncpp/learn/lecture/13191534#questions/12460534

    //int A[] = {2, 5, 8, 12, 3, 6, 7, 10};
    //int n = sizeof(A)/sizeof(A[0]);

    array<int, 8> VA{2, 5, 8, 12, 3, 6, 7, 10};

    cout << "\nIterative MergeSort" << endl;
	Print(VA, VA.size(), "Test A[] array   ");

    IterativeMergeSort(VA.data(), VA.size());
    Print(VA, VA.size(), "Algorithm sorted ");

    array<int, 8> VB{2, 5, 8, 12, 3, 6, 7, 10};

	Print(VA, VA.size(), "\nTest A[] array   ");
    stdlibMergeSort(VB.data(), VB.size());
	Print(VB, VB.size(), "Std::merge result");

    return 0;
}
