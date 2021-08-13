//============================================================================
// Name        : hacker-rank-problem-solving.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://www.hackerrank.com/
//============================================================================

#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

string ltrim(const string &);
string rtrim(const string &);
string& lft_trim(string& str, const string& chars);
string& rt_trim(string& str, const string& chars);
string& trim(string& str, const string& chars);

vector<string> split_string(string);
vector<string> split(const string &);
template<class T>
void printVector(string name, vector<T> const &vec) {
    cout << name << ": " << endl;
    cout << "  [ ";
    for (T val: vec) {
        cout << val << " ";
    }
    cout << "]" << endl;
}
template<class T>
void printMatrix(string name, vector<vector<T>> const &mat) {
    cout << "Matrix " << name << ":" << endl;
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

/*
 * Grading Students
 *
HackerLand University has the following grading policy:

Every student receives a  in the inclusive range from 0 to 100.
Any grade less than40  is a failing grade.
Sam is a professor at the university and likes to round each student's  according to these rules:

    o If the difference between the grade and the next multiple of 5 is less than 3, round grade up to the next multiple of 5.
If the value of grade is less than 38, no rounding occurs as the result will still be a failing grade.

Examples:
    o grade = 84 round to 84 (85 - 84 is less than 3)
    o grade = 29 do not round (result is less than 40)
    o grade = 57 do not round (60 - 57 is 3 or higher)

Given the initial value of grade for each of Sam's n students, write code to automate the rounding process.

Function Description:
Complete the function gradingStudents in the editor below.

gradingStudents has the following parameter(s):
    o int grades[n]: the grades before rounding

Returns
    o int[n]: the grades after rounding as appropriate

Input Format:
The first line contains a single integer, n, the number of students.
Each line i of the n subsequent lines contains a single integer, grades[i].

Constraints:
    o 1 <= n <= 60
    o <= grades[i] <= 100

Sample Input 0:
    4
    73
    67
    38
    33

Sample Output 0:
    75
    67
    40
    33

Explanation:
    ID  Original Grade      Final Grade
    1       73                  75
    2       67                  67
    3       38                  40
    4       33                  33

    1. Student 1 received a 73, and the next multple of 5 from 73 is 75. Since 75 -73 < 3,
       the student's grade is rounded to 75.
    2. Student 2 received a 67, and the next multiple of 5 from 67 is 70. Since 70-67 = 3,
       the grade will not be modified and the students's final grade is 67.
    3. Student 3 received a 38, and the next multiple of 5 from 38 is 40. Since 40 - 38 < 3,
       the student's grade will be rounded to 40.
    4. Student 4 received a grade below 33, so the grade will not be modified and the student's
       final grade is 33.
 */

/*
 * Complete the 'gradingStudents' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts INTEGER_ARRAY grades as parameter.
 */

vector<int> gradingStudents(vector<int> grades) {
    vector<int> result;

    int rounded_mark = 0;
    int rounding = 0;
    for (int i = 0; i < (int) grades.size(); i++) {
        int mark = grades[i];
        if(mark < 38) {
            rounded_mark = mark;
        }
        else if((rounding = mark % 5) > 2) {
            rounded_mark = mark + 5 - rounding;
        }
        else {
            rounded_mark = mark;
        }
        result.emplace_back(rounded_mark);
    }
    return result;
}

/*
 * Apple and Orange
 * https://www.hackerrank.com/challenges/apple-and-orange/problem
 *
Sam's house has an apple tree and an orange tree that yield an abundance of fruit.
Using the information given below, determine the number of apples and oranges that
land on Sam's house.

In the diagram below:

    o The red region denotes the house, where S is the start point, and T is the endpoint.
      The apple tree is to the left of the house, and the orange tree is to its right.
    o Assume the trees are located on a single point, where the apple tree is at point A,
      and the orange tree is at point B.
    o When a fruit falls from its tree, it lands D units of distance from its tree of
      origin along the x-axis. *A negative value of D means the fruit fell D units to
      the tree's left, and a positive value of D means it falls D units to the tree's
      right. *

        ^                                     ^
      {a a}                                 {o o}
     {{{ }}}                               {{{ }}}
       | |    a             a      o         | |   o
        A--------->    <--------------->       B
            D          S               T

Given the value of D for M apples and N oranges, determine how many apples and
oranges will fall on Sam's house (i.e., in the inclusive range [s,t])

For example, Sam's house is between S = 7 and T = 10. the apple tree is located
at A = 4 and the orange at B = 12. There are M = 3 apples and N= 3 oranges. Apples
are thrown apples = [2,3,-4] units distance from A, and oranges = [3,-2,m-4] units
distance. Adding each apple distance to the position of the tree, they land at
[4+2, 4+3,4+-4] = [6,7,0]. Oragnes land at [12+3, 12+-2,12+-4] = [15,10,8]. One
apple and two oranges land in the inclusive range 7 - 10 so we print

    1
    2

    Function Description
Complete the countApplesAndOranges function in the editor below. It should print
the number of apples and oranges that land on Sam's house, each on a separate line.

countApplesAndOranges has the following parameter(s):

    o s: integer, starting point of Sam's house location.
    o t: integer, ending location of Sam's house location.
    o a: integer, location of the Apple tree.
    o b: integer, location of the Orange tree.
    o apples: integer array, distances at which each apple falls from the tree.
    o oranges: integer array, distances at which each orange falls from the tree.

Input Format:
The first line contains two space-separated integers denoting the respective values of S and T.
The second line contains two space-separated integers denoting the respective values of A and B.
The third line contains two space-separated integers denoting the respective values of M and N.
The fourth line contains  space-separated integers denoting the respective distances that each apple falls from point A.
The fifth line contains  space-separated integers denoting the respective distances that each orange falls from point B.

Constraints:
    1 <= S,T,A,B,M,N < 100,000
    -100,000 <= D <= 100,000
    A < S < T < B

Output Format:
Print two integers on two different lines:
    1. The first integer: the number of apples that fall on Sam's house.
    2. The second integer: the number of oranges that fall on Sam's house.

Sample Input 0:
7 11        // house location
5 15        // apple tree = 5, orange = 15
3 2         // 3 apples, 2 oranges
-2 2 1      // apples path
5 -6        // orange path

Sample Output 0:
1
1

Explanation 0:
The first apple falls at position 5 - 2 = 3
The second apple falls at position 5 + 2 = 7
The third apple falls at position 5 + 1 = 6
The first orange falls at position 15 + 5 = 20
The second orange falls at position 15 - 6 = 9
Only one fruit (the second apple) falls within the region between 7 and 11,
so we print  as our first line of output.
Only the second orange falls within the region between 7 and 11,
so we print 1 as our second line of output.
 */

// house = [s - t]
// apple tree = a
// orange tree = b
void countApplesAndOranges(int s, int t, int a, int b, vector<int> apples, vector<int> oranges) {

    transform(begin(apples), end(apples), begin(apples), [a](auto elem){return elem + a;});
    int apple_count = count_if(begin(apples), end(apples), [s,t](auto elem){return elem >= s && elem <= t;});
    cout << apple_count << endl;

    transform(begin(oranges), end(oranges), begin(oranges), [b](auto elem){return elem + b;});
    int orange_count = count_if(begin(oranges), end(oranges), [s,t](auto elem){return elem >= s && elem <= t;});
    cout << orange_count << endl;

}

int applesAndOranges()
{
    string st_temp;
    getline(cin, st_temp);

    vector<string> st = split_string(st_temp);

    int s = stoi(st[0]);

    int t = stoi(st[1]);

    string ab_temp;
    getline(cin, ab_temp);

    vector<string> ab = split_string(ab_temp);

    int a = stoi(ab[0]);

    int b = stoi(ab[1]);

    string mn_temp;
    getline(cin, mn_temp);

    vector<string> mn = split_string(mn_temp);

    int m = stoi(mn[0]);

    int n = stoi(mn[1]);

    string apples_temp_temp;
    getline(cin, apples_temp_temp);

    vector<string> apples_temp = split_string(apples_temp_temp);

    vector<int> apples(m);

    for (int i = 0; i < m; i++) {
        int apples_item = stoi(apples_temp[i]);

        apples[i] = apples_item;
    }

    string oranges_temp_temp;
    getline(cin, oranges_temp_temp);

    vector<string> oranges_temp = split_string(oranges_temp_temp);

    vector<int> oranges(n);

    for (int i = 0; i < n; i++) {
        int oranges_item = stoi(oranges_temp[i]);

        oranges[i] = oranges_item;
    }

    cout << endl;

    countApplesAndOranges(s, t, a, b, apples, oranges);

    return 0;
}

/*
 * Number Line Jumps
 * https://www.hackerrank.com/challenges/kangaroo/problem
 *
You are choreographing a circus show with various animals. For one act, you are given two
kangaroos on a number line ready to jump in the positive direction (i.e, toward positive infinity).

    o The first kangaroo starts at location X1 and moves at a rate of V1 meters per jump.
    The second kangaroo starts at location X2 and moves at a rate of V2 meters per jump.
    You have to figure out a way to get both kangaroos at the same location at the same
    time as part of the show. If it is possible, return YES, otherwise return NO.

Function Description:
Complete the function kangaroo in the editor below. It should return YES if they reach the
same position at the same time, or NO if they don't.

kangaroo has the following parameter(s):

    o x1, v1: integers, starting position and jump distance for kangaroo 1
    o x2, v2: integers, starting position and jump distance for kangaroo 2

Input Format:
A single line of four space-separated integers denoting the respective values of x1,v1,x2 and v2.

Constraints:
    0 <= x1 < x2 <10000
    1 <= v1 <= 10000
    1 <= v2 <- 10000

Output Format:
    Print YES if they can land on the same location at the same time; otherwise print NO.
    Note: The two kangaroos must land at the same location after making the same number of jumps.

Sample Input 0:
0 3 4 2

Sample Output 0:
YES

 */
// Complete the kangaroo function below.
string kangaroo(int x1, int v1, int x2, int v2) {

    int deltaX = (x2 - x1);
    int deltaV = (v1 - v2);
    if(deltaV == 0) return "NO";
    if(deltaX == 0) return "YES";

    int xDivByV = deltaX % deltaV;
    int num_jumps = deltaX / deltaV;

    return (xDivByV == 0 && num_jumps >= 0) ? "YES" : "NO";
}

int jumpingKangaroos()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string x1V1X2V2_temp;
    getline(cin, x1V1X2V2_temp);

    vector<string> x1V1X2V2 = split_string(x1V1X2V2_temp);

    int x1 = stoi(x1V1X2V2[0]);

    int v1 = stoi(x1V1X2V2[1]);

    int x2 = stoi(x1V1X2V2[2]);

    int v2 = stoi(x1V1X2V2[3]);

    string result = kangaroo(x1, v1, x2, v2);

    fout << result << "\n";

    fout.close();

    return 0;
}

/*
 * Between Two Sets
 * https://www.hackerrank.com/challenges/between-two-sets/problem
There will be two arrays of integers. Determine all integers that satisfy the
following two conditions:

    o The elements of the first array are all factors of the integer being considered
    o The integer being considered is a factor of all elements of the second array
    o These numbers are referred to as being between the two arrays.
      Determine how many such numbers exist.

Example:
    a = [2,6]
    b = [24,36]

There are two numbers between the arrays: 6 & 12
6%2 = 0, 6%6 = 0, 24%6 = 0, 36%6 = 0 for the first value
12%2 = 0, 12%6 = 0 & 24%12 = 0, 36%12 =0 for the second value. Return 2

Function Description:
Complete the getTotalX function in the editor below. It should return the number of
integers that are between the sets.

getTotalX has the following parameter(s):
    o int a[n]: an array of integers
    o int b[m]: an array of integers

Returns:
    o int: the number of integers that are between the sets

Input Format:
The first line contains two space-separated integers, n and m, the number of elements
in arrays a and b.
The second line contains n distinct space-separated integers a[i] where 0<=i<n.
The third line contains m distinct space-separated integers b[j] where 0<=j<m.

Constraints:
    1 < n, m < 10
    1 <= a[i] <=100     // element must be a factor of numbers set
    1 <= b[i] <= 100

Sample Input:
2 3
2 4
16 32 96

Sample Output
3

Explanation:
2 and 4 divide evenly into 4, 8, 12 and 16.
4, 8 and 16 divide evenly into 16, 32, 96.

4, 8 and 16 are the only three numbers for which each element of a is a factor and each is a factor of all elements of b.

 */
/*
 * a[] contains factors of numbers that: Are factors of all numbers in b[]
 *   Therefore:
 *   0 == a[i] % X_number; for(i=0; i<a.size(); i++)    // all elements of a[] are factors of X_number
 *
 *   0 == X_number % b[j]; for(j=0; j<b.size(); j++)
 *
 *   Since a factor of a number must necessarily have a smaller value by some multiple of that number value.
 *   It follows that:
 *   1. Each number of interest must be less than or equal to the lowest value of b[].
 *   2. Each X_number <= b[0] (for a sorted b[] )
 */
int getTotalX(vector<int> factors_of_X, vector<int> multiples_of_X) {

    // Let a[] be renamed factors_of_X
    // Let b[] be renamed multiples_of_X
    sort(factors_of_X.begin(), factors_of_X.end());
    sort(multiples_of_X.begin(), multiples_of_X.end());

    unsigned int count = 0;
    unsigned short times_multiplied = 2;
    unsigned short num = factors_of_X.back();

    // Since a factor of a number must necessarily have a smaller
    // value by some multiple of that number value. Therefore each
    // number of interest must be less than or equal to the lowest
    // value of multiples_of_X[].
    while ( num <= multiples_of_X.front())
    {
        bool is_multiple = true;
        bool is_factor = true;

        //printf("\nTesting factor %d\n", num);
        for (unsigned int i = 0; i < factors_of_X.size(); ++i)
        {
            if (num % factors_of_X[i] != 0)
            {
                //printf("factor array number %d is not a factor of candidate number %d\n", factors_of_X[i], num);
                is_multiple = false;
                break;
            }
        }

        // Each number of interest is a factor of all elements in multiples_of_X[]
        for (unsigned int j = 0; j < multiples_of_X.size(); ++j)
        {
            if (is_multiple && multiples_of_X[j] % num != 0)
            {
                //printf("candidate number %d is not a factor of multiples array number %d\n", num, multiples_of_X[j]);
                is_factor = false;
                break;
            }
        }

        if (is_multiple && is_factor)
        {
            count++;
            //printf("number %d meets both factors and multiples tests, count = %d\n", num, count);
        }
        num = factors_of_X.back() * times_multiplied;
        times_multiplied++;
    }
    return count;

}

int betweenTwoSets() {
    //ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int m = stoi(first_multiple_input[1]);

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split(rtrim(arr_temp_temp));

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    string brr_temp_temp;
    getline(cin, brr_temp_temp);

    vector<string> brr_temp = split(rtrim(brr_temp_temp));

    vector<int> brr(m);

    for (int i = 0; i < m; i++) {
        int brr_item = stoi(brr_temp[i]);

        brr[i] = brr_item;
    }

    int total = getTotalX(arr, brr);

    cout << total << "\n";

    //fout.close();

    return 0;
}

/*
 * Breaking the Records
 * https://www.hackerrank.com/challenges/breaking-best-and-worst-records/problem
 *
Maria plays college basketball and wants to go pro. Each season she maintains a record of her play.
She tabulates the number of times she breaks her season record for most points and least points in
a game. Points scored in the first game establish her record for the season, and she begins
counting from there.

For example, assume her scores for the season are represented in the array scores = [12,24,10,24].
Scores are in the same order as the games played. She would tabulate her results as follows:

              Count
Game  Score  Minimum  Maximum   Min Max
 0      12     12       12       0   0
 1      24     12       24       0   1
 2      10     10       24       1   1
 3      24     10       24       1   1

Given the scores for a season, find and print the number of times Maria breaks her records for most
and least points scored during the season.

Function Description:
Complete the breakingRecords function in the editor below. It must return an integer array containing
the numbers of times she broke her records. Index 0 is for breaking most points records, and index 1
is for breaking least points records.

breakingRecords has the following parameter(s):

    o scores: an array of integers

Input Format:
The first line contains an integer n, the number of games.
The second line contains n space-separated integers describing the respective values of
score0,score1,...score(n-1)

Constraints:
    1 <= n <= 1000
    0 <= scores[i] <= 10**8

Sample Input 0:
9
10 5 20 20 4 5 2 25 1

Sample Output 0:
2 4

Explanation 0

 */
vector<int> breakingRecords(vector<int> scores) {
    // Input is already range checked. Array scores has length >= 1.
    int highest_score = scores[0];
    int lowest_score = scores[0];
    int highest_score_record_count = 0;
    int lowest_score_record_count = 0;


    for(auto score : scores) {
        if(score > highest_score) {
            highest_score_record_count++;
            highest_score = score;
        }
        else if(score < lowest_score) {
            lowest_score_record_count++;
            lowest_score = score;
        }
    }
    vector<int> result(2, 0);
    result[0] = highest_score_record_count;
    result[1] = lowest_score_record_count;
    return result;
}

int breakingTheRecords()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string scores_temp_temp;
    getline(cin, scores_temp_temp);

    vector<string> scores_temp = split_string(scores_temp_temp);

    vector<int> scores(n);

    for (int i = 0; i < n; i++) {
        int scores_item = stoi(scores_temp[i]);

        scores[i] = scores_item;
    }

    vector<int> result = breakingRecords(scores);

    for (int i = 0; i < (int) result.size(); i++) {
        cout << result[i];

        if (i != (int) result.size() - 1) {
            cout << " ";
        }
    }

    cout << "\n";

    //fout.close();

    return 0;
}

/*
 * Subarray Division
 * https://www.hackerrank.com/challenges/the-birthday-bar/problem
 *
Given a chocolate bar, two children, Lily and Ron, are determining how to share it.
Each of the squares has an integer on it.

Lily decides to share a contiguous segment of the bar selected such that:

The length of the segment matches Ron's birth month, and,
The sum of the integers on the squares is equal to his birth day.
You must determine how many ways she can divide the chocolate.

Consider the chocolate bar as an array of squares, s=[2,2,1,3,2]. She wants to find
segments summing to Ron's birth day,  with a length equaling his birth month, m=2.
In this case, there are two segments meeting her criteria: [2,2] and [1,3].

Function Description:
Complete the birthday function in the editor below. It should return an integer denoting
the number of ways Lily can divide the chocolate bar.

birthday has the following parameter(s):

    o s: an array of integers, the numbers on each of the squares of chocolate
    o d: an integer, Ron's birth day
    o m: an integer, Ron's birth month

Input Format:
The first line contains an integer n, the number of squares in the chocolate bar.
The second line contains n space-separated integers s[i], the numbers on the
chocolate squares where 0 < i < n.
The third line contains two space-separated integers, d and m, Ron's birth day
and his birth month.

Constraints:
    1 <= n <= 100
    1 <= s[i] <=5, where (0 <= i < n)
    1 <= d <= 31
    1 <= m <= 12

Output Format:
Print an integer denoting the total number of ways that Lily can portion her chocolate bar to share with Ron.

Sample Input 0:

5
1 2 1 3 2
3 2

Sample Output 0:

2
 */
// Complete the birthday function below.
int birthday(vector<int> squares, int day, int month) {
int num_ways = 0;
int num_sq = squares.size();

    int seg_sum = accumulate(begin(squares), begin(squares)+month, 0);
    if(seg_sum == day) num_ways++;
    for(int i=0; i<num_sq-month; i++) {
        seg_sum += squares[i+month] - squares[i];
        if(seg_sum == day) num_ways++;
    }

    return num_ways;
}

int subarrayDivision()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string s_temp_temp;
    getline(cin, s_temp_temp);

    vector<string> s_temp = split(rtrim(s_temp_temp));

    vector<int> s(n);

    for (int i = 0; i < n; i++) {
        int s_item = stoi(s_temp[i]);

        s[i] = s_item;
    }

    string dm_temp;
    getline(cin, dm_temp);

    vector<string> dm = split(rtrim(dm_temp));

    int d = stoi(dm[0]);

    int m = stoi(dm[1]);

    int result = birthday(s, d, m);

    cout << result << "\n";

    //fout.close();

    return 0;
}

/*
 * Divisible Sum Pairs
 * https://www.hackerrank.com/challenges/divisible-sum-pairs/problem
 *
Given an array of integers and a positive integer k, determine the number of (i,j) pairs
where i<j and ar[i] + ar[j] is divisible by k.

Example:

ar = [1,2,3,4,5,6]
k = 5

Three pairs meet the criteria: [1,4], [2,3] and [4,6].

Function Description

Complete the divisibleSumPairs function in the editor below.

divisibleSumPairs has the following parameter(s):

    o int n: the length of array
    o int ar[n]: an array of integers
    o int k: the integer divisor

Returns:
    - int: the number of pairs

Input Format:
The first line contains 2 space-separated integers, n and k.
The second line contains n space-separated integers, each a value of arr[i].

Constraints
    2 <= n <= 100
    1 <= k <= 100
    1 <= ar[i] <= 100

Sample Input:
6 3
1 3 2 6 1 2

Sample Output:
5
 */
int divisibleSumPairs2(int n, int k, vector<int> ar) {
    multiset<int> pairArray;
    int num_pairs = 0;

    for(auto& elem : ar) {
        int mod_remainder = elem % k;
        pairArray.emplace(mod_remainder);
    }

    for(auto& rem : pairArray) {
        int divk = k - rem;
        int rem_pairs = pairArray.count(divk);
        num_pairs += rem_pairs;
    }
    return num_pairs/2;
}

int divisibleSumPairs(int n, int k, vector<int> ar) {
    int num_pairs = 0;
    int arlen = ar.size();

    for(int i=0; i<arlen-1; i++) {
        int pi = ar[i];
        for(int j=i+1; j<arlen; j++) {
            int pj = ar[j];
            int psum = pi + pj;
            bool divk = (psum % k) == 0;
            if(divk) { num_pairs++; }
        }
    }

    return num_pairs;
}

int dspMain()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string nk_temp;
    getline(cin, nk_temp);

    vector<string> nk = split_string(nk_temp);

    int n = stoi(nk[0]);

    int k = stoi(nk[1]);

    string ar_temp_temp;
    getline(cin, ar_temp_temp);

    vector<string> ar_temp = split_string(ar_temp_temp);

    vector<int> ar(n);

    for (int i = 0; i < n; i++) {
        int ar_item = stoi(ar_temp[i]);

        ar[i] = ar_item;
    }

    cout << "divSum1 = ";
    int result = divisibleSumPairs(n, k, ar);

    cout << result << "\n";

    cout << "divSum2 = ";
    result = divisibleSumPairs2(n, k, ar);

    cout << result << "\n";

    //fout.close();

    return 0;
}

/*
 * Migratory Birds
 * https://www.hackerrank.com/challenges/migratory-birds/problem
 *
Given an array of bird sightings where every element represents a bird type id, determine
the id of the most frequently sighted type. If more than 1 type has been spotted that maximum
amount, return the smallest of their ids.

Example:
arr = [1,1,2,2,3]

There are two each of types 1 and 2, and one sighting of type 3. Pick the lower of the two types seen twice: type 1.

Function Description:
migratoryBirds function has the following parameter(s):
    o int arr[n]: the types of birds sighted

Returns
    o int: the lowest type id of the most frequently sighted birds

Input Format:
The first line contains an integer, n, the size of arr.
The second line describes arr as n space-separated integers, each a type number of the bird sighted.

Constraints
    5 <= n <= 2 x 10**5
    1 <= id <= 5

Sample Input 0:
6
1 4 4 4 5 3

Sample Output 0:
4
 */
int migratoryBirds(vector<int> arr) {
    const int maxBirdId = 5;
    vector<int> birdTypeCount(maxBirdId + 1, 0);

    cout << endl;
    for(auto& type : arr) {
        birdTypeCount.at(type)++;
        //int typeCount = birdTypeCount[type];
        //printf("Type %d count = %d %s\n", type, typeCount, typeCount == 1 ? "bird":"birds");
    }
    /*
    for(int i=1; i<=maxBirdId; i++) {
        int count = birdTypeCount[i];
        printf("Type %d: %d %s\n", i, count, count == 1 ? "bird":"birds");
    }
    */
    auto itr = max_element(begin(birdTypeCount), end(birdTypeCount));
    int mostFreqSighted = itr - begin(birdTypeCount);
    return mostFreqSighted;
}

int mbMain()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string arr_count_temp;
    getline(cin, arr_count_temp);

    int arr_count = stoi(ltrim(rtrim(arr_count_temp)));

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split(rtrim(arr_temp_temp));

    vector<int> arr(arr_count);

    for (int i = 0; i < arr_count; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    int result = migratoryBirds(arr);

    cout << result << "\n";

    //fout.close();

    return 0;
}

/*
 * Day of the Programmer
 * https://www.hackerrank.com/challenges/day-of-the-programmer/problem
 *
 */
enum class Month {NAM,  JAN,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC};
int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
bool isLeapYear(int year) {
    if(year < 1918)
    {
        if(year % 4 == 0)
            return true;
        else
            return false;
    }
    else if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
        return true;
    return false;
}

int getDaysInMonth(int month, int year) {
    if(static_cast<Month>(month) == Month::FEB) {

        if(isLeapYear(year)) {
            return 29;
        }
        else {
#ifdef CSARIST_RUSSIA
            // switch from Julian to Gregorian calendar
            if(year == 1918) {
                return 15;
            }
#endif
            return 28;
        }
    }
    switch(static_cast<Month>(month)) {
    case Month::APR:
    case Month::JUN:
    case Month::SEP:
    case Month::NOV:
        return 30;

    default:
        return 31;
    }
}

string dayOfProgrammer(int year) {
    string dopDate;
    int dopDay = 256;
    int month=1;
    int day=0;

    while(dopDay >= getDaysInMonth(month, year)) {
        dopDay -= getDaysInMonth(month++, year);
    }
    day = dopDay;
    string zero_day_pad = day < 10 ? "0" : "";
    string zero_month_pad = month < 10 ? "0" : "";
    dopDate = zero_day_pad + to_string(day) + "." + zero_month_pad + to_string(month) + "." + to_string(year);

    return dopDate;
}

/*
 * Bill Division
 * https://www.hackerrank.com/challenges/bon-appetit/problem
 *
Two friends Anna and Brian, are deciding how to split the bill at a dinner. Each will only
pay for the items they consume. Brian gets the check and calculates Anna's portion. You must
determine if his calculation is correct.

For example, assume the bill has the following prices: bill = [2,4,6]. Anna declines to eat
item k = bill[2] which costs 6. If Brian calculates the bill correctly, Anna will pay (2+4)/2 = 3.
If he includes the cost of 6, he will calculate (2+4+6)/2 = 6. In the second case, he should
refund 3 to Anna.

Function Description:
Complete the bonAppetit function in the editor below. It should print Bon Appetit if the bill
is fairly split. Otherwise, it should print the integer amount of money that Brian owes Anna.

bonAppetit has the following parameter(s):
    o bill: an array of integers representing the cost of each item ordered
    o k: an integer representing the zero-based index of the item Anna doesn't eat
    o b: the amount of money that Anna contributed to the bill

Input Format:
The first line contains two space-separated integers n and k, the number of items ordered and
the 0-based index of the item that Anna did not eat.
The second line contains  space-separated integers  where .
The third line contains an integer, b, the amount of money that Brian charged Anna for her
share of the bill.
 */
void bonAppetit(vector<int> bill, int k, int charges) {
    int total = accumulate(begin(bill), end(bill), 0);
    int deduction = bill.at(k);
    int cost = (total - deduction)/2;

    if(charges == (cost)) {
        cout << "Bon Appetit" << endl;
    }
    else {
        cout << charges - cost;
    }
}

/*
 * Sales by Match
 * https://www.hackerrank.com/challenges/sock-merchant/problem
 *
There is a large pile of socks that must be paired by color. Given an array of integers
representing the color of each sock, determine how many pairs of socks with matching colors
there are.

Example:
n = 7
ar = [1,2,1,2,1,3,2]

There is one pair of color 1 and one of color 2. There are three odd socks left, one of each
color. The number of pairs is 2.

Function Description:
Complete the sockMerchant function in the editor below.

sockMerchant has the following parameter(s):
    o int n: the number of socks in the pile
    o int ar[n]: the colors of each sock

Returns:
    o int: the number of pairs
Input Format

The first line contains an integer n, the number of socks represented in ar.
The second line contains n space-separated integers, ar[i], the colors of the socks in the pile.

Constraints:
    1 <= n <= 100
    1 <= ar[i] <= 100 where 0 <= i < n

Sample Input:
9
10 20 20 10 10 30 50 10 20

Sample Output:
3
 */
int sockMerchant(int n, vector<int> ar) {
    sort(begin(ar), end(ar));
    unordered_multiset<int> sockPairs(begin(ar), end(ar));

    auto itr = adjacent_find(begin(ar), end(ar));
    int num_pairs = 0;
    while(itr != end(ar)) {
        int num_socks = sockPairs.count(*itr);
        //printf("Number sock type %d = %d\n", *itr, num_socks);
        num_pairs += num_socks / 2;
        itr += num_socks;
        itr = adjacent_find(itr, end(ar));
    }
    return num_pairs;
}

int smMain()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string ar_temp_temp;
    getline(cin, ar_temp_temp);

    vector<string> ar_temp = split_string(ar_temp_temp);

    vector<int> ar(n);

    for (int i = 0; i < n; i++) {
        int ar_item = stoi(ar_temp[i]);

        ar[i] = ar_item;
    }

    int result = sockMerchant(n, ar);

    cout << result << "\n";

    // fout.close();

    return 0;
}

/*
 * Drawing Book
 * https://www.hackerrank.com/challenges/drawing-book/problem
 *
A teacher asks the class to open their books to a page number. A student can either start
turning pages from the front of the book or from the back of the book. They always turn
pages one at a time. When they open the book, page  is always on the right side:

When they flip page 1, they see pages 2 and 3. Each page except the last page will always
be printed on both sides. The last page may only be printed on the front, given the length
of the book. If the book is n pages long, and a student wants to turn to page p, what is
the minimum number of pages to turn? They can start at the beginning or the end of the book.

Given n and p, find and print the minimum number of pages that must be turned in order to
arrive at page p.

Example:
n=5
p=3

    [ |1] --> [2|3] --> [4|5]

Using the diagram above, if the student wants to get to page 3, they open the book to page 1,
flip 1 page and they are on the correct page. If they open the book to the last page, page 5,
they turn 1 page and are at the correct page. Return 1.

Function Description
Complete the pageCount function in the editor below.

pageCount has the following parameter(s):
    o int n: the number of pages in the book
    o int p: the page number to turn to

Returns
    o int: the minimum number of pages to turn

Input Format
The first line contains an integer n, the number of pages in the book.
The second line contains an integer, p, the page to turn to.

Constraints:
    1 <= n < 10**5
    1 <= p <= n

Sample Input 0:
6
2

Sample Output 0:
1
 */
int pageCount(int n, int p) {
    int front_turns = p/2;
    int back_turns = (n/2) - (p/2);

    return (front_turns <= back_turns) ? front_turns : back_turns;
}

int drawingBook()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int p;
    cin >> p;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int result = pageCount(n, p);

    cout << result << "\n";

    //fout.close();

    return 0;
}

/*
 * Counting Valleys
 * https://www.hackerrank.com/challenges/counting-valleys/problem
 *
An avid hiker keeps meticulous records of their hikes. During the last hike that took
exactly STEPS steps, for every step it was noted if it was an uphill, U, or a downhill,
D step. Hikes always start and end at sea level, and each step up or down represents
a 1 unit change in altitude. We define the following terms:

    o A mountain is a sequence of consecutive steps above sea level, starting with a
      step up from sea level and ending with a step down to sea level.
    o A valley is a sequence of consecutive steps below sea level, starting with a
      step down from sea level and ending with a step up to sea level.

Given the sequence of up and down steps during a hike, find and print the number of
valleys walked through.

Example
STEPS = 8 path = [DDUUUUDD]
The hiker first enters a valley 2 units deep. Then they climb out and up onto a
mountain 2 units high. Finally, the hiker returns to sea level and ends the hike.

Function Description:
Complete the countingValleys function in the editor below.

countingValleys has the following parameter(s):

    o int steps: the number of steps on the hike
    o string path: a string describing the path

Returns:
    o int: the number of valleys traversed

Input Format:
The first line contains an integer STEPS, the number of steps in the hike.
The second line contains a single string PATH, of STEPS characters that describe
the path.

Constraints:
    2 <= STEPS <= 10**6
    path[i] is composed of set {UD}

Sample Input:
8
UDDDUDUU

Sample Output:
1

Explanation

If we represent _ as sea level, a step up as /, and a step down as \, the hike
can be drawn as:
_/\      _
   \    /
    \/\/
The hiker enters and leaves one valley.
 */
int countingValleys(int steps, string path) {
    int elevation = 0;
    int valleys = 0;
    bool start_or_end = false;

    for(auto& step : path) {
        if(elevation == 0) {
            start_or_end = true;
        }

        if(step == 'U')
            elevation++;
        else
            elevation--;

        if(start_or_end && elevation < 0) {
            valleys++;
            start_or_end = false;
        }
        else {
            start_or_end = false;
        }
    }
    return valleys;
}

int cvMain()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string steps_temp;
    getline(cin, steps_temp);

    int steps = stoi(ltrim(rtrim(steps_temp)));

    string path;
    getline(cin, path);

    int result = countingValleys(steps, path);

    cout << result << "\n";

    //fout.close();

    return 0;
}

/*
 * Electronics Shop
 * https://www.hackerrank.com/challenges/electronics-shop/problem
 *
A person wants to determine the most expensive computer keyboard and USB drive that can be
purchased with a give budget. Given price lists for keyboards and USB drives and a budget,
find the cost to buy them. If it is not possible to buy both items, return -1.

Function Description
Complete the getMoneySpent function in the editor below.

getMoneySpent has the following parameter(s):

    o int keyboards[n]: the keyboard prices
    o int drives[m]: the drive prices
    o int b: the budget

Returns:
    int: the maximum that can be spent, or -1 if it is not possible to buy both items

Input Format:
The first line contains three space-separated integers b, n, and m, the budget, the number
of keyboard models and the number of USB drive models.
The second line contains n space-separated integers keyboard[i], the prices of each keyboard
model.
The third line contains n space-separated integers keyboard[i], the prices of the USB drives.

Sample Input 0:
10 2 3
3 1
5 2 8

Sample Output 0:
9

Explanation 0:
Buy the 2nd keyboard and the  3rd USB drive for a total cost of 8+1=9.
 */
int getMoneySpent(vector<int> keyboards, vector<int> drives, int budget) {
    sort(begin(keyboards), end(keyboards));
    sort(begin(drives), end(drives));

    int total_cost = -1;
    for(auto& kb_cost : keyboards) {
        for(auto& drv_cost : drives) {
            int test_cost = drv_cost + kb_cost;
            if(test_cost <= budget) {
                total_cost = max(total_cost, test_cost);
            }
            else {
                break;
            }
        }
    }
    return total_cost;
}

int esMain()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string bnm_temp;
    getline(cin, bnm_temp);

    vector<string> bnm = split_string(bnm_temp);

    int b = stoi(bnm[0]);

    int n = stoi(bnm[1]);

    int m = stoi(bnm[2]);

    string keyboards_temp_temp;
    getline(cin, keyboards_temp_temp);

    vector<string> keyboards_temp = split_string(keyboards_temp_temp);

    vector<int> keyboards(n);

    for (int keyboards_itr = 0; keyboards_itr < n; keyboards_itr++) {
        int keyboards_item = stoi(keyboards_temp[keyboards_itr]);

        keyboards[keyboards_itr] = keyboards_item;
    }

    string drives_temp_temp;
    getline(cin, drives_temp_temp);

    vector<string> drives_temp = split_string(drives_temp_temp);

    vector<int> drives(m);

    for (int drives_itr = 0; drives_itr < m; drives_itr++) {
        int drives_item = stoi(drives_temp[drives_itr]);

        drives[drives_itr] = drives_item;
    }

    /*
     * The maximum amount of money she can spend on a keyboard and USB drive, or -1 if she can't purchase both items
     */

    int moneySpent = getMoneySpent(keyboards, drives, b);

    cout << moneySpent << "\n";

    //fout.close();

    return 0;
}

/*
 * Picking Numbers
 * https://www.hackerrank.com/challenges/picking-numbers/problem
 *
Given an array of integers, find the longest subarray where the absolute difference
between any two elements is less than or equal to 1.

Example:
a = [1,1,2,2,4,4,5,5,5]
There are two subarrays meeting the criterion: [1,1,2,2] and [4,4,5,5,5]. The maximum
length subarray has 5 elements.

Function Description:
pickingNumbers has the following parameter(s):
    o int a[n]: an array of integers

Returns:
    o int: the length of the longest subarray that meets the criterion

Input Format:
The first line contains a single integer n, the size of the array a.
The second line contains n space-separated integers, each an a[i].

Constraints:
    o 2 <= n <= 100
    o 0 <= a[i] <= 100
    o The answer will be >= 2.

Sample Input:
6
4 6 5 3 3 1

Sample Output:
3
 */
int pickingNumbers(vector<int> a) {
    int alen = a.size();
    vector<int>idxFreqMap(100, 0);

    for(auto& freq : a) {
        idxFreqMap[freq]++;
    }

    int idx = 0;
    while(idxFreqMap[idx] == 0) { idx++; }  // start freq map at first used value

    int max_sa_len = 0;
    int last_sa_len = 0;
    for(; idx<alen; idx++) {
        int next_sa_len = idx<(alen-1) ? idxFreqMap[idx+1] : 0;
        int sa_len = last_sa_len + idxFreqMap[idx] + next_sa_len;
        max_sa_len = max(max_sa_len, sa_len);
    }

    return max_sa_len;
}

int pnMain()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string a_temp_temp;
    getline(cin, a_temp_temp);

    vector<string> a_temp = split(rtrim(a_temp_temp));

    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        int a_item = stoi(a_temp[i]);

        a[i] = a_item;
    }

    int result = pickingNumbers(a);

    cout << result << "\n";

    //fout.close();

    return 0;
}

/*
 * The Hurdle Race
 * https://www.hackerrank.com/challenges/the-hurdle-race/problem
 *
A video player plays a game in which the character competes in a hurdle race.
Hurdles are of varying heights, and the characters have a maximum height they
can jump. There is a magic potion they can take that will increase their
maximum jump height by 1 unit for each dose. How many doses of the potion must
the character take to be able to jump all of the hurdles. If the character can
already clear all of the hurdles, return 0.

Example:
The character can jump 1 unit high initially and must take 3-1=2 doses of
potion to be able to jump all of the hurdles.

Function Description
hurdleRace has the following parameter(s):

    o int k: the height the character can jump naturally
    o int height[n]: the heights of each hurdle

Returns:
    o int: the minimum number of doses required, always  or more

Input Format:
The first line contains two space-separated integers n and k, the number of
hurdles and the maximum height the character can jump naturally.
The second line contains n space-separated integers height[i] where 0 <= i < n.

Constraints
    1 <= n,k <= 100
    1 <= height[i] <= 100

Sample Input 0:
5 4
1 6 3 5 2

Sample Output 0
2

This code frag is interesting, but is not what the problem is asking:
    *
    auto lambda = [k](int sum, int h) {
        printf("sum=%d, height=%d, k=%d: result=", sum, h, k);
        int result=0;
        if(h > k) { result = sum + (h-k); }else{ result=sum;}
        printf("%d\n", result);
        return result;
    };
    return potion_doses;
    *
 */
int hurdleRace(int k, vector<int> height) {
    auto max_height = *max_element(begin(height), end(height));
    return (max_height > k) ? max_height - k : 0;
}

int hrMain()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string nk_temp;
    getline(cin, nk_temp);

    vector<string> nk = split_string(nk_temp);

    int n = stoi(nk[0]);

    int k = stoi(nk[1]);

    string height_temp_temp;
    getline(cin, height_temp_temp);

    vector<string> height_temp = split_string(height_temp_temp);

    vector<int> height(n);

    for (int i = 0; i < n; i++) {
        int height_item = stoi(height_temp[i]);

        height[i] = height_item;
    }

    int result = hurdleRace(k, height);

    cout << result << "\n";

    //fout.close();

    return 0;
}

/*
 * Designer PDF Viewer
 * https://www.hackerrank.com/challenges/designer-pdf-viewer/problem
 */
int designerPdfViewer(vector<int> heights, string word) {
    int wlen = word.length();
    int max_cheight = 0;
    for(auto& c : word) {
        int idx = c - 'a';
        int cheight = heights.at(idx);
        max_cheight = max(max_cheight, cheight);
    }
    int area = max_cheight * wlen;
    return area;
}

/*
 * Utopian Tree
 * https://www.hackerrank.com/challenges/utopian-tree/problem
 *
The Utopian Tree goes through 2 cycles of growth every year. Each spring, it doubles in height.
Each summer, its height increases by 1 meter. A Utopian Tree sapling with a height of 1 meter
is planted at the onset of spring. How tall will the tree be after n growth cycles?

For example, if the number of growth cycles is n=5, the calculations are as follows:
Period  Height
0          1
1          2
2          3
3          6
4          7
5          14
 */
int utopianTree(int n) {
    // double in height for each odd cycle
    // add 1 meter for every even cycle
    if(n == 0) return 1;
    return (n & 1) ? utopianTree(n-1) * 2 : utopianTree(n-1) + 1;
}

/*
 * Angry Professor
 * https://www.hackerrank.com/challenges/angry-professor/problem
 *
 */
string angryProfessor(int threshold, vector<int> arrivalTime) {
    int num_students = arrivalTime.size();
    if(num_students < threshold) return "NO";

    sort(begin(arrivalTime), end(arrivalTime));
    int ontime = 0;
    for(auto& arrival : arrivalTime) {
        if(arrival <= 0) ontime++;
        if(ontime >= threshold) break;
    }
    // many different ways to count the number of student arriving on time vs those arriving late.
#ifdef TESTING
    // Using upper_bound():
    auto itr_ontime = lower_bound(begin(arrivalTime), end(arrivalTime), 0);
    printf("lower_bound: threshold=%d, on time students=%d\n", threshold, num_students - (int) distance(begin(arrivalTime), itr_ontime));
    // Using count_if() with std::less_equal()
    ontime = std::count_if (begin(arrivalTime), end(arrivalTime), bind2nd(less_equal<int>(),0));
    printf("count_if(gte): threshold=%d, on time students=%d\n", threshold, ontime);
    // Using count_if() and a lambda
    int ontime = count_if(begin(arrivalTime), end(arrivalTime), [](int t){ return (t <= 0);});
    //printf("count_if(lambda): threshold=%d, on time students=%d\n", threshold, ontime);
#endif

    return (ontime >= threshold) ? "NO" : "YES";

}

int apMain()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string nk_temp;
        getline(cin, nk_temp);

        vector<string> nk = split_string(nk_temp);

        int n = stoi(nk[0]);

        int k = stoi(nk[1]);

        string a_temp_temp;
        getline(cin, a_temp_temp);

        vector<string> a_temp = split_string(a_temp_temp);

        vector<int> a(n);

        for (int i = 0; i < n; i++) {
            int a_item = stoi(a_temp[i]);

            a[i] = a_item;
        }

        string result = angryProfessor(k, a);

        cout << result << "\n";
    }

    //fout.close();

    return 0;
}

/*
 * Beautiful Days at the Movies
 * https://www.hackerrank.com/challenges/beautiful-days-at-the-movies/problem
 */
int beautifulDays(int start_day, int end_day, int divisor) {
    int beautyDays = 0;
    for(int day=start_day; day<=end_day; day++) {
        string revstr = to_string(day);
        reverse(begin(revstr), end(revstr));
        int revday = stoi(revstr);
        if(day == revday) {
            beautyDays++;
        }
        else if(0 == (day - revday) % divisor) {
            beautyDays++;
        }
    }
    return beautyDays;
}

/*
 * Viral Advertising
 * https://www.hackerrank.com/challenges/strange-advertising/problem
 *
HackerLand Enterprise is adopting a new viral advertising strategy. When they launch a new product,
they advertise it to exactly 5 people on social media. On the first day, half of those 5 people
(i.e., floor(5/2)=2 like the advertisement and each shares it with  of their friends. At the
beginning of the second day, floor(5/2) x 3 = 2 x 3 = 6 people receive the advertisement.
Each day, floor(recipients/2) of the recipients like the advertisement and will share it with 3
friends on the following day. Assuming nobody receives the advertisement twice, determine how many
people have liked the ad by the end of a given day, beginning with launch day as day 1.
 */
int likedAdvertising(int day) {
    if(day == 1) return 2;

    return ((likedAdvertising(day-1) * 3)/2);
}

int viralAdvertising(int numdays) {
    int totalLiked = 0;
    for(int day=1; day<=numdays; day++) {
        totalLiked += likedAdvertising(day);
    }
    return totalLiked;
}

int vaMain() {
    printf("Day    Liked\n");
    for(int day=1; day<=5; day++) {
        printf("%d     %d\n", day, likedAdvertising(day));
    }
    printf("5 day total = %d\n", viralAdvertising(5));
    return 0;
}

/*
 * Save the Prisoner!
 * https://www.hackerrank.com/challenges/save-the-prisoner/problem
 *
Returns:
    o int: the chair number of the prisoner to warn

Input Format:
The first line contains an integer, t, the number of test cases.
The next t lines each contain  space-separated integers:
    o n: the number of prisoners
    o m: the number of sweets
    o s: the chair number to start passing out treats at

Constraints:
    1 <= t <= 100
    1 <= n <= 10**9
    1 <= m <= 10**9
    1 <= s <= n
 */
int saveThePrisoner(int num_prisoners, int num_sweets, int start_chair) {
    printf("prisoners=%d, sweets=%d, chair=%d\n", num_prisoners, num_sweets, start_chair);
    unsigned int warn_chair = 0;
    unsigned int u_num_sweets = num_sweets;
    unsigned int u_num_prisoners = num_prisoners;

    if(num_sweets > num_prisoners) {
        warn_chair = (start_chair-1) + (u_num_sweets % u_num_prisoners);
        if(warn_chair == 0) {
            warn_chair = num_prisoners;
        }
        else if(warn_chair > u_num_prisoners) {
            warn_chair = warn_chair % u_num_prisoners;
        }
    }
    else {
        warn_chair = (start_chair-1) + u_num_sweets;
        if(warn_chair > u_num_prisoners) {
            warn_chair = warn_chair % u_num_prisoners;
            if(warn_chair == 0) {
                warn_chair = num_prisoners;
            }
        }
    }
    printf("warn_chair = %d\n", warn_chair);
    return (int) warn_chair;
}

int stpMain()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string nms_temp;
        getline(cin, nms_temp);

        vector<string> nms = split_string(nms_temp);

        int n = stoi(nms[0]);

        int m = stoi(nms[1]);

        int s = stoi(nms[2]);

        int result = saveThePrisoner(n, m, s);

        cout << result << "\n";
    }

    //fout.close();

    return 0;
}

/*
 * Circular Array Rotation
 * https://www.hackerrank.com/challenges/circular-array-rotation/problem
 *
For each array, perform a number of right circular rotations and return the values of the elements at the given indices.

circularArrayRotation has the following parameter(s):
    o int a[n]: the array to rotate
    o int k: the rotation count
    o int queries[1]: the indices to report

Returns:
    o int[q]: the values in the rotated A as requested in M

Sample Input 0:
3 2 3
1 2 3
0
1
2

Sample Output 0:
2
3
1
 */
vector<int> circularArrayRotation(vector<int> circle, int right_rotations, vector<int> queries) {
    int num_elems = circle.size();
    int num_results = queries.size();

    int rotations = right_rotations % num_elems;
    vector<int>result(num_results, 0);

    if(rotations) {
        rotate(rbegin(circle), rbegin(circle)+rotations, rend(circle));  // right rotation
        //rotate(begin(circle), begin(circle)+rotations, end(circle));   // left rotation
    }
    for(size_t i=0; i<queries.size(); i++) {
        int idx = queries[i];
        result[i] = circle[idx];
    }
    return result;
}

int carMain()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string nkq_temp;
    getline(cin, nkq_temp);

    vector<string> nkq = split_string(nkq_temp);

    int n = stoi(nkq[0]);

    int k = stoi(nkq[1]);

    int q = stoi(nkq[2]);

    string a_temp_temp;
    getline(cin, a_temp_temp);

    vector<string> a_temp = split_string(a_temp_temp);

    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        int a_item = stoi(a_temp[i]);

        a[i] = a_item;
    }

    vector<int> queries(q);

    for (int i = 0; i < q; i++) {
        int queries_item;
        cin >> queries_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        queries[i] = queries_item;
    }

    vector<int> result = circularArrayRotation(a, k, queries);

    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i];

        if (i != result.size() - 1) {
            cout << "\n";
        }
    }

    cout << "\n";

    //fout.close();

    return 0;
}

/*
 * Sequence Equation
 * https://www.hackerrank.com/challenges/permutation-equation/problem
 *
For each X...find any integer Y such that P[P[Y]]] = X and print the value of y on a new line.

Sample Input 1:
5
4 3 5 1 2

Sample Output 1:
1
3
5
4
2
 */
vector<int> permutationEquation(vector<int> p) {
    unordered_map<int, int> pidx_map;
    vector<int> result;
    // insert a zero at beginning to correct 1-based indexing
    p.emplace(begin(p), 0);
    for(size_t x=1; x<p.size(); x++) {
        // keys are values of p
        pidx_map.emplace(make_pair(p[x], x));
    }
    for(size_t x=1; x<p.size(); x++) {
        auto itr = pidx_map.find(x);
        if(itr != end(pidx_map)) {
            int pidx = itr->second;
            itr = pidx_map.find(pidx);
            if(itr != end(pidx_map)) {
                int y = itr->second;
                result.push_back(y);
            }
        }
    }
    return result;
}

int seMain()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string p_temp_temp;
    getline(cin, p_temp_temp);

    vector<string> p_temp = split_string(p_temp_temp);

    vector<int> p(n);

    for (int i = 0; i < n; i++) {
        int p_item = stoi(p_temp[i]);

        p[i] = p_item;
    }

    vector<int> result = permutationEquation(p);

    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i];

        if (i != result.size() - 1) {
            cout << "\n";
        }
    }

    cout << "\n";

    //fout.close();

    return 0;
}

/*
 * Jumping on the Clouds:
 * https://www.hackerrank.com/challenges/jumping-on-the-clouds/problem
 *
There is a new mobile game that starts with consecutively numbered clouds. Some of the clouds are
thunderheads and others are cumulus. The player can jump on any cumulus cloud having a number that
is equal to the number of the current cloud plus 1 or 2. The player must avoid the thunderheads.
Determine the minimum number of jumps it will take to jump from the starting position to the last
cloud. It is always possible to win the game.

For each game, you will get an array of clouds numbered 0 if they are safe or 1 if they must be avoided.

Example:
c = [0,1,0,0,0,1,0]

Index the array from 0....6. The number on each cloud is its index in the list so the player must avoid
the clouds at indices 1 and 5. They could follow these two paths: 0->2->4->6 or 0->2->3->4->6. The first
path takes 3 jumps while the second takes 4. Return 3.

Input Format:
The first line contains an integer n, the total number of clouds. The second line contains n
space-separated binary integers describing clouds c[i] where 0 <= i < n.
    o If c[i]=0, then cloud  is a cumulus cloud.
    o If c[i]=1, then cloud  is a thunderhead.
 */
int jumpingOnClouds(vector<int> clouds) {
    int num_clouds = clouds.size();
    int steps = 0;
    int current_cloud = 0;
    int remaining_clouds = num_clouds - 1;
    int next_step = 0;
    const int CUMULUS = 0;

    while(remaining_clouds > 0) {
        // "It is always possible to win the game"
        if(remaining_clouds >= 2)
            next_step = clouds[current_cloud + 2] == CUMULUS ? 2 : 1;
        else
            next_step = 1;
        current_cloud += next_step;
        remaining_clouds -= next_step;
        steps++;
    }

    return steps;
}



/*
 * Jumping on the Clouds: Revisited
 * https://www.hackerrank.com/challenges/jumping-on-the-clouds-revisited/problem
 *
Input Format:
The first line contains two space-separated integers, n and k, the number of clouds and the jump distance.
The second line contains  space-separated integers c[i] where 0<=i<n. Each cloud is described as follows:
    o If c[i]=0, then cloud  is a cumulus cloud.
    o If c[i]=1, then cloud  is a thunderhead.
 */
int jumpingOnCloudsRevisited(vector<int> clouds, int jump_size) {
    int num_clouds = clouds.size();
    int next_cloud = jump_size;
    if(next_cloud >= num_clouds) {
        next_cloud = next_cloud % num_clouds;
    }
    int energy_level = 100 - 1 - (2*clouds[next_cloud]);
    //printf("cloud = %d, energy=%d\n", next_cloud, energy_level);
    while(next_cloud) {
        next_cloud += jump_size;
        if(next_cloud >= num_clouds) {
            next_cloud = next_cloud % num_clouds;
        }
        energy_level = energy_level - 1 - (2*clouds[next_cloud]);
        //printf("cloud = %d, energy=%d\n", next_cloud, energy_level);
    }

    return energy_level;
}

int jotcMain()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string nk_temp;
    getline(cin, nk_temp);

    vector<string> nk = split_string(nk_temp);

    int n = stoi(nk[0]);

    int k = stoi(nk[1]);

    string c_temp_temp;
    getline(cin, c_temp_temp);

    vector<string> c_temp = split_string(c_temp_temp);

    vector<int> c(n);

    for (int i = 0; i < n; i++) {
        int c_item = stoi(c_temp[i]);

        c[i] = c_item;
    }


    int result = jumpingOnClouds(c);
    cout << result << "\n";
    result = jumpingOnCloudsRevisited(c, k);
    cout << result << "\n";

    //fout.close();

    return 0;
}

/*
 * Find Digits
 * https://www.hackerrank.com/challenges/find-digits/problem
 *
An integer d is a divisor of an integer n if the remainder of n / d == 0.
Given an integer, for each digit that makes up the integer determine whether it is a divisor.
Count the number of divisors occurring within the integer.

Example:
n = 124
Check whether 1,2 and 4 are divisors of 124. All 3 numbers divide evenly into 124 so return 3.
n = 10
Check whether 1 and 0 are divisors of 10. 1 is, but 0 is not. Return 1.

Function Description:
findDigits has the following parameter(s):
    o int n: the value to analyze

Returns
    o int: the number of digits in n that are divisors of n

Input Format:
The first line is an integer, t, the number of test cases.
The t subsequent lines each contain an integer, n.

Constraints:
    1 <= t <= 15
    0 <= n < 10**9
 */
int findDigits(int num) {
    int digit = num;
    vector<bool>digitIsDivisor(10);
    vector<int> digits; // max number of digits in a 32-bit number

    while(digit) {
        digits.push_back(digit%10);
        digit /= 10;
    }

    //printVector("Digits", digits);

    int numDivisors = 0;
    for(auto itr=begin(digits); itr<end(digits); itr++) {
        int single_digit = *itr;
        if(single_digit != 0) {
            if(num % single_digit == 0) {
                numDivisors++;
            }
        }
    }
    return numDivisors;
}

/*
 * Append & Delete
 * https://www.hackerrank.com/challenges/append-and-delete/problem
 *
You have two strings of lowercase English letters. You can perform two types of operations
on the first string:
    1. Append a lowercase English letter to the end of the string.
    2. Delete the last character of the string. Performing this operation on an empty string
       results in an empty string.
Given an integer, k, and two strings, s and t, determine whether or not you can convert s to
t by performing exactly k of the above operations on s. If it's possible, print Yes. Otherwise,
print No.

Example:
    s = [a,b,c]
    t = [d,e,f]
    k = 6

To convert s to t, we first delete all of the characters in 3 moves. Next we add each of the
characters of t in order. On the  move, you will have the matching string. Return Yes.

If there were more moves available, they could have been eliminated by performing multiple
deletions on an empty string. If there were fewer than 6 moves, we would not have succeeded
in creating the new string.

Function Description
appendAndDelete has the following parameter(s):
    o string s: the initial string
    o string t: the desired string
    o int k: the exact number of operations that must be performed

Returns:
string: either Yes or No

Input Format:
The first line contains a string s, the initial string.
The second line contains a string t, the desired final string.
The third line contains an integer k, the number of operations.

Sample Input 0:
hackerhappy
hackerrank
9

Sample Output 0:
Yes

Explanation 0
We perform 5 delete operations to reduce string 5 to hacker. Next, we perform 4 append operations
(i.e., r, a, n, and k), to get hackerrank. Because we were able to convert s to t by performing
exactly k=9 operations, we return Yes.

 */
string appendAndDelete(string s, string t, int k) {
    int slen = s.length();
    int tlen = t.length();
    int num_del = 0;
    int num_add = 0;
    int num_ops = 0;
    const char *yes = "Yes";
    const char *no = "No";

    printf("s=%s, t=%s, k=%d\n", s.c_str(), t.c_str(), k);
    printf("s.len=%d, t.len=%d\n", slen, tlen);
    auto diff_pair = mismatch(begin(s), end(s), begin(t));
    int first_diff = diff_pair.first - begin(s);
    if(first_diff == slen) {
        num_del = 0;
        num_add = tlen - first_diff;    // if s == t, then num_add = 0
    }
    else {
        num_del = slen - first_diff;
        num_add = tlen - first_diff;
    }
    num_ops = num_del + num_add;
    printf("first_diff = %d\n", first_diff);
    printf("num_del = %d\n", num_del);
    printf("num_add = %d\n", num_add);
    if(k < num_ops) {
        return no;
    }
    else if(k == num_ops) {
        return yes;
    }
    else if(tlen == slen && k >= num_ops) {
        return yes;
    }
    else if(k >= (2*tlen) + num_ops) {
        return yes;
    }
    else {
        if((k & 1) == (num_ops & 1)) {   // fails cases 9 & 12
            return yes;
        }
        return no;
    }
}

/*
 * Cut the Sticks
 * https://www.hackerrank.com/challenges/cut-the-sticks/problem
 *
You are given a number of sticks of varying lengths. You will iteratively cut the sticks
into smaller sticks, discarding the shortest pieces until there are none left. At each
iteration you will determine the length of the shortest stick remaining, cut that length
from each of the longer sticks and then discard all the pieces of that shortest length.
When all the remaining sticks are the same length, they cannot be shortened so discard
them. Given the lengths of n sticks, print the number of sticks that are left before each
iteration until there are none left.

Input Format:
The first line contains a single integer n, the size of arr.
The next line contains n space-separated integers, each an arr[i], where each value
represents the length of the ith stick.

Sample Input O:
6
5 4 4 2 2 8

Sample Output 0:
6
4
2
1
 */
vector<int> cutTheSticks(vector<int> arr) {
    vector<int>result;

    while(arr.size()) {
        int shortest = *min_element(begin(arr), end(arr));
        int num_cut = count_if(begin(arr), end(arr), [](int elem){ return elem!=0;});
        result.push_back(num_cut);
        transform(begin(arr), end(arr), begin(arr),
                [shortest](int elem) {return elem - shortest;});
        arr.erase(remove(begin(arr), end(arr), 0), end(arr));
    }
    return result;
}

/*
 * Equalize the Array
 * https://www.hackerrank.com/challenges/equality-in-a-array/problem
 *
Given an array of integers, determine the minimum number of elements to delete to leave
only elements of equal value.
 */
int equalizeArray(vector<int> arr) {
    vector<int>freqMap(101);

    for(auto& val : arr) {
        freqMap[val]++;
    }
    auto max_itr = max_element(begin(freqMap), end(freqMap));
    int max_freq = distance(begin(freqMap), max_itr);
    int max_count = freqMap[max_freq];
    return arr.size() - max_count;
}

/*
 * Repeated String
 * https://www.hackerrank.com/challenges/repeated-string/problem
 *
There is a string, s, of lowercase English letters that is repeated infinitely many times.
Given an integer, n, find and print the number of letter a's in the first n letters of the
infinite string.

Example:
s = 'abcac'
n = 10

The substring we consider is abcacabcac, the first 10 characters of the infinite string.
There are 4 occurrences of a in the substring.

Function Description:
repeatedString has the following parameter(s):

    o s: a string to repeat
    o n: the number of characters to consider

Returns:
int: the frequency of a in the substring
 */
long repeatedString(string repeated, long n) {

    long slen = repeated.length();
    long num_a = count(begin(repeated), end(repeated), 'a');
    long num_substr = n / slen;
    long num_remain = n % slen;
    long num_a_in_remain = count(begin(repeated), begin(repeated)+num_remain, 'a');
    /*
    printf("string=%s, n=%ld, num_a=%ld, num_substr=%ld, num_remain=%ld, num_a_in_remain=%ld\n",
            repeated.c_str(), n, num_a, num_substr, num_remain, num_a_in_remain);
            */
    return (num_a * num_substr) + num_a_in_remain;
}

/*
 * Sherlock and Squares
 * https://www.hackerrank.com/challenges/sherlock-and-squares/problem
 *
Watson likes to challenge Sherlock's math ability. He will provide a starting and ending value
that describe a range of integers, inclusive of the endpoints. Sherlock must determine the number
of square integers within that range.
Note: A square integer is an integer which is the square of an integer, e.g. 1, 4, 9, 16, 25.

Example:
a = 24
b = 49
There are three square integers in the range: 25,36 and 49. Return 3.

Function Description:
Complete the squares function in the editor below. It should return an integer representing
the number of square integers in the inclusive range from a to b.

squares has the following parameter(s):
    o int a: the lower range boundary
    o int b: the upper range boundary

Returns:
    o int: the number of square integers in the range

Sample Input 0:
2
3 9
17 24

Sample Output 0:
2
0
 */
// This design only works for consecutive sequences that have some overlap.
// Otherwise it misses cases.
int squares_does_not_work_but_uses_set_lower_bound(int lower_num, int upper_num) {
    static set<int> squares_set;
    static int lowest_num = 1e9;
    static int highest_num = 0;
    int num_cached = 0;
    int num_squares = 0;
    if(lower_num == 1) {
        num_squares = 1;
        lower_num = 2;
    }

    static int test_count = 0;
    if(++test_count == 33) {
        printf("lower_num=%d, upper_num=%d, lowest_num=%d, highest_num=%d\n",
                lower_num, upper_num, lowest_num, highest_num);
        for(auto& ps : squares_set) {
            printf("%d, ", ps);
        }
        cout << ":" << endl;
    }
    for(int num=lower_num; num<=upper_num; num++) {
        // Check if number is cached
        if(num >= lowest_num && num <= highest_num) {
            // get lower iterator that is equivalent or goes after
            auto lower_itr = squares_set.lower_bound(lower_num);
            if(lower_itr == end(squares_set)) {
                break;  // no elements found
            }
            // get upper iterator or end condition, which is first element after the
            int last_cached_num = highest_num >= upper_num ? upper_num : highest_num;
            auto upper_itr = squares_set.upper_bound(last_cached_num);
            if(upper_itr == end(squares_set)) {
                ;  // highest_num is out of cached numbers
            }
            num_cached = distance(lower_itr, upper_itr);
            num_squares += num_cached;
            num = last_cached_num;
            if(num == upper_num) { return num_squares; }
            continue;
        }

        int lastdigit = num & 0x0F;
        // Properties of Squares:
        // https://www.ask-math.com/properties-of-square-numbers.html
        // 1: No square number ends in 2, 3, 7 or 8:
        if(lastdigit == 2 || lastdigit == 3 ||
                lastdigit == 7 || lastdigit == 8) {
            continue;
        }
        // 2: The square of a number other than 1 is either a multiple of 3
        //    or exceeds a multiple of 3 by 1.
        int remdiv = num % 3;
        if(!(remdiv == 0) && !(remdiv == 1)) {  // 1 is already checked
            continue;
        }
        // 3: The square of a number other than 1 is either a multiple of 4
        //    or exceeds a multiple of 4 by 1.
        remdiv = num % 4;
        if(!(remdiv == 0) && !(remdiv == 1)) {  // 1 is already checked
            continue;
        }

        int sqrtOfNum = sqrt(num);
        if(sqrtOfNum*sqrtOfNum == num) {
            squares_set.emplace(num);
            num_squares++;
        }

    }
    if(lowest_num > lower_num) {
        lowest_num = lower_num;
    }
    if(highest_num < upper_num) {
        highest_num = upper_num;
    }
    //printf("Found %d numbers cached\n", num_cached);

    return num_squares;
}

// Properties of Squares:
// https://www.ask-math.com/properties-of-square-numbers.html
bool num_filtered(int test_num) {
    int last_digit = test_num & 0x0F;
    // 1: No square number ends in 2, 3, 7 or 8:
    if(last_digit == 2 || last_digit == 3 ||
            last_digit == 7 || last_digit == 8) {
        return true;
    }
    // 2: The square of a number other than 1 is either a multiple of 3
    //    or exceeds a multiple of 3 by 1.
    int remdiv = test_num % 3;
    if(!(remdiv == 0) && !(remdiv == 1)) {  // 1 is already checked
        return true;
    }
    // 3: The square of a number other than 1 is either a multiple of 4
    //    or exceeds a multiple of 4 by 1.
    remdiv = test_num % 4;
    if(!(remdiv == 0) && !(remdiv == 1)) {  // 1 is already checked
        return true;
    }

    return false;
}

int squares(int lower_num, int upper_num) {
    int num_squares = 0;
    int next_num = 0;
    int num_sqrt = sqrt(lower_num);
    int num_sqrt_squared =  num_sqrt * num_sqrt;

    if(num_sqrt_squared == lower_num) {
        //printf("%d ", num);
        num_squares++;
    }
    next_num = (num_sqrt_squared + 1) + (2*num_sqrt);
    //
    // The next number to test has to be at least (number+1) + (2 * sqrt_num)
    // example: num=16 : (num+1) + (sqrt(num)*2) = 16+1 + (4 * 2) = 17 + 8 = 25
    //          num=25 : (num+1) + (sqrt(num)*2) = 25+1 + (5 * 2) = 26 + 10 = 36
    while(next_num <= upper_num) {
        //printf("%d ", next_num);
        num_squares++;
        num_sqrt++;
        next_num = (next_num + 1) + (2*num_sqrt);
    }

    return num_squares;
}

int sasMain()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string ab_temp;
        getline(cin, ab_temp);

        vector<string> ab = split_string(ab_temp);

        int a = stoi(ab[0]);

        int b = stoi(ab[1]);

        int result = squares(a, b);

        cout << result << "\n";
    }

    //fout.close();

    return 0;
}

/*
 * Library Fine
 * https://www.hackerrank.com/challenges/library-fine/problem
 *
Your local library needs your help! Given the expected and actual return dates for a library book,
create a program that calculates the fine (if any). The fee structure is as follows:
    o If the book is returned on or before the expected return date, no fine will be charged (i.e.: fine=0).
    o If the book is returned after the expected return day but still within the same calendar month and
      year as the expected return date, fine = 15 Hackos X (the number of days late).
    o If the book is returned after the expected return month but still within the same calendar year as
    the expected return date, the fine = 500 Hackos & (the number of months late).
    o If the book is returned after the calendar year in which it was expected, there is a fixed fine of 10000 Hackos.
Charges are based only on the least precise measure of lateness. For example, whether a book is due January 1, 2017 or
December 31, 2017, if it is returned January 1, 2018, that is a year late and the fine would be 10,000 Hackos.

Example:
d1,m1,y1 = 14,7,2018
d2,m2,y2 = 5,7,2018

The first values are the return date and the second are the due date. The years are the same and the months are the
same. The book is 14-5 = 9 days late. Return 9*15 = 135.

Sample Input:
9 6 2015
6 6 2015

Sample Output:
45
 */
int libraryFine(int return_day, int return_month, int return_year, int due_day, int due_month, int due_year) {

    if(return_year > due_year) {
        return 10'000;
    }
    else if(return_year == due_year) {
        if(return_month > due_month) {
            return 500 * (return_month - due_month);
        }
        if(return_month == due_month) {
            if(return_day > due_day) {
                return 15 * (return_day - due_day);
            }
        }
    }
    return 0;
}

/*
 * Cavity Map
 * https://www.hackerrank.com/challenges/cavity-map/problem
 *
You are given a square map as a matrix of integer strings. Each cell of the map has a value
denoting its depth. We will call a cell of the map a cavity if and only if this cell is not
on the border of the map and each cell adjacent to it has strictly smaller depth. Two cells
are adjacent if they have a common side, or edge.

Find all the cavities on the map and replace their depths with the uppercase character X.
 */
vector<string> cavityMap(vector<string> grid) {
    vector<string> result(grid);
    int num_rows = grid.size();
    int num_cols = grid[0].length();

    for(int i=1; i<num_cols-1; i++) {
        string& above_row = grid[i-1];
        string& row = grid[i];
        string& below_row = grid[i+1];
        for(int j=1; j<num_rows-1; j++) {
            char& test_cell = row[j];
            char above_cell = above_row[j];
            char below_cell = below_row[j];
            char left_cell = row[j-1];
            char right_cell = row[j+1];
            if((test_cell > above_cell) &&
               (test_cell > below_cell) &&
               (test_cell > left_cell) &&
               (test_cell > right_cell) ) {
                test_cell = 'X';
            }
        }
    }
    return grid;
}

/*
 * ACM ICPC Team
 * https://www.hackerrank.com/challenges/acm-icpc-team/problem
 *
There are a number of people who will be attending ACM-ICPC World Finals. Each of them may be well versed
in a number of topics. Given a list of topics known by each attendee, presented as binary strings, determine
the maximum number of topics a 2-person team can know. Each subject has a column in the binary string, and
a '1' means the subject is known while '0' means it is not. Also determine the number of teams that know the
maximum number of topics. Return an integer array with two elements. The first is the maximum number of
topics known, and the second is the number of teams that know that number of topics.

Input Format:
The first line contains two space-separated integers n and m, where n is the number of attendees and m is
the number of topics.

Each of the next  lines contains a binary string of length .
 */
struct acm_player {
    int team_number;
    string topics;
};
struct acm_team {
    acm_team() {
        num_topics = 0;
    }
    acm_team(acm_player t1, acm_player t2) : team1(t1), team2(t2) {
        num_topics = 0;
    }

    acm_player team1;
    acm_player team2;
    string team_topics;
    int num_topics;
};

vector<int> acmTeam(vector<string> player_topics) {
    int attendees = player_topics.size();
    int num_topics = player_topics[0].length();
    vector<int>topics_known(attendees);
    int team = 1;
    for(auto& known : player_topics) {
//        cout << "Team " << team << " topics: " << known << endl;
        int num_topics = count(begin(known), end(known), '1');
//        printf("Team %d topic count = %d\n", team++, num_topics);
        topics_known[team-1] = num_topics;
    }

    int max_topics_count = 0;
    int max_topics_team = 0;
    vector<acm_team> team_combos;

    vector<int> result;
    vector<acm_team> team_list;

    for(int team1_idx=0; team1_idx<attendees-1; team1_idx++) {
        for(int team2_idx=team1_idx+1; team2_idx<attendees; team2_idx++) {
            acm_team formed_team;
            string& team1_topics = player_topics[team1_idx];
            string& team2_topics = player_topics[team2_idx];

            for(int idx=0; idx<num_topics; idx++) {
                formed_team.team_topics += (team1_topics[idx] == '1' || team2_topics[idx] == '1') ? '1' : '0';
            }
//            printf("Team (%d, %d) topics = %s\n", team1_idx+1, team2_idx+1, formed_team.team_topics.c_str());
            int team_topics = count(begin(formed_team.team_topics), end(formed_team.team_topics), '1');
            max_topics_count = max(max_topics_count, team_topics);

            formed_team.team1.team_number = team1_idx+1;
            formed_team.team2.team_number = team2_idx+1;
            formed_team.team1.topics = team1_topics;
            formed_team.team2.topics = team2_topics;
            formed_team.num_topics = team_topics;
            team_list.push_back(formed_team);
        }
    }

    result.push_back(max_topics_count);
    for(auto& team : team_list) {
        if(team.num_topics == max_topics_count)
            max_topics_team++;
    }
    result.push_back(max_topics_team);

//    printf("Max topics = %d, max topics teams = %d\n", max_topics_count, max_topics_team);

    return result;
}

int acmMain()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string nm_temp;
    getline(cin, nm_temp);

    vector<string> nm = split_string(nm_temp);

    int n = stoi(nm[0]);

    int m = stoi(nm[1]);

    vector<string> topic(n);

    for (int i = 0; i < n; i++) {
        string topic_item;
        getline(cin, topic_item);

        topic[i] = topic_item;
    }

    vector<int> result = acmTeam(topic);

    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i];

        if (i != result.size() - 1) {
            cout << "\n";
        }
    }

    cout << "\n";

    //fout.close();

    return m;
}

/*
 * Taum & Bday
 * https://www.hackerrank.com/challenges/taum-and-bday/problem
 */
bool lowest_cost(long cost1, long cost2) {
    if(cost1 >= 0 && cost2 >= 0) {  // +, +
        return cost1 < cost2;
    }
    else if(cost1 < 0) {  // -, +
        return false;
    }
    else if(cost2 < 0) {  // +, -
        return true;
    }
    else {  // -, - ...? not sure what to do here
        return cost1 < cost2;
    }
}
long long taumBday(long long b, long long w, long long bc, long long wc, long long z) {
    vector< long long> cost_choices(3);
    long long bcost = b*bc;
    long long wcost = w*wc;
    cost_choices[0] = bcost+wcost;
    bcost = (b*bc) + (w*(bc + z));
    cost_choices[1] = bcost;
    wcost = (w*wc) + (b*(wc + z));
    cost_choices[2] = wcost;

    return *min_element(begin(cost_choices), end(cost_choices), lowest_cost);
}

/*
 * Kaprekar Numbers
 *
A modified Kaprekar number is a positive whole number with a special property. If you square it,
then split the number into two integers and sum those integers, you have the same value you started
with. Consider a positive whole number n with d digits. We square n to arrive at a number that is
either 2xd  digits long or (2xd) -1 digits long. Split the string representation of the square into
two parts, l and r. The right hand part, r must be d digits long. The left is the remaining substring.
Convert those two substrings back to integers, add them and see if you get n.

Example:
First calculate that n**2 = 25. Split that into two strings and convert them back to integers 2 and 5.
Test 2 + 5 =7 != 5, so this is not a modified Kaprekar number. If n=9, still d=1, and n**2 = 81. This
gives us 1 + 8 = 9, the original n.

Note: r may have leading zeros.

Here's an explanation from Wikipedia about the ORIGINAL Kaprekar Number (spot the difference!):

In mathematics, a Kaprekar number for a given base is a non-negative integer, the representation of
whose square in that base can be split into two parts that add up to the original number again. For
instance, 45 is a Kaprekar number, because 45² = 2025 and 20+25 = 45.

Given two positive integers p and q where p is lower than q, write a program to print the modified
Kaprekar numbers in the range between  and , inclusive. If no modified Kaprekar numbers exist in the
given range, print INVALID RANGE.

Input Format:
     o The first line contains the lower integer limit p.
     o The second line contains the upper integer limit q.

Sample Input:
1
100

Sample Output:
1 9 45 55 99
 */
void kaprekarNumbers(int p, int q) {
    int numFound = 0;

    for(long long num=p; num<=q; num++) {
        string orig_num = to_string(num);
        int digits = orig_num.length();
        long long num_squared = num*num;
        string base = to_string(num_squared);

        int blen = base.length();
        if(blen == 1) {
            if(num == 1) {
                cout << num;
                numFound++;
            }
            continue;
        }

        // Problem includes the following: 'Note: r may have leading zeros'
        // The 'r' designation here refers to the variable rhs.
        // What about the left hand side variable lhs? It is affected also.
        string rhs = base.substr(blen - digits);
        string lhs = base.substr(0, blen - digits);

        /*
        printf("num = %lld, numsqrd = %lld, numsqrd_s = %s, lhs = %s, rhs = %s\n",
                num, num_squared, base.c_str(), lhs.c_str(), rhs.c_str());
        */

        // first try without removing leading zeros
        int rhs_val = stoi(rhs);
        int lhs_val = stoi(lhs);

        if(rhs_val + lhs_val == num) {
            printf("%s%lld", (numFound > 0) ? " " : "", num);
            numFound++;
            continue;
        }

//#define RHS_LEADING_ZEROS
//#define LHS_LEADING_ZEROS

#ifdef LHS_LEADING_ZEROS
        // next check for lhs leading zeros
        bool lhs_leading_zeros = false;
        int lhs_len = lhs.length();
        if(lhs_len && lhs.at(lhs_len-1) == '0') {
            string lhs_nz = lhs;
            rt_trim(lhs_nz, "0");
            lhs_val = stoi(lhs_nz);
            lhs_leading_zeros = true;

            if(rhs_val + lhs_val == num) {
                printf("%s%lld", numFound ? " " : "", num);
                numFound++;
                continue;
            }
        }
#endif

#ifdef RHS_LEADING_ZEROS
        bool rhs_leading_zeros = false;
        // next check for rhs leading zeros
        int rhs_len = rhs.length();
        if(rhs_len && rhs.at(rhs_len-1) == '0') {
            string rhs_nz = rhs;
            rt_trim(rhs_nz, "0");
            // not valid if rhs is all zeros
            if(rhs_nz.length() == 0) {
                continue;
            }
            rhs_leading_zeros = true;

            rhs_val = stoi(rhs_nz);

            if(rhs_val + lhs_val == num) {
                printf("%srhs-%lld", numFound ? " " : "", num);
                numFound++;
                continue;
            }
        }
#endif

#ifdef LHS_LEADING_ZEROS
#ifdef RHS_LEADING_ZEROS
        // finally try both lhs & rhs with leading zeros
        if(rhs_leading_zeros && lhs_leading_zeros) {
            rt_trim(lhs, "0");
            rt_trim(rhs, "0");
            rhs_val = stoi(rhs);
            lhs_val = stoi(lhs);
            if(rhs_val + lhs_val == num) {
                printf(" %lld ", num);
                continue;
            }
        }
#endif
#endif
    }
    if(numFound == 0) {
        printf("INVALID RANGE");
    }
}

/*
 * Manasa and Stones
 * https://www.hackerrank.com/challenges/manasa-and-stones/problem
 *
Manasa is out on a hike with friends. She finds a trail of stones with numbers on them. She starts
following the trail and notices that any two consecutive stones' numbers differ by one of two values.
Legend has it that there is a treasure trove at the end of the trail. If Manasa can guess the value
of the last stone, the treasure will be hers.

Example:
n=2
a=2
b=3

She finds 2 stones and their differences are a=2 or b=3. We know she starts with a 0 stone not
included in her count. The permutations of differences for the two stones are [2,2],[2,3],[3,2]
or [3,3]. Looking at each scenario, stones might have [2,4],2,5],[3,5] or [3,6] on them. The
last stone might have any of 4,5, or 6 on its face.

Compute all possible numbers that might occur on the last stone given a starting stone with a 0
on it, a number of additional stones found, and the possible differences between consecutive
stones. Order the list ascending.

Function Description:
stones has the following parameter(s):
    int n: the number of non-zero stones
    int a: one possible integer difference
    int b: another possible integer difference

Returns:
    int[]: all possible values of the last stone, sorted ascending

Input Format:
The first line contains an integer , the number of test cases.
Each test case contains  lines:
- The first line contains n, the number of non-zero stones found.
- The second line contains a, one possible difference
- The third line contains b, the other possible difference.

Sample Input:
2       T = 2 (test cases)

3       n = 3 (test case 1)
1       a = 1
2       b = 2

4       n = 4 (test case 2)
10      a = 10
100     b = 100

Sample Output
2 3 4
30 120 210 300

Explanation:
With differences 1 and 2, all possible series for the first test
case are given below:
0,1,2
0,1,3
0,2,3
0,2,4
Hence the answer 2 3 4.

With differences 10 and 100, all possible series for the second
test case are the following:

0, 10, 20, 30
0, 10, 20, 120
0, 10, 110, 120
0, 10, 110, 210
0, 100, 110, 120
0, 100, 110, 210
0, 100, 200, 210
0, 100, 200, 300
Hence the answer 30 120 210 300.
 */

int possible_stonesV0(set<int>& bag, int n, int a, int b, int val) {
    if(n == 0) return 0;
    if(n == 1) {  // last level of includes all possible stones
        int val_plus_a = val + a;
        int val_plus_b = val + b;
        //cout << val_plus_a << " ";
        //cout << val_plus_b << " ";
        bag.emplace(val_plus_a);
        bag.emplace(val_plus_b);
    }
    possible_stonesV0(bag, n-1, a, b, val+a);
    possible_stonesV0(bag, n-1, a, b, val+b);
    return bag.size();
}
int possible_stones(set<int>& bag, int n, int a, int b, int val) {
    for(int level=n; level<0; level--) {
        int val_plus_a = val + a;
        int val_plus_b = val + b;
        if(n == 1) {  // last level of includes all possible stones
            //cout << val_plus_a << " ";
            //cout << val_plus_b << " ";
            bag.emplace(val_plus_a);
            bag.emplace(val_plus_b);
        }

    }
    possible_stones(bag, n-1, a, b, val+a);
    possible_stones(bag, n-1, a, b, val+b);
    return bag.size();
}

vector<int> stonesV0(int n, int a, int b) {
    set<int> bag_of_stones;
    vector<int> result;
    int num_stones =
    possible_stones(bag_of_stones, n, a, b, 0);
    cout << endl << num_stones << " Stones: ";
    for(auto stone : bag_of_stones) {
        cout << stone << " ";
        result.push_back(stone);
    }
    cout << endl;
    return result;
}

vector<int> stonesV1(int num_stones, int a, int b) {
     vector<int> result;
     unordered_set<int> bag_of_stones;
     queue<int> q;

     q.emplace(0);

     while(num_stones--)
     {
         int nodeCount = q.size();

         while(nodeCount--)
         {
             int last_stone = q.front();
             q.pop();

             if(num_stones == 1) {
                 bag_of_stones.emplace(last_stone + a);
                 bag_of_stones.emplace(last_stone + b);
             }
             else {
                 q.emplace(last_stone + a);
                 q.emplace(last_stone + b);
             }
         }
     }
     for(auto stone : bag_of_stones) {
         result.push_back(stone);
     }
     sort(begin(result), end(result));
     printVector("Stones", result);

     return result;
}

vector<int> stones(int num_stones, int a, int b) {
    vector<int> result(num_stones);

    for(int i=0; i<num_stones; i++) {
        result[i] = (a * i) + (b * (num_stones - (i + 1)));
    }
    sort(begin(result), end(result));
    auto itr = unique(begin(result), end(result));
    result.resize(distance(begin(result), itr));
    //printVector("Stones", result);
    return result;
}

int msMain()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    int T;
    cin >> T;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int T_itr = 0; T_itr < T; T_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int a;
        cin >> a;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int b;
        cin >> b;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        vector<int> result = stones(n, a, b);
        printf("\nTest %d: ", T_itr+1);
        for (size_t i = 0; i < result.size(); i++) {
            cout << result[i];

            if (i != result.size() - 1) {
                cout << " ";
            }
        }

        cout << "\n";
    }

    //fout.close();

    return 0;
}

/*
 * Beautiful Triplets
 * https://www.hackerrank.com/challenges/beautiful-triplets/problem
 *
Given a sequence of integers a, a triplet (a[i],a[j],a[k]) is beautiful if:
    o i < j < k
    o a[j] - a[i] = a[k] - a[j] = d

Given an increasing sequence of integers and the value of d, count the number
of beautiful triplets in the sequence.

For example, the sequence arr = [2,2,3,4,5] and d=1. There are three beautiful
triplets, by index: [i,j,k] = [0,2,3],[1,2,3],[2,3,4].

To test the first triplet, arr[j] - arr[i] = 3 - 2 = 1 and arr[k] - arr[j] = 4 - 3 = 1.

Input Format:
The first line contains 2 space-separated integers n and d, the length of the
sequence and the beautiful difference.
The second line contains n space-separated integers arr[i].

Output Format:
Print a single line denoting the number of beautiful triplets in the sequence.

Sample Input:
7 3
1 2 4 5 7 8 10

Sample Output:
3

Explanation:
7 - 4 = 4 - 1 = 3 = d   OR  1 + 3 = 4, 4 + 3 = 7
10 - 7 = 7 - 4 = 3 = d  OR  4 + 3 = 7, 7 + 3 = 10
8 - 5 = 5 - 2 = 3 = d   OR  2 + 3 = 5, 5 + 3 = 8
 */
int beautifulTriplets(int d, vector<int> arr) {
    int num_triplets = 0;
    int arr_len = arr.size();
    if(!arr_len) return 0;
    int max_val = *rbegin(arr);
    unordered_multimap <int, int> minusd_map;

    int idx = arr_len - 1;
    for(auto ritr=rbegin(arr); ritr!=rend(arr); ++ritr) {
        int minusd = *ritr - d;

        if(minusd < 0)
            break;

        //printf("Hashing %d lookup for arr[%d] = %d\n", minus3, idx, *ritr);
        minusd_map.emplace(make_pair(minusd, idx--));
    }

    for(auto& val : arr) {
        auto itr = minusd_map.find(val);
        //printf("Lookup %d...", val);
        if(itr!=end(minusd_map)) {
            auto idx = itr->second;
            int twin = arr[idx];
            int triplet = twin + d;
            if(triplet > max_val) {
                //printf("Third number out of range, no more triplets\n");
                break;
            }
            //printf("found %d, looking for triplet %d\n", twin, triplet);

            auto triplet_itr = minusd_map.find(twin);
            if(triplet_itr != end(minusd_map)) {
                //printf("Found a triplet!\n");
                num_triplets++;
            }
        }
    }

    return num_triplets;
}

/*
 * Minimum Distance
 *
The distance between two array values is the number of indices between them. Given a,
find the minimum distance between any pair of equal elements in the array. If no such
value exists, return -1.

Example:
There are two matching pairs of values: 3 and 2. The indices of the 3's are i=0 and
j=4, so their distance is d[i,j] = |j-i| = 4. The indices of the 2's are i=1 and j=3,
so their distance is d[i,j] = |j-i| = 2. The minimum distance is 2.

minimumDistances has the following parameter(s):
    o int a[n]: an array of integers

Returns:
    int: the minimum distance found or -1 if there are no matching elements

Input Format:
The first line contains an integer n, the size of array a.
The second line contains n space-separated integers a[i].
 */
int minimumDistances(vector<int> arr) {
    multimap<int, int> arr_map;
    const int MAX_IDX = 100'000;  // 1< a[i] <= 10**5
    int min_dist = MAX_IDX;

    if(min_dist <= 1) return (-1);

    int elem_idx=0;
    for(auto elem : arr) {
        printf("val=%d, idx=%d\n", elem, elem_idx);
        arr_map.insert(make_pair(elem, elem_idx++));
    }
    sort(begin(arr), end(arr));
    auto uitr = unique(begin(arr), end(arr));
    arr.erase(uitr, arr.end());

    for(auto val : arr) {
        if(arr_map.count(val) >= 2) {
            // Equivalent to: make_pair(arr_map.lower_bound(val), arr_map.upper_bound(val))
            auto pitr = arr_map.equal_range(val);
            int prev_idx = pitr.first->second;
            auto itr=pitr.first;
            for(++itr; itr!=pitr.second; ++itr) {
                int curr_idx = itr->second;
                min_dist = min(min_dist, curr_idx - prev_idx);
                printf("pair: val=%d, idx=%d, dist=%d\n", itr->first, itr->second, curr_idx - prev_idx);
            }
        }
    }

    return min_dist == MAX_IDX ? (-1) : min_dist;
}

/*
 * Halloween Sale
 * https://www.hackerrank.com/challenges/halloween-sale/problem
 *
You wish to buy video games from the famous online video game store Mist. Usually, all games are
sold at the same price, p dollars. However, they are planning to have  the seasonal Halloween
Sale next month in which you can buy games at a cheaper price. Specifically, the first game will
cost p dollars, and every subsequent game will cost d dollars less than the previous one. This
continues until the cost becomes less than or equal to m dollars, after which every game will
cost m dollars. How many games can you buy during the Halloween Sale?
 */
int howManyGames(int starting_price, int deduction, int limit, int budget) {
    // Return the number of games you can buy
    int num_games = 0;
    int next_price = starting_price;

    while(budget >= next_price) {
        next_price = starting_price - (num_games * deduction);
        if(next_price <= limit)
            next_price = limit;
        if(next_price > budget)
            break;
        num_games++;
        budget -= next_price;
        //printf("bought 1 game for %d$, budget = %d\n", next_price, budget);
    }
    return num_games;
}

/*
 * Chocolate Feast
 * https://www.hackerrank.com/challenges/chocolate-feast/problem
 *
Returns:
    int: the number of chocolates Bobby can eat after taking full advantage of the promotion
 */
int chocolateFeast(int budget, int cost, int exchange) {
    if(budget < cost) { return 0; }

    int num_chocos = budget / cost;
    int num_wrappers = num_chocos;

    while(num_wrappers >= exchange) {
        int num_exchanged = num_wrappers / exchange;
        num_chocos += num_exchanged;
        num_wrappers = (num_wrappers % exchange) + num_exchanged;
    }
    return num_chocos;
}

/*
 * Service Lane
 * https://www.hackerrank.com/challenges/service-lane/problem
 *
You will be given an array of widths at points along the road (indices), then a list of the indices
of entry and exit points. Considering each entry and exit point pair, calculate the maximum size
vehicle that can travel that segment of the service lane safely.

Input Format:
The first line of input contains two integers, n and t, where n denotes the number of width measurements
and t, the number of test cases. The next line has n space-separated integers which represent the array
width. The next t lines contain two integers, i and j, where i is the start index and j is the end index
of the segment to check.

Sample Input:
8 5                 ;n = 8, t = 5
2 3 1 2 3 2 3 3     ;width = [2, 3, 1, 2, 3, 2, 3, 3]
0 3                 ;cases = [[0, 3], [4, 6], [6, 7], [3, 5], [0, 7]]
4 6
6 7
3 5
0 7
Returns:
    o int[t]: the maximum width vehicle that can pass through each segment of the service
      lane described
 */
vector<int> serviceLane(int n, vector<int> width, vector<vector<int>> cases) {
    vector<int> result;

    for(auto& indices : cases)
    {
        int start = indices[0];
        int end = indices[1];
        auto wstart = &width[start];
        auto wend = &width[end+1];
        int min_width = *min_element(wstart, wend);
        result.push_back(min_width);
    }

    return result;
}

int slMain()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string nt_temp;
    getline(cin, nt_temp);

    vector<string> nt = split_string(nt_temp);

    int n = stoi(nt[0]);

    int t = stoi(nt[1]);

    string width_temp_temp;
    getline(cin, width_temp_temp);

    vector<string> width_temp = split_string(width_temp_temp);

    vector<int> width(n);

    for (int i = 0; i < n; i++) {
        int width_item = stoi(width_temp[i]);

        width[i] = width_item;
    }

    vector<vector<int>> cases(t);
    for (int i = 0; i < t; i++) {
        cases[i].resize(2);

        for (int j = 0; j < 2; j++) {
            cin >> cases[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    vector<int> result = serviceLane(n, width, cases);

    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i];

        if (i != result.size() - 1) {
            cout << "\n";
        }
    }

    cout << "\n";

    //fout.close();

    return 0;
}

/*
 * Lisa's Workbook
 *
Lisa just got a new math workbook. A workbook contains exercise problems, grouped into chapters.
Lisa believes a problem to be special if its index (within a chapter) is the same as the page
number where it's located. The format of Lisa's book is as follows:

There are  chapters in Lisa's workbook, numbered from 1 to n.
The  chapter has arr[i] problems, numbered from 1 to arr[i].
Each page can hold up to k problems. Only a chapter's last page of exercises may contain fewer than k problems.
Each new chapter starts on a new page, so a page will never contain problems from more than one chapter.
The page number indexing starts at 1.
Given the details for Lisa's workbook, can you count its number of special problems?

For example, Lisa's workbook contains arr[1] = 4 problems for chapter 1, and arr[2] = 2 problems
for chapter 2.
Each page can hold k = 3 problems.
The first page will hold 3 problems for chapter 1.
Problem 1 is on page 1, so it is special.
Page 2 contains only Chapter 1, Problem 4, so no special problem is on page 2.
Chapter 2 problems start on page 3 and there are 3 problems.
Since there is no problem 3 on page 3, there is no special problem on that page either.
There is 1 special problem in her workbook.

 */
int workbook(int chapters, int probs_per_page, vector<int> arr) {
    int page_num = 0;
    int chap = 0;
    int num_special = 0;
    for(int problems : arr) {
        int ppp = 0;
        page_num++;
        printf("chapter %d: %d problems\n", ++chap, problems);
        for(int pnum=1; pnum <= problems; pnum++) {
            if(ppp++ == probs_per_page) {
                page_num++;
                ppp = 1;
            }
            printf("ppp=%d, problem #%d, page %d", ppp, pnum, page_num);
            if(pnum == page_num) {
                printf(" *** special ***\n");
                num_special++;
            }
            else {
                printf("\n");
            }
        }
    }
    return num_special;
}

/*
 * Flatland Space Stations
 *
https://www.hackerrank.com/challenges/flatland-space-stations/problem

Hackerrank user Java solution:
// This is a better solution...
private static int solution(int[] arr, int n){
    Arrays.sort(arr);
    int maxDistance = arr[0];
    for(int i = 1; i < arr.length; i++){
        int distance = (arr[i] - arr[i-1]) / 2;
        if(maxDistance < distance) maxDistance = distance;
    }
    int lastGap = (n-1) - arr[arr.length - 1];
    return (lastGap < maxDistance) ? maxDistance : lastGap;
}
 */
int flatlandSpaceStations(int num_cities, vector<int> ss_cities) {
    vector<int> sslen(num_cities, num_cities);
    sort(begin(ss_cities), end(ss_cities));
    int first_city = ss_cities.front();
    int last_city = ss_cities.back();
    unordered_set<int> ss(begin(ss_cities), end(ss_cities));
    int prev_len = 0;

    cout << "Space Stations: ";
    for(auto& city : ss_cities) {
        cout << city << " ";
    }
    cout << endl;
    // first forward
    for(int i=0; i<num_cities; i++) {
        if(ss.find(i) != ss.end()) {
            sslen[i] = 0;
            if(i == last_city) { break; }
        }
        else {
            sslen[i] = prev_len + 1;
        }
        prev_len = sslen[i];
    }

    prev_len = 0;
    for(int j=num_cities-1; j>=0; j--) {
        if(ss.find(j) != ss.end()) {
            sslen[j] = 0;
            if(j == first_city) { break; }
        }
        else {
            sslen[j] = min(sslen[j], prev_len + 1);
        }
        prev_len = sslen[j];
    }

    return *max_element(begin(sslen), end(sslen));
}

/*
 * Fair Rations
 * https://www.hackerrank.com/challenges/fair-rations/problem
 *
You are the benevolent ruler of Rankhacker Castle, and today you're distributing bread. Your
subjects are in a line, and some of them already have some loaves. Times are hard and your
castle's food stocks are dwindling, so you must distribute as few loaves as possible according
to the following rules:
    o Every time you give a loaf of bread to some person i, you must also give a loaf of bread
      to the person immediately in front of or behind them in the line (i.e., persons i+1 or i-1).
    o After all the bread is distributed, each person must have an even number of loaves.
      Given the number of loaves already held by each citizen, find and print the minimum number
      of loaves you must distribute to satisfy the two rules above. If this is not possible,
      print NO.

Input Format:
The first line contains an integer N, the number of subjects in the bread line.
The second line contains N space-separated integers B[i].

Constraints:
  o 2 <= N <= 1000
  o 1 <= B[i] <= 10, where 1 <= i <= N

Output Format:
Print a single integer that denotes the minimum number of loaves that must be distributed so
that every person has an even number of loaves. If it's not possible to do this, print NO.

Sample Input 0:
5
2 3 4 5 6

Sample Output 0:
4

Explanation 0:
The initial distribution is (2,3,4,5,6). The requirements can be met as follows:

Give 1 loaf of bread each to the second and third people so that the distribution becomes 2,4,5,5,6.
Give 1 loaf of bread each to the third and fourth people so that the distribution becomes 2,4,6,6,6.
Each of the n subjects has an even number of loaves after 4 loaves were distributed.
 */
#define isOdd(a)    (a & 1)
#define isEven(a)   (!(a & 1))
string fairRations(vector<int> breadline) {
    int loaves = 0;
    int num_subjects = breadline.size();
    if(num_subjects == 2) {
        int first = breadline[0];
        int second = breadline[1];
        if(isOdd(first) && isOdd(second))
            return "2";
        else if(isEven(first) && isEven(second))
            return "0";
        else
            return "NO";
    }

    for(int i=1; i<num_subjects-1; i++) {
        int& prev_p = breadline[i-1];
        int& curr_p = breadline[i];

        if(isOdd(prev_p) && isOdd(curr_p)) {
            prev_p++;
            curr_p++;
            loaves+=2;
        }
        else if(isOdd(prev_p) & isEven(curr_p)) {
            prev_p++;
            curr_p++;
            loaves+=2;
        }
        else if(isEven(prev_p) && isOdd(curr_p)) {
            // let last odd/even decide YES or NO
        }
        else {
            // both even...continue
        }

    }
    int last_p = breadline[num_subjects-1];
    int last_curr_p = breadline[num_subjects-2];

    if(isOdd(last_p) && isOdd(last_curr_p)) {
        return to_string(loaves + 2);
    }
    else if(isEven(last_p) && isEven(last_curr_p)) {
        return to_string(loaves);
    }
    return "NO";
}

/*
 * Happy Ladybugs
 * https://www.hackerrank.com/challenges/happy-ladybugs/problem
 *
Happy Ladybugs is a board game having the following properties:
    o The board is represented by a string, b, of length n. The  character of the string,
      b[i], denotes the ith cell of the board.
      o If b[i] is an underscore (i.e., _), it means the ith cell of the board is empty.
      o If b[i] is an uppercase English alphabetic letter (ascii[A-Z]), it means the ith
        cell contains a ladybug of color b[i].
      o String  will not contain any other characters.
    o A ladybug is happy only when its left or right adjacent cell (i.e., b[i+/-1) is
      occupied by another ladybug having the same color.
    o In a single move, you can move a ladybug from its current position to any empty cell.
Given the values of n and b for b games of Happy Ladybugs, determine if it's possible to
make all the ladybugs happy. For each game, print YES on a new line if all the ladybugs
can be made happy through some number of moves. Otherwise, print NO.

Input Format:
The first line contains an integer g, the number of games.
The next  pairs of lines are in the following format:
    o The first line contains an integer , the number of cells on the board.
The second line contains a string  describing the  cells of the board.

Sample Input 0:
4
7
RBY_YBR
6
X_Y__X
2
__
6
B_RRBR

Sample Output 0:
YES
NO
YES
YES
 */
string happyLadybugs(string ladybugs) {
    string NO("NO");
    string YES("YES");
    if(ladybugs.length() == 1) {
        if(ladybugs[0] == '_')
            return YES;
        return NO;
    }
    vector<int> bug_color(26);
    int spaces=0;
    int num_bugs = 0;
    int num_spaces = 0;

    for(auto ch : ladybugs) {
        if(ch == '_') {
            spaces++;
            num_spaces++;
        }
        else {
            int bug = ch - 'A';    // 'A' -> 1, 'B' -> 2...
            bug_color[bug]++;
            num_bugs++;
        }
    }
    // need at least 2 matching ladybugs
    auto itr = find(begin(bug_color), end(bug_color), 1);
    if(itr != end(bug_color)) {
        return NO;
    }
    if(0 == num_bugs) {
        return YES;
    }
    if(num_spaces > 0) {
        return YES;
    }

    // What is left has minimum size of 2 and has no spaces, only ladybugs
    char prev_bug = ladybugs[0];
    char curr_bug = ladybugs[1];
    int last_idx = ladybugs.size()-1;
    char last_bug = ladybugs[last_idx];
    char next_to_last_bug = ladybugs[last_idx-1];
    // first and last 2 must be matched pairs
    if((prev_bug != curr_bug) || (next_to_last_bug != last_bug)) {
        return NO;
    }

    for(int i=1; i<last_idx-1; i++) {
        curr_bug = ladybugs[i];
        char next_bug = ladybugs[i+1];
        if(curr_bug != prev_bug && curr_bug != next_bug) {
            return NO;
        }
        prev_bug = curr_bug;
    }

    return YES;
}

/*
 * Strange Counter
 * https://www.hackerrank.com/challenges/strange-code/problem
 *
There is a strange counter. At the first second, it displays the number 3. Each second,
the number displayed by decrements by 3 until it reaches 1. In next second, the timer
resets to 2 x the initial number for the prior cycle and continues counting down. The
diagram below shows the counter values for each time t in the first three cycles:

time: 1,2,3
val:  3,2,1
reset
time: 4,5,6,7,8,9
val:  6,5,4,3,2,1
reset
time: 10,11,12,13,14,15...21
val:  12,11,10,9,8,7......1

Find and print the value displayed by the counter at time t.

Constraints:
  o 1 <= t <= 10**12 = 1'000'000'000'000
 */
long long strangeCounter(long long time) {

    double ftime = time;
    double fpower = ceil(ftime/3);
    fpower = log2(fpower);
    long ipower = fpower;
    double fcycle = 3 * pow(2, ipower);
    long long llcycle = fcycle;
    long long t_start = llcycle - 2;
    long long counter = llcycle - (time - t_start);
    //printf("time %lld: cycle = %lld, counter = %lld\n", time, llcycle, counter);
    return counter;
}

int scMain()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    long long t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    long long result = strangeCounter(1'000'000'000'000);

    cout << "Max value = " << result << "\n";

    //fout.close();

    return 0;
}

int main()
{
    cout << "https://www.hackerrank.com/" << endl;

    for(long long t=10; t<=30; t++)
        strangeCounter(t);
    return 0;
    cout << happyLadybugs("____") << endl;
    cout << happyLadybugs("AAZZ") << endl;
    cout << happyLadybugs("AA_Z") << endl;
    cout << happyLadybugs("A_ZZ") << endl;
    cout << happyLadybugs("AABBCD_DZZ") << endl;

    return 0;

    cout << fairRations({2,3,4,5,6});
    return 0;

    int dist_ss = flatlandSpaceStations(95, {68, 81, 46, 54, 30, 11, 19, 23, 22, 12, 38, 91, 48, 75, 26, 86, 29, 83, 62});
    printf("Max distance to space station = %d\n", dist_ss);
    dist_ss = flatlandSpaceStations(5, {0, 4});
        printf("Max distance to space station = %d\n", dist_ss);
    return 0;

    int num_special = workbook(5, 3, {4,2,6,1,10});
    printf("Found %d special problems\n", num_special);
    return 0;
    slMain();
    return 0;

    int num_chocos = chocolateFeast(10, 2, 5);
    printf("chocos bought = %d\n", num_chocos);
    num_chocos = chocolateFeast(12, 4, 4);
    printf("chocos bought = %d\n", num_chocos);
    num_chocos = chocolateFeast(6, 2, 2);
    printf("chocos bought = %d\n", num_chocos);
    return 0;

    int num_games = howManyGames(20, 3, 6, 80);
    printf("games bought = %d\n", num_games);
    return 0;

    int min_dist = minimumDistances({7, 7});
    printf("min dist = %d\n", min_dist);
    return 0;

    vector<int> triplets_arr {1, 2, 4, 5, 7, 8, 10};
    int num_triplets = beautifulTriplets(3, triplets_arr);
    printf("Triplets = %d\n", num_triplets);
    num_triplets = beautifulTriplets(3, {0, 3, 6});
    printf("Triplets = %d\n", num_triplets);
    num_triplets = beautifulTriplets(1, {2,2,3,4,5});
    printf("Triplets = %d\n", num_triplets);
    return 0;

    msMain();
    return 0;

    //stones(3, 10, 100);
    stones(4, 10, 100);
    return 0;

    //kaprekarNumbers(99630, 99630);
    kaprekarNumbers(1, 99999);
    return 0;

    acmMain();
    return 0;

    vector<string>grid{"989", "191", "111"};
    printVector("Grid Before", grid);
    auto cm_result = cavityMap(grid);
    printVector("Grid Result", cm_result);
    return 0;
    //sasMain();
    //return 0;

    int numbers = 100;
    auto start = high_resolution_clock::now();
    int num_squares = squares(1, numbers);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "number of squares 1 - " << numbers << ": " << num_squares << endl;
    cout << "1st squares timing: " << duration.count() << " microseconds" << endl;
    return 0;
    //numbers *= 10;
    start = high_resolution_clock::now();
    num_squares = squares(8, 963);
    cout << "number of squares 1 - " << numbers << ": " << num_squares << endl;
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "2nd squares timing: " << duration.count() << " microseconds" << endl;
    cout << "Done" << endl;
    return 0;

    /*
    //numbers *= 10;
    num_squares = squares(1, numbers);
    cout << "number of squares 1 - " << numbers << ": " << num_squares << endl;
    numbers *= 10;
    num_squares = squares(1, numbers);
    cout << "number of squares 1 - " << numbers << ": " << num_squares << endl;
    numbers *= 10;
    num_squares = squares(1, numbers);
    cout << "number of squares 1 - " << numbers << ": " << num_squares << endl;
    numbers *= 10;
    num_squares = squares(1, numbers);
    cout << "number of squares 1 - " << numbers << ": " << num_squares << endl;
    numbers *= 10;
    num_squares = squares(1, numbers);
    cout << "number of squares 1 - " << numbers << ": " << num_squares << endl;
    */

    cout << "Repeated 'a' = ";
    cout << repeatedString("aba", 10) << endl;
    return 0;

    cout << appendAndDelete("abcdef", "fedcba", 15) << " (should be 'Yes')" << endl;
    cout << appendAndDelete("ashley", "ash", 2) << " (should be 'No')" << endl;
    cout << appendAndDelete("aaaaaaaaaa", "aaaaa", 7) << " (should be 'Yes')" << endl;
    cout << appendAndDelete("zzzzz", "zzzzzzz", 4) << " (should be 'Yes')" << endl;
    cout << appendAndDelete("y", "yu", 2) << " (should be 'No')" << endl;
    cout << appendAndDelete("hackerhappy", "hackerrank", 9) << " (should be 'Yes')" << endl;
    cout << appendAndDelete("aba", "aba", 7) << " (should be 'Yes')" << endl;
    return 0;
    cout << "Digits 124: " << findDigits(124) << endl;
    return 0;
    jotcMain();
    return 0;

    seMain();
    return 0;

    carMain();
    return 0;

    stpMain();
    return 0;

    vaMain();
    return 0;

    apMain();
    return 0;

    cout << "Period  Height" << endl;
    for(int cycle=0; cycle<=10; cycle++)
        cout << cycle << "        " << utopianTree(cycle) << endl;
    return 0;

    hrMain();
    return 0;

    pnMain();
    return 0;

    esMain();
    return 0;

    cvMain();
    return 0;

    smMain();
    return 0;

    cout << "1800: " << dayOfProgrammer(1800) << endl;
    cout << "1918: " << dayOfProgrammer(1918) << endl;
    cout << "1984: " << dayOfProgrammer(1984) << endl;
    cout << "2016: " << dayOfProgrammer(2016) << endl;
    cout << "2017: " << dayOfProgrammer(2017) << endl;

    mbMain();
    return 0;

    dspMain();
    return 0;

    subarrayDivision();
    return 0;

    breakingTheRecords();
    return 0;

    betweenTwoSets();
    return 0;

    jumpingKangaroos();
    return 0;

    applesAndOranges();
    return 0;

    string grades_count_temp;
    getline(cin, grades_count_temp);

    int grades_count = stoi(ltrim(rtrim(grades_count_temp)));

    vector<int> grades(grades_count);

    for (int i = 0; i < grades_count; i++) {
        string grades_item_temp;
        getline(cin, grades_item_temp);

        int grades_item = stoi(ltrim(rtrim(grades_item_temp)));

        grades[i] = grades_item;
    }

    vector<int> result = gradingStudents(grades);

    for (int i = 0; i < (int) result.size(); i++) {
        cout << result[i];

        if (i != (int) result.size() - 1) {
            cout << "\n";
        }
    }

    cout << "\n";

    return 0;
}

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

// http://www.martinbroadhurst.com/how-to-trim-a-stdstring.html
string& lft_trim(string& str, const string& chars = "\t\n\v\f\r ")
{
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

string& rt_trim(string& str, const string& chars = "\t\n\v\f\r ")
{
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

string& trim(string& str, const string& chars = "\t\n\v\f\r ")
{
    return lft_trim(rt_trim(str, chars), chars);
}

vector<string> split_string(string input_string) {
    // interesting way to condense multiple space to a single space
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    // remove the excess spaces from the condensed input string
    input_string.erase(new_end, input_string.end());

    // remove trailing space(s) from input string (b/c of previous call to unique s/b at most a single space
    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    // translates to 'until the end of the string'
    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
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
