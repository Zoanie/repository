//============================================================================
// Name        : palindromic-substrings.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

/*
 * Palindromic Substrings
 *
Given a string, your task is to count how many palindromic substrings in this string.
The substrings with different start indexes or end indexes are counted as different substrings even they consist of same characters.

Example 1:
Input: "abc"
Output: 3
Explanation: Three palindromic strings: "a", "b", "c".

Example 2:
Input: "aaa"
Output: 6
Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".

Note:

The input string length won't exceed 1000.
 */

class Solution {
	int strLen;
	int subStrCount;

public:
    int countSubstrings(string s) {
		strLen = s.length();
		//cout << "Input: s = '" << s << "', strlen = " << strLen << endl;
		if(strLen < 1)
			return 0;
		if (strLen < 2)
			return 1;

		subStrCount = 0;

		for (int i = 0; i < strLen-1; i++) {
			extendPalindrome(s, i, i);	// Odd length count
			extendPalindrome(s, i, i+1); // Even length count
		}
		// Add 1 for last character in string
		return subStrCount+1;
	}

	void extendPalindrome(string s, int j, int k) {
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
		while (j >= 0 && k < strLen && s[j] == s[k]) {
			subStrCount++;
			//printf("\n\ts[%d] == s[%d]", j, k);
			j--;
			k++;
		}
	}
};

int main() {
	cout << "https://leetcode.com/problems/palindromic-substrings/" << endl;
	Solution PS;
	int count = PS.countSubstrings("aaa");
	cout << "\nCount = " << count << endl;
	return 0;
}
