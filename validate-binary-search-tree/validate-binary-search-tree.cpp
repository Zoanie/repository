#include <iostream>
#include <queue>
#include <deque>

using namespace std;

/*

Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.


Example 1:

    2
   / \
  1   3

Input: [2,1,3]
Output: true

Example 2:

    5
   / \
  1   4
     / \
    3   6

Input: [5,1,4,null,null,3,6]
Output: false
Explanation: The root node's value is 5 but its right child's value is 4.


Example 3:

    10
   / \
  5   15
     / \
    6   20

Input: [10,5,15,null,null,6,20]

*/

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/*
 * Solution to validate BST will use a Breadth First Search (BFS) traversal.
 */
class Solution {
private:
	queue<TreeNode* > bfsQueue;
	int maxLeftNodeVal;
	int maxRightNodeVal;
	int rootNodeVal;

public:
	Solution(){
		maxLeftNodeVal = 0;
		maxRightNodeVal = 0;
		rootNodeVal = 0;
	}
	bool isValidBST(TreeNode* root) {
		TreeNode* currentNode;
		int depth = 0;

		if(root == nullptr)
			return true;
		rootNodeVal = root->val;
		bfsQueue.push(root);
		while(!bfsQueue.empty()) {
			currentNode = bfsQueue.front();
			bfsQueue.pop();

			if(depth++)
			{
				if(!testNode(currentNode))
					return false;
			}

			if(currentNode->left) {
				bfsQueue.push(currentNode->left);
			}
			if(currentNode->right) {
				bfsQueue.push(currentNode->right);
			}
		}
		return true;
	}

	bool testNode(TreeNode* node) {
		int nodeValue = node->val;
		if(node->left) {
			if(nodeValue <= rootNodeVal)
				return false;
			if(nodeValue <= (node->left->val) ) {	// left values should be less
				return false;
			}
		}
		if(node->right) {
			if(nodeValue >= rootNodeVal)
				return false;
			if(nodeValue >= (node->right->val) ) {	// right value should be greater
				return false;
			}
		}
		return true;
	}
};

int main(int argc, char **argv) {
	cout << "https://leetcode.com/problems/validate-binary-search-tree/" << endl;

	TreeNode *bTreeTest1 = new TreeNode(1, new TreeNode(1), new TreeNode(3));
	TreeNode *bTreeTest2 = new TreeNode(5, new TreeNode(1), new TreeNode(4, new TreeNode(3), new TreeNode(6) ));
	TreeNode *bTreeTest3 = new TreeNode(10, new TreeNode(5), new TreeNode(15, new TreeNode(6), new TreeNode(20) ));

	Solution TestBST;

	cout << "Test 1 - Binary Tree is ";
	if(!TestBST.isValidBST(bTreeTest1)) {
		cout << "invalid" << endl;
	}
	else {
		cout << "valid" << endl;
	}
	cout << "Test 2 - Binary Tree is ";
	if(!TestBST.isValidBST(bTreeTest2)) {
		cout << "invalid" << endl;
	}
	else {
		cout << "valid" << endl;
	}

	cout << "Test 3 - Binary Tree is ";
	if(!TestBST.isValidBST(bTreeTest3)) {
		cout << "invalid" << endl;
	}
	else {
		cout << "valid" << endl;
	}

	return 0;
}
