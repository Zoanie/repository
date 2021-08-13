//============================================================================
// Name        : stl-vector-operations.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : Let's code!
//============================================================================

#include <bits/stdc++.h>

/*
 * <numeric>
 *
Functions
accumulate()			Accumulate values in range (function template )
						http://www.cplusplus.com/reference/numeric/accumulate/

adjacent_difference()	Compute adjacent difference of range (function template )
inner_product()			Compute cumulative inner product of range (function template )
partial_sum()			Compute partial sums of range (function template )
iota()					Store increasing sequence (function template )
 */

using namespace std;
using namespace std::chrono;

vector<vector<int>> VectorMatrix;

template<class T>
void printMatrix(vector<vector<T>> const &mat) {
	cout << "Matrix:" << endl;
	cout << "[" << endl;
	for (vector<T> row: mat) {
		cout << "  [ ";
		for (T val: row) {
			cout << val << " ";
		}
		cout << "]" << endl;
	}
	cout << "]" << endl;
}

template<class T>
void printVector(string name, vector<T> const &vec) {
	cout << name << ": " << endl;
	cout << "  [ ";
	for (T val: vec) {
		cout << val << " ";
	}
	cout << "]" << endl;
}

void load_matrix(vector<vector<int>>& matrix, int num_rows, int num_cols)
{
	printf("Creating a %d X %d ", num_rows, num_cols);
	for (int rows=0; rows<num_rows; rows++ ) {
		vector<int> row;
		for(int cols=0; cols<num_cols; cols++)
		{
			row.push_back(cols+1);
		}
		matrix.push_back(row);
	}
	printMatrix(matrix);

}

void iterate_over_vectors(vector<int>& vec)
{
	for(auto& elem : vec) {
		cout << elem << " ";
	}
	cout << endl;

	for(auto itr=begin(vec); itr<end(vec); ++itr) {
		cout << *itr << " ";
	}
	cout << endl;

	for(size_t i=0; i<vec.size(); i++) {
		cout << vec[i] << " ";
	}
	cout << endl;

	for_each(begin(vec), end(vec), [](const int elem){ cout << elem << " ";});
	cout << endl;
}

// https://stackoverflow.com/questions/25108854/initializing-the-size-of-a-c-vector
int vector_constructors(int num)
{
    string str[]={"Alex","John","Robert"};

	cout << "\nVector Constructors:" << endl;

	// variable number of vector elements
	vector<int> v0(num);
	cout << "Number of elements in vector v0     = " << v0.size() << endl;
	cout << "Capacity of elements in vector v0   = " << v0.capacity() << endl;

    // empty vector object
    vector<int> v1;

    // creates vector with 10 empty elements
    vector<int> v2(10);

    // creates vector with 10 elements,
    // and assign value 0 for each
    vector<int> v3(10,0);

    // creates vector and assigns
    // values from string array
    vector<string> v4(str+0,str+3);

    vector<string>::iterator sIt = v4.begin();
    while ( sIt != v4.end() )
        cout << *sIt++ << " ";
    cout << endl;

    // copy constructor
    vector<string> v5(v4);
    for ( int i=0; i<3; i++ )
        cout << v5[i] << " ";
    cout << endl;

    return 0;
}

int vector_assign()
{
    int ary[]={1,2,3,4,5};
    vector<int> v;

	cout << "\nVector Assign:" << endl;

    // assign to the "v" the contains of "ary"
    v.assign(ary,ary+5);

    copy(v.begin(),v.end(),
            ostream_iterator<int>(cout," "));
    cout << endl;

    // replace v for 3 copies of 100
    v.assign(3,100);

    copy(v.begin(),v.end(),
            ostream_iterator<int>(cout," "));
    cout << endl;

    return 0;
}

template<class T, class D>
class Member
{
    public:
        Member(T t, D d) : name(t), sal(d) {}
        void print() {  cout << name << "  " << sal << endl; }

    private:
        T name;
        D sal;
};


//======================================
int vector_back ()
{
    typedef Member<string,double> M;
    vector<M> v;

	cout << "\nVector Back:" << endl;

    v.push_back(M("Robert",60'000));
    v.push_back(M("Linda",75'000));

    vector<M>::iterator It = v.begin();
    cout << "Entire vector:" << endl;

    while ( It != v.end() )
        (It++)->print();
    cout << endl;

    cout << "Return from back()" << endl;
    v.back().print();
    return 0;
}

int vector_begin()
{
    vector<int> v(5);
    iota(v.begin(),v.end(),1);

    vector<int>::iterator It = v.begin();
    while ( It != v.end() )
        cout << *It++ << " ";
    cout << endl;

    // third element of the vector
    It = v.begin()+2;
    cout << *It << endl;

    return 0;
}

void vector_2d_removal()
{
	// Initializing 2D vector "vect" with
	// sample values
	vector<vector<int> > vec{ { 1, 2, 3 },
		{ 4, 5, 6 },
		{ 7, 8, 9 } };

	cout << "\n2D-Vector before removing 2 vectors:" << endl;
	printMatrix(vec);
	// Removing elements from the
	// last row of the vector
	vec[2].pop_back();
	vec[1].pop_back();

	cout << "\n2D-Vector after removing 2 items from last 2 rows:" << endl;
	printMatrix(vec);
}

void vector_capacity()
{
    vector<int> v(10);

	cout << "\nVector Capacity:" << endl;

    cout << "Size     of v = "
         << v.size() << endl;
    cout << "Capacity of v = "
         << v.capacity() << endl;

    v.resize(100);

    cout << "After resizing:" << endl;
    cout << "Size     of v = "
         << v.size() << endl;
    cout << "Capacity of v = "
         << v.capacity() << endl;
}

void vector_erase()
{
    vector<int> v(10);
    vector<int>::iterator It;

	cout << "\nVector Erase, before:" << endl;

    iota(v.begin(),v.end(),1);
    //for ( int i=0; i<10; i++ )
    //    v[i] = i+1;

    copy(v.begin(),v.end(),
            ostream_iterator<int>(cout," "));
    cout << endl;

    It = v.begin()+2;

    // remove third element
    v.erase(It);

	cout << "\nVector Erase, after remove 3rd element:" << endl;
    copy(v.begin(),v.end(),
            ostream_iterator<int>(cout," "));
    cout << endl;

    It = v.begin();
    // remove 2 elements from beginning of v
    v.erase(It,It+2);

	cout << "\nVector Erase, after removing first 2 elements:" << endl;
    copy(v.begin(),v.end(),
            ostream_iterator<int>(cout," "));
    cout << endl;

}

// https://leetcode.com/explore/interview/card/top-interview-questions-easy/92/array/646/
/*
 * Rotate Array
 *
Given an array, rotate the array to the right by k steps, where k is non-negative.

Follow up:

Try to come up as many solutions as you can, there are at least 3 different ways to solve this problem.
Could you do it in-place with O(1) extra space?

Example 1:
Input: nums = [1,2,3,4,5,6,7], k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]

Example 2:
Input: nums = [-1,-100,3,99], k = 2
Output: [3,99,-1,-100]
Explanation:
rotate 1 steps to the right: [99,-1,-100,3]
rotate 2 steps to the right: [3,99,-1,-100]
 */
void vector_rotate(vector<int>& nums, int k)
{
    auto num_elements = nums.size();
    k %= num_elements;
	// Rotates the order of the elements in the range [first,last), in such a way that the element pointed by middle becomes the new first element.
	auto middle = end(nums) - k;
	rotate(begin(nums), middle, end(nums));

}

void vector_front_n_back(vector<int>& nums)
{
	// front of vector is accessed:
	if(nums.size()) {
		cout << "Vector size is " << nums.size() << endl;
		cout << "First element is " << nums.front() << endl;
		cout << "Last element is " << nums.back() << endl;

	}
}

//https://leetcode.com/explore/interview/card/top-interview-questions-easy/92/array/578/
/*
 * Contains Duplicate
 *
Given an array of integers, find if the array contains any duplicates.

Your function should return true if any value appears at least twice in the array, and it should return false if every element is distinct.

Example 1:
Input: [1,2,3,1]
Output: true

Example 2:
Input: [1,2,3,4]
Output: false

Example 3:
Input: [1,1,1,3,3,4,3,2,4,2]
Output: true
 */
bool containsDuplicate(vector<int>& nums)
{
    unordered_set<int> numset;
    for(auto val : nums) {
    	auto itn = numset.emplace(val);
    	if(!itn.second) { return true; }
    }
    return false;

    /* this is another way, but requires sorting */
    sort(begin(nums), end(nums));
    auto itdup = adjacent_find(begin(nums), end(nums));
    if(itdup != end(nums)) {
    	return true;
    }
    return false;


}

// https://leetcode.com/explore/interview/card/top-interview-questions-easy/92/array/549/
/*
 * Single Number
 *
Given a non-empty array of integers nums, every element appears twice except for one. Find that single one.

Follow up: Could you implement a solution with a linear runtime complexity and without using extra memory?

Example 1:
Input: nums = [2,2,1]
Output: 1

Example 2:
Input: nums = [4,1,2,1,2]
Output: 4

Example 3:
Input: nums = [1]
Output: 1

Constraints:
	o 1 <= nums.length <= 3 * 104
	o -3 * 104 <= nums[i] <= 3 * 104
	o Each element in the array appears twice except for one element which appears only once.
 */
int singleNumber(vector<int>& nums) {

	// from browsing the leetcode discussion groups
	// https://leetcode.com/problems/single-number/discuss/42994/One-line-c%2B%2B-STL
    return accumulate(begin(nums), end(nums), 0, bit_xor<int>());

	int num_elements = nums.size();
	if(num_elements == 1) {
		return nums[0];
	}
	sort(begin(nums), end(nums));

	int single = nums[0];
	for(int i=0, j=1; j<num_elements; j++) {
		if(single != nums[j]) {
			return nums[i];
		}
		while(nums[i] == nums[j]) {
			j++;
		}
		i = j;
		single = nums[i];
	}
	return single;
}

//https://leetcode.com/explore/interview/card/top-interview-questions-easy/92/array/674/
/*
 * Intersection of Two Arrays II
 *
Given two arrays, write a function to compute their intersection.

Example 1:
Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2,2]

Example 2:
Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
Output: [4,9]
Note:

Each element in the result should appear as many times as it shows in both arrays.
The result can be in any order.
Follow up:

What if the given array is already sorted? How would you optimize your algorithm?
What if nums1's size is small compared to nums2's size? Which algorithm is better?
What if elements of nums2 are stored on disk, and the memory is limited such that you cannot load all elements into the memory at once?
 */
vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
	vector<int> nums3;

	sort(begin(nums1), end(nums1));
	sort(begin(nums2), end(nums2));
	set_intersection(cbegin(nums1), cend(nums1), cbegin(nums2), cend(nums2), back_inserter(nums3));

	return nums3;
}

/*
 * Move Zeros
 *
Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.

Example:
Input: [0,1,0,3,12]
Output: [1,3,12,0,0]
Note:

You must do this in-place without making a copy of the array.
Minimize the total number of operations
 */
void moveZeroes(vector<int>& nums) {
	//int num_zeros = count(begin(nums), end(nums), 0);

	//partial_sort(begin(nums), end(nums), begin(nums)+num_zeros);
	stable_partition(rbegin(nums), rend(nums), [](auto elem){return elem == 0;});

	// if you need the zeros at the beginning...
	//auto middle = partition(rbegin(nums), rend(nums), [](auto elem){return elem == 0;});

	// if you need the zeros anywhere else...
	//rotate(begin(nums), middle, end(nums));
}

/*
 * Plus One
 *
Given a non-empty array of decimal digits representing a non-negative integer, increment one to the integer.
The digits are stored such that the most significant digit is at the head of the list, and each element in
the array contains a single digit. You may assume the integer does not contain any leading zero, except the
number 0 itself.

Example 1:
Input: digits = [1,2,3]
Output: [1,2,4]
Explanation: The array represents the integer 123.

Example 2:
Input: digits = [4,3,2,1]
Output: [4,3,2,2]
Explanation: The array represents the integer 4321.

Example 3:
Input: digits = [0]
Output: [1]

Constraints:
1 <= digits.length <= 100
0 <= digits[i] <= 9
 */

vector<int> plusOne(vector<int>& digits) {
    int carry = 1;
    for (int i = digits.size() - 1; i >= 0; --i) {
    	digits[i] += carry;
        if (i != 0) {
            if (digits[i] > 9) {
            	digits[i] -= 10;
                carry = 1;
            } else {
                carry = 0;
            }
        }
    }

    if (digits[0] > 9) {
        // top digit carried over; make an additional digit at front
    	digits[0] -= 10;
    	digits.insert(begin(digits), 1);	// insert(0, (size_t) 1, '1');
    }

    return digits;
}

class PascalsTriangleSolution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res;
        for(auto i=0;i<numRows;++i)
        {
        	// Create and push back a vector of increasing sizes(1,2,3,4...), all with
        	// elements initialized to 1.  This might be a bit wasteful as the interior
        	// elements other than res[0] and res[i] are later overwritten.
            res.push_back(vector<int>(i+1,1));
            //res.push_back(vector<int>(i+1);
            // res[0] = res[i] = 1;
            for(auto j=1; j<i; ++j) {
            	res[i][j] = res[i-1][j-1] + res[i-1][j];
            }
        }
        return res;
    }
};
/*
 * STL vector tests
 */
int main() {

	load_matrix(VectorMatrix, 5, 3);
	return 0;
	vector<int>hacker(10);
	iota(begin(hacker), end(hacker), 1);
	vector_front_n_back(hacker);
	vector<int>hacker2{39,45,12, 9, 16, 22, 19, 77};
	sort(begin(hacker2), end(hacker2));
	vector_front_n_back(hacker2);

	return 0;

	PascalsTriangleSolution PTS;
	auto start = high_resolution_clock::now();
	vector<int>testVector(10'000'000, 0);
	for(auto loops=0; loops<100; loops++)
		PTS.generate(100);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Test timing is " << duration.count() << " microseconds" << endl;
	return 0;

	cout << "Vector operations" << endl;
	vector<int> vP1{9,9,9,9};
	printVector("Vector PlusOne Before", vP1);
	plusOne(vP1);
	printVector("Vector PlusOne After", vP1);

	return 0;

	vector<int> vMZ{0,1,0,3,12};
	printVector("Vector Move Zeros Before", vMZ);
	moveZeroes(vMZ);
	printVector("Vector Move Zeros After", vMZ);


	vector<int> vS{4,1,2,1,2};
	int single = singleNumber(vS);
	cout << "Single number = " << single << endl;
	return 0;

	vector<int> vR{-1};
	printVector("Vector Rotate Before", vR);
	vector_rotate(vR, 2);
	printVector("Vector Rotate After", vR);

	return 0;

	// count how many entries have the target value (2)
	vector<int> vA{2,7,1,6,2,-2,4,0};

	// create a vector of size arg1, all having values arg2
	vector<int> vB(10, 123);

	// initialize a vector from an array
	int arr[] = {10, 20, 30, 40, 50};
	int arrElems = sizeof(arr) / sizeof(int);
	vector<int> vC(arr, arr + arrElems);

	// count number of 2's in vector
	int twos = 0;
	int const target =2;
	twos = count(begin(vA), end(vA), target);

	printVector("Counting Vector", vA);
	cout << "Number of '2s' = " << twos << endl;

	vector_constructors(9);

	vector_assign();

	vector_back();

	vector_2d_removal();

	vector_capacity();

	vector_erase();

	return 0;
}
