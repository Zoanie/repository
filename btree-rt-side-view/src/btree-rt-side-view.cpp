//============================================================================
// Name        : btree-rt-side-view.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : We don' need no badges
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <algorithm>
#include <functional>
#include <bits/stdc++.h>

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
Given a binary tree, imagine yourself standing on the right side of it, return the
values of the nodes you can see ordered from top to bottom.

Example:

Input: [1,2,3,null,5,null,4]
Output: [1, 3, 4]
Explanation:

   1            <---
 /   \
2     3         <---
 \     \
  5     4       <---
*/

/*
 * The problem is asking for a level order traversal of a binary tree.
 */
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <functional>
#include <bits/stdc++.h>

using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
private:
	vector<int> ResultVector;
	map<int, int>ResultMap;
	int map_level;

public:
	Solution() {
		map_level = 0;
	}

    vector<int> rightSideView(TreeNode* root) {
        ResultVector.clear();
    	if(root == nullptr)
    		return ResultVector;

    	//addToResultVector(root->val);
        ResultVector.push_back(root->val);

    	if(root->right)
    	{
    		map_level = 0;
    		walkDownBtree(root->right);
    		map_level = 0;
    		walkDownBtree(root->left);
    	}
    	else
    	{
    		map_level = 0;
    		walkDownBtree(root->left);
    	}

    	for(auto it = ResultMap.begin(); it != ResultMap.end(); it++)
    	{
        	//addToResultVector(it->second);
            ResultVector.push_back(it->second);
    	}

    	displayResultVector("Result");
    	return ResultVector;
    }

    void walkDownBtree(TreeNode* root)
    {
    	if(root == nullptr)
    		return;

    	map_level++;
        int current_level = map_level;

    	if(root->right)
    	{
            //addToResultMap(map_level, root->val);
            ResultMap.insert(pair<int, int>(map_level, root->val));
        	walkDownBtree(root->right);
            map_level = current_level;
        	return walkDownBtree(root->left);
    	}
    	else if(root->left)
    	{
            //addToResultMap(map_level, root->val);
            ResultMap.insert(pair<int, int>(map_level, root->val));
        	return walkDownBtree(root->left);
    	}
    	else
    	{
            //addToResultMap(map_level, root->val);
            ResultMap.insert(pair<int, int>(map_level, root->val));
    	}

    }

    void addToResultVector(int val)
    {
    	ResultVector.push_back(val);
    }

    void addToResultMap(int level, int val)
    {
    	ResultMap.insert(pair<int, int>(level, val));
    }

    void displayResultVector(const string name)
    {
    	vector<int>& numsVec = ResultVector;

    	int numCount = numsVec.size();
    	cout << name << ": " << "[";
    	for(auto n : numsVec)
    	{
    		cout << n;
    		if(--numCount)
    			cout << ",";
    	}
    	cout << "]" << endl;
    }

};

/*
   1            <---
 /   \
2     3         <---
 \     \
  5     4       <---
 */
int main() {
	cout << "https://leetcode.com/problems/binary-tree-right-side-view/" << endl;

	TreeNode *bTree = new TreeNode(1, new TreeNode(2, nullptr, new TreeNode(5)), new TreeNode(3, nullptr, new TreeNode(4) ));

	Solution BtreeRtSideView;

	BtreeRtSideView.rightSideView(bTree);

	return 0;
}
