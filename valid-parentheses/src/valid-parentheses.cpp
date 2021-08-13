//============================================================================
// Name        : valid-parentheses.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://leetcode.com/problems/valid-parentheses/solution/
//============================================================================

#include <iostream>
#include <string>
#include <stack>

using namespace std;

class Solution {
public:
	stack<char>right_bracket;

    bool isValid(string s) {
    	int len = s.length();
    	if(len < 1) return false;

    	int idx = 0;
    	char last_matching_type = 0;
    	while(len)
    	{
    		char btype = s[idx++];
    		if( (btype == '(') || (btype == '{') || (btype == '[') ) {
    			//cout << "left " << btype << endl;
    			char r_type = right_match(btype);
    			right_bracket.emplace(r_type);
    		} else if( (btype == ')') || (btype == '}') || (btype == ']') ) {
    	    	if(right_bracket.empty()) {
    	    		return false;
    	    	}
    			last_matching_type = right_bracket.top();
    			//cout << "right " << btype << ", last match is " << last_matching_type << endl;
    			if(last_matching_type == btype) {
        			//cout << "matching right " << btype << endl;
    				right_bracket.pop();
    			}
    			else {
    				return false;
    			}
    		}
    		len--;
    	}
    	if(right_bracket.empty())
    		return true;
        return false;
    }

    char right_match(char lbracket)
    {
    	if(lbracket == '(') {
    		return lbracket + 1;	// char '(' ascii table offset to right bracket
    	}
    	else {
    		return lbracket + 2;	// chars '{' & '[' ascii table offset to right brackets
    	}
    }
};

using namespace std;

int main() {
	cout << "https://leetcode.com/problems/valid-parentheses/" << endl; // prints https://leetcode.com/problems/valid-parentheses/

	Solution VP;
	bool result = false;
	result = VP.isValid("[[[[{{{{()(){}[]}}}}]]]]");
	cout << "Test 1: " << result << endl;
	result = VP.isValid("))((");
	cout << "Test 2: " << result << endl;

	return 0;
}
