//============================================================================
// Name        : validate-BST.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <unordered_map>
#include<bits/stdc++.h>

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
 *
 * BST internal nodes each store a key greater than all the keys in the node's left subtree
 * and less than those in its right subtree.
 *
 * From Wikipedia: https://en.wikipedia.org/wiki/Binary_search_tree#Verification
 *
 * The condition needed to check at each node is:
 *   o If the node is the left child of its parent, then it must be smaller than (or equal to)
 *	   the parent and it must pass down the value from its parent to its right subtree to make
 *     sure none of the nodes in that subtree is greater than the parent.
 *   o If the node is the right child of its parent, then it must be larger than the parent
 *     and it must pass down the value from its parent to its left subtree to make sure none
 *     of the nodes in that subtree is lesser than the parent.
 *
 *
[10,5,15,null,null,6,20]
[3,null,30,10,null,null,15,null,45]
[]
[5,1,4,null,null,3,6]
[1,1]
[10,5,15,null,null,6,20]
[2,1,3]
[3,1,5,0,2,4,6]
[3,1,8,0,2,6,10,null,null,null,null,5,7,9,18]
[-2147483648,-2147483648]
[2147483647]
 */
class Solution {

public:
	Solution(){
	}
    bool isValidBST(TreeNode* root) {

        return testNode(root, nullptr, nullptr);
    }

	bool testNode(TreeNode* node, TreeNode* minNode, TreeNode* maxNode) {
		if(node == nullptr) {
			return true;
		}

        if(minNode != nullptr) {
            if(node->val <= minNode->val) {
                return false;
            }
        }

        if(maxNode != nullptr) {
            if(node->val >= maxNode->val) {
                return false;
            }
        }

		// Left side test must verify all nodes are smaller than parent AND
		// parent must pass down value as maximum node value
		if(node->left) {
			if(!testNode(node->left, minNode, node)) {
				return false;
			}
		}

		// Right side test must verify all nodes are greater than parent node AND
		// parent must pass down value as minimum node
		if(node->right) {
			if(!testNode(node->right, node, maxNode)) {
				return false;
			}
		}
		return true;
	}

};

// Utility function to create new Node
TreeNode *newTreeNode(int key)
{
	TreeNode *node = new TreeNode;
	node->val = key;
	node->left = node->right = nullptr;
    return (node);
}

// Creates tree from parent[0..n-1] and returns root of the created tree
TreeNode *createTree(int parent[], int n)
{
	// create an empty map
	unordered_map<int, TreeNode*> map;

	// create n new tree nodes each having value from 0 to n-1
	// and store them in a map
	for (int i = 0; i < n; i++)
		map[i] = newTreeNode(i);

	// represents root node of binary tree
	TreeNode *root = nullptr;

	// traverse the parent array and build the tree
	for (int i = 0; i < n; i++)
	{
		// if parent is -1, set root to current node having
		// value i (stored in map[i])
		if (parent[i] == -1)
		{
			root = map[i];
		}
		else
		{
			// get parent node for current node
			TreeNode *ptr = map[parent[i]];

			// if parent's left child is filled, map the node to its right child
			if (ptr->left)
				ptr->right = map[i];
			// if parent's left child is empty, map the node to it
			else
				ptr->left = map[i];
		}
	}

	// return root of the constructed tree
	return root;
}

// Utility function to do inorder traversal
void inorderTraversal(TreeNode *root)
{
    if (root != NULL)
    {
    	inorderTraversal(root->left);
        cout << root->val << " ";
        inorderTraversal(root->right);
    }
}

/*
[10,5,15,null,null,6,20]
[3,null,30,10,null,null,15,null,45]
[]
[1,1]
[10,5,15,null,null,6,20]
[2,1,3]
[3,1,5,0,2,4,6]
[3,1,8,0,2,6,10,null,null,null,null,5,7,9,18]
[-2147483648,-2147483648]
[2147483647]
[3,1,5,0,2,4,6,null,null,null,3]
 */
int main(int argc, char **argv) {
	cout << "https://leetcode.com/problems/validate-binary-search-tree/" << endl;

	//TreeNode *bTreeTest1 = new TreeNode(2, new TreeNode(1), new TreeNode(3));	// true
//	TreeNode *bTreeTest1 = new TreeNode(INT_MAX, new TreeNode(INT_MIN), nullptr);
//	TreeNode *bTreeTest2 = new TreeNode(1, new TreeNode(1), new TreeNode(1));	// false
//	TreeNode *bTreeTest3 = new TreeNode(5, new TreeNode(1), new TreeNode(4, new TreeNode(3), new TreeNode(6) ));	// false
//	TreeNode *bTreeTest4 = new TreeNode(10, new TreeNode(5), new TreeNode(15, new TreeNode(6), new TreeNode(20) ));	// false
//	TreeNode *bTreeTest5 = new TreeNode(3, new TreeNode(1, nullptr, new TreeNode(2)), new TreeNode(5, new TreeNode(4), new TreeNode(6)) );	// true
//	TreeNode *bTreeTest6 = new TreeNode(3, nullptr, new TreeNode(30, new TreeNode(10, nullptr, new TreeNode(15, nullptr, new TreeNode(45))), nullptr));	// true
	TreeNode *bTreeTest6 = new TreeNode(3, new TreeNode(1, new TreeNode(0), new TreeNode(2, nullptr, new TreeNode(3))), new TreeNode(5, new TreeNode(4), new TreeNode(6)) );	// true
	TreeNode *bTreeTest7 = new TreeNode(INT_MAX, new TreeNode(INT_MIN), nullptr);

	TreeNode *bTreeTest1 = new TreeNode(3, new TreeNode(2, new TreeNode(1), new TreeNode(INT_MIN)), nullptr);



	int testCase[] = {-1,3,1,5,0,2,4,6};
	int numNodes = sizeof testCase / sizeof testCase[0];
	TreeNode *root = createTree(testCase, numNodes);
	cout << "Inorder Traversal:" << endl;
	inorderTraversal(root);
	cout << endl;

	Solution TestBST;

	cout << "Test 1 - Binary Tree is ";
	if(!TestBST.isValidBST(bTreeTest1)) {
		cout << "invalid" << endl;
	}
	else {
		cout << "valid" << endl;
	}
//
//	cout << "Test 2 - Binary Tree is ";
//	if(!TestBST.isValidBST(bTreeTest2)) {
//		cout << "invalid" << endl;
//	}
//	else {
//		cout << "valid" << endl;
//	}
//
//	cout << "Test 3 - Binary Tree is ";
//	if(!TestBST.isValidBST(bTreeTest3)) {
//		cout << "invalid" << endl;
//	}
//	else {
//		cout << "valid" << endl;
//	}
//
//	cout << "Test 4 - Binary Tree is ";
//	if(!TestBST.isValidBST(bTreeTest4)) {
//		cout << "invalid" << endl;
//	}
//	else {
//		cout << "valid" << endl;
//	}
//
//	cout << "Test 5 - Binary Tree is ";
//	if(!TestBST.isValidBST(bTreeTest5)) {
//		cout << "invalid" << endl;
//	}
//	else {
//		cout << "valid" << endl;
//	}
//
	cout << "Test 6 - Binary Tree is ";
	if(!TestBST.isValidBST(bTreeTest6)) {
		cout << "invalid" << endl;
	}
	else {
		cout << "valid" << endl;
	}

	cout << "Test 7 - Binary Tree is ";
	if(!TestBST.isValidBST(bTreeTest7)) {
		cout << "invalid" << endl;
	}
	else {
		cout << "valid" << endl;
	}

	return 0;
}
