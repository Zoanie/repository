//============================================================================
// Name        : merge-intervals.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://leetcode.com/problems/merge-intervals/
//============================================================================

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>

using namespace std;

/*
Given a collection of intervals, merge all overlapping intervals.

Example 1:

Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].
Example 2:

Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.

Constraints:

intervals[i][0] <= intervals[i][1]

*/
template<class T>
void printMatrix(vector<vector<T>> const &mat) {
	cout << "Matrix:" << endl;
	cout << "[" << endl;
	for (vector<T> row: mat) {
		cout << "  [ ";
		for (T val: row) {
			cout << val << " ";
		}
		cout << "]" << endl;
	}
	cout << "]" << endl;
}

template<class T>
void printVector(vector<T> const &vec) {
	cout << "Vector:" << endl;
	cout << "  [ ";
	for (T val: vec) {
		cout << val << " ";
	}
	cout << "]" << endl;
}

/*
 * Solution from user sacerdoti:
 *
class Solution {
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        if (intervals.size() <= 1) return intervals;
        sort(intervals.begin(), intervals.end(), [](Interval& a, Interval& b) {
            return a.start < b.start;
        });
        vector<Interval> ret;
        ret.push_back( move(intervals[0]) );
        for (int i=1; i<intervals.size(); i++) {
            if (intervals[i].start > ret.back().end) {       // new
                ret.push_back( move(intervals[i]) );
            }
            else                                             // merge
                ret.back().end = max(ret.back().end, intervals[i].end);
        }
        return ret;
    }
};
 */
class Solution {
public:
    static bool comp(vector<int> &a, vector<int> &b)
    {
        return (a[0]<b[0]);
    }
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> ans;
        int num_intervals = intervals.size();
        if(num_intervals)
            return ans;
        sort(intervals.begin(),intervals.end(), comp);
        ans.push_back(intervals[0]);
        int index =0;

        for(int i=1; i<num_intervals; i++)
        {
            if(ans[index][1]<intervals[i][0])
            {
                // No merge required, simply push back the interval
                ans.push_back(intervals[i]);
                index++;
            }
            else{
                // merge the interval
                // resolve tricky problem that end of first interval is greater than
                // end of next interval
                ans[index][1] = max(ans[index][1],intervals[i][1]);
            }
        }
        return ans;
    }
};

vector<int> productExceptSelf(vector<int>& nums) {

    int num_elems = nums.size();
    vector<int> vout(num_elems, 1);

    for(int i=0; i<num_elems; i++) {
        swap(vout[i], nums[i]);
        /*
        int sum = accumulate(begin(nums), end(nums), 1,
        		[](int sum, int elem) { return sum * elem; });
        */
        int sum = 1;
        int elem = 1;
        int sign = 1;
        for(int j=0; j<num_elems; j++) {
        	elem = nums[j];
        	if(elem == (-1))
        	{
        		sign ^= 1;
        		continue;
        	}
        	if(elem == 1)
        	{
        		continue;
        	}
        	sum = sum * elem;
        }

        swap(vout[i], nums[i]);
        vout[i] = sum * sign;
    }

    return vout;

}

vector<vector<int> > Interval1 {
	{1,3},
	{2,6},
	{8,10},
	{15,18}
};

vector<vector<int> > Interval2 {
	{1,3},
	{2,6},
	{8,10},
	{15,18}
};

vector<int> vin{1,2,3,4};

int main() {
	cout << "https://leetcode.com/problems/merge-intervals/" << endl;

	Solution mi;
	//vector<vector<int>>& ref_interval = Interval1;
	auto resultMatrix = mi.merge(Interval2);
	printMatrix(resultMatrix);

	return 0;

	auto vout = productExceptSelf(vin);
	printf("Vout=[");
	int vsize = vout.size();
	for(int i=0; i<vsize; i++) {
		printf("%d ", vout[i]);
	}
	printf("]");


	return 0;
}
