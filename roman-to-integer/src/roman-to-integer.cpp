//============================================================================
// Name        : roman-to-integer.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://leetcode.com/problems/roman-to-integer/
//============================================================================

#include <bits/stdc++.h>
using namespace std;

/*
 * Roman to Integer
 *
Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.

Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
For example, 2 is written as II in Roman numeral, just two one's added together. 12 is written as XII,
which is simply X + II. The number 27 is written as XXVII, which is XX + V + II.

Roman numerals are usually written largest to smallest from left to right. However, the numeral for
four is not IIII. Instead, the number four is written as IV. Because the one is before the five we
subtract it making four. The same principle applies to the number nine, which is written as IX.
There are six instances where subtraction is used:

I can be placed before V (5) and X (10) to make 4 and 9.
X can be placed before L (50) and C (100) to make 40 and 90.
C can be placed before D (500) and M (1000) to make 400 and 900.
Given a Roman numeral, convert it to an integer.

Example 1:
Input: s = "III"
Output: 3

Example 2:
Input: s = "IV"
Output: 4

Example 3:
Input: s = "IX"
Output: 9

Example 4:
Input: s = "LVIII"
Output: 58
Explanation: L = 50, V= 5, III = 3.

Example 5:
Input: s = "MCMXCIV"
Output: 1994
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.

Constraints:
1 <= s.length <= 15
s contains only the characters ('I', 'V', 'X', 'L', 'C', 'D', 'M').
It is guaranteed that s is a valid Roman numeral in the range [1, 3999].

Test data:
"V"
"X"
"L"
"C"
"D"
"M"
"XI"
"III"
"IV"
"VI"
"IX"
"LVIII"
"MCMXCIV"
 */
class Solution {
public:
    int romanToInt(string s) {
    	const int I_index = 'I' - 'A';
    	const int V_index = 'V' - 'A';
    	const int X_index = 'X' - 'A';
    	const int L_index = 'L' - 'A';
    	const int C_index = 'C' - 'A';
    	const int D_index = 'D' - 'A';
    	const int M_index = 'M' - 'A';
    	//cout << "Roman numerals: " << s << endl;
    	vector<int> roman2int(26);
    	roman2int[I_index] = 1;
    	roman2int[V_index] = 5;
    	roman2int[X_index] = 10;
    	roman2int[L_index] = 50;
    	roman2int[C_index] = 100;
    	roman2int[D_index] = 500;
    	roman2int[M_index] = 1000;

    	int slen = s.length();
    	if(slen == 0) return 0;
    	if(slen == 1) return roman2int[s[0] - 'A'];

    	vector<int>numbers(slen);
    	int result = 0;

    	//printf("string length = %d numerals\n", slen);
        for (auto i=0; i < slen; i++) {
            numbers[i] = roman2int[s[i] - 'A'];
        }

        // reading number right to left
        //int curr_num = 0;
        int prev_num = 0;
        for (auto i=slen-1; i >= 0; i--) {
            int curr_num = numbers[i];
            if(curr_num < prev_num) {
            	result -= curr_num;
                //printf("(-)curr_num = %d, result = %d\n", curr_num, result);
            	continue;
            }

            result += curr_num;
            //("(+)curr_num = %d, result = %d\n", curr_num, result);
            prev_num = curr_num;
        }

        printf("final result = %d\n", result);

        return result;
    }
};

int main() {
	cout << "https://leetcode.com/problems/roman-to-integer/" << endl;

	Solution R2I;
	R2I.romanToInt("VI");
	R2I.romanToInt("IV");
	R2I.romanToInt("IX");
	R2I.romanToInt("LVIII");
	R2I.romanToInt("MCMXCIV");
	return 0;
}
