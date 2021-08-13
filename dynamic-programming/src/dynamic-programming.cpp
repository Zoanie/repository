//============================================================================
// Name        : dynamic-programming.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://leetcode.com/explore/interview/card/top-interview-questions-easy/97/dynamic-programming/
//============================================================================

#include <iostream>
#include <bits/stdc++.h>
#include <numeric>	// partial_sum, accumulate
using namespace std;
using namespace std::chrono;

template<class T>
void printVector(vector<T> const &vec) {
	cout << "Vector:" << endl;
	cout << "  [ ";
	for (T val: vec) {
		cout << val << " ";
	}
	cout << "]" << endl;
}

// https://leetcode.com/problems/climbing-stairs/
class ClimbingStairsSolutionI {
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

class ClimbingStairsSolutionII {
	int steps_cache[46] = {0};

public:
    int climbStairs(int n) {
    	if(n <= 3) {
    		return n;
    	}
    	else {
    		auto cached = steps_cache[n];
    		if(cached != 0) {
    			return cached;
    		}
    		else {
    	    	int result = climbStairs(n-1) + climbStairs(n-2);
    			steps_cache[n] = result;
    	    	return result;
    		}
    	}
    }
};

/*
 * Maximum Subarray
 *
Given an integer array nums, find the contiguous subarray (containing at least one number)
which has the largest sum and return its sum.

Follow up: If you have figured out the O(n) solution, try coding another solution using
the divide and conquer approach, which is more subtle.


Example 1:
Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.

Example 2:
Input: nums = [1]
Output: 1

Example 3:
Input: nums = [0]
Output: 0

Example 4:
Input: nums = [-1]
Output: -1

Example 5:
Input: nums = [-2147483647]
Output: -2147483647

Constraints:
1 <= nums.length <= 2 * 104
-231 <= nums[i] <= 231 - 1

Test cases:
[-1,-1,-1,2,2,1,-2,-2,-2,2,2,2,-1,-1,-1]
[-2,1,-3,4,-1,2,1,-5,4]
 */
class MaxSubarraySolution {

public:
    int maxSubArray(vector<int>& nums) {
        // 1 <= nums.length <= 2 * 104, therefore no need to check for empty nums
    	int numlen = nums.size();
    	int max_sum = accumulate(begin(nums), end(nums), 0,
    			[](int total, int elem) {if(elem > 0) return total+elem; return total;});

    	// queues
    	queue<int> curr_sequence;
    	curr_sequence.emplace(nums[0]);
    	queue<int> max_sequence(curr_sequence);

        // vectors
        vector<int> curr_elems(nums[0]);
        vector<int> max_elems(nums[0]);

    	printVector(nums);
    	printf("Adding %d to curr_sequence\n", nums[0]);

    	int max_subarray_sum = nums[0];
    	int prev_subarray_sum = nums[0];

        printf("nums[0] = %d: numlen = %d, prev_sum = max_sum = %d\n", nums[0], numlen, max_subarray_sum);
    	for(int i=1; i<numlen; i++) {
    		int num = nums[i];
            printf("num[%d] = %d\n", i, num);
       		int curr_subarray_sum = max(prev_subarray_sum + num, num);

       		int curr_test = prev_subarray_sum + num;
            if(curr_test > num)
            {
            		printf("Adding %d to curr_sequence\n", num);
            		curr_sequence.emplace(num);
                    // using a vector
                    curr_elems.push_back(num);
            }
            else {
            	printf("Restarting curr_sequence with %d\n", num);
            	queue<int> empty;
            	swap(curr_sequence, empty);
            	curr_sequence.emplace(num);

                // using a vector is similar, but perhaps faster
                curr_elems.clear();
                curr_elems.emplace_back(num);
            }

            //printf("num[%d] = %d: curr_sum = max(%d + %d OR %d)\n", i, num, prev_subarray_sum, num, num);
            //printf("    max_sum = max(%d OR %d)", max_subarray_sum, curr_subarray_sum);

            if(curr_subarray_sum > max_subarray_sum) {
            	printf("Setting new max sequence\n");
            	queue<int> tempq(curr_sequence);
            	max_sequence.swap(tempq);
                // using a vector...is much easier
                max_elems = curr_elems;
            }
            max_subarray_sum = max(max_subarray_sum, curr_subarray_sum);
            //printf(" = %d\n", max_subarray_sum);

            prev_subarray_sum = curr_subarray_sum;
            //printf("    prev_sum = curr_sum = %d\n", curr_subarray_sum);
    	}

        printf("max_subarray_sum = %d\n", max_subarray_sum);
    	cout << "max_sequence[] = {";
        while(!max_sequence.empty()) {
        	cout << max_sequence.front();
        	max_sequence.pop();
        	if(!max_sequence.empty()) {
        		cout << ", ";
        	}
        }
        cout << "}" << endl;
    	return max_subarray_sum;
    }

};

/*
 * House Robber
 *
You are a professional robber planning to rob houses along a street. Each house has a certain
amount of money stashed, the only constraint stopping you from robbing each of them is that
adjacent houses have security system connected and it will automatically contact the police
if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing the amount of money of each house, determine
the maximum amount of money you can rob tonight without alerting the police.

Example 1:
Input: nums = [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
             Total amount you can rob = 1 + 3 = 4.

Example 2:
Input: nums = [2,7,9,3,1]
Output: 12
Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
             Total amount you can rob = 2 + 9 + 1 = 12.

Constraints:
0 <= nums.length <= 100
0 <= nums[i] <= 400

Testcases:
[1,2,3,1]
[2,7,9,3,1]
 */
class Solution {
public:
    int rob(vector<int>& nums) {
    	int nums_len = nums.size();
    	// 1 more than size to be able to use previous amount for nums[0]
    	vector<int> max_amt(nums_len + 1);
    	max_amt[0] = 0;
    	max_amt[1] = nums[0];
    	for(int i=1; i<nums_len; i++) {
    		int curr_house = nums[i];
    		max_amt[i+1] = max(max_amt[i], max_amt[i-1] + curr_house);
    	}
    	return max_amt[nums_len];
    }
};
int main() {
	cout << "https://leetcode.com/explore/interview/card/top-interview-questions-easy/97/dynamic-programming/" << endl; 
	cout << "https://leetcode.com/problems/maximum-subarray/" << endl;
	MaxSubarraySolution MSS;
	vector<int> numsvec{-2,1,-3,4,-1,2,1,-5,4};
	//vector<int> numsvec{-2,-1};
	//vector<int> numsvec{1,2};
	//vector<int> numsvec{1,2,3,-1,-2,-3};
	MSS.maxSubArray(numsvec);
	return 0;

	cout << "https://leetcode.com/problems/climbing-stairs/" << endl;
	ClimbingStairsSolutionI CS1;
	int stairs = 45;
	auto start = high_resolution_clock::now();
	int result = CS1.climbStairs(stairs);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	cout << "V1 Ways to climb " << stairs << " stairs is " << result << endl;
	cout << "V1 timing is " << duration.count() << " microseconds" << endl;

	ClimbingStairsSolutionII CS2;
	start = high_resolution_clock::now();
	result = CS2.climbStairs(stairs);
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);

	cout << "V2 Ways to climb " << stairs << " stairs is " << result << endl;
	cout << "V2 timing is " << duration.count() << " microseconds" << endl;

	return 0;
}
