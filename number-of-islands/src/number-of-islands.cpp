//============================================================================
// Name        : number-of-islands.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://leetcode.com/problems/number-of-islands/
//============================================================================

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <boost/multi_array.hpp>

using namespace std;

unordered_map<int, int> fib_cache;

template<class T>
void printVector(vector<vector<T>> const &mat) {
	cout << "2D-Vector:" << endl;
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

//Input:
// char grid1[] =
vector<vector<int> > grid1{
	{1,1,1,1,0},
	{1,1,0,1,0},
	{1,1,0,0,0},
	{0,0,0,0,0}
};
// Output: 1


//Input:
vector<vector<int> > grid2{
	{1,1,0,0,0},
	{1,1,0,0,0},
	{0,0,1,0,0},
	{0,0,0,1,1}
};
// Output: 3

vector<vector<int>> GridStep {
         { 1,  0},		// vertical down, horizontal stay
         {-1,  0},		// vertical up,   horizontal stay
         { 0,  1},		// vertical stay, horizontal right
         { 0, -1}		// vertical stay, horizontal left
};
						 //   -1       0       1
const char* row_step[] = {  "up",   "stay", "down"};
const char* col_step[] = {  "left", "stay", "right"};

class Solution {
public:
	int numIslands(vector<vector<int>>& grid) {
		int nr = grid.size();
		if (!nr) return 0;
		int nc = grid[0].size();

		printVector(grid);
		int num_islands = 0;
		for (int r = 0; r < nr; ++r) {
			for (int c = 0; c < nc; ++c) {
				if (grid[r][c] == 1) {
					++num_islands;
					grid[r][c] = 0; // mark as visited - this is an important point to prevent below test looping back
					queue<pair<int, int>> neighbors;
					neighbors.push({r, c});	// push is the same as push_back which inserts element at end of queue

					while (!neighbors.empty()) {
						auto rc = neighbors.front();
						neighbors.pop();
						int row = rc.first;
						int col = rc.second;

						// check left of grid island, if its valid and still an island, then add to queue
						// GridStep[1]
						if (row - 1 >= 0 && grid[row-1][col] == 1) {
							neighbors.push({row-1, col}); grid[row-1][col] = 0;
						}
						// GridStep[0]
						if (row + 1 < nr && grid[row+1][col] == 1) {
							neighbors.push({row+1, col}); grid[row+1][col] = 0;
						}
						// GridStep[3]
						if (col - 1 >= 0 && grid[row][col-1] == 1) {
							neighbors.push({row, col-1}); grid[row][col-1] = 0;
						}
						// GridStep[2]
						if (col + 1 < nc && grid[row][col+1] == 1) {
							neighbors.push({row, col+1}); grid[row][col+1] = 0;
						}
					}
				}
			}
		}

		return num_islands;
	}

};

/*
 * Approach #2: BFS
 * Algorithm:
 *     Linear scan the 2d grid map, if a node contains a '1', then it is a root node that triggers a Breadth First Search.
 *     Put it into a queue and set its value as '0' to mark as visited node. Iteratively search the neighbors of enqueued
 *     nodes until the queue becomes empty.
 */
class SolutionBFS {
public:
	int num_rows;
	int num_cols;

	SolutionBFS() { num_rows = 0; num_cols = 0; }
	int numIslandsBFS(vector<vector<int>>& grid) {
		int nr = grid.size();
		num_rows = nr;
		if (!nr) return 0;
		int nc = grid[0].size();
		num_cols = nc;

		printVector(grid);
		int num_islands = 0;
		/*
		 * Walk the grid from the top left node 0,0.
		 */
		for (int r = 0; r < num_rows; ++r) {
			for (int c = 0; c < num_cols; ++c) {
				if (grid_node_is_island(grid, r, c)) {
					++num_islands;
					// mark as visited - this is an important point to prevent below test looping back
					set_grid_node_visited(grid, r, c);

					queue<pair<int, int>> neighbors;
					// interesting way to make a pair!
					neighbors.push({r, c});	// push is the same as push_back which inserts element at end of queue

					while (!neighbors.empty()) {
						auto rc = neighbors.front();
						neighbors.pop();
						int row = rc.first;
						int col = rc.second;

						const int step_up = row - 1;
						const int step_down = row + 1;
						const int step_left = col - 1;
						const int step_right = col + 1;

						// check upper grid node, if its valid and still an island, then add to queue
						if (step_up_ok_to_island(grid, row, col)) {
							neighbors.push({step_up, col});
							set_grid_node_visited(grid, step_up, col);
						}
						// check lower grid node, if its valid and still an island, then add to queue
						if (step_down_row_OK(row) && step_down_row_is_island(grid, row, col)) {
							neighbors.push({step_down, col});
							set_grid_node_visited(grid, step_down, col);
						}
						// check left grid node, if its valid and still an island, then add to queue
						if (step_left_ok_to_island(grid, row, col)) {
							neighbors.push({row, step_left});
							set_grid_node_visited(grid, row, step_left);
						}
						// check right grid node, if its valid and still an island, then add to queue
						if (step_right_ok_to_island(grid, row, col)) {
							neighbors.push({row, step_right});
							set_grid_node_visited(grid, row, step_right);
						}
					}
				}
			}
		}

		return num_islands;
	}

	bool step_up_row_OK(int row) { return (row - 1 >= 0); }
	bool step_down_row_OK(int row) { return (row + 1 < num_rows); }
	bool step_left_col_OK(int col) { return (col - 1 >= 0); }
	bool step_right_col_OK(int col) { return (col + 1 < num_cols);  }

	bool step_up_row_is_island(vector<vector<int>>& grid, int row, int col) { return (grid[row-1][col] == 1); }
	bool step_down_row_is_island(vector<vector<int>>& grid, int row, int col) { return (grid[row+1][col] == 1); }
	bool step_left_col_is_island(vector<vector<int>>& grid, int row, int col) { return (grid[row][col-1] == 1); }
	bool step_right_col_is_island(vector<vector<int>>& grid, int row, int col) { return (grid[row][col+1] == 1); }

	bool step_up_ok_to_island(vector<vector<int>>& grid, int row, int col) {
		return ( step_up_row_OK(row) && step_up_row_is_island(grid, row, col) );
	}
	bool step_down_ok_to_island(vector<vector<int>>& grid, int row, int col) {
		return ( step_down_row_OK(row) && step_down_row_is_island(grid, row, col) );
	}
	bool step_left_ok_to_island(vector<vector<int>>& grid, int row, int col) {
		return( step_left_col_OK(row) && step_left_col_is_island(grid, row, col) );
	}
	bool step_right_ok_to_island(vector<vector<int>>& grid, int row, int col) {
		return( step_right_col_OK(row) && step_right_col_is_island(grid, row, col) );
	}

	bool grid_node_is_island(vector<vector<int>>& grid, int row, int col) { return (grid[row][col] == 1); }

	void set_grid_node_visited(vector<vector<int>>& grid, int row, int col) { grid[row][col] = 0; }
};


class SolutionDFS {
private:
	int num_rows;
	int num_cols;
	int num_islands;

	void dfs(vector<vector<int>>& grid, int row, int col) {
		set_grid_node_visited(grid, row, col);
		if (step_up_ok_to_island(grid, row, col)) dfs(grid, row - 1, col);
		if (step_down_ok_to_island(grid, row, col)) dfs(grid, row + 1, col);
		if (step_left_ok_to_island(grid, row, col)) dfs(grid, row, col - 1);
		if (step_right_ok_to_island(grid, row, col)) dfs(grid, row, col + 1);
	}

	bool step_up_row_OK(int row) { return (row - 1 >= 0); }
	bool step_down_row_OK(int row) { return (row + 1 < num_rows); }
	bool step_left_col_OK(int col) { return (col - 1 >= 0); }
	bool step_right_col_OK(int col) { return (col + 1 < num_cols);  }

	bool step_up_row_is_island(vector<vector<int>>& grid, int row, int col) { return (grid[row-1][col] == 1); }
	bool step_down_row_is_island(vector<vector<int>>& grid, int row, int col) { return (grid[row+1][col] == 1); }
	bool step_left_col_is_island(vector<vector<int>>& grid, int row, int col) { return (grid[row][col-1] == 1); }
	bool step_right_col_is_island(vector<vector<int>>& grid, int row, int col) { return (grid[row][col+1] == 1); }

	bool step_up_ok_to_island(vector<vector<int>>& grid, int row, int col) {
		return ( step_up_row_OK(row) && step_up_row_is_island(grid, row, col) );
	}
	bool step_down_ok_to_island(vector<vector<int>>& grid, int row, int col) {
		return ( step_down_row_OK(row) && step_down_row_is_island(grid, row, col) );
	}
	bool step_left_ok_to_island(vector<vector<int>>& grid, int row, int col) {
		return( step_left_col_OK(row) && step_left_col_is_island(grid, row, col) );
	}
	bool step_right_ok_to_island(vector<vector<int>>& grid, int row, int col) {
		return( step_right_col_OK(row) && step_right_col_is_island(grid, row, col) );
	}

	bool grid_node_is_island(vector<vector<int>>& grid, int row, int col) { return (grid[row][col] == 1); }

	void set_grid_node_visited(vector<vector<int>>& grid, int row, int col) { grid[row][col] = 0; }

public:
	SolutionDFS() { num_rows = 0; num_cols = 0; num_islands = 0; }

	int numIslandsDFS(vector<vector<int>>& grid) {
		num_rows = grid.size();
		if (!num_rows) return 0;
		num_cols = grid[0].size();

		num_islands = 0;
		for (int row = 0; row < num_rows; ++row) {
			for (int col = 0; col < num_cols; ++col) {
				if (grid_node_is_island(grid, row, col)) {
					++num_islands;
					dfs(grid, row, col);
				}
			}
		}

		return num_islands;
	}
};

int main() {
	cout << "https://leetcode.com/problems/number-of-islands/" << endl;
	int islands = 0;
	// ONLY ONE SOLUTION CAN RUN AT A TIME.  IT CLEARS THE GRID.
	vector<vector<int>>& grid = grid2;

//	Solution NumberOfIslands;
//	islands = NumberOfIslands.numIslands(grid);
//	cout << "Number of islands found by original code is " << islands << endl;

//	cout << "2D-Directions:" << endl;
//	cout << "[" << endl;
//	for( auto& dir : GridDirections) {
//		cout << "  [ ";
//		for( auto& val : dir) {
//			cout << val << " ";
//		}
//		cout << "]" << endl;
//	}
//	cout << "]" << endl;

	SolutionBFS NumberOfIslandsBFS;
	islands = NumberOfIslandsBFS.numIslandsBFS(grid);
	cout << "Number of islands found by BFS is " << islands << endl;

//	SolutionDFS NumberOfIslandsDFS;
//	islands = NumberOfIslandsDFS.numIslandsDFS(grid);
//	cout << "Number of islands found by DFS is " << islands << endl;



	return 0;
}
