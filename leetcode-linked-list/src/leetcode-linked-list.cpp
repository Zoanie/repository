//============================================================================
// Name        : leetcode-linked-list.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://leetcode.com/explore/interview/card/top-interview-questions-easy/93/linked-list
//============================================================================

#include <iostream>
#include<bits/stdc++.h>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void displayNode(ListNode* list)
{
	if(list == nullptr)
		return;

	cout << list->val;

	if(list->next != nullptr)
	{
		cout << " -> ";
		displayNode(list->next);
	}
}

void displayList(ListNode* list)
{
    cout << "List: (";
	displayNode(list);
    cout << ")" << endl;
}


/*
 * Delete Node in a Linked List
 *
Write a function to delete a node in a singly-linked list. You will not be given access
to the head of the list, instead you will be given access to the node to be deleted directly.

It is guaranteed that the node to be deleted is not a tail node in the list.

Example 1:
Input: head = [4,5,1,9], node = 5
Output: [4,1,9]
Explanation: You are given the second node with value 5, the linked list should become 4 -> 1 -> 9 after calling your function.

Example 2:
Input: head = [4,5,1,9], node = 1
Output: [4,5,9]
Explanation: You are given the third node with value 1, the linked list should become 4 -> 5 -> 9 after calling your function.

Example 3:
Input: head = [1,2,3,4], node = 3
Output: [1,2,4]

Example 4:
Input: head = [0,1], node = 0
Output: [1]

Constraints:

The number of the nodes in the given list is in the range [2, 1000].
-1000 <= Node.val <= 1000
The value of each node in the list is unique.
The node to be deleted is in the list and is not a tail node
 */
// https://leetcode.com/explore/interview/card/top-interview-questions-easy/93/linked-list/553/
void deleteNode(ListNode* node) {
	ListNode* nextNode = node->next;
	node->next = nextNode->next;
	node->val = nextNode->val;
	delete nextNode;
}

/*
 * Remove Nth Node From End of List
 *
Given the head of a linked list, remove the nth node from the end of the list and return its head.
Follow up: Could you do this in one pass?

Example 1:
Input: head = [1,2,3,4,5], n = 2
Output: [1,2,3,5]

Example 2:
Input: head = [1], n = 1
Output: []

Example 3:
Input: head = [1,2], n = 1
Output: [1]
 */
ListNode* removeNthFromEnd(ListNode* head, int n) {
    queue<ListNode*> nodeQueue;
    ListNode* nextNode = head;
    ListNode* nthNode = head;
    ListNode* prevNode = head;
    int nodeCount = 1;
    while(nextNode) {
    	if (nextNode->next)
    		printf("node %d has next\n", nextNode->val);
    	else
    		printf("node %d is tail\n", nextNode->val);

        nodeQueue.push(nextNode);
        nextNode = nextNode->next;
        if(++nodeCount > n) {
            prevNode = nthNode;
            nthNode = nodeQueue.front();
            nodeQueue.pop();
            printf("nthNode=%d, prevNode=%d\n", nthNode->val, prevNode->val);
        }
    }
    printf("last nthNode is %d\n", nthNode->val);
    if(nthNode == head) {
    	printf("Deleting head=%d\n", head->val);
        nextNode = head->next;
        delete head;
        head = nextNode;
    }
    else {
        if(prevNode) {
        	printf("prev nthNode is %d\n", prevNode->val);
        	prevNode->next = nthNode->next;
        	delete nthNode;
        }
        else {
            printf("prev nthNode is null!");
        }
    }
    return head;
}

/*
 * Palindrome Linked List
 * https://leetcode.com/problems/palindrome-linked-list/
 *
Given the head of a singly linked list, return true if it is a palindrome.

Test data:
[1,0,1]
[1,0,0]
[]
[-1,1]
[-126,-126]
[1,2]
[0,0]
[1,2,2,1]
[1,2,2,2,1]
[1,2,3,4,5,4,3,2,1]
[1,2,3,4,5,4,3,2]
[-16557,-8725,-29125,28873,-21702,15483,-28441,-17845,-4317,-10914,-10914,-4317,-17845,-28441,15483,-21702,28873,-29125,-8725,-16557]
[-31900,22571,-31634,19735,13748,16612,-28299,-16628,9614,-14444,-14444,9614,-16628,-31900,16612,13748,19735,-31634,22571,-28299]
 */
bool isPalindromeV1(ListNode* head)
{
    if((head == nullptr) || (head->next == nullptr)) return true;

    ListNode* prevNode = nullptr;
    ListNode* currNode = head;
    ListNode* nextNode = head->next;
    int currVal = head->val;
    int listSum = currVal;
    int nodeCount = 1;
    bool midway = false;

    printf("Count = %d, node = %d\n", nodeCount, currNode->val);
    printf("initial listSum = %d\n", listSum);
    while(nextNode != nullptr) {

        prevNode = currNode;
        currNode = nextNode;
        nextNode = currNode->next;

        // Test for midway node
        if(!midway) {
        	if(prevNode && nextNode) {
        		if(prevNode->val == nextNode->val) {
        			midway = true;
        			printf("Midway found, skipping middle value %d\n", currNode->val);
        			prevNode = currNode;
        			currNode = nextNode;
        			nextNode = currNode->next;
        		}
        	}
        	if(!midway && currNode && nextNode) {
        		if(currNode->val == nextNode->val) {
        			// skip middle values
        			midway = true;
        			currVal = currNode->val;
        			while(nextNode && (currNode->val == nextNode->val)) {
        				printf("skipping middle value %d\n", currNode->val);
        				prevNode = currNode;
        				currNode = nextNode;
        				nextNode = currNode->next;
        			}
        			if(nextNode) {
        				printf("skipping last middle value %d\n", currNode->val);
        				prevNode = currNode;
        				currNode = nextNode;
        				nextNode = currNode->next;
        			}
        		}
        	}
        }

        currVal = currNode->val;
        printf("Count = %d, node = %d\n", ++nodeCount, currNode->val);

        // Before midway we increment node value sum
        // At midway we skip modifying the node value sum
        // After midway we decrement node value sum
        if(midway){
            listSum -= currVal;
            printf("decrement listSum -= %d, sum = %d\n", currVal, listSum);
        }
        else {
            listSum += currVal;
            printf("increment listSum += %d, sum = %d\n", currVal, listSum);
        }
    }
    printf("Final sum = %d, midway seen = %d\n", listSum, midway);
    return (listSum == 0 && midway);
}

//
bool isPalindromeV2(ListNode* head)
{
    if((head == nullptr) || (head->next == nullptr)) return true;

    ListNode* currNode = head;
    ListNode* nextNode = head;
    int nodeCount = 0;

    while(nextNode != nullptr) {
        currNode = nextNode;
        nextNode = currNode->next;
    	nodeCount++;
    }
    vector<int>nodeVec(nodeCount);
    nextNode = head;
	for(int i=0; i<nodeCount; i++) {
		currNode = nextNode;
		nodeVec[i] = currNode->val;
        nextNode = currNode->next;
	}

	for(int i=0; i< nodeCount/2; i++) {
		if(nodeVec[i] != nodeVec[nodeCount - 1 - i]) {
			return false;
		}
	}
	return true;
}

/*
 * Tortoise & Hare design
 *
 * We do not need to worry about linked lists with a middle value (i.e. an odd number of nodes)
 * because there is no "mirror" element to match it up with. As such, in a linked list like
 * [1, 2, 3, 2, 1], we only need to reverse the [2, 1] "second half" into [1, 2] and then match
 * it up with the start of the list. In this example, the 3 could be literally any value and it
 * would still hold (as it is a fixed point).
 */
bool isPalindrome(struct ListNode *head)
{
    // When the fast pointer (hare) reaches
	// the end of the list, the slow pointer
	// (tortoise) will be halfway there
    struct ListNode *fast = head;
    struct ListNode *slow = head;
    while (fast && fast->next) {
    	// The fast node pointer takes 2 nodes for every 1 node the slow node pointer takes
        fast = fast->next->next;
        slow = slow->next;
    }

	// Take the list at the halfway point (the slow list pointer) and
	// split it in two by making the midthen reverse it in place
    struct ListNode *prev = NULL;
    struct ListNode *curr = slow;
    struct ListNode *next = NULL;
    printf("\nReversing list:\n");
    while (curr) {
        if(curr->next != NULL) printf("next=%d, \n", curr->next->val);
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    printf("\nReversed ");
    displayList(prev);

	// Compare the original head of the list
	// with the reversed second half. If at any
	// point there is inequality, return false.
    while (prev) {
        if (prev->val != head->val) {
            return false;
        }
        prev = prev->next;
        head = head->next;
    }

    return true;
}

int main() {
	cout << "https://leetcode.com/explore/interview/card/top-interview-questions-easy/93/linked-list" << endl;
	// Setup for isPalindrome()
	/*
	 *
[1,0,1]
[1,0,0]
[]
[0,0]
[-1,1]
[1,2]
[1,2,2,1]
[1,2,3,4,5,4,3,2,1]
[1,2,3,4,5,4,3,2]
[1,2,2,2,1]
[-16557,-8725,-29125,28873,-21702,15483,-28441,-17845,-4317,-10914,-10914,-4317,-17845,-28441,15483,-21702,28873,-29125,-8725,-16557]
[-31900, 22571,-31634, 19735, 13748, 16612, -28299, -16628, 9614, -14444, -14444, 9614, -16628, -31900, 16612, 13748, 19735, -31634, 22571, -28299]
	 *
	 */
	//ListNode *pPal1 = new ListNode(1, new ListNode(0, new ListNode(1)));
	//ListNode *pPal2 = new ListNode(-1, new ListNode(1));
	//ListNode *pPal3 = new ListNode(1, new ListNode(2));
	//ListNode *pPal4 = new ListNode(1, new ListNode(2, new ListNode(2, new ListNode(1))));
	//ListNode *pPal5 = new ListNode(1, new ListNode(2, new ListNode(2, new ListNode(2, new ListNode(1)))));

	ListNode *pPal6 =
			new ListNode(-16557, new ListNode(-8725, new ListNode(-29125, new ListNode(28873, new ListNode(-21702,
			new ListNode(15483, new ListNode(-28441, new ListNode(-17845, new ListNode(-4317, new ListNode(-10914,
			new ListNode(-10914, new ListNode(-4317, new ListNode(-17845, new ListNode(-28441, new ListNode(15483,
			new ListNode(-21702, new ListNode(28873, new ListNode(-29125, new ListNode(-8725, new ListNode(-16557)
				)))))))))))))))))));

	ListNode *pPal7 =
			new ListNode(-31900, new ListNode(22571, new ListNode(-31634, new ListNode(19735, new ListNode(13748,
			new ListNode(16612, new ListNode(-28299, new ListNode(-16628, new ListNode(9614, new ListNode(-14444,
			new ListNode(-14444, new ListNode(9614, new ListNode(-16628, new ListNode(-31900, new ListNode(16612,
			new ListNode(13748, new ListNode(19735, new ListNode(-31634, new ListNode(22571, new ListNode(-28299)
				)))))))))))))))))));

//
	//ListNode *pPal7 = new ListNode(0, new ListNode(0));

	cout << "Test Palindrome ";
	displayList(pPal6);
	cout << "List is palindrome: " << boolalpha << isPalindrome(pPal6) << endl;
    return 0;

	cout << "Test Palindrome ";
	displayList(pPal7);
	cout << "List is palindrome: " << boolalpha << isPalindrome(pPal7) << endl;
	return 0;

	// Setup for removeNthFromEnd()
	ListNode *pDisplayList = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
	cout << "Before ";
	displayList(pDisplayList);
	for(int n=1; n<=5; n++) {
		ListNode *pListNode = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
		cout << "Removing n = " << n << endl;
		pListNode = removeNthFromEnd(pListNode, n);
		displayList(pListNode);
	}
	return 0;
}
