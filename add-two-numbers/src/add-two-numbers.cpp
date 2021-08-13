//============================================================================
// Name        : add-two-numbers.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : Robusto hand-rolled code
// Description : C++ code problem & solution from leetcode.com
//============================================================================

#include <iostream>
#include <vector>
#include <list>
#include <array>
#include <math.h>
#include <boost/lexical_cast.hpp>
#include <mutex>

using namespace std;

/**
 * You are given two non-empty linked lists representing two non-negative integers.
 * The digits are stored in reverse order and each of their nodes contain a single digit.
 *
 * Add the two numbers and return it as a linked list.
 *
 * You may assume the two numbers do not contain any leading zero, except the number 0 itself.
 *
 * Example:
 *
 * Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
 * Output: 7 -> 0 -> 8
 * Explanation: 342 + 465 = 807.
 *
 * Notes: There is some info available for the case of adding big number strings here:
 * https://web.stanford.edu/class/archive/cs/cs106b/cs106b.1186/lectures/08-Fractals/code/expressions/lib/StanfordCPPLib/util/biginteger.cpp
 */
string padLeft(const string& s, int length) {
    size_t lenS = s.length();
    if ((int) lenS < length) {
        // left-pad numbers with 0s to be the same length as needed
        string scopy = s;
        scopy.insert(0, (length - lenS), '0');
        return scopy;
    } else {
        return s;
    }
}

string addTwoStrings(const string& n1, const string& n2) {
    // sum variable to store result;
    // left-pad numbers with 0s to be the same length as needed
    int digits = (int) (n1.length() > n2.length() ? n1.length() : n2.length());
    string sum = padLeft("", digits);
    string n1copy = padLeft(n1, digits);
    string n2copy = padLeft(n2, digits);

    // add each digit pair
    int carry = 0;
    for (int i = n1copy.length() - 1; i >= 0; --i) {
        sum[i] = (carry + (n1copy[i] - '0') + (n2copy[i] - '0')) + '0';
        if (i != 0) {
            if (sum[i] > '9') {
                sum[i] -= 10;
                carry = 1;
            } else {
                carry = 0;
            }
        }
    }

    if (sum[0] > '9') {
        // top digit carried over; make an additional digit at front
        sum[0] -= 10;
        sum.insert(0, (size_t) 1, '1');
    }

    return sum;
}
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

class Solution {
private:
	ListNode *resultList;

public:
	Solution() {
		resultList = nullptr;
	}

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        cout << "Input: (";
        displayNode(l1);
        cout << ") + (";
        displayNode(l2);
        cout << ")" << endl;

        /*
         * If the list of numbers is larger 9 numbers, or the result is beyond 64 bits, the method of
         * adding integers is not going to work.
         */
        int digitsValSum = 0;
        int carryVal = 0;
        ListNode* addNode1 = l1;
        ListNode* addNode2 = l2;
    	int val1=0;
    	int val2=0;
		resultList = new ListNode();
		ListNode* addResultNode = resultList;

		do
        {
        	val1 = val2 = 0;

        	//cout << "Adding [";
        	if(addNode1 != nullptr)
        	{
        		val1 = addNode1->val;
        		//cout << val1;
        	}
        	else
        	{
        		//cout << "0";
        	}
        	//cout << "+";
        	if(addNode2 != nullptr)
        	{
        		val2 = addNode2->val;
        		//cout << val2;
        	}
        	else
        	{
        		//cout << "0";
        	}

        	digitsValSum = val1 + val2 + carryVal;
        	if(digitsValSum >= 10)
        	{
        		carryVal = 1;
        		digitsValSum -= 10;
        	}
        	else
        	{
        		carryVal = 0;
        	}
        	addResultNode->val = digitsValSum;

        	//cout << "+" << carryVal << "c] => [" << digitsValSum << "]" << endl;

    		if(addNode1 != nullptr)
    			addNode1 = addNode1->next;
    		if(addNode2 != nullptr)
    			addNode2 = addNode2->next;
    		if(carryVal || (addNode1 != nullptr || addNode2 != nullptr))
    		{
    			addResultNode->next = new ListNode();
    			addResultNode = addResultNode->next;
    		}

        } while(carryVal || (addNode1 != nullptr || addNode2 != nullptr));


		addResultNode->next = nullptr;

		cout << "Output: ";
        displayNode(resultList);
        cout << endl;

        cout << "Explanation: ";
        displayReverseListNodeDigits(l1);
        cout << " + ";
        displayReverseListNodeDigits(l2);
        cout << " = ";
        displayReverseListNodeDigits(resultList);
        cout << endl;

        return (resultList);
    }


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

    void displayListNodeDigits(ListNode* list)
    {
    	if(list == nullptr)
    		return;

    	cout << list->val;
    	if(list->next != nullptr)
    	{
    		displayListNodeDigits(list->next);
    	}
    }

    void displayReverseListNodeDigits(ListNode* list)
    {
    	// Interesting.  This design is post-order traversal.
    	if(list == nullptr)
    		return;

    	if(list->next != nullptr)
    	{
    		displayReverseListNodeDigits(list->next);
    	}
    	cout << list->val;
    }

};

unsigned long long int getReverseNumber(ListNode* list, int level)
{
	unsigned long long int numBuilder = 0;

	if(list == nullptr)
		return list->val * pow(10, level);

	if(list->next != nullptr)
	{
		numBuilder = getReverseNumber(list->next, level+1);
	}
	numBuilder = numBuilder + (list->val * pow(10, level));

	return numBuilder;
}

void putReverseNumber(ListNode* list, unsigned long long int number)
{
	if(number >= 10)
	{
    	list->next = new(ListNode);
    	list->val = number % 10;
    	number = number / 10;
    	putReverseNumber(list->next, number);
    	return;
	}

	list->val = number;
	return;
}

list<int> l1{2, 4, 3};
list<int> l2{5, 6, 4};
list<int> lResult;

int main() {
#ifdef TESTING
	Solution Add2Numbers;

	ListNode *p1ListNode = new ListNode(2, new ListNode(4, new ListNode(3)));
	ListNode *p2ListNode = new ListNode(5, new ListNode(6, new ListNode(4)));
	Add2Numbers.addTwoNumbers(p1ListNode, p2ListNode);
	cout << endl;

	ListNode *p3ListNode = new ListNode(6, new ListNode(3, new ListNode(5)));
	ListNode *p4ListNode = new ListNode(5, new ListNode(6, new ListNode(4)));
	Add2Numbers.addTwoNumbers(p3ListNode, p4ListNode);
	cout << endl;

	ListNode *p5ListNode = new ListNode(9);
	ListNode *p6ListNode = new ListNode(1);
	Add2Numbers.addTwoNumbers(p5ListNode, p6ListNode);
	cout << endl;

	ListNode *p7ListNode = new ListNode(9);
	ListNode *p8ListNode = new ListNode(1, new ListNode(9, new ListNode(9, new ListNode(9, new ListNode(9, new ListNode(9, new ListNode(9, new ListNode(9, new ListNode(9, new ListNode(9))))))))));
	cout << endl;

	Add2Numbers.addTwoNumbers(p7ListNode, p8ListNode);

    return 0;

    /*
     * What follows is another method of adding 2 numbers using STL lists and boost lib lexical_cast()
     */
	// cout << "\nhttps://leetcode.com/problems/add-two-numbers/" << endl;

	// Display input data
	cout << "Input: (";
	auto it = l1.begin();
	do {
		cout << *it++;
		if(it != l1.end())
			cout << " -> ";
	} while (it != l1.end());

	cout << ") + (";
	it = l2.begin();
	do {
		cout << *it++;
		if(it != l2.end())
			cout << " -> ";
	} while (it != l2.end());
	cout << ")" << endl;

	int index = l1.size() - 1;
	int powerOfTen = pow(10, index);
	int l1Number = 0;

	for(auto it = l1.rbegin(); it != l1.rend(); it++)
	{
		//cout << "l1[" << index-- << "] = " << *it << endl;
		l1Number += *it * powerOfTen;
		//cout << "l1 = " << l1Number << endl;
		powerOfTen /= 10;
	}

	index = l1.size() - 1;
	powerOfTen = pow(10, index);
	int l2Number = 0;

	for(auto it = l2.rbegin(); it != l2.rend(); it++)
	{
		//cout << "l2[" << index-- << "] = " << *it << endl;
		l2Number += *it * powerOfTen;
		//cout << "l2 = " << l2Number << endl;
		powerOfTen /= 10;
	}

#endif
	int sum = 123987;

	cout << "result = " << sum << endl;

	string sResult = boost::lexical_cast<string> (sum);

	cout << "sResult = '" << sResult << "'" << endl;

	return 0;
#ifdef TESTING
	index = sResult.size() - 1;

	int digit = 0;
	for(auto it = sResult.begin(); it < sResult.end(); it++)
	{
		digit = boost::lexical_cast<int> (sResult[index]);
		//cout << "lresult[" << index << "] = " << *it << endl;
		lResult.push_back(digit);
		index--;
	}

	int numDigits = sResult.size();
	cout << "Output: ";
	for(auto it = lResult.begin(); it != lResult.end(); it++)
	{
		cout << *it;
		if(--numDigits)
		{
			cout << " -> ";
		}
	}
	cout << endl;
#endif
	return 0;
}
