//============================================================================
// Name        : dijkstras-algorithm.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
//============================================================================

#include<bits/stdc++.h>

using namespace std;

/*
 * Dijkstra's Shortest Path Algorithm
 *
 * For Dijkstra’s algorithm, it is always recommended to use heap (or priority queue) as the required
 * operations (extract minimum and decrease key) match with specialty of heap (or priority queue).
 * However, the problem is, priority_queue doesn’t support decrease key. To resolve this problem, do
 * not update a key, but insert one more copy of it. So we allow multiple instances of same vertex in
 * priority queue. This approach doesn’t require decrease key operation and has below important properties.
 *
 *   o Whenever distance of a vertex is reduced, we add one more instance of vertex in priority_queue.
 *     Even if there are multiple instances, we only consider the instance with minimum distance and
 *     ignore other instances.
 *
 *   o The time complexity remains O(ELogV)) as there will be at most O(E) vertices in priority queue
 *     and O(Log E) is same as O(Log V).
 *
 *  Algorithm Process
 *
 *  1) Initialize distances of all vertices as infinite.
 *
 *  2) Create an empty priority_queue pq.  Every item of pq is a pair (weight, vertex). Weight (or distance)
 *     is used used as first item  of pair as first item is by default used to compare two pairs.
 *       o How to implement Min Heap?
 *         By default the STL priority_queue implements a max-heap.  Dijkstra's algorithm requires a min-heap.
 *         The STL priority_queue supports a constructor that requires two extra arguments to make it min-heap.
 *
 *         priority_queue <Type, vector<Type>, ComparisonType > min_heap;
 *
 *         The third parameter, ‘Comparison Type’ can either be a function or factor (aka function object)
 *         that must have bool as return-type and must have 2 arguments.  The STL function greater() can be used here.
 *
 *  3) Insert source vertex into pq and make its distance as 0.
 *
 *  4) While either pq doesn't become empty
 *       a) Extract minimum distance vertex from pq. Let the extracted vertex be u.
 *       b) Loop through all adjacent of u and do the following for every vertex v.
 *            o If there is a shorter path to v through u:
 *
 *            o If dist[v] > dist[u] + weight(u, v)
 *                (i)  Update distance of v, i.e., do
 *                     dist[v] = dist[u] + weight(u, v)
 *                (ii) Insert v into the pq (Even if v is already there)
 *
 *  5) Print distance array dist[] to print all shortest paths.
 */

// Program to find Dijkstra's shortest path using
// priority_queue in STL
# define INF 0x3f3f3f3f

// Adjacency list pair. Adjacent vertex first=label, second=weight/cost/distance
typedef pair<int, int> Path;

// Distance of destination.  Distance must be first element of pair to sort by distance
typedef pair<int, int> DistOfDest;

// This class represents a directed graph using
// adjacency list representation
class Graph
{
	int numVertices; // No. of vertices

	// In a weighted graph, we need to store vertex
	// and weight pair for every edge
	list<Path> *adjList;

public:
	Graph(int V); // Constructor

	// function to add an edge to graph
	void addEdge(int src, int dst, int weight);

	// prints shortest path from s
	void shortestPath(int s);
};

// Allocates memory for adjacency list
Graph::Graph(int V)
{
	this->numVertices = V;
	// Array of vertex path lists: adjacent vertex, weight
	adjList = new list<Path> [V];
}

// Graph edges are often expressed as u -> v, where src = u and dst = v. The weight is w.
void Graph::addEdge(int src, int dst, int weight)
{
	// Note:
	// Dijkstra's algorithm is similar to the Breadth-First-Search algorithm. The adjacency list includes
	// one important difference.  The adjaceny list for Dijkstra's implementation uses a pair formed by
	// the adjacent vertex and the weight or distance between each vertex.  If the edge map is directed, then
	// only a single list element is created, while for an undirected edge map a list element is created for
	// both src --> dst the reverse dst to src.
	//
	adjList[src].push_back(make_pair(dst, weight));
	adjList[dst].push_back(make_pair(src, weight));
}

// Prints shortest paths from src to all other vertices
void Graph::shortestPath(int src)
{
	if(src < 0 || src >= numVertices) {
		cout << "Invalid source vertices. Source must be range from 0 to " << numVertices << endl;
		return;
	}
	// Create a priority queue to store vertices that
	// are being preprocessed. This is weird syntax in C++.
	// Refer below link for details of this syntax
	// https://www.geeksforgeeks.org/implement-min-heap-using-stl/
	priority_queue< DistOfDest, vector <DistOfDest> , greater<DistOfDest> > minHeapPriQ;

	// Create a vector for distances and initialize all
	// distances as infinite (INF)
	vector<int> distFromSrcTo(numVertices, INF);
	cout << "Number Vertices = " << numVertices << endl;

	// Insert source itself in priority queue and initialize
	// its distance as 0.
	minHeapPriQ.push(make_pair(0, src));
	distFromSrcTo[src] = 0;

	/* Looping till priority queue becomes empty (or all
	distances are not finalized) */
	while (!minHeapPriQ.empty())
	{
		// The first vertex in pair is the minimum distance
		// vertex, extract it from priority queue.
		// vertex label is stored in second of pair (it
		// has to be done this way to keep the vertices
		// sorted distance (distance must be first item
		// in pair)
		int visitingVertex = minHeapPriQ.top().second;
		minHeapPriQ.pop();

		// CN: Using C++11 range based for loop
		// 'i' is used to get all adjacent vertices of a vertex
		//list< pair<int, int> >::iterator i;
		//for (i = adjList[u].begin(); i != adjList[u].end(); ++i)
		cout << "Visiting vertex " << visitingVertex << endl;
		for(auto& adjVertexElement : adjList[visitingVertex] )
		{
			// Get vertex label and weight of current adjacent
			// of u.
			//was: int v = (*i).first;
			int adjV = adjVertexElement.first;
			//was: int weight = (*i).second;
			int distFromVisitingVToAdjV = adjVertexElement.second;

			// printf is just easier...
			//cout << "    (" << u << ")" << "---" << weight << "--->(" << adjV << ")" << endl;
			printf("    (%d)---%d--->(%d)\n", visitingVertex, distFromVisitingVToAdjV, adjV);

			// If there is a shorter path to the adjacent vertex from the src vertex through minDistVertex.
			// CN: Note the dist[] array starts off being initialized to INF (infinite),
			//     so if a path is found it will update the dist[] array, at least once.
			int distFromSrcToAdjV = distFromSrcTo[visitingVertex] + distFromVisitingVToAdjV;
			if (distFromSrcTo[adjV] > distFromSrcToAdjV)
			{
				// Updating distance of vertex to source
				distFromSrcTo[adjV] = distFromSrcToAdjV;
				printf("Updating minimum distance path to vertex %d: dist[%d]=%d\n", adjV, adjV, distFromSrcToAdjV);
				minHeapPriQ.push(make_pair(distFromSrcTo[adjV], adjV));
			}
		}
	}

	// Print shortest distances stored in dist[]
	printf("Vertex Distance from Source\n");
	for (int i = 0; i < numVertices; ++i)
		printf("%d \t\t %d\n", i, distFromSrcTo[i]);
}

// Driver program to test methods of graph class
/*       8       7
    (1)-----(2)-----(3)
    /|       |\      |\
  4/ |      2| \     | \9
  /  |       |  \    |  \
(0)  |      (8) 4\ 14|  (4)
  \  |     / |    \  |  /
  8\ |  7/  6|     \ | /10
    \| /     |      \|/
    (7)-----(6)-----(5)
          1      2
*/
int main()
{
	cout << "https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/" << endl; 
	// create the graph given in above fugure
	int V = 9;
	Graph g(V);

	// making above shown graph
	g.addEdge(0, 1, 4);
	g.addEdge(0, 7, 5);  // was 0,7,8
	g.addEdge(1, 2, 8);  // was 1,2,8
	g.addEdge(1, 7, 11);
	g.addEdge(2, 3, 7);
	g.addEdge(2, 8, 2);
	g.addEdge(2, 5, 4);
	g.addEdge(3, 4, 9);
	g.addEdge(3, 5, 14);
	g.addEdge(4, 5, 6);  // was 4,5,10
	g.addEdge(5, 6, 2);
	g.addEdge(6, 7, 1);
	g.addEdge(6, 8, 6);
	g.addEdge(7, 8, 7);

	g.shortestPath(0);

	return 0;
}
