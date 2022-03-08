//============================================================================
// Name        : hacker-rank-interview-prep.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://www.hackerrank.com/
//============================================================================

#include <bits/stdc++.h>

#define DEBUG 0
#define dprintf(fmt, ...) \
    do { if(DEBUG) fprintf(stdout, fmt, ##__VA_ARGS__); } while (0)
using namespace std;
using namespace std::chrono;

string ltrim(const string &);
string rtrim(const string &);
string& lft_trim(string& str, const string& chars);
string& rt_trim(string& str, const string& chars);
string& trim(string& str, const string& chars);

vector<string> split_string(string);
vector<string> split(const string &);
int count_digits(int n);
int triangular_number(int n);

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
 * 2D Array - DS
 * https://www.hackerrank.com/challenges/2d-array/
 *
There are 16 hourglasses in arr. An hourglass sum is the sum of an hourglass' values.
Calculate the hourglass sum for every hourglass in arr, then print the maximum hourglass
sum. The array will always be 6 x 6.
 */
int hourglassSum(vector<vector<int>> arr) {
    int max_hg_sum = -100;
    int sum_num = 0;

    for(int row=0; row<4; row++) {
        auto& v1 = arr[row];
        auto& v2 = arr[row+1];
        auto& v3 = arr[row+2];
        for(int col=0; col<4; col++) {
            int hg_sum = 0;
            int top = accumulate(begin(v1)+col, begin(v1)+col+3, 0);
            int mid = v2[col+1] + top;
            hg_sum = accumulate(begin(v3)+col, begin(v3)+col+3, mid);
            max_hg_sum = max(max_hg_sum, hg_sum);
            sum_num++;
        }
    }
    return max_hg_sum;
}

int two_d_arr_ds_main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    vector<vector<int>> arr(6);
    for (int i = 0; i < 6; i++) {
        arr[i].resize(6);

        for (int j = 0; j < 6; j++) {
            cin >> arr[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    printMatrix("Hour Glass", arr);

    int result = hourglassSum(arr);

    cout << result << "\n";

    //fout.close();

    return 0;
}

/*
 * Arrays: Left Rotation
 * https://www.hackerrank.com/challenges/ctci-array-left-rotation/problem
A left rotation operation on an array shifts each of the array's elements 1 unit to the left. For example,
if 2 left rotations are performed on array [1,2,3,4,5], then the array would become [3,4,5,1,2]. Note that
the lowest index item moves to the highest index in a rotation. This is called a circular array.

Given an array a of n integers and a number, d, perform d left rotations on the array. Return the updated
array to be printed as a single line of space-separated integers.

rotLeft has the following parameter(s):
    o int arr[n]: the array to rotate
    o int d: the number of rotations

Returns:
    o int arr[n]: the rotated array

Constraints:
    o 1 <= n <= 100,000
    o 1 <= d <= n
    o 1 <= arr[i] <= 1,000,000
 */
vector<int> rotLeft(vector<int> arr, int d) {
    // Div is only necessary when rotations is greater than array size
    // auto num_elements = arr.size();
    // d %= num_elements;

    // Rotates left the order of the elements in the range [first,last), in such a way
    // that the element pointed by middle becomes the new first element.
    //printVector("Array", arr);
    auto middle = begin(arr) + d;
    rotate(begin(arr), middle, end(arr));
    return arr;
}

int rl_main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string nd_temp;
    getline(cin, nd_temp);

    vector<string> nd = split_string(nd_temp);

    int n = stoi(nd[0]);

    int d = stoi(nd[1]);

    string a_temp_temp;
    getline(cin, a_temp_temp);

    vector<string> a_temp = split_string(a_temp_temp);

    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        int a_item = stoi(a_temp[i]);

        a[i] = a_item;
    }

    vector<int> result = rotLeft(a, d);

    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i];

        if (i != result.size() - 1) {
            cout << " ";
        }
    }

    cout << "\n";

    //cout.close();

    return 0;
}

/*
 * Minimum Swaps 2
 * https://www.hackerrank.com/challenges/minimum-swaps-2/problem
 *
You are given an unordered array consisting of consecutive integers  [1, 2, 3, ..., n] without any duplicates.
You are allowed to swap any two elements. Find the minimum number of swaps required to sort the array in
ascending order.

minimumSwaps has the following parameter(s):
    o int arr[n]: an unordered array of integers

Returns:
    o int: the minimum number of swaps to sort the array

Constraints:
    1 <= n  <= 100,000
    1 <= arr[i] <= n
 */
int minimumSwaps(vector<int> arr) {
    map<int, int> arr_map;

    int idx = 0;
    for(auto elem : arr) {
        arr_map[elem] = idx++;
    }

    idx = 0;
    int num_swaps = 0;
    for(auto elem : arr_map) {
        int arr_val = arr[idx];
        if(arr_val != elem.first) {
            auto itr = arr_map.find(arr_val);
            if(itr != arr_map.end()) {
                num_swaps++;
                int swap_idx = elem.second;

                int swap_val = arr[swap_idx];
                arr[idx] = arr[swap_idx];

                arr[swap_idx] = arr_val;
                arr_map[swap_val] = idx;
                arr_map[arr_val] = swap_idx;
            }
        }
        idx++;
    }
    return num_swaps;
}

int ms_main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    int res = minimumSwaps(arr);

    cout << res << "\n";

    //fout.close();

    return 0;
}

/*
 * New Years Chaos
 * https://www.hackerrank.com/challenges/new-year-chaos/problem
 *
It is New Year's Day and people are in line for the Wonderland rollercoaster ride. Each person wears
a sticker indicating their initial position in the queue from 1 to n. Any person can bribe the person
directly in front of them to swap positions, but they still wear their original sticker. One person
can bribe at most two others.

Determine the minimum number of bribes that took place to get to a given queue order. Print the number
of bribes, or, if anyone has bribed more than two people, print Too chaotic.
 */
void minimumBribesFwd(vector<int> q) {
    int total_bribes = 0;

    int original_position = 1;
    for(auto it=q.begin(); it!=q.end(); ++it) {
        int sticker = *it;
        if(sticker - original_position++ > 2) {
            { cout << "Too chaotic" << endl; return; }
        }
        int bribes = count_if(it, q.end(),
                [sticker](int position){ return(position < sticker); });
        printf("MBF: sticker %d, bribes taken = %d\n", sticker, bribes);
        total_bribes += bribes;
    }

    cout << total_bribes << endl;
}

void minimumBribesRev(vector<int> q) {
    int total_bribes = 0;

    int original_position = q.size();
    for(auto rit=q.rbegin(); rit!=q.rend(); ++rit) {
        int sticker = *rit;
        if(sticker - original_position-- > 2) {
            { cout << "Too chaotic\n"; return; }
        }
        // A position may have at most 1 larger number
        // ahead of its original position.
        int max_ahead_idx = (sticker - 2) > 0 ? (sticker-2):0;

        // rend() is pointer to theoretical element preceding the first element (mirror of end())
        // rbase()
        auto last_idx = distance(q.rend(), q.rend() + max_ahead_idx);
        // a reverse_iterator has always an offset of -1 with respect to its base iterator
        auto idx = distance(q.begin(), rit.base()) - 1;
        printf("counting from idx=%ld to last_idx=%ld\n", (long int) idx, (long int) last_idx);
        auto last_it = max_ahead_idx > 0 ? q.rend() - max_ahead_idx : q.rend();
        printf("counting from sticker=%d to origin-1=%d\n", *rit, *last_it);
        int bribes = count_if(rit, last_it,
                [sticker](int position) {
                  return(position > sticker);
            });
        total_bribes += bribes;
    }

    cout << total_bribes << endl;
}

void minimumBribesTest(vector<int> q) {
    int bribes=0;
    for(int i=q.size();i>=1;--i)
    {
        if (q[i - 1] - i > 2) {
            cout << "Too chaotic\n";
            return;
        }
        //Check to front of my position, if there are numbers greater than me then they must have bribed me to get ahead.
        for(int j=i-2;j>=max(q[i-1]-2,0);--j) {
            printf("Testing q[%d]=%d > q[%d]=%d: %s\n", j, q[j], i-1, q[i-1], (q[j] > q[i-1]) ? "Yes" : "No");
            if(q[j]>q[i-1]) bribes++;
        }
    }
    cout<<bribes<<"\n";
}

int nyc_main()
{
    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string q_temp_temp;
        getline(cin, q_temp_temp);

        vector<string> q_temp = split_string(q_temp_temp);

        vector<int> q(n);

        for (int i = 0; i < n; i++) {
            int q_item = stoi(q_temp[i]);

            q[i] = q_item;
        }

        minimumBribesTest(q);
    }

    return 0;
}

/*
 * Array Manipulation
 * https://www.hackerrank.com/challenges/crush/problem
 *
Starting with a 1-indexed array of zeros and a list of operations, for each operation
add a value to each the array element between two given indices, inclusive. Once all
operations have been performed, return the maximum value in the array.
 */
struct Operations {
    int left_idx;
    int right_idx;
    int summand;

public:
    Operations(int left, int right, int sum): left_idx(left), right_idx(right), summand(sum) {

    }
};

long long arrayManipulationV1(int n, vector<vector<int>> queries) {
    vector<long long> arr(n, 0);
    int first_left_idx = n;
    int last_left_idx = 0;

    long long max_val = 0;
    auto begin_itr = begin(arr);
    for(auto& query : queries) {
        int left_idx = query[0] - 1;
        if(left_idx < first_left_idx)
            first_left_idx = left_idx;
        if(left_idx > last_left_idx)
            last_left_idx = left_idx;

        int right_idx = query[1];  // -1 is adjusted
        int summand = query[2];

        // right iterator is specified as 'one-past'
        transform(begin_itr+left_idx, begin_itr+right_idx, begin_itr+left_idx,
            [summand, &max_val](long long elem) {
                max_val = max(max_val, elem+summand);
                return elem + summand;});
            }

    return max_val; //*max_element(begin_itr+first_left_idx, begin_itr+last_left_idx+1);
}

// https://www.hackerrank.com/challenges/crush/forum
long long arrayManipulationV2(int arr_len, vector<vector<int>> queries) {
    vector<long long> arr(arr_len+2, 0);    // 1-indexing + right index test
    int first_left_idx = arr_len+1;
    int last_left_idx = 0;

    for(auto& query : queries) {
        int left_idx = query[0];
        if(left_idx < first_left_idx)
            first_left_idx = left_idx;
        if(left_idx > last_left_idx)
            last_left_idx = left_idx;

        int right_idx = query[1];
        int summand = query[2];

        arr[left_idx] += summand;
        arr[right_idx+1] -= summand;
    }
    long long  max_val = 0;
    long long arr_sum = 0;
    for(auto itr=begin(arr)+first_left_idx; itr != begin(arr)+last_left_idx+1; ++itr) {
        arr_sum += *itr;
        max_val = max(max_val, arr_sum);
    }
    return max_val;
}

int am_main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));
    bool fileio = true;
    string fname("/home/carlos/Documents/am-test4-input.txt");
    ifstream ifile(fname);
    istream& str = fileio ? ifile : cin;

    if(fileio && ifile.fail()) {
        cout << "Unable to open file " << fname << endl;
        return -1;
    }

    string nm_temp;
    getline(str, nm_temp);

    vector<string> nm = split_string(nm_temp);

    int n = stoi(nm[0]);

    int m = stoi(nm[1]);

    vector<vector<int>> queries(m);
    for (int i = 0; i < m; i++) {
        queries[i].resize(3);

        for (int j = 0; j < 3; j++) {
            str >> queries[i][j];
        }
        if(!fileio) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    long long result = arrayManipulationV2(n, queries);

    cout << result << "\n";

    //fout.close();

    return 0;
}

/*
 * Hash Tables: Ransom Note
 * https://www.hackerrank.com/challenges/ctci-ransom-note/problem
 *

 */
void checkMagazine(vector<string> magazine, vector<string> note) {
    unordered_multiset<string> mag_set(begin(magazine), end(magazine));
    unordered_multiset<string> note_set(begin(note), end(note));
    unordered_set<string> history;

    for(auto& word : note) {
        if(history.find(word) != end(history)) {
            continue;
        }
        if(mag_set.find(word) == end(mag_set)) {
            cout << "No";
            return;
        }
        else if(mag_set.count(word) < note_set.count(word)) {
            cout << "No";
            return;
        }
        history.emplace(word);
    }
    cout << "Yes";
    return;
}

/*
 * Count Triplets
 * https://www.hackerrank.com/challenges/count-triplets-1/problem
 *
You are given an array and you need to find number of triplets of indices (i,j,k) such that
the elements at those indices are in geometric progression for a given common ratio r and i<j<k.

countTriplets has the following parameter(s):
    o int arr[n]: an array of integers
    o int r: the common ratio

Example:
arr = [1,4,16,64], r = 4
There are [1,4,16] and [4,16,64] at indices (0,1,2) and (1,2,3). Return 2.

Constraints:
    1 <= n <= 100,000
    1 <= r <= 1,000,000,000
    1 <= arr[i] <= 1,000,000,000

Notes:
https://www.statisticshowto.com/probability-and-statistics/probability-main-index/permutation-combination-formula/
The hardest part about solving permutation and combination problems is:
    Which is a combination and which is a permutation?

Combination: If you don't care what order you have things, it's a combination. Think of combining ingredients,
    or musical chords: Flour, salt and water in a bowl is the same as salt, water and flour. Lottery tickets,
    where you pick a few numbers, are a combination. That's because the order doesn't matter (but the numbers
    you select do). You can also have combinations in mathematics, like combinations of functions or linear
    combinations.

Permutation: IF YOU DO CARE ABOUT ORDER, IT'S A PERMUTATION. Picking winners for a first, second and third
    place raffle is a permutation, because the order matters. Permutation isn't a word you use in everyday
    language. It's the more complex of the two. Details matters: Eggs first? Then salt? Or flour first?

Permutations = More Possibilities

You always have fewer combinations than permutations, and here's why:
Take the numbers 1, 2, 3, 4. If you want to know how many ways you can select 3 items where the order doesn't
matter (and the items aren't allowed to repeat), you can pick:

123
234
134
124

However, if you want permutations (where the order does matter, the same set has 24 different possibilities.
Just take the first set of numbers listed above {1, 2, 3} and think of the ways you can order it.

123
132
321
312
231
213

There are 6 ways to order the 3 numbers, which means there are 4 x 6 ways to order the set of 4 numbers.

Repetitions are just repeating numbers. They become important when it comes to choosing the right formula.

123 has no repetitions (each of those numbers is unique).
223 has the number 2 repeated.

Allowing repetition depends on your situation. For example:

    o Combination locks can have any number in any position (for example, 9, 8, 9, 2), so repetitions are
      allowed. The number "9" appears twice here.

    o Lottery numbers don't allow repetition. The same number won't appear twice in the same ticket. For
      example, you can pick numbers 67, 76, and 99. But you can't choose 67, 67, and 67 as your winning ticket.

Logic should tell you if repetitions are allowed. For example, if you're dealing with items that
aren't going to be replaced (like lottery balls), then you're looking at no repetitions allowed.

The Formulas:
Combination (C) and permutation (P) each have their own formula:

    C(n,r) =    n!
             -------
             r!(n-r)!

    P(n,r) =    n!
             -------
              c++ (n-r)!

Overflow Problem:
    Factorials get very big very quickly.  Factorial 13 will overflow a 32 bit integer.

For answer to arr[100] with all '1''s:
Google equation '100 choose 3'. Answer is 161700
https://www.hackmath.net/en/calculator/n-choose-k?n=100&k=3&order=0&repeat=0
    C(100,3) =    100!        100 * 99 * 98
               ----------  =  -------------  =  161700
               3!(100-3)!       3 * 2 * 1
 */
long countTriplets(vector<long> arr, long common_ratio) {
    int arr_len = arr.size();
    if(arr_len < 3) {
        return 0;
    }
    int tripletState = 1;
    long num_triplets = 0;
    int multiplier = 0;
    long prev_val = arr[0];
    long arr_val = 0;

    for(int i=1; i<arr_len; i++) {
        arr_val = arr[i];
        printf("arr_val=%ld, prev_val=%ld\n", arr_val, prev_val);
        if(arr_val == prev_val) {
            multiplier++;
            if(arr_val == 1) {
                if(tripletState < 3) {
                    tripletState++;
                }
                if(tripletState == 3) {
                    num_triplets++;
                }
            }
        }
        else if(arr_val == prev_val * common_ratio) {
            printf("arr_val=%ld == prev_val*common_ratio\n", arr_val);
            prev_val = arr_val;
            if(tripletState < 3) {
                tripletState++;
            }
            if(tripletState == 3) {
                num_triplets++;
            }
        }
        else {
            tripletState = 1;
            prev_val = arr_val;
        }
    }
    printf("num_triplets=%ld, multiplier=%d, tripletState=%d\n", num_triplets, multiplier, tripletState);
    return num_triplets * pow(2, multiplier);
}

/*
 * Frequency Queries
 * https://www.hackerrank.com/challenges/frequency-queries/problem
 *
You are given q queries. Each query is of the form two integers described below:
- 1 x: Insert x in your data structure.
- 2 y: Delete one occurrence of y from your data structure, if present.
- 3 z: Check if any integer is present whose frequency is exactly z. If yes, print 1 else 0.

The queries are given in the form of a 2-D array queries of size q where queries[i][0]
contains the operation, and queries[i][1] contains the data element.

Example
queries = [(1,1),(2,2),(3,2),(1,1),(2,1),(3,2)]

The results of each operation are:
Operation   Array   Output
(1,1)       [1]
(2,2)       [1]
(3,2)                 0
(1,1)       [1,1]
(1,1)       [1,1,1]
(2,1)       [1,1]
(3,2)                 1

Return an array with the output [0,1]

 */
vector<int> freqQuery(vector<vector<int>> queries) {
    map <int, int> freq_map;
    map <int, int> freq_count_map;
    vector<int> result;
    enum class Actions {INVALID_OP, INSERT_X, DELETE_Y, FREQ_Z};
    int qcount = 1;

    for(auto& ops : queries) {
        int ops_action = ops[0];
        int ops_val = ops[1];
        dprintf("query %d: action=%d, val=%d: ", ++qcount, ops_action, ops_val);

        int prev_count = 0;
        int match = 0;
        auto itr = freq_map.find(ops_val);
        if(itr != end(freq_map)) {
            prev_count = itr->second;
        }
        if(static_cast<Actions>(ops_action) == Actions::INSERT_X) {
            dprintf("insert %d, prev_count=%d\n", ops_val, prev_count);
            freq_map[ops_val]++;
            if(prev_count > 0) {
                freq_count_map[prev_count]--;
                freq_count_map[prev_count+1]++;
            }
            else {
                freq_count_map[1]++;
            }
        }
        else if(static_cast<Actions>(ops_action) == Actions::DELETE_Y) {
            dprintf("delete %d, prev_count=%d\n", ops_val, prev_count);
            if(prev_count > 0) {
                freq_map[ops_val]--;
                freq_count_map[prev_count]--;
                if(prev_count-1 > 0) {
                    freq_count_map[prev_count-1]++;
                }
            }
        }
        else if(static_cast<Actions>(ops_action) == Actions::FREQ_Z) {
            // Actions: FREQ_Z
            if(freq_count_map.find(ops_val) != end(freq_count_map)) {
                auto fcm_itr = freq_count_map.find(ops_val);
                if(fcm_itr->second > 0) {
                    dprintf("add result 1 for count %d\n", ops_val);
                    match = 1;
                }
                else {
                    dprintf("add result 0 for count %d\n", ops_val);
                    match = 0;
                }
            }
            else {
                dprintf("add result 0 for count %d\n", ops_val);
                match = 0;
            }
            result.push_back(match);
        }
        else {
            // Invalid action
        }
    }
    return result;
}

int fq_main()
{
    // ofstream fout(getenv("OUTPUT_PATH"));
    bool fileio = true;
    string fname("/home/carlos/Documents/hr-fq-test8-input.txt");
    ifstream ifile(fname);
    istream& str = fileio ? ifile : cin;

    if(fileio && ifile.fail()) {
        cout << "Unable to open file " << fname << endl;
        return -1;
    }

    ofstream fout;
    // Open a test file and truncate the data for new output data
    fout.open("/home/carlos/Documents/fq-test8-output.txt", ios::out | ios::trunc);
    if(!fout.is_open()) {
        cout << "Unable to open output file\n";
        ifile.close();
        return -1;
    }

    string q_temp;
    getline(str, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    vector<vector<int>> queries(q);

    for (int i = 0; i < q; i++) {
        queries[i].resize(2);

        string queries_row_temp_temp;
        getline(str, queries_row_temp_temp);

        vector<string> queries_row_temp = split(rtrim(queries_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int queries_row_item = stoi(queries_row_temp[j]);

            queries[i][j] = queries_row_item;
        }
    }

    vector<int> ans = freqQuery(queries);

    for (size_t i = 0; i < ans.size(); i++) {
        fout << ans[i];

        if (i != ans.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();
    ifile.close();

    return 0;
}

/*
 * Sorting: Bubble Sort
 * https://www.hackerrank.com/challenges/ctci-bubble-sort/problem
 *
Consider the following version of Bubble Sort:
for (int i = 0; i < n; i++) {

    for (int j = 0; j < n - 1; j++) {
        // Swap adjacent elements if they are in decreasing order
        if (a[j] > a[j + 1]) {
            swap(a[j], a[j + 1]);
        }
    }
}
Given an array of integers, sort the array in ascending order using the Bubble Sort
algorithm above. Once sorted, print the following three lines:

  1. Array is sorted in numSwaps swaps., where numSwaps is the number of swaps that took place.
  2. First Element: firstElement, where firstElement is the first element in the sorted array.
  3. Last Element: lastElement, where lastElement is the last element in the sorted array.

Hint: To complete this challenge, you must add a variable that keeps a running tally of all swaps that occur during execution.
 */
void countSwaps(vector<int> a) {
    int n = a.size();
    int numSwaps = 0;
    //int firstElement = 0;
    //int lastElement = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            // Swap adjacent elements if they are in decreasing order
            if (a[j] > a[j + 1]) {
                numSwaps++;
                //swap(a[j], a[j + 1]);
                iter_swap(a.begin()+j, a.begin()+j+1);
            }
        }
    }

    printf("Array is sorted in %d swaps.\n", numSwaps++);
    printf("First Element: %d\n", a.front());
    printf("Last Element: %d\n", a.back());

}

/*
 * Mark and Toys
 * https://www.hackerrank.com/challenges/mark-and-toys/problem
 *
Mark and Jane are very happy after having their first child. Their son loves toys,
so Mark wants to buy some. There are a number of different toys lying in front of him,
tagged with their prices. Mark has only a certain amount to spend, and he wants to
maximize the number of toys he buys with this money. Given a list of toy prices and
an amount to spend, determine the maximum number of gifts he can buy.

Note Each toy can be purchased only once.
 */
int maximumToys(vector<int> prices, int budget) {

    sort(begin(prices), end(prices));

    int max_gifts = 0;
    int total_cost = 0;
    for(auto toy_price : prices) {
        total_cost += toy_price;
        if(total_cost >= budget) {
            return max_gifts;
        }
        max_gifts++;
    }
    return max_gifts;
}

/*
 * Sorting Comparator
 * https://www.hackerrank.com/challenges/ctci-comparator-sorting/problem
 *
Comparators are used to compare two objects. In this challenge, you'll create a comparator
and use it to sort an array. The Player class is provided in the editor below. It has two fields:
    1. name: a string
    2. score: an integer
Given an array of n Player objects, write a comparator that sorts them in order of decreasing score.
If 2 or more players have the same score, sort those players alphabetically ascending by name. To
do this, you must create a Checker class that implements the Comparator interface, then write an
int compare(Player a, Player b) method implementing the Comparator.compare(T o1, T o2) method.

In short, when sorting in ascending order, a comparator function returns -1 if a<b, 0 if a=b, and 1 if a>b.

Declare a Checker class that implements the comparator method as described. It should sort first
descending by score, then ascending by name. The code stub reads the input, creates a list of Player
objects, uses your method to sort the data, and prints it out properly.

Example:
n=3, data={{"Smith",20},{"Jones",15},{"Jones",20}}
Sort the list as {{"Jones",20},{"Smith",20},{"Jones",15}}
Sort first descending by score, then ascending by name

 */
struct Player {
    int score;
    string name;
};

class Checker{
public:
    // complete this method
    static int comparator(Player a, Player b)  {
        if(a.score < b.score) {
            return -1;
        }
        else if(a.score == b.score) {
            if(a.name < b.name) {
                return 1;
            }
            else if(a.name == b.name) {
                return 0;
            }
            else {
                return -1;
            }
        }
        else {
            return 1;
        }
    }
};

/*
 * Fraudulent Activity Notifications
 * https://www.hackerrank.com/challenges/fraudulent-activity-notifications/problem
 *
HackerLand National Bank has a simple policy for warning clients about possible fraudulent
account activity. If the amount spent by a client on a particular day is greater than or
equal to 2X the client's median spending for a trailing number of days, they send the client
a notification about potential fraud. The bank doesn't send the client any notifications
until they have at least that trailing number of prior days' transaction data.

Given the number of trailing days d and a client's total daily expenditures for a period of
n days, determine the number of times the client will receive a notification over all n days.

Example
expenditure = {10,20,30,40,50]
d = 3

On the first three days, they just collect spending data. At day 4, trailing expenditures are
[10,20,30]. The median is 20 and the day's expenditure is 40. Because 40 >= 2x20, there will
be a notice. The next day, trailing expenditures are [20,30,40] and the expenditures are 50.
This is less than 2x30 so no notice will be sent. Over the period, there was 1 notice sent.

Note: The median of a list of numbers can be found by first sorting the numbers ascending.
If there is an odd number of values, the middle one is picked. If there is an even number of
values, the median is then defined to be the average of the two middle values. (Wikipedia)

Constraints:
    1 <= n <= 2 x 10**5
    1 <= d <= n
    0 <= expenditure[i] <= 200

    vector<int> sorted_exps(begin(exps), begin(exps)+tdays+1);
    sort(begin(sorted_exps), end(sorted_exps));
    int tdays_mid = tdays/2;
    int median = odd_td ? sorted_exps[(tdays_mid)+1] : sorted_exps[tdays_mid] + sorted_exps[tdays_mid-1] / 2;

 */
/*
 * set_median()
 *
 * Median can be defined as the element in the data set which separates the higher half of the
 * data sample from the lower half. In other words, we can get the median element as, when the
 * input size is odd, we take the middle element of sorted data. If the input size is even, we
 * pick an average of middle two elements in the sorted stream.
 */
float set_median(multiset<int> arr) {
    int arr_size = arr.size();
    bool odd_arr = arr_size & 1;
    printf("%s-set { ", odd_arr ? "odd":"even");
    for(auto exp : arr) {
        cout << exp << " ";
    }
    cout << "}" << endl;
    auto low_itr = next(begin(arr), (arr_size/2) - 1);
    int high_side = *next(low_itr);
    if(odd_arr) return high_side;
    int low_side = *low_itr;
    float flt_median = (low_side + high_side)/2.0;
    return flt_median;
}

int activityNotificationsV2(vector<int> expenses, int tdays) {
    int num_exps = expenses.size();
    multiset <int> sorted_exps(begin(expenses), begin(expenses)+tdays);
    bool odd_size = tdays & 1;
    int notify_days = 0;
    const int low_mid_offset = (tdays/2) -1;

    for(int head=tdays, tail=0; head<num_exps; head++, tail++) {
        //
        auto low_itr = next(begin(sorted_exps), low_mid_offset);
        int high_side = *next(low_itr);
        float median_exp = 0; // = set_median(sorted_exps);
        if(odd_size) {
            median_exp = high_side;
        }
        else {
            int low_side = *low_itr;
            median_exp = (low_side + high_side)/2.0;
        }
        float new_expense = expenses[head];
        printf("day %d: median=%5.2f, expense=%5.2f\n", head+1, median_exp, new_expense);
        if(new_expense >= 2*median_exp) {
            notify_days++;
        }
        // move the expense window, deleting aged out expense...
        int aged_out_expense = expenses[tail];
        sorted_exps.erase(sorted_exps.find(aged_out_expense));
        // then adding new expenses
        sorted_exps.emplace(new_expense);
    }

    return notify_days;
}

int activityNotifications(vector<int> expenses, int tdays) {
    int num_exps = expenses.size();
    bool odd_size = tdays & 1;
    int notify_days = 0;
    unordered_map<int, int> hash_table;
    priority_queue<int, vector<int>, greater<int> > hi;
    priority_queue<int> lo(begin(expenses), begin(expenses)+tdays);
    // load hi queue with windows upper half values
    for(int i=0; i<tdays/2; i++) {
        hi.push(lo.top());
        lo.pop();
    }

    for(int head=tdays, tail=0; head<num_exps; head++, tail++) {
        float median = odd_size ? lo.top() : ((lo.top() + hi.top())/2.0);
        float expense = expenses[head];
        //printf("day %d: median=%5.2f, expense=%5.2f\n", head+1, median, expense);
        if(expense >= 2 * median) {
            notify_days++;
        }
        int aged_out_exp = expenses[tail];
        int balance = 0;

        // exit window
        balance += (aged_out_exp <= lo.top() ? -1 : 1);
        hash_table[aged_out_exp]++;

        // entrance window
        if(!lo.empty() && expense <= lo.top()) {
            balance++;
            lo.push(expense);
        }
        else {
            balance--;
            hi.push(expense);
        }

        // rebalance the heaps
        if(balance < 0) {
            lo.push(hi.top());
            hi.pop();
            balance++;
        }
        else if(balance > 0) {
            hi.push(lo.top());
            lo.pop();
            balance--;
        }

        // remove out of range numbers
        while(hash_table[lo.top()]) {
            hash_table[lo.top()]--;
            lo.pop();
        }
        while(!hi.empty() && hash_table[hi.top()]) {
            hash_table[hi.top()]--;
            hi.pop();
        }
    }

    return notify_days;
}

/*
 * Strings: Making Anagrams
 * https://www.hackerrank.com/challenges/ctci-making-anagrams/problem
 *
A student is taking a cryptography class and has found anagrams to be very useful. Two strings
are anagrams of each other if the first string's letters can be rearranged to form the second
string. In other words, both strings must contain the same exact letters in the same exact
frequency. For example, bacdc and dcbac are anagrams, but bacdc and dcbad are not.

The student decides on an encryption scheme that involves two large strings. The encryption is
dependent on the minimum number of character deletions required to make the two strings anagrams.
Determine this number.

Given two strings, a and b, that may or may not be of the same length, determine the minimum
number of character deletions required to make  and  anagrams. Any characters can be deleted
from either of the strings.

Example:
    a = 'cde'
    b = 'dcf'

Delete e from a and f from b so that the remaining strings are cd and dc which are anagrams.
This takes 2 character deletions.
 */
int makeAnagram(string s1, string s2) {
    vector<bool> freq_map(26);
    unordered_multiset<char> s1_set(begin(s1), end(s1));
    unordered_multiset<char> s2_set(begin(s2), end(s2));
    int total_slen = s1.length() + s2.length();

    int deletions=0;
    int chars_in_common = 0;
    for(auto ch : s2) {
        int idx = ch - 'a';
        // It's actually not necessary to use '.at' here as idx is guaranteed be 0 to 25.
        if(freq_map.at(idx)) {
            continue;
        }
        freq_map.at(idx) = true;
        // get a count of chars in common
        auto it = s1_set.find(ch);	// iterator it != end if char is common
        if(it != s1_set.end()) {
            int s1_count = s1_set.count(ch);
            int s2_count = s2_set.count(ch);
            chars_in_common += min(s1_count, s2_count) * 2;
        }
    }

    deletions = total_slen - chars_in_common;
    return deletions;
}

/*
 * Special String Again
 * https://www.hackerrank.com/challenges/special-palindrome-again/problem
 *
A string is said to be a special string if either of two conditions is met:
    o All of the characters are the same, e.g. aaa.
    o All characters except the middle one are the same, e.g. aadaa.

A special substring is any substring of a string which meets one of those criteria.
Given a string, determine how many special substrings can be formed from it.

Example 0:
    s = mnonopoo
    s contains the following 12 special substrings: {m,n,o,n,o,p,o,o,non,ono,opo,oo}.

Example 1:
    s = aaaa
    s contains 10 special substrings: {a,a,a,a, aa,aa,aa, aaa,aaa, aaaa} = {4 + 3 + 2 + 1}

Returns
- int: the number of special substrings

Input Format:
The first line contains an integer, n, the length of s.
The second line contains the string s.

Constraints
    1 <= n < 1,000,000

Each character of the string is a lowercase English letter, ascii[a - z].
 */
int extendPalindrome(string s, int slen, int j, int k, bool odd)
{
	int ssCount=0;

#ifdef DEBUGGING
	string extString(s);
	size_t jpos = j;
	extString.insert(jpos, "[");
	jpos+=2;
	extString.insert(jpos, "]");

	if(j != k) {
		jpos = k+2;
		extString.insert(jpos, "[");
		jpos+=2;
		extString.insert(jpos, "]");
	}
	if(j==k)
		printf("\nOdd extension  '%s':   j=%d, k=%d: ", extString.c_str(), j, k);
	else
		printf("\nEven extension '%s': j=%d, k=%d: ", extString.c_str(), j, k);
#endif
	// This is the key logic to finding palindrome substrings.
	// - The substring remains a palindrome as long as s[j] == s[k]
	// - The substring increases as j is decremented leftward relative to the string position
	//   and k is incremented rightward relative to the string position.

	if(odd) {
		ssCount++;
		j--; k++;
	}
	//bool once = true;
	const char *left = &s[j];
	const char *right = &s[k];
	char match = *left;

	while (j-- >= 0 && k++ < slen && *right == match && (*left-- == *right++)) {

		ssCount++;

		/*
		if(odd && once) {
			match = *left;
			once = false;
		}*/
	}

	return ssCount;
}


long substrCount(int sslen, string s)
{
    //printf("\nString: '%s'", s.c_str());
    //printf("\n");
    if(sslen == 1) {
        return 1;
    }
    else if(sslen == 2) {
        return (s[0] == s[1]) ? 3 : 2;
    }

    long total_ss_count = 0;
    //bool odd = slen & 1;
    const char *left = &s[0];
    const char *right = &s[1];

	for (int i = 0; i < sslen-1; i++) {
		total_ss_count += extendPalindrome(s, sslen, i, i, true);	// Odd length count
		if(*left++ == *right++)
		    total_ss_count += extendPalindrome(s, sslen, i, i+1, false); // Even length count
		//printf("%ld\r", total_ss_count);
	}
	// Add 1 for last character in string
	return total_ss_count + 1;
}

int sps_main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));
    bool fileio = true;
    string fname("C:\\Users\\zoani\\git\\repository\\hacker-rank-interview-prep\\hr-sps-test2-input.txt");
    ifstream ifile(fname);
    istream& str = fileio ? ifile : cin;

    if(fileio && ifile.fail()) {
        cout << "Unable to open file " << fname << endl;
        return -1;
    }

    /*
     * Output file is not necessary for a single output result
     *
    ofstream fout;
    // Open a test file and truncate the data for new output data
    fout.open("/home/carlos/Documents/sps-test2-output.txt", ios::out | ios::trunc);
    if(!fout.is_open()) {
        cout << "Unable to open output file\n";
        ifile.close();
        return -1;
    }
    */

    int n;
    str >> n;
    str.ignore(numeric_limits<streamsize>::max(), '\n');

    string s;
    getline(str, s);

    auto start = high_resolution_clock::now();
    long result = substrCount(n, s);
    auto stop = high_resolution_clock::now();
    cout << "number of substrings: " << result << endl;
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "function timing: " << duration.count()/1000000 << " seconds" << endl;

    cout << result << endl;

    //fout.close();
    ifile.close();

    return 0;
}

int main() {
	cout << "https://www.hackerrank.com/" << endl;
	sps_main(); // s/b 1272919
	return 0;
	long ss_count = 0;
	ss_count = substrCount(8, "mnonopoo");
    cout << "\nTotal substring = " << ss_count << endl; // s/b 12
    ss_count = substrCount(5, "asasd");    // s/b 7
    cout << "\nTotal substring = " << ss_count << endl; // s/b 12
    ss_count = substrCount(7, "abcbaba");  // s/b 10
    cout << "\nTotal substring = " << ss_count << endl; // s/b 12
    ss_count = substrCount(4, "aaaa");     // s/b 10
    cout << "\nTotal substring = " << ss_count << endl; // s/b 12
    ss_count = substrCount(12, "abbbbabacccc");     // s/b 10
    cout << "\nTotal substring = " << ss_count << endl; // s/b 12
	return 0;

    cout << activityNotifications({10,20,30,40,50}, 3) << endl;
    cout << activityNotifications({1,2,3,4,4}, 4) << endl;
    cout << activityNotifications({2,3,4,2,3,6,8,4,5}, 5) << endl;
	return 0;
	countSwaps({6,4,1});
	return 0;
	fq_main();
	return 0;
	vector<int> result;
	/* result = freqQuery({{1,1}, {2,2}, {3,2}, {1,1}, {1,1}, {2,1}, {3,2}});
	printVector("Result-1", result);
    result = freqQuery({{1,5}, {1,6}, {3,2}, {1,10}, {1,10}, {1,6}, {2,5}, {3,2}});
    printVector("Result-2", result);
    result = freqQuery({{3,4}, {2,1003}, {1,16}, {3,1}});
    printVector("Result-3", result); */
    //result = freqQuery({{1,3}, {2,3}, {3,2}, {1,4}, {1,5}, {1,5}, {1,4}, {3,2}, {2,4}, {3,2}});
    //result = freqQuery({{1,3}, {1,3}, {1,3}, {1,4}, {1,4}, {1,5}, {2,5}, {2,5}, {3,1}, {3,2}, {3,3}});
    result = freqQuery({{1,3}, {1,3}, {1,3}, {1,4}, {1,4}, {1,5}, {2,5}, {2,5}});
    printVector("Result-4", result);

	return 0;

	vector<long> ct_test(100, 1);
    //cout << countTriplets(ct_test, 100) << endl;
    cout << countTriplets({1,2,1,2,4}, 2) << endl;
	return 0;
	checkMagazine({"two", "times", "three", "is", "not", "four"},
	        {"two", "times", "two", "is", "four"});
	return 0;
    //cout << arrayManipulationV1(10, {{2,6,8},{3,5,7},{1,8,1},{5,9,15}}) << endl;
    //return 0;
    am_main();
    return 0;
    cout << arrayManipulationV1(10, {{1,5,3},{4,8,7},{6,9,1}}) << endl;
	cout << arrayManipulationV1(5, {{1,2,100}, {2,5,100}, {3,4,100}}) << endl;
    cout << arrayManipulationV1(10, {{2,6,8},{3,5,7},{1,8,1},{5,9,15}}) << endl;
	return 0;
	//nyc_main();
	//minimumBribesRev({1, 2, 5, 3, 7, 8, 6, 4});
    minimumBribesRev({2, 5,1, 3, 4});

	return 0;

	ms_main();
    return 0;

	rl_main();
	two_d_arr_ds_main();
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

// To count the no. of digits in a number
int count_digits(int n)
{
    // converting number to string using
    // to_string in C++
    string num = to_string(n);

    // calculate the size of string
    return num.length();
}

// factorial for 64bit long long integer.
// Note largest long long integer is LONG_LONG_MAX or (9,223,372,036,854,775,807);
// factorial for !21 exceeds this limit.
long long factorial(int i) {
    // ex: !5 = 5 * 4 * 3 * 2 * 1 = 120
    static long long factorials[] = {
        //  0  1  2  3  4   5
            1, 1, 2, 6, 24, 120,
            720, 5040, 40320, 362880, 3628800,
            39'916'800, 479'001'600, 6'227'020'800, 87'178'291'200, 1'307'674'368'000, 20'922'789'888'000,
            355'687'428'096'000, 6'402'373'705'728'000, 121'645'100'408'832'000, 2'432'902'008'176'640'000
    };
    if (i<0 || i>20) {
        fprintf(stderr, "Factorial input out of range\n");
        return -1;
        // exit(EXIT_FAILURE); // You could also return an error code here
    }
    return factorials[i];
}

int triangular_number(int n) {
    return (n * (n + 1)) / 2;
}
