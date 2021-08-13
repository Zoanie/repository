//============================================================================
// Name        : two-sum.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://leetcode.com/problems/two-sum/
//============================================================================

#include <iostream>
#include <map>
#include <vector>

using namespace std;

/*
 * Two Sum
 *
Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
You may assume that each input would have exactly one solution, and you may not use the same element twice.
You can return the answer in any order.

Example 1:
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Output: Because nums[0] + nums[1] == 9, we return [0, 1].

Example 2:
Input: nums = [3,2,4], target = 6
Output: [1,2]

Example 3:
Input: nums = [3,3], target = 6
Output: [0,1]
 */

class Solution {
	map<int, int> numIdxMap;

public:
    vector<int> twoSum(vector<int>& nums, int target) {
    	vector<int> result(0,0);

    	if(nums.size() == 0)
    		return nums;

    	int diff = 0;
    	int idx = 0;

    	for(auto& num : nums) {
    		if(0 == idx) {
        		numIdxMap.emplace(make_pair(num, idx));
//        		cout << "map data: key = " << num << ", idx = " << idx << endl;
    		}
    		else {
        		diff = target - num;
//        		cout << "diff = " << diff << " = " << target << " - " << num << endl;
        		auto it = numIdxMap.find(diff);
            	if(it != end(numIdxMap))
        		{
//            		cout << "found diff in database index " << idx << endl;
        			result.push_back(it->second);
        			result.push_back(idx);
        			return result;
        		}
        		numIdxMap.emplace(make_pair(num, idx));
//        		cout << "map data: key = " << num << ", idx = " << idx << endl;
    		}
			idx++;
    	}
    	return result;
    }
};

int main() {
	cout << "https://leetcode.com/problems/two-sum/" << endl; // prints https://leetcode.com/problems/two-sum/
	//vector<int> nums =  {2,7,11,15};
	vector<int> nums =  {3,2,4};
	int target = 6;

	Solution TwoSumProblem;
	vector<int> result;
	cout << "Input: [";
	for(auto& num : nums) {
		cout << num << ",";
	}
	cout << "]" << endl;

	result = TwoSumProblem.twoSum(nums, target);

	cout << "Output: [";
	for(auto& num : result) {
		cout << num << ",";
	}
	cout << "]" << endl;


	return 0;
}
