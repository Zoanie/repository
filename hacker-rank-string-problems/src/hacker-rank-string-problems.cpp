//============================================================================
// Name        : hacker-rank-string-problems.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://www.hackerrank.com/
//============================================================================

#include <bits/stdc++.h>

#define DEBUG_ENABLED 1
#define DEBUG 1
#ifdef DEBUG_ENABLED
#define dprintf(fmt, ...) \
    do { if(DEBUG) fprintf(stdout, fmt, ##__VA_ARGS__); } while (0)
#endif
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
 * Super Reduced String
 * https://www.hackerrank.com/challenges/reduced-string/problem
 *
Reduce a string of lowercase characters in range ascii[‘a’..’z’]by doing a series of operations.
In each operation, select a pair of adjacent letters that match, and delete them.
Delete as many characters as possible using this method and return the resulting string.
If the final string is empty, return Empty String
 */

string superReducedString(string s) {
    bool found_adj_letters=false;
    cout << s;
    do {
        found_adj_letters = false;
        if(s.length()) {
            auto af_itr = adjacent_find(begin(s), end(s),
                    [](auto first, auto next){ return ((first == next) && (isalpha(first) && isalpha(next))); });
            if(af_itr != end(s)) {
                cout << " -> ";
                s.erase(af_itr, af_itr+2);
                found_adj_letters = true;
                cout << s;
            }
        }
        else {
            s = "Empty String";
            cout << s;
            break;
        }
    } while (found_adj_letters);

    cout << endl;

    return s;
}

int srsMain()
{
    //ofstream fout(getenv("OUTPUT_PATH"));
    string s;
    getline(cin, s);
    string result = superReducedString(s);
    cout << result << "\n";
    //fout.close();
    return 0;
}

/*
 * CamelCase
 * https://www.hackerrank.com/challenges/camelcase/problem
 *
There is a sequence of words in CamelCase as a string of letters, s, having the following properties:
    o It is a concatenation of one or more words consisting of English letters.
    o All letters in the first word are lowercase.
    o For each of the subsequent words, the first letter is uppercase and rest of the letters are
      lowercase.
Given s, determine the number of words in s.
 */
int camelcase(string s) {
    if(s.length() <= 1) {
        return (int) s.length();
    }
    int num_caps = count_if(begin(s), end(s), [](char c){ return isupper(c);});
    return 1 + num_caps;
}

/*
 * Two Characters
 * https://www.hackerrank.com/challenges/two-characters/problem
 *
Given a string, remove characters until the string is made up of any two alternating characters.
When you choose a character to remove, all instances of that character must be removed. Determine
the longest string possible that contains just two alternating letters.

Example:
s = 'abaacdabd'

Delete a, to leave bcdbd. Now, remove the character c to leave the valid string bdbd with a length
of 4. Removing either b or d at any point would not result in a valid string.
Given a string s, convert it to the longest possible string t made up only of alternating
characters. Print the length of string t on a new line. If no string t can be formed, print
0 instead.

Constraints:
    o 1 <= s.length() <= 1000
    s s[i] E (contains) ascii[a-z]

    womzxmuemangtoqgfqvznxerhravxnvomh b oqmvfagxgwt p g p qrmeoxvjunbjetepugbvhjxhpomrtmfhaogepvbwmpeiqumibjmrpgbv
 */
int alternating_len(string s, char a, char b) {
    int slen = s.length();
    if(slen <= 1)
        return 0;
    slen = 0;
    string altchars {a, b};
    auto ffo_itr = find_first_of(begin(s), end(s), begin(altchars), end(altchars));
    if(ffo_itr != end(s)) {
        char first = *ffo_itr;
        char second = (first == a) ? b : a;
        char next = first;
        char prev = second;
        //printf("first=%c, second=%c, next=%c\n", first, second, next);
        for(; ffo_itr != end(s); ffo_itr++) {
            auto ch = *ffo_itr;
            if(ch == next) {
                slen++;
                prev = ch;
                next = (next == first) ? second : first;
            }
            else if(ch == prev) {
                return 0;
            }
            else {
                ;
            }
        }
    }
    //printf("len alt-pair {%c, %c} = %d\n", a, b, slen);
    return slen;
}

struct elem_freq {
    char elem;
    int  freq;
};

int alternate(string s) {
    int slen = s.length();
    char rm_ch = 0;
    if(slen <= 1) {
        return 0;
    }

    // Actually this section removing the adjacent pairs is not necessary, but left in for the example
    bool found_adj_chars=false;
    //cout << s << endl;

    do {
        found_adj_chars = false;
        if(s.length()) {
            auto af_itr = adjacent_find(begin(s), end(s));
            if(af_itr != end(s)) {
                rm_ch = *af_itr;
                //printf(" -'%c' -> ", rm_ch);
                s.erase(remove(begin(s), end(s), rm_ch), end(s));
                found_adj_chars = true;
                //cout << s << endl;
            }
        }
        else {
            return 0;
        }
    } while (found_adj_chars);
    slen = s.length();
    if(slen <= 1) {
        return 0;
    }
    if(slen == 2) {
        return 2;
    }
    if(slen == 3) {
        if(s[0] == s[2])
            return 3;
        else
            return 2;
    }

    // Nice way to load a string into a set container, but...
    // it does not provide a frequency map - which is what is needed.
    //unordered_multiset<char> str_set(begin(s), end(s));
    vector<elem_freq> freq_map(26);  // 26 chars x 25 combinations = 650
    for(int idx=0; idx<26; idx++) {
        freq_map[idx].elem = 'a' + idx;
    }
    for(auto map_key : s) {
        // normally I would add isalpha(ch) and islower(ch), however...
        // the constraints of the problem limit the input to [a-z]
        int map_idx = map_key - 'a';
        freq_map[map_idx].elem = map_key;
        freq_map[map_idx].freq += 1;
        //printf("key %c = %d\n", map_key, freq_map.at(map_idx).freq);
    }
    sort(begin(freq_map), end(freq_map), [](elem_freq& a, elem_freq& b){ return a.freq > b.freq; });
    /*
    printf("Freq map:\n");
    int alpha_num = 1;
    for(auto& elem : freq_map) {
        printf("[%d] =  %c : %d\n", alpha_num++, elem.elem, elem.freq);
    }
    */
    int max_alt_s = 0;
    int map_size = freq_map.size();
    for(int aidx=0; aidx<map_size-1; aidx++) {
        for(int bidx=aidx+1; bidx<map_size; bidx++) {
            int max_possible_len = freq_map[aidx].freq + freq_map[bidx].freq;
            if((max_possible_len > max_alt_s) &&
               (freq_map[aidx].freq > 0 && freq_map[bidx].freq > 0)) {
                char elem_a = freq_map[aidx].elem;
                char elem_b = freq_map[bidx].elem;
                int next_alt_s = alternating_len(s, elem_a, elem_b);
                if(next_alt_s) {
                    //printf("Testing s[%d], s[%d] = [%c/0x%02x, %c/0x%02x] = %d\n", aidx, bidx, elem_a, elem_a, elem_b, elem_b, next_alt_s);
                    max_alt_s = max(max_alt_s, next_alt_s);
                }
            }
            else { break; }
        }
    }

    return max_alt_s;
}

/*
 * Strong Password
 * https://www.hackerrank.com/challenges/strong-password/problem
 *
Strong password criteria:

Its length is at least 6.
It contains at least one digit.
It contains at least one lowercase English character.
It contains at least one uppercase English character.
It contains at least one special character. The special characters are: !@#$%^&*()-+
 */
int minimumNumber(int n, string password) {
    // Return the minimum number of characters to make the password strong
    bool digit = false;
    bool lc = false;
    bool uc = false;
    bool special = false;

    string special_chars("!@#$%^&*()-+");
    auto found = password.find_first_of("!@#$%^&*()-+");
    if(found != string::npos) {
        special = true;
    }
    for(auto& ch : password) {
        if(isdigit(ch)) {
            digit = true;
        }
        else if(isupper(ch)) {
            uc = true;
        }
        else if(islower(ch)) {
            lc = true;
        }
    }
    int num_to_add = 0;
    if(!special)
        num_to_add++;
    if(!digit)
        num_to_add++;
    if(!uc)
        num_to_add++;
    if(!lc)
        num_to_add++;

    return (num_to_add < 6) ? 6 - num_to_add : num_to_add;
}

/*
 * Caesar Cipher
 * https://www.hackerrank.com/challenges/caesar-cipher-1/problem
Julius Caesar protected his confidential information by encrypting it using a cipher.
Caesar's cipher shifts each letter by a number of letters. If the shift takes you past
the end of the alphabet, just rotate back to the front of the alphabet. In the case of
a rotation by 3, w, x, y and z would map to z, a, b and c.
 */
string caesarCipher(string s, int rc) {
    cout << s << " -> ";
    transform(begin(s), end(s), begin(s),
            [rc](char ch) -> char {
                char char_case = 0x41;
                if(islower(ch)) { char_case = 0x61; }
                if(isalpha(ch)) {
                    return (char) (((ch-char_case)+rc)%0x1A)+char_case;
                }
                else {
                    return (char) ch;
                }
    });
    return s;
}

/*
 * Mars Exploration
 * https://www.hackerrank.com/challenges/mars-exploration/problem
 *
 */
int marsExploration(string s) {
    string signal("SOS");
    int idx = 0;
    int num_changed = 0;
    for(auto ch : s) {
        if(ch != signal[idx])
            num_changed++;
        idx++;
        idx %= 3;
    }
    return num_changed;
}

/*
 * HackerRank in a String!
 * https://www.hackerrank.com/challenges/hackerrank-in-a-string/problem
 *
We say that a string contains the word hackerrank if a subsequence of its characters spell the word hackerrank.
Remember that a subsequence maintains the order of characters selected from a sequence.
 */
// derived from https://www.geeksforgeeks.org/longest-common-subsequence-dp-4/
// Another way: Try loop using find_first_of
string hackerrankInString(string s) {
    int slen = s.length();
    string hr("hackerrank");
    int hrlen = hr.length();
    int lcs[slen + 1][hrlen + 1];

    printf("s=%s, hr=%s\n", s.c_str(), hr.c_str());

    for(int j=0; j<=hrlen; j++) {
        for(int i=0; i<=slen; i++) {
            if(i ==0 || j == 0) {
                lcs[i][j] = 0;
            }
            else if(s[i-1] == hr[j-1]) {
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
                printf("match %d: s[%d] = hr[%d]\n", lcs[i][j], i-1, j-1);
            }
            else {
                lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
                printf("no match %d: s[%d] != hr[%d]\n", lcs[i][j], i-1, j-1);

            }
        }
    }
    int lcs_len = lcs[slen][hrlen];
    return lcs_len == hrlen ? "YES" : "NO";
}

/*
    var hackerrank = new Queue<char>("hackerrank".ToCharArray());
    foreach (char c in text)
    {
        if (c == hackerrank.Peek())
            hackerrank.Dequeue();

        if (hackerrank.Count == 0)
            return "YES";
    }
 */
/*
 * Pangrams
 * https://www.hackerrank.com/challenges/pangrams/problem
 *
A pangram is a string that contains every letter of the alphabet. Given a sentence determine whether
it is a panagram in the English alphabet. Ignore case. Return either panagram or not panagram as appropriate.
 */
string pangrams(string s) {
    int letter_count = 0;
    // single event frequency map
    vector<bool> freq_map(26, false);  // 26 letters of the alphabet

    cout << "String '" << s << "' is ";
    for(auto map_key : s) {
        // the constraints of the problem limit the input to [a-z], [A-Z], space
        if(isalpha(map_key))
        {
            int map_idx = tolower(map_key) - 'a';
            if(!freq_map[map_idx]) {
               if(++letter_count == 26) {
                   return "pangram";
               }
               freq_map[map_idx] = true;
            }
        }
        //printf("key %c = %d\n", map_key, freq_map.at(map_idx).freq);
    }
    return "not pangram";
}

/*
 * Separate the Numbers
 * https://www.hackerrank.com/challenges/separate-the-numbers/problem
 *
A numeric string, s, is beautiful if it can be split into a sequence of two or more positive integers,
a[1],a[2],...,a[n], satisfying the following conditions:

    1. a[i] - a[i-1] = 1 for any 1 < i <= n (i.e., each element in the sequence is 1 more than
       the previous element).
    2. No a[i] contains a leading zero. For example, we can split s=10203 into the sequence [1,02,03},
       but it is not beautiful because 02 and 03 have leading zeroes.
    3. The contents of the sequence cannot be rearranged. For example, we can split 312 into the
       sequence [3,1,2], but it is not beautiful because it breaks our first constraint (i.e., 1-3 != 1).

Beautiful strings
    "1234" = 1 + 2 +3 + 4
    "91011" = 9 + 10 + 11
    "99100" = 99 + 100

Perform q queries where each query consists of some integer string s. For each query, print whether or
not the string is beautiful on a new line. If it is beautiful, print YES x, where  is the first number
of the increasing sequence. If there are multiple such values of x, choose the smallest. Otherwise,
print NO.

Constraints:
    1 <= q <= 10
    1 <= s <= 32
    s[i] == [0 - 9]

Sample Input 0:
7
1234
91011
99100
101103
010203
13
1

Sample Output 0:
YES 1
YES 9
YES 99
NO
NO
NO
NO
 */
// Note: this passes the hackerrank tests, but only because the testcases
// are not too onerous.  It will fail for the below test case:
// "1234 1235 1238 1234 1235 1239"
// Here the spaces are added for clarity only. The
void separateNumbers(string s) {
    int slen = s.length();
    int mid_point = slen / 2;
    long long int mid_int = -1;
    long long int start_num = -1;
    dprintf("string = '%s', len=%d\n", s.c_str(), slen);
    int curr_idx = 0;
    if(s[curr_idx] == '0') { cout << "NO" << endl; return; }

    long long curr_int = s[curr_idx] - '0';
    mid_int = curr_int;
    int curr_slen = 1;
    while(curr_idx + curr_slen < slen) {
        long long next_int = curr_int + 1;
        string next_s = to_string(next_int);
        int next_slen = next_s.length();

        string match_s = s.substr(curr_idx + curr_slen, next_slen);

        dprintf("curr_idx=%d, curr_int=%llu, next_int=%llu, next_s='%s', match_s='%s'\n",
                curr_idx, curr_int, next_int, next_s.c_str(), match_s.c_str());

        if(match_s != next_s) {
            // NO MATCH
            if(curr_idx + curr_slen >= mid_point) {
                { cout << "NO" << endl; return; }
            }
            start_num = -1;
            curr_idx = 0;
            //curr_int = (curr_int * 10) + s[curr_idx + curr_slen] - '0';
            curr_int = mid_int;
            string mid_s = to_string(mid_int);
            curr_slen = mid_s.length();
            dprintf("no match: curr_idx = %d, curr_slen = %d, curr_int = %llu\n", curr_idx, curr_slen, curr_int);

            mid_int = (mid_int * 10) + s[curr_idx + curr_slen] - '0';
        }
        else {
            // MATCH
            if(curr_idx + curr_slen < mid_point) {
                mid_int = (mid_int * 10) + s[curr_idx + curr_slen] - '0';
            }
            if(start_num == -1) {
                start_num = curr_int;
            }
            curr_idx += curr_slen;
            curr_slen = next_slen;
            curr_int = next_int;
            dprintf("match: curr_idx = %d, curr_slen = %d, curr_int = %llu\n", curr_idx, curr_slen, curr_int);
        }
    }
    if(start_num >= 0)
        cout << "YES " << start_num << endl;
    else
        cout << "NO" << endl;
}

// https://www.hackerrank.com/apghr
// This one works - and its way less code
void separateNumbersV2(string s) {
    string t, a;
    {
        for(size_t l = 1; l <= s.size()/2 && s != t; l++){
            a = t = s.substr(0, l);
            for(int i = 1; t.size() < s.size(); i++)
                t += to_string(stoll(a) + i);
        }
        cout << (s == t ? "YES " + a : "NO") << endl;
    }
    return;
}

/*
 * Weighted Uniform Strings
 * https://www.hackerrank.com/challenges/weighted-uniform-string/problem
 *
A weighted string is a string of lowercase English letters where each letter has a weight.
Character weights are a to z from 1 to 26.

The weight of a string is the sum of the weights of its characters. For example:
apple = 1+16+16+12+5 = 30
ccccc = 3+3+3+3+3 = 15

A uniform string consists of a single character repeated zero or more times.
For example, ccc and a are uniform strings, but bcb and cd are not.

Given a string, s, let U be the set of weights for all possible uniform contiguous substrings
of string s. There will be  queries to answer where each query consists of a single integer.
Create a return array where for each query, the value is Yes if query[i] E U. Otherwise, append No.

Example:
 'abbcccdddd'
 queries = [1,7,5,4,15]
 Working from left to right the weights that exist are
 a      1
 b      2
 bb     4
 c      3
 cc     6
 ccc    9
 d      4
 dd     8
 ddd    12
 dddd   16

Now for each value in queries, see if it exists in the possible string weights.
The return array is ['Yes', 'No', 'No', 'Yes', 'No'].
 */
vector<string> weightedUniformStrings(string s, vector<int> queries) {
    vector<string> answer;
    unordered_multiset<int> wus;
    int prev_val = 0;
    int next_val = 0;
    for(auto ch : s) {
        int curr_val = ch - 0x60;    // 1 - 26
        if(curr_val == prev_val) {
            next_val += curr_val;
        }
        else {
            next_val = curr_val;
        }
        prev_val = curr_val;
        dprintf("%d ", next_val);
        wus.emplace(next_val);
    }

    for(auto q : queries) {
        if(wus.find(q) != wus.end()) {
            answer.push_back("Yes");
        }
        else {
            answer.push_back("No");
        }
    }
    return answer;
}
/*
 * Funny String
 * https://www.hackerrank.com/challenges/funny-string/problem
 *
To determine whether a string is funny, create a copy of the string in reverse e.g. abc -> cba. Iterating
through each string, compare the absolute difference in the ascii values of the characters at positions
0 and 1, 1 and 2 and so on to the end. If the list of absolute differences is the same for both strings,
they are funny.

Determine whether a give string is funny. If it is, return Funny, otherwise return Not Funny.
 */
string funnyString(string s) {
    int slen = s.length();

    for(int idx=0; idx<slen/2; idx++) {
        if(abs(s[idx] - s[idx+1]) != abs(s[slen-(idx+1)] - s[slen-(idx+2)])) {
            return "Not Funny";
        }
    }
    return "Funny";
}

/*
 * Gemstones
 *
There is a collection of rocks where each rock has various minerals embedded in it. Each type of mineral
is designated by a lowercase letter in the range ascii[a-z]. There may be multiple occurrences of a
mineral in a rock. A mineral is called a gemstone if it occurs at least once in each of the rocks in
the collection.

Given a list of minerals embedded in each of the rocks, display the number of types of gemstones in
the collection.

Example:
arr = ['abc','abc', 'bc']
The minerals b and c appear in each rock, so there are 2 gemstones.

Function Description:
gemstones has the following parameter(s):
    o string arr[n]: an array of strings

Returns:
    o int: the number of gemstones found
 */
int gemstones(vector<string> arr) {
    vector<int> freq_map(26);

    for(auto& rock : arr) {
        sort(begin(rock), end(rock));
        rock.erase(unique(begin(rock), end(rock)), end(rock));
        dprintf("rock: '%s'\n", rock.c_str());

        for(auto mineral : rock) {
            int idx = mineral - 'a';
            freq_map[idx]++;
        }
    }
    int num_gemstones = count_if(begin(freq_map), end(freq_map), [&](int gem) { return gem == (int) arr.size();});
    dprintf("gemstones = %d\n", num_gemstones);
    return num_gemstones;
}

/*
 * Alternating Characters
 * https://www.hackerrank.com/challenges/alternating-characters/problem
 *
You are given a string containing characters A and B only. Your task is to change it into a string
such that there are no matching adjacent characters. To do this, you are allowed to delete zero or
more characters in the string.

Your task is to find the minimum number of required deletions.
 */
int alternatingCharacters(string s) {
    int prev = s[0];
    int slen = s.length();
    int deletes = 0;
    for(int idx=1; idx<slen; idx++) {
        int curr = s[idx];
        if(curr == prev)
            deletes++;
        prev = curr;
    }
    return deletes;
}

/*
 * Beautiful Binary String
 * https://www.hackerrank.com/challenges/beautiful-binary-string/problem
 *
Alice has a binary string. She thinks a binary string is beautiful if and only if it doesn't contain
the substring "010". In one step, Alice can change a 0 to a 1 or vice versa. Count and print the
minimum number of steps needed to make Alice see the string as beautiful.
 */
int beautifulBinaryString(string b) {
    int slen = b.length();
    int deletes = 0;
    for(int idx=2; idx<slen; idx++) {
        char prev = b[idx-2];
        if(prev != '0') continue;
        char curr = b[idx-1];
        if(curr != '1') continue;
        char next = b[idx];
        if(next != '0') continue;
        deletes++;
        b[idx]='1';
    }
    return deletes;
}

/*
 * The Love-Letter Mystery
 * https://www.hackerrank.com/challenges/the-love-letter-mystery/problem
 *
James found a love letter that his friend Harry has written to his girlfriend. James is a prankster,
so he decides to meddle with the letter. He changes all the words in the letter into palindromes.

To do this, he follows two rules:
    1. He can only reduce the value of a letter by 1, i.e. he can change d to c, but he cannot
       change c to d or d to b.
    2. The letter a may not be reduced any further.

Each reduction in the value of any letter is counted as a single operation. Find the minimum number
of operations required to convert a given string into a palindrome.

Constraints:
1 <= |s| <= 10,000
All strings are composed of lower case English letters, ascii[a-z], with no spaces.

Sample Input:
abc
abcba
abcd
cba

Sample Output:
2
0
4
2
 */
int theLoveLetterMystery(string s) {
    int convert_count = 0;
    int idx=0;
    int jdx=s.length() - 1;
    while(idx < jdx) {

        if(s[idx] == s[jdx]) {
            ;
        }
        else if(s[idx] > s[jdx]) {
            while(s[idx] > s[jdx]) {
                s[idx]--;
                convert_count++;
            }
        }
        else {
            while(s[idx] < s[jdx]) {
                s[jdx]--;
                convert_count++;
            }
        }
        idx++;
        jdx--;
    }
    return convert_count;
}

/*
 * Palindrome Index
 * https://www.hackerrank.com/challenges/palindrome-index/problem
 *
Given a string of lowercase letters in the range ascii[a-z], determine the index of a character
that can be removed to make the string a palindrome. There may be more than one solution, but
any will do. If the word is already a palindrome or there is no solution, return -1. Otherwise,
return the index of a character to remove.

Sample Input:
aaab
baa
aaa

Sample Output:
3
0
-1
 */
bool isPalindrome(string::iterator low, string::iterator high)
{
    while (low < high)
    {
       if (*low != *high)
          return false;
       low++; high--;
    }
    return true;
}

int palindromeIndex(string s) {
    //  Initialize low and right by both the ends of the string
    int low = 0, high = s.length() - 1;
    //  loop until low and high cross each other
    while (low < high)
    {
        // If both characters are equal then move both pointer
        // towards end
        if (s[low] == s[high])
        {
            low++;
            high--;
        }
        else
        {
            /*  If removing s[low] makes the whole string palindrome.
                We basically check if substring str[low+1..high] is
                palindrome or not. */
            if (isPalindrome(s.begin() + low + 1, s.begin() + high))
                return low;

            /*  If removing s[high] makes the whole string palindrome
                We basically check if substring str[low+1..high] is
                palindrome or not. */
            if (isPalindrome(s.begin() + low, s.begin() + high - 1))
                return high;

            /* something is broke - it is not possible to make a palindrome */
            return -2;
        }
    }

    //  String is already a palindrome
    return -1;
}

/*
 * Anagram
 * https://www.hackerrank.com/challenges/anagram/problem
 *
Two words are anagrams of one another if their letters can be rearranged to form the other word.
Given a string, split it into two contiguous substrings of equal length. Determine the minimum
number of characters to change to make the two substrings into anagrams of one another.

Returns:
    o int: the minimum number of characters to change or -1.
 */
int anagram(string s) {
    int slen = s.length();
    if(slen & 0x01) { return -1; }
    vector<bool> freq_map(26);
    int split_len = slen/2;
    string s1 = s.substr(0, split_len);
    string s2 = s.substr(split_len, split_len);
    dprintf("s1=%s, s2=%s\n", s1.c_str(), s2.c_str());
    unordered_multiset<char> s1_set(begin(s1), end(s1));
    unordered_multiset<char> s2_set(begin(s2), end(s2));

    int changes=0;
    int chars_in_common = 0;
    for(auto ch : s2) {
        int idx = ch - 'a';
        dprintf("s1 lookup %c: ", ch);
        if(freq_map.at(idx)) {
            dprintf("already counted\n");
            continue;
        }
        freq_map.at(idx) = true;
        // get a count of chars in common
        auto it = s1_set.find(ch);
        if(it != s1_set.end()) {
            int s1_count = s1_set.count(ch);
            int s2_count = s2_set.count(ch);
            chars_in_common += min(s1_count, s2_count);
            dprintf("s1 has %d, s2 has %d, chars in common count = %d\n", s1_count, s2_count, chars_in_common);
        }
    }
    dprintf("common chars = %d\n", chars_in_common);
    changes = split_len - chars_in_common;
    return changes;
}

/*
 * Making Anagrams
 * https://www.hackerrank.com/challenges/making-anagrams/problem
 *
We consider two strings to be anagrams of each other if the first string's letters can be
rearranged to form the second string. In other words, both strings must contain the same
exact letters in the same exact frequency. For example, bacdc and dcbac are anagrams, but
bacdc and dcbad are not.

Alice is taking a cryptography class and finding anagrams to be very useful. She decides
on an encryption scheme involving two large strings where encryption is dependent on the
minimum number of character deletions required to make the two strings anagrams. Can you
help her find this number?

Given two strings, s1 and s2, that may not be of the same length, determine the minimum
number of character deletions required to make s1 and s2 anagrams. Any characters can be
deleted from either of the strings.

Example.
s1 = 'abc'
s2 = 'amnop'

The only characters that match are the 's so we have to remove bc from s1 and mnop from
s2 for a total of 6 deletions.
 */
int makingAnagrams(string s1, string s2) {
    vector<bool> freq_map(26);
    unordered_multiset<char> s1_set(begin(s1), end(s1));
    unordered_multiset<char> s2_set(begin(s2), end(s2));
    int total_slen = s1.length() + s2.length();

    int deletions=0;
    int chars_in_common = 0;
    for(auto ch : s2) {
        int idx = ch - 'a';
        if(freq_map.at(idx)) {
            continue;
        }
        freq_map.at(idx) = true;
        // get a count of chars in common
        auto it = s1_set.find(ch);
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
 * Game of Thrones - I
 * https://www.hackerrank.com/challenges/game-of-thrones/problem
 *
Dothraki are planning an attack to usurp King Robert's throne. King Robert learns of this conspiracy
from Raven and plans to lock the single door through which the enemy can enter his kingdom.

But, to lock the door he needs a key that is an anagram of a palindrome. He starts to go through his
box of strings, checking to see if they can be rearranged into a palindrome. Given a string, determine
if it can be rearranged into a palindrome. Return the string YES or NO.

Constraints:
    1 <= |s| <= 100,000
    s contains only lowercase letters [a - z]
 */

string gameOfThrones(string s) {
    unordered_multiset<char> got_set(begin(s), end(s));
    vector<bool> freq_map(26);
    int num_odd = 0;
    for(auto ch : got_set) {
        int idx = ch - 'a';
        if(freq_map.at(idx)) {
            continue;
        }
        freq_map.at(idx) = true;
        int num_ch = got_set.count(ch);
        if(num_ch & 0x01) {
            if(++num_odd > 1) {
                return "NO";
            }
        }
    }
    return "YES";
}

/*
 * Two Strings
 * https://www.hackerrank.com/challenges/two-strings/problem
 *
Given two strings, determine if they share a common substring. A substring may be as small as one character.
 */
string twoStrings(string s1, string s2) {
    unordered_multiset<char> s1_set(begin(s1), end(s1));
    for(auto ch : s2) {
        auto it = s1_set.find(ch);
        if(it != s1_set.end()) {
            return "YES";
        }
    }
    return "NO";
}

/*
 * String Construction
 * https://www.hackerrank.com/challenges/string-construction/problem
 *
Amanda has a string of lowercase letters that she wants to copy to a new string. She can perform the
following operations with the given costs. She can perform them any number of times to construct a
new string p:

    o Append a character to the end of string p at a cost of 1 dollar.
    o Choose any substring of p and append it to the end of p at no charge.
Given n strings s[i], find and print the minimum cost of copying each s[i] to p[i] on a new line.

For example, given a string s = 'abcabc', it can be copied for 3 dollars. Start by copying a, b and c
individually at a cost of 1 dollar per character. String p = 'abc' at this time. Copy p[0:2] to the
end of p at no cost to complete the copy.
 */
int stringConstruction(string s) {
    vector<bool> freq_map(26);
    int total_cost = 0;
    int cost = 0;
    for(auto ch : s) {
        int idx = ch - 0x61;
        if(freq_map.at(idx)) {
            cost = 0;
        }
        else {
            cost = 1;
            freq_map.at(idx) = true;
        }
        total_cost += cost;
    }
    return total_cost;
}

/*
 * Sherlock & the Valid String
 * https://www.hackerrank.com/challenges/sherlock-and-valid-string/problem
 *
Sherlock considers a string to be valid if all characters of the string appear the same number of times.
It is also valid if he can remove just  character at  index in the string, and the remaining characters
will occur the same number of times. Given a string , determine if it is valid. If so, return YES,
otherwise return NO.
 */
string isValid(string s) {
    //printf("s=%s:\n", s.c_str());
    vector<int> freq_map(26);

    for(auto ch : s) {
        int idx = ch - 0x61;
        freq_map.at(idx)++;
    }
    // mode: The most frequently occurring value in a distribution
    unordered_map<int, int> freq_hash;
    for(auto freq : freq_map) {
        if(freq!=0) {
            ++freq_hash[freq];
        }
    }

    auto mode = max_element(begin(freq_hash), end(freq_hash),
            []( const auto& a, const auto& b ){ return a.second < b.second ; });
    //printf("Frequency %d appears %d times\n", mode->first, mode->second);

    int valid_count = mode->first;
    bool one_char = true;

    for(int freq_idx=0; freq_idx<26; freq_idx++) {
        int freq_count = freq_map.at(freq_idx);
        if(freq_count == 0) { continue; }

        int freq_diff  = abs(freq_count - valid_count);
        if(freq_diff == 0) {
            ;
        }
        else if(freq_diff > 1 && freq_count != 1) {
            if(freq_count == 1 && one_char) {
                one_char = false;
            }
            else {
                return "NO";
            }
        }
        else if(freq_diff == 1 && one_char) {
            one_char = false;
        }
        else {
            return "NO";
        }
    }
    return "YES";
}

/*
 * Highest Value Palindrome
 * https://www.hackerrank.com/challenges/richie-rich/problem
 *
Palindromes are strings that read the same from the left or right, for example madam or 0110.
You will be given a string representation of a number and a maximum number of changes you can make.
Alter the string, one digit at a time, to create the string representation of the largest number
possible given the limit to the number of changes. The length of the string may not be altered,
so you must consider 0's left of all higher digits in your tests. For example 0110 is valid,0011 is not.

Given a string representing the starting number, and a maximum number of changes allowed, create
the largest palindromic string of digits possible or the string '-1' if it is not possible to
create a palindrome under the constraints.
 */
bool isPalindrome(string s)
{
    if(!s.length()) return false;

    auto low = begin(s);
    auto high = end(s)-1;

    while (low < high)
    {
       if (*low != *high)
          return false;
       low++; high--;
    }
    return true;
}

int palindromeChangeCount(string s) {
    if(!s.length()) return false;

    auto low = begin(s);
    auto high = end(s)-1;
    int change_count = 0;

    while (low < high)
    {
       if (*low != *high) {
           change_count++;
       }
       low++; high--;
    }
    return change_count;
}

string highestValuePalindrome(string s, int num_digits, int num_changes) {
    int slen = s.length();
    if(!slen) { return "-1"; }
    if(slen == 1) return num_changes ? "9" : s;

    // minimum number of changes to create palindrome
    int min_change_count = palindromeChangeCount(s);
    if(num_changes < min_change_count) return "-1";

    // additional changes available to maximize the number
    int max_val_changes = num_changes - min_change_count;

    char const nine = '9';

    auto l = s.begin();
    auto r = s.end()-1;
    // min_change_count is necessary make the string a palindrome
    // max_val_changes are what is available to increase the value
    int changes = num_changes;
    while(changes) {
        if(r > l) {
            if(*r > *l) {
                if(*r != nine && max_val_changes) {
                    *r = nine;
                    max_val_changes--;
                    changes--;
                }
                *l = *r;
                changes--;
            }
            else if(*l > *r) {
                if(*l != nine && max_val_changes) {
                    *l = nine;
                    max_val_changes--;
                    changes--;
                }
                *r = *l;
                changes--;
            }
            else {
                // *r == *l, only change if max val changes are available
                if(*r != nine) {  // only need to test one side
                    if(max_val_changes >= 2)
                    {
                        *l = nine;
                        *r = nine;
                        max_val_changes -= 2;
                        changes -= 2;
                    }
                }
                else {
                    ; // both *l and *r are 9, leave it as is
                }
            }
        }
        else if(r == l) {
            // overlap case of both max val and min changes types
            if(*r != nine) {
                if(max_val_changes) {
                    max_val_changes--;
                }
            }
            *r = nine;
            changes--;
        }
        else {
            break;
        }
        l++; r--;
    }

    return s;
}

int hvpMain() {
    int num_digits=0;
    int num_changes=0;
    string line;
    string fname("/home/carlos/Documents/hvp_input.txt");
    ifstream ifile(fname);
    istream& str = ifile;

    if(ifile.fail()) {
        cout << "Unable to open input file " << fname << endl;
        return -1;
    }

    getline(str,line);
    stringstream ss(line);
    ss >> num_digits;
    ss >> num_changes;
    getline(str, line);

    ofstream fout;
    // Open a test file and truncate the data for new output data
    fout.open("/home/carlos/Documents/hvp_output.txt", ios::out | ios::trunc);
    if(!fout.is_open()) {
        cout << "Unable to open output file\n";
        ifile.close();
        return -1;
    }
    string result = highestValuePalindrome(line, num_digits, num_changes);
    fout << result << endl;
    fout.close();
    ifile.close();

    return 0;
}

/*
 * Sherlock and Anagrams
 * https://www.hackerrank.com/challenges/sherlock-and-anagrams/problem
 *
Two strings are anagrams of each other if the letters of one string can be rearranged to form
the other string. Given a string, find the number of pairs of substrings of the string that are
anagrams of each other.

Constraints:
2 <= length of s <= 100
string s contains only lowercase letters in the range ascii[a - z].

Example:
s = mom
The list of all anagrammatic pairs is [m, m], [mo, om] at positions [0 - 2], [0,1 - 1,2] respectively
 */
/*
 * An anagram of a string is another string that contains same characters,
 * only the order of characters can be different.
 */
int testAnagram(string s1, string s2)
{
    vector<int> s1_freq_map(26);
    vector<int> s2_freq_map(26);

    //if string lengths are different
    if(s1.length()!=s2.length())
        return 0; //they are not anagrams

    // get freq map for s1
    for(auto ch : s1) {
        int idx = ch - 0x61;
        s1_freq_map.at(idx)++;
    }

    // get freq map for s2
    for(auto ch : s2) {
        int idx = ch - 0x61;
        s1_freq_map.at(idx)++;
    }

    return s1_freq_map == s2_freq_map ? 1 : 0;
}

int sherlockAndAnagrams(string s) {
    int slen = s.length();
    if(slen == 2) {
        if(s[0] == s[1]) {
            return 1;
        }
        return 0;
    }
    // load string into set
    unordered_map<string, int> saa_ss_map;

    for(int ss_len=1; ss_len<slen; ++ss_len) {
        // for each substring length
        for(int i=0; i <= slen-ss_len; ++i) {
            // starting substring position
            string ssp = s.substr(i, ss_len);
            // sort each substring
            sort(begin(ssp), end(ssp));
            saa_ss_map[ssp]++;
        }
    }

    // n choose k, with k = 2:
    // n choose 2 in probability: aka the number of ways to choose 2 elements (anagram pairs) out of n elements
    // https://www.reddit.com/r/learnmath/comments/3bg21t/what_exactly_is_n_choose_2_in_probability/
    // np = num * (num -1) / 2
    long long result = 0;
    for(auto ss : saa_ss_map) {
        long long ss_count = ss.second;
        result += (ss_count * (ss_count - 1)) / 2;
    }
    return result;
}

int main() {
	cout << "https://www.hackerrank.com/" << endl;
	//hvpMain();
	//return 0;
    cout << highestValuePalindrome("11331", 5, 4) << endl;
    return 0;
    cout << highestValuePalindrome("1231", 4, 3) << endl;
    cout << highestValuePalindrome("12321", 5, 1) << endl;
    cout << highestValuePalindrome("3943", 4, 1) << endl;
    cout << highestValuePalindrome("092282", 4, 3) << endl;
    cout << highestValuePalindrome("0011", 4, 1) << endl;

	return 0;
    cout << isValid("abc") << endl;
    cout << isValid("abcc") << endl;
    cout << isValid("abccc") << endl;
    cout << isValid("aabbcd") << endl;
    cout << isValid("aabbccddeefghi") << endl;
    cout << isValid("abcdefghhgfedecba") << endl;
    return 0;
    cout << stringConstruction("abcabc") << endl;
    cout << stringConstruction("abcd") << endl;
    cout << stringConstruction("abab") << endl;
    return 0;
    cout << twoStrings("hello", "world") << endl;
    cout << twoStrings("hi", "world") << endl;
    return 0;
    cout << gameOfThrones("aaabbbb") << endl;
    cout << gameOfThrones("cdefghmnopqrstuvw") << endl;
    cout << gameOfThrones("cdcdcdcdeeeef") << endl;
	return 0;
    cout << makingAnagrams("abc", "amnop") << endl;
    cout << makingAnagrams("cde", "abc") << endl;
	return 0;
    cout << anagram("fdhlvosfpafhalll") << endl;
    cout << anagram("aaabbb") << endl;
    cout << anagram("ab") << endl;
    cout << anagram("abc") << endl;
    cout << anagram("mnop") << endl;
    cout << anagram("xyyx") << endl;
    cout << anagram("xaxbbbxx") << endl;
	return 0;
    cout << theLoveLetterMystery("abc") << endl;
    cout << theLoveLetterMystery("abcba") << endl;
    cout << theLoveLetterMystery("abcd") << endl;
    cout << theLoveLetterMystery("cba") << endl;
	return 0;
    cout << beautifulBinaryString("0101010") << endl;
    cout << beautifulBinaryString("01100") << endl;
    cout << beautifulBinaryString("0100101010") << endl;
	return 0;
    cout << alternatingCharacters("AAAA") << endl;
    cout << alternatingCharacters("BBBBB") << endl;
    cout << alternatingCharacters("ABABABAB") << endl;
    cout << alternatingCharacters("BABABA") << endl;
    cout << alternatingCharacters("AAABBB") << endl;
	return 0;
	gemstones({"abcdde", "baccd", "eeabg"});
	return 0;

    cout << funnyString("lmnop") << endl;
    cout << funnyString("lmnopq") << endl;
    cout << funnyString("acxz") << endl;
    cout << funnyString("bcxz") << endl;
    cout << funnyString("asdfasdffdsafdsa") << endl;
	return 0;

	auto result = weightedUniformStrings("abccddde", {1,3,12,5,9,10});
	printVector("Queries", result);
	return 0;

    separateNumbersV2("123412351238123412351239");
    separateNumbers("78798081828384858687888990919293");
    separateNumbers("1234");
    separateNumbers("91011");
    separateNumbers("99100");
    separateNumbers("101103");
    separateNumbers("010203");
    separateNumbers("13");
    separateNumbers("1");
    return 0;
    //separateNumbers("90071992547409929007199254740993");
    separateNumbers("45035996273704964503599627370497");
    return 0;
    separateNumbers("010203");
    separateNumbers("10203");
    separateNumbers("91011");
    separateNumbers("99100");
    separateNumbers("101103");
    separateNumbers("010203");
    separateNumbers("13");
    separateNumbers("1");
    printf("Extra tests:\n");
    separateNumbers("99100101102");
    separateNumbers("99910001001");
    separateNumbers("7891011");
    separateNumbers("9899100");
    separateNumbers("999100010001");
	return 0;

	cout << pangrams("The quick brown fox jumps over the lazy dog");
	return 0;

	cout << hackerrankInString("rhbaasdndfsdskgbfefdbrsdfhuyatrjtcrtyytktjjt") << endl;
	return 0;

    cout << marsExploration("SOSSPSSQSSOR") << endl;
    cout << marsExploration("SOSSOT") << endl;
    cout << marsExploration("SOSSOSSOS") << endl;
	return 0;
	cout << caesarCipher("abcDefghIjklMnopQrstUvwxyZ", 3) << endl;
	return 0;
	cout << alternate("ascbsdcagfsdbgdfanfghbsfdab") << endl;
    cout << alternate("cwomzxmuelmangtosqkgfdqvkzdnxerhravxndvomhbokqmvsfcaddgxgwtpgpqrmeoxvkkjunkbjeyteccpugbkvhljxsshpoymkryydtmfhaogepvbwmypeiqumcibjskmsrpllgbvc") << endl;
    cout << alternate("beabeefeabaffb") << endl;
	return 0;

	cout << camelcase("saveChangesInTheEditor") << endl;
	return 0;

    superReducedString("aab");
    superReducedString("abba");
    superReducedString("aaabccddd");
    superReducedString("aa");
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
