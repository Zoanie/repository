//============================================================================
// Name        : interview-coding-problems.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

template<class T>
void printVector(vector<T> const &vec) {
	cout << "Vector:" << endl;
	cout << "  [ ";
	for (T val: vec) {
		cout << val << " ";
	}
	cout << "]" << endl;
}

/*
 * Description: Write a program that counts frequency of each letter in the string (string consists lowercase letters only).
 */
void freq(string s){
	//array to store frequency of 26 characters,initialized to 0
	int arr[26]={0};
	int ascii_index = 0;

	for(size_t i=0; i<s.length();i++){
		// s[i] is the ascii value of the letter at index i & 'a'
		//also gives the ascii value of a, in this way we are
		//checking which alphabet is at index i and increasing its frequency
		ascii_index = s[i]-'a';
		arr[ascii_index]++;
	}

	for(int i=0;i<26;i++){
		if(arr[i]!=0)
			printf("%d%c, ",arr[i],'a'+i);
	}

	cout<<endl;
}

//function to swap by reference
void swap(int*a,int*b){
	int temp;
	temp=*b;
	*b=*a;
	*a=temp;
	return;
}

/*
 * Description: Sort an array of 0's, 1's and 2's in linear time complexity.
 *
 * Problem statement: Given an array consisting only 0's, 1's and 2's. Give an algorithm for sorting the array
 * 		in O(n) time complexity ( in the sorted array, 0's will be at starting ,then the 1's & then the 2's).
 */
void asort(vector<int> &a,int n)
{
	int low=0,mid=0,high=n-1;   //variables are set

	n = a.size();
/*
	printf("Starting Array[%d] = {", n); for(int i=0; i<n; i++) printf("%d ", a[i]); printf("}\n");
	printf("Enter any key to continue...");
	getchar();
	printf("\n");
*/
	while(mid<=high){
/*
		printf("Array[%d] = {", n); for(int i=0; i<n; i++) printf("%d ", a[i]); printf("}\n");
		printf("Sorting elem[%d]=%d, low=%d, mid=%d, high=%d\n", mid, a[mid], low, mid, high);
		printf("Enter any key to continue...");
		getchar();
		printf("\n");
*/
		/*
		 * 0: An encountered mid position 0 can be swapped backward with the low position 1
		 * 1: An encountered mid position 1 is left in place
		 * 2: An encountered mid position 2 can be swapped with the mid position 1
		 * An encountered 2 can be swapped with the next lower
		 */
		switch(a[mid]){
			case 0:     //if a[mid]==0
				//swap a[low] & a[mid], swapping by reference
				//printf("Case 0: Swapping elem[%d++] <=> elem[%d++], low++ & mid++\n", low, mid);
				swap(&a[low],&a[mid]);
				low++;      //increment low
				mid++;      //increment mid
				break;
			case 1:     //if a[mid]==1
				//printf("Case 1: Incrementing mid=%d => %d\n", mid, mid+1);
				mid++;      //increment mid
				break;
			case 2:     //if a[mid]==2
				//swap a[mid] & a[high], swapping by reference
				//printf("Case 2: Swapping elem[%d] <=> elem[%d], high--\n", mid, high);
				swap(&a[mid],&a[high]);
				high--;     //decrement high
				break;
		}
	}
	//address of array(sorted) by reference
	return;
}

void runLengthStringEncoding(){
	string s;

	cout<<"Enter string: ";
	cin>>s;
	cout<<"Encoded string is : "<<endl;
	freq(s);

	cout<<"Enter any key to continue..." << endl;
	getchar();
	cout << endl;

}

void displayMenu()
{
	cout << "Select Coding Interview Question:" << endl;
	cout << "1. Run-length encoding (find/print frequency of letters in a string)" << endl;
	cout << "2. Sort an array of 0's, 1's and 2's in linear time complexity" << endl;
	cout << "3. Checking Anagrams (check whether two string is anagrams or not)" << endl;
	cout << "X. Exit\n" << endl;
	cout << "___" << flush;
	/*
	cout << "4. " << endl;
	cout << "5. " << endl;
	cout << "6. " << endl;
	*/
}
void linearTimeArray012Sort()
{
	int n;

	cout << "Enter no of array elements: " << flush;
	//input array length
	cin >> n;
	// scanf("%d",&n);

    vector<int> pArray(n);

    cout << "Enter array elements: " << flush;

	//input array elements
	for(int j=0;j<n;j++)
		scanf("%d",&pArray[j]);

	//array is modified
	asort(pArray, n);
	printf("after being sorted..............\n");

	//printing the sorted array
	for(int j=0;j<n-1;j++)
		printf("%d ",pArray[j]);

	printf("%d\n",pArray[n-1]);

	cout<<"Enter any key to continue..." << endl;
	getchar();
	cout << endl;

}

/*
 * An anagram of a string is another string that contains same characters,
 * only the order of characters can be different.
 */
int anagram(string s1,string s2)
{
	int array1[26]={0},array2[26]={0};
	int ascii_offset = 0;

	//if string lengths are different
	if(s1.length()!=s2.length())
		return 0; //they are not anagrams
	//for string1
	for(int i=0;s1[i]!='\0';i++){
		ascii_offset = s1[i] - 'a';
		//storing frequency for each letter in the string
		array1[ascii_offset]++;
	}

	//for string2
	for(int i=0;s2[i]!='\0';i++){
		ascii_offset = s2[i] - 'a';
		//storing frequency for each letter in the string
		array2[ascii_offset]++;
	}
	//comparison step
	for(int i=0;i<26;i++){
		// if any letter has different no of occurrence,
		// then strings are not anagrams
		if(array1[i]!=array2[i])
			return 0;
	}

	return 1;// else they are anagrams
}

/*
 * Problem statement: Given two strings, check whether two given strings are anagram of each other or not.
 * 	An anagram of a string is another string that contains same characters, only the order of characters can be different.
 *
 * 	For example, "act" and "cat" are anagram of each other.
 */
void checkingAnagrams()
{
	string s1,s2;

	//input the strings
	cout<<"Enter string1: ";
	cin>>s1;
	cout<<"Enter string2: ";
	cin>>s2;

	if(anagram(s1,s2))
		printf("strings are anagrams of each other\n");
	else
		printf("strings are not anagrams of each other\n");

	cout<<"Enter any key to continue..." << endl;
	getchar();
	cout << endl;

}

/*
 * Leetcode: Reverse Linked List
 *
 * Reverse a singly linked list.
 *
Input: 1->2->3->4->5->NULL
Output: 5->4->3->2->1->NULL
 */

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class List {
private:
	int numElements;
	ListNode *listHead;
	ListNode *listTail;
	string listName;

public:
	List(string name) {
		numElements = 0;
		listHead = nullptr;
		listTail = nullptr;
		listName = name;
	}

	List(string name, int A[], int numNodes) {
		ListNode *pNode;
		listHead = new ListNode(A[0]);
		listHead->next = nullptr;
		listTail = listHead;
		for(int i=1; i<numNodes; i++) {
			pNode = new ListNode(A[1]);
			pNode->val = A[i];
			pNode->next = nullptr;
			listTail->next = pNode;
			listTail = pNode;
		}
		numElements = numNodes;
		listName = name;
	}
    int listCount (struct ListNode *p)
    {
    	static bool initialized = false;

    	if(initialized) {
    		return numElements;
    	}

    	while(p)
    	{
    		numElements++;
    		p=p->next;
    	}
    	initialized = true;
    	return numElements;
    }

	int listCount() { return listCount(listHead); }
	void setListName(string name) { listName = name; }
	string getListName() const { return listName; }
	ListNode* getListHead() const { return listHead; }
	bool isSorted(ListNode *pNode) {
		int x = INT_MIN;

		while(pNode != nullptr) {
			if(pNode->val < x)
				return false;
			x = pNode->val;
			pNode = pNode->next;
		}
		return true;
	}

	bool isLoop(ListNode *pNode) {
		if(pNode == nullptr || pNode->next == nullptr)
			return false;
		ListNode* prevNode;
		ListNode* nextNode;

		prevNode = nextNode = pNode;

		do {
			prevNode = prevNode->next;
			nextNode = nextNode->next;
			nextNode = (nextNode != nullptr) ? nextNode->next : nextNode;
		} while(prevNode && nextNode && prevNode != nextNode);

		return (prevNode == nextNode) ? true : false;
	}

    ListNode* reverseList(ListNode* head) {
    	if((head == nullptr) || (head->next == nullptr)) return head;

    	ListNode* currNode = head;
    	ListNode* prevNode = nullptr;
    	ListNode* nextNode = head->next;

    	while(nextNode != nullptr) {
    		// Order is very important: N, C, P, C
    		// First fix the next pointer
    		//   1. N = Cn
    		// 	 2. Cn = P
    		// Then move previous and current pointers to next node
    		//   3. P = C
    		//   4. C = N
    		nextNode = currNode->next;
    		currNode->next = prevNode;
    		prevNode = currNode;
    		currNode = nextNode;
    	}
    	currNode = listHead;
    	listHead = listTail;
    	listTail = currNode;

    	return prevNode;
    }

    /*
     * Insert node at index x into unsorted list
     * Index 0 is before list head
     * Index 1 is after list head
     * Last index position is equal to list count and located after list tail
     */
    void insertNode(int index, int x) {
    	ListNode* prev = listHead;

    	// Two cases:
    	// 1. Inserting before first node
    	// 2. Inserting anywhere else in list
    	if(index < 0 || index > listCount()) {
    		return;
    	}
    	// First create the new node and initialize it
    	ListNode* curr = new ListNode(x);
    	curr->val = x;

    	// Next insert the node
    	if(index == 0) {	// Case 1. Insert before
    		curr->next = listHead;
    		listHead = curr;
    	}
    	else {	// Case 2. Insert anywhere else in list
    		for(int i=0; i<index-1; i++) {
    			prev = prev->next;
    		}
    		// Cut the list line right here: ill take your next and you take me for your next
    		curr->next = prev->next;
    		prev->next = curr;
    	}
    	return;
    }

    void sortedInsertNode(ListNode *prevNode, int nodeVal) {
    	ListNode *currNode;
    	ListNode *nextNode;

    	currNode = new ListNode(nodeVal);
    	currNode->next = nullptr;

    	if(listHead == nullptr) {
    		listHead = currNode;
    	}
    	else {
    		// find the location to insert the new current node
    		while(prevNode && prevNode->val < nodeVal) {
    			nextNode = prevNode;	// save a pointer to the previous node
    			prevNode = prevNode->next;
    		}
    		// Now insert the
    		if(prevNode == listHead) {
    			currNode->next = listHead;
    			listHead = currNode;
    		}
    		else {
    			currNode->next = nextNode->next;
    			nextNode->next = currNode;
    		}
    	}
    }

    // 1-based node ID
    int deleteNode(ListNode *currNode, int nodeId) {
    	ListNode *prevNode;
    	int listVal = -1;

    	if(nodeId < 1 || nodeId > listCount()) {
    		return (-1);
    	}
    	if(nodeId == 1) {
    		prevNode = listHead;
    		listVal = prevNode->val;
    		listHead = listHead->next;
    		delete prevNode;
    	}
    	else {
    		// Find the matching node id
    		for(int i=0; i<nodeId-1; i++) {
    			prevNode = currNode;
    			currNode = currNode->next;
    		}
    		prevNode->next = currNode->next;
    		listVal = currNode->val;
    		delete currNode;
    	}
    	return listVal;
    }

    ListNode* mergeLists(ListNode *l1, ListNode *l2) {
    	ListNode *lastNode;
    	ListNode *l3;	// the merged list

    	// This list is sorted by increasing values.
    	// Select the lower value for each entry
    	// For this merge the list must have at least 1 element
    	if(l1 && l2) {
			if(l1->val < l2->val) {
				l3 = lastNode = l1;
				l1 = l1->next;
				l3->next = nullptr;
			}
			else {
				l3 = lastNode = l2;
				l2 = l2->next;
				l3->next = nullptr;
			}
    	}
    	else {	// End case where one or both of the lists is empty
        	if(l1) { l3 = l1;}
        	else if(l2) { l3 = l2;}
        	else { l3 = nullptr;}
        	return l3;
    	}

    	// Merge until one of the lists becomes empty
    	while(l1 && l2) {
    		if(l1->val < l2->val) {
    			lastNode->next = l1;
    			lastNode = l1;
    			l1 = l1->next;
    			lastNode->next = nullptr;
    		}
    		else {
    			lastNode->next = l2;
    			lastNode = l2;
    			l2 = l2->next;
    			lastNode->next = nullptr;
    		}
    	}

    	// Only one list remains, it can be simply appended to the end of the merged list
    	if(l1) lastNode->next = l1;
    	if(l2) lastNode->next = l2;

    	return l3;
    }

    void displayNode(ListNode* list) const
    {
    	if(list == nullptr)
    		return;

    	cout << list->val;

    	if(list->next != nullptr)
    	{
    		cout << " -> ";
    		displayNode(list->next);
    	}
    }

    void displayList(ListNode* list) const
    {
        cout << "List: " << listName << "(";
    	displayNode(list);
        cout << ")" << endl;
    }
    void displayList() { displayList(listHead); }

};

/*
 * Binary Gap
 * Find longest sequence of zeros in binary representation of an integer N.
 * N is an integer within the range [1..2,147,483,647].
 */
int binaryGap(int numInt)
{
	unsigned num = static_cast<unsigned>(numInt);
	unsigned bitnum = 0;
	unsigned zeros = 0;
	//int ones = 0;
	unsigned lastbit = 0;
	unsigned bitmask = 0x01;
	unsigned max_zeros_seq = 0;
	bool counting_zeros = false;
	//int max_ones_seq = 0;

	//printf("\nInput num = 0x%X\n", num);
	while((bitnum < 32)) {
		if(bitmask & num) {
			//printf("1 = bitnum = %d, bitmask = 0x%X\n", bitnum, (unsigned int) bitmask);
			if(counting_zeros) {
				//printf("stop counting zeros=%d, max_zeros_seq = %d\n", zeros, max_zeros_seq);
				max_zeros_seq = max(zeros, max_zeros_seq);
			}
			counting_zeros = true;
			zeros = 0;
			//if(lastbit)
			//	ones++;
			lastbit = 1;
		}
		else {
			//printf("0 = bitnum = %d, bitmask = 0x%X\n", bitnum, (unsigned int) bitmask);
			//ones = 0;
			if(counting_zeros) {
				if(!lastbit) {
					zeros++;
					//printf("incrementing zeros, zeros = %d\n", zeros);
				}
				else {
					zeros++;
					//printf("start counting zeros at bitnum = %d, zeros = %d\n", bitnum, zeros);
				}
			}
			lastbit = 0;
		}
		bitmask <<= 1;
		bitnum++;
	}
	return max_zeros_seq;
}

/*
 * OddOccurrencesInArray
 *
 * Find value that occurs in odd number of elements.
 *
A non-empty array A consisting of N integers is given. The array contains an odd number of elements, and each
element of the array can be paired with another element that has the same value, except for one element that
is left unpaired.

For example, in array A such that:

  A[0] = 9  A[1] = 3  A[2] = 9
  A[3] = 3  A[4] = 9  A[5] = 7
  A[6] = 9
the elements at indexes 0 and 2 have value 9,
the elements at indexes 1 and 3 have value 3,
the elements at indexes 4 and 6 have value 9,
the element at index 5 has value 7 and is unpaired.
Write a function:

int solution(vector<int> &A);

that, given an array A consisting of N integers fulfilling the above conditions, returns the value of the
unpaired element.

For example, given array A such that:

  A[0] = 9  A[1] = 3  A[2] = 9
  A[3] = 3  A[4] = 9  A[5] = 7
  A[6] = 9

the function should return 7, as explained in the example above.

Write an efficient algorithm for the following assumptions:

N is an odd integer within the range [1..1,000,000];
each element of array A is an integer within the range [1..1,000,000,000];
all but one of the values in A occur an even number of times.
 *
 */
int oddOccurrencesInArray(vector<int> &A)
{
	//!!! An unordered multiset is not the answer !!!
	// A possible solution is to sort the array and then search for an unpaired element
	if(A.size() == 0)
		return 0;

	int unpaired_element = 0;
	unordered_multiset<int> elementCounter;
	elementCounter.reserve(2*A.size());

	// If we need to know the index
	for(auto& array_element : A) {
		//printf("Adding element %d\n", array_element);

		// Don't waste the time to add the element if already paired
		if(elementCounter.count(array_element) < 2) {
			elementCounter.emplace(array_element);
		}
	}

	for(auto set_element : elementCounter) {
		if(elementCounter.count(set_element) == 1) {
			unpaired_element = set_element;
			//printf("Found unpaired element %d\n", unpaired_element);
			break;
		}
	}

	return unpaired_element;
}

/*
 * Frog Jump.
 *
 * Count minimal number of jumps from position X to Y.
 *
A small frog wants to get to the other side of the road. The frog is currently located at position X
and wants to get to a position greater than or equal to Y. The small frog always jumps a fixed distance, D.
Count the minimal number of jumps that the small frog must perform to reach its target.

Write a function:

int solution(int X, int Y, int D);

that, given three integers X, Y and D, returns the minimal number of jumps from position X to a position
equal to or greater than Y.

For example, given:

  X = 10
  Y = 85
  D = 30
the function should return 3, because the frog will be positioned as follows:

after the first jump, at position 10 + 30 = 40
after the second jump, at position 10 + 30 + 30 = 70
after the third jump, at position 10 + 30 + 30 + 30 = 100
Write an efficient algorithm for the following assumptions:

X, Y and D are integers within the range [1..1,000,000,000];
X ≤ Y.
 *
 */
/*
 * For example, for the input (3, 999111321, 7) the solution returned a wrong answer (got 142730192 expected 142730189).
 */
int frogJumps(int x, int y, int d)
{
	// Y = X + jumps * D
	// jumps = cieling ((Y - X) / D);
	double jumps = ceil(((double)(y-x))/ (double)d);
	return jumps;
}

/*
 * Missing Number
 * https://leetcode.com/problems/missing-number/
 *
 * Given an array nums containing n distinct numbers in the range [0, n], return the only number in the
 * range that is missing from the array.
 *
 * Follow up: Could you implement a solution using only O(1) extra space complexity and O(n) runtime complexity?
 *
Example 1:

Input: nums = [9,6,4,2,3,5,7,0,1]
Output: 8
Explanation: n = 9 since there are 9 numbers, so all numbers are in the range [0,9]. 8 is the missing number
in the range since it does not appear in nums.

Example 2:

Input: nums = [0]
Output: 1
Explanation: n = 1 since there is 1 number, so all numbers are in the range [0,1]. 1 is the missing number
in the range since it does not appear in nums.
 */
int missingNumberFaster(vector<int>& nums)
{
	int sum = 0, n = nums.size();
	// we can also use stl accumulate()
	sum = accumulate(begin(nums), end(nums), 0);
	/*
	for(auto n: nums){
		sum += n;
	}
	*/

	int req_sum = (n*(n+1))/2;

	return req_sum - sum;
}

bool not_sequential(int elem1, int elem2) {
	return(elem2 != elem1+1);
}

int missingNumber(vector<int>& nums)
{
	int missing_num = 0;
	cout << "Input ";
	printVector(nums);

	if(nums.size() < 2)
		return nums.size();

	sort(begin(nums), end(nums), less<int>());

	cout << "Sorted ";
	printVector(nums);

	auto missing_it = adjacent_find(begin(nums), end(nums), not_sequential);
	if(missing_it != end(nums)) {
		missing_num = *missing_it + 1;
		printf("Missing non-sequential number is %d\n", missing_num);
	}
	else {

		if(nums[0] == 0) {
			missing_num = nums[nums.size()-1] + 1;
		}
		else {
			missing_num = nums[0] - 1;
		}
		printf("Missing end-case number is %d\n", missing_num);
	}
	return missing_num;

}

/*
 * This is a demo task.

Write a function:

int solution(vector<int> &A);

that, given an array A of N integers, returns the smallest positive integer (greater than 0) that does not occur in A.

For example, given A = [1, 3, 6, 4, 1, 2], the function should return 5.

Given A = [1, 2, 3], the function should return 4.

Given A = [−1, −3], the function should return 1.

Write an efficient algorithm for the following assumptions:

N is an integer within the range [1..100,000];
each element of array A is an integer within the range [−1,000,000..1,000,000].
 */
// For example, for the input [4, 5, 6, 2] the solution returned a wrong answer (got 3 expected 1).
int codilitySolution(vector<int> &A) {
    // write your code in C++14 (g++ 6.2.0)
    int sum = 0;
    int nums = A.size();

    // First sort the array
    sort(begin(A), end(A), less<int>());

    // Get a sum of the array
    int arr_sum = 0;
    for(auto n : A) {
        arr_sum += n;
    }

    // Get a sum equal to a sequential number of array elements
    int first = A[0];
    int last = A[nums-1];
    sum = (nums * (first + last)) / 2;

    // We can remove the end cases here
    if(arr_sum <= 0) {
        return 1;
    }
    if(arr_sum == sum) {
    	if(first == 1) {
            return last + 1;
    	}
        else {
            return first - 1;
    	}
    }


    /* method 2: */
    // First make the array a set of unique sequential numbers by removing duplicates
    auto itAend = unique(begin(A), end(A));

	// Erase the old unused elements to resize the vector
	A.erase(itAend, end(A));

     // Get the new array size
    nums = A.size();

    /* Method 1: */
	int missing_num = 0;
    auto missing_it = adjacent_find(begin(A), end(A),
            [](int elem1, int elem2) {
	            return(elem2 != elem1+1);
                });
	if(missing_it != end(A)) {
		missing_num = *missing_it + 1;
		//printf("Missing non-sequential number is %d\n", missing_num);
	}
	else {  // These cases should have been previously handled
		if(A[0] == 0) {
			missing_num = A[nums-1] + 1;
		}
		else {
			missing_num = A[0] - 1;
		}
		//printf("Missing end-case number is %d\n", missing_num);
	}
	return missing_num;

    /* Method 2: should be faster than method 1...BUT I DOES NOT WORK! */
    // Now get the array sum over the remaining set of numbers
    #ifdef NOT_YET
    arr_sum = 0;
    printf("A[");
	for(auto n: A){
		arr_sum += n;
		printf("%d, ", n);
	}
	printf("]\n");


	printf("arr_sum = %d, nums = %d\n", arr_sum, nums);

    // Now use a well known algorithm for finding the sum of a sequential set of numbers
    // Get a sum equal to a sequential number of array elements
    first = A[0];
    last = A[nums-1];
    sum = ((nums+1) * (first + last)) / 2;

    printf("first = %d, last = %d, sum = %d, diff = %d\n", first, last, sum, sum - arr_sum);

	return sum - arr_sum;
	#endif
}

int oldmain() {


	int A[] = {1,12,31,42,55};
	List ll("Test List", A, 5);

	ll.displayList(ll.getListHead());
	cout << "Insert 23 into sorted list:" << endl;
	ll.sortedInsertNode(ll.getListHead(), 23);
	ll.displayList(ll.getListHead());
	cout << "Delete index 2 from list:" << endl;
	ll.deleteNode(ll.getListHead(), 2);
	ll.displayList(ll.getListHead());

	int C[]={10,20,40,50,60};
	int D[]={15,18,25,30,55};
	List lC("List C", C, 5);
	lC.displayList();
	List lD("List D", D, 5);
	lD.displayList();
	List lMerged("Merged List");
	lMerged.mergeLists(lC.getListHead(), lD.getListHead());
	lMerged.displayList();


	return 0;

	vector<int> numsVec{0,1};

	missingNumber(numsVec);

	return 0;

	int x = 10, y= 80, d = 30;
	printf("Frog jumps = %d, with x=%d, y=%d, d=%d\n", frogJumps(x, y, d), x, y, d);
	x=3; y=999111321; d=7;	// expecting 142730189
	printf("Frog jumps = %d, with x=%d, y=%d, d=%d\n", frogJumps(x, y, d), x, y, d);

	return 0;

	vector<int> testArray{3,3,9,3,9,7,9,1,1,2,2,4,4,5,5};

	printf("Odd occurrences in array found unpaired element %d\n", oddOccurrencesInArray(testArray));

	return 0;

	printf("Binary gap for N=0x%X = %d\n", 0x101, binaryGap(0x101));

	return 0;

	int N[10] = {1041, 1, 0x11, 0x1001, 0x1000100, 0x10000100, 0x10000001, 0x10000000, 0x10001, 0x100001};
	for(int test=0; test < 10; test++) {
		printf("Binary gap for N=0x%X = %d\n", N[test], binaryGap(N[test]));
	}

	return 0;


	ListNode *pListNode = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5, new ListNode(6, new ListNode(7, new ListNode(8, new ListNode(9, new ListNode(10))))))))));
	List RL("Reverse List");
    cout << "Input: (";
	RL.displayNode(pListNode);
    cout << ")" << endl;
    ListNode *revList = RL.reverseList(pListNode);
    cout << "Output: (";
	RL.displayNode(revList);
    cout << ")";
    return 0;

int item = 0;
	cout << "https://www.includehelp.com/icp/" << endl; // prints https://www.includehelp.com/icp/

	while(item != (-1))
	{
		displayMenu();
		item = getchar();
		switch (item)
		{
		case '1':
			runLengthStringEncoding();
			break;
		case '2':
			linearTimeArray012Sort();
			break;
		case '3':
			checkingAnagrams();
			break;
		case 'x':
		case 'X':
			cout << "Exiting program" << endl;
			item = (-1);
			break;
		default:
			cout << "Invalid item selected" << endl;
			break;
		}
	}
	return 0;
}

// https://leetcode.com/problems/min-stack/
/*
 * Min Stack
 *
Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
getMin() -- Retrieve the minimum element in the stack.
 */
class MinStack {
    stack <int> mstack;
    multiset<int> values;
    int minVal;
public:
    /** initialize your data structure here. */
    MinStack() {
        minVal = INT_MAX;
    }

    void push(int x) {
    	values.insert(x);
        mstack.push(x);
        minVal = *values.begin();
    }

    void pop() {
    	int val = mstack.top();
    	// VERY INTERESTING FACT ABOUT set.erase(const value_type& val);
    	// "All elements with a value equivalent to this are removed from the container."
    	auto iterase = values.find(val);
    	if(iterase != values.end()) {
    		values.erase(iterase);
    	}

        mstack.pop();
        minVal = *values.begin();
    }

    int top() {
        return mstack.top();
    }

    int getMin() {
        return minVal;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */
class Solution {
    vector<int> saved_nums;
    vector<int> *pnums;
public:
    Solution(vector<int>& nums) {
        //int nums_len = nums.size();
        pnums = &nums;
        saved_nums = nums;
    }

    /** Resets the array to its original configuration and return it. */
    vector<int> reset() {
        return saved_nums;
    }

    /** Returns a random shuffling of the array. */
    vector<int> shuffle() {
        random_shuffle ( pnums->begin(), pnums->end() );
        return *pnums;
    }
};

// https://leetcode.com/problems/count-primes/
/*
 * Count Primes
 *
 * Hints:
 * As we know the number must not be divisible by any number > n / 2, we can immediately
 * cut the total iterations half by dividing only up to n / 2. Could we still do better?
 *
 * Yes. We only need to consider factors up to √n because, if n is divisible by some
 * number p, then n = p × q and since p ≤ q, we could derive that p ≤ √n.
 *
 * The Sieve of Eratosthenes is one of the most efficient ways to find all prime numbers
 * up to n. We start off with a table of n numbers. Let's look at the first number, 2.
 * We know all multiples of 2 must not be primes, so we mark them off as non-primes. Then
 * we look at the next number, 3. Similarly, all multiples of 3 such as 3 × 2 = 6,
 * 3 × 3 = 9, ... must not be primes, so we mark them off as well. Now we look at the next
 * number, 4, which was already marked off. What does this tell you? Should you mark off
 * all multiples of 4 as well? 4 is not a prime because it is divisible by 2, which means
 * all multiples of 4 must also be divisible by 2 and were already marked off. So we can
 * skip 4 immediately and go to the next number, 5. Now, all multiples of 5 such as
 * 5 × 2 = 10, 5 × 3 = 15, 5 × 4 = 20, 5 × 5 = 25, ... can be marked off. There is a
 * slight optimization here, we do not need to start from 5 × 2 = 10. Where should we
 * start marking off? In fact, we can mark off multiples of 5 starting at 5 × 5 = 25,
 * because 5 × 2 = 10 was already marked off by multiple of 2, similarly 5 × 3 = 15 was
 * already marked off by multiple of 3. Therefore, if the current number is p, we can
 * always mark off multiples of p starting at p2, then in increments of p: p2 + p,
 * p2 + 2p, ... Now what should be the terminating loop condition? Yes, the terminating
 * loop condition can be p < √n, as all non-primes ≥ √n must have already been marked off.
 * When the loop terminates, all the numbers in the table that are non-marked are prime.
 *
 * The Sieve of Eratosthenes uses an extra O(n) memory and its runtime complexity is O(n log log n).
 */
bool isPrime(int num) {
	if (num <= 1) return false;
	// Loop's ending condition is i * i <= num instead of i <= sqrt(num)
	// to avoid repeatedly calling an expensive function sqrt().
	for (int i = 2; i * i <= num; i++) {
		if (num % i == 0) return false;
	}
	return true;
}

int countPrimes(int n) {
					  //0,1,2,3,4,5,6,7,8,9,10,11,12,13,     17,  19      23          29   31                37          41    43          47
	char first50[51] = {0,0,0,1,2,3,3,3,4,4,4, 4, 5, 5,6,6,6,6,7, 7,8,8,8,8,9,9,9,9,9,9,10,10,11,11,11,11,11,11,12,12,12,12,13,13,14,14,14,14,15,15,15};
	if(n < 50) {
		return first50[n];
	}

	vector<bool> isPrime(n, true);
	// Loop's ending condition is i * i < n instead of i < sqrt(n)
	// to avoid repeatedly calling an expensive function sqrt().
	for (int i = 2; i * i < n; i++) {
		if (!isPrime[i]) continue;
		for (int j = i * i; j < n; j += i) {
			isPrime[j] = false;
		}
	}
	int count = 15;
	for (int i = 51; i < n; i++) {
		if (isPrime[i]) count++;
	}
	return count;
}

int main()
{

	printf("long int size = %lu bytes\n", sizeof(long int));
	return 0;
	int n = 5;
    for(int stairs=1; stairs <= n; stairs++) {
        cout << string(n-stairs, ' ') << string(stairs, '#') << endl;
    }
	return 0;
	MinStack MS;
	MS.push(-2);
	cout << "getMin() = " << MS.getMin() << endl;
	MS.push(0);
	cout << "getMin() = " << MS.getMin() << endl;
	MS.push(-3);
	cout << "getMin() = " << MS.getMin() << endl;
	MS.pop();
	cout << "top = " << MS.top() << endl;
	cout << "getMin() = " << MS.getMin() << endl;

	return 0;
}
