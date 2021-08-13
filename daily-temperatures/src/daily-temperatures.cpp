//============================================================================
// Name        : daily-temperatures.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://leetcode.com/problems/daily-temperatures/
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <stack>
#include <numeric>
#include "big-testcase.h"

using namespace std;

struct DailyTemps
{
    int		day;
    int		temperature;
};

template<class T>
void printVector(vector<T> const &vec) {
	cout << "Vector:" << endl;
	cout << "  [ ";
	for (T val: vec) {
		cout << val << " ";
	}
	cout << "]" << endl;
}



vector<int> DailyTemps0 {73,74,75,71,69,72,76,73};
vector<int> DailyTemps1 {73,74,75,71,69,72,76,73,89,62,70,58,47,47,46,76,100,70,71,69,72,76,73,89,62,70,58};
vector<int> DailyTemps2 {89,62,70,58,47,47,46,76,100,70};
vector<int> DailyTemps3 {73,72,71,70,69,68,67,74};



/*
 * Daily Temperatures
 *
Given a list of daily temperatures T, return a list such that, for each day in the input, tells you -

	How many days you would have to wait until a warmer temperature.

If there is no future day for which this is possible, put 0 instead.

For example, given the list of temperatures
T = [73, 74, 75, 71, 69, 72, 76, 73],
your output should be
[1, 1, 4, 2, 1, 1, 0, 0].

Note: The length of temperatures will be in the range [1, 30000].
Each temperature will be an integer in the range [30, 100].
 */
class BruteForceSolution {

public:
	vector<int> dailyTemperatures(vector<int>& T) {
		int num_temps = T.size();
		if(num_temps < 2) {
			if(num_temps)
				T[0] = 0;
			return T;
		}

		int i = 0;
		for(; i < num_temps && T[i+1] > T[i]; i++) {
			T[i] = 1;
		}
		int j = i;
		int k = j+1;

		while(j < num_temps) {
			while( k < num_temps && T[k] <= T[j]) {
				k++;
			}
			if(k == num_temps)
				T[j] = 0;
			else {
				T[j] = k - j ;
			}
			j++;
			k = j+1;
		}

		return T;
	}
};

class SolutionReverse {
    stack<int> indexStack;
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        int len = T.size();
        vector<int> result(len);	// default value of elements is zero

        indexStack.push(len - 1);	// this could be (-1)
        // looping from right to left, starting from the penultimate element
        // Note: for loop will not start with len < 2
        for (int i = len - 2, n; i >=0; --i) {
            n = T[i];
            // removing all the indexes stacked before if they are smaller
            while (indexStack.size() && n >= T[indexStack.top()]) {
            	indexStack.pop();
            }
            // if we still have something in the stack, we update the result
            if (indexStack.size()) {
            	result[i] = indexStack.top() - i;
            }
            // updating the stack
            indexStack.push(i);
        }
        return result;
    }
};

// This is the easier to understand solution
class SolutionForward {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
    	int numDays = T.size();
    	stack<int> indexStack;
    	vector<int> result(numDays, 0);

    	// 	How many days you would have to wait until a warmer temperature.
    	for (int i = 0; i < numDays; ++i) {
    		cout << "Testing Day " << i << ": " << endl;
    		if(!indexStack.empty())
    			printf("Comparing day %d=%d  <  day %d=%d\n", indexStack.top(), T[indexStack.top()], i, T[i]);
    		// while stack is not empty AND temperature on stack is less than day_i's temperature:
    		//   - pop day index from stack
    		while (!indexStack.empty() and T[indexStack.top()] < T[i]) {
    			int j = indexStack.top();
        		printf("  Warmer day found for day %d on day %d, a %d day wait\n", j, i, i - j);
    			indexStack.pop();
    			result[j] = i - j;
    		}
    		printf("Adding day %d, T=%d to stack\n", i, T[i]);
    		indexStack.push(i);
    	}
    	return result;
    }
};


int main() {
	cout << "https://leetcode.com/problems/daily-temperatures/" << endl;

	SolutionForward DT;
	// BruteForceSolution DT;

	vector<int>& tempVector = DailyTemps3;
	cout << "Input Days [";
	for(auto itr=begin(tempVector); itr != end(tempVector); itr++) {
		cout << *itr;
		if(itr+1 != end(tempVector)) cout << ", ";
	}
	cout << "]" << endl;

	vector<int> resultVector = DT.dailyTemperatures(tempVector);

	cout << "Output Days [";
	for(auto itr=begin(resultVector); itr != end(resultVector); itr++) {
		cout << *itr;
		if(itr+1 != end(resultVector)) cout << ", ";
	}
	cout << "]" << endl;
	return 0;
}
