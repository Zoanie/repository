//============================================================================
// Name        : merge-k-sorted-lists.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://leetcode.com/problems/merge-k-sorted-lists/
//============================================================================

#include <iostream>
#include <vector>
#include <list>
#include <set>

using namespace std;

/*
 *
You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.

Merge all the linked-lists into one sorted linked-list and return it.

Example 1:

Input: lists = [[1,4,5],[1,3,4],[2,6]]
Output: [1,1,2,3,4,4,5,6]
Explanation: The linked-lists are:
[
  1->4->5,
  1->3->4,
  2->6
]
merging them into one sorted list:
1->1->2->3->4->4->5->6

Constraints:

k == lists.length
0 <= k <= 10^4
0 <= lists[i].length <= 500
-10^4 <= lists[i][j] <= 10^4
lists[i] is sorted in ascending order.
The sum of lists[i].length won't exceed 10^4.
 */
/**
 * Definition for singly-linked list.
 */
struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};
ListNode *TestCaseList1 = new ListNode(1, new ListNode(4, new ListNode(5)));
ListNode *TestCaseList2 = new ListNode(1, new ListNode(3, new ListNode(4)));
ListNode *TestCaseList3 = new ListNode(2, new ListNode(6));

vector<ListNode*> TestCaseLoL{TestCaseList1, TestCaseList2, TestCaseList3};

class Solution {
	multiset<int> ListData;
	ListNode* ReturnList;

public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {

    	if(lists.empty()) {
    		cout << "Huh? Input vector is empty!" << endl;
    		return nullptr;
    	}

    	for(auto& li : lists) {
    		insertListData(li);
    	}

    	return createReturnList();
    }

    int insertListData(ListNode *pNode) {
    	auto it = ListData.cbegin();

    	cout << "Inserting list [";
    	while(pNode != nullptr) {
    		cout << pNode->val;
        	it = ListData.emplace_hint(it, pNode->val);
        	pNode = pNode->next;
        	if(pNode != nullptr)
        		cout << ", ";
    	}
    	cout << "]" << endl;

    	return (ListData.size());
    }

    ListNode* createReturnList() {
    	if(0 == ListData.size())
    		return nullptr;

    	auto cit = ListData.begin();

    	ReturnList = new ListNode;
    	ListNode *pNode = ReturnList;
    	pNode->val = *cit++;
    	pNode->next = nullptr;
    	ListNode *lastNode = pNode;

    	cout << "Sorted List: [" << *cit;
		if(cit != ListData.cend()) {
			cout << ", ";
		}

    	// Insert the sorted list data at the end for fastest insertion
    	for (; cit != ListData.cend(); ) {
    		pNode = new ListNode;
    		pNode->val = *cit;
    		cout << pNode->val;
    		pNode->next = nullptr;
    		lastNode->next = pNode;
    		lastNode = pNode;
    		++cit;
    		if(cit != ListData.cend()) {
    			cout << ", ";
    		}
    		else {
    			break;
    		}
    	}
		cout << "]" << endl;

    	return ReturnList;
    }

#ifdef THE_TAKES_TOO_LONG_WAY
    // This is for the long way home method of merging lists
    void merge2lists(ListNode *px, ListNode *py[], ListNode *pz[]) {
    	ListNode *plast = nullptr;
    	bool first = true;
        int i = 0;
        int j = 0;
        int k = 0;
        while (p != nullptr && py != nullptr) {
        	pz = new ListNode;
            pz->next = nullptr;
            if(first) {
        		first = false;
        		plast = pz;
        	}

            if (px->val < py->val){
                pz->val = px->val;
                px = px->next;
                plast = pz;

            } else {
                z[k++] = y[j++];
            }
        }
        while (i < m){
            z[k++] = x[i++];
        }
        while (j < n){
            z[k++] = x[j++];
        }
    }

    struct ListNode* searchList(ListNode *p, int key) {
    	while(p!=nullptr) {
    		if(key==p->val) {
    			return p;
    		}
    	}
    	return NULL;
    }

    struct ListNode* getNext(ListNode *p) {
    	if(p) {
    		return p->next;
    	}
    }
#endif

};
int main() {
	cout << "https://leetcode.com/problems/merge-k-sorted-lists/" << endl; // prints https://leetcode.com/problems/merge-k-sorted-lists/

	Solution MergeKLists;

	auto& lol = TestCaseLoL;
	MergeKLists.mergeKLists(lol);

	return 0;
}
