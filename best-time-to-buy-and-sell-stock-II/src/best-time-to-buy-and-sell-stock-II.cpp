//============================================================================
// Name        : best-time-to-buy-and-sell-stock-II.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://leetcode.com/explore/interview/card/top-interview-questions-easy/92/array/564/
//============================================================================

#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>
#include <climits>

using namespace std;

/*
 * Best Time to Buy and Sell Stock II
 *
Say you have an array prices for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like
(i.e., buy one and sell one share of the stock multiple times).

Note: You may not engage in multiple transactions at the same time (i.e., you must sell the stock before you buy again).

Example 1:
Input: [7,1,5,3,6,4]
Output: 7
Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 5-1 = 4.
             Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 6-3 = 3.

Example 2:
Input: [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
             Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are
             engaging multiple transactions at the same time. You must sell before buying again.

Example 3:
Input: [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.
 *
 */

template<class T>
void printVector(vector<T> const &vec) {
	cout << "Vector:" << endl;
	cout << "  [ ";
	for (T val: vec) {
		cout << val << " ";
	}
	cout << "]" << endl;
}


class SolutionII {

public:
    int maxProfit(vector<int>& prices) {
    	int days = prices.size();
    	int profit=0;

    	if(days < 2) {
    		return 0;
    	}

    	for(int i=1; i < days; i++) {
    		int sell_price = prices[i];
    		int buy_price = prices[i-1];
    		if(sell_price > buy_price) {
    			profit += sell_price - buy_price;
    		}
    	}
    	return profit;
    }
};

class Solution {

public:
    int maxProfit(vector<int>& prices) {
    	int days = prices.size();

    	if(days < 2) {
    		return 0;
    	}
    	int max_profit=0;

    	for(int i=1; i < days; i++) {
    		int sell_price = prices[i];
    		int buy_price = prices[i-1];

    		// look for new lower buy price
    		int minimum_buy_price = min(minimum_buy_price, buy_price);
    		// look for new max profit
    		max_profit = max(max_profit, sell_price - minimum_buy_price);
    	}
    	return max_profit;
    }
};


int main() {
	cout << "https://leetcode.com/explore/interview/card/top-interview-questions-easy/92/array/564/" << endl;

	Solution Stocks;
	vector<int> prices{7,1,5,3,6,4};
	//vector<int> prices{7,6,4,4,3,1};
	printVector(prices);
	int profit = Stocks.maxProfit(prices);
	cout << "Max profit = $" << profit << endl;
	return 0;
}
