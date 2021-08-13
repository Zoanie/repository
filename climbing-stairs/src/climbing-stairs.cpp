//============================================================================
// Name        : climbing-stairs.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://leetcode.com/problems/climbing-stairs/
//============================================================================

#include <iostream>
#include <unordered_map>

using namespace std;

/*
 * Climbing Stairs
 *
You are climbing a stair case. It takes n steps to reach to the top.
Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

Example 1:
Input: 2
Output: 2
Explanation: There are two ways to climb to the top.
1. 1 step + 1 step
2. 2 steps

Example 2:
Input: 3
Output: 3
Explanation: There are three ways to climb to the top.
1. 1 step + 1 step + 1 step
2. 1 step + 2 steps
3. 2 steps + 1 step

Constraints:
1 <= n <= 45
 */

class Solution {
	unordered_map<int, int> steps_cache;

public:
    int climbStairs(int n) {
    	if(n <= 3) {
    		return n;
    	}
    	else {
    		auto cached = steps_cache.find(n);
    		if(cached != end(steps_cache)) {
    			return cached->second;
    		}
    		else {
    	    	int result = climbStairs(n-1) + climbStairs(n-2);
    			steps_cache.emplace(n, result);
    	    	return result;
    		}
    	}
    }
};

int main() {
	cout << "https://leetcode.com/problems/climbing-stairs/" << endl;
	Solution CS;
	int stairs = 11;
	int result = CS.climbStairs(stairs);
	cout << "Ways to climb " << stairs << " stairs is " << result << endl;
	return 0;
}
