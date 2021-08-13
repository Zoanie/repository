//============================================================================
// Name        : longest-substring-wo-repeating.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <unordered_map>

/*
 *
Given a string s, find the length of the longest substring without repeating characters.

Example 1:
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.

Example 2:
Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

Example 3:
Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.

Example 4:
Input: s = ""
Output: 0

Constraints:

0 <= s.length <= 5 * 104
s consists of English letters, digits, symbols and spaces.
 */

using namespace std;

class Solution {

// using sliding window protocol with storing last occurrence of chars

public:
    int lengthOfLongestSubstring(string s) {

    	// Map of a character key and it's last index
        unordered_map<char, int> last_occurence;
        int left = -1, max_len = 0;
        int slen = s.length();

        for(int right = 0; right<slen; right++){

            // if it has occurred within our window
            if(last_occurence.find(s[right]) != last_occurence.end() &&
               last_occurence[s[right]] > left) {
                left = last_occurence[s[right]];
            	//printf("left = lo[ s[%d]='%c' ] = %d\n", right, s[right], left);
            }
            max_len = max((right - left),  max_len);

            last_occurence[s[right]] = right;
        	//printf("lo[ s[%d]='%c' ] = %d\n", right, s[right], right);
        }

        for(auto it=last_occurence.begin(); it!=last_occurence.end(); ++it) {
        	//printf("'%c' : %d\n", it->first, it->second);
        }

        return max_len;
    }

    int lolsUsingFreqMap(string s) {
        unordered_map<char, int> freqMap;
    	int left = 0;
    	int right = 0;
        int slen = s.length();
        int max_len = 0;

    	while(right < slen) {
    		char right_key = s[right++];
    		freqMap[right_key] += 1;

    		// check if the key we just added is already in our longest string
            if(freqMap.find(right_key) != freqMap.end())
            {
        		bool duplicate = false;
            	do {
            		if(freqMap[right_key] > 1)
            		{
            			// drop left char out of our longest string sliding window
            			char left_key = s[left++];
            			freqMap[left_key] -= 1;
            			duplicate = true;
            		}
            		else
            		{
            			duplicate = false;
            		}
            	} while(duplicate);
            }
            max_len = max((right - left),  max_len);
    	}
    	return max_len;
    }
};


int main() {
	cout << "https://leetcode.com/problems/longest-substring-without-repeating-characters/" << endl;
	Solution LS;

	string case1 = "abcabcbb";
	cout << "lsIdxTest = " << LS.lengthOfLongestSubstring(case1) << endl;
	cout << "lsFrqTest = " << LS.lolsUsingFreqMap(case1) << endl;
	//string case2 = "pwwkew";
	//string case3 = "bbbbb";
	return 0;
}
