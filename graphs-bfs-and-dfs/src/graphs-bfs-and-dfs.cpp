//============================================================================
// Name        : graphs-bfs-and-dfs.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://www.udemy.com/course/datastructurescncpp/learn/lecture/13193676
//============================================================================

#include <iostream>
#include <stack>
#include <queue>
#include <vector>

using namespace std;

/*
 * Coding Notes:
 *
 * C++ does not allow to pass an entire array as an argument to a function.
 *
 * However, You can pass a pointer to an array by specifying the array's name without an index.
 * There are three ways to pass a 2D array to a function.
 *
 * 1. Specify the size of columns of the 2D array: 		fcn(int a[][8])
 * 2. Pass array containing pointers: 					fcn(int *a[8])
 * 3. Pass a pointer to a pointer:						fcn(int **a)
 *
 * Another way to receive an array of objects is to first initialize a vector with the array elements
 * and then pass the vector.
 *
 *	// using an initializer list to initialize a two-dimensional vector
 *	std::vector<std::vector<int>> matrix {
 *				{ 1, 1, 1, 1 },
 *				{ 1, 1, 1, 1 },
 *				{ 1, 1, 1, 1 }
 *			};
 *
 *  // 2D vector initialized with user defined size n rows X m columns
 *  vector<vector<int> > two_D_vector(n, vector<int>(m));
 *
 *  template<class T>
 *  void printVector(std::vector<std::vector<T>> const &matrix) {
 *  	for (std::vector<T> row: matrix) {
 *  		for (T val: row) {
 *  			std::cout << val << " ";
 *  		}
 *  		std::cout << endl;
 *  	}
 *  }
 *
 *
 * For this Depth-First-Search coding implementation:
 *
 *   o The Vertices are numbered from 1 to n.  The numbering affects the n x n adjacency matrix AdjMatrix[8][8]
 *     to include an unused row 0 and col 0.
 *   o Same reasoning as above applies to use of a 'visited' array.
 */

/*
 * Based on Lecture:
 * Input arguments:
 *   u 		- Adjacency matrix row
 *   A[]    - Adjacency matrix[8][8], with row[0] and col[0] unused to facilitate 1-based vertices numbering
 *   n		- number of vertices
 */
void DFSiteration(int u, bool A[][8], int n) {
    // Initialize visit tracking array and stack
    //bool visited[8] {0};  replacing fixed size variable
    vector<bool> visited(n, false);	// been there done that
    stack<int> stk;
    stk.emplace(u);		// prefer emplace to push - it saves a copy step

    // Visit start vertex u
    cout << u << ", " << flush;
    visited[u] = true;  // Visited vertex u

    // Initial Adjacent vertex
    int v = 0;

    while (!stk.empty()){
        while (v < n){
            if (A[u][v] == true && visited[v] == false){
                stk.push(u); // Suspend exploring current vertex u
                u = v;  // Update current vertex as the next adjacent vertex

                // Visit current vertex u
                cout << u << ", " << flush;
                visited[u] = true;
                v = -1;  // Increment will make this 0
            }
            v++;
        }
        v = u;  // Can set v = 0 but setting v = u is better
        u = stk.top();  // Return to previous suspended vertex
        stk.pop();
    }
}

// Simpler and adds elements to stack from end
void DFSsimpleInteration(int u, bool A[][8], int n){
    //bool visited[8] {0};  replacing fixed size variable
    vector<bool> visited(n, false);	// been there done that
    stack<int> stk;
    stk.emplace(u);

    while (!stk.empty()){
        u = stk.top();
        stk.pop();

        if (visited[u] == false){
            cout << u << ", " << flush;
            visited[u] = true;

            for (int v=n-1; v>=0; v--){
                if (A[u][v] == true && visited[v] == false){
                    stk.emplace(v);
                }
            }
        }
    }
}


void DFSrecursion(int u, bool A[][8], int n){
    // static bool visited[8] {0};
    static vector<bool> visited(n, false);	// been there done that

    if (visited[u] == false){
        cout << u << ", " << flush;
        visited[u] = true;
        // test vertices matrix for presence of a vertex to visit
        for (int v=1; v<n; v++){
            if (A[u][v] == true && visited[v] == false){
            	DFSrecursion(v, A, n);
            }
        }
    }
}

void BFSiteration(int vtx, bool A[][8], int n){
    queue<int> Q;
    vector<bool> visited(n, false);	// been there done that

    // Initial
    cout << vtx << ", " << flush;  // Visit vertex
    visited[vtx] = true;
    Q.emplace(vtx);

    // Explore
    while (!Q.empty()){
        int u = Q.front();  // Vertex u for exploring
        Q.pop();
        // Otherwise a vector of adjacent edges can be visted and marked as well
        for (int v=1; v<n; v++){  // Adjacent vertices of vertex u
            if (A[u][v] == true && visited[v] == false){  // Adjacent vertex and not visited
                cout << v << ", " << flush;  // Visit vertex
                visited[v] = true;
                Q.emplace(v);
            }
        }
    }
    cout << endl;
}

/*
 * 		[1]-------[2]
 * 		 | \       |
 * 		 |   \     |
 * 		 |     \   |
 * 		 |       \ |
 * 		[4]-------[3]
 * 		   \      /
 * 		    \    /
 * 		    [ 5 ]
 * 		    /   \
 * 		   /     \
 * 		 [6]     [7]
 */

int main (){
	cout << "https://www.udemy.com/course/datastructurescncpp/learn/lecture/13193676#notes" << endl;

	// Vertices row 0 and column 0 are not used
    bool AdjMatrix[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
    		         //
                     {0, 		0, 1, 1, 1, 0, 0, 0},
                     {0, 		1, 0, 1, 0, 0, 0, 0},
                     {0, 		1, 1, 0, 1, 1, 0, 0},
                     {0, 		1, 0, 1, 0, 1, 0, 0},
                     {0, 		0, 0, 1, 1, 0, 1, 1},
                     {0, 		0, 0, 0, 0, 1, 0, 0},
                     {0, 		0, 0, 0, 0, 1, 0, 0}};

    // Convert

    int u = 5;
    cout << "DFS iteration Vertex: " << u << " -> " << flush;
    DFSiteration(u, AdjMatrix, 8);
    cout << endl;

    cout << "DFS simplified iteration Vertex: " << u << " -> " << flush;
    DFSsimpleInteration(u, AdjMatrix, 8);
    cout << endl;

    cout << "DFS recursion Vertex: " << u << " -> " << flush;
    DFSrecursion(u, AdjMatrix, 8);
    cout << endl;

    cout << "BFS iteration Vertex: " << u << " -> " << flush;
    BFSiteration(u, AdjMatrix, 8);
    cout << endl;


    return 0;
}
