//============================================================================
// Name        : btree-class-with-stl.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : Udemy.com course Master Data Structures & Algorithms using C and C++
//============================================================================

#include <iostream>
#include <queue>	// FIFO	- first in first out
#include <stack>	// LIFO	- last in first out
#include <vector>
#include <map>
#include <tgmath.h>	// log2(int)
#include <climits>	// INT_MAX
#include <algorithm>
#include<bits/stdc++.h>

using namespace std;

/*
 * Analysis notes:
 *
 * Definitions:
 * o Root == One designated node of a tree drawn to be the top of an inverted tree
 * o Parent == A node is a parent to its next descendants or children
 * o Children ==
 * o Siblings == children of same parent
 * o Descendants == all nodes which can be reached from a particular node in a path to the terminal node
 * o Ancestor == all the nodes along the path to the root
 * o Degree of a node == number of children a nodes has is degree of a node
 * o Degree of a tree == maximum degree of any node in the tree
 * o Internal nodes == non-leaf nodes, or nodes with degree greater than zero
 * o External nodes == leaf nodes, or nodes with degree zero, or terminal nodes
 * o Levels == root starts level counting at 1. AKA count of nodes in a path from root to leaf
 * o Edges == connections or links between nodes
 * o Height == root starts height counting at 0. AKA count of edges in a path from root to leaf
 * o Forest == collection of trees
 *
 * For N nodes in a tree:
 * o Number of recursive calls = (2 * N) + 1
 * o Time complexity correlates to number of recursive calls
 * o Height of the calling stack = height of tree + 2
 * o There are N+1 null pointers
 * o Number of external or leaf nodes 'e'  == number of internal nodes 'i' + 1 (strict binary tree)
 * o Number of edges == number of nodes - 1  (edges are connections or links between nodes)
 * o Maximum nodes for tree with height n = 2^(h+1) - 1
 *   o Minimum height for tree with #nodes: 2^(h+1) = n + 1 => h+1 = log(n+1) => [ h = log(n+1) - 1 ]
 * o Minimum nodes for tree with height n = h + 1
 *   o Maximum height for tree with #nodes: h = n - 1
 *
 * o Height of a Binary Tree, based on number of nodes can range:  log(n+1)-1 <= height <= n-1    O(log n)
 * o Number of Nodes in a Binary Tree based on height can range:   h+1 <= nodes <= 2^(h+1) - 1    O(n)
 *
 *
 * Traversal type notes:
 * o Pre-order traversal is only method that will allow creating the exact same structure of the original tree (pre-order traversal -> insert new node)
 * o In-order traversal visits each node according to its value in a least to greatest path.
 * o Level-order traversal requires a queue.
 * o Iterative traversal of pre/in/post order trees requires a stack.
 *
 *
 * Generating Binary Trees from traversal
 * o Not possible using only pre/in/post order traversal methods. Many more than 1 tree output is possible - too ambiguous.
 * o 2 methods are available using 2 types: (preorder and inorder) or (postoder and inorder)
 *
 * Postorder is most common method employed in processing data from binary trees.  Example: counting nodes uses postorder traversal method.
 *
 * Counting Node types logic
 * 1. Leaf nodes, degree 0:
 * 	  if(p->lchild == nullptr && p->rchild == nullptr)
 *
 * 2. Node degree 1
 * 	  if( (p->lchild != nullptr) ^ (p->rchild != nullptr) ) // exclusive OR of boolean conditions
 * 	     or
 * 	  if( (p->lchild == nullptr) ^ (p->rchild == nullptr) ) // exclusive OR of boolean conditions
 *
 *
 */
template<class T>
void printVector(string name, vector<T> const &vec) {
	cout << name << ": " << endl;
	cout << "  [ ";
	for (T val: vec) {
		cout << val << " ";
	}
	cout << "]" << endl;
}

class Node{
public:
    Node* lchild;
    int data;
    Node* rchild;
};

class Tree{
private:
    Node* root;
    int maxTreeDiameter;
    int numTreeNodes;
    multimap<int, int> NodePosition;
	vector<vector<int>> PositionMatrix;
	vector<vector<int>> LevelMatrix;

public:
    Tree();
    ~Tree();
    void CreateTree();
    Node* createBinaryTree(int dataArray[], int numNodes);

    Node* getTree() { return root; };
    void recursivePreorder(Node* p);
    void Preorder() { recursivePreorder(root); }  // Passing Private Parameter in Constructor
    void recursiveInorder(Node* p);
    void recursiveLeftSideInorder(Node* node, vector<int>& vec);
    void recursiveRightSideInorder(Node* node, vector<int>& vec);
    void Inorder() { recursiveInorder(root); }
    void recursivePostorder(Node* p);
    void Postorder() { recursivePostorder(root); }
    void Levelorder(Node* p);
    void Levelorder() { Levelorder(root); }

    void setPreOrderVerticalPosition(Node *p, int position);
    void setInOrderVerticalPosition(Node *p, int position);
    void setPostOrderVerticalPosition(Node *p, int position);
    void setLevelOrderVerticalPosition(Node *p, int position);
    void setLevelOrderVerticalPosition() { setLevelOrderVerticalPosition(root, 0); };

    multimap<int, int> *getPositionMap() { return &NodePosition; };
    vector<vector<int>> *getPositionMatrix() { return &PositionMatrix; }
    void loadMatrix();


    int Height(Node* p);
    int Height() { return Height(root); }
    int Count(Node* p);
    int Count() { return Count(root); }
    int Sum(Node* p);
    int Sum(){ return Sum(root); }
    int deg2NodeCount(Node* p);
    int deg2NodeCount() { return deg2NodeCount(root); }
    int deg1NodeCount(Node* p);
    int deg1NodeCount() { return deg1NodeCount(root); }
    int LeafNodeCount(Node* p);
    int LeafNodeCount() { return LeafNodeCount(root); }
    int getNodeCount() { return numTreeNodes; }

    void iterativePreorder(Node* p);
    void iterativePreorder() { iterativePreorder(root); }
    void iterativeInorder(Node* p);
    void iterativeInorder() { iterativeInorder(root); }
    void iterativePostorder(Node* p);
    void iterativePostorder() { iterativePostorder(root); }
    Node *CreateDefaultTree();
    bool isValidBST(Node* root);
    bool testBST(Node* node, Node* minNode, Node* maxNode);
    bool isSymmetric(Node* node);
    bool isSymmetric() { return isSymmetric(root); };

    void iterativeInsert(int key);
    void recursiveInsert(Node*p, int key);

    Node* Delete(Node *p, int key);
    Node* Delete(int key) { return Delete(root, key); }

    void deletePostorder(Node *p);
    void deletePostorder() { return deletePostorder(root); }

    Node* inorderPredecessor(Node *p);
    Node* inorderSuccessor(Node *p);

    Node* iterativeSearch(Node *, int key);
    Node* iterativeSearch(int key) { return iterativeSearch(root, key); };
    Node* recursiveSearch(Node *, int key);
    Node* recursiveSearch(int key) { return recursiveSearch(root, key); };

    void creatBSTfromPreorder(int pre[], int n);
    Node* sortedArrayToBST(vector<int> vec, int start, int end);


    int postOrderNodeCount(Node *p)
    {
    	if(!p)return 0;
    	int left=postOrderNodeCount(root->lchild);
    	int right=postOrderNodeCount(root->rchild);
        maxTreeDiameter=max(maxTreeDiameter,left+right);
    	return max(left,right)+1;
    }
    int diameterOfBinaryTree(Node* p) {
    	maxTreeDiameter=0;
    	postOrderNodeCount(p);
    	return maxTreeDiameter;
    }

};

Tree::Tree() {
    root = nullptr;
    maxTreeDiameter = 0;
    numTreeNodes = 0;
}

Tree::~Tree() {
    // TODO
}

Node *Tree::CreateDefaultTree() {
	int dataArray[] = {50, 30,70, 20,40, 60,80, -1, -1};
	//int dataArray[] = {7, 3,15, -1,-1, 9,20, -1, -1, -1, -1, -1, -1, -1, -1};
	//int dataArray[] = {1, 2, 3, -1, -1, 4, 5};
	//int dataArray[] = {1, 2, 2, 3, 4, 4, 3};
	//int dataArray[] = {1,2,2,3,4,4,3,4,5,5,6,6,5,5,4};
	//int dataArray[] = {1,2,2,2,-1,2,-1};
	//int dataArray[] = {2,3,3,4,5,-1,4};
    Node* p;
    Node* t;
    int x;
    queue<Node*> q;
    int idx = 0;
    int numNodes = sizeof(dataArray) / sizeof(int);

    root = new Node;
    root->data = dataArray[idx++];
    root->lchild = nullptr;
    root->rchild = nullptr;
    q.emplace(root);

    while (! q.empty() && idx < numNodes){
        p = q.front();
        q.pop();

        x = dataArray[idx++];
        if (x != -1){
            t = new Node;
            t->data = x;
            t->lchild = nullptr;
            t->rchild = nullptr;
            p->lchild = t;
            q.emplace(t);
            numTreeNodes++;
        }

        x = dataArray[idx++];
        if (x != -1){
            t = new Node;
            t->data = x;
            t->lchild = nullptr;
            t->rchild = nullptr;
            p->rchild = t;
            q.emplace(t);
            numTreeNodes++;
        }
    }

	return root;
}

void Tree::CreateTree() {
    Node* p;
    Node* t;
    int x;
    queue<Node*> q;

    root = new Node;
    cout << "Enter root data: " << flush;
    cin >> x;
    root->data = x;
    root->lchild = nullptr;
    root->rchild = nullptr;
    q.emplace(root);

    while (! q.empty()){
        p = q.front();
        q.pop();

        cout << "Enter left child data of " << p->data << ": " << flush;
        cin >> x;
        if (x != -1){
            t = new Node;
            t->data = x;
            t->lchild = nullptr;
            t->rchild = nullptr;
            p->lchild = t;
            q.emplace(t);
            numTreeNodes++;
        }

        cout << "Enter right child data of " << p->data << ": " << flush;
        cin >> x;
        if (x != -1){
            t = new Node;
            t->data = x;
            t->lchild = nullptr;
            t->rchild = nullptr;
            p->rchild = t;
            q.emplace(t);
            numTreeNodes++;
        }
    }
}

Node* Tree::createBinaryTree(int dataArray[], int numNodes) {
	//int dataArray[] = {7, 3,15, -1,-1, 9,20, -1, -1, -1, -1, -1, -1, -1, -1};
    Node* p;
    Node* t;
    int x;
    queue<Node*> q;
    int idx = 0;

    if(numNodes <= 0)
    	return 0;

    root = new Node;
    root->data = dataArray[idx++];
    root->lchild = nullptr;
    root->rchild = nullptr;
    q.emplace(root);

    while (! q.empty() && idx < numNodes){
        p = q.front();
        q.pop();

        x = dataArray[idx++];
        //if (x != -1){
            t = new Node;
            t->data = x;
            t->lchild = nullptr;
            t->rchild = nullptr;
            p->lchild = t;
            q.emplace(t);
            numTreeNodes++;
        //}
        if(idx < numNodes) {
        	x = dataArray[idx++];
        	//if (x != -1){
            t = new Node;
            t->data = x;
            t->lchild = nullptr;
            t->rchild = nullptr;
            p->rchild = t;
            q.emplace(t);
            numTreeNodes++;
            //}
        }
    }

	return root;
}


void Tree::recursivePreorder(Node *p) {
    if (p){
        cout << p->data << ", " << flush;	// Output data 'pre' or before left & right recursive calls
        recursivePreorder(p->lchild);
        recursivePreorder(p->rchild);
    }
}

void Tree::recursiveInorder(Node *p) {
    if (p){
        recursiveInorder(p->lchild);
        cout << p->data << ", " << flush;	// Output data 'in'-between left & right recursive calls
        recursiveInorder(p->rchild);
    }
}

void Tree::recursivePostorder(Node *p) {
    if (p){
        recursivePostorder(p->lchild);
        recursivePostorder(p->rchild);
        cout << p->data << ", " << flush;	// Output data 'post' or after left & right recursive calls
    }
}

void Tree::recursiveLeftSideInorder(Node* node, vector<int>& vec) {
	if(node) {
		recursiveLeftSideInorder(node->lchild, vec);
	    cout << node->data << " ";
	    vec.emplace_back(node->data);
	}
}

void Tree::recursiveRightSideInorder(Node* node, vector<int>& vec) {
	if(node) {
	    recursiveRightSideInorder(node->rchild, vec);
	    cout << node->data << " ";
	    vec.emplace_back(node->data);
	}
}

/*
[1,2,2,3,4,4,3]
[1,2,2,null,3,null,3]
[1,2,2,2,null,2,null]
[1,2,2,3,4,4,3,4,5,5,6,6,5,5,4]
[2,3,3,4,5,null,4]
[2,3,3,4,5,5,4,null,null,8,9,null,null,9,8]
[]
 */
bool Tree::isSymmetric(Node *p) {
	vector<int> rightSideVec;
	vector<int> leftSideVec;
    if(p) {
    	recursiveLeftSideInorder(p, leftSideVec);
    	recursiveRightSideInorder(p, rightSideVec);
    }
    int rightNodeCount = rightSideVec.size();
    cout << endl;
    cout << "Right side size = " << rightNodeCount << endl;
    printVector("Right Side", rightSideVec);

    int leftNodeCount = leftSideVec.size();
    cout << "Reft side size = " << leftNodeCount << endl;
    printVector("Left Side", leftSideVec);

    if(leftNodeCount != rightNodeCount) return false;

    return (leftSideVec == rightSideVec);
}

/*
 * https://www.cs.bu.edu/teaching/cs112/spring-2000/breadth-first/
 */
void Tree::Levelorder(Node *p) {
	if(p == nullptr)
		return;

    queue<Node*> q;
    // queue node, get/pop/remove node, if left:output data & queue node, if right:output data & queue node...repeat
    //cout << p->data << ", " << flush;
    q.emplace(p);

    while (! q.empty()){
        p = q.front();
        // Visiting node
        cout << p->data << ", " << flush;
        q.pop();

        // In a graph this is where a for loop iterates through an adjacency list, where the vertex id is the index
        // each vertices is tested against a visited[] boolean array indexed by the same vertex id.
        // if the vertices is not visited, then the vertices id is pushed into the queue.
        // Searching in a binary tree is similar, but does not require an adjacency list, nor a visited array.
        // The node elements are similarly pushed in to a queue for
        if (p->lchild){
            //cout << p->lchild->data << ", " << flush;
            q.emplace(p->lchild);
        }

        if (p->rchild){
            //cout << p->rchild->data << ", " << flush;
            q.emplace(p->rchild);
        }
    }
    cout << endl;
}

void Tree::setPreOrderVerticalPosition(Node *p, int position) {
    if (p){
    	if(p->data >= 0) {
    		NodePosition.emplace(make_pair(position, p->data));
    		cout << p->data << "(" << position << "), " << flush;	// Output data 'pre' or before left & right recursive calls
    	}
        setPreOrderVerticalPosition(p->lchild, position + (1));
        setPreOrderVerticalPosition(p->rchild, position + (1));
    }
}

void Tree::setInOrderVerticalPosition(Node *p, int position) {
    if (p){
        setPreOrderVerticalPosition(p->lchild, position + (-1));
    	if(p->data >= 0) {
    		NodePosition.emplace(make_pair(position, p->data));
    		cout << p->data << "(" << position << "), " << flush;	// Output data 'pre' or before left & right recursive calls
    	}
        setPreOrderVerticalPosition(p->rchild, position + (1));
    }
}

void Tree::setPostOrderVerticalPosition(Node *p, int position) {
    if (p){
        setPreOrderVerticalPosition(p->lchild, position + (-1));
        setPreOrderVerticalPosition(p->rchild, position + (1));
    	if(p->data >= 0) {
    		NodePosition.emplace(make_pair(position, p->data));
    		cout << p->data << "(" << position << "), " << flush;	// Output data 'pre' or before left & right recursive calls
    	}
    }
}
void Tree::setLevelOrderVerticalPosition(Node *p, int position)
{
	if(p == nullptr)
		return;

	struct LevelNode {
		Node *p;
		int level;
	};

    queue<LevelNode*> q;
    LevelNode *lnp = new LevelNode;
    lnp->level = 0;
    lnp->p = p;

    // queue node, get/pop/remove node,
    // if left:output data & queue node,
    // if right:output data & queue node...repeat
	if(p->data >= 0) {
		cout << p->data << ", " << flush;
		NodePosition.emplace(make_pair(position, p->data));
	}
    q.emplace(lnp);

    while (! q.empty()){
        lnp = q.front();
        q.pop();

        if (lnp->p->lchild){
        	if(lnp->p->data >= 0) {
                int lpos = lnp->level + 1;

                // Output data 'pre' or before left & right recursive calls
        		cout << lnp->p->lchild->data << "(" << lpos << "), " << flush;
        		NodePosition.emplace(make_pair(lpos, p->lchild->data));
            	LevelNode *leftLevelNode = new LevelNode;
            	leftLevelNode->level = lpos;
            	leftLevelNode->p = lnp->p->lchild;
                q.emplace(leftLevelNode);
        	}
        }

        if (lnp->p->rchild){
        	if(lnp->p->data >= 0) {
        		int rpos = lnp->level + 1;
        		// Output data 'pre' or before left & right recursive calls
        		cout << lnp->p->rchild->data << "(" << rpos << "), " << flush;
        		NodePosition.emplace(make_pair(rpos, p->rchild->data));
            	LevelNode *rightLevelNode = new LevelNode;
            	rightLevelNode->level = rpos;
            	rightLevelNode->p = lnp->p->rchild;
                q.emplace(rightLevelNode);
        	}
        }
    }
}

int Tree::Height(Node *p) {
    int l = 0;
    int r = 0;
    if (p == nullptr) {
        return 0;
    }

    // Looks like post order tree traversal
    l = Height(p->lchild);	// returns 0 when final left child is nullptr
    r = Height(p->rchild);	// returns 0 when final right child is nullptr

    if (l > r){
        return l + 1;
    } else {
        return r + 1;
    }
}

int Tree::Count(Node *p) {
    int x;
    int y;
    if (p == nullptr){
    	return 0;
    }

    // Looks like post order tree traversal
    x = Count(p->lchild);
    y = Count(p->rchild);

    return x + y + 1;
}

int Tree::Sum(Node *p) {
    int x;
    int y;
    if (p == nullptr){
    	return 0;
    }
    // Looks like post order tree traversal
    x = Sum(p->lchild);
    y = Sum(p->rchild);

    return x + y + p->data;
}

int Tree::deg2NodeCount(Node *p) {
	int x;
	int y;
	if (p == nullptr){
		return 0;
	}

    // Looks like post order tree traversal
	x = deg2NodeCount(p->lchild);
	y = deg2NodeCount(p->rchild);

	if (p->lchild && p->rchild){
		return x + y + 1;
	} else {
		return x + y;
	}
}

int Tree::deg1NodeCount(Node *p) {
	int x;
	int y;
	if (p == nullptr){
		return 0;
	}

    // Looks like post order tree traversal
	x = deg2NodeCount(p->lchild);
	y = deg2NodeCount(p->rchild);
	if ( (p->lchild != nullptr) ^ (p->rchild != nullptr) ){
		return x + y + 1;
	} else {
		return x + y;
	}
}

int Tree::LeafNodeCount(Node *p) {
	int x;
	int y;
	if (p != nullptr){
		return 0;
	}

    // Looks like post order tree traversal
	x = LeafNodeCount(p->lchild);
	y = LeafNodeCount(p->rchild);
	if(p->lchild == nullptr && p->rchild == nullptr)
		return x + y + 1;
	else
		return x + y;
}


void Tree::iterativePreorder(Node *p) {
    stack<Node*> stk;
    while (p != nullptr || ! stk.empty()){
        if (p != nullptr){
            cout << p->data << ", " << flush;
            stk.emplace(p);
            p = p->lchild;
        } else {
            p = stk.top();
            stk.pop();
            p = p->rchild;
        }
    }
    cout << endl;
}

void Tree::iterativeInorder(Node *p) {
    stack<Node*> stk;
    while (p != nullptr || ! stk.empty()){
        if (p != nullptr){
            stk.emplace(p);
            p = p->lchild;
        } else {
            p = stk.top();
            stk.pop();
            cout << p->data << ", " << flush;
            p = p->rchild;
        }
    }
    cout << endl;
}

void Tree::iterativePostorder(Node *p) {
    stack<long int> stk;
    long int temp;
    while (p != nullptr || ! stk.empty()){
        if (p != nullptr){
            stk.emplace((long int)p);
            p = p->lchild;
        } else {
            temp = stk.top();
            stk.pop();
            if (temp > 0){
                stk.emplace(-temp);
                p = ((Node*)temp)->rchild;
            } else {
                cout << ((Node*)(-1 * temp))->data << ", " << flush;
                p = nullptr;
            }
        }
    }
    cout << endl;
}

bool Tree::isValidBST(Node* root) {

    return testBST(root, nullptr, nullptr);
}

void Tree::deletePostorder(Node *p) {
    if (p){
    	deletePostorder(p->lchild);
    	deletePostorder(p->rchild);
        cout << p->data << ", " << flush;	// Output deleted Node...
    	delete p;
    }
}

/*
 * How do you know if a binary tree is valid?
 *
 * To see if a binary tree is a binary search tree, check:
 * If a node is a left child, then its key and the keys of the nodes in its right subtree are less than its parent's key.
 * If a node is a right child, then its key and the keys of the nodes in its left subtree are greater than its parent's key.
 */
bool Tree::testBST(Node* node, Node* minNode, Node* maxNode) {
	if(node == nullptr) {
		return true;
	}

    if(minNode != nullptr) {
        if(node->data <= minNode->data) {
            return false;
        }
    }

    if(maxNode != nullptr) {
        if(node->data >= maxNode->data) {
            return false;
        }
    }

	// Left side test must verify all nodes are smaller than parent AND
	// parent must pass down value as maximum node value.
    //
    // If a node is a left child, then its key and the keys of the nodes in its right subtree are less than its parent's key.
	if(node->lchild) {
		if(!testBST(node->lchild, minNode, node)) {
			return false;
		}
	}

	// Right side test must verify all nodes are greater than parent node AND
	// parent must pass down value as minimum node.
	//
	// If a node is a right child, then its key and the keys of the nodes in its left subtree are greater than its parent's key.
	if(node->rchild) {
		if(!testBST(node->rchild, node, maxNode)) {
			return false;
		}
	}
	return true;
}

void Tree::iterativeInsert(int key) {

    Node* testNode = root;
    Node* p;
    Node* parentNode;

    // root is empty
    if (root == nullptr){
        p = new Node;
        p->data = key;
        p->lchild = nullptr;
        p->rchild = nullptr;
        root = p;
        return;
    }

    // First find the correct parent to link the new key
    while(testNode != nullptr){
        parentNode = testNode;   // save the node parent, test which side the key will be placed
        if (key < testNode->data){
            testNode = testNode->lchild;
        } else if (key > testNode->data){
            testNode = testNode->rchild;
        } else {
        	// indication a leaf already exists - no insertion
            return;
        }
    }

    // Now testNode points at NULL and parentNode points at parent insert location
    p = new Node;
    p->data = key;
    p->lchild = nullptr;
    p->rchild = nullptr;

    if (key < parentNode->data){
        parentNode->lchild = p;
    } else {
        parentNode->rchild = p;
    }
    numTreeNodes++;

}

void Tree::recursiveInsert(Node *p, int key) {
	// TBD
	iterativeInsert(key);
}

Node* Tree::Delete(Node *p, int key) {
    Node* q;

    if (p == nullptr){
        return nullptr;
    }

    if (p->lchild == nullptr && p->rchild == nullptr){
        if (p == root){
            root = nullptr;
        }
        delete p;
        return nullptr;
    }

	/*
	 * This will either delete the child node and return nullptr or return
	 */
    if (key < p->data){
        p->lchild = Delete(p->lchild, key);
    } else if (key > p->data){
        p->rchild = Delete(p->rchild, key);
    } else {
    	// key is found, decide which node to delete, depending on height.
    	// Delete the node with the greater height to maintain tree balance
        if (Height(p->lchild) > Height(p->rchild)){
            q = inorderPredecessor(p);
            p->data = q->data;
            numTreeNodes--;
            p->lchild = Delete(p->lchild, q->data);
        } else {
            q = inorderSuccessor(p);
            p->data = q->data;
            numTreeNodes--;
            p->rchild = Delete(p->rchild, q->data);
        }
    }
    return p;
}

/*
 * The inorder predecessor of a node is the right-most child
 * of the left subtree.
 */
Node* Tree::inorderPredecessor(Node *p) {
	p = p->lchild;
	// now find right-most child
    while (p && p->rchild != nullptr){
        p = p->rchild;
    }
    return p;
}

/*
 * The inorder successor of a node is the left-most child
 * of the right subtree.
 */
Node* Tree::inorderSuccessor(Node *p) {
	// first get the right subtree
	p = p->rchild;
	// now find left-most child
    while (p && p->lchild != nullptr){
        p = p->lchild;
    }
    return p;
}

Node* Tree::iterativeSearch(Node *t, int key) {

	while (t != nullptr){
        if (key == t->data){
            return t;
        } else if (key < t->data){
            t = t->lchild;
        } else {
            t = t->rchild;
        }
    }
    return nullptr;
}

Node* Tree::recursiveSearch(Node *p, int key) {
    if (p == nullptr){
        return nullptr;
    }

    if (key == p->data){
        return p;
    } else if (key < p->data){
        return recursiveSearch(p->lchild, key);
    } else {
        return recursiveSearch(p->rchild, key);
    }
}

void Tree::creatBSTfromPreorder(int *pre, int n) {

    // Create root node
    int i = 0;
    root = new Node;
    root->data = pre[i++];
    root->lchild = nullptr;
    root->rchild = nullptr;

    // Iterative steps
    Node* t;
    Node* p = root;
    stack<Node*> stk;

    while (i < n){
        // Left child case
        if (pre[i] < p->data){
        	// New leaf value preorderList[i] is less than parent leaf value parentNode->val:
        	// 1. Create a new node, load the val member, clear the link members
        	// 2. Load the new node pointer into the parent left side pointer.
        	// 3. Push the current parentNode into the stack.
        	// 4. Set the parent node pointer to the new node
            t = new Node;
            t->data = pre[i++];
            t->lchild = nullptr;
            t->rchild = nullptr;
            p->lchild = t;
            stk.push(p);
            p = t;
        } else {
            // Right child cases
        	// To be able to process a preorder array list, the stack becomes empty at the point between inserting
        	// the left side nodes and the remaining right side nodes.  The kludgy INT_MAX logic allows the logic
        	// to continue at this past this point and process the rest of the node elements.
            if (pre[i] > p->data && pre[i] < (stk.empty() ? INT_MAX : stk.top()->data)){
            	// New leaf value preorderList[i] is less than parent leaf value parentNode->val:
            	// 1. Create a new node, load the val member, clear the link members
            	// 2. Load the new node pointer into the parent right side pointer.
            	// 3. Push the current parentNode into the stack.
            	// 4. Set the parent node pointer to the new node
                t = new Node;
                t->data = pre[i++];
                t->lchild = nullptr;
                t->rchild = nullptr;
                p->rchild = t;
                p = t;
            } else {
                p = stk.top();
                stk.pop();
            }
        }
    }
}

// https://www.geeksforgeeks.org/sorted-array-to-balanced-bst/
Node* Tree::sortedArrayToBST(vector<int> vec, int start, int end)
{
	if(start > end)
		return nullptr;

	int middle = start + end / 2;

	Node *root = new Node;
	root->data = vec[middle];
	root->lchild = sortedArrayToBST(vec, start, middle - 1);
	root->lchild = sortedArrayToBST(vec, middle + 1, end);

	return root;
}

void Tree::loadMatrix() {
	int col = -1;
	int lastCol = INT_MAX;

	auto pNodeMap = getPositionMap();
	for (auto it=pNodeMap->begin(); it!=pNodeMap->end(); ) {
		//cout << it->first << ": " << it->second << '\n';
		if(it->first != lastCol) {
			col++;
			lastCol = it->first;
			vector<int> row;
			while(it->first == lastCol)
			{
				row.push_back(it->second);
				it++;
			}
			// sort(begin(row), end(row));
			PositionMatrix.push_back(row);
		}
	}
}

/*
 * Symmetric Tree
 *
https://leetcode.com/problems/symmetric-tree/
https://leetcode.com/problems/symmetric-tree/discuss/980285/Simple-Recursive-Solution....0ms-(100-faster)
 */
class SymmetricTreeSolution
{
public:
    bool isMirror(Node* root1, Node* root2)
    {
        if(root1 == NULL && root2 == NULL)
            return true;
        if(root1 != NULL && root2 != NULL && root1->data == root2->data)
            return (isMirror(root1->lchild, root2->rchild) && isMirror(root1->rchild, root2->lchild));
        else
            return false;
    }
    bool isSymmetric(Node* root)
    {
        return isMirror(root, root);
    }
};

/*
 * Binary Tree Level Order Traversal
 *
Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

 */
// https://leetcode.com/problems/binary-tree-level-order-traversal/
class LevelOrderSolution {
public:
    vector<vector<int>> levelOrder(Node* root) {

        if(root == nullptr) return {};
        vector<vector<int>> result;

        queue<Node*> q;
        q.emplace(root);

        while(!q.empty())
        {
            /*
             * Create a temporary vector and insert all the nodes in a level.
             * The first level has only the root node, but each successive level
             * increases by a power of 2.  The queue contains a current count
             * of all the nodes in a single level. We can create a vector with
             * a size that corresponds to the queue size.  This will prevent
             * the performance hit from resizing the vector.
             */

            int nodeCount = q.size();
            vector<int> nodeLeveVec(nodeCount);

            while(nodeCount--)
            {
                Node* curr = q.front();
                q.pop();
                nodeLeveVec.emplace_back(curr->data);
                if(curr->lchild) q.emplace(curr->lchild);
                if(curr->rchild) q.emplace(curr->rchild);
            }

            result.emplace_back(nodeLeveVec);
        }
        return result;
    }
};

template<class T>
void printMatrix(vector<vector<T>> const &mat) {
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

// Less than ideal solution
class LevelOrderSolutionII {
    vector<vector<int>> result;
    multimap<int, int> nodeLevelMap;
public:
    vector<vector<int>> levelOrder(Node* root) {
        if(root == nullptr)
            return result;

        recordPreOrderTraversal(root, 0);
        loadMatrix();
        //printMatrix(result);
        return result;
    }

    void recordPreOrderTraversal(Node* node, int level) {
        if (node){
    		nodeLevelMap.emplace(make_pair(level, node->data));
            //result[level].push_back(node->val);
            // Output data 'pre' or before left & right recursive calls
            // cout << node->val << "(" << level << "), " << flush;
            recordPreOrderTraversal(node->lchild, level + 1);
            recordPreOrderTraversal(node->rchild, level + 1);
        }
    }

    void loadMatrix() {
        int col = -1;
        int lastCol = INT_MAX;

        auto pNodeMap = &nodeLevelMap;
        for (auto it=pNodeMap->begin(); it!=pNodeMap->end(); ) {
            //cout << it->first << ": " << it->second << '\n';
            if(it->first != lastCol) {
                col++;
                lastCol = it->first;
                vector<int> row;
                while(it->first == lastCol)
                {
                    row.push_back(it->second);
                    it++;
                }
                result.push_back(row);
            }
        }
    }

};

int main() {

    cout << "hello";
    return 0;

    Tree bt;
    vector<int> vec {-10,-3,0,5,9};
    bt.sortedArrayToBST(vec, 0, vec.size()-1);

#define COMPLETE_TEST
#ifdef COMPLETE_TEST
    //bt.CreateTree();
    bt.CreateDefaultTree();

    cout << "Levelorder Iterative: " << flush;
    bt.Levelorder();
    cout << endl;

    cout << "Inorder Recursive: " << flush;
    bt.Inorder();
    cout << endl;

    if(bt.isValidBST(bt.getTree()))
    	cout << "Default tree created is a valid BST" << endl;
    else
    	cout << "Default tree created is NOT a valid BST" << endl;

    cout << "Total Node Count: " << bt.Count() << endl;

    cout << "Log(node-count) = " << log2(bt.Count()) << endl;

    cout << "Sum of Elements: " << bt.Sum() << endl;

    cout << "Degree 2 Node Count: " << bt.deg2NodeCount() << endl;

    cout << "Degree 1 Node Count: " << bt.deg1NodeCount() << endl;

    cout << "Leaf Node Count: " << bt.LeafNodeCount() << endl;

    cout << "Height: " << bt.Height() << endl;

    cout << "Preorder Recursive: " << flush;
    bt.Preorder();
    cout << endl;

    cout << "Inorder Recursive: " << flush;
    bt.Inorder();
    cout << endl;

    cout << "Postorder Recursive: " << flush;
    bt.Postorder();
    cout << endl;

    cout << "Levelorder Iterative: " << flush;
    bt.Levelorder();
    cout << endl;

    cout << "Iterative Preorder: " << flush;
    bt.iterativePreorder();

    cout << "Iterative Inorder: " << flush;
    bt.iterativeInorder();

    cout << "Iterative Postorder: " << flush;
    bt.iterativePostorder();
    cout << endl;

    // Search
    int element = 60;
    cout << "Search for element " << element << endl;
    Node* temp = bt.iterativeSearch(element);
    if (temp != nullptr){

        cout << "Found element " << temp->data << endl;
    } else {
        cout << "Element not found" << endl;
    }

    // Search
    element = 99;
    cout << "Search for element " << element << endl;
    temp = bt.iterativeSearch(element);
    if (temp != nullptr){

        cout << "Found element " << temp->data << endl;
    } else {
        cout << "Element " << element << " not found" << endl;
    }
#endif

    //int pre[] = {3,9,20,-1,-1,15,7};
    //int pre[] = {0,8,1,-1,-1,3,2,-1,4,5,-1,-1,7,6};
    int pre[] = {50, 30, 20, 40, 70, 60, 80};	// first default BST in preorder form
    int n = sizeof(pre)/sizeof(pre[0]);
    bt.createBinaryTree(pre, n);
    cout << "Display Binary Tree InOrder: " << flush;
    bt.Inorder();
    cout << endl;

    cout << "Display Binary Tree LevelOrder: " << flush;
    bt.Levelorder();
    cout << endl;

    cout << "Vertical Position: " << flush;
    bt.setLevelOrderVerticalPosition(bt.getTree(), 0);
    cout << endl;


	auto pNodeMap = bt.getPositionMap();
	cout << "Position Node Map:" << endl;
	for (auto it=pNodeMap->begin(); it!=pNodeMap->end(); ++it) {
	    cout << it->first << " => " << it->second << '\n';
	}
    cout << endl;

	bt.loadMatrix();

	auto resultMatrix = bt.getPositionMatrix();
    printMatrix(*resultMatrix);


    return 0;
}
