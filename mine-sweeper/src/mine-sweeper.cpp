//============================================================================
// Name        : mine-sweeper.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://leetcode.com/problems/minesweeper/
//============================================================================

#include <iostream>
#include <vector>

using namespace std;

/*
 *

Let's play the minesweeper game (Wikipedia, online game, http://minesweeperonline.com/)!

You are given a 2D char matrix representing the game board.
	'M' represents an unrevealed mine,
	'E' represents an unrevealed empty square,
	'B' represents a revealed blank square that has no adjacent (above, below, left, right, and all 4 diagonals) mines,
	digit ('1' to '8') represents how many mines are adjacent to this revealed square, and finally
	'X' represents a revealed mine.

Now given the next click position (row and column indices) among all the unrevealed squares
('M' or 'E'), return the board after revealing this position according to the following rules:

	1. If a mine ('M') is revealed, then the game is over - change it to 'X'.
	2. If an empty square ('E') with no adjacent mines is revealed, then change it to revealed
	   blank ('B')and all of its adjacent unrevealed squares should be revealed recursively.
	3. If an empty square ('E') with at least one adjacent mine is revealed, then change it to
	   a digit ('1' to '8') representing the number of adjacent mines. Return the board when no
	   more squares will be revealed.

Example 1:

Input:

[['E', 'E', 'E', 'E', 'E'],
 ['E', 'E', 'M', 'E', 'E'],
 ['E', 'E', 'E', 'E', 'E'],
 ['E', 'E', 'E', 'E', 'E']]

Click : [3,0]

Output:

[['B', '1', 'E', '1', 'B'],
 ['B', '1', 'M', '1', 'B'],
 ['B', '1', '1', '1', 'B'],
 ['B', 'B', 'B', 'B', 'B']]

 Example 2:

Input:

[['B', '1', 'E', '1', 'B'],
 ['B', '1', 'M', '1', 'B'],
 ['B', '1', '1', '1', 'B'],
 ['B', 'B', 'B', 'B', 'B']]

Click : [1,2]

Output:

[['B', '1', 'E', '1', 'B'],
 ['B', '1', 'X', '1', 'B'],
 ['B', '1', '1', '1', 'B'],
 ['B', 'B', 'B', 'B', 'B']]

 Note:

1. The range of the input matrix's height and width is [1,50].
2. The click position will only be an unrevealed square ('M' or 'E'), which also means the input
   board contains at least one clickable square.
3. The input board won't be a stage when game is over (some mines have been revealed).
   For simplicity, not mentioned rules should be ignored in this problem. For example, you don't
   need to reveal all the unrevealed mines when the game is over, consider any cases that you
   will win the game or flag any squares.
 *
 */
class Solution {
	int num_rows = 0;
	int num_cols = 0;
	bool left_tested_OK = false;
	bool right_tested_OK = false;

	inline bool not_clickable(int row, int col) { return (row < 0 || col < 0 || row >= num_rows || col >= num_cols); }
	inline bool not_empty(vector<vector<char>>& board, int row, int col) { return (board[row][col] != 'E'); }
	inline bool step_up_OK(int row) { return (row - 1 >= 0); }
	inline bool step_down_OK(int row) { return (row + 1 < num_rows); }
	inline bool step_left_OK(int col) { return (col - 1 >= 0); }
	inline bool step_right_OK(int col) { return (col + 1 < num_cols);  }
	inline bool step_up_right_OK(int row, int col) { return (step_up_OK(row) && step_right_OK(col)); }
	inline bool step_up_left_OK(int row, int col) { return (step_up_OK(row) && step_left_OK(col)); }
	inline bool step_down_right_OK(int row, int col) { return (step_down_OK(row) && step_right_OK(col)); }
	inline bool step_down_left_OK(int row, int col) { return (step_down_OK(row) && step_left_OK(col)); }
	inline bool foundBomb(vector<vector<char>>& board, int row, int col) {
		return (row>=0 && col>=0 && row<num_rows && col<num_cols && board[row][col]=='M');
	}

	int mineCount(vector<vector<char>>& board, int row, int col) {
		//cout << "mineCount: row=" << row << ", col=" << col << endl;

		int count = 0;	// compiler problem using count += (setup_X_OK(...) && foundBomb(..))
		const int step_left = col - 1;
		const int step_right = col + 1;

		if(step_left_OK(col)) {
			left_tested_OK = true;
			count += foundBomb(board, row, step_left);
		}
		if(step_right_OK(col)) {
			right_tested_OK = true;
			count += foundBomb(board, row, step_right);
		}
		if(step_up_OK(row)) {
			const int step_up = row - 1;
			count += foundBomb(board, step_up, col);
			if(left_tested_OK && step_up_left_OK(row, col)) count += foundBomb(board, step_up, step_left);
			if(right_tested_OK && step_up_right_OK(row, col)) count += foundBomb(board, step_up, step_right);
		}
		if(step_down_OK(row)) {
			const int step_down = row + 1;
			count += foundBomb(board, step_down, col);
			if(left_tested_OK && step_down_left_OK(row, col)) count += foundBomb(board, step_down, step_left);
			if(right_tested_OK && step_down_right_OK(row, col)) count += foundBomb(board, step_down, step_right);
		}
		if(count)
			board[row][col] = '0' + count;
		return count;
	}

	void clickSquare(vector<vector<char>>& board, int row, int col) {
		if(not_clickable(row, col))
			return;
		if(not_empty(board, row, col))
			return;

		left_tested_OK = false;
		right_tested_OK = false;

		if(mineCount(board, row, col))
			return;
		else
			board[row][col] = 'B';

		const int step_left = col - 1;
		const int step_right = col + 1;

		if(left_tested_OK) {
			clickSquare(board, row, step_left);
		}
		if(right_tested_OK) {
			clickSquare(board, row, step_right);
		}
		if(step_up_OK(row)) {
			const int step_up = row - 1;
			clickSquare(board, step_up, col);
			if(left_tested_OK && step_up_left_OK(row, col)) clickSquare(board, step_up, step_left);
			if(right_tested_OK && step_up_right_OK(row, col)) clickSquare(board, step_up, step_right);
		}
		if(step_down_OK(row)) {
			const int step_down = row + 1;
			clickSquare(board, step_down, col);
			if(left_tested_OK && step_down_left_OK(row, col)) clickSquare(board, step_down, step_left);
			if(right_tested_OK && step_down_right_OK(row, col)) clickSquare(board, step_down, step_right);
		}
	}

public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
    	// if click location is a bomb - Gagne - game over!
    	int click_row = click[0];
    	int click_col = click[1];
    	num_rows = board.size();
    	num_cols = board[0].size();

    	if(not_clickable(click_row, click_col)) {
    		return board;
    	}

    	char& click_position = board[click_row][click_col];
    	if(click_position == 'M') {
    		// game over!
    		click_position = 'X';
    	}
    	else {
    		// your move
    		clickSquare(board, click_row, click_col);
    	}

		return board;
    }
};

template<class T>
void printVector(vector<vector<T>> const &mat) {
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

vector<vector<char> > board1{
	{'E','E','E','E','E'},
	{'E','E','M','E','E'},
	{'E','E','E','E','E'},
	{'E','E','E','E','E'}
};

vector<vector<char> > board2{
	{'E','E','E','E','E','E','E','E'},
	{'E','E','E','E','E','E','E','M'},
	{'E','E','M','E','E','E','E','E'},
	{'M','E','E','E','E','E','E','E'},
	{'E','E','E','E','E','E','E','E'},
	{'E','E','E','E','E','E','E','E'},
	{'E','E','E','E','E','E','E','E'},
	{'E','E','M','M','E','E','E','E'}
};

vector<vector<char> > board2_result {
 {'B','B','B','B','B','B','1','E'},
 {'B','1','1','1','B','B','1','M'},
 {'1','2','M','1','B','B','1','1'},
 {'M','2','1','1','B','B','B','B'},
 {'1','1','B','B','B','B','B','B'},
 {'B','B','B','B','B','B','B','B'},
 {'B','1','2','2','1','B','B','B'},
 {'B','1','M','M','1','B','B','B'}
};

vector<int> click1 {0, 0};


int main() {
	cout << "https://leetcode.com/problems/minesweeper/" << endl;
	Solution MS;

	vector<vector<char>>& board = board2;
	vector<int>& click = click1;

	cout << "Before minesweeper" << endl;
	printVector(board);
	MS.updateBoard(board, click);
	cout << "After minesweeper" << endl;
	printVector(board);

	return 0;
}
