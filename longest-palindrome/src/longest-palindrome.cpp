//============================================================================
// Name        : longest-palindrome.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://leetcode.com/problems/longest-palindromic-substring/
//============================================================================

#include <iostream>
#include <string>

using namespace std;

/*
 * Longest Palindrome
 *
Given a string s, return the longest palindromic substring in s.

Example 1:
Input: s = "babad"
Output: "bab"
Note: "aba" is also a valid answer.

Example 2:
Input: s = "cbbd"
Output: "bb"

Example 3:
Input: s = "a"
Output: "a"

Example 4:
Input: s = "ac"
Output: "a"

Constraints:
1 <= s.length <= 1000
s consist of only digits and English letters (lower-case and/or upper-case),
 */
class Solution {
	int start;
	int maxLen;
	int strLen;

public:
	string longestPalindrome(string s) {
		strLen = s.length();
		cout << "Input: s = '" << s << "', strlen = " << strLen << endl;
		if (strLen < 2)
			return s;

		start = 0;
		maxLen = 0;

		for (int i = 0; i < strLen-1; i++) {
			extendPalindrome(s, i, i);  //assume odd length, try to extend Palindrome as possible
			extendPalindrome(s, i, i+1); //assume even length.
		}
		return s.substr(start, maxLen);
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
		//int len = s.length();
		// This is the key logic to finding palindrome substrings.
		// - The substring remains a palindrome as long as s[j] == s[k]
		// - The substring increases as j is decremented leftward relative to the string position
		//   and k is incremented righward relative to the string position.
		while (j >= 0 && k < strLen && s[j] == s[k]) {
			//printf("\n\ts[%d] == s[%d]", j, k);
			j--;
			k++;
		}
		if (maxLen < k - j - 1) {
			start = j + 1;
			maxLen = k - j - 1;
			//printf("\n\tmaxLen=%d", maxLen);
		}
		//printf("\n");
	}
};

int main() {
	cout << "https://leetcode.com/problems/longest-palindromic-substring/" << endl; // prints https://leetcode.com/problems/longest-palindromic-substring/
	Solution LP;
	string testString = "baLLabad";
	string resultString = LP.longestPalindrome(testString);
	cout << "Longest Palindrome = '" << resultString << "'" << endl;
	return 0;
}
