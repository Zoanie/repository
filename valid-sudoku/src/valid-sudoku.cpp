//============================================================================
// Name        : valid-sudoku.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://leetcode.com/problems/valid-sudoku/
//============================================================================

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*
 * Valid Sudoku
 *
Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:

Each row must contain the digits 1-9 without repetition.
Each column must contain the digits 1-9 without repetition.
Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.
Note:

A Sudoku board (partially filled) could be valid but is not necessarily solvable.
Only the filled cells need to be validated according to the mentioned rules.

Example 1:
Input: board =
[["5","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
Output: true

Example 2:
Input: board =
[["8","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
Output: false

Explanation:
Same as Example 1, except with the 5 in the top left corner being modified to 8.
Since there are two 8's in the top left 3x3 sub-box, it is invalid.

Constraints:
board.length == 9
board[i].length == 9
board[i][j] is a digit or '.'.
 */

class Solution {

public:
    bool isValidSudoku(vector<vector<char>>& board) {
		int num_rows = board.size();
		if (!num_rows) return 0;
		int num_cols = board[0].size();

    	bool sub_box_freq_map[3][3][10] = {};

    	for(int i=0; i<num_rows; i++) {
        	vector<bool> row_freq_map(10, 0);
        	vector<bool> col_freq_map(10, 0);

        	for(int j=0; j<num_cols; j++) {

        		// Each row must contain the digits 1-9 without repetition
            	int row_val = board[i][j] - '0';
            	if(row_val > 0) {
					if(row_freq_map[row_val]) {
						//printf("Invalid Sudoku: row[%d] has duplicate %d values\n",
						//		i+1, row_val);
						return false;
					}
					//printf("row[%d][%d]=%d\n", i, j, row_val);
					row_freq_map[row_val] = true;
            	}

        		// Each column must contain the digits 1-9 without repetition
        		int col_val = board[j][i] - '0';
        		if(col_val > 0) {
					if(col_freq_map[col_val]) {
						//printf("Invalid Sudoku: column[%d] has duplicate %d values\n",
						//		j+1, col_val);
						return false;
					}
					col_freq_map[col_val] = true;
					//printf("col[%d][%d]=%d\n", j, i, col_val);
        		}

        		// Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition
        		int sub_box_val = row_val;
        		if(sub_box_val > 0) {
					int sub_box_row = i / 3;
					int sub_box_col = j / 3;
					if(sub_box_freq_map[sub_box_row][sub_box_col][sub_box_val]) {
						//printf("Invalid Sudoku: sub_box[%d][%d] has duplicate %d values\n",
						//		sub_box_row, sub_box_col, sub_box_val);
						return false;
					}
					sub_box_freq_map[sub_box_row][sub_box_col][sub_box_val] = true;
        		}
        	}
    	}

    	return true;
    }
};

vector<vector<char>> SudokoBoard
{
		 {'5','3','.','.','7','.','.','.','.'}
		,{'6','.','.','1','9','5','.','.','.'}
		,{'.','9','8','.','.','.','.','6','.'}
		,{'8','.','.','.','6','.','.','.','3'}
		,{'4','.','.','8','.','3','.','.','1'}
		,{'7','.','.','.','2','.','.','.','6'}
		,{'.','6','.','.','.','.','2','8','.'}
		,{'.','.','.','4','1','9','.','.','5'}
		,{'.','.','.','.','8','.','.','7','9'}
};

int main() {
	cout << "https://leetcode.com/problems/valid-sudoku/" << endl;

	Solution VS;
	printf("Sudoko Board is %s\n", VS.isValidSudoku(SudokoBoard) ? "VALID":"INVALID");
	return 0;
}
