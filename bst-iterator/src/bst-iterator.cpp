//============================================================================
// Name        : bst-iterator.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://leetcode.com/problems/binary-search-tree-iterator/
//============================================================================

#include <iostream>
#include <stack>
#include <queue>
#include <climits>	// INT_MAX

using namespace std;

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
 ["BSTIterator","next","next","hasNext","next","hasNext","next","hasNext","next","hasNext"]
 [[[7,3,15,null,null,9,20]],[null],[null],[null],[null],[null],[null],[null],[null],[null]]
 */

class Tree {
private:
	TreeNode* root;
	stack<TreeNode*>stk;

public:
	Tree();
	~Tree();

	TreeNode* getRootNode() { return root; }
	void setRootNode(TreeNode* node) { root = node; }

	void iterativePreorder(TreeNode *p) {

		while (p != nullptr || ! stk.empty()){
			if (p != nullptr){
				cout << p->val << ", " << flush;
				stk.emplace(p);
				p = p->left;
			} else {
				p = stk.top();
				stk.pop();
				p = p->right;
			}
		}
		cout << endl;
	}

	void iterativeInorder(TreeNode *p) {

		while (p != nullptr || ! stk.empty()){
			if (p != nullptr){
				stk.emplace(p);
				p = p->left;
			} else {
				p = stk.top();
				stk.pop();
				cout << p->val << ", " << flush;
				p = p->right;
			}
		}
		cout << endl;
	}

	void insertNode(int key) {

		TreeNode* t = getRootNode();
		TreeNode* p;
		TreeNode* r;

		// root is empty
		if (getRootNode() == nullptr)
		{
			p = new TreeNode(key);
			setRootNode(p);
			return;
		}

		// First find the correct parent to link the new key
		while(t != nullptr)
		{
			r = t;
			if (key < t->val){
				t = t->left;
			} else if (key > t->val){
				t = t->right;
			} else {
				return;
			}
		}

		// Now t points at NULL and r points at insert location
		p = new TreeNode(key);

		if (key < r->val){
			r->left = p;
		} else {
			r->right = p;
		}

	}

	void deletePostorder(TreeNode *p);
	void deletePostorder() { return deletePostorder(root); }

};

Tree::Tree() {
	root = nullptr;
}

Tree::~Tree() {
	// TODO
	deletePostorder(root);
}

void Tree::deletePostorder(TreeNode *p) {
	if (p != nullptr){
		deletePostorder(p->left);
		deletePostorder(p->right);
		// cout << p->val << ", " << flush;	// Output deleted Node...
		delete p;
	}
}


class BSTIterator {
	stack<TreeNode*> stk;
	queue<int>nextQueue;

public:
	BSTIterator(TreeNode* root) {
		TreeNode *pNode = root;

		// now find next value to setup
		while(pNode != nullptr || !stk.empty()) {
			if(pNode != nullptr)
			{
				// keep going left toward the next smallest number on this subtree
				stk.emplace(pNode);
				pNode = pNode->left;
			} else {
				// At this point there are no more nodes to traverse, p is null.
				// Pop the last node off the stack. The stack has valid nodes that have a val data attribute.
				pNode = stk.top();
				stk.pop();

				// Queue up the node for the iterator
				nextQueue.emplace(pNode->val);
				pNode = pNode->right;
			}
		}
	}

	/** @return the next smallest number */
	int next() {
		static int nextVal = 0;

		if(nextQueue.empty()) {
			return nextVal;
		}
		nextVal = nextQueue.front();
		nextQueue.pop();

		return nextVal;
	}

	/** @return whether we have a next smallest number */
	bool hasNext() {
		if(nextQueue.empty()) {
			return false;
		}
		return true;
	}

};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
int main() {
	cout << "https://leetcode.com/problems/binary-search-tree-iterator/" << endl; // prints https://leetcode.com/problems/binary-search-tree-iterator/
	Tree BST;
	BST.insertNode(7);
	BST.insertNode(3);
	BST.insertNode(15);
	BST.insertNode(9);
	BST.insertNode(20);

	BSTIterator bstItr = BSTIterator(BST.getRootNode());
	cout << "Test Tree preorder: " << endl;
	BST.iterativePreorder(BST.getRootNode());
	cout << "Calling sequence: ";
	bstItr.next();
	bstItr.next();
	bstItr.hasNext();
	bstItr.next();
	bstItr.hasNext();
	bstItr.next();
	bstItr.hasNext();
	bstItr.next();
	bstItr.hasNext();
	cout << endl;
	return 0;
}
