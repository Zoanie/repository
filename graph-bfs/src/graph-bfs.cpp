//============================================================================
// Name        : graph-bfs.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://www.programiz.com/dsa/graph-bfs
//============================================================================

#include <iostream>
#include <string>
#include <queue>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

// BFS algorithm in C++
//
// Note: There is a boost library that provides functions to implement BFS:
//       https://www.boost.org/doc/libs/1_74_0/libs/graph/example/bfs-example.cpp
//       https://www.boost.org/doc/libs/1_74_0/libs/graph/doc/breadth_first_search.html
//

using namespace std;

// Secondary way to construct and adjacency list
// https://www.techiedelight.com/breadth-first-search/
struct Edge {
	int src, dest;
};

// Primary way to construct a Graph object
// https://www.programiz.com/dsa/graph-bfs
class Graph {
	int numVertices;
	list<int>* adjList;
	bool* visited;
	list<int> verticeQueue;
	vector<int> pathLength;
	vector<int> parentPath;


public:
	Graph(int vertices);
	void addEdge(int src, int dst);
	void BFS(int startVertex);
	void recursiveBFS();
	void displayAdjList(list<int> adj_list[], int numV);
	void displayAdjList() { if(adjList) { displayAdjList(adjList, numVertices); } }
	bool isVisited(int vertex) { if(vertex < 0 || vertex > numVertices) {return false;} else {return visited[vertex];} }
	void setVisited(int vertex) { if(vertex < 0 || vertex > numVertices) {return;} else { visited[vertex] = true;} }
	void addVertex(int vertex) { if(vertex < 0 || vertex > numVertices) {return;} else { verticeQueue.push_back(vertex);} }
	int getNumVertices() { return numVertices; }
	void displayShortestPath(int toVertex);

};

// Create a graph with given vertices,
// and maintain an adjacency list
Graph::Graph(int vertices) {

	// This code design allows creating structures for a variable number of vertices
	if(vertices < 0 || vertices > 100)
	{
		cout << "Invalid number of vertices.  Number must be between 0 and 100." << endl;
		return;
	}

	numVertices = vertices;

	visited = new bool[vertices];
	for (int i = 0; i < vertices; i++) {
		visited[i] = false;
	}

	adjList = new list<int>[vertices];

	pathLength.reserve(vertices);
	parentPath.reserve(vertices);

}

// Add edges to the graph. Note this version creates an undirected graph.
// The edges are added from both src to dest and dest to src
void Graph::addEdge(int src, int dst) {
	adjList[src].push_back(dst);
	adjList[dst].push_back(src);
}

// BFS iterative algorithm
void Graph::BFS(int startVertex) {

	list<int> queue;

	// Mark the starting vertex as visited and enqueue it
	visited[startVertex] = true;
	cout << "Pushing back starting vertex " << startVertex << endl;
	queue.push_back(startVertex);

	// list<int>::iterator i;

	parentPath[startVertex] = -1;	// This provides: pathLength[startVertex] = pathLength[startVertex] + 1 = (-1) + 1 = 0

	while (!queue.empty()) {
		int currVertex = queue.front();
		cout << "Visiting vertex " << currVertex << endl;
		queue.pop_front();

		/*
		 * Get all adjacent vertices of the dequeued current vertex.
		 * If an adjacent vertex has not been visited, then mark it
		 * visited and enqueue it for later visitation.
		 */
		// Two different ways to iterate through the adjacency list
		// for(auto it = adjLists[currVertex].begin(); it != adjLists[currVertex].end(); ++it) {
		//     int adjVertex = *it;
		for(auto adjVertex : adjList[currVertex]) {
			if (!visited[adjVertex]) {
				visited[adjVertex] = true;
				cout << "  Pushing back unvisited vertex " << adjVertex << endl;
				queue.push_back(adjVertex);

				// Get a record of hops from starting vertex
				pathLength[adjVertex] = pathLength[currVertex] + 1;
				// Get a record of path back to parent vertex
				parentPath[adjVertex] = currVertex;

			}
			else {
				;// cout << "  Skipping visited vertex " << adjVertex << endl;
			}
		}
		cout << "Done visiting vertex " << currVertex << endl;
	}
}

// BFS recursive algorithm - this needs some work
// - It currently requires the visited[] array to be cleared, as well as a function to loop
//   through the list of unvisited verticies or nodes and push it into the verticeQueue.
// example:
//   for(int v=0; v < numVertices; v++) {
//     visited[v] = true;
//     verticeQueue.push(v);
//     recursiveBFS()
//   }
void Graph::recursiveBFS() {
	if (verticeQueue.empty()) {
		return;
	}

	int vertex = verticeQueue.front();
	verticeQueue.pop_front();
	cout << "Visiting vertex " << vertex << endl;

	/*
	 * Get all adjacent vertices of the dequeued current vertex.
	 * If an adjacent vertex has not been visited, then mark it
	 * visited and enqueue it for later visitation.
	 */
	// Two different ways to iterate through the adjacency list
	// for(auto it = adjLists[vertex].begin(); it != adjLists[vertex].end(); ++it) {
	//     int adjVertex = *it;
	for(int adjVertex : adjList[vertex]) {
		if (!visited[adjVertex]) {
			visited[adjVertex] = true;
			cout << "  Pushing back unvisited vertex " << adjVertex << endl;
			verticeQueue.push_back(adjVertex);
		}
		else {
			;//cout << "Skipping visited vertex " << vertex << endl;
		}
	}
	cout << "Done visiting vertex " << vertex << endl;
	recursiveBFS();
}

void Graph::displayAdjList(list<int> adj_list[], int numV) {
   for(int i = 0; i<numV; i++) {
      cout << i << "--->";
      //list<int> :: iterator it;
      //for(it = adj_list[i].begin(); it != adj_list[i].end(); ++it) {
      for(auto adjVertex : adj_list[i]) {
         cout << adjVertex << " ";
      }
      cout << endl;
   }
}

void Graph::displayShortestPath(int toVertex) {
	if(!visited[toVertex]) {
		cout << "No path to vertex" << toVertex << endl;
	} else {
		vector<int> path;
		for(int vertex = toVertex; vertex != (-1); vertex = parentPath[vertex]) {
			path.push_back(vertex);
		}
		reverse(begin(path), end(path));
		cout << "Path to " << toVertex << ": ";
		for(auto edge : path)
			cout << edge << " ";
		cout << endl;
	}
}
/*
 *     [0]-----[3]
 *      | \
 *      |  [2]
 *      |     \
 *     [1]-----[4]
 */
int main() {
	cout << "https://www.programiz.com/dsa/graph-bfs" << endl; // prints https://www.programiz.com/dsa/graph-bfs
	cout << "Iterative Graph BFS" << endl;
	Graph g(5);
	// Vertex Number:    0    1     2     3
	// Adjacency List: {1,2},{4}, {0,3}, {3}
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(0, 3);
	g.addEdge(1, 4);
	g.addEdge(2, 4);

	g.displayAdjList();

	g.BFS(0);
	g.displayShortestPath(4);

	cout << endl << "Recursive Graph BFS" << endl;
	Graph RecursiveG(5);
	RecursiveG.addEdge(0, 1);
	RecursiveG.addEdge(0, 2);
	RecursiveG.addEdge(0, 3);
	RecursiveG.addEdge(1, 4);
	RecursiveG.addEdge(2, 4);

	RecursiveG.displayAdjList();

	for(int vertex=0; vertex < RecursiveG.getNumVertices(); vertex++) {
		if(RecursiveG.isVisited(vertex) == false) {
			RecursiveG.setVisited(vertex);
			RecursiveG.addVertex(vertex);
			RecursiveG.recursiveBFS();
		}
	}
	cout << "BFS Tests Complete" << endl;


	return 0;
}
