//============================================================================
// Name        : reverse-polish-notation.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://leetcode.com/problems/evaluate-reverse-polish-notation/
//============================================================================

#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <algorithm>
#include <functional>	// std::function - Class that can wrap any kind of callable element
						//                 (such as functions and function objects) into a copyable
						//                 object, and whose type depends solely on its call
						//                 signature (and not on the callable element type itself).

using namespace std;

/*
Evaluate the value of an arithmetic expression in Reverse Polish Notation.

Valid operators are +, -, *, /. Each operand may be an integer or another expression.

Note:

Division between two integers should truncate toward zero.
The given RPN expression is always valid. That means the expression would always
evaluate to a result and there won't be any divide by zero operation.
Example 1:

Input: ["2", "1", "+", "3", "*"]
Output: 9
Explanation: ((2 + 1) * 3) = 9
Example 2:

Input: ["4", "13", "5", "/", "+"]
Output: 6
Explanation: (4 + (13 / 5)) = 6
Example 3:

Input: ["10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"]
Output: 22
Explanation:
  ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22
 */

vector<string> TestTokens{"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"};

class Solution {
	// store the operators in a look-up that maps to their evaluation function
	unordered_map<std::string, function<int(int,int)>> valid_operators = {
			{ "+", []( int left, int right ) { int result = left + right; cout << "OP: " << left << " + " << right << " = " << result << endl; return result; } },
			{ "-", []( int left, int right ) { int result = left - right; cout << "OP: " << left << " - " << right << " = " << result << endl; return result; } },
			{ "*", []( int left, int right ) { int result = left * right; cout << "OP: " << left << " * " << right << " = " << result << endl; return result; } },
			{ "/", []( int left, int right ) { int result = left / right; cout << "OP: " << left << " / " << right << " = " << result << endl; return result; } }
	};

	bool is_operator( const std::string& chr )
	{
		return valid_operators.find( chr ) != valid_operators.end();
	}
public:
	int evalRPN(vector<string>& tokens) {
		auto numbersStack = std::stack<int>();

		for( auto& tok : tokens )
		{
			// If its an operator we are guaranteed by the problem to
			// have at least 2 numbers on the stack
			// This also ensures that using the map '[]' operator
			// with map variable valid_operators will return a reference
			// to the lambda function and invoke the function with the
			// presented input arguments.  Very nice!
			if( is_operator( tok ) )
			{
				// left + right will be reversed due to the stack
				const auto right = numbersStack.top();
				numbersStack.pop();
				const auto left = numbersStack.top();
				numbersStack.pop();

				// push the result of the valid_operators onto the stack
				numbersStack.push( valid_operators[tok]( left, right ) );
			}
			else
			{
				// just save the number - note use of std lib string to integer
				numbersStack.push( stoi( tok ) );
			}
		}

		// The final result should be on stack top
		return numbersStack.top();
	}

	int recursiveEvalRPN(vector<string>& tokens) {
		auto t = tokens.back(); tokens.pop_back();
		if (isdigit(t.back())) return stoi(t);
		int n2 = evalRPN(tokens), n1 = evalRPN(tokens);
		return t[0] == '+' ? n1 + n2 : t[0] == '-' ? n1 - n2 : t[0] == '*' ? n1 * n2 : n1 / n2;
	}
};
int main() {
	cout << "https://leetcode.com/problems/evaluate-reverse-polish-notation/" << endl;
	Solution ERPN;

	int result = ERPN.evalRPN(TestTokens);
	cout << "EvalRPN result = " << result << endl;

	return 0;
}
