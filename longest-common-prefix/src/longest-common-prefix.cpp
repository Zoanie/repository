//============================================================================
// Name        : longest-common-prefix.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://leetcode.com/problems/longest-common-prefix/
//============================================================================

#include <bits/stdc++.h>

using namespace std;

/*
 * Longest Common Prefix
 *
Write a function to find the longest common prefix string amongst an array of strings.
If there is no common prefix, return an empty string "".

Example 1:
Input: strs = ["flower","flow","flight"]
Output: "fl"

Example 2:
Input: strs = ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.

Constraints:
0 <= strs.length <= 200
0 <= strs[i].length <= 200
strs[i] consists of only lower-case English letters.

https://leetcode.com/problems/longest-common-prefix/discuss/7322/c-one-small-trick-to-boost-code-from-16ms-to-8ms
	"From observation, the problem need O(MN) time, M is the length of shortest string,
	N is the number of strings. So I first scan all strings, to find the shortest, it
	takes O(N), doesn't hurt. To improve efficiency, a small trick is to put the shortest
	always at the beginning, using swap(). When compare, use the beginning string to
	compare with others.
	BTW: the inspiration of this trick comes from Quick Sort, but not completed from that."
 */

vector<string> TestStr1{"flower","flow","flock", "flog", "floppy", "flood", "florida", "flotsam", "float"};
class Solution1 {
public:
    string longestCommonPrefix(vector<string>& strs)
    {
    	int numstrs = strs.size();
    	if(numstrs == 0) return "";
    	if(numstrs == 1) return strs[0];

    	int prefix_len = 0;
    	auto& base = strs[0];
    	int longest_prefix_len = base.size();

    	for(int idx=1; idx<numstrs; idx++) {
    		auto prefix_pair = mismatch(base.begin(), base.end(), strs[idx].begin());
    		prefix_len = prefix_pair.first - base.begin();
    		//printf("Comparing %s and %s: prefix len = %d chars\n", base.c_str(), strs[idx].c_str(), prefix_len);
    		longest_prefix_len = min(prefix_len, longest_prefix_len);
    	}
    	return base.substr(0, longest_prefix_len);
    }
};

class Solution2 {
public:
    string longestCommonPrefix(vector<string> &strs)
    {
        if (strs.empty()) return "";
        string result;

        string& shortestString = strs[0];
        // initialize the shortest string with the first one
        for (int i = 1; i < (int)strs.size(); ++i)
        {
            if (shortestString.size() > strs[i].size())
            {
                swap(shortestString,strs[i]);
                // always put the shortest string at the beginning, using swap
            }
        }

        int pos = 0;
        while (pos < (int)shortestString.size())
        {
            for (int i = 1; i < (int)strs.size(); ++i)
            {
                if (shortestString[pos] != strs[i][pos]) return result;
            }
            result += shortestString[pos];
            ++pos;
        }
        return result;
    }
};

int main() {
	cout << "https://leetcode.com/problems/longest-common-prefix/" << endl;

	Solution1 LCP;
	auto result = LCP.longestCommonPrefix(TestStr1);
	cout << "Longest common prefix = '" << result << "'" << endl;

	return 0;
}
