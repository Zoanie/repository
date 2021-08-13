//============================================================================
// Name        : first_and_last_elem.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/
//============================================================================
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

/*
 * Results from leetcode.com:
 * Success
 * Details
 * Runtime: 16 ms, faster than 90.97% of C++ online submissions for Find First and Last Position of Element in Sorted Array.
 * Memory Usage: 13.9 MB, less than 46.37% of C++ online submissions for Find First and Last Position of Element in Sorted Array.
 */
class Solution {
public:
	vector<int> searchRange(vector<int>& nums, int target) {
		vector<int> search_result{-1, -1};
		if(nums.size() == 0) {
			return search_result;
		}
		else {
			int needle[] = {target, target};
			/*
			 * A bit of testing here.  How many ways can this problem be solved?
			 */
			// find the starting position with a forward iterator using search_n
			auto it=search_n(begin(nums), end(nums), 2, target);
			if (it!=end(nums)) {
				cout << "search_n finds first match is: " << (it - begin(nums)) << endl;

				// find the end position with a reverse iterator using search_n
				auto rit=search_n(rbegin(nums), rend(nums), 2, target);
		        auto idx = distance(begin(nums), rit.base()) - 1;
				cout << "reverse search_n finds end match is: " << (idx) << endl;
			}

			it = find_first_of (begin(nums), end(nums), needle, needle+1);
			if (it!=end(nums)) {
				cout << "find_first_of finds first match index is: " << (it - begin(nums)) << endl;
				search_result[0] = (it - begin(nums));
				it = find_end(it, end(nums), needle, needle+1);
				if (it!=end(nums)) {
					cout << "find_end finds end match index is: " << (it - begin(nums)) << endl;
					search_result[1] = (it - begin(nums));
				}
			}

		}
		return search_result;
	}
};

int main() {
    vector<int> nums{5,7,7,8,8,8,8,10,1,2,3,4,5,};
    int const target1 = 8;
    //int const target2 = 6;

    Solution FindFirstAndLast;

    vector<int> result = FindFirstAndLast.searchRange(nums, target1);

    cout << "Output[" << flush;
    auto num_idxs = result.size();
    for(auto& pos_idx : result) {

        cout << pos_idx;
        if(--num_idxs > 0)
        {
        	cout << ",";
        }
    }
    cout << "]" << endl;
    return 0;
}
