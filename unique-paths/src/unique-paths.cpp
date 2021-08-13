//============================================================================
// Name        : unique-paths.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://leetcode.com/problems/unique-paths/
//============================================================================

#include <iostream>
#include <unordered_map>
#include <utility>

using namespace std;

/*
 * Unique Paths
 *
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
The robot 'R' can only move either down or right at any point in time. The robot is trying to reach
the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?


Example 1:
(row=m, col=n)
[R][_][_][_][_][_][_]
[_][_][_][_][_][_][_]
[_][_][_][_][_][_][*] Finish (row=1, col=1)

Input: m = 3, n = 7
Output: 28

Example 2:
[R][_]
[_][_]
[_][*]
Input: m = 3, n = 2
Output: 3
Explanation:
From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:
1. Right -> Down -> Down
2. Down -> Down -> Right
3. Down -> Right -> Down

Example 3:
Input: m = 7, n = 3
Output: 28

Example 4:
Input: m = 3, n = 3
Output: 6

Constraints:
1 <= m, n <= 100
It's guaranteed that the answer will be less than or equal to 2 * 10**9.
 */

/*
 * Example 1: m=3, n=7
 *
Example 1:
  - There is only one path to reach the cells in the first row: right->right->...->right
  - The same is valid for the first column, though the path here is down->down-> ...->down
(row=m, col=n)
[R][1][1][1][1][1][1]
[1][T][_][_][_][_][_]
[1][_][_][_][_][_][*] Finish (row=1, col=1)

  -
 */

class Solution {

public:
    int uniquePaths(int m, int n) {
        unsigned int dp[m][n];

        dp[0][0]=1;

        for(int i=1;i<n;i++)
        	dp[0][i]=1;

        for(int row=1;row<m;row++) {
        	dp[row][0] = 1;
            for(int col=1;col<n;col++) {
            	//dp[0][col] = 1;
                dp[row][col]=dp[row-1][col]+dp[row][col-1];
            }
        }

        return dp[m-1][n-1];
    }
};

class TestSolution {
	unordered_map<size_t, int> cached_paths;
	inline size_t make_key_pair(int m, int n) {return (size_t) m << 32 | (unsigned int) n;}
	inline pair<int, int> get_key_pair(size_t key) { return make_pair( key >> 16, key & 0xFFFF); }

public:

	int uniquePaths(int m, int n) {
		int dp[m][n];
		int ways_row_minus1_col = 0;
		int ways_row_col_minus1 = 0;
		int ways_value = 0;

		// dp[0][0]=1;
        for(int i=0;i<n;i++) {
        	dp[0][i]=1;
        	auto key = make_key_pair(0, i);
			cached_paths.emplace(key, 1);
        }
        for(int i=0; i<m; i++) {
			dp[i][0] = 1;
			auto key = make_key_pair(i, 0);
			cached_paths.emplace(key, 1);
        }

		for(int row=1;row<m;row++) {
			//dp[row][0] = 1;
			for(int col=1;col<n;col++) {

				// test for cached key from row-1, col
				auto ways_key = make_key_pair(row-1, col);

				auto cached = cached_paths.find(ways_key);
				if(cached != cached_paths.end()) {
					ways_row_minus1_col = cached->second;
				}
				else {
					ways_row_minus1_col = dp[row-1][col];
					cached_paths.emplace(ways_key, ways_row_minus1_col);
				}

				// test for cached key from row, col-1
				ways_key = make_key_pair(row, col-1);

				cached = cached_paths.find(ways_key);
				if(cached != cached_paths.end()) {
					ways_row_col_minus1 = cached->second;
				}
				else {
					ways_row_col_minus1 = dp[row][col-1];
					cached_paths.emplace(ways_key, ways_row_minus1_col);
				}

				ways_key = make_key_pair(row, col);
				ways_value = ways_row_minus1_col + ways_row_col_minus1;
				cached_paths.emplace(ways_key, ways_value);
				//dp[row][col]=dp[row-1][col]+dp[row][col-1];
				dp[row][col]=ways_value;
			}
		}

		return dp[m-1][n-1];
	}
};

int main() {
	cout << "https://leetcode.com/problems/unique-paths/" << endl; // prints https://leetcode.com/problems/unique-paths/
	Solution UP;
	int rows = 23;
	int cols = 12;
	printf("Base Unique paths for array: %d rows, %d cols = %d\n", rows, cols, UP.uniquePaths(rows, cols));
	TestSolution TUP;
	printf("Test Unique paths for array: %d rows, %d cols = %d\n", rows, cols, TUP.uniquePaths(rows, cols));
	return 0;
}
