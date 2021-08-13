//============================================================================
// Name        : valid-palindrome-II.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://leetcode.com/problems/valid-palindrome-ii/
//============================================================================

#include <iostream>
#include <algorithm>
#include <string>
#include <numeric>
#include<bits/stdc++.h>

using namespace std;

/*
 * Valid Palindrome II
 *
Given a non-empty string s, you may delete at most one character. Judge whether you can make it a palindrome.

Example 1:
Input: "aba"
Output: True

Example 2:
Input: "abca"
Output: True
Explanation: You could delete the character 'c'.

Note:
The string will only contain lowercase characters a-z. The maximum length of the string is 50000.
 */

// https://www.geeksforgeeks.org/remove-character-string-make-palindrome/
// Utility method to check if substring from low to high is
// palindrome or not.
bool isPalindrome(string::iterator low, string::iterator high)
{
    while (low < high)
    {
       if (*low != *high)
          return false;
       low++;
       high--;
    }
    return true;
}

// https://leetcode.com/explore/interview/card/top-interview-questions-easy/127/strings/883/
bool isPalindrome(string s) {
    auto low = s.cbegin();
    auto high = s.cend()-1;

    // Started with: https://www.cplusplus.com/reference/algorithm/reverse/
    while(low < high) {
        while(!isalnum(*low)) {
            if(++low >= high) return true;
        }
        while(!isalnum(*high)) {
            if(--high <= low) return true;
        }
        if(low < high) {
            if(tolower(*low) != tolower(*high))
                return false;
            low++; high--;
        }
    }
    return true;
}
bool isNotAlnum(const char c) { return !isalnum(c); }
// This is another view of the same idea and combining two sources
// https://medium.com/better-programming/algorithms-101-palindromes-8a06ea97af86
// https://stackoverflow.com/questions/6319872/how-to-strip-all-non-alphanumeric-characters-from-a-string-in-c
bool checkPalindrome(string s) {
	  s.erase(std::remove_if(s.begin(), s.end(), isNotAlnum), s.end());

	int slen = s.length();

	for(int i=0; i< slen/2; i++) {
		if(s[i] != s[slen - 1 - i]) {
			return false;
		}
	}
	return true;
}

// https://www.geeksforgeeks.org/remove-character-string-make-palindrome/
// This method returns -1 if it is not possible to make string
// a palindrome. It returns -2 if string is already a palindrome.
// Otherwise it returns index of character whose removal can
// make the whole string palindrome.
int possiblePalinByRemovingOneChar(string str)
{
    //  Initialize low and right by both the ends of the string
    int low = 0, high = str.length() - 1;

    //  loop untill low and high cross each other
    while (low < high)
    {
        // If both characters are equal then move both pointer
        // towards end
        if (str[low] == str[high])
        {
            low++;
            high--;
        }
        else
        {
            /*  If removing str[low] makes the whole string palindrome.
                We basically check if substring str[low+1..high] is
                palindrome or not. */
            if (isPalindrome(str.begin() + low + 1, str.begin() + high))
                return low;

            /*  If removing str[high] makes the whole string palindrome
                We basically check if substring str[low+1..high] is
                palindrome or not. */
            if (isPalindrome(str.begin() + low, str.begin() + high - 1))
                return high;

            return -1;
        }
    }

    //  We reach here when complete string will be palindrome
    //  if complete string is palindrome then return mid character
    return -2;
}

class Solution {
public:
	bool validPalindrome(string s) {
		bool valid = false;
		string rev = string(s.rbegin(), s.rend());
		int strLen = s.length();

		cout<< "str = '" << s << "'" << ", length = " << strLen << endl;

		cout<< "rev = '" << rev << "'" <<endl;

		if(s == rev) {
			valid = true;
			printf("String '%s' is a valid palindrome!", s.c_str());
			return valid;
		}
		int j=0;
		int k=strLen - 1;
		int testIdxCount = 0;
		int testIdx = 0;
		//
		// Case 1:
		//    aabcaa: 		We can delete either s[2]='b' or s[3]='c'
		// Case 2:
		//    abaa:   		We can delete either s[1]='b' or s[2]='a'
		// Case 3:
		//    axbabbaba		We can delete s[1] = x
		// Case 4:
		//    axaa
		// Case 5:
		//    babab
		// Case 6:
		//    abca			We can delete s[1]='b' or s[2]='c'
		// Case 6:
		//    cbbcc			We can delete s[3]='c' or s[4]='c'

		//string::iterator it = s.begin();
		//string::iterator it_rev = rev.begin();

#ifdef TESTING
		auto change = mismatch(begin(s), end(s), begin(rev));
		cout << "Forward Mismatch at: s = " << *(change.first) << endl;
		cout << "Mismatch index = " << change.first - begin(s) << endl;
		// Test skipping from forward string
		auto fwd_offset = change.first - s.end();
		string_view str2 = s.string_view(fwd_offset);
		cout << "Original string = '" << s << "', len = " << s.length() << endl;
		cout << "Offset " << fwd_offset << endl;
		cout << "Forward string =  '" << str2 << "', len = " << str2.length() << endl;

		auto rev_offset = end(rev) - change.second;
		string str3 = rev.substr(rev_offset);
		cout << "Reverse string = '" << str3 << "', len = " << str2.length() << endl;

		auto same = equal(change.first+1, end(s), change.second);
		if(same) {
			cout << "Removing first mismatch char from forward string creates a palindrome" << endl;
			return true;
		}
		else {
			cout << "Removing first char from forward string fails to create palindrome" << endl;
		}
		same = equal(change.first, end(s), change.second+1);
		if(same) {
			cout << "Removing first mismatch char from reverse string creates a palindrome" << endl;
			return true;
		}
		else {
			cout << "Removing first char from reverse string fails to create palindrome" << endl;
		}

		//printf("\nMismatch: '%c'=s[%d] != '%c'=s[%d]", *(change.first[0]), change.first - begin(s), *(change.second[0]), change.second - begin(rev));
		return false;
#endif


		while (j <= k && k >= j) {
			if(s[j] == s[k]) {
				j++;
				k--;
			}
			else
			{
				printf("\nForward test: '%c'=s[%d] != '%c'=s[%d]", s[j], j, s[k], k);
				cout << endl;

				if(++testIdxCount > 1) {
					cout << "\nForward side test has too many chars to delete" << endl;
					break;
				}

				if( ((j+1) <= k) && s[j+1] == s[k])
				{
					printf("\nForward test getting rid of '%c'=s[%d]", s[j], j);
					testIdx = j;
					j++;
				}
				else {
					cout << "\nForward side test failed" << endl;
					testIdxCount++;
					break;
				}
			}
		}

		if(testIdxCount <= 1) {
			return true;
		}

		testIdxCount = 0;
		j=0;
		k=strLen - 1;
		testIdx = 0;

		while (j <= k && k >= j) {
			if(s[j] == s[k]) {
				j++;
				k--;
			}
			else
			{
				printf("\nReverse test: '%c'=s[%d] != '%c'=s[%d]", s[j], j, s[k], k);
				cout << endl;

				if(++testIdxCount > 1) {
					cout << "\nReverse side test has too many chars to delete" << endl;
					break;
				}

				if( ((k-1) >= j) && s[j] == s[k-1]) {
					printf("\nReverse test getting rid of '%c'=s[%d]", s[k], k);
					testIdx = k;
					k--;
				}
				else {
					cout << "\nReverse side test failed" << endl;
					return false;
				}
			}
		}


		if(testIdxCount == 1){
			printf("\nRemoving char '%c' at s[%d] will create palindrome string\n", s[testIdx], testIdx);
			valid = true;
		}
		else {
			printf("\nFinal 2 comparisons incorrect, s[%d] != s[%d] - somethings wrong! \n", s[j], s[k]);
		}

		return valid;
	}
};

int main() {
	cout << "https://leetcode.com/problems/valid-palindrome-ii/" << endl;
	string stest("A man, a plan, a canal: Panama");
	cout << "Testing '" << stest << "' = " << boolalpha << isPalindrome(stest) << endl;
	return 0;

	Solution VP;
	//string test("razysdieftupaukuvjqmjblwulrexmsmrzdfjvwovxxxehqhrx");
	//string test("aguokepatgbnvfqmgmlcupuufxoohdfpgjdmysgvhmvffcnqxjjxqncffvmhvgsymdjgpfdhooxfuupuculmgmqfvnbgtapekouga");
	string test("cbbcc");
	VP.validPalindrome(test);
	return 0;
}
