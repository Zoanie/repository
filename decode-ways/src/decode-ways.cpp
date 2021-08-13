//============================================================================
// Name        : decode-ways.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>

using namespace std;

/*
 * Decode Ways
 *
A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given a non-empty string containing only digits, determine the total number of ways to decode it.
The answer is guaranteed to fit in a 32-bit integer.

Example 1:
Input: s = "12"
Output: 2
Explanation: It could be decoded as "AB" (1 2) or "L" (12).

Example 2:
Input: s = "226"
Output: 3
Explanation: It could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).

Example 3:
Input: s = "0"
Output: 0
Explanation: There is no character that is mapped to a number starting with '0'.
We cannot ignore a zero when we face it while decoding. So, each '0' should be part of "10" --> 'J' or "20" --> 'T'.

Example 4:
Input: s = "1"
Output: 1

Constraints:

1 <= s.length <= 100
s contains only digits and may contain leading zero(s).
 */

/*
 * 1-char letters: A=1, B=2, C=3,....I=9,
 * 2-char letters: J=10, K=11, L=12,...Z=26
 *
 * s="226" = [0x32, 0x32, 0x36]
 * s2num1 = s[0] - 0x30;
 * 		  = 0x32 - 0x30 = 0x02;
 * char1 = s2num1 + 0x40 = 0x02 + 0x40 = 0x42 = 'B';
 *
 * s2num2 = s[1] - 0x30;
 * 		  = 0x32 - 0x30 = 0x02;
 * char2 = (s2num1 * 10) + s2num2 + 0x40
 *       = 0x14 + 2 + 0x40 = 0x16 + 0x40 = 0x56 = 'V'
 */
class Solution {
	//unordered_map<pair<int,int>, int> cached_paths;

public:
	int numDecodings(string s) {
		int len = s.length();
		printf("numDecodings: s='%s', len=%d\n", s.c_str(), len);
		vector<int> dp(len+1);
		dp[len] = 1;
		// iterate from end(s) to begin(s)
		for(int i=len-1;i>=0;i--) {
			printf("i=%d:\n", i);
			if(s[i]=='0') {
				// zero by itself is not a valid translation.  Only if paired with 1 or 2 for '10' or '20'
				dp[i]=0;
			}
			else {
				dp[i] = dp[i+1];
				printf("dp[%d] = dp[%d] = %d\n", i, i+1, dp[i+1]);
				// testing string elements from 0 to len - 1
				if(i<len-1) {
					// Valid translations are 1 - 26.
					// Which means s[i] == '1'
					if(s[i]=='1'|| (s[i]=='2'&& s[i+1]<'7')) {
						dp[i]+=dp[i+2];
						printf("s[%d]='%c%c' => dp[%d] = %d\n", i, s[i], s[i+1], i, dp[i]);
					}
					else {
						printf("skipping increment: s[%d]='%c%c' => dp[%d] = %d\n", i, s[i], s[i+1], i, dp[i]);
					}
				}
			}
		}
		printf("dp = ");
		for(unsigned i=0; i<dp.size(); i++)
		{
			printf("[%d]", dp[i]);
		}
		printf("\n");
		return s.empty()? 0 : dp[0];
	}
};

int main() {
	cout << "https://leetcode.com/problems/decode-ways/" << endl; // prints https://leetcode.com/problems/decode-ways/

	Solution DW;
	//string testString = "22912";
	string testString = "121";

	int decodeWays = DW.numDecodings(testString);
	cout << "Decode ways = " << decodeWays << endl;

	return 0;
}
