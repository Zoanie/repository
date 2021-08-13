//============================================================================
// Name        : leetcode-fb-problems.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://leetcode.com/problems/
//============================================================================

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>	// INT_MIN
#include <algorithm>


using namespace std;

/*
 * K Closest Points to Origin
 *
We have a list of points on the plane.  Find the K closest points to the origin (0, 0).
(Here, the distance between two points on a plane is the Euclidean distance.)
You may return the answer in any order.  The answer is guaranteed to be unique
(except for the order that it is in.)

Example 1:

Input: points = [[1,3],[-2,2]], K = 1
Output: [[-2,2]]
Explanation:
The distance between (1, 3) and the origin is sqrt(10).
The distance between (-2, 2) and the origin is sqrt(8).
Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
We only want the closest K = 1 points from the origin, so the answer is just [[-2,2]].
Example 2:

Input: points = [[3,3],[5,-1],[-2,4]], K = 2
Output: [[3,3],[-2,4]]
(The answer [[-2,4],[3,3]] would also be accepted.)

Note:
1 <= K <= points.length <= 10000
-10000 < points[i][0] < 10000
-10000 < points[i][1] < 10000
 */
//https://leetcode.com/problems/k-closest-points-to-origin/
class SolutionKC1 {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        sort(points.begin(), points.end(),
        		[](vector<int> a, vector<int> b){
        			// equivalent: ( (a[0]*a[0]) + (a[1]*a[1]) < (b[0]*b[0]) + (b[1]*b[1]) )
        			return pow(a[0], 2) + pow(a[1], 2) < pow(b[0], 2) + pow(b[1], 2);
        		});

        vector<vector<int>> ans;

        for (int i = 0; i < K; i++) {
            ans.push_back(points[i]);
        }

        return ans;
    }
};

/*
 * Interesting use of a priority_queue.  This is a heap structure with the max element at the top.
 */
class SolutionKC2 {
public:
	struct compare
	{
		bool operator()(vector<int>&a,vector<int>&b)
		{
			return a[0]*a[0]+a[1]*a[1]>b[0]*b[0]+b[1]*b[1];
		}
	};
	vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
		priority_queue<vector<int>,vector<vector<int>>,compare>pq;

		for( vector<int>&point:points)
		{
			pq.push(point);
		}
		vector<vector<int>>ans;
		int index=0;
		while(!pq.empty()&&index!=K)
		{
			index++;
			ans.push_back(pq.top());
			pq.pop();
		}
		return ans;

	}
};
//https://leetcode.com/problems/subarray-sum-equals-k/
class SolutionSS {
public:
    int subarraySum(vector<int>& nums, int k) {
        int result = 0;
        unordered_map<int, int> seen;
        int runningSum = 0;
        for(int& num : nums){
            seen[runningSum]++;
            runningSum += num;

            result += seen[runningSum - k];
        }
        return result;
    }
};
// https://leetcode.com/problems/verifying-an-alien-dictionary/
class SolutionVAAD {
public:
    bool isAlienSorted(vector<string>& words, string order) {
    	int num_words = words.size();
        for (int i = 0; i < num_words - 1; i++) {
        string word1 = words[i];
        string word2 = words[i + 1];
        int i1 = 0, i2 = 0;
        while (word1[i1] == word2[i2]) {
            i1++, i2++;
        }
        int r = order.find(word1[i1]);
        int s = order.find(word2[i2]);
        if (r > s) return false;
    }
    return true;
    }
};

/*
 * Serialize and Deserialize Binary Tree
 *
Serialization is the process of converting a data structure or object into a sequence
of bits so that it can be stored in a file or memory buffer, or transmitted across a
network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on
how your serialization/deserialization algorithm should work. You just need to ensure that
a binary tree can be serialized to a string and this string can be deserialized to the
original tree structure.

Clarification: The input/output format is the same as how LeetCode serializes a binary tree.
You do not necessarily need to follow this format, so please be creative and come up with
different approaches yourself.

Example 1:
Input: root = [1,2,3,null,null,4,5]
Output: [1,2,3,null,null,4,5]

   1            <---
 /   \
2     3         <---
     / \
    5   4       <---

Example 2:
Input: root = []
Output: []
 */
// https://leetcode.com/problems/serialize-and-deserialize-binary-tree/discuss/74252/Clean-C%2B%2B-solution
struct TreeNode {
	int val;
    TreeNode *left;
    TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}

};

class Codec {
	stack <TreeNode*> stk;
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (root == nullptr) return "#";
        return to_string(root->val)+","+serialize(root->left)+","+serialize(root->right);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        return mydeserialize(data);
    }
    TreeNode* mydeserialize(string& data) {
        if (data[0]=='#') {
            if(data.size() > 1) data = data.substr(2);
            return nullptr;
        } else {
            TreeNode* node = new TreeNode(helper(data));
            node->left = mydeserialize(data);
            node->right = mydeserialize(data);
            return node;
        }
    }
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


private:
    int helper(string& data) {
        int pos = data.find(',');
        int val = stoi(data.substr(0,pos));
        data = data.substr(pos+1);
        return val;
    }
};

/*
 * Binary Tree Maximum Path Sum
 *
Given a non-empty binary tree, find the maximum path sum.

For this problem, a path is defined as any sequence of nodes from some starting node to any node
in the tree along the parent-child connections. The path must contain at least one node and does
not need to go through the root.

Example 1:
Input: [1,2,3]

       1
      / \
     2   3

Output: 6

Example 2:
Input: [-10,9,20,null,null,15,7]
	TreeNode *bTree = new TreeNode(-10, new TreeNode(9), new TreeNode(20, new TreeNode(15), new TreeNode(7) ));

   -10
   / \
  9  20
    /  \
   15   7

Output: 42
 */
// https://leetcode.com/problems/binary-tree-maximum-path-sum/
class SolutionMPS {
	int max_sum;

public:
	int max_gain(TreeNode* root)
	{
		if(!root)return 0;
		int l=max(max_gain(root->left),0);
		int r=max(max_gain(root->right),0);
		int new_price=root->val+l+r;
		max_sum=max(max_sum,new_price);
		return root->val+max(l,r);
	}
	int maxPathSum(TreeNode* root) {
		max_sum=INT_MIN;

		max_gain(root);
		return max_sum;
	}
};

/*
 * Word Break II
 *
Given a non-empty string s and a dictionary wordDict containing a list of non-empty words,
add spaces in s to construct a sentence where each word is a valid dictionary word. Return
all such possible sentences.

Note:

The same word in the dictionary may be reused multiple times in the segmentation.
You may assume the dictionary does not contain duplicate words.
Example 1:

Input:
s = "catsanddog"
wordDict = ["cat", "cats", "and", "sand", "dog"]
Output:
[
  "cats and dog",
  "cat sand dog"
]
Example 2:

Input:
s = "pineapplepenapple"
wordDict = ["apple", "pen", "applepen", "pine", "pineapple"]
Output:
[
  "pine apple pen apple",
  "pineapple pen apple",
  "pine applepen apple"
]
Explanation: Note that you are allowed to reuse a dictionary word.
 */
// https://leetcode.com/problems/word-break-ii/
class SolutionWB2 {
	// key = string, value
    unordered_map<string, vector<string>> u;

public:

    vector<string> wordBreak(string inputStr, vector<string>& wordDict) {
        vector<string> res;

    	cout << "Input string: " << inputStr << endl;


        if(u.find(inputStr)!=u.end())
        {
        	cout << "** Found string " << inputStr << " in map object" << endl;
            return u[inputStr];
        }

        for(auto word:wordDict){
        	cout << "Testing dictionary word '" << word << "'" << endl;
        	// For each word in the word vector 'dictionary':
            if(inputStr.substr(0, word.length())== word){
            	cout << "Found word '" << word <<"' at beginning of input string" << endl;
            	// The input string has a substring from offset 0 for word.length() bytes -- equal -- to the current dictionary word
                if(word.length()==inputStr.length()){
                	// dictionary word length is equal to the input string length - no more input string remaining
                	cout << "Found word match '" << inputStr << "' at end of input string " << inputStr << endl;
                    res.push_back(word);	// push the dictionary word into the result vector
                }
                else{
                	cout << "Continuing with remaining string '" << inputStr.substr(word.length()) << "'" << endl;
                    vector<string> temp = wordBreak(inputStr.substr(word.length()),wordDict);
                    cout << "Adding word '" << word << "' , with space to result" << endl;
                    for(auto t:temp)
                        res.push_back(word + " " + t);
                }
            }
        }


        u[inputStr]=res;
        return res;
    }
};
int main() {
	cout << "https://leetcode.com/problems/" << endl; // prints https://leetcode.com/problems/

	string s{"catsanddog"};

	vector<string> wordDict = {"cat", "cats", "and", "sand", "dog"};

	SolutionWB2 wb2;
	auto res = wb2.wordBreak(s, wordDict);

	cout << "Find result: " << endl;
	for(auto& rs : res)
		cout << rs << ", " << endl;

	return 0;

	TreeNode *maxSumTree = new TreeNode(-10, new TreeNode(9), new TreeNode(20, new TreeNode(15), new TreeNode(7) ));
	SolutionMPS mps;

	int maxSum = mps.maxPathSum(maxSumTree);
	cout << "Max Path Sum: " << maxSum << endl;

	return 0;

	Codec encoderDecoder;

	TreeNode *bTree = new TreeNode(1, new TreeNode(2), new TreeNode(3, new TreeNode(4), new TreeNode(5) ));
	cout << "Preorder Traversal: " << flush;
	encoderDecoder.iterativePreorder(bTree);
	cout << "Inorder Traversal: " << flush;
	encoderDecoder.iterativePreorder(bTree);

	string encoded = encoderDecoder.serialize(bTree);
	cout << "Encoded tree: '" << encoded << "'" << endl;
	TreeNode *decoded = encoderDecoder.deserialize(encoded);
	cout << "Decoded Preoder Traversal:" << endl;
	encoderDecoder.iterativePreorder(decoded);

	return 0;
}
