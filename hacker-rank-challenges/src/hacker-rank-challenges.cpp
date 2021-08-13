//============================================================================
// Name        : hacker-rank-challenges.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://www.hackerrank.com/challenges/compare-the-triplets/
//============================================================================

#include <bits/stdc++.h>

using namespace std;

template < class ContainerT >
void tokenize(const string& str, ContainerT& tokens,
              const string& delimiters = " ", bool trimEmpty = false)
{
   size_t pos, lastPos = 0, length = str.length();

   using value_type = typename ContainerT::value_type;
   using size_type  = typename ContainerT::size_type;

   while(lastPos < length + 1)
   {
      pos = str.find_first_of(delimiters, lastPos);
      if(pos == std::string::npos)
      {
         pos = length;
      }

      if(pos != lastPos || !trimEmpty)
         tokens.push_back(value_type(str.data()+lastPos,
               (size_type)pos-lastPos ));

      lastPos = pos + 1;
   }
}

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

// Complete the compareTriplets function below.
vector<int> compareTriplets(vector<int> a, vector<int> b) {
	vector<int> result(2);

	for(size_t i=0; i<a.size(); i++) {
		result[0] += (a[i] > b[i]) ? 1 : 0;
		result[1] += (a[i] < b[i]) ? 1 : 0;
	}

	return result;
}

/*
 * Variable Sized Arrays
 * https://www.hackerrank.com/challenges/variable-sized-arrays/problem
 *
Consider an n-element array, A, where each index i in the array contains a reference to an array
of k integers (where the value of k(i) varies from array to array). Given A, you must answer q queries.
Each query is in the format i j, where i denotes an index in array j and  denotes an index in the array
located at A[i]. For each query, find and print the value of element j in the array at location A[i] on
a new line.

Input Format:
The first line contains two space-separated integers denoting the respective values of n (the number of
variable-length arrays) and q (the number of queries). Each line i of the n subsequent lines contains a
space-separated sequence in the format k A[i]0 A[i]1 … A[i]k-1 describing the k-element array located
at A[i]. Each of the q subsequent lines contains two space-separated integers describing the respective
values of i (an index in array A) and j (an index in the array referenced by A[i]) for a query.
 */
void variable_sized_arrays()
{
    int num_arrays=0;
    int num_queries=0;
    bool fileio = true;
    string line;
	string fname("vsa1.txt");
	ifstream ifile(fname);
	istream& str = fileio ? ifile : cin;

	if(fileio && ifile.fail()) {
	    cout << "Unable to open file " << fname << endl;
	    return;
	}

    getline(str,line);
    stringstream ss(line);
    ss >> num_arrays;
    ss >> num_queries;

    if(!fileio) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int nqmax = 100'000;
    if((num_arrays < 1) || (num_arrays > nqmax)) {
    	printf("Invalid number of arrays: %d\n", num_arrays);
    	return;
    }
    if((num_queries < 1) || (num_queries > nqmax)) {
    	printf("Invalid number of queries: %d\n", num_queries);
    	return;
    }
    printf("Number of arrays: %d\n", num_arrays);
    printf("Number of queries: %d\n", num_queries);

	const int kmax = 300'000;
	vector<vector<int>> nkarray;
	int array=0;
    while(num_arrays--) {
    	int kelems;
        getline(str,line);
        stringstream ss(line);
    	ss >> kelems;
    	if((kelems < 1) || (kelems > kmax)) {
    		printf("Invalid number of array elements: %d\n", kelems);
    		return;
    	}
    	vector<int> karray(kelems);
		printf("Array %d size %d: ", array, kelems);
    	for(int i=0; i<kelems; i++) {
    		ss >> karray[i];
    		printf("[%d]", karray[i]);
		}
    	cout << endl;
    	nkarray.push_back(karray);
    	array++;
    }
    cout << endl;

	int query=0;
    while(num_queries--) {
    	int idx, jdx;
        getline(str,line);
        stringstream ss(line);
        ss >> idx;
    	ss >> jdx;
    	cout << "Query " << ++query << ": " << nkarray[idx][jdx] << endl;
    }
    ifile.close();
}

/*
 * Vector-Sort
 * https://www.hackerrank.com/challenges/vector-sort/problem
 *
You are given N integers.Sort the N integers and print the sorted order.
 */
void vector_sort() {
    int num_integers=0;
    string line;

    cin >> num_integers;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    vector<int> vec(num_integers);
    getline(cin,line);
    stringstream ss(line);
    for(int i=0; i<num_integers; i++) {
        ss >> vec[i];
    }
    sort(vec.begin(), vec.end());
    for(auto& elem:vec) {
        cout << elem << " ";
    }
}

/*
 * Lower Bound-STL
 * https://www.hackerrank.com/challenges/cpp-lower-bound/problem
 *
You are given N integers in sorted order. Also, you are given Q queries. In each query, you will be given
an integer and you have to tell whether that integer is present in the array. If so, you have to tell at
which index it is present and if it is not present, you have to tell the index at which the smallest integer
that is just greater than the given number is present.

Input Format
The first line of the input contains the number of integers N. The next line contains N integers in sorted
order. The next line contains Q, the number of queries. Then Q lines follow each containing a single integer Y.

Note: If the same number is present multiple times, you have to print the first index at which it occurs.
Also, the input is such that you always have an answer for each query.

Output Format

For each query you have to print "Yes" (without the quotes) if the number is present and at which index(1-based)
it is present separated by a space. If the number is not present you have to print "No" (without the quotes)
followed by the index of the next smallest number just greater than that number. You have to output each query
in a new line.
 */
void lower_bound_stl()
{
    int num_integers=0;
    int num_queries=0;
    string line;

    cin >> num_integers;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    vector<int> vec(num_integers);
    getline(cin,line);
    stringstream ss(line);
    for(int i=0; i<num_integers; i++) {
        ss >> vec[i];
    }
    cin >> num_queries;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for(int i=0; i<num_queries; i++) {
        getline(cin,line);
        stringstream ss(line);
        int query;
        ss >> query;
        // Returns an iterator pointing to the first element in the range [first,last) which does not compare less than val.
        auto lbit = lower_bound(vec.begin(), vec.end(), query);
        if(lbit == vec.end()) {
            cout << "Error: All numbers are less than query value " << query << endl;
        }
        if(*lbit == query) {
            cout << "Yes " << (lbit - vec.begin()) + 1;
        }
        else {
            cout << "No " << (lbit - vec.begin()) + 1;
        }
        cout << endl;
    }
}

/*
 * Sets-STL
 * https://www.hackerrank.com/challenges/cpp-sets/problem
 *
Sets are a part of the C++ STL. Sets are containers that store unique elements following a specific order.
Coming to the problem, you will be given Q queries. Each query is of one of the following three types:
  1: Add an element x to the set.
  2: Delete an element x from the set. (If the number x is not present in the set, then do nothing).
  3: If the number x is present in the set, then print "Yes"(without quotes) else print "No"(without quotes).

Input Format:
The first line of the input contains Q where Q is the number of queries. The next Q lines contain 1 query
each. Each query consists of two integers y and x where y is the type of the query and x is an integer.

Constraints:
1 <= Q <= 10**5
1 <= y <= 3
1 <= x <= 10**9

Output Format:
For queries of type 3 print "Yes"(without quotes) if the number x is present in the set and if the number
is not present, then print "No"(without quotes). Each query of type 3 should be printed in a new line.

Sample Input:
8           :Q number of queries
1 9         :1 Add an element
1 6         :1 Add and element
1 10        :1 Add and element
1 4         :1 Add and element
3 6         :3 If x...
3 14        :3 If x...
2 6         :2 Delete and element
3 6         :3 If x...

Sample Output:
Yes
No
No
 */
void sets_stl()
{
    set<int> HackerSet;
    int num_queries=0;
    string line;
    const int ADD_ELEM=1;
    const int ERASE_ELEM=2;
    const int FIND_ELEM=3;

    cin >> num_queries;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for(int i=0; i<num_queries; i++) {
        getline(cin,line);
        stringstream ss(line);
        int query;
        ss >> query;
        int elem;
        ss >> elem;
        printf("Q%d = %d, elem = %d\n", i+1, query, elem);
        auto itr = HackerSet.find(elem);
        if(query == ADD_ELEM) {
            if(itr == HackerSet.end()) {
                HackerSet.emplace(elem);
            }
        }
        else if(query == ERASE_ELEM) {
            if(itr != HackerSet.end()) {
                HackerSet.erase(elem);
            }
        }
        else if(query == FIND_ELEM) {
            if(itr != HackerSet.end()) {
                cout << "Yes" << endl;
            }
            else {
                cout << "No" << endl;
            }
        }
        else {
            ;  // do nothing
        }
    }
}

/*
 * Maps-STL
 * https://www.hackerrank.com/challenges/cpp-maps/problem
 *
Maps are a part of the C++ STL.Maps are associative containers that store elements formed by a combination
of a key value and a mapped value, following a specific order.

You are appointed as the assistant to a teacher in a school and she is correcting the answer sheets of the
students.Each student can have multiple answer sheets.So the teacher has Q queries:
  1 X Y: Add the marks  to the student whose name is .
  2 X:   Erase the marks of the students whose name is .
  3 X:   Print the marks of the students whose name is . (If  didn't get any marks print .)

Input Format:
The first line of the input contains Q where Q is the number of queries. The next Q lines contain 1 query
each. The first integer, Type of each query is the type of the query. If query is of type 1, it consists
of one string and an integer X and Y where X is the name of the student and Y is the marks of the student.
If query is of type 2 or 3, it consists of a single string X where X is the name of the student.

Constraints:
1 <= Q <= 10**5
1 <= type <= 3
1 <= |X| <=6
1 <= Y <= 10**3

Output format:
For queries of type 3 print the marks of the given student.

Sample Input:
7
1 Jesse 20
1 Jess 12
1 Jess 18
3 Jess
3 Jesse
2 Jess
3 Jess

Sample Output:
30
20
0
 */
void maps_stl()
{
    map<string, vector<int>> HackerMap;
    int num_queries=0;
    string line;
    const int ADD_ELEM=1;
    const int ERASE_ELEM=2;
    const int FIND_ELEM=3;

    cin >> num_queries;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for(int i=0; i<num_queries; i++) {
        getline(cin,line);
        stringstream ss(line);
        int query;
        ss >> query;
        string student;
        ss >> student;
        auto map_itr = HackerMap.find(student);
        int marks = 0;
        if(query == ADD_ELEM) {
            ss >> marks;
            printf("Q%d = %d, student = %s, marks = %d\n", i+1, query, student.c_str(), marks);
            HackerMap[student].push_back(marks);
        }
        else if(query == ERASE_ELEM) {
            if(map_itr != HackerMap.end()) {
                HackerMap.erase(student);
            }
        }
        else if(query == FIND_ELEM) {
            // excellent info on looping through vector with a map:
            // http://www.cplusplus.com/forum/beginner/161248/
            if(map_itr != HackerMap.end()) {
                int marks_sum = 0;
                for(auto vec_itr=map_itr->second.cbegin();
                    vec_itr != map_itr->second.cend(); ++vec_itr) {
                    marks_sum += *vec_itr;
                }
                cout << marks_sum << endl;
            }
            else {
                cout << marks << endl;
            }
        }
        else {
            ;  // do nothing
        }
    }
}

/*
 * Print Pretty
 * https://www.hackerrank.com/challenges/prettyprint/problem
 *
Given a text file with many lines of numbers to format and print, for each row of 3 space-separated
doubles, format and print the numbers using the specifications in the Output Format section below.

Input Format:
The first line contains an integer, T, the number of test cases. Each of the T subsequent lines
describes a test case as 3 space-separated floating-point numbers: A, B, and C, respectively.

Constraints:
1<= T <= 1000
Each number will fit into a double

Output Format:
For each test case, print 3 lines containing the formatted A, B, and C, respectively.
Each A, B, and C must be formatted as follows:

  1 A: Strip its decimal (i.e., truncate it) and print its hexadecimal representation (including
       the 0x prefix) in lower case letters.
  2 B: Print it to a scale of 2 decimal places, preceded by a + or - sign (indicating if it's
       positive or negative), right justified, and left-padded with underscores so that the printed
       result is exactly 15 characters wide.
  3 C: Print it to a scale of exactly nine decimal places, expressed in scientific notation using
       upper case.

Sample Input:
1
100.345 2006.008 2331.41592653498

Sample Output:
0x64
_______+2006.01
2.331415927E+03

 */
void pretty_print() {
    int num_test_cases = 0;
    string line;
    double A=0;
    double B=0;
    double C=0;

    cin >> num_test_cases;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> A >> B >> C;
    long long A_ll = static_cast<long long>(A);

    /*
     * One way to change formatting is to change ios_base::fmtflags
     * The below example is the same as using the stream std::manipulators 'uppercase'.
     *
    // To make output all lower case:
    cout << nouppercase;
    // OR:
    ios_base::fmtflags ff;
    ff = cout.flags();
    ff &= ~cout.uppercase;
    cout.flags(ff);
    */

    cout << left << setbase(16) << showbase << nouppercase << A_ll << endl;
    cout << right << setbase(10) << fixed << setprecision(2) << setw(15) << setfill('_') << showpos << B << endl;
    cout << fixed << scientific << setprecision(9) << uppercase << noshowpos << C << endl;
    return;
}

/*
 * Vector-Erase
 * https://www.hackerrank.com/challenges/vector-erase/problem
 *
You are provided with a vector of N integers. Then, you are given 2 queries. For the first query,
you are provided with  integer, which denotes a position in the vector. The value at this position
in the vector needs to be erased. The next query consists of 2 integers denoting a range of the
positions in the vector. The elements which fall under that range should be removed. The second
query is performed on the updated vector which we get after performing the first query.

Input Format

The first line of the input contains an integer N. The next line contains N space separated integers
(1-based index). The third line contains a single integer x, denoting the position of an element that
should be removed from the vector. The fourth line contains two integers a and b denoting the range
that should be erased from the vector inclusive of a and exclusive of b.

Constraints:
1 <= N <= 10**5
1 <= x <= N
1 <= a <= b <= N

Output Format:
Print the size of the vector in the first line and the elements of the vector after the two erase
operations in the second line separated by space.

Sample Input:
6
1 4 6 2 8 9
2
2 4
erase 2:
1 6 2 8 9
erase range 2~4:
1 [6 2] 8 9


Sample Output:
3
1 8 9

Explanation:
The first query is to erase the 2nd element in the vector, which is 4. Then, modified vector is
{1 6 2 8 9}. Next we want to remove the range of 2~4, which means the 2nd and 3rd elements should
be removed. Then 6 and 2 in the modified vector are removed and we finally get {1 8 9}.
 */
void vector_erase()
{
    int num_integers=0;
    int single_elem=0;
    int range_begin=0;
    int range_end=0;
    string line;

    cin >> num_integers;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    vector<int> vec(num_integers);
    getline(cin,line);
    stringstream ss(line);
    for(int i=0; i<num_integers; i++) {
        ss >> vec[i];
    }
    cin >> single_elem;;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> range_begin >> range_end;

    //printf("Starting Vec[%d]: ", num_integers);
    //for(auto& elem : vec) {
    //    cout << elem << " ";
    //}
    //cout << endl;

    vec.erase(vec.begin()+single_elem-1);
    vec.erase(vec.begin()+range_begin-1, vec.begin()+range_end-1);

    cout << vec.size() << endl;
    // printf("Erased Vec[%d]: ", num_integers);
    for(auto& elem : vec) {
        cout << elem << " ";
    }
    return;

}

/*
 * Deque-STL
 * https://www.hackerrank.com/challenges/deque-stl/problem
 *
Double ended queue or Deque(part of C++ STL) are sequence containers with dynamic sizes that can
be expanded or contracted on both ends (either its front or its back).

Given a set of arrays of size N and an integer K, you have to find the maximum integer for each
and every contiguous subarray of size  for each of the given arrays.

Input Format:
First line of input will contain the number of test cases T. For each test case, you will be
given the size of array N and the size of subarray to be used K. This will be followed by the
elements of the array Ai.

Constraints:
1<= T <= 1000
1<= N <= 10000
1<= K <= N
1<= Ai <= 10000, where Ai is the ith element in the array A

Output Format:
For each of the contiguous subarrays of size K of each array, you have to print the maximum integer.

Sample Input:
2                   = Number of test cases
5 2                 = Array size 5, subarray size 2
3 4 6 3 4           = Array[5] elements
7 4                 = Array size 7, sub array size 4
3 4 5 8 1 4 10      = Array[7] elements

Sample Output:
4 6 6 4
8 8 8 10

Explanation:
For the first case, the contiguous subarrays of size 2 are {3,4},{4,6},{6,3} and {3,4}.
The 4 maximum elements of subarray of size 2 are: 4 6 6 4.

For the second case,the contiguous subarrays of size 4 are {3,4,5,8},{4,5,8,1},{5,8,1,4}
and {8,1,4,10}. The 4 maximum element of subarray of size 4 are: 8 8 8 10.
 */
void printKMax(int arr[], int n, int k) {
    /*
    ofstream fout;
    // Open a test file and truncate the data for new output data
    fout.open("/home/carlos/Documents/kmax-test6.txt", ios::out | ios::trunc);
    if(!fout.is_open()) {
        cout << "Unable to open output file\n";
        return;
    }
    */
    deque<int> dq;

    int i;
    for(i=0 ; i < k; ++i)
    {
        // For every element, the previous
        // smaller elements are useless so
        // remove them from dq
        while ((!dq.empty()) && arr[i] >= arr[dq.back()]) {
            // Remove from rear
            dq.pop_back();
        }

        // Add new element at rear of queue
        dq.push_back(i);
    }

    // Process rest of the elements,
    // i.e., from arr[k] to arr[n-1]
    for (; i < n; ++i)
    {

        // The element at the front of
        // the queue is the largest element of
        // previous window, so print it
        //fout << arr[dq.front()] << " ";
        //cout << arr[dq.front()] << " ";
        printf("%d, ", arr[dq.front()]);

        // Remove the elements which
        // are out of this window
        /*
         * This is used to keep the window of k updated with the correct number
         * of elements required in the window. As 'i' moves ahead, there is
         * requirement to remove first indexes which are not fitting in the window
         * that is why we subtract k from current i which will give us the first
         * index of the updated window. Hence what all is below or equal to (i-k)
         * needs to be removed as these indexes will be from old window.
         */
        //while ((!dq.empty()) && dq.front() <= i - k) {
        if(dq.front() <= (i - k)) {
            // Remove from front of queue
            dq.pop_front();
        }

        // Remove all elements
        // smaller than the currently
        // being added element (remove
        // useless elements)
        while ((!dq.empty()) && arr[i] >= arr[dq.back()]) {
            dq.pop_back();
        }

        // Add current element at the rear of dq
        dq.push_back(i);
    }

    // Print the maximum element
    // of last window
    //fout << arr[dq.front()];
    cout << arr[dq.front()];
    cout << "\nTest complete" << endl;
    //fout.close();
}

void deque_stl()
{
    int num_test_cases=0;
    int num_integers=0;
    int subarray_size=0;
    string line;

    //bool fileio = false;
    string fname("/home/carlos/Documents/input06.txt");
    //ifstream ifile(fname);
    //istream& str = fileio ? ifile : cin;

    //if(fileio && ifile.fail()) {
    //    cout << "Unable to open file " << fname << endl;
    //    return;
    //}

    getline(cin,line);
    stringstream ss(line);
    ss >> num_test_cases;
    printf("Number of test cases = %d\n", num_test_cases);

    //if(!fileio) {
        //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //}

    int test = 1;
    while(num_test_cases) {
        getline(cin,line);
        printf("Read input line: %s\n", line.c_str());
        stringstream nums_ss(line);
        nums_ss >> num_integers >> subarray_size;
        //if(!fileio) {
        //    cin.ignore(numeric_limits<streamsize>::max(), '\n');
        //}
        cout << "\nTest " << test++ << ", num ints = " << num_integers << ", subarray size = " << subarray_size << endl;
        int arr[num_integers];
        getline(cin,line);
        stringstream data_ss(line);
        for(int i=0; i<num_integers; i++) {
            data_ss >> arr[i];
        }
        cout << endl;
        for(auto& elem: arr) {
            printf("%d, ", elem);
        }
        cout << endl;

        printKMax(arr, num_integers, subarray_size);
        num_test_cases--;
    }
    //ifile.close();
}

/*
 * Cpp exception handling
 * https://www.hackerrank.com/challenges/cpp-exception-handling/problem
 *
You are required to extend the existing code so that it handles std::invalid_argument exception properly.
More specifically, you have to extend the implementation of process_input function. It takes integer n
as an argument and has to work as follows:

    1. It calls function largest_proper_divisor(n).
    2. If this call returns a value without raising an exception, it should print in a single line 'result=d'
       where  is the returned value.
    3. Otherwise, if the call raises a std::invalid_argument exception, it has to print in a single line
       the string representation of the raised exception, i.e. its message. Finally, no matter if the
       exception is raised or not, it should print in a single line returning control flow to caller after
       any other previously printed output.

To keep the code quality high, you are advised to have exactly one line printing returning control flow to
caller in the body of process_input function.

Input Format:
The input is read by the provided locked code template. In the only line of the input, there is a single
integer n, which is going to be the argument passed to function process_input.

Sample Input 0:
0
Sample Output 0:
    "largest proper divisor is not defined for n=0"
    "returning control flow to caller"
Explanation 0:
In the first sample, n=0, so the call largest_proper_divisor(0) raises an exception. In this case, the
function process_input prints two lines. In the first of them it prints the string representation of
the raised exception, and in the second line it prints returning control flow to caller.

Sample Input 9:
9
Sample Output 9:
    "result=3"
    "returning control flow to caller"
Explanation 1

In the first sample, n=9, so the call largest_proper_divisor(9) doesn't raise an exception and returns
value 3. In this case, the function process_input prints two lines. In the first of them it prints
result=3 because the returned value by largest_proper_divisor(9) is 3, and in the second line it prints
returning control flow to caller.
*/
int largest_proper_divisor(int n) {
    if (n == 0) {
        throw invalid_argument("largest proper divisor is not defined for n=0");
    }
    if (n == 1) {
        throw invalid_argument("largest proper divisor is not defined for n=1");
    }
    for (int i = n/2; i >= 1; --i) {
        if (n % i == 0) {
            return i;
        }
    }
    return -1; // will never happen
}

void process_input(int n) {
    try {
        int d = largest_proper_divisor(n);
        cout << "result=" << d << endl;
    }
    catch (const std::invalid_argument& ia) {
       std::cerr << ia.what() << endl;
    }
    cout << "returning control flow to caller" << endl;
}

void test_invalid_arg_exception()
{
    int n;

    for(int i=0; i<5; i++) {
    cin >> n;
    cout << "Input arg = " << n << endl;
    process_input(n);
    }
}

/*
 * C++ Class Template Specialization
 * https://www.hackerrank.com/challenges/cpp-class-template-specialization/problem
 *
You are given a main function which reads the enumeration values for two different types as input,
then prints out the corresponding enumeration names. Write a class template that can provide the
names of the enumeration values for both types. If the enumeration value is not valid, then print
unknown.

Input Format:
The first line contains t, the number of test cases.
Each of the t subsequent lines contains two space-separated integers. The first integer is a color
value, c, and the second integer is a fruit value, f.

Output Format:
The locked stub code in your editor prints t lines containing the color name and the fruit name
corresponding to the input enumeration index.

Sample Input:
2
1 0
3 3

Sample Output:
green apple
unknown unknown

Explanation
Since t=2, there are two lines of output.
    1. The two input index values, 1 and 0, correspond to green in the color enumeration and
       apple in the fruit enumeration. Thus, we print green apple.
    2. The two input values, 3 and 3, are outside of the range of our enums. Thus, we print
       unknown unknown.
 */
enum class Color { red, green, orange };
enum class Fruit { apple, orange, pear };


template <typename T> struct Traits;    // declaration

template<>  // specialization
struct Traits<Color> {
    static string name(int color_type) {
        static const string ColorTypes[3] = {"red", "green", "orange"};
        switch(static_cast<Color>(color_type)) {
        case Color::red:
        case Color::green:
        case Color::orange:
            return ColorTypes[color_type];
        default:
            return "unknown";
        }
    }
};

template<>  // specialization
struct Traits<Fruit> {
    static string name(int fruit_type) {
        static const string FruitTypes[3] = {"apple", "orange", "pear"};

        Fruit f = static_cast<Fruit>(fruit_type);

        if(f >= Fruit::apple && f <= Fruit::pear) {
            return FruitTypes[fruit_type];
        } else {
            return "unknown";
        }
    }
};

int test_template_specialization()
{
    int t = 0; std::cin >> t;

    for (int i=0; i!=t; ++i) {
        int index1; std::cin >> index1;
        int index2; std::cin >> index2;
        cout << Traits<Color>::name(index1) << " ";
        cout << Traits<Fruit>::name(index2) << "\n";
    }
    return 0;
}

/*
 * Attending Workshops
 * https://www.hackerrank.com/challenges/attending-workshops/problem
 *
 * Solution info from: https://www.programmersought.com/article/66473423996/
 *
A student signed up for N workshops and wants to attend the maximum number of workshops where
no two workshops overlap. You must do the following:

Implement 2 structures:

    1. struct Workshop having the following members:
       * The workshop's start time.
       * The workshop's duration.
       * The workshop's end time.

    2. struct Available_Workshops having the following members:
       * An integer, N (the number of workshops the student signed up for).
       * An array of type Workshop array having size N.

Implement 2 functions:

    1. Available_Workshops* initialize (int start_time[], int duration[], int n)
       Creates an Available_Workshops object and initializes its elements using the elements
       in the 'start_time'  and 'duration[]' parameters (both are of size N). Here, 'start_time[i]'
       and 'duration[i]' are the respective start time and duration for the ith workshop. This
       function must return a pointer to an Available_Workshops object.

    2. int CalculateMaxWorkshops(Available_Workshops* ptr)
       Returns the maximum number of workshops the student can attend—without overlap. The next
       workshop cannot be attended until the previous workshop ends.

    Note: An array of unknown size () should be declared as follows:

        DataType* arrayName = new DataType[n];

Constraints:
    1 <= N <= 10**5
    0 <= start_time <= 10**3
    0 <= duration <= 10**3
Input Format:
    Input from stdin is handled by the locked code in the editor; you simply need to write your
    functions to meet the specifications of the problem statement above.

Output Format:
    Output to stdout is handled for you.

Your initialize function must return a pointer to an Available_Workshops object.
Your CalculateMaxWorkshops function must return maximum number of non-overlapping workshops
the student can attend.

Sample Input:
6
1 3 0 5 5 8
1 1 6 2 4 1

Sample Output:
CalculateMaxWorkshops should return 4.

Explanation:
    The first line denotes N, the number of workshops.
    The next line contains N space-separated integers where the ith integer is the ith workshop's start time.
    The next line contains N space-separated integers where the ith integer is the ith workshop's duration.

The student can attend the workshops 0,1,3 and 5 without overlap, so CalculateMaxWorkshops returns
4 to main (which then prints 4 to std out).
 */

//Define the structs Workshops and Available_Workshops.
//#define DEBUG_AWS   1
struct Workshop {
    int id;
       // The workshop's start time.
    int start_time;
       // The workshop's duration.
    int duration;
       // The workshop's end time.
    int end_time;
};

struct Available_Workshops {
       // An integer, N (the number of workshops the student signed up for)
    int num_workshops;
       // An array of type Workshop array having size N.
    vector<struct Workshop *> Workshops;

};

// Implement the functions initialize and CalculateMaxWorkshops
Available_Workshops *initialize(int start_time[], int duration[], int n) {
    Available_Workshops* pAW = new (struct Available_Workshops);

    pAW->num_workshops = n;

    for(int i=0; i<n; i++) {
        struct Workshop *ws = new Workshop;
        ws->id = i;
        ws->start_time = start_time[i];
        ws->duration = duration[i];
        ws->end_time = ws->start_time + ws->duration;
        pAW->Workshops.push_back(ws);
    }
    return pAW;
}

bool non_decreasing_end_time(struct Workshop *wsa, struct Workshop *wsb) {
    return (wsa->end_time < wsb->end_time);
}

// AKA the Greedy algorithm for activity scheduling
int CalculateMaxWorkshops(Available_Workshops *aws) {
    if(aws->num_workshops == 1) {
        return 1;
    }
    vector<bool>selected_workshops(aws->num_workshops);
    int max_workshops = 0;
    sort(aws->Workshops.begin(), aws->Workshops.end(), non_decreasing_end_time);

#ifdef DEBUG_AWS
    cout << "WS End Time Sorted Schedule:" << endl;
    for(auto& wsp : aws->Workshops) {
        cout << "[" << wsp->id << ":e=" << wsp->end_time << " - s=" << wsp->start_time << "]" << endl;
    }
#endif

    selected_workshops[0] = true;
    max_workshops = 1;
    int j=0;
    for(int i=1; i<aws->num_workshops; i++) {
        struct Workshop *current_ws = aws->Workshops[j];
        struct Workshop *next_ws = aws->Workshops[i];

        // if next activity does not overlap with current activity, then add next activity to schedule
        if(next_ws->start_time >= current_ws->end_time) {
            selected_workshops[i] = true;
            // current = next
            j=i;
            max_workshops++;
        }
        else {
            selected_workshops[i] = false;
        }
    }
#ifdef DEBUG_AWS
    cout << "\nWS Max Schedule:" << endl;
    int i = 0;
    for(auto& wsp : aws->Workshops) {
        if(selected_workshops[i++]) {
            cout << "[" << wsp->id << ":s=" << wsp->start_time << "- e=" << wsp->end_time << "]" << endl;
        }
    }
#endif

    return max_workshops;
}

int test_workshops() {
    int n; // number of workshops
    cin >> n;
    // create arrays of unknown size n
    int* start_time = new int[n];
    int* duration = new int[n];

    for(int i=0; i < n; i++){
        cin >> start_time[i];
    }
    for(int i = 0; i < n; i++){
        cin >> duration[i];
    }

    Available_Workshops * ptr;
    ptr = initialize(start_time,duration, n);
    int max_workshops = CalculateMaxWorkshops(ptr);
    cout << "Max Workshops = " << max_workshops << endl;
    return 0;
}

/*
 * Bit Array
 * https://www.hackerrank.com/challenges/bitset-1/problem
 *
You are given four integers: N, S, P, Q. You will use them in order to create the sequence 'a'
with the following pseudo-code.

a[0] = S (modulo 2^31)
for i = 1 to N-1
    a[i] = a[i-1]*P+Q (modulo 2^31)
///////////////////////////  https://en.wikipedia.org/wiki/Modular_arithmetic
Notes:
Congruence modulo n is denoted:
a ≡ b(mod n)
    The statement a ≡ b (mod n) asserts is that a and b have the same remainder when divided by n.
That is,
    a=pn+r
    b=qn+r
where 0 ≤ r < n is the common remainder. Subtracting these two expressions, we recover the
previous relation:

    a-b=kn

by setting k = p − q.

Examples:
    38 ≡ 14 (mod 12)
    because 38-14 = 24, which is a multiple of 12 . Another way to express this is to say that
    both 38 and 14 have the same remainder 2, when divided by 12.

/////////////////////////////
Your task is to calculate the number of distinct integers in the sequence 'a'.

Input Format:
Four space separated integers on a single line, N, S, P, and Q respectively.

Output Format:
A single integer that denotes the number of distinct integers in the sequence .

Constraints
1 <= N <= 10**8
0<= S,P,Q < 2**31

Sample Input:
3 1 1 1

Sample Output:
3

Explanation:
a = [1,2,3]
Hence, there are 3 different integers in the sequence.
 */
unsigned int two_pow_31 = 0x80000000;
void test_bitarray_problem()
{
    unsigned int N=3;
    unsigned int S=1;
    unsigned int P=1;
    unsigned int Q=1;
    vector<unsigned long long> a_seq;

    // cin >> N >> S >> P >> Q;
/*
a[0] = S (modulo 2^31)
for i = 1 to N-1
    a[i] = a[i-1]*P+Q (modulo 2^31)
 */
    a_seq[0] = S % 0x80000000;
    for(unsigned int i=1; i<N; i++) {
        unsigned int Qmod = Q % two_pow_31;
        a_seq[i] = a_seq[i-1] * P + Qmod;
    }

    cout << "\nA[";
    for(auto& a : a_seq) {
        cout << a << ", ";
    }
    cout << "]" << endl;

}

/*
 * Magic Spells
 * https://www.hackerrank.com/challenges/magic-spells/problem
 *
While playing a video game, you are battling a powerful dark wizard. He casts his spells from
a distance, giving you only a few seconds to react and conjure your counterspells. For a
counterspell to be effective, you must first identify what kind of spell you are dealing with.
The wizard uses scrolls to conjure his spells, and sometimes he uses some of his generic spells
that restore his stamina. In that case, you will be able to extract the name of the scroll from
the spell. Then you need to find out how similar this new spell is to the spell formulas written
in your spell journal.

Spend some time reviewing the locked code in your editor, and complete the body of the
counterspell function. Check Dynamic cast (http://en.cppreference.com/w/cpp/language/dynamic_cast)
to get an idea of how to solve this challenge.

Input Format:
The wizard will read T scrolls, which are hidden from you. Every time he casts a spell,
it's passed as an argument to your counterspell function.

Constraints
1 <= T <= 100
1 <= S <= 1000, where S is a scroll name
Each scroll S, consists of uppercase and lowercase letters.

Output Format:
After identifying the given spell, print its name and power.
If it is a generic spell, find a subsequence of letters that are contained in both the spell name
and your spell journal. Among all such subsequences, find and print the length of the longest
one on a new line.

Sample Input:
3
fire 5
AquaVitae 999 AruTaVae
frost 7

Sample Output:
Fireball: 5
6
Frostbite: 7

Explanation
Fireball and Frostbite are common spell types.
AquaVitae is not, and when you compare it with AruTaVae in your spell journal, you get a sequence: AuaVae
 */
enum class SpellType { UNSET, GENERIC_SPELL, KNOWN_SPELL};

#ifdef MY_WIZARD_SPELL_CLASS
class Spell {
    int spell_power;
    SpellType spell_type;
    string spell_name;
public:
    Spell (int power) {
        spell_type = SpellType::KNOWN_SPELL;
        spell_power = power;
        spell_name = "unset";
    }
    Spell (const string& name) {
        spell_type = SpellType::GENERIC_SPELL;
        spell_power = 999;
        spell_name = name;
    }
    void setSpellName(const string& name) {
        spell_name = name;
    }
    string& getSpellName() {
        return spell_name;
    }
    void setSpellPower(const int power) {
        spell_power = power;
    }
    const int getSpellPower() {
        return spell_power;
    }
    SpellType getSpellType() {
        return spell_type;
    }
    void setSpellType(SpellType type) {
        spell_type = type;
    }

};

class Fireball: public Spell {
public:
    Fireball(int power) : Spell(power)  {
        setSpellName("fire");
    }
};

class Frostbite: public Spell {
public:
    Frostbite(int power) : Spell(power)  {
        setSpellName("frost");
    }
};

class Waterbolt: public Spell {
public:
    Waterbolt(int power) : Spell(power)  {
        setSpellName("water");
    }
};

class Thunderstorm: public Spell {
public:
    Thunderstorm(int power) : Spell(power)  {
        setSpellName("thunder");
    }
};
#endif

class Spell {
    private:
        string scrollName;
    public:
        Spell(): scrollName("") { }
        Spell(string name): scrollName(name) { }
        virtual ~Spell() { }
        string revealScrollName() {
            return scrollName;
        }
};

class Fireball : public Spell {
    private: int power;
    public:
        Fireball(int power): power(power) { }
        void revealFirepower(){
            cout << "Fireball: " << power << endl;
        }
};

class Frostbite : public Spell {
    private: int power;
    public:
        Frostbite(int power): power(power) { }
        void revealFrostpower(){
            cout << "Frostbite: " << power << endl;
        }
};

class Thunderstorm : public Spell {
    private: int power;
    public:
        Thunderstorm(int power): power(power) { }
        void revealThunderpower(){
            cout << "Thunderstorm: " << power << endl;
        }
};

class Waterbolt : public Spell {
    private: int power;
    public:
        Waterbolt(int power): power(power) { }
        void revealWaterpower(){
            cout << "Waterbolt: " << power << endl;
        }
};

class SpellJournal {
    public:
        static string journal;
        static string read() {
            return journal;
        }
};
string SpellJournal::journal = "";

/* Handrolled solution to longest common sequence */
string getLcs(string s, string t) {
    string lcs;
    int slen = s.size();
    int tlen = t.size();

    if(abs(slen - tlen) > k) {
        return "NO";
    }

    int minlen = (slen > tlen) ? slen : tlen;
    int i = 0;
    int j = 0;

    while(i < minlen) {
        if(s[i] == t[j]) {
            lcs.push_back(s[i]);
        }
        else if(s[i+1] == t[j]) {
            lcs.push_back(t[j]);
            i++;
        }
        else if(s[i] == t[j+1]) {
            lcs.push_back(s[i]);
            j++;
        }
        i++;
        j++;
    }
    cout << "LCS = '" << lcs << "'" << endl;
    return lcs;
}

void counterspell(Spell *spell)
{
    string scrollName = std::move(spell->revealScrollName());
    int scrollLen = scrollName.length();
    bool isGenericSpell = (scrollLen > 0) ? true : false;
    if(isGenericSpell) {
        string& genSpellName = SpellJournal::journal;
        int genSpellLen = genSpellName.length();

        // derived from https://www.geeksforgeeks.org/longest-common-subsequence-dp-4/
        int lcs[scrollLen + 1][genSpellLen + 1];

        for(int i=0; i<=scrollLen; i++) {
            for(int j=0; j<=genSpellLen; j++) {
                if(i ==0 || j == 0) {
                    lcs[i][j] = 0;
                }
                else if(scrollName[i-1] == genSpellName[j-1]) {
                    lcs[i][j] = lcs[i - 1][j - 1] + 1;
                }
                else {
                    lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
                }
            }
        }

        int lcs_len = lcs[scrollLen][genSpellLen];
        cout << lcs_len << endl;
        //printf("length of LCS between generic spell '%s' and scroll '%s' is %d bytes\n",
        //        genSpellName.c_str(), scrollName.c_str(), lcs_len);
    }
    else {
        Fireball *fireSpell = dynamic_cast<Fireball*> (spell);
        if(fireSpell) {
            fireSpell->revealFirepower();
            return;
        }
        Frostbite *frostSpell = dynamic_cast<Frostbite*> (spell);
        if(frostSpell) {
            frostSpell->revealFrostpower();
            return;
        }
        Thunderstorm *thunderSpell = dynamic_cast<Thunderstorm*> (spell);
        if(thunderSpell) {
            thunderSpell->revealThunderpower();
            return;
        }
        Waterbolt *waterSpell = dynamic_cast<Waterbolt*> (spell);
        if(waterSpell) {
            waterSpell->revealWaterpower();
            return;
        }
        cout << "Unidentified spell!" << endl;
    }
}

class Wizard {
public:
    Spell *cast() {
        Spell *spell;
        string s; cin >> s;
        int power; cin >> power;
        //cout << "Casting spell '" << s << " " << power << "'" << endl;
        if(s == "fire") {
            spell = new Fireball(power);
        }
        else if(s == "frost") {
            spell = new Frostbite(power);
        }
        else if(s == "water") {
            spell = new Waterbolt(power);
        }
        else if(s == "thunder") {
            spell = new Thunderstorm(power);
        }
        else {
            spell = new Spell(s);
            string journal;
            cin >> SpellJournal::journal;
        }
        return spell;
    }
};


/*
5
fire 5
frost 10
water 15
thunder 20
AquaVitae 999 AruTaVae

 */

int test_magic_spells()
{
    int T;
    cin >> T;
    //cout << "Tests = " << T << endl;
    Wizard Arawn;
    while(T--) {
        Spell *spell = Arawn.cast();
        counterspell(spell);
    }
    return 0;
}

// derived from https://www.geeksforgeeks.org/longest-common-subsequence-dp-4/
int lcs_str(string& xs, string& ys) {
    int xs_len = xs.length();
    int ys_len = ys.length();
    int L[xs_len + 1][ys_len + 1];

    for(int i=0; i<=xs_len; i++) {
        for(int j=0; j<=ys_len; j++) {
            if(i ==0 || j == 0) {
                L[i][j] = 0;
            }
            else if(xs[i-1] == ys[j-1]) {
                L[i][j] = L[i - 1][j - 1] + 1;
            }
            else {
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
            }
        }
    }

    return L[xs_len][ys_len];
}

int main()
{
    test_magic_spells();
    return 0;

    test_bitarray_problem();
    return 0;

    test_workshops();
    return 0;

    test_template_specialization();
    return 0;

    test_invalid_arg_exception();
    return 0;

    //Squirrelly bullshit 2d array indexing
    //int a2[2][4] = {3, 6, 9, 12, 15, 18, 21, 24};
    //       cout << *(a2[1] + 2) << *(*(a2 + 1) + 2) << 2[1[a2]];
    //return 0;

    deque_stl();
    return 0;

    pretty_print();
    return 0;

    variable_sized_arrays();
    return 0;
    string a_temp_temp;
    getline(cin, a_temp_temp);

    vector<string> a_temp = split(rtrim(a_temp_temp));

    vector<int> a(3);

    for (int i = 0; i < 3; i++) {
        int a_item = stoi(a_temp[i]);

        a[i] = a_item;
    }

    string b_temp_temp;
    getline(cin, b_temp_temp);

    vector<string> b_temp = split(rtrim(b_temp_temp));

    vector<int> b(3);

    for (int i = 0; i < 3; i++) {
        int b_item = stoi(b_temp[i]);

        b[i] = b_item;
    }

    vector<int> result = compareTriplets(a, b);

    ofstream fout(getenv("OUTPUT_PATH"));
    for (int i = 0; i < (int)result.size(); i++) {
        fout << result[i];

        if (i != (int)result.size() - 1) {
            fout << " ";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

// https://stackoverflow.com/a/1493195/6101104

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}

void nextMove(int n, int r, int c, vector <string> grid){
	//vector<bool> verified_moves(4, true);
	//enum { left, right, up, down };
	int p_row = 0;
	int p_col = 0;
    //your logic here
	for(auto s : grid) {
		size_t col = s.find('p');
		if(col != string::npos) {
			p_col = col;
			break;
		}
		p_row++;
	}

	/*
	if(r == 0) { verified_moves[up] = false; }
	else if(r == n-1) { verified_moves[down] = false; }

	if(c == 0) { verified_moves[left] = false; }
	else if(c == n-1) { verified_moves[right] = false; }
	*/

	if(p_col < c) {
		cout << "LEFT";
	}
	else if(p_col > c) {
		cout << "RIGHT";
	}
	else if(p_row < r) {
		cout << "UP";
	}
	else {
		cout << "DOWN";
	}

}

